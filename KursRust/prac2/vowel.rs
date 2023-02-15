fn get_count(string: &str) -> usize {
  let mut vowels_count: usize = 0;

  vowels_count = string.chars().fold(0, | cnt, x | match x { 'a' | 'e' | 'i' | 'o' | 'u' => cnt + 1, _ => cnt });
  
  vowels_count
}