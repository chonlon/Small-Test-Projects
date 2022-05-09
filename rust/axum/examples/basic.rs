use std::net::SocketAddr;
use serde::{Deserialize, Serialize};

use axum::{routing::get, Router, Server, Json};
use axum::response::Html;

#[derive(Clone, Debug, Serialize, Deserialize)]
struct Todo {
    id: u32,
    title: String,
    completed: bool,
}

#[tokio::main]
async fn main() {
    let router = Router::new()
        .route("/", get(index_handler))
        .route("/todos", get(todohandler).post(create_todohandler));

    let addr = SocketAddr::from(([127, 0, 0, 1], 8080));
    println!("Listening on {}", addr);
    Server::bind(&addr).serve(router.into_make_service()).await.unwrap();
}

async fn index_handler() -> Html<String> {
    Html("<h1>Hello, world!</h1>".to_string())
}

async fn todohandler() -> Json<String> {
    let todo = Todo {
        id: 1,
        title: "Learn Rust".to_string(),
        completed: false,
    };
    Json::from(serde_json::to_string(&todo).unwrap())
}

async fn create_todohandler() {
    todo!();
}
