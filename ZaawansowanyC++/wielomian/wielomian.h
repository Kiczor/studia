#include <initializer_list>
#include <exception>
#include <cmath>
#include <iostream>
#include <algorithm>

class wielomian
{
private:
	int n;
	double* a;
	void regulate( int x );
public:
	wielomian ();
	wielomian (int st);
	wielomian (int st, double wsp); // konstruktor tworzący jednomian
	wielomian (int st, const double wsp[]); // konstruktor tworzący wielomian
	wielomian (std::initializer_list<double> wsp); // lista współczynników
	wielomian (const wielomian &w); // konstruktor kopiujący
	wielomian (wielomian &&w); // konstruktor przenoszący
	wielomian& operator = (const wielomian &w); // przypisanie kopiujące
	wielomian& operator = (wielomian &&w); // przypisanie przenoszące
	friend std::istream& operator >> (std::istream &we, wielomian &w);
	friend std::ostream& operator << (std::ostream &wy, const wielomian &w);
	friend wielomian operator + (const wielomian &u, const wielomian &v);
	friend wielomian operator - (const wielomian &u, const wielomian &v);
	friend wielomian operator * (const wielomian &u, const wielomian &v);
	friend wielomian operator * (const wielomian &u, double c);
	wielomian& operator += (const wielomian &v);
	wielomian& operator -= (const wielomian &v);
	wielomian& operator *= (const wielomian &v);
	wielomian& operator *= (double c);
	double operator () (double x) const; // obliczenie wartości wielomianu dla x
	double operator [] (int i) const; // odczytanie i-tego współczynnika
	~wielomian (); // destruktor//
};
