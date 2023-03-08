#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>

const std::vector<std::pair<int, std::string>> rzym = {{1000, "M"},{900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},{90, "XC"}, {50, "L"}, {40, "XL"}, {10, "X"},{9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}};

std::string bin2rzym( int x )
{
	std::string res = "";
	int it = 0;

	while( x > 0 )
	{
		while( rzym[it].first > x )
			it ++;

		res += rzym[it].second;
		x -= rzym[it].first;
	}

	return res;
}

int main(int argc, char* argv[] )
{
	for(int i = 1; i < argc; i++)
	{
		bool nie_cyfra = false;
		try
		{
  			std::stoi( argv[i] );
		}
		catch(std::invalid_argument& e)
		{
			std::clog << "na wejsciu nie jest liczba\n";
			continue;
		}
		if( strlen( argv[i] ) > 4 || nie_cyfra )
		{
			std::clog << "nie mozna skonwertowac na liczbe\n";
			continue;
		}

		int n = std::stoi( argv[i] );

		if( n <= 0 )
		{
			std::clog << "liczba mniejsza lub rowna 0\n";
			continue;
		}
		if( n >= 4000 )
		{
			std::clog << "liczba wieksza od 3999\n";
			continue;
		}

		std::cout << bin2rzym( n ) << "\n";
	}

	return 0;
}
