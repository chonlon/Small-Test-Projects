use std::fmt::Debug;
use std::net::SocketAddr;
use std::sync::{Arc, Mutex, RwLock};
use serde::{Deserialize, Serialize};

use axum::{routing::{get, post}, Router, Server, Json, async_trait, TypedHeader, Extension};
use axum::extract::{FromRequest, RequestParts};
use axum::headers::Authorization;
use axum::headers::authorization::Bearer;
use axum::http::StatusCode;
use axum::response::Html;

use jsonwebtoken as jwt;
use serde::de::DeserializeOwned;

const SECRET: &[u8] = b"secret";

#[derive(Clone, Debug, Serialize, Deserialize)]
struct Todo {
    id: u32,
    user_id: u32,
    title: String,
    completed: bool,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
struct CreateTodo {
    title: String,
}

#[derive(Clone, Debug, Serialize, Deserialize, Default)]
struct LoginRequest {
    email: String,
    password: String,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
struct LoginResponse {
    token: String,
}

#[derive(Clone, Debug, Default)]
struct TodoStore {
    todos: Arc<RwLock<Vec<Todo>>>,
}


#[derive(Clone, Debug, Serialize, Deserialize)]
struct Claim {
    id: u32,
    login_request: LoginRequest,
    exp: u64,
}

impl Default for Claim {
    fn default() -> Self {
        Claim {
            id: 0,
            exp: 7 * 24 * 60 * 60 + get_epoch(),
            login_request: LoginRequest::default(),
        }
    }
}

struct ClaimsWrapper<T> {
    pub claim: T,
}

#[async_trait]
impl<B, T> FromRequest<B> for ClaimsWrapper<T>
    where B: Send + Debug,
          T: DeserializeOwned + 'static + Default
{
    type Rejection = StatusCode;
    async fn from_request(req: &mut RequestParts<B>) -> Result<Self, Self::Rejection> {
        println!("{:?}", req);
        let TypedHeader(Authorization(bearer)) = TypedHeader::<Authorization<Bearer>>::from_request(req).await.unwrap();
        let token = bearer.token();
        println!("{:?}", token);

        let token1 = req.headers().get("Authorization").unwrap().to_str().unwrap();
        println!("{:?}", token1);

        let key = jwt::DecodingKey::from_secret(SECRET);
        let claim = jwt::decode::<T>(token, &key, &jwt::Validation::default())
            .map_err(|_| StatusCode::UNAUTHORIZED)?
            .claims;

        Ok(ClaimsWrapper { claim })
    }
}

#[tokio::main]
async fn main() {
    let state = TodoStore {
        todos: Arc::new(RwLock::new(vec![
            Todo {
                id: 1,
                user_id: 1,
                title: "todo1".to_string(),
                completed: false,
            },
            Todo {
                id: 2,
                user_id: 1,
                title: "todo2".to_string(),
                completed: false,
            },
        ])),
    };
    let router = Router::new()
        .route("/", get(index_handler))
        .route("/todos", get(todo_handler).post(create_todo_handler).layer(Extension(state.clone())))
        .route("/login", post(login_handler))
        .route("/test", post(test_handler));

    let addr = SocketAddr::from(([127, 0, 0, 1], 8080));
    println!("Listening on {}", addr);
    Server::bind(&addr).serve(router.into_make_service()).await.unwrap();
}

async fn index_handler() -> Html<String> {
    Html("<h1>Hello, world!</h1>".to_string())
}

async fn todo_handler(Extension(todo_store): Extension<TodoStore>) -> Json<Vec<Todo>> {
    Json(todo_store.todos.read().unwrap().clone())
}

async fn create_todo_handler(ClaimsWrapper { claim }: ClaimsWrapper<Claim>, Json(create_todo): Json<CreateTodo>, Extension(todo_store): Extension<TodoStore>) -> StatusCode {
    println!("accepted {:?}", create_todo);
    println!("accepted {:?}", todo_store);

    todo_store.todos.write().unwrap().push(
        Todo {
            id: 3, // assume id is auto increment
            user_id: claim.id,
            title: create_todo.title,
            completed: false,
        }
    );
    StatusCode::CREATED
}


async fn login_handler(Json(login): Json<LoginRequest>) -> Json<LoginResponse> {
    println!("accepted {:?}", login);

    let claim = Claim {
        id: 1, // assume we have a user id in the database
        login_request: login,
        ..Default::default()
    };

    let key = jwt::EncodingKey::from_secret(SECRET);
    let token = jwt::encode(&jwt::Header::default(), &claim, &key).unwrap();
    println!("token: {}", token);

    Json(LoginResponse { token })
}

async fn test_handler(ClaimsWrapper { claim }: ClaimsWrapper<Claim>) -> Json<Claim> {
    println!("accepted {:?}", claim);
    Json(claim)
}

// get_epoch returns the number of seconds since the Unix epoch
fn get_epoch() -> u64 {
    let now = std::time::SystemTime::now();
    let since_epoch = now.duration_since(std::time::UNIX_EPOCH).unwrap();
    since_epoch.as_secs()
}