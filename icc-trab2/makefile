# PROGRAMA
    PROG = perfEG

# Compilador
    CC     = gcc
    CFLAGS = -O3 -mavx -march=native 
    LFLAGS = -lm -llikwid -I/home/lbo21/Faculdade/icc/icc-trab1/likwid-5.2.2/ -L/home/lbo21/Faculdade/icc/icc-trab1/likwid-5.2.2/

# Lista de arquivos para distribuição
DISTFILES = *.c *.h # LEIAME* Makefile
DISTDIR = `basename ${PWD}`

.PHONY: all clean purge dist

$(PROG): $(DISTFILES)
	@echo "Compilando ..."
	@$(CC) $(CFLAGS) -o $(PROG) $(DISTFILES) $(LFLAGS)
	
clean:
	@echo "Limpando sujeira ..."
	@rm -f *~ *.bak

purge:  clean
	@echo "Limpando tudo ..."
	@rm -f $(PROG) *.o core a.out $(DISTDIR) $(DISTDIR).tar

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tar) ..."
	@ln -s . $(DISTDIR)
	@tar -cvf $(DISTDIR).tar $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)