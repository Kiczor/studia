type 'a zlist = list 'a * list 'a

let revlist xs =
match xs with
| [] -> []
| head::tail List.append (revlist tail) head

let of_list a = ([], a)

let to_list a = (revlist (fst a)) @ (snd a)

let elem (x, head::tail) = head

let move_left (lh::lt, p) = (lt, lh::p)

let move_right (l, ph::pt) = (ph::l, pt)

let insert x (l, p) = (x::l, p)

let remove (x::l, p) = (l, p)
