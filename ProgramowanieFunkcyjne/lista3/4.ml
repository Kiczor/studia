let rec rpolynomial xs n =
if xs == [] then 0.0
else (List.hd xs) +. (n *. (rpolynomial (List.tl xs) n));;

let rpolynomial2 xs n = List.fold_right (fun a b -> a +. (b *. n)) xs 0.0;;

let rpolynomial3 l n =
let rec cnt xs mn acc = if xs == [] then acc
else cnt (List.tl xs) (mn *. n) ((mn *. (List.hd xs)) +. acc)
in cnt l 1.0 0.0;;

let rpolynomial4 l n = (fst (List.fold_left (fun a b -> ((fst a) +. ((snd a) *. b), (snd a) *. n ) ) (0.0, 1.0) l));;
