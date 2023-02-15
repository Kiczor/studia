fn solution(num: i32) -> i32 {
    if num < 0 
    {
        return 0;
    }
    let d3 = (num - 1) / 3;
    let d5 = (num - 1) / 5;
    let d15 = (num - 1) / 15;
    3 * ((d3 * (d3+1)) / 2) + 5 * ((d5 * (d5+1)) / 2) - 15 * ((d15 * (d15 + 1)) / 2)
}