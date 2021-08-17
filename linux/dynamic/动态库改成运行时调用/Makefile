#Makefile 
all:main

lib_so1.so: lib_so1.o
		gcc -shared -o $@ $< 

main: main.o lib_so1.so
		gcc -o $@ main.o -ldl

%.o : %.c
		gcc -fPIC -c $< -o $@

clean:
		rm -rf *.o *.a *.so main
