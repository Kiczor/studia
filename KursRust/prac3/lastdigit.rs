fn last_digit(str1: &str, str2: &str) -> i32 {
    let ld1 = str1.chars().last().unwrap().to_digit(10).unwrap();
    let ld2 = str2.chars().last().unwrap().to_digit(10).unwrap();
    let mut cycle = 1;
    let mut x = ld1;
    while (x * ld1) % 10 != ld1
    {
        x = (x * ld1) % 10;
        cycle += 1;
    }
    
    let mut md = 0;
    let mut p = 1;
    for c in str2.chars().rev().collect::<String>().chars()
    {
        let d: u32 = c.to_digit(10).unwrap().try_into().unwrap();
        md = (md + p * d) % cycle;
        p = (p * 10) % cycle;
    }
    
    if str2.len() < 2
    {
        let res: i32 = (ld1.pow(ld2) % 10).try_into().unwrap();
        return res;
    }
    
    if cycle == 1
    {
        let res: i32 = (ld1 % 10).try_into().unwrap();
        return res;
    }
    
    if md == 0
    {
        md = cycle;
    }
    let res: i32 = (ld1.pow( md ) % 10).try_into().unwrap();
    res
}