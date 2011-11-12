all:	simcpu
	
simcpu_types.o: simcpu_types.h simcpu_types.c 
	gcc -c -Wall -fprofile-arcs -ftest-coverage simcpu_types.c

main.o:	main.c
	gcc -c -Wall -fprofile-arcs -ftest-coverage main.c

simcpu:	main.o simcpu_types.o
	gcc -o simcpu -Wall -fprofile-arcs -ftest-coverage main.o
	
clean:
	rm -f simcpu *.o *.gcno *.gcda *.gcov
