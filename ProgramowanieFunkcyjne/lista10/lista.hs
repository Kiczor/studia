import Data.Char

echoLower :: IO ()

echoLower = do
    c <- getChar
    if c == '\n'
        then putChar c
        else do
            putChar '\n'
            putChar (toLower c)
            echoLower

data StreamTrans i o a
    = Return a
    | ReadS (Maybe i -> StreamTrans i o a)
    | WriteS o (StreamTrans i o a)

mytoLower :: StreamTrans Char Char Bool
mytoLower = ReadS (\znak -> case znak of
                                    Nothing -> Return True
                                    Just c -> WriteS (toLower c) mytoLower)

runIOStreamTrans :: StreamTrans Char Char a -> IO a
runIOStreamTrans (ReadS f) = do 
    c <- getChar
    if c == '\n'
        then runIOStreamTrans (f Nothing)
        else runIOStreamTrans (f (Just c))

runIOStreamTrans (WriteS x c) = do
    putChar x
    runIOStreamTrans c

runIOStreamTrans (Return x) = return x

listTrans :: StreamTrans i o a -> [i] -> ( [o], a )
listTrans (ReadS f) xs = if (length xs) == 0
    then listTrans (f Nothing) (tail xs) 
    else listTrans (f (Just (head xs))) (tail xs)

listTrans (WriteS x c) xs = 
    let dalej = (listTrans c xs) 
    in ( [x] ++ (fst dalej), (snd dalej))

listTrans (Return x) xs = ( [], x )

--runCycle :: StreamTrans a a b -> b
--runCycle (ReadS f) = runCycle 
--runCycle (WriteS x c) = 

--(|>|) :: StreamTrans i m a -> StreamTrans m o b -> StreamTrans i o b
--(|>|) (WriteS x c) (ReadS f) = (ReadS (\y -> case y of )

--catchOutput :: StreamTrans i o a -> StreamTrans i b ( a, [o] )
--catchOutput (ReadS f) = (ReadS f)
--catchOutput (WriteS x c) = 