use std::fs::File;
use std::io::{BufRead, BufReader, Read};

fn main() {
    let file = File::open("../data.txt").unwrap();
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

    print!("{}", sum);
}
