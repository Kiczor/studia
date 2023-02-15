#Szymon Kiczak Lista 3

max=$1

function przedzial {
    for i in $(seq 2 $max)
    do
        echo $i
    done
}

function filter {
    read d

    if [ -z "$d" ]
    then
        return
    fi

    echo $d

    while read x
    do
        if [ $(("$x" % "d")) -ne 0 ]
        then
            echo $x
        fi
    done | filter &
}

przedzial | filter | cat
