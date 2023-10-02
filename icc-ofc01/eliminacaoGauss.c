#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "eliminacaoGauss.h"

double calculaResiduo(double **A, double *vetorSolucao, double *b, int ordem)
{
    double *residuo = (double *)malloc(ordem * sizeof(double));
    double maxResiduo = 0.0;

    for (int i = 0; i < ordem; i++)
    {
        residuo[i] = 0.0;
        for (int j = 0; j < ordem; j++)
        {
            residuo[i] += A[i][j] * vetorSolucao[j];
        }
        residuo[i] -= b[i];
        residuo[i] = fabs(residuo[i]);
        if (residuo[i] > maxResiduo)
        {
            maxResiduo = residuo[i];
        }
    }

    free(residuo);
    return maxResiduo;
}

int encontraMax(double **A, int i, int ordem)
{
    int max = i;
    for (int j = i + 1; j < ordem; j++)
        if (fabs(A[j][i]) > fabs(A[max][i]))
            max = j;
    return max;
}

void trocaLinha(double **A, double *b, int i, int iPivo, int ordem)
{
    double aux;
    for (int j = 0; j < ordem; j++)
    {
        aux = A[i][j];
        A[i][j] = A[iPivo][j];
        A[iPivo][j] = aux;
    }
    aux = b[i];
    b[i] = b[iPivo];
    b[iPivo] = aux;
}

void retroSubstituicao(double **A, double *b, int ordem)
{
    for (int i = ordem - 1; i >= 0; i--)
    {
        double soma = 0.0;
        for (int j = i + 1; j < ordem; j++)
            soma += A[i][j] * b[j];
        b[i] = (b[i] - soma) / A[i][i];
    }
}

void eliminacaoGauss(double **A, double *b, int ordem)
{
    double **matrizFuncao = alocaMatriz(ordem);
    double *resultadoFuncao = alocaVetor(ordem);
    copiaMatriz(A, matrizFuncao, ordem);
    copiaVetorResultado(b, resultadoFuncao, ordem);

    rtime_t startTime = timestamp();
    printf("1. Eliminação Gauss\n");
    int i, k, j;
    for (i = 0; i < ordem; i++)
    {
        int iPivo = encontraMax(matrizFuncao, i, ordem);
        if (iPivo != i)
            trocaLinha(matrizFuncao, resultadoFuncao, i, iPivo, ordem);

        for (k = i + 1; k < ordem; k++)
        {
            double m = matrizFuncao[k][i] / matrizFuncao[i][i];
            matrizFuncao[k][i] = 0.0;
            for (j = i + 1; j < ordem; j++)
                matrizFuncao[k][j] -= m * matrizFuncao[i][j];
            resultadoFuncao[k] -= m * resultadoFuncao[i];
        }
    }
    retroSubstituicao(matrizFuncao, resultadoFuncao, ordem);
    rtime_t endTime = timestamp();
    double residuo = calculaResiduo(A, resultadoFuncao, b, ordem);

    imprimeVetorResultado(resultadoFuncao, ordem);
    printf("Tempo de execução: %lf\n", (endTime - startTime));
    printf("Residuo: %lf\n\n", residuo);
    desalocaMatriz(matrizFuncao, ordem);
    desalocaVetor(resultadoFuncao);
}