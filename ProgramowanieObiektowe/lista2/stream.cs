using System;
using System.Collections.Generic;

class IntStream
{
	protected int op = 1;
	virtual public int next()
	{
		return op ++;
	}

	public void reset()
	{
		op = 1;
	}

	virtual public bool eos()
	{
		return false;
	}
}

class PrimeStream : IntStream
{
	private bool pierwsza( int x )
	{
		for(int i = 2; i * i <= x; i++)
			if( x % i == 0 )
				return false;
		return true;
	}

	override public bool eos()
	{
		int temp = op + 1;
		while( !this.pierwsza( temp ) )
		{
			temp++;
			if( temp >= (1 << 31) )
				return true;
		}
		return false;
	}

	override public int next()
	{
		op ++;
		while( !this.pierwsza( op ) )
		{
			op ++;
		}
		return op;
	}
}

class RandomStream : IntStream
{
	Random rnd = new Random();

	override public int next()
	{
		return rnd.Next( 0, 1000 );
	}

	override public bool eos()
	{
		return false;
	}
}

class RandomWordStream : IntStream
{
	PrimeStream ps = new PrimeStream();
	RandomStream rs = new RandomStream();

 	public string next()
	{
		string res = "";

		int ln = ps.next();
		for(int i = 0; i < ln; i++)
		{
			res += (char)( 'a' + (char)(rs.next() % 26) );
		}

		return res;
	}
}

class sprawdzanie
{
	public static void Main()
	{
		Console.WriteLine( "siema" );

		PrimeStream ps = new PrimeStream();
		Console.WriteLine( ps.next() );
		Console.WriteLine( ps.next() );

		RandomWordStream rws = new RandomWordStream();
		Console.WriteLine( rws.next() );
		Console.WriteLine( rws.next() );
		Console.WriteLine( rws.next() );
		Console.WriteLine( rws.next() );
	}
}
