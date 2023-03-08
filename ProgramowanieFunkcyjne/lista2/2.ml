let cycle ls n =
	let rec cycleit ( t, p ) =
		if (List.length p) == n then p @ t else cycleit( t @ [List.hd p], List.tl p )
	in cycleit ( [], ls )
