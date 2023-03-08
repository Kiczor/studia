#include "wyrazenia.h"

liczba::liczba( double x )
{
	val = x;
}

std::string liczba::opis()
{
	return std::to_string( val );
}

double liczba::oblicz()
{
	return val;
}

zmienna::zmienna( std::string e )
{
	etykieta = e;
}

std::string zmienna::opis()
{
	return etykieta;
}

std::vector<std::pair<std::string, double> > zmienna::wartosci;
double zmienna::oblicz()
{
	/*double res = 0;
	for(int i = 0; i < wartosci.size(); i++)
		if( wartosci[i].first == etykieta )
		{
			res = wartosci[i].second;
			break;
		}
	return res;*/
	return findvalue( etykieta );
}

void zmienna::setvalue( std::string e, double x )
{
	bool zn = false;
	for(int i = 0; i < zmienna::wartosci.size(); i++)
		if( zmienna::wartosci[i].first == e )
		{
			zn = true;
			zmienna::wartosci[i].second = x;
		}

	if( !zn )
		zmienna::wartosci.push_back( make_pair( e, x ) );
}

double zmienna::findvalue( std::string e )
{
	for(int i = 0; i < zmienna::wartosci.size(); i++)
		if( zmienna::wartosci[i].first == e )
		{
			return zmienna::wartosci[i].second;
		}
	throw std::invalid_argument("taka zmienna nie zostala dodana do zbioru zmiennych");
}

std::string pi::opis()
{
	return "pi";
}

pi::pi()
{
	val = 3.141592653590l;
}

double stala::oblicz()
{
	return val;
}

std::string e::opis()
{
	return "e";
}

e::e()
{
	val = 2.718281820l;
}

std::string fi::opis()
{
	return "fi";
}

fi::fi()
{
	val = 1.6180339l;
}


sinus::sinus( wyrazenie* x )
{
	pod = x;
}

double sinus::oblicz()
{
	return sin( pod -> oblicz() );
}

std::string sinus::opis()
{
	return "sin(" + pod -> opis() + ")";
}


cosinus::cosinus( wyrazenie* x )
{
	pod = x;
}

double cosinus::oblicz()
{
	return cos( pod -> oblicz() );
}

std::string cosinus::opis()
{
	return "cos(" + pod -> opis() + ")";
}


exp::exp( wyrazenie* x )
{
	pod = x;
}

double exp::oblicz()
{
	return pow( 2.7182818, pod -> oblicz() );
}

std::string exp::opis()
{
	return "exp(" + pod -> opis() + ")";
}


ln::ln( wyrazenie* x )
{
	pod = x;
}

double ln::oblicz()
{
	return log( pod -> oblicz() );
}

std::string ln::opis()
{
	return "ln(" + pod -> opis() + ")";
}


bezwzgl::bezwzgl( wyrazenie* x )
{
	pod = x;
}

double bezwzgl::oblicz()
{
	return abs( pod -> oblicz() );
}

std::string bezwzgl::opis()
{
	return "|" + pod -> opis() + "|";
}


przeciw::przeciw( wyrazenie* x )
{
	pod = x;
}

double przeciw::oblicz()
{
	return 0.0 - ( pod -> oblicz() );
}

std::string przeciw::opis()
{
	return "przeciw(" + pod -> opis() + ")";
}


odwrot::odwrot( wyrazenie* x )
{
	pod = x;
}

double odwrot::oblicz()
{
	return 1.0 / ( pod -> oblicz() );
}

std::string odwrot::opis()
{
	return "odwrot(" + pod -> opis() + ")";
}


dodaj::dodaj( wyrazenie* l, wyrazenie* p )
{
	left = l;
	right = p;
}

double dodaj::oblicz()
{
	return ( left -> oblicz() ) + ( right -> oblicz() );
}

std::string dodaj::opis()
{
	return "(" + ( left -> opis() ) + "+" + ( right -> opis() ) + ")";
}


odejmij::odejmij( wyrazenie* l, wyrazenie* p )
{
	left = l;
	right = p;
}

double odejmij::oblicz()
{
	return ( left -> oblicz() ) - ( right -> oblicz() );
}

std::string odejmij::opis()
{
	return "(" + ( left -> opis() ) + "-" + ( right -> opis() ) + ")";
}


mnoz::mnoz( wyrazenie* l, wyrazenie* p )
{
	left = l;
	right = p;
}

double mnoz::oblicz()
{
	return ( left -> oblicz() ) * ( right -> oblicz() );
}

std::string mnoz::opis()
{
	return "(" + ( left -> opis() ) + "*" + ( right -> opis() ) + ")";
}


dziel::dziel( wyrazenie* l, wyrazenie* p )
{
	left = l;
	right = p;
}

double dziel::oblicz()
{
	double p = right -> oblicz();
	if( p == 0.0 )
		throw std::invalid_argument("dzielenie przez zero");
	return ( left -> oblicz() ) / ( right -> oblicz() );
}

std::string dziel::opis()
{
	return "(" + ( left -> opis() ) + "/" + ( right -> opis() ) + ")";
}

/////////////////////////////////////////tutaj trzeba dopisac logarytm

modulo::modulo( wyrazenie* l, wyrazenie* p )
{
	left = l;
	right = p;
}

double modulo::oblicz()
{
	double l = left -> oblicz();
	double p = right -> oblicz();
	while( p > l )
		p -= l;
	return p;
}

std::string modulo::opis()
{
	return "(" + ( left -> opis() ) + "%" + ( right -> opis() ) + ")";
}

potega::potega( wyrazenie* l, wyrazenie* p )
{
	left = l;
	right = p;
}

double potega::oblicz()
{
	return pow( ( left -> oblicz() ), ( right -> oblicz() ) );
}

std::string potega::opis()
{
	return "(" + ( left -> opis() ) + "^" + ( right -> opis() ) + ")";
}
