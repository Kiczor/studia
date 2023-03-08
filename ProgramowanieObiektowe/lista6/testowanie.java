import java.io.*;

class testowanie
{
	public static void main(String[] args)
	{
		list<String> x = new list<String>();

		x.AddFront( "s" );
		x.AddFront( "i" );
		x.AddBack( "a" );
		x.AddBack( "b" );
		x.AddBack( "c" );
		x.AddBack( "d" );

		System.out.println( x.RemoveBack() );
		System.out.println( x.RemoveBack() );

		String NazwaPliku = "/home/szymon/po/lista6/lista.ser";
		ObjectOutputStream out = new ObjectOutputStream( new BufferedOutputStream( new FileOutputStream(NazwaPliku) ) );
		out.writeObject("Lista");
		out.writeObject(x);
		out.close();

		ObjectInputStream in = new ObjectInputStream( new BufferedInputStream( new FileInputStream(NazwaPliku) ) );
		String nagłowek = (String) in.readObject();
		x = (list<String>) in.readObject();
		in.close();
	}
}
