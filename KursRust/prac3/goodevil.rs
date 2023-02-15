fn good_vs_evil(good: &str, evil: &str) -> String {
    let g: [i32; 6] = good.split(' ').map(|x| x.parse::<i32>().unwrap()).collect::<Vec<i32>>().try_into().unwrap();
    let gval = [1,2,3,3,4,10];
    let e: [i32; 7] = evil.split(' ').map(|x| x.parse::<i32>().unwrap()).collect::<Vec<i32>>().try_into().unwrap();
    let eval = [1,2,2,2,3,5,10];
    let resgood = g.iter().zip(gval.iter()).fold(0, |a, (x, y)| a + x * y);
    let resevil = e.iter().zip(eval.iter()).fold(0, |a, (x, y)| a + x * y);
    let res = resgood - resevil;
    if res > 0
    {
        return String::from("Battle Result: Good triumphs over Evil");
    }
    if res < 0
    {
        return String::from("Battle Result: Evil eradicates all trace of Good");
    }
    String::from("Battle Result: No victor on this battle field")
}