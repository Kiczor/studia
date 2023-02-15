#!/bin/bash

for i in $(seq 0 $1)
do
	echo "$i"
	./gen > test.in
	./tro < test.in > wzo.out
	./brut < test.in > bru.out
	d=$(diff -bq <(head -n 1 wzo.out) <(head -n 1 bru.out))
	if [ "$d" != "" ]
	then
		echo zle!!!
		echo "test:"
		cat test.in
		echo "odpowiedz bruta:"
		cat bru.out
		echo "odpowiedz wzorcowki:"
		cat wzo.out
		break
	fi
done
