use std::collections::HashSet;

struct Sudoku{
    data: Vec<Vec<u32>>,
}

impl Sudoku{
    fn is_valid(&self) -> bool {      
        let n = self.data.len();
        let sqn: usize = num::integer::sqrt( n );
        
        //checking size
        if self.data.iter().fold( true, |a, x| a && (x.len() == n) ) == false { return false; }
        if sqn * sqn != n { return false; }
        
        //validating rows
        for v in self.data.iter()
        {
            let mut nums: HashSet<u32> = HashSet::new();
            for x in v.iter()
            {
                if (*x > (n as u32)) || (*x < 1) { return false; }
                nums.insert(*x);
            }
            
            if nums.len() != n { return false; }
        }
        
        //validating columns
        for j in 0..n
        {
            let mut nums: HashSet<u32> = HashSet::new();
            for i in 0..n
            {
                let x = self.data[i][j];
                if (x > (n as u32)) || (x < 1) { return false; }
                nums.insert(x);
            }
            if nums.len() != n { return false; }
        }
        
        //validating squares
        for i in 0..sqn
        {
            for j in 0..sqn
            {
                let mut nums: HashSet<u32> = HashSet::new();
                for sqi in (i * sqn)..((i + 1) * sqn)
                {
                    for sqj in (j * sqn)..((j + 1) * sqn)
                    {
                        let x = self.data[sqi][sqj];
                        if (x > (n as u32)) && (x < 1) { return false; }
                        nums.insert(x);
                    }
                }
                if nums.len() != n { return false; }
            }
        }
        
        return true;
    }
}