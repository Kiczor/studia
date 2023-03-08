using System;
using System.Collections;

class PrimeCollection : IEnumerable
{
	public IEnumerator GetEnumerator()
	{
		return new PrimeCollectionEnum();
	}
}

class PrimeCollectionEnum : IEnumerator
{
	public int op = 1;

	public void Reset()
	{
		op = 1;
	}

	public PrimeCollectionEnum()
	{
		op = 1;
	}

	private bool pierwsza( int x )
	{
		for(int i = 2; i * i <= x; i++)
			if( x % i == 0 )
				return false;
		return true;
	}

	public bool eos()
	{
		int temp = op + 1;
		while( !this.pierwsza( temp ) )
		{
			temp++;
			if( temp >= (1 << 30) )
				return true;
		}
		return false;
	}

	public bool MoveNext()
	{
		op ++;
		while( !this.pierwsza( op ) )
		{
			op ++;
		}

		//Console.WriteLine( op );
		//Console.WriteLine( eos() );

		return !eos();
	}

	object IEnumerator.Current
	{
		get
		{
			return op;
		}
	}
}

class sprawdzanie
{
	public static void Main()
	{
		PrimeCollection ps = new PrimeCollection();
		foreach(int p in ps)
			Console.WriteLine( p );
	}
}
