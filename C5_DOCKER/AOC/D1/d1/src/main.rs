use clap::Parser;
use std::collections::HashMap;
use std::fs::File;
use std::io::{BufReader, Read};

#[derive(Parser)]
struct Args {
    #[arg(long = "file", short = 'f')]
    /// Pass a file to parse
    file: String,
    #[arg(short, long)]
    /// Not required
    lol: Option<String>,
}

fn main() {
    let args = Args::parse();

    let file = File::open(args.file).unwrap();
    let mut reader = BufReader::new(file);
    let mut data = String::new();
    reader.read_to_string(&mut data).unwrap();

    /* Vecteurs A et B pour chaque colonne
     *  Calcul du diff
     * Somme
     */
    let mut a: Vec<u64> = Vec::new();
    let mut b: Vec<u64> = Vec::new();

    for l in data.lines() {
        let vals: Vec<u64> = l.split("   ").map(|v| v.parse().unwrap()).collect();

        if vals.len() != 2 {
            continue;
        }
        a.push(vals[0]);
        b.push(vals[1]);
    }

    a.sort();
    b.sort();

    let sum: u64 = a
        .iter()
        .zip(b.iter())
        .map(|(va, vb)| va.abs_diff(*vb))
        .sum();

    println!("Q1 {}", sum);

    let mut sum: u64 = 0;

    for v1 in a.iter() {
        let mut occ = 0;
        for v2 in b.iter() {
            if v2 == v1 {
                occ += 1;
            }
        }
        sum += occ * v1;
    }

    println!("Q2' {}", sum);

    let sum: u64 = a
        .iter()
        .map(|va| {
            let occ = b.iter().filter(|vb| *va == **vb).count();
            *va * occ as u64
        })
        .sum();
    println!("Q2 {}", sum);

    let mut m: HashMap<u64, u64> = HashMap::new();

    for v1 in b.iter() {
        if let Some(k) = m.get_mut(v1) {
            *k += 1;
        } else {
            m.insert(*v1, 1);
        }
    }

    let tot: u64 = a.iter().map(|v1| v1 * m.get(v1).unwrap_or(&0)).sum();
    println!("Q2'' {}", tot);
}
