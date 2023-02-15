class Monad m => Random m where
    random :: m Int

shuffle :: Random m => [a] -> m [a]
shuffle [] = return []
shuffle [x] = return [x]
shuffle xs = 
    do
        x <- random
        let p = mod (length xs) x
        a <- shuffle $ take p xs ++ drop (p+1) xs
        return $ (xs !! p) : a


newtype RS a = RS { unRS :: Int -> (Int, a) }

withSeed :: RS a -> Int -> a
withSeed x seed = snd $ unRS x seed

newSeed :: Int -> Int
newSeed a = if b > 0 then b else b + 2147483647
    where b = 16807 * (mod a 127773) - 2836 * (div a 127773)


instance Functor RS where
    fmap f rs = RS (\s -> let (p, x) = unRS rs s in (p, f x))

instance Applicative RS where
    pure x = RS (\s -> (newSeed s, x))
    (<*>) x y = RS (\s1 -> 
        let s2 = newSeed s1 in
        let s3 = newSeed s2 in
        (s3, withSeed x s1 (withSeed y s2)))

instance Monad RS where 
    return x = RS (\s -> (newSeed s, x))
    x >>= f = RS (\s -> let (p, y) = unRS x s in unRS (f y) p)

instance Random RS where
    random = RS (\s -> (newSeed s, s))

q :: RS [Int]
q = shuffle [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]


main :: IO ()
main = do
    let (seed, res) = unRS q 1
    putStrLn $ show seed
    putStrLn $ show res