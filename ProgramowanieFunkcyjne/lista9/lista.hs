module QBF where

type Var = String
data Formula =
    Var Var 
    | Bot
    | Not Formula 
    | And Formula Formula 
    | All Var Formula

type Env = Var -> Bool
eval :: Env -> Formula -> Bool

eval e (Var x) = (e x)
eval e Bot = False
eval e (Not f) = (not (eval e f))
eval e (And f1 f2) = ((eval e f1) && (eval e f2))
eval e (All zm f) = (eval (\x -> if x == zm then True else (e x)) f) && (eval (\x -> if x == zm then False else (e x)) f) 

emptyenv = (\x -> False)

example = (All "p" (Not (All "q" (Not (And (Not (And (Var "p") (Var "q") ) ) (Not (And (Not (Var "p")) (Not (Var "q")) ) ) ) ) ) ) )
okej = ( And (Var "p") (Not Bot) )
ex2 = (All "p" okej)

isTrue :: Formula -> Bool
isTrue f = eval emptyenv f