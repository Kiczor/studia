#include "wyrazenia.h"

int main()
{
	wyrazenie* t1 = new dodaj( new pi(), new liczba( 2.0 ) );
	std::cout << t1 -> opis() << "\n";
	std::cout << t1 -> oblicz() << "\n";

	wyrazenie *w = new odejmij(new pi(),new dodaj(new liczba(2),new mnoz(new zmienna("x"),new liczba(7))));
	zmienna::setvalue( "x", 1.0 );
	std::cout << w -> opis() << "\n";
	std::cout << w -> oblicz() << "\n";

	zmienna::setvalue( "x", 2.0 );
	std::cout << w -> oblicz() << "\n";

	wyrazenie* t2 = new dziel( new mnoz( new odejmij( new zmienna( "x" ), new liczba( 1 ) ), new zmienna( "x" ) ), new liczba( 2 ) );
	std::cout << t2 -> opis() << "\n";

	wyrazenie* t3 = new dziel( new dodaj( new liczba( 3 ), new liczba( 5 ) ), new dodaj( new liczba( 2 ), new mnoz( new zmienna( "x" ), new liczba( 7 ) ) ) );
	std::cout << t3 -> opis() << "\n";

	wyrazenie* t4 = new odejmij( new dodaj( new liczba( 2 ), new mnoz( new zmienna( "x" ), new liczba( 7 ) ) ), new dodaj( new mnoz( new zmienna("y"), new liczba( 3 ) ), new liczba( 5 ) ) );
	std::cout << t4 -> opis() << "\n";
	//std::cout << t4 -> oblicz() << "\n";

	wyrazenie* t5 = new dziel(
		new cosinus(
			new mnoz(
				new dodaj
				(
					new zmienna( "x" ),
					new liczba( 1 )
				),
				new zmienna( "x" )
			)
		),
		new potega(
			new e(),
			new potega
			(
				new zmienna( "x" ),
				new liczba( 2 )
			)
		)
	);

	std::cout << t5 -> opis() << "\n";

	zmienna::setvalue( "y", 1 );
	for( double xv = 0.0; xv <= 1; xv += 0.01 )
	{
		zmienna::setvalue( "x", xv );
		std::cout << "xv: " << xv << "\n";
		std::cout << "wartosc 1: " << t2 -> oblicz() << "\n";
		std::cout << "wartosc 2: " << t3 -> oblicz() << "\n";
		std::cout << "wartosc 3: " << t4 -> oblicz() << "\n";
		std::cout << "wartosc 4: " << t5 -> oblicz() << "\n";
		std::cout << "\n";
	}
}
