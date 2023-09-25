#include <stdio.h>
#include <stdlib.h>
#include "auxiliar.h"

void copiaMatriz(double **A, double **B, int qntPontos)
{
    for (int i = 0; i < qntPontos; i++)
    {
        for (int j = 0; j < qntPontos; j++)
        {
            B[i][j] = A[i][j];
        }
    }
}

void copiaVetorResultado(double *b, double *bBackup, int qntPontos)
{
    for (int i = 0; i < qntPontos; i++)
    {
        bBackup[i] = b[i];
    }
}

void imprimeMatriz(double **A, int qntPontos)
{
    for (int i = 0; i < qntPontos; i++)
    {
        for (int j = 0; j < qntPontos; j++)
        {
            printf("%lf ", A[i][j]);
        }
        printf("\n");
    }
}

void imprimeVetorResultado(double *b, int qntPontos)
{
    for (int i = 0; i < qntPontos; i++)
    {
        printf("x%d= %lf \n", (i + 1), b[i]);
    }
}

double **alocaMatriz(int qntPontos)
{
    double **matriz;
    matriz = (double **)calloc(qntPontos, sizeof(double *));
    for (int i = 0; i < qntPontos; i++)
        matriz[i] = (double *)calloc(qntPontos, sizeof(double));
    return matriz;
}

double *alocaVetor(int qntPontos)
{
    double *vetor;
    vetor = (double *)calloc(qntPontos, sizeof(double));
    return vetor;
}

void desalocaMatriz(double **matriz, int qntPontos)
{
    for (int i = 0; i < qntPontos; i++)
        free(matriz[i]);
    free(matriz);
}

void desalocaVetor(double *vetor)
{
    free(vetor);
}