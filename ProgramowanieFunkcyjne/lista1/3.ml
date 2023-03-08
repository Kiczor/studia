let hd s = s 0;;
let add s a = fun x -> (s x) + a;;
let map s f = fun x -> f (s x);;
let map2 s1 s2 f = fun x -> f (s1 x) (s2 x);;
let replace s a n = fun x -> if x mod n == 0 then a else (s x);;
let take s n = fun x -> (s (n * x));;
let rec tabulate s x y = if x > y then [] else [(s x)] @ (tabulate s (x + 1) y);;
let rec scan f a s = fun x -> if x == 0 then (f a (s 0)) else (f (scan f  s) (s x));;
