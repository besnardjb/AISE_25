#!/bin/sh

for i in $(seq 1 1 1000)
do
	echo "TOTO=$i"
done

# Draw a cat!
echo "/_/\
( o.o )
 > ^ <"

# Bonus: animate the cat's eyes!
while true; do
    echo -ne "\r/_/\ \r( o.O )\r> ^ <"
    sleep 0.5
    echo -ne "\r/_/\ \r( ^ - ^ )\r> ^ <"
    sleep 0.5
done

# Don't forget to stop the animation with Ctrl+C!
