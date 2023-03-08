#include <vector>
#include <algorithm>
#include <iostream>
#include <initializer_list>
#include <exception>
#include <cmath>
#include <vector>

template <typename T>
class bst
{
	class node
	{
	public:
		T value;
		node* left;
		node* right;
		node* parent;
		node();
		node( T x );
		~node();

		//template <typename U>
		void wypis( std::ostream& wy, const typename bst<T>::node& b )
		{
			if( b.left != nullptr )
				wypis( wy, *b.left );
			wy << b.value << "\n";
			if( b.right != nullptr )
				wypis( wy, *b.right );
		}
	};

	int rozmiar;
	node* root;
	void zdodaj( T x, node* u );
	bool czyjest( T x, node* u );
	void flatten( std::vector<T>& s, node* u );
	void usuwanie( T x, node* u, bool czylewy );
	node* znajdz( T x, node* u );
	node* znajdznast( node* u );
	node* znajdzmin( node* u );
public:
	bst();
	bst( std::initializer_list<T> s );
	bst( const bst<T> &b );
	bst( bst<T> &&b );
	void dodaj( T x );
	void usun( T x );
	bool search( T x );

	template <typename U>
	friend std::ostream& operator <<( std::ostream& wy, const bst<U>& b )
	{
		b.root -> wypis( wy, *b.root );
		return wy;
	}

	bst<T>& operator =(const bst<T>& w);
	bst<T>& operator =(bst &&w);
	~bst();
};
