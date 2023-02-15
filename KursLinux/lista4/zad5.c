//Szymon Kiczak Lista 4 Zadanie 5

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>	

int main(int argc, char **argv)
{
    int capitalize = 0;
    char greeting[1000] = "Hello";
    int help = 0;
    int world = 0;
    int version = 0;
    char color[200] = "never";

    int c;
    while( 1 )
    {
        static struct option long_options[] =
        {
            {"capitalize", no_argument, 0, 'c'},
            {"greeting", required_argument, 0, 'g'},
            {"help", no_argument, 0, 'h'},
            {"version", no_argument, 0, 'v'},
            {"world", no_argument, 0, 'w'},
            {"color", required_argument, 0, 0},
            {0, 0, 0, 0}
        };

        int option_index = 0;

        c = getopt_long (argc, argv, "cg:hvw", long_options, &option_index);

        if( c == -1 )
            break;

        switch( c )
        {
            case 'c':
                capitalize = 1;
                break;
            case 'g':
                strcpy(greeting, optarg);
                break;
            case 'h':
                help = 1;
                break;
            case 'v':
                version = 1;
                break;
            case 'w':
                world = 1;
                break;
            case 0:
                strcpy(color, optarg);
                break;
            case '?':
                break;
        }
    }

    if( version )
    {
        printf("Version 1\n");
    }
    
    if( help )
    {
        printf("Simple program for writing Hello, name!\n");
        printf("To make first letter of word or world big use --capitalize or -c\n");
        printf("For help use -h\n");
        printf("To change Hello to something else -g something or --greeting=something\n");
        printf("To display version -v or --version\n");
        printf("To change color of name displayed --color=[always|auto|never]\n");
    }

    while( optind < argc )
    {
        if( !strcmp( color, "always" ) )
            printf("%s, \e[32m%s\e[0m!\n", greeting, argv[optind]);
        if( !strcmp( color, "auto" ) )
        {
            if( isatty(fileno(stdout)) )
                printf("%s, \e[32m%s\e[0m!\n", greeting, argv[optind]);
            else
                printf("%s, %s!\n", greeting, argv[optind]);
        }
        if( !strcmp( color, "never") )
            printf("%s, %s!\n", greeting, argv[optind]);
        optind ++;
    }

    if( world )
    {
        printf("Hello, world!\n");
    }
}