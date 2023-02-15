object Utils
{
    def isSorted( as: List[Int], ordering: (Int, Int) => Boolean ) : Boolean = if( as.tail == List() ) true else ordering( as.head, as.tail.head ) & isSorted( as.tail, ordering )
    
    def isAscSorted( as: List[Int] ) = isSorted( as, (x: Int, y: Int) => x <= y )
    def isDescSorted( as: List[Int] ) = isSorted( as, (x: Int, y: Int) => x >= y )

    def foldLeft[A, B](l: List[A], z: B)(f: (B, A) => B): B =
    {
        l match 
        {
            case x :: rl => foldLeft( rl, f( z, x ) )( f )
            case Nil => z
        }
    }

    def sum( l: List[Int] ) = foldLeft( l, 0 )( (a, b) => a + b )
    def length[A]( l: List[A] ) = foldLeft( l, 0 )( (b, _) => b + 1 )

    def compose[A, B, C]( f1: B => C, f2: A => B ) = (x: A) => f1( f2(x) )
    def repeat( f: Int => Int, n: Int ) = 
    {
        def rep2( f: Int => Int, n: Int, cnt: Int ): Int = if( cnt == n ) f( n ) else f( rep2( f, n, cnt + 1 ) )
        rep2( f, n, 0 )
    }

    def curry[A, B, C]( f: ( A, B ) => C ): A => B => C = (a: A) => (b: B) => f(a, b): C
    def uncurry[A, B, C]( f: A => B => C ): (A, B) => C = (a: A, b: B) => f(a)(b)
}

def unSafe[T](ex: Exception)( f: => T ): T = 
{
    try
    {
       f 
    } catch
    {
        case (e: Exception) => println( e.getMessage )
        throw ex
    }
}