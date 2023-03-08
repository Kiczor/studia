#include "wielomian.h"

int main()
{
	wielomian *t1 = new wielomian( { 1.2, 3.4 } );
	std::cout << *t1 << "\n";
	std::cout << *( new wielomian( { 1.9, 2.2 } ) );

	wielomian *t2 = new wielomian( { 1.0, 1.0, 2.0 } );
	wielomian *t3 = new wielomian( 2 );
	*t3 = (*t2) * (*t2);
	std::cout << *t3;
	std::cout << *t2 * 3.0;

	std::cout << (*t1)[1] << "\n";
	std::cout << (*t2)(2.0) << "\n";

	wielomian *t4 = new wielomian( *t2 );
	*t4 -= *t1;
	std::cout << *t4;

	//testy pamieci
	int lim = 50000000;
	wielomian *tst = new wielomian( 2 );
	for(int i = 0; i <= lim; i++)
	{
		//std::cout << new wielomian( { (double)i, (double)(i + 1) } );
		*tst = *(new wielomian( { (double)i, (double)(i + 1) } ));
		//*tst = *t2;
		//wielomian tst2;
		//*tst2 = *tst;
	}
}
