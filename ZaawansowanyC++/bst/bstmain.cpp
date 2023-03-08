#include "bst.h"

int main()
{
	bst<int>* t1 = new bst<int>();

	t1 -> dodaj( 5 );
	t1 -> dodaj( 10 );
	t1 -> dodaj( 2 );
	t1 -> dodaj( 12 );
	std::cout << "t1:\n" << *t1 << "\n";

	bst<int>* t2 = new bst<int>( { 1, 3, 130, 212 } );
	std::cout << "t2:\n" << *t2 << "\n";

	t2 = t1;
	std::cout << "t2:\n" << *t2 << "\n";

	bst<int>* t3 = new bst<int>( *t2 );
	std::cout << "t3:\n" << *t3 << "\n";

	bst<int>* t4 = new bst<int>( { 1, 2, 5, 8, 3, 4, 11, 7, 32 } );
	t4 -> usun( 32 );
	t4 -> usun( 8 );
	std::cout << "t4:\n" << *t4 << "\n";
}
