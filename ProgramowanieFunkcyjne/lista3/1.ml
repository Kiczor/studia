let length = List.fold_left (fun x y -> x + 1) 0;;
let rev xs = List.fold_right (fun x y -> y @ [x]) xs [];;

let filter f xs = List.fold_right (fun x y -> if f x then x::y else y) xs [];;

let rev_map f xs = List.fold_right (fun x y -> y @ [f x]) xs [];;
