#include "kolejka.h"

void kolejka::wloz(std::string a)
{
	t[(pocz + ile) % pojemnosc] = a;
	ile ++;
	/*if( ile > pojemnosc )
		throw std::invalid_argument("nie ma miejsca w kolejce");*/
}

std::string kolejka::wyciagnij()
{
	/*if( ile == 0 )
		throw std::invalid_argument("kolejka jest pusta");*/
	ile --;
	pocz = (pocz + 1) % pojemnosc;
	return t[ (pocz - 1 + pojemnosc ) % pojemnosc ];
}

std::string kolejka::sprawdz()
{
	/*if( ile == 0 )
		throw std::invalid_argument("kolejka jest pusta");*/
	return t[pocz];
}

int kolejka::rozmiar()
{
	return ile;
}

kolejka::kolejka()
{
	pocz = 0; ile = 0; pojemnosc = 1;
	t = new std::string[pojemnosc + 1];
}

kolejka::kolejka( int p )
{
	pocz = 0; ile = 0; pojemnosc = p;
	t = new std::string[p + 1];
}

kolejka::kolejka( const kolejka &x )
{
	pojemnosc = x.pojemnosc; pocz = x.pocz; ile = x.ile;
	t = new std::string[pojemnosc];
	for(int i = 0; i < pojemnosc; i++)
		t[i] = x.t[i];
}

kolejka::kolejka( kolejka&& x )
{
	pojemnosc = x.pojemnosc; pocz = x.pocz; ile = x.ile;
	t = x.t;
	x.t = nullptr;
}

kolejka::kolejka( initializer_list<std::string> s )
{
	pojemnosc = s.size();
	t = new std::string[pojemnosc];
	pocz = 0; ile = 0;
	for(int i = 0; i < s.size(); i++)
	{
		ile ++;
		q[i] = s[i];
	}
}

kolejka kolejka::operator=( const kolejka &x )
{
	pojemnosc = x.pojemnosc; pocz = x.pocz; ile = x.ile;
	delete t;
	t = new std::string[pojemnosc];
	for(int i = 0; i < pojemnosc; i++)
		t[i] = x.t[i];
	return *this;
}

kolejka kolejka::operator=( kolejka&& x )
{
	pojemnosc = x.pojemnosc; pocz = x.pocz; ile = x.ile;
	delete t;
	t = x.t;
	x.t = nullptr;
	return *this;
}

kolejka::~kolejka()
{
	delete[] t;
}
