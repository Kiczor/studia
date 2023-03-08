#include <cstdio>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <iostream>
#include <exception>

class wyrazenie
{
public:  // moze VIRTUAL?
	virtual double oblicz(){};
	virtual std::string opis(){};
	//~wyrazenie();
};

class liczba : public wyrazenie
{
private:
	double val;
public:
	liczba( double x );
	double oblicz();
	std::string opis();
};

class zmienna : public wyrazenie
{
private:
	std::string etykieta;
	static std::vector<std::pair<std::string, double> > wartosci;
public:
	zmienna( std::string s );
	static void setvalue( std::string e, double x );
	static double findvalue( std::string e );
	double oblicz();
	std::string opis();
};

class stala : public wyrazenie
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

class operator1arg : public wyrazenie
{
protected:
	wyrazenie* pod;
};

class sinus : public operator1arg
{
public:
	sinus( wyrazenie* x );
	double oblicz();
	std::string opis();
};

class cosinus : public operator1arg
{
public:
	cosinus( wyrazenie* x );
	double oblicz();
	std::string opis();
};

class exp : public operator1arg
{
public:
	exp( wyrazenie* x );
	double oblicz();
	std::string opis();
};

class ln : public operator1arg
{
public:
	ln( wyrazenie* x );
	double oblicz();
	std::string opis();
};

class bezwzgl : public operator1arg
{
public:
	bezwzgl( wyrazenie* x );
	double oblicz();
	std::string opis();
};

class przeciw : public operator1arg
{
public:
	przeciw( wyrazenie* x );
	double oblicz();
	std::string opis();
};

class odwrot : public operator1arg
{
public:
	odwrot( wyrazenie* x );
	double oblicz();
	std::string opis();
};

class operator2arg : public wyrazenie
{
protected:
	wyrazenie* left;
	wyrazenie* right;
};

class dodaj : public operator2arg
{
public:
	dodaj( wyrazenie* a, wyrazenie* b );
	double oblicz();
	std::string opis();
};

class odejmij : public operator2arg
{
public:
	odejmij( wyrazenie* a, wyrazenie* b );
	double oblicz();
	std::string opis();
};

class mnoz : public operator2arg
{
public:
	mnoz( wyrazenie* a, wyrazenie* b );
	double oblicz();
	std::string opis();
};

class dziel : public operator2arg
{
public:
	dziel( wyrazenie* a, wyrazenie* b );
	double oblicz();
	std::string opis();
};

class logarytm : public operator2arg
{
public:
	logarytm( wyrazenie* a, wyrazenie* b );
	double oblicz();
	std::string opis();
};

class modulo : public operator2arg
{
public:
	modulo( wyrazenie* a, wyrazenie* b );
	double oblicz();
	std::string opis();
};

class potega : public operator2arg
{
public:
	potega( wyrazenie* a, wyrazenie* b );
	double oblicz();
	std::string opis();
};
