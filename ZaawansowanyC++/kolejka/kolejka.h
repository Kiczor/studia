#include <string>
#include <initializer_list>
#include <exception>

class kolejka
{
	std::string *t;
	int pocz, ile, pojemnosc;
public:
	kolejka();
	kolejka( int p );
	kolejka( const kolejka &p );
	kolejka( std::initializer_list<std::string> s );
	kolejka( kolejka&& p );
	~kolejka();
	kolejka operator=( const kolejka &x );
	kolejka operator=( kolejka&& );
	void wloz( std::string s );
	std::string wyciagnij();
	std::string sprawdz();
	int rozmiar();
};
