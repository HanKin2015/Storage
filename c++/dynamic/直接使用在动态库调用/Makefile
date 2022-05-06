#Makefile 
all:main

lib_so1.so: lib_so1.o
		gcc -shared -o $@ $< 

main: main.o lib_so1.so
		gcc -o $@ main.o -l_so1 -L. -Wl,--rpath=.

%.o : %.c
		gcc -fPIC -c $< -o $@

clean:
		rm -rf *.o *.a *.so main
