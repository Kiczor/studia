#Szymon Kiczak Lista 3

while true
do
    printf "Available entropy: $(cat /proc/sys/kernel/random/entropy_avail)/$(cat /proc/sys/kernel/random/poolsize)\r"
    sleep 1
    if read -n 1 cos
    then
        break
    fi
done