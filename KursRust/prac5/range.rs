mod solution {
    pub fn range_extraction(a: &[i32]) -> String {
        let mut res = String::new();
        let mut p: i32 = a[0];
        let mut k: i32 = a[0];
        for x in a.iter().skip(1)
        {
            if x - 1 != k
            {
                res.push_str(",");
                if k - p > 1
                {
                    res.push_str(&p.to_string());
                    res.push_str("-");
                    res.push_str(&k.to_string());
                }
                else if k - p == 1
                {
                    res.push_str(&p.to_string());
                    res.push_str(",");
                    res.push_str(&k.to_string());
                }
                else
                {
                    res.push_str(&p.to_string());
                }
                p = *x;
                k = *x;
            }
            else
            {
                k = *x;
            }
        }
        res.push_str(",");
        if k - p > 1
        {
            res.push_str(&p.to_string());
            res.push_str("-");
            res.push_str(&k.to_string());
        }
        else if k - p == 1
        {
            res.push_str(&p.to_string());
            res.push_str(",");
            res.push_str(&k.to_string());
        }
        else
        {
            res.push_str(&p.to_string());
        }
        return res[1..res.len()].to_string();
    }
}