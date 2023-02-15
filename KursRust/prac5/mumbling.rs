fn accum(s:&str)->String {
    let mut res: String = String::new();
    for (i, c) in s.chars().enumerate()
    {
        if i != 0 { res.push('-'); }
        res.push(c.to_ascii_uppercase());
        res.push_str(&c.to_ascii_lowercase().to_string().repeat(i));
    }
    res
}