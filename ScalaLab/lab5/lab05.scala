package plugins
{
    abstract class Pluggable {
        def plugin(s: String) = s
    }
    trait Reverting extends Pluggable {
        abstract override def plugin(s: String) = super.plugin( s.reverse )
    }

    trait LowerCasing extends Pluggable {
        abstract override def plugin(s: String) = super.plugin( s.toLowerCase )
    }

    trait SingleSpaceing extends Pluggable {
        abstract override def plugin(s: String) = super.plugin( s.replaceAll( " +", " " ) )
    }

    trait NoSpacing extends Pluggable {
        abstract override def plugin(s: String) = super.plugin( s.replaceAll( " ", "" ) )
    }

    trait DuplicateRemoval extends Pluggable {
        abstract override def plugin(s: String) = 
        {
            def f(xs: String, before: String, res: String): String = 
            {
                if( xs == "" )
                {
                    res
                }
                else if( before.contains( xs.head ) )
                {
                    f( xs.tail, before, res )
                }
                else
                {
                    f( xs.tail, before + xs.head, res + xs.head )
                }
            }
            super.plugin( f(s, "", "") )
        }
    }

    trait Rotating extends Pluggable {
        abstract override def plugin(s: String) = super.plugin( s.last + s.take( s.size - 1 ) )
    }

    trait Doubling extends Pluggable {
        abstract override def plugin(s: String) = 
        {
            def f(i: Int, xs: String, res: String): String = 
            {
                if( xs == "" )
                {
                    res
                }
                else if( i % 2 == 0 )
                {
                    f( i + 1, xs.tail, res + xs.head + xs.head  )
                }
                else
                {
                    f( i + 1, xs.tail, res + xs.head )
                }
            }
            super.plugin( f(0, s, "") )
        }
    }

    trait Shortening extends Pluggable {
        abstract override def plugin(s: String) = 
        {
            def f(i: Int, xs: String, res: String): String = 
            {
                if( xs == "" )
                {
                    res
                }
                else if( i % 2 == 0 )
                {
                    f( i + 1, xs.tail, res + xs.head )
                }
                else
                {
                    f( i + 1, xs.tail, res )
                }
            }
            super.plugin( f(0, s, "") )
        }
    }

    object Actions
    {
        val actionA = new Pluggable with Shortening with Doubling with SingleSpaceing
        val actionB = new Pluggable with Doubling with Shortening with NoSpacing
        val actionC = new Pluggable with Doubling with LowerCasing
        val actionD = new Pluggable with Rotating with DuplicateRemoval
        val actionE = new Pluggable with Reverting with Doubling with Shortening with NoSpacing
        val actionF = new Pluggable with Rotating {
            override def plugin(s: String) = super.plugin( super.plugin( super.plugin( super.plugin( super.plugin( s ) ) ) ) )
        }
        val actionG = new Pluggable {
            override def plugin(s: String) = actionB.plugin( actionA.plugin( s ) )
        }
    }
}

object MyApplication
{
    import plugins.*

    def main( args: Array[String] ) : Unit = 
    {
        val text = "Ala  ma Kota"

        println("pluggable class:")
        val prev = new Pluggable with Reverting
        println("reverting: " + prev.plugin(text) )

        val plow = new Pluggable with LowerCase
        println("lowercase: " + plow.plugin(text) )

        val psin = new Pluggable with SingleSpaceing
        println("singl espaceing: " + psin.plugin(text) )

        val pnospace = new Pluggable with NoSpacing
        println("no spacing: " + pnospace.plugin(text) )

        val pdup = new Pluggable with DuplicateRemoval
        println("duplicate removal: " + pdup.plugin(text) )

        val prot = new Pluggable with Rotating
        println("rotating: " + prot.plugin(text) )

        val pdou = new Pluggable with Doubling
        println("doubling: " + pdou.plugin(text) )

        val psho = new Pluggable with Shortening
        println("shortening: " + psho.plugin(text) )

        //Action
        println("Action object:")
        println("actionA: " + Actions.actionA.plugin(text))
        
        println("actionB: " + Actions.actionB.plugin(text))

        println("actionC: " + Actions.actionC.plugin(text))

        println("actionD: " + Actions.actionD.plugin(text))

        println("actionE: " + Actions.actionE.plugin(text))

        println("actionF: " + Actions.actionF.plugin(text))

        println("actionG: " + Actions.actionG.plugin(text))
    }
}