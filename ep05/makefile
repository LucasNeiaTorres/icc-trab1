parametrosCompilacao=-Wall -std=c99 -lm -D_DEFAULT_SOURCE #-Wshadow
arquivos=monteCarlo.o utils.o
all: monteCarlo

monteCarlo: $(arquivos)
	gcc -o monteCarlo $(arquivos) $(parametrosCompilacao)

.o: .c
	gcc -c *.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch monteCarlo 

purge: clean
	-rm -f monteCarlo