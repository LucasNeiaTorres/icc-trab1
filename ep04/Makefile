# PROGRAMA
    PROG = matmult

# Compilador
    CC     = gcc
    CFLAGS = -O3 -mavx -march=native 
    LFLAGS = -lm -I/home/soft/likwid/include -L/home/soft/likwid/lib -DLIKWID_PERFMON -llikwid

# Lista de arquivos para distribuição
DISTFILES = *.c *.h # LEIAME* Makefile
DISTDIR = `basename ${PWD}`

.PHONY: all clean purge dist

$(PROG): $(DISTFILES)
	@$(CC) $(CFLAGS) -o $(PROG) $(DISTFILES) $(LFLAGS)
	
clean:
	@rm -f *~ *.bak

purge:  clean
	@rm -f $(PROG) *.o core a.out $(DISTDIR) $(DISTDIR).tar

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tar) ..."
	@ln -s . $(DISTDIR)
	@tar -cvf $(DISTDIR).tar $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)