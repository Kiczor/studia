let ctrue = fun a b -> if true then a else b;;
let cfalse = fun a b -> if false then a else b;;
let cand x y = if x == ctrue && y == ctrue then ctrue else cfalse;;
let cor x y = if x == ctrue || y == ctrue then ctrue else cfalse;;
let cbool_of_bool x = if x == true then ctrue else cfalse;;
let bool_of_cbool x = if x == ctrue then true else false;;
