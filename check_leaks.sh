#!/bin/sh

if [[ $# -eq 0 ]]
    then
    echo "enter program_name as argument"
fi

while true; do
    if ! pgrep -x $1 > /dev/null
        then
            echo "$1 stopped"
			sleep 1
			clear
		continue
    fi
    leaks $1 | tail -5
    sleep 1
	clear
done
