fn string_to_number(s: &str) -> i32 {
    s.trim().parse().expect("enter a number!")
}
  
#[cfg(test)]
mod tests {
    use super::string_to_number;
    use rand::prelude::*;

    #[test]
    fn returns_expected() {
      assert_eq!(string_to_number("1234"), 1234);
      assert_eq!(string_to_number("605"), 605);
      assert_eq!(string_to_number("1405"), 1405);
      assert_eq!(string_to_number("-7"), -7);
      assert_eq!(string_to_number("0"), 0);
      assert_eq!(string_to_number("123456789"), 123456789);
      assert_eq!(string_to_number("1"), 1);
      assert_eq!(string_to_number("-123"), -123);
      assert_eq!(string_to_number("-123412"), -123412);      
    }

    #[test]
    fn works_on_random() {
        let mut rng = thread_rng();
        for _ in 0..5 {
            let num : i32 = rng.gen();
            let input = num.to_string();
            assert_eq!(string_to_number(&input), num);
        }        
    }
}