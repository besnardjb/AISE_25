# Explication

gcc -shared -fpic ./lib.c -o libadd.so

gcc ./main.c -ladd 


# Runtime

LD_LIBARY_PATH=$PWD:$LD_LIBARY_PATH
./a.out

# Rpath

gcc ./main.c -ladd -Wl,-rpath=$PWD