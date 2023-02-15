#include <cstdio>
#include <cstdlib>

using namespace std;

int main()
{
    int testy; scanf("%d", &testy);
    for(int i = 0; i < testy; i++)
    {
        printf("%d\n", i);
        system("./gen > test.in");
        system("./cho < test.in > wzo.out");
        int czybrak = system("diff -bq brakfile.txt wzo.out");
        if( !czybrak )
        {
            system("python3 brut.py < test.in > bru.out");
            int czy2 = system("diff -bq wzo.out bru.out");
            if( czy2 != 0 )
            {
                printf("ZLE\n");
                printf("test:");
                system("cat test.in");

                printf("odpowiedz brut:");
                system("cat bru.out");

                printf("odpowiedz wzorcoweczka:");
                system("cat wzo.out");
                break;
            }
            printf("odpowiedz brak\n");
            continue;
        }
        system("./check < wzo.out");
    }
}
