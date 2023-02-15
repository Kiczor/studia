import pizzeria.*
import orders.*

object MyApplication
{
    def main( args: Array[String] ) : Unit = 
    {
        val p1 = Pizza(Margarita, Regular, Thin)
        val p2 = Pizza(Funghi, Large, Thick, Some(Salami), Some(Garlic))

        println( "pizza1: " + p1.toString )
        println( "pizza1 price: " + p1.price )

        println( "pizza2: " + p2.toString )
        println( "pizza2 price: " + p2.price )

        val o1 = new Order( "Adam Smith", "Nice street 5/6", PhoneNumber("1234567890"), List( p1, p2 ), List( Lemonade ), Some(SeniorDiscount) )
        println( o1.toString )
        println( "order price:" + o1.price)
    }
}