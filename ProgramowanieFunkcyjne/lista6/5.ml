type 'a dllist = 'a dllist_data lazy_t
and 'a dllist_data =
{ prev : 'a dllist
; elem : 'a
; next : 'a dllist
}

let malalista w = let rec x = lazy { prev = x; elem = w; next = x } in x;;

let of_list lst =
  let rec off l pop = 
    if l == [] then pop
    else let rec x = lazy { elem = List.hd l;
    next = ( off (List.tl l) x );
    prev = pop } in x
  in (off (List.tl lst) (malalista (List.hd lst)));; 


let of_list2 lst =
 let rec off2 l pop = 
   if l == [] then pop
   else let rec x = lazy { elem = List.hd l;
   next = ( off2 (List.tl l) x );
   prev = pop } in x
 in let z = (off2 (List.tl lst) (malalista (List.hd lst)))
 in let rec poc = lazy { elem = (List.hd lst), next = z, prev = poc } in poc;;
  

let prev ( d:( 'a dllist ) ) = (Lazy.force d).prev;;
let elem ( d:( 'a dllist ) ) = (Lazy.force d).elem;;
let next ( d:( 'a dllist ) ) = (Lazy.force d).next;;
