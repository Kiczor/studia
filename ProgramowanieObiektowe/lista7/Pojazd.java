import java.io.*;
import java.io.Serializable;

public class Pojazd implements Serializable
{
	private static final long serialVersionUID = 4661681646491395516L;
	public String producent, model;
	public int rok_produkcji;

	public Pojazd( String p, String m, int r )
	{
		producent = p;
		model = m;
		rok_produkcji = r;
	}

	public Pojazd()
	{
		producent = "Producent";
		model = "Model";
		rok_produkcji = 0;
	}

	public String toString()
	{
		return "Producent: " + producent + "\nModel: " + model + "\nRok produkcji: " + rok_produkcji + "\n";
	}
}
