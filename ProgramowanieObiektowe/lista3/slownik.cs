using System;
using System.Collections.Generic;

class Slownik<K, V>
{
	private class para
	{
		public K key;
		public V value;

		public para( K kl, V wa )
		{
			key = kl;
			value = wa;
		}

		public para(){}
	}

	List<para> t = new List<para>();

	public V Find( K x )
	{
		foreach( para p in t )
		{
			if( p.key == x )
				return p.value;
		}
		return null;
	}

	public void Insert( K kl, V wa )
	{
		t.Add( para( kl, wa ) );
	}

	public void Erase( K kl, V wa )
	{
		t.Remove( para( kl, wa ) );
	}
}
