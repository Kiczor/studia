import Prelude hiding ((++), head, tail, length, null, (!!))
import qualified Prelude ((++), head, tail, length, null, (!!))

class List l where
    nil :: l a
    cons :: a -> l a -> l a
    head :: l a -> a
    tail :: l a -> l a
    (++) :: l a -> l a -> l a
    (!!) :: l a -> Int -> a
    toList   :: [a] -> l a
    fromList :: l a -> [a]

instance List [] where                                                          
    nil = []                                                                    
    cons x xs = x:xs                                                            
    head (x:xs) = x                                                             
    tail (x:xs) = xs                                                            
    (++) xs ys = (Prelude.++) xs ys                                             
    (!!) xs n = (Prelude.!!) xs n                                               
    toList xs = xs                                                              
    fromList xs = xs

class List l => SizedList l where
    length :: l a -> Int
    null :: l a -> Bool
    null l = length l == 0

instance SizedList [] where
    length [] = 0
    length (x:xs) = (length xs) + 1
    null [] = True
    null (x:xs) = False

data SL l a = SL { len :: Int, list :: l a }

instance List l => List (SL l) where                                            
    nil = SL 0 nil                                                              
    cons x (SL lx xs) = SL (lx + 1) (cons x xs)                               
    head (SL lx xs) = head xs                                       
    tail (SL lx xs) = SL (lx - 1) (tail xs)
    (++) (SL lx xs) (SL ly ys) = (SL (lx + ly) (xs ++ ys))
    (!!) (SL lx xs) n = (xs !! n)
    toList xs = (SL (Prelude.length xs) (toList xs))
    fromList (SL lx xs) = fromList xs

instance List l => SizedList (SL l) where
    length (SL lx xs) = lx
    null (SL lx xs) = lx == 0
    
infixr 6 :+
data AppList a = Nil | Sngl a | AppList a :+ AppList a
                deriving (Show)

instance SizedList AppList where
    length (Sngl x) = 1
    length (l :+ p) = (length l) + (length p)
    null Nil = True
    null (Sngl a) = False
    null (l :+ p) = False

rozmiar Nil = 0
rozmiar (Sngl x) = 1
rozmiar (l :+ p) = (rozmiar l) + (rozmiar p)

--dzielna2 l p 0 = (l, p)
dzielna2 l (x:p) = if (abs ((length p) - (length l))) > 1
    then (dzielna2 (l ++ [x]) p)
    else (l, (x:p))

npierwszych (x:xs) n = x:(npierwszych xs (n - 1))
npierwszych xs 0 = []

instance List AppList where
    nil = Nil
    cons x xs = ((Sngl x) :+ xs)
    head (Sngl x) = x
    head (l :+ p) = head l
    tail (Sngl x) = nil
    tail (l :+ p) = (tail l) :+ p
    (++) xs ys = xs :+ ys
    --(!!) (l :+ p) n = 
    toList xs = let para = (dzielna2 [] xs) in 
        (toList (fst para)) :+ (toList (snd para))
    --toList (x:xs) = (Sngl x) :+ (toList xs)
    toList [] = nil
    fromList Nil = []
    fromList (Sngl x) = [x]
    fromList (l :+ p) = (fromList l) ++ (fromList p)

test :: AppList Int
test = (toList [1,2,3,4])

