#include "wielomian.h"

wielomian::wielomian()
{
	 n = 0;
	 a = new double[1];
}

wielomian::wielomian( int st, double wsp )
{
	if( st < 0 ) throw std::invalid_argument("nie mozna tworzyc wielomianu o stopniu mniejszym od zera");
	n = st;
	a = new double[n + 1];
	*a = wsp;
}

wielomian::wielomian( int st )
{
	if( st < 0 ) throw std::invalid_argument("nie mozna tworzyc wielomianu o stopniu mniejszym od zera");
	n = st;
	a = new double[n + 1];
}

wielomian::wielomian(int st, const double wsp[] )
{
	if( st < 0 ) throw std::invalid_argument("nie mozna tworzyc wielomianu o stopniu mniejszym od zera");
	n = st;
	a = new double[n + 1];
	for(int i = 0; i <= n; i++)
		a[i] = wsp[i];
}

wielomian::wielomian ( std::initializer_list<double> wsp )
{
	n = wsp.size() - 1;
	a = new double[n + 1];

	int i = 0;
	for(auto it = wsp.begin(); it != wsp.end(); it++)
	{
		a[i] = *it;
		i++;
	}
}

wielomian::wielomian ( const wielomian &w )
{
	n = w.n;
	a = new double[n + 1];
	for(int i = 0; i <= n; i++)
		a[i] = w.a[i];
}

wielomian::wielomian ( wielomian &&w )
{
	n = w.n;
	delete[] a;
	a = w.a;
	w.a = nullptr;
}

wielomian& wielomian::operator= ( const wielomian &w )
{
	n = w.n;
	delete[] a;
	a = new double[n + 1];
	for(int i = 0; i <= n; i++)
		a[i] = w.a[i];
	return *this;
}

wielomian& wielomian::operator= ( wielomian&& w )
{
	/*this -> ~wielomian();
	n = std::move( w.n );
	a = std::move( w.a );*/
	n = w.n;
	delete[] a;
	a = w.a;
	w.a = nullptr;
	return *this;
}

std::ostream& operator << ( std::ostream &wy, const wielomian &w )
{
	wy << "stopien wielomianu: " << w.n << "\nwspolczynniki wielomianu:\n";
	for(int i = 0; i <= w.n; i++)
		wy << w.a[i] << " ";
	wy << "\n";
	return wy;
}

std::istream& operator >> ( std::istream &we, wielomian &w )
{
	we >> w.n;
	for(int i = w.n; i >= 0; i--)
		we >> w.a[i];
	return we;
}

void wielomian::regulate( int x )
{
	double* temp = new double[x + 1];
	for(int i = 0; i <= n; i++)
		temp[i] = a[i];
	for(int i = n + 1; i <= x; i++)

	delete[] a;
	n = x;
	a = temp;
}

wielomian operator + ( const wielomian &w, const wielomian &v )
{
	int nres = std::max( w.n, v.n );

	wielomian res = wielomian( nres );
	for(int i = 0; i <= nres; i++)
		res.a[i] = ( (i > w.n) ? 0 : w.a[i] ) + ( ( i > v.n ) ? 0 : v.a[i] );
	return res;
}

wielomian operator - ( const wielomian &w, const wielomian &v )
{
	int nres = std::max( w.n, v.n );

	wielomian res = wielomian( nres );
	for(int i = 0; i <= nres; i++)
		res.a[i] = ( (i > w.n) ? 0 : w.a[i] ) - ( ( i > v.n ) ? 0 : v.a[i] );
	return res;
}

wielomian operator * ( const wielomian &u, const wielomian &v )
{
	wielomian res = wielomian( u.n + v.n );

	for(int i = 0; i <= u.n; i++)
	{
		for(int j = 0; j <= v.n; j++)
		{
			//std::cout << "i: " << i << " j: " << j << "\n";
			res.a[i + j] += u.a[i] * v.a[j];
		}
	}

	return res;
}

wielomian operator * (const wielomian &u, double c)
{
	wielomian res = wielomian( u.n );
	for(int i = 0; i <= u.n; i++)
		res.a[i] = u.a[i] * c;
	return res;
}

wielomian& wielomian::operator += ( const wielomian &v )
{
	if( v.n > n )
		regulate( v.n );

	for(int i = 0; i <= std::min( n, v.n ); i++)
		a[i] += v.a[i];

	return *this;
}

wielomian& wielomian::operator -= ( const wielomian &v )
{
	if( v.n > n )
		regulate( v.n );

	for(int i = 0; i <= std::min( n, v.n ); i++)
		a[i] -= v.a[i];

	return *this;
}

wielomian& wielomian::operator *= ( const wielomian &v )
{
	wielomian res = wielomian( v.n + n );
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= v.n; j++)
			res.a[i + j] += a[i] * v.a[j];

	a = res.a;
	res.a = nullptr;
	return *this;
}

wielomian& wielomian::operator *= ( double c )
{
	for(int i = 0; i <= n; i++)
		a[i] *= c;
	return *this;
}

double wielomian::operator() ( double x ) const
{
	double res = 0.0, mnoz = 1;
	for(int i = 0; i <= n; i++)
	{
		res += mnoz * a[i];
		mnoz *= x;
	}

	return res;
}

double wielomian::operator[] ( int i ) const
{
	return *(a + i);
}

wielomian::~wielomian()
{
	delete[] a;
	//delete &n;
}
