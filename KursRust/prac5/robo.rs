pub fn execute(code: &str) -> String {
    if code == ""
    {
        return "*".to_string();
    }
    
    let directions = [(0, 1), (1, 0), (0, -1), (-1, 0)];
    let mut visited = std::collections::HashMap::new();
    let mut x = 0;
    let mut y = 0;
    let mut maxx = 0;
    let mut minx = 0;
    let mut maxy = 0;
    let mut miny = 0;
    let mut diridx = 0;
    visited.insert( (x, y), 1 );
    let mut cb = code.as_bytes();
    for (i, &c) in cb.iter().enumerate()
    {
        if c != b'F' && c != b'R' && c != b'L' { continue; }
        
        let mut times = 1;
        if i != code.len() - 1
        {
            if cb[i + 1] != b'F' && cb[i + 1] != b'R' && cb[i + 1] != b'L'
            {
                let mut b = i + 1;
                while b + 1 < code.len() && cb[b + 1] != b'F' && cb[b + 1] != b'R' && cb[b + 1] != b'L'
                {
                    b += 1;
                }
                times = code[(i + 1)..(b + 1)].parse().unwrap();
            }
        }
        
        if c == b'F'
        {
            for it in 0..times
            {
                x += directions[diridx].0;
                y += directions[diridx].1;
                visited.insert( (x, y), 1 );                
            }
        }
        if c == b'R'
        {
            for it in 0..times
            {
                diridx = (diridx + 1) % 4
            }
        }
        if c == b'L'
        {
            for it in 0..times
            {
                diridx = ((diridx as i32 - 1 + 4) % 4) as usize
            }
        }
        
        maxx = std::cmp::max( maxx, x );
        minx = std::cmp::min( minx, x );
        maxy = std::cmp::max( maxy, y );
        miny = std::cmp::min( miny, y );
    }
    
    let mut res = String::new();
    for i in minx..(maxx + 1)
    {
        for j in miny..(maxy + 1)
        {
            if visited.contains_key( &(i, j) )
            {
                res.push('*');
            }
            else
            {
                res.push(' ');
            }
        }
        if i != maxx { res.push('\r'); res.push('\n'); }
    }
    return res;
}