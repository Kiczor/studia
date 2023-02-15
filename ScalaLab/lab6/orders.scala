import pizzeria.*

package orders
{
    case class PhoneNumber(num: String)
    {
        override def toString = num
        val phoneregex = "^(\\+\\d{1,3}( )?)?((\\(\\d{1,3}\\))|\\d{1,3})[- .]?\\d{3,4}[- .]?\\d{4}$"
        require(num.matches(phoneregex), "Enter valid phone number")
    }

    trait Discount
    {
        def pizzadiscount: Double
        def drinkdiscount: Double 
    }

    case object StudentDiscount extends Discount
    {
        override def pizzadiscount = 0.05
        override def drinkdiscount = 0.0
        override def toString = "student discount"
    }

    case object SeniorDiscount extends Discount
    {
        override def pizzadiscount = 0.07
        override def drinkdiscount = 0.07
        override def toString = "senior discount"
    }

    class Order(name: String, address: String, phone: PhoneNumber, pizzas: List[Pizza], drinks: List[Drink], discount: Option[Discount]=None, specialInfo: Option[String]=None)
    {
        override def toString = "Person's name:" + name + ", address:" + address + ", phone:"+ phone + ", pizzas:" + (for (p <- pizzas) yield p.toString + ", ").mkString + "drinks:" + (for (p <- drinks) yield p.toString + ", ").mkString + "special info:" + specialInfo.getOrElse("")
        def extraMeatPrice: Option[Double] = Some(pizzas.map( _.extraMeat.map(_.price).getOrElse(0.0) ).sum)
        def pizzasPrice: Option[Double] = Some(pizzas.map(_.price).sum)
        def drinksPrice: Option[Double] = Some(drinks.map(_.price).sum)

        val price: Double = pizzasPrice.getOrElse(0.0) * ( 1.0 - discount.map(_.pizzadiscount).getOrElse(0.0) ) + drinksPrice.getOrElse(0.0) * ( 1.0 - discount.map(_.drinkdiscount).getOrElse(0.0) )
    }
}