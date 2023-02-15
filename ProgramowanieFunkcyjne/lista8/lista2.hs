f xs = [ x | x <- xs, x `mod` (head xs) /= 0 ]
s (p:xs) = p:s [ x | x <- (f (p:xs)) ]
primes = s [2..]

pierwsza x = all (\q -> (x `mod` q /= 0) ) (takeWhile (\y -> y * y <= x) [2..])
primes' = 2 : [ x | x <- [3..], pierwsza x ]
primes2' = 2 : [ x | x <- [3..], all (\q -> (x `mod` q /= 0) ) (takeWhile (\y -> y * y <= x) primes2') ]

subsets (h:tl) = if tl == []
    then [[h], []]
    else let s = (subsets tl) in (map (\z -> h:z) s) ++ s 

insertat co gdzie xs = let iter p l = if (length p) == gdzie then (p ++ [co] ++ l) else (iter (p ++ [(head l)]) (tail l)) in (iter [] xs)

skladanie (h:tl) = if tl == [] then h else h ++ (skladanie tl)
iperm (h:tl) = if tl == []
    then [[h]]
    else let w = (iperm tl)
     in (skladanie (map (\x -> [ (insertat h i x) | i <- [0..(length x)]]) w))

cantor xs ys = let iter dl res = if (dl > (length xs)) || (dl > (length ys)) then res else iter (dl + 1) (res ++ (zip (take dl xs) (reverse (take dl ys)))) in iter 1 []

caniter l1 l2 [] x = (zip l1 (reverse l2))
caniter l1 l2 x [] = (zip l1 (reverse l2))
caniter l1 l2 (h1:p1) (h2:p2) = (zip l1 (reverse l2)) ++ (caniter (l1 ++ [h1]) (l2 ++ [h2]) p1 p2)

cantor2 xs ys = caniter [] [] xs ys

delete elem (hd:tl) = if elem == hd then tl else hd : (delete elem tl)
sperm [] = [[]]
sperm [x] = [[x]]
sperm list = concat (map (\a -> map (\x -> a : x) (sperm (delete a list))) list)

merge [] [] = []
merge [] xs = xs
merge xs [] = xs
merge (h1:t1) (h2:t2) = if h1 < h2 then h1:(merge t1 (h2:t2)) else h2:(merge (h1:t1) t2)

qsort [] = []
qsort (h:tl) = merge (qsort [x | x <- tl, x < h]) (h:(qsort [x | x <- tl, x >= h] ))
