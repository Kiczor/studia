fn count_red_beads(n: u32) -> u32 {
    if n >= 2
    {
        return (n - 1) * 2;
    }
    0
}

#[test]
fn test2() {
  assert_eq!(count_red_beads(6), 10);
  assert_eq!(count_red_beads(2), 2);
  assert_eq!(count_red_beads(1), 0);
  assert_eq!(count_red_beads(1001), 2000);
  assert_eq!(count_red_beads(129), 256);
}