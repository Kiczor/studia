import Utils.*

object MyApplication
{
    def main( args: Array[String] ) : Unit = 
    {
        val l1 = List( 1, 2, 3, 2 )
        val l2 = List( 1, 2, 3, 4 )
        val l3 = List( 4, 3, 2, 1 )
        println( "is l1 sorted?: " + isSorted( l1, (x: Int, y: Int) => x < y ) )
        println( "is l2 sorted?: " + isAscSorted( l2 ) )
        println( "is l3 desc sorted?: " + isDescSorted( l3 ) )
        println( "l2 sum: " + sum( l2 ) )
        println( "l2 length: " + length( l2 ) )
        println( "compose( (x: Int) => x * 2, (y: Int) => y + 1)(5): " + compose( (x: Int) => x * 2, (y: Int) => y + 1)(5) )
        println( "Utils.repeat( (x: Int) => x * 2, 3 ): " + Utils.repeat( (x: Int) => x * 2, 3 ) )

        val fun = (x: Int, y: Int) => x + y
        println( "fun curried (2)(3): " + curry(fun)(2)(3) )
        val func = (x: Int) => (y: Int) => x + y
        println( "fun uncurried (2, 3): " + uncurry(func)(2, 3) )

        println( "safe operation ( 1 / 1 ): ")
        unSafe( new Exception("my exception ") )( println( 1 / 1 ) )
        println( "unsafe operation ( 1 / 0 ): ")
        unSafe( new Exception("my exception ") )( println( 1 / 0 ) )
    }
}