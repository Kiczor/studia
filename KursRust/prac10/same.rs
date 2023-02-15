fn comp(a: Vec<i64>, b: Vec<i64>) -> bool {
    if a.len() != b.len() { return false; }
    let mut asv = a.iter().map(|x| num::abs(*x)).collect::<Vec<i64>>();;
    let mut bsv = b;
    
    asv.sort();
    bsv.sort();
    
    for i in 0..asv.len() { if asv[i] * asv[i] != bsv[i] { return false; } }
    return true;
}