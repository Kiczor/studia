let zero f x = x;;
let jeden f x = f(x);;
let dwa f x = (f(f(x));;
let trzy f x = (f(f(f(x))));;
let succ a = fun f x -> (a f (f(x)));;
let add a b = fun f x -> (a f (b f x));;
let is_zero a = if a == zero then true else false;;
let rec cnum_of_int a = if a == 1 then zero else succ (cnum_of_int (a - 1));;
