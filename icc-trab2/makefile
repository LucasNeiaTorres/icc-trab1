parametrosCompilacao=-Wall -std=c99 -lm -D_DEFAULT_SOURCE -O3 -mavx -march=native #-Wshadow
arquivos=main.o
all: main

main: $(arquivos)
	gcc -o main $(arquivos) $(parametrosCompilacao)

.o: .c
	gcc -c *.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch main 

purge: clean
	-rm -f main