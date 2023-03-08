let rec fold_left_cps f acc xs =
match xs with
h::t fold_left_cps (fun v -> ) (f acc h) t
| [] k acc
