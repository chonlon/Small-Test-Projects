use tokio::net::{TcpStream, TcpListener};
use tokio::io::{AsyncReadExt, AsyncWriteExt};
use std::env;

#[tokio::main]
async fn main() {
  let args = env::args().nth(1).unwrap();
  let listener = TcpListener::bind(args).await.unwrap();
  println!("{listener:?}");
  
  loop {
    let (mut stream, addr) = listener.accept().await.unwrap();
    let mut buf  = [0 ; 65535];
    //let buf : [i8: 65535] = [0 as i8: 65535];

    println!("{stream:?} {addr:?}");

    tokio::spawn(async move {
      loop {
        // let buf:[i8; 1000] = buf[0..100];
        // let mut buf = &buf[..];
        let n = stream
        .read(&mut buf)
        .await
        .expect("failed to read data from socket");
      }
    });
  }
}
