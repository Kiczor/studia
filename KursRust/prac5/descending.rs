fn descending_order(x: u64) -> u64 {
    let mut x = x;
    let mut r:Vec<u64> = Vec::new();
    while x > 0 
    {
        r.push(x % 10);
        x = x / 10;
    }
    r.sort();
    let mut res = 0;
    let mut d = 1;
    for digit in r
    {
        res += d * digit;
        d = d * 10;
    }
    return res;
}