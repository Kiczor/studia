using System;
using Lista;

class sprawdzanie
{
	public static void Main()
	{
		Lista<string> x = new Lista<string>();

		x.AddFront( "s" );
		x.AddFront( "i" );
		x.AddBack( "a" );
		x.AddBack( "b" );
		x.AddBack( "c" );
		x.AddBack( "d" );

		Console.WriteLine( x.RemoveBack() );
		Console.WriteLine( x.RemoveBack() );

		x.AddBack( e );

		Console.WriteLine( x.RemoveBack() );
		Console.WriteLine( x.RemoveFront() );
	}
}
