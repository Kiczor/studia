//1
let rec myfold f acc l = 
    match l with
    | [] -> acc
    | x::xs -> myfold f (f acc x) xs

let rec myfoldback f l acc = 
    match l with
    | [] -> acc
    | x::xs -> f x (myfoldback f xs acc)

printfn "myfold: %d" (myfold (fun a x -> a + x) 0 [1 .. 4])
printfn "myfoldback: %d" (myfoldback (fun x a -> a + x) [1 .. 4] 0)

//2
let SumAhead l = 
    let (res, _) = List.fold ( fun (acc, start) x -> match (x, start) with
                                                        | (v, 1) -> (acc + v, 1)
                                                        | (v, 0) when v < 0 -> (acc + v, 1)
                                                        | (v, 0) when v >= 0 -> (acc, 0) ) (0, 0) l
    res

let mySumAhead l = 
    let (res, _) = myfold ( fun (acc, start) x -> match (x, start) with
                                                        | (v, 1) -> (acc + v, 1)
                                                        | (v, 0) when v < 0 -> (acc + v, 1)
                                                        | (v, 0) when v >= 0 -> (acc, 0) ) (0, 0) l
    res

let examplelist = [3;3;-1;5;5;-2;6;4;-3;8;2]

printfn "sum ahead example result: %d" (SumAhead examplelist)
printfn "sum ahead example result using myfold: %d" (mySumAhead examplelist)

//3
let counterf = fun x (acc, start)-> match (x, start) with
                                        | (v, 1) -> (acc + v, 1)
                                        | (v, 0) when v < 0 -> (acc + v, 1)
                                        | (v, 0) when v >= 0 -> (acc, 0)
let SumBack l = 
    let (res, _) = List.foldBack counterf l (0, 0)
    res

let mySumBack l = 
    let (res, _) = myfoldback counterf l (0, 0)
    res

printfn "sum back example result: %d" (SumBack examplelist)
printfn "sum back example result using myfoldback: %d" (mySumBack examplelist)

//4
let countnonwhite l =
   let l2 = List.map (fun x -> (x + "").Trim()) (List.filter (fun x -> not (System.String.IsNullOrWhiteSpace x)) l) //list without whitespace elements and trailing whitespaces
   let (res, _) = List.fold (fun (acc, cnt) x -> (acc + (String.length x) + cnt, cnt + 1)) (0, 0) l2
   res

let textlist1 = ["   ala";"";"ma ";" ";"kota";"   "]
let textlist2 = ["   ala i ela";"";"ma ";" ";"kota";"   "]
let textlist3 = ["";"  "] 

printfn "count non white text 1: %A" (countnonwhite textlist1)
printfn "count non white text 2: %A" (countnonwhite textlist2)
printfn "count non white text 3: %A" (countnonwhite textlist3)
