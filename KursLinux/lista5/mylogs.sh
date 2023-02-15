#!/bin/bash

mkfifo mylog

while true
do
    read a < mylog
    echo $(date +'%Y-%m-%d %H:%M:%S') $a
done