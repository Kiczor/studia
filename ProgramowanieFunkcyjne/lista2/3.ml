let rec merge cmp xs ys =
	if (List.length xs) == 0 || (List.length ys) == 0
		then xs @ ys
		else if cmp (List.hd xs) (List.hd ys)
			then [(List.hd xs)] @ (merge cmp (List.tl xs) ys)
			else [(List.hd ys)] @ (merge cmp xs (List.tl ys))

let merge2 f a b =
	let rec mergog cmp xs ys w =
		if (List.length xs) == 0 || (List.length ys) == 0
			then w @ xs @ ys
			else if cmp (List.hd xs) (List.hd ys)
				then (mergog cmp (List.tl xs) ys w @ [(List.hd xs)])
				else (mergog cmp xs (List.tl ys) w @ [(List.hd ys)])
	in mergog f a b []

let split l =
	let rec sp xs ys =
		if ((List.length ys) - (List.length xs)) <= 1
		then (xs, ys)
		else sp (xs @ [(List.hd ys)]) (List.tl ys)
	in sp [] l;;

let rec mergesort f xs =
	if (List.length xs) <= 1
		then xs
		else let s = split xs in merge f (mergesort f (fst s)) (mergesort f (snd s));;
