use std::{
    cmp,
    io::{self},
};

use rand::Rng;

fn main() {
    println!("Guess the number !");

    let toguess: u64 = rand::thread_rng().gen_range(0..100);

    loop {
        println!("Please enter number:");
        let mut num = String::new();

        io::stdin().read_line(&mut num).expect("Crash");

        let num: u64 = num.trim().parse().expect("Not a number");

        match toguess.cmp(&num) {
            cmp::Ordering::Less => println!("Plus petit"),
            cmp::Ordering::Equal => {
                println!("Gagné");
                break;
            }
            cmp::Ordering::Greater => println!("Plus grand"),
        }
    }
}
