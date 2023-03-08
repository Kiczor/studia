#include "onp.h"

std::set<std::string> rozne;

double stronp( std::string s )
{
	std::string x = "";
	int it = 0;

	std::vector<double> stos;
	while( it < s.size() )
	{
		if( s[it] == ' ' || it == s.size() - 1 )
		{
			symbol* smb;
			//std::cout << "x: |" << x << "|\n";
			if( '0' <= x[0] && x[0] <= '9')
			{
				smb = new liczba( std::stod( x ) );
			}
			else if( rozne.find( x ) == rozne.end() ) // jest to zmienna
			{
				smb = new liczba( ( new zmienna("tmp") ) -> findvalue( x ) );
			}
			if( x == "pi" )
			{
				smb = new liczba( 3.1415926535 );
			}
			if( x == "e" )
			{
				smb = new liczba( 2.7182818284 );
			}
			if( x == "fi" )
			{
				smb = new liczba( 1.6180339887 );
			}
			if( x == "+" )
			{
				smb = new dodaj( new liczba( stos[stos.size() - 2] ), new liczba( stos[stos.size() - 1] ) );
				stos.pop_back();
				stos.pop_back();
			}
			if( x == "-" )
			{
				smb = new odejmij( new liczba( stos[stos.size() - 2] ), new liczba( stos[stos.size() - 1] ) );
				stos.pop_back();
				stos.pop_back();
			}
			if( x == "*" )
			{
				smb = new mnoz( new liczba( stos[stos.size() - 2] ), new liczba( stos[stos.size() - 1] ) );
				stos.pop_back();
				stos.pop_back();
			}
			if( x == "/" )
			{
				smb = new dziel( new liczba( stos[stos.size() - 2] ), new liczba( stos[stos.size() - 1] ) );
				stos.pop_back();
				stos.pop_back();
			}
			if( x == "mod" )
			{
				smb = new modulo( new liczba( stos[stos.size() - 2] ), new liczba( stos[stos.size() - 1] ) );
				stos.pop_back();
				stos.pop_back();
			}
			if( x == "exp" )
			{
				smb = new potega( new liczba( stos[stos.size() - 2] ), new liczba( stos[stos.size() - 1] ) );
				stos.pop_back();
				stos.pop_back();
			}
			if( x == "abs" )
			{
				smb = new bezwzgl( new liczba( stos[stos.size() - 1] ) );
				stos.pop_back();
			}
			if( x == "sin" )
			{
				smb = new sinus( new liczba( stos[stos.size() - 1] ) );
				stos.pop_back();
			}
			if( x == "cos" )
			{
				smb = new cosinus( new liczba( stos[stos.size() - 1] ) );
				stos.pop_back();
			}
			if( x == "ln" )
			{
				smb = new ln( new liczba( stos[stos.size() - 1] ) );
				stos.pop_back();
			}

			stos.push_back( smb -> oblicz() );
			x = "";
		}
		else
		{
			//std::cout << "s: " << s << " it: " << it << " s[it]: " << s[it] << "\n";
			x += s[it];
		}

		it ++;
		if( it == s.size() - 1 )
			x += s[it];
	}

	return stos[ stos.size() - 1 ];
}

int main()
{
	rozne.insert( "+" );
	rozne.insert( "-" );
	rozne.insert( "*" );
	rozne.insert( "/" );
	rozne.insert( "pi" );
	rozne.insert( "e" );
	rozne.insert( "fi" );
	rozne.insert( "sin" );
	rozne.insert( "cos" );
	rozne.insert( "exp" );
	rozne.insert( "ln" );
	rozne.insert( "abs" );
	rozne.insert( "mod" );

	std::string in;
	symbol p;
	while( std::getline( std::cin, in ) )
	{
		if( in == "exit" )
			break;
		if( in[0] == 'p' ) //print wartosci
		{
			std::string s = "";
			for(int i = 6; i < in.size(); i++)
				s += in[i];

			//std::cout << s << "\n";

			std::cout << stronp( s ) << std::endl;
		}
		if( in[0] == 'a' )
		{
			std::string zm = "";
			for(int i = in.size() - 1; in[i] != ' '; i--)
				zm += in[i];

			reverse( zm.begin(), zm.end() );

			std::string s = "";
			for(int i = 7; i < in.size() - zm.size() - 3; i++)
				s += in[i];

			//std::cout << "s: " << s << " zm: " << zm << "\n";

			double wynik = stronp( s );
			zmienna* temp = new zmienna( "temp" );
			temp -> setvalue( zm, wynik );
		}
		if( in[0] == 'c' )
		{
			zmienna* temp = new zmienna( "temp" );
			temp -> czysc();
		}
	}
}
