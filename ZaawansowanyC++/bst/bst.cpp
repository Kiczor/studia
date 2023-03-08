#include "bst.h"

template <typename T>
bst<T>::node::node()
{
	left = nullptr;
	right = nullptr;
}

template <typename T>
bst<T>::node::node( T x )
{
	value = x;
	left = nullptr;
	right = nullptr;
	parent = nullptr;
}

template <typename T>
bst<T>::bst()
{
	rozmiar = 0;
	root = new node();
}

template <typename T>
bst<T>::bst( std::initializer_list<T> s )
{
	rozmiar = 0;
	root = new node();
	for(auto it = s.begin(); it != s.end(); it++)
		dodaj( *it );
}

template <typename T>
bst<T>::bst( const bst<T> &b )
{
	rozmiar = 0;
	root = new node();
	std::vector<T> x;
	std::vector<T>& v = x;
	flatten( v, b.root );
	std::random_shuffle( v.begin(), v.end() );

	for(int i = 0; i < v.size(); i++)
		dodaj( v[i] );
}

template <typename T>
bst<T>::bst( bst<T>&& b )
{
	rozmiar = 0;
	root = new node();

	root = b.root;
	b.root = nullptr;
}

template <typename T>
void bst<T>::zdodaj( T x, bst<T>::node* u )
{
	//std::cout << "jestem w: " << x << "\n";
	if( ( u -> value ) == x )
	{
		rozmiar --;
		return;
	}

	if( u == nullptr )
		return;

	if( ( u -> value ) > x )
	{
		if( ( u -> left ) == nullptr )
		{
			u -> left = new node( x );
			u -> left -> parent = u;
			return;
		}
		zdodaj( x, u -> left );
		return;
	}

	if( ( u -> right ) == nullptr )
	{
		u -> right = new node( x );
		u -> right -> parent = u;
		return;
	}
	zdodaj( x, u -> right );
	return;
}

template <typename T>
bool bst<T>::czyjest( T x, bst<T>::node* u )
{
	if( ( u -> value ) == x )
		return true;

	if( ( u -> value ) > x )
	{
		if( ( u -> left ) == nullptr )
			return false;
		else
			return czyjest( x, u -> left );
	}

	if( ( u -> right ) == nullptr )
		return false;
	else
		return czyjest( x, u -> right );
}

template <typename T>
bool bst<T>::search( T x )
{
	return czyjest( x, root );
}

template<typename T>
void bst<T>::dodaj( T x )
{
	//std::cout << "dodaje " << x << "\n";
	if( rozmiar == 0 && ( ( root -> left == nullptr ) && ( root -> right == nullptr ) ) )
		root -> value = x;
	else
		zdodaj( x, root );
	rozmiar ++;
	return;
}

template <typename T>
typename bst<T>::node* bst<T>::znajdz( T x, bst<T>::node* u )
{
		if( ( u -> value ) == x )
			return u;

	if( ( u -> value ) > x )
	{
		if( ( u -> left ) == nullptr )
			return u;
		return znajdz( x, u -> left );
	}

	if( ( u -> right ) == nullptr )
		return u;
	return znajdz( x, u -> right );
}

template<typename T>
typename bst<T>::node* bst<T>::znajdzmin( node* u )
{
	if( u -> left == nullptr )
		return u;

	return znajdzmin( u -> left );
}

template<typename T>
typename bst<T>::node* bst<T>::znajdznast( node* u )
{
	if( u -> right != nullptr )
		return znajdzmin( u );

	bst<T>::node* t = u -> parent;
	while( t != nullptr && t -> left != u )
	{
		u = t;
		t = t -> parent;
	}
	return t;
}

template<typename T>
void bst<T>::usuwanie( T x, bst<T>::node* u, bool czylewy )
{
	//std::cout << "usuwam: " << x << " i jestem w: " << u -> value << "\n";
	if( x == u -> value )
	{
		if( ( ( u -> left ) == nullptr ) && ( ( u -> right ) == nullptr ) )
		{
			if( czylewy )
				u -> parent -> left = nullptr;
			else
				u -> parent -> right = nullptr;
			return;
		}

		if( ( u -> left ) == nullptr )
		{
			if( czylewy )
			{
				u -> parent -> left = u -> right;
				u -> parent -> left -> parent = u -> parent;
			}
			else
			{
				u -> parent -> right = u -> right;
				u -> parent -> right -> parent = u -> parent;
			}

			u -> left = nullptr;
			u -> right = nullptr;
			return;
		}

		if( ( u -> right ) == nullptr )
		{
			if( czylewy )
			{
				u -> parent -> left = u -> left;
				u -> parent -> left -> parent = u -> parent;
			}
			else
			{
				u -> parent -> right = u -> left;
				u -> parent -> right -> parent = u -> parent;
			}

			u -> left = nullptr;
			u -> right = nullptr;
			return;
		}

		bst<T>::node* zast = znajdznast( u );
		u -> value = zast -> value;
		if( zast -> right == nullptr )
		{
			zast -> parent -> left = nullptr;
		}
		else
		{
			zast -> parent -> left = zast -> right;
			zast -> right -> parent = zast -> parent;
		}
		return;
	}

	if( u -> value > x )
		usuwanie( x, u -> left, true );
	else
		usuwanie( x, u -> right, false );
	return;
}

template<typename T>
void bst<T>::usun( T x )
{
	if( !czyjest( x, root ) )
		throw std::invalid_argument("nie mozna usuwac z bst elementu ktorego tam nie ma");

	usuwanie( x, root, false );
}

template<typename T>
bst<T>::node::~node()
{
	delete left;
	delete right;
	delete this;
}

template<typename T>
bst<T>::~bst()
{
	delete (root -> left);
	delete (root -> right);
	delete this;
}

template<typename T>
void bst<T>::flatten( std::vector<T>& s, bst<T>::node* u )
{
	if( u == nullptr )
		return;

	flatten( s, u -> left );
	s.push_back( u -> value );
	flatten( s, u -> right );
}

template<typename T>
bst<T>& bst<T>::operator =( const bst<T>& w )
{
	std::vector<T> x;
	std::vector<T>& v = x;
	flatten( v, w.root );
	std::random_shuffle( v.begin(), v.end() );

	delete root;
	root = new bst<T>::node();
	rozmiar = 0;
	for(int i = 0; i < v.size(); i++)
		dodaj( v[i] );

	return *this;
}

template<typename T>
bst<T>& bst<T>::operator =( bst<T>&& w )
{
	delete this;
	root = w.root;
	w.root = nullptr;
	return *this;
}

template class bst<int>;
//template class bst<std::string>;
