let connect lst =
	if lst == []
	then []
	else (List.hd lst) @ connect (List.tl lst);;

let permutacje lst =
	let mozliwosci lista =
		let rec ir lewo prawo w =
			if prawo == []
			then w
			else ir (lewo @ [(List.hd prawo)]) (List.tl prawo) (w @ [ ( (List.hd prawo), lewo @ (List.tl prawo) ) ] )
		in ir [] lista []

	in let rec pr w poz =
		if poz == []
		then [w]
		else
			let moz = mozliwosci poz in
				connect (List.map (fun x -> pr (w @ [fst x]) (snd x)) moz)
	in pr [] lst;;
