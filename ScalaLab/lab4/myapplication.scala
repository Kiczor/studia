import lab04.cards.*
import lab04.deck.*

object MyApplication
{
    def main( args: Array[String] ) : Unit = 
    {
        var c1 = Card(Hearts, Queen)
        var d = Deck()
        d = d.push(c1)
        d = d.push(c1)
        println(d)
        println(c1)

        var c2 = Card(Hearts, Number(3))
        d = d.push(c2)
        println( d.getCards() )
        println( d.amountOfColor(Hearts) )
        println( d.amountWithNumerical )

        println( d.isStandard )
        var d2 = Deck()
        println( d2.isStandard )
    }
}