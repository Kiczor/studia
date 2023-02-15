fn print(n: i32) -> Option<String> {
    if n % 2 == 0 || n < 0 { return None; }
    
    let mut res: String = String::new();
    let mut stars: String = String::new();
    let mut spaces: String = String::new();
    stars.push('*');
    for i in 0..(n/2) {spaces.push(' ');}
    while spaces.len() > 0
    {
        res.push_str(&spaces);
        res.push_str(&stars);
        res.push('\n');
        spaces.pop();
        stars.push_str("**");
    }
    
    res.push_str(&spaces);
    res.push_str(&stars);
    res.push('\n');
    
    while stars.len() > 2
    {
        spaces.push(' ');
        stars.pop(); stars.pop();
        res.push_str(&spaces);
        res.push_str(&stars);
        res.push('\n');
    }
    
    return Some(res);
}

