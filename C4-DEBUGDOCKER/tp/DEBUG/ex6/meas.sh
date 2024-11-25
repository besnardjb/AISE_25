for i in $(seq 1 1 50)
do
	echo "ITER $i"
	/bin/time -a -f "$i %e" -o ./time.dat ./a.out $i
done
