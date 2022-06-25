use std::net::SocketAddr;

use axum::{
    middleware::AddExtension,
    routing::{get, Route},
    Extension, Router, Server,
};
use dashmap::DashMap;
use futures::{SinkExt, StreamExt};
use serde::de::Unexpected::Str;

use crate::server::run;

mod msg;

mod server {
    use crate::msg;
    use crate::msg::ChatMessage::{Join, Leave, Say};
    use axum::extract::ws::{Message, WebSocket};
    use axum::extract::WebSocketUpgrade;
    use axum::response::IntoResponse;
    use axum::Extension;
    use dashmap::{DashMap, DashSet};
    use std::collections::HashMap;
    use std::process::exit;
    use std::sync::Arc;
    use tokio::io::AsyncBufReadExt;
    use tokio::sync::broadcast;

    const CAPACITY: usize = 64;

    #[derive(Debug, Clone)]
    pub struct State {
        room_users: DashMap<String, DashSet<String>>,
        user_rooms: DashMap<String, DashSet<String>>,
        msg_sender: broadcast::Sender<msg::Msg>,
    }

    impl Default for State {
        fn default() -> Self {
            let (tx, _rx) = broadcast::channel(CAPACITY);
            Self {
                room_users: Default::default(),
                user_rooms: Default::default(),
                msg_sender: tx,
            }
        }
    }

    #[derive(Debug, Clone, Default)]
    struct ChatState {
        state: Arc<State>,
    }

    struct ChatState2(Arc<State>);

    pub async fn run(
        web_socket: WebSocketUpgrade,
        Extension(chat_state): Extension<ChatState>,
    ) -> impl IntoResponse {
        web_socket.on_upgrade(move |socket| async {
            let rx = chat_state.state.msg_sender.subscribe();
            let (mut socket_tx, mut socket_rx) = socket.split();

            let recv_handle = tokio::spawn(async move {
                while let Some(Ok(msg)) = socket_rx.next().await {
                    match msg {
                        Message::Text(t) => {
                            process_recv(t.as_str().try_into().unwrap(), chat_state.state.clone())
                                .await
                        }
                        _ => {
                            println!("Useless message: {:?}", msg);
                        }
                    }
                }
            });

            let send_handle = tokio::spawn(async move {});

            tokio::select! {
                _ = recv_handle => {},
                _ = send_handle => {},
                // ctrl_c stops the server
                _ = tokio::signal::ctrl_c() => {
                    exit(0);
                },
            }
        })
    }

    async fn process_recv(msg: msg::Msg, state: Arc<State>) {
        match msg.chat_message {
            Join => {
                let room = msg.room.clone();
                let user = msg.username.clone();

                state.room_users.get(&room).map(|users| {
                    users.insert(user.clone());
                });
            }
            _ => {}
        }
    }
}

fn main() {
    let addr = SocketAddr::from(([127, 0, 0, 1], 3000));
    let app = Router::new().route(
        "/ws",
        get(server::run).layer(Extension(server::State::default())),
    );

    Server::bind(&addr).serve(app.into_make_service());

    println!("Hello, world!");
}
