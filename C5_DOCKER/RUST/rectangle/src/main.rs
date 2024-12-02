use std::collections::HashMap;

use rayon::prelude::*;

#[derive(Debug)]
struct Rectangle {
    height: f64,
    width: f64,
}

impl Rectangle {
    fn init(width: f64, height: f64) -> Rectangle {
        Rectangle { height, width }
    }

    fn surface(&self) -> f64 {
        self.width * self.height
    }
}

fn main() {
    let mut v: Vec<Rectangle> = Vec::new();

    for l in 1..10000000000usize {
        v.push(Rectangle {
            width: l as f64,
            height: l as f64,
        });
    }

    /**   let mut tot_surf: f64 = 0.0;

       for r in v.iter() {
           tot_surf += r.surface();
       }

       println!("TOT {tot_surf}");
    */
    let tot_surf: f64 = v.iter().map(|r| r.surface()).sum();

    println!("SEC TOT {tot_surf}");

    let mut m: HashMap<String, u32> = HashMap::new();

    m.insert("Hello".to_string(), 5);
    m.insert("World".to_string(), 10);

    for k in m.keys() {
        println!("==> {k}");
    }

    for k in m.values() {
        println!("==> {k}");
    }

    for (k, v) in m.iter() {
        println!("==> {k}");
    }

    let rect = Rectangle::init(10.0, 10.0);
    println!("Surface is {}", rect.surface());
}
