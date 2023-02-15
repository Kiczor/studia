fn dna_strand(dna: &str) -> String {
    let res: String = dna.chars().map(|c| match c { 'A' => 'T', 'C' => 'G', 'G' => 'C', 'T' => 'A', _ => panic!() }).collect();
    return res;
}


#[cfg(test)]
mod tests2 {
    use super::dna_strand;

    fn dotest(s: &str, expected: &str) {
        let actual = dna_strand(s);
        assert!(actual == expected, 
            "With dna = \"{s}\"\nExpected \"{expected}\" but got \"{actual}\"")
    }
    
    #[test]
    fn fixed_tests() {
        dotest("A","T");
        dotest("GTC","CAG");
        dotest("C","G");
        dotest("CTCTCTCTCTCTCTCT","GAGAGAGAGAGAGAGA");
        dotest("ACGTGCA", "TGCACGT")
    }