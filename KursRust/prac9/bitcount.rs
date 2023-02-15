fn count_bits(n: i64) -> u32 {
    format!("{:b}", n).chars().fold(0, |a, c| match c { '1' => a + 1, _ => a } )
}