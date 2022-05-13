use std::net::SocketAddr;
use serde::{Deserialize, Serialize};

use axum::{routing::{get, post},Router, Server, Json};
use axum::http::StatusCode;
use axum::response::Html;

use jsonwebtoken as jwt;

const SECRET: &[u8] = b"secret";

#[derive(Clone, Debug, Serialize, Deserialize)]
struct Todo {
    id: u32,
    title: String,
    completed: bool,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
struct CreateTodo {
    title: String,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
struct LoginRequest {
    email: String,
    password: String,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
struct LoginResponse {
    token: String,
}

#[tokio::main]
async fn main() {
    let router = Router::new()
        .route("/", get(index_handler))
        .route("/todos", get(todo_handler).post(create_todo_handler))
        .route("/login", post(login_handler));


    let addr = SocketAddr::from(([127, 0, 0, 1], 8080));
    println!("Listening on {}", addr);
    Server::bind(&addr).serve(router.into_make_service()).await.unwrap();
}

async fn index_handler() -> Html<String> {
    Html("<h1>Hello, world!</h1>".to_string())
}

async fn todo_handler() -> Json<Vec<Todo>> {
    Json(vec![
        Todo {
            id: 1,
            title: "Todo 1".to_string(),
            completed: false,
        },
        Todo {
            id: 2,
            title: "Todo 2".to_string(),
            completed: false,
        },
    ])
}

async fn create_todo_handler(Json(create_todo): Json<CreateTodo>) -> StatusCode {
    println!("accepted {:?}", create_todo);
    StatusCode::CREATED
}


async fn login_handler(Json(login): Json<LoginRequest>) -> Json<LoginResponse> {
    println!("accepted {:?}", login);

    let key = jwt::EncodingKey::from_secret(SECRET);
    let token = jwt::encode(&jwt::Header::default(), &login, &key).unwrap();
    println!("token: {}", token);

    Json(LoginResponse {
        token: jwt::encode(&jwt::Header::default(), &login, &key).unwrap(),
    })
}