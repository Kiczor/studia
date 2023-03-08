exception Zle;;

let rec for_all f xs =
match xs with
| [] -> true
| x::xs -> if (f x) then (for_all f xs) else false;;

let rec mult_list xs =
match xs with
| [] -> 1
| x::xs -> if x == 0 then 0 else x * mult_list xs

let rec sorted xs =
match xs with
| [] -> true
| x::[] -> true
| x::y::xs -> if x > y then false else sorted xs
