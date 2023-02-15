#!/bin/bash

trap "logger "sygnal SIGUSR1"" SIGUSR1
trap "" SIGHUP

while true
do
    echo "komunikat"
    logger "komunikat"
    sleep 10 &
    wait $!
done