use std::io;
use std::io::prelude::*;

fn main()
{
    let mut res: i64 = 0;
    let mut sum: i64 = 0;
    let mut vr: Vec<i64> = Vec::new();

    let stdin = io::stdin();
    for line in stdin.lock().lines() {
        let s = line.unwrap();
        println!("{}", s);
        if s == ""
        {
            res = std::cmp::max(res, sum);
            vr.push( - sum);
            sum = 0;
        }
        else
        {
            let x: i64 = s.parse().unwrap();
            sum += x;
        }
    }   
    vr.sort();

    println!("result: {}, 3 best: {}", res, - (vr[0] + vr[1] + vr[2]) );
}