module NestedQBF where
    import Data.Void

    data Inc v = Z | S v

    data Formula v =
        Var v
        | Bot
        | Not (Formula v)
        | And (Formula v) (Formula v)
        | All (Formula (Inc v))

    type Env = Inc Void -> Bool
    eval :: Env -> Formula (Inc Void) -> Bool

    eval e (Var x) = (e x)
    eval e Bot = False
    eval e (Not f) = not (eval e f)
    eval e (And f1 f2) = (eval e f1) && (eval e f2)
    eval e (All f) = (eval (\x -> case x of
                                    Z -> True
                                    S v -> (e (S v))) f) && (eval (\x -> case x of 
                                                                        Z -> False
                                                                        S v -> (e (S v)) ) f)

    example = All (Var Z `And` All (Var (S Z) `And` (Var Z)))
    ex3 = (All (Not (All (Not (And (Not (And (Var (S Z)) (Var Z) ) ) (Not (And (Not (Var (S Z))) (Not (Var Z)) ) ) ) ) ) ) )
    ex2 = All (Var Z `And` Bot)
    --ex4 = All (Var Z `And` (Var (S Z)))

    isTrue :: Formula (Inc Void) -> Bool
    isTrue f = eval (\(S x) -> absurd x) f