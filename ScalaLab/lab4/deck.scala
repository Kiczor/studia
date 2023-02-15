package lab04.deck
import lab04.cards.*

class Deck(cards: List[Card]) 
{
    def pull() = Deck(cards.tail)
    def push(c: Card): Deck = Deck( c :: cards )
    def push(color: Color, value: Value): Deck = new Deck( Card(color, value) :: cards )
    def duplicatesOfCard(card: Card): Int = cards.count( x => x == card )
    def amountOfColor(color: Color): Int = cards.count( x => x.color == color )
    def amountOfNumerical(numerical: Number): Int = cards.count( x => x.value == numerical)
    val amountWithNumerical: Int = cards.count( x => x.value.isInstanceOf[Number] )
    def amountOfFace(face: Face): Int = cards.count( x => x.value == face )
    val amountWithFace: Int = cards.count( x => x.value.isInstanceOf[Face] )
    val isStandard: Boolean = 
    {
        if( cards.length != 52)
            false 
        else
        {
            val l: List[Boolean] = for { x <- Deck.standardDeck } yield cards.contains( x )
            l.foldLeft(true)((x, y) => x && y)
        }
    }

    def getCards(): List[Card] = cards
}

object Deck
{
    val standardDeck = for
    {
        c <- List( Diamonds, Spades, Clubs, Hearts )
        v <- List( Jack, Queen, King, Ace ) ::: (for {i <- (2 to 10).toList} yield Number(i))
    } yield Card( c, v )
    
    def apply() = new Deck(standardDeck)
    def apply(cards: List[Card]) = new Deck(cards)
}
