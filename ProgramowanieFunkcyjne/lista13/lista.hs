import Control.Monad

data RegExp a
    = Eps
    | Lit  (a -> Bool)
    | Or   (RegExp a) (RegExp a)
    | Cat  (RegExp a) (RegExp a)
    | Star (RegExp a)

match :: MonadPlus m => RegExp a -> [a] -> m (Maybe [a])
match Eps xs = return $ Just xs
match (Lit s) [] = mzero
match (Lit p) (x:xs) = if (p x) then return (Just xs) else mzero
match (Or r1 r2) xs = mplus (match r1 xs) (match r2 xs)
match (Cat r1 r2) xs = match r1 xs >>= \x -> case x of
                                            Nothing -> match r2 xs
                                            Just xd -> match r2 xd

match (Star r) xs = mplus (return Nothing)
						  (match r xs >>= (\x -> case x of 
						  						Nothing -> return Nothing
						  						Just xd -> mplus (return x) (match (Star r) xd)))

tresc = Star (Star (Lit (/= 'b')) `Or` (Lit (== 'b') `Cat` Lit (== 'a')))
przyklad = (Lit (== 'c')) `Cat` ((Lit (== 'b')) `Or` (Lit (== 'a')))
xxx = Star (Lit (== 'a')) `Cat` ((Lit (== 'a')) `Cat` (Lit (== 'b')))

list_match :: RegExp a -> [a] -> [Maybe [a]]
list_match = match

match_all :: RegExp a -> [a] -> Bool
match_all r xs = any (\x -> case x of
                            Nothing  -> null xs
                            Just xs' -> null xs')
                 $ list_match r xs
