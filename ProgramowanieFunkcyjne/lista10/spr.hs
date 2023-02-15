import Prelude hiding ((^^))

int :: (String -> a) -> String -> Integer -> a
str :: (String -> a) -> String -> String -> a
lit :: String -> (String -> a) -> String -> a
(^^) :: ((String -> a) -> String -> b) -> ((String -> c) -> String -> a) -> ((String -> c) -> String -> b)

int c pop x = c (pop ++ (show x))
str c pop s = c (pop ++ s)
lit s c pop = c (pop ++ s)
(^^) l p = (l . p)

sprintf :: ((String -> String) -> String -> b) -> b
sprintf s = s id ""

test n =  sprintf (lit "Ala ma " ^^ int ^^ lit " kot" ^^ str ^^ lit ".") n (if n == 1 then "a" else if 1 < n && n < 5 then "y" else "ow")
