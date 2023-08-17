parametrosCompilacao=-Wall -std=c99 -lm -D_DEFAULT_SOURCE #-Wshadow
arquivos=analiseIntervalar.o operadores.o
all: analise

analise: $(arquivos)
	gcc -o analise $(arquivos) $(parametrosCompilacao)

.o: .c
	gcc -c *.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch analise 

purge: clean
	-rm -f analise