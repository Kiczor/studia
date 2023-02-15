package lab04.cards

sealed abstract class Color extends Product
case object Diamonds extends Color
case object Spades extends Color
case object Clubs extends Color
case object Hearts extends Color

sealed abstract class Value extends Product
sealed abstract class Face extends Value
case object Jack extends Face
case object Queen extends Face
case object King extends Face
sealed abstract class Ace extends Value
case object Ace extends Ace

case class Number(no: Int) extends Value
{
    require( no >= 2 && no <= 10 )
}

case class Card(val color: Color, val value: Value)