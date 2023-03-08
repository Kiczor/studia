#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

int n, wynik;
double R, D;

int main()
{
    scanf("%lf%lf%d", &R, &D, &n);
    for(int i = 0; i < n; i++)
    {
        double x, y, r; scanf("%lf%lf%lf", &x, &y, &r);
        double dl = sqrt( x * x + y * y );
        if( R - D + r <= dl && dl + r <= R )
            wynik ++;
    }

    printf("%d", wynik);
}
