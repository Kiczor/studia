let sufiksy l =
	let rec f p w =
		if p == []
		then w @ [p]
		else f (List.tl p) w @ [p]
	in f l [];;

let prefiksy lst =
	let rec f l p w =
		if p == []
		then w @ [l]
		else f (l @ [(List.hd p)]) (List.tl p) w @ [l]
	in f [] lst [];;
