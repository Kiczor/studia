using System;
using System.Collections.Generic;

class ListaLeniwa
{
	protected List<int> t;
	public int size()
	{
		return t.Count;
	}

	public int element( int i )
	{
		if( i < this.size() )
			return t[i];

		Random rnd = new Random();
		while( t.Count <= i )
		{
			t.Add( rnd.Next( -1000, 1000 ) );
		}

		return t[i];
	}

	public ListaLeniwa()
	{
		t = new List<int>();
	}
}

class Pierwsze : ListaLeniwa
{
	private bool pierwsza( int x )
	{
		for(int i = 2; i * i <= x; i++)
			if( x % i == 0 )
				return false;
		return true;
	}

	public int element( int i )
	{
		if( i < this.size() )
			return t[i];

		while( t.Count <= i )
		{
			int x = t[ t.Count - 1 ] + 1;
			while( !this.pierwsza( x ) )
				x++;
			t.Add( x );
		}

		return t[i];
	}

	public Pierwsze()
	{
		t = new List<int>();
		t.Add(2);
	}
}

class sprawdzanie
{
	public static void Main()
	{
		Console.WriteLine( "siema" );

		ListaLeniwa l = new ListaLeniwa();
		Console.WriteLine( l.element( 40 ) );
		Console.WriteLine( l.element( 38 ) );
		Console.WriteLine( l.element( 40 ) );

		Pierwsze p = new Pierwsze();
		Console.WriteLine( p.element( 5 ) );
		Console.WriteLine( p.element( 7 ) );
	}
}
