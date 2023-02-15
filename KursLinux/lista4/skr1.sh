#Szymon Kiczak Lista 4 zadanie 1

IFS=$'\n'
sciezki=($(find ./music -name *.mp3))
len=${#sciezki[@]}
len=$(($len-1))
for i in $(seq 0 $len)
do
    utwory[i]=$(mp3info -p "%l (%a): %t" ${sciezki[$i]})
done

for i in $(seq 0 $len)
do
    opcje+=($i "${utwory[$i]}")
done

cmd=(dialog --keep-tite --menu "Choose track:" 22 76 16)
choices=$("${cmd[@]}" "${opcje[@]}" 2>&1 >/dev/tty)

for choice in $choices
do
    mplayer ${sciezki[$choice]}
done
