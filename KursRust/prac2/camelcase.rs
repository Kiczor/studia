fn camel_case(str: &str) -> String {
    str.split_whitespace().map(|s| s[0..1].to_uppercase() + &s[1..]).collect()
}