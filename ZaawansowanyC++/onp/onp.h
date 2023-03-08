#include <cstdio>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>
#include <exception>
#include <set>

class symbol
{
public:  // moze VIRTUAL?
	virtual double oblicz(){};
	virtual std::string opis(){};
	//~symbol();
};

class liczba : public symbol
{
private:
	double val;
public:
	liczba( double x );
	double oblicz();
	std::string opis();
};

class zmienna : public symbol
{
private:
	std::string etykieta;
	static std::map<std::string, double> wartosci;
public:
	zmienna( std::string s );
	static void setvalue( std::string e, double x );
	static double findvalue( std::string e );
	static void czysc();
	double oblicz();
	std::string opis();
};

class stala : public symbol
{
protected:
	double val;
public:
	double oblicz();
};

class pi : public stala
{
public:
	pi();
	std::string opis();
};

class e : public stala
{
public:
	e();
	std::string opis();
};

class fi : public stala
{
public:
	fi();
	std::string opis();
};

class funkcja1arg : public symbol
{
protected:
	symbol* pod;
};

class sinus : public funkcja1arg
{
public:
	sinus( symbol* x );
	double oblicz();
	std::string opis();
};

class cosinus : public funkcja1arg
{
public:
	cosinus( symbol* x );
	double oblicz();
	std::string opis();
};

class exp : public funkcja1arg
{
public:
	exp( symbol* x );
	double oblicz();
	std::string opis();
};

class ln : public funkcja1arg
{
public:
	ln( symbol* x );
	double oblicz();
	std::string opis();
};

class bezwzgl : public funkcja1arg
{
public:
	bezwzgl( symbol* x );
	double oblicz();
	std::string opis();
};

class przeciw : public funkcja1arg
{
public:
	przeciw( symbol* x );
	double oblicz();
	std::string opis();
};

class odwrot : public funkcja1arg
{
public:
	odwrot( symbol* x );
	double oblicz();
	std::string opis();
};

class funkcja2arg : public symbol
{
protected:
	symbol* left;
	symbol* right;
};

class dodaj : public funkcja2arg
{
public:
	dodaj( symbol* a, symbol* b );
	double oblicz();
	std::string opis();
};

class odejmij : public funkcja2arg
{
public:
	odejmij( symbol* a, symbol* b );
	double oblicz();
	std::string opis();
};

class mnoz : public funkcja2arg
{
public:
	mnoz( symbol* a, symbol* b );
	double oblicz();
	std::string opis();
};

class dziel : public funkcja2arg
{
public:
	dziel( symbol* a, symbol* b );
	double oblicz();
	std::string opis();
};

class logarytm : public funkcja2arg
{
public:
	logarytm( symbol* a, symbol* b );
	double oblicz();
	std::string opis();
};

class modulo : public funkcja2arg
{
public:
	modulo( symbol* a, symbol* b );
	double oblicz();
	std::string opis();
};

class potega : public funkcja2arg
{
public:
	potega( symbol* a, symbol* b );
	double oblicz();
	std::string opis();
};
