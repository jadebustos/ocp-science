CC=gcc
FLAGS=-O2 -Wall

mytime:
	$(CC) $(FLAGS) -c mytime.c

chudnovsky-gmp:
	$(CC) $(FLAGS) -o chudnovsky-gmp.bin chudnovsky-gmp.c -lgmp

chudnovsky-gmp-omp: mytime
	$(CC) $(FLAGS) -o chudnovsky-gmp-omp.bin chudnovsky-gmp-omp.c mytime.o -lgmp -fopenmp
	$(CC) $(FLAGS) pi2txt.c -o pi2txt.bin

mid:
	$(CC) $(FLAGS) pi-mid-point-rule.c -o pi-mid-point-rule.bin -fopenmp

all:
	make chudnovsky-gmp
	make chudnovsky-gmp-omp
	make mid

clean:
	rm -f *.o *.bin *~
