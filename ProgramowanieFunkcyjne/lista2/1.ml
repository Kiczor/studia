let sublists ls =
	let rec subit (l, w) =
		if l == []
		then w
		else subit( List.tl l, w @ List.map (fun x -> x @ [List.hd l]) w )
	in subit( ls, [[]] );;
