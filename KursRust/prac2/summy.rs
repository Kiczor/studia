fn summy(strng: &str) -> i32 {
    strng.split(' ').map(|x| x.parse::<i32>().unwrap()).sum()
}