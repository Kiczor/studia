let listtoint l =
let rec changing xs acc = if xs == [] then acc else changing (List.tl xs) ((List.hd xs) + 10 * acc)
in changing l 0;;

let listtoint2 l = List.fold_left (fun x y -> 10 * x + y) 0 l;;
