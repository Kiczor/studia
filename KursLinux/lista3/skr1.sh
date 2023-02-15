#Szymon Kiczak Lista 3

IFS=$'\n'
sciezki=($(find ./music -name *.mp3))
len=${#sciezki[@]}
len=$(($len-1))
for i in $(seq 0 $len)
    do
        utwory[i]=$(mp3info -p "%l (%a): %t" ${sciezki[$i]})
done

PS3="Choose a number to play> "
select tr in "${utwory[@]}"
do
    mplayer ${sciezki[$REPLY]}
done
