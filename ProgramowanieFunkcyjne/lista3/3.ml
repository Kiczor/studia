let polynomial l x =
let rec cnt xs acc = if xs == [] then acc else cnt (List.tl xs) ((acc *. x) +. (List.hd xs))
in cnt l 0.0;;
let polynomial2 l x = List.fold_left (fun a b -> (a *. x) +. b) 0.0 l;;
