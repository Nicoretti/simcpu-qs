all:	simcpu
	
main.o:	main.c
	gcc -c -Wall -fprofile-arcs -ftest-coverage main.c

simcpu:	main.o 
	gcc -o simcpu -Wall -fprofile-arcs -ftest-coverage main.o
	
clean:
	rm -f simcpu *.o *.gcno *.gcda *.gcov
