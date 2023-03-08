import java.io.*;

class element<T> implements java.io.Serializable
{
	protected element<T> prev, next;
	protected T val;

	public element()
	{
		prev = null;
		next = null;
	}

	public element( T x )
	{
		prev = null;
		next = null;
		val = x;
	}
}

class list<T> implements java.io.Serializable
{
	private element<T> front, back;
	private int size;

	public list()
	{
		front = new element<>();
		back = new element<>();
		size = 0;

		front.prev = back;
		back.next = front;
	}

	public void AddFront( T x )
	{
		front.val = x;
		front.next = new element<>();
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
		back.prev = new element<>();
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

	public int GetSize()
	{
		return size;
	}
}
