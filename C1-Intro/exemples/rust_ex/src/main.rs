use colored::*;
use rouille::{Response, Server};
use serde::Serialize;

#[derive(Serialize)]
struct Toserialize {
    a: i32,
    b: i32,
}

fn main() {
    println!("Hello, world!");
    let mut vec: Vec<Toserialize> = Vec::new();

    for i in 0..99 {
        vec.push(Toserialize { a: i, b: i + 1 });
    }

    let server = Server::new("localhost:1235", move |request| Response::json(&vec)).unwrap();
    println!("Listening on {:?}", server.server_addr());
    server.run();
}
