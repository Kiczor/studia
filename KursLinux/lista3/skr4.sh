#Szymon Kiczak Lista 3

max=1000
primes[0]=2
i=1
n=3
while [ $n -le $max ]
do
    j=0
    zle=0
    while [ $j -lt $i ] && [ "$((${primes[$j]}" * "${primes[$j]}))" -le "$n" ]
    do
        if [ $(("$n" % "${primes[$j]}")) -eq 0 ]
        then
            zle=1
            break
        fi
        j=$(($j+1))
    done
    if [ $zle = 0 ]
    then
        primes[i]=$n
        i=$(($i+1))
    fi
    n=$(($n+1))
done

for p in ${primes[@]}
do
    echo $p
done