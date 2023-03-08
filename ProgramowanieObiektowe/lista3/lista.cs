using System;
using System.Collections.Generic;

class Lista<T>
{
	private class elem
	{
		public elem next, prev;
		public T val;

		public elem( T x )
		{
			next = null;
			prev = null;
			val = x;
		}

		public elem()
		{
			next = null;
			prev = null;
		}
	}

	elem front, back;
	int size;

	public Lista()
	{
		size = 0;
		front = new elem();
		back = new elem();
		front.prev = back;
		back.next = front;
	}

	public void AddFront( T x )
	{
		front.val = x;
		front.next = new elem();
		front.next.prev = front;
		front = front.next;
		size ++;
	}

	public T RemoveFront()
	{
		front.prev.next = null;
		front = front.prev;
		size --;
		return front.val;
	}

	public void AddBack( T x )
	{
		back.val = x;
		back.prev = new elem();
		back.prev.next = back;
		back = back.prev;
		size ++;
	}

	public T RemoveBack()
	{
		back.next.prev = null;
		back = back.next;
		size --;
		return back.val;
	}

	public bool empty()
	{
		if( size > 0 )
			return false;
		return true;
	}
}

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

		x.AddBack( "e" );
		x.AddBack( "f" );

		Console.WriteLine( x.RemoveBack() );
		Console.WriteLine( x.RemoveFront() );

		x.AddFront( "e" );

		Console.WriteLine( x.RemoveBack() );
		Console.WriteLine( x.RemoveFront() );
	}
}
