//Szymon Kiczak Lista 8 Zadanie 3

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>	
#include <time.h>

int main(int argc, char **argv)
{
    int period = 1;
    int interval = 60;
    char logfile[2000] = "/var/log/mystat.log";

    int ile = 0;
    double srednia = 0.0;
    double maksimum = 0.0;
    double minimum = 10000.0;
   
    int c;
    while( 1 )
    {
        static struct option long_options[] =
        {
            {"period", required_argument, 0, 'p'},
            {"interval", required_argument, 0, 'i'},
            {"logfile", required_argument, 0, 'f'},
            {0, 0, 0, 0}
        };

        int option_index = 0;

        c = getopt_long(argc, argv, "p:i:f:", long_options, &option_index);

        if( c == -1 )
            break;

        switch( c )
        {
            case 'p':
                period = atoi( optarg );
                break;
            case 'i':
                interval = atoi( optarg );
                break;
            case 'f':
                strcpy(logfile, optarg);
                break;
            case '?':
                break;
        }
    }

    printf("period:%d, interval:%d\n", period, interval);
    for(int i = 0; i < strlen( logfile ); i++)
        printf("%c", logfile[i]);

    //czyszczenie logow
    FILE * czysc = fopen( logfile, "w" );
    fclose( czysc );

    FILE * pproc = fopen( "/proc/stat", "r" );

    //poczatkowe wartosci, poniewaza dane w stat/proc sa od uruchomienia komputera
    char psmiec[200];
    fscanf( pproc, "%s", psmiec);
    int puser, pnice, psystem, pidle, piowait, pirq, psoftirq;
    fscanf( pproc, " %d %d %d %d %d %d %d", &puser, &pnice, &psystem, &pidle, &piowait, &psoftirq);
    int pwszystko = puser + pnice + psystem + pidle + piowait + pirq + psoftirq;
    double pwynik = 100.0 - (pidle * 100.0)/pwszystko;
    
    double licznik = 0.0;

    clock_t teraz = clock();
    clock_t ostatnio = teraz;

    double interwaly = interval;
    double okresy = period;
    while(1)
    {
        teraz = clock();

        licznik += (double)(teraz - ostatnio);
        ostatnio = teraz;

        if( licznik > (double)( okresy * CLOCKS_PER_SEC ) )
        {
            okresy += period;
            ile ++;
            FILE * proc = fopen( "/proc/stat", "r" );
            char smiec[200];
            fscanf( proc, "%s", smiec);
            int user, nice, system, idle, iowait, irq, softirq;
            fscanf( proc, " %d %d %d %d %d %d %d", &user, &nice, &system, &idle, &iowait, &softirq);
            int wszystko = user + nice + system + idle + iowait + irq + softirq;
            double wynik = 100.0 - ((idle - pidle) * 100.0)/(wszystko - pwszystko);
            pwszystko = wszystko;
            pidle = idle;

            if( wynik > maksimum )
            {
                maksimum = wynik;
            }
            if( wynik < minimum )
            {
                minimum = wynik;
            }

            srednia = (srednia * (ile - 1.0) + wynik) / ile;
            printf("\n%lf", wynik);
        }

        if( licznik > (double)( interwaly * CLOCKS_PER_SEC ) )
        {
            interwaly += interval;
            printf("%lf/%lf/%lf\n", minimum, srednia, maksimum);
            FILE * fl = fopen( logfile, "a" );
            fprintf(fl, "%lf/%lf/%lf\n", minimum, srednia, maksimum);
            fclose( fl );
        }
    }
}