fn longest_slide_down(pyramid: &[Vec<u16>]) -> u16 {
    let mut dp: Vec<u16> = Vec::new();
    dp.push(0);
    for l in pyramid.iter()
    {
        let mut newdp: Vec<u16> = Vec::new();
        for (i, x) in l.iter().enumerate()
        {
            let mut y = 0;
            if i == 0
            {
                y = dp[i];
            }
            else if i == dp.len()
            {
                y = dp[i - 1];
            }
            else
            {
                y = std::cmp::max(dp[i], dp[i - 1]);
            }
            newdp.push(y + x);
        }
        dp = newdp;
    }
    return *dp.iter().max().unwrap();
}