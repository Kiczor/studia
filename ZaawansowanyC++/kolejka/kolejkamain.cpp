#include "kolejka.h"
#include <iostream>

int main()
{
	kolejka *a = new kolejka(100);
	kolejka *b = new kolejka( { "asdf", "dfd" } );
	kolejka *c = new kolejka( *b );
	std::cout << b -> sprawdz() << "\n";
	kolejka *test = std::move( b );
	std::cout << b -> sprawdz() << "\n";

	while( true )
	{
		std::string zap; std::cin >> zap;

		if( zap == "koniec" )
		{
			delete a;
			return 0;
		}

		if( zap == "wyciagnij" )
		{
			std::cout << a -> wyciagnij() << "\n";
		}

		if( zap == "sprawdz" )
		{
			std::cout << a -> sprawdz() << "\n";
		}

		if( zap == "insert" )
		{
			std::string x; std::cin >> x;
			a -> wloz( x );
		}
	}
}
