#!/bin/bash
#Szymon Kiczak Lista 4 zadanie 4

op=`getopt -o cg:hvw --long capitalize::,greeting::,help::,version::,world::,color:: -- "$@"`
eval set -- "$op"

CAPITALIZE=false
GREETING="Hello"
HELP=false
WORLD=false
VERSION=false

while true ; do
    case $1 in
        -c|--capitalize)
            CAPITALIZE=true;;
        -g|--greeting)
            shift;
            GREETING=$1;;
        -h|--help)
            HELP=true;;
        -v|--version)
            VERSION=true;;
        -w|--world)
            WORLD=true;;
        --color)
            shift;
            COLORING=$1
            if [ ! "$COLORING" = "always" ] && [ ! "$COLORING" = "auto" ] && [ ! "$COLORING" = "never" ]
            then 
                echo "Incorrect coloring option"
                echo $COLORING
                exit 1
            fi
            ;;
        --)
            shift; break;;
    esac
    shift
done

if $HELP
then
    echo "Simple program for writing Hello, name!\n"
    echo "To make first letter of word or world big use --capitalize or -c"
    echo "For help use -h"
    echo "To change Hello to something else -g something or --greeting=something"
    echo "To display version -v or --version"
    echo "To change color of name displayed --color=[always|auto|never]"
fi
if $VERSION
then
    echo "Version 1"
fi

for var in "$@"
do
    if [ "$COLORING" = "always" ]
    then
        echo -e $GREETING, "\e[32m"$var"\e[0m!"
    fi
    if [ "$COLORING" = "auto" ]
    then
        if [ -t 1 ]
        then
            echo -e $GREETING, "\e[32m"$var"\e[0m!"
        else
            echo -e $GREETING, $var"!"
        fi
    fi
    if [ "$COLORING" = "never" ]
    then
        echo -e $GREETING, $var"!"
    fi
done

if $WORLD
then
    echo "Hello, world!"
fi