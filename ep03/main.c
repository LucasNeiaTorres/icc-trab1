#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "interpolacao.h"
#include "auxiliar.h"
#include "likwid.h"

int main(int argc, char *argv[])
{

    int qntPontos, i;
    double xe = atof(argv[1]);
    double pl;
    double pn;
    char aux;

    if (scanf("%d", &qntPontos) != 1)
    {
        perror("Erro ao ler entrada");
        exit(EXIT_FAILURE);
    }

    double *x = alocaVetor(qntPontos);
    double *fx = alocaVetor(qntPontos);

    // Leitura da entrada
    for (i = 0; i < qntPontos; i++)
    {
        aux = scanf("%lf", &x[i]);
        aux = scanf("%lf", &fx[i]);
    }

    // Verifica se xe está dentro do intervalo
    if (xe < x[0] || xe > x[qntPontos - 1])
    {
        fprintf(stderr, "Valor de xe fora do intervalo.\n");
        exit(EXIT_FAILURE);
    }

    LIKWID_MARKER_INIT;
    rtime_t startTimePL = timestamp();
    LIKWID_MARKER_START("InterpolaçãoNewton");
    pn = interpolacaoNewton(xe, x, fx, qntPontos);
    LIKWID_MARKER_STOP("InterpolaçãoNewton");
    rtime_t endTimePL = timestamp();

    rtime_t startTimePN = timestamp();
    LIKWID_MARKER_START("InterpolaçãoLagrange");
    pl = interpolacaoLagrange(xe, x, fx, qntPontos);
    LIKWID_MARKER_STOP("InterpolaçãoLagrange");
    rtime_t endTimePN = timestamp();
    LIKWID_MARKER_CLOSE;

    printf("%lf\n", pl);
    printf("%lf\n", pn);
    printf("%lf\n", endTimePL - startTimePL);
    printf("%lf\n", endTimePN - startTimePN);

    desalocaVetor(x);
    desalocaVetor(fx);
    return 0;
}