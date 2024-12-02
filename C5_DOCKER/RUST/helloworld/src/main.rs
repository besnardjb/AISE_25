use std::{
    cmp,
    io::{self},
};

use rand::Rng;

struct Hello {
    age: u32,
    name: String,
}

impl Hello {}

fn print(str: &String) {
    println!("==> Valeur: {str}");
}

fn main() {
    /* Ownership */
    let a = String::new();
    //let b = &a;
    print(&a);
    println!("{a}");

    /* TUPLE */
    let a = (2, 'c');
    println!("{} {}", a.0, a.1);

    /* Struct */
    let h = Hello {
        age: 3,
        name: String::from("Bob"),
    };

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
