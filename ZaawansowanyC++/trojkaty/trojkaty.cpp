#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>

const double EPS = 0.00001;

class punkt
{
	double x, y;
public:
	punkt(){}
	punkt( double a, double b )
	{
		x = a;
		y = b;
	}

	double getx(){ return x; }
	double gety(){ return y; }

	void setx( double a ){ x = a; }
	void sety( double a ){ y = a; }

	void move( double vx, double vy )
	{
		x += vx;
		y += vy;
	}

	void obroc( double kat, punkt p )
	{
		double px = p.getx(), py = p.gety();
		double x1 = ( x - px ) * cos( kat ) - ( y - py ) * sin( kat ) + px;
		double y1 = ( x - px ) * sin( kat ) + ( y - py ) * cos( kat ) + py;
		x = x1; y = y1;
	}

	void wypisz()
	{
		std::cout << x << ", " << y << "\n";
	}
	/*punkt operator=( )
	{
	}*/
};

double dist( punkt a, punkt b )
{
	return std::sqrt( ( a.getx() - b.gety() ) * ( a.getx() - b.gety() ) + ( a.gety() - b.gety() ) * ( a.gety() - b.gety() ) );
}

class odcinek
{
	punkt p, k;
public:
	odcinek(){}
	odcinek( punkt a, punkt b )
	{
		p = punkt( a.getx(), a.gety() );
		k = punkt( b.getx(), b.gety() );
	}

	punkt getp(){ return p; }
	punkt getk(){ return k; }

	void move( double vx, double vy )
	{
		p.move( vx, vy );
		k.move( vx, vy );
	}

	void obroc( double kat, punkt pt )
	{
		p.obroc( kat, pt );
		k.obroc( kat, pt );
	}

	double length()
	{
		return dist( p, k );
	}

	punkt srodek()
	{
		return punkt( ( p.getx() + k.getx() ) / 2.0, ( p.gety() + k.gety() ) / 2.0 );
	}

	void wypisz()
	{
		std::cout << "odc: ";
		p.wypisz();
		k.wypisz();
		std::cout << "\n";
	}
};

punkt przeciecie( odcinek o1, odcinek o2 )
{

}

double ilowek( punkt a, punkt b, punkt c )
{
	double ax = a.getx() - c.getx(), ay = a.gety() - c.gety(), bx = b.getx() - c.getx(), by = b.gety() - c.gety();
	return ax * by - ay * bx;
}

double iloskal( punkt a, punkt b, punkt c )
{
	double ax = a.getx() - c.getx(), ay = a.gety() - c.gety(), bx = b.getx() - c.getx(), by = b.gety() - c.gety();
	return ax * bx + ay * by;
}

bool rownolegle( odcinek a, odcinek b )
{
	punkt ap = a.getp(), ak = a.getk(), bp = b.getp(), bk = b.getk();

	bp.setx( bp.getx() - ap.getx() );
	bp.sety( bp.gety() - ap.gety() );
	bk.setx( bk.getx() - ap.getx() );
	bk.sety( bk.gety() - ap.gety() );

	double il = iloskal( bk, ak, ap );
	il /= a.length() * b.length();

	if( abs( abs( il ) - 1.0 ) < EPS )
		return true;
	return false;
}

bool prostopadle( odcinek a, odcinek b )
{
	punkt ap = a.getp(), ak = a.getk(), bp = b.getp(), bk = b.getk();

	bp.setx( bp.getx() - ap.getx() );
	bp.sety( bp.gety() - ap.gety() );
	bk.setx( bk.getx() - ap.getx() );
	bk.sety( bk.gety() - ap.gety() );

	double il = iloskal( bk, ak, ap );
	//il /= a.length() * b.length();

	std::cout << il << "\n";

	if( abs( il ) < EPS )
		return true;
	return false;
}

class trojkat
{
	punkt a, b, c;
public:
	trojkat(){}
	trojkat( punkt x, punkt y, punkt z)
	{
		a = punkt( x.getx(), x.gety() );
		b = punkt( y.getx(), y.gety() );
		c = punkt( z.getx(), z.gety() );
	}

	punkt geta(){ return a; }
	punkt getb(){ return b; }
	punkt getc(){ return c; }

	double obwod()
	{
		return dist( a, b ) + dist( b, c ) + dist( a, c );
	}

	double pole()
	{
		return abs( ilowek( a, b, c ) );
	}

	void move( double vx, double vy )
	{
		a.move( vx, vy );
		b.move( vx, vy );
		c.move( vx, vy );
	}

	void obroc( double kat, punkt s )
	{
		a.obroc( kat, s );
		b.obroc( kat, s );
		c.obroc( kat, s );
	}

	bool wewnatrz( punkt d )
	{
		double w1 = ilowek( a, d, c ), w2 = ilowek( b, d, a ), w3 = ilowek( c, d, b );

		if( w1 >= 0 && w2 >= 0 && w3 >= 0 )
			return true;
		if( w1 <= 0 && w2 <= 0 && w3 <= 0 )
			return true;
		return false;
	}
};

punkt srodektrojkata( trojkat t )
{
	punkt a = t.geta(), b = t.getb(), c = t.getc();
	return punkt( ( a.getx() + b.getx() + c.getx() ) / 3.0, ( a.gety() + b.gety() + c.gety() ) / 3.0 );
}

bool trojkat_w_trojkacie( trojkat t1, trojkat t2 ) //czy t2 jest w t1
{
	if( t1.wewnatrz( t2.geta() ) && t1.wewnatrz( t2.getb() ) && t1.wewnatrz( t2.getc() ) )
		return true;
	return false;
}

bool trojkaty_przecinaja_sie( trojkat t1, trojkat t2 )
{
	if( !( t1.wewnatrz( t2.geta() ) && t1.wewnatrz( t2.getb() ) && t1.wewnatrz( t2.getc() ) ) && ( t1.wewnatrz( t2.geta() ) || t1.wewnatrz( t2.getb() ) || t1.wewnatrz( t2.getc() ) ) )
		return true;
	return false;
}

int main()
{
	punkt test1 = punkt( 1.5, 2.5 );
	test1.move( 0.5, -0.5 );
	test1.wypisz();
	test1.obroc( M_PI / 2.0, punkt( 0.0, 0.0 ) );
	test1.wypisz();

	odcinek odc1 = odcinek( punkt( 1, 1 ), punkt( 4, 7 ) );
	std::cout << odc1.length() << "\n";
	odc1.srodek().wypisz();

	odcinek odc2 = odcinek( punkt( 1, 1 ), punkt( 5, 7 ) );
	odcinek odc3 = odcinek( punkt( 1, 4 ), punkt( 6, 4 ) );
	std::cout << rownolegle( odc2, odc3 ) << "\n";
	std::cout << rownolegle( odc1, odc2 ) << "\n";

	odcinek odc4 = odcinek( punkt( 3, 1 ), punkt( 0, 8 ) );
	std::cout << prostopadle( odc3, odc4 ) << "\n";
	std::cout << prostopadle( odc3, odc2 ) << "\n";
}
