#include <cstdio>

typedef int data;

using namespace std;

struct tab
{
	int left, right, size;
	int *t;

	tab()
	{
		left = 0;
		right = 0;
		size = 0;
	}

	void ins( int it, data x )
	{
		if( size == 0 )
		{
			size = 1;
			t = new data[size + 1];
			*t = x;
			left = it;
			right = it;
		}
		else
		{
			if( left < it && it < right )
			{
				*(t + it - left) = x;
			}
			else
			{
				if( left > it )
				{
					int *newt = new data[right - it + 2];
					*newt = x;

					int d = left - it;
					for(int i = 0; i < size; i++)
					{
						*(newt + d + i) = *( t + i );
					}

					left = it;
					size = right - left + 1;
					delete[] t;
					t = newt;
				}
				else
				{
					int *newt = new data[it - left + 2];

					for(int i = 0; i < size; i++)
					{
						*( newt + i ) = *(t + i);
					}

					*( newt + it - left ) = x;
					right = it;
					size = right - left + 1;
					delete[] t;
					t = newt;
				}
			}
		}
	}

	void wypisz()
	{
		for(int i = 0; i < size; i++)
			printf("%d ", *(t + i) );
		printf("\n");
	}
};

int main()
{
	tab s = tab();

	s.ins( -1, 2 );
	s.wypisz();
	s.ins( -2, 234 );
	s.wypisz();
	s.ins( -3, 33 );
	s.wypisz();

	s.ins( 2, 3 );
	s.ins( 3, 4 );

	s.wypisz();
}
