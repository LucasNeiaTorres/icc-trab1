#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gaussIntervalar.h"

void eliminacaoGaussIntervalar(intervalo_t **A, intervalo_t *b, int ordem)
{
    intervalo_t **matrizIntevalar = alocaMatrizIntervalar(ordem);
    intervalo_t *resultadoIntervalar = alocaVetorIntervalar(ordem);
    copiaMatrizIntervalar(A, matrizIntevalar, ordem);
    copiaVetorIntervalar(b, resultadoIntervalar, ordem);

    rtime_t startTime = timestamp();

    int i, k, j;
    for (i = 0; i < ordem; i++)
    {
    }
    // printf("1. Eliminação Gauss\n");
    // int i, k, j;
    // for (i = 0; i < ordem; i++)
    // {
    //     int iPivo = encontraMax(matrizFuncao, i, ordem);
    //     if (iPivo != i)
    //         trocaLinha(matrizFuncao, resultadoFuncao, i, iPivo, ordem);

    //     for (k = i + 1; k < ordem; k++)
    //     {
    //         double m = matrizFuncao[k][i] / matrizFuncao[i][i];
    //         matrizFuncao[k][i] = 0.0;
    //         for (j = i + 1; j < ordem; j++)
    //             matrizFuncao[k][j] -= m * matrizFuncao[i][j];
    //         resultadoFuncao[k] -= m * resultadoFuncao[i];
    //     }
    // }
    // retroSubstituicao(matrizFuncao, resultadoFuncao, ordem);
    // rtime_t endTime = timestamp();
    // double residuo = calculaResiduo(A, resultadoFuncao, b, ordem);

    // imprimeVetorResultado(resultadoFuncao, ordem);
    // printf("Tempo de execução: %lf\n", (endTime - startTime));
    // printf("Residuo: %lf\n\n", residuo);
    // desalocaMatriz(matrizFuncao, ordem);
    // desalocaVetor(resultadoFuncao);
}