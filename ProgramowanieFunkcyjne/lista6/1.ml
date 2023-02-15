let rec fix f x = f (fix f) x

let fib_f fib n =
  if n <= 1 then n
  else fib (n - 1) + fib (n - 2)

let fibonacci = fix fib_f;;

let rec fix_with_limit lim f x = 
  if lim == 0 
  then raise ( Failure "za duzo" )
  else f (fix_with_limit (lim - 1) f) x;;

let fiblimit = fix_with_limit 6 fib_f

let pam = Hashtbl.create 0;;
let rec fix_memo f x =
  try Hashtbl.find pam (f, x) with Not_found 
  -> let w = (f (fix_memo f) x)
    in begin Hashtbl.add pam (f, x) w; w end;;

let fibmem = fix_memo fib_f
