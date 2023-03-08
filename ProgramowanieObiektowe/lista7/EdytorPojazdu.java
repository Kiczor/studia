import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.Scanner;

public class EdytorPojazdu extends JFrame implements Serializable, ActionListener
{
	private static final long serialVersionUID = 1L;
	public JButton Zapisz, Otworz;
	public JTextField Producent, Model, Rok;
	public Pojazd p;

	public EdytorPojazdu( String s )
	{
		initUI();
		p = new Pojazd();

		if(s != "")
		{
			File file = new File(s);
			ReadFromFile(file);
		}
	}

	public void ReadPojazd()
	{
		Producent.setText( p.producent );
		Model.setText( p.model );
		Rok.setText( Integer.toString( p.rok_produkcji ) );
	}

	public void WritePojazd()
	{
		p = new Pojazd( Producent.getText(), Model.getText(), Integer.parseInt( Rok.getText() ) );
	}

	public final void initUI()
	{
		Zapisz = new JButton("Zapisz do pliku");
		Otworz = new JButton("Otwórz z pliku");

		Zapisz.setBounds(0, 10, 200, 30);
		Otworz.setBounds(0, 50, 200, 30);

		this.setLayout(null);

        getContentPane().add(Zapisz);
        getContentPane().add(Otworz);
        Zapisz.addActionListener(this);
        Otworz.addActionListener(this);

		Producent = new JTextField("Producent:");
		Producent.setBounds(200, 40, 200, 30);
		getContentPane().add( Producent );

		Model = new JTextField("Model:");
		Model.setBounds(200, 80, 200, 30);
		getContentPane().add( Model );

		Rok = new JTextField("Rok Produkcji:");
		Rok.setBounds(200, 120, 200, 30);
		getContentPane().add( Rok );

        setSize(500, 250);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
	}

	public void SaveToFile(File file)
	{
		try
		{
			PrintWriter zapis = new PrintWriter(file);
			WritePojazd();
			zapis.println( p.toString() );
			zapis.close();
		}
		catch (FileNotFoundException e1) {}
	}

	public void ReadFromFile(File file)
	{
		try
		{
			Scanner in = new Scanner(file);

			String P = in.nextLine();
			String M = in.nextLine();
			String R = in.nextLine();

			p = new Pojazd( P, M, Integer.parseInt(R) );
			ReadPojazd();
			in.close();
		}
		catch (FileNotFoundException e1) {}
	}

	public void actionPerformed(ActionEvent e)
	{
		Object source = e.getSource();

		if( source == Zapisz )
		{
			JFileChooser fileChooser = new JFileChooser();
			if (fileChooser.showSaveDialog(Zapisz) == JFileChooser.APPROVE_OPTION)
			{
				File file = fileChooser.getSelectedFile();
				SaveToFile(file);
			}
		}

		if( source == Otworz )
		{
			JFileChooser fileChooser = new JFileChooser();

			if (fileChooser.showOpenDialog(Otworz) == JFileChooser.APPROVE_OPTION)
			{
				File file = fileChooser.getSelectedFile();
				ReadFromFile(file);
			}
		}
	}
}
