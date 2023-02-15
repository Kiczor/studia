package pizzeria
{
    trait PizzaName
    {
        def price: Double
    }

    case object Margarita extends PizzaName
    {
        def price = 5
        override def toString = "Margarita"
    }

    case object Pepperoni extends PizzaName
    {
        def price = 6.5
        override def toString = "Pepperoni"
    }

    case object Funghi extends PizzaName
    {
        def price = 7
        override def toString = "Funghi"
    }

    trait Size
    {
        def pricepercent: Double
    }

    case object Small extends Size
    {
        def pricepercent = 0.9
        override def toString = "Small"
    }

    case object Regular extends Size
    {
        def pricepercent = 1
        override def toString = "Regular"
    }

    case object Large extends Size
    {
        def pricepercent = 1.5
        override def toString = "Large"
    }

    trait Crust
    
    case object Thin extends Crust
    {
        override def toString = "Thin"
    }

    case object Thick extends Crust
    {
        override def toString = "Thick"
    }

    trait Topping
    {
        def price: Double = 0.5
    }

    case object Ketchup extends Topping
    {
        override def toString = "Ketchup"
    }
    
    case object Garlic extends Topping
    {
        override def toString = "Garlic"
    }

    trait Meat
    {
        def price: Double
    }
    case object Salami extends Meat
    {
        def price = 1
        override def toString = "Salami"
    }

    trait Drink
    {
        def price: Double
    }
    case object Lemonade extends Drink
    {
        def price = 2
        override def toString = "Lemonade"
    }

    case class Pizza(name: PizzaName, size: Size, crust: Crust, extraMeat: Option[Meat]=None, extraTopping: Option[Topping]=None)
    {
        override def toString() = "Pizza Type:" + name.toString + ", size:" + name.toString + ", Extra Meat:" + (if extraMeat == None then "no" else extraMeat.toString()) + ", Extra Topping:" + (if extraTopping == None then "no" else extraTopping.toString)
        val price: Double = name.price * (size.pricepercent + extraMeat.map(_.price).getOrElse(0.0) + extraTopping.map(_.price).getOrElse(0.0) )
    }
}
