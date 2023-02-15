use std::io;
use std::io::prelude::*;

fn main()
{
    let mut score: i32 = 0;

    let stdin = io::stdin();
    for line in stdin.lock().lines() {
        let s = line.unwrap();
        let bs = s.as_bytes();
        let x: i32 = (bs[0] - b'A' + 1).into();
        let y: i32 = (bs[2] - b'X' + 1).into();
        println!("x:{}, y:{}", x, y);
        
        match (x, y)
        {
            (1, 3) => score += 6 + 2,
            (2, 3) => score += 6 + 3,
            (3, 3) => score += 6 + 1,
            (_, 2) => score += x + 3, //draw
            (1, 1) => score += 3,
            (2, 1) => score += 1,
            (3, 1) => score += 2,
            _ => ()
        }
    }   

    println!("result: {}", score );
}