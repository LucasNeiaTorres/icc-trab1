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

void copiaMatrizIntervalar(intervalo_t **A, intervalo_t **B, int qntPontos)
{
    for (int i = 0; i < qntPontos; i++)
    {
        for (int j = 0; j < qntPontos; j++)
        {
            B[i][j].menor = A[i][j].menor;
            B[i][j].maior = A[i][j].maior;
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

void copiaVetorIntervalar(intervalo_t *b, intervalo_t *bBackup, int qntPontos)
{
    for (int i = 0; i < qntPontos; i++)
    {
        bBackup[i].menor = b[i].menor;
        bBackup[i].maior = b[i].maior;
    }
}

void imprimeMatriz(double **A, int qntPontos)
{
    for (int i = 0; i < qntPontos; i++)
    {
        for (int j = 0; j < qntPontos; j++)
        {
            printf("%1.8e ", A[i][j]);
        }
        printf("\n");
    }
}

void imprimeVetorResultado(double *b, int qntPontos)
{
    for (int i = 0; i < qntPontos; i++)
    {
        printf("alpha%d= %lf \n", (i + 1), b[i]);
    }
}

void imprimeMatrizIntervalar(intervalo_t **matriz, int grauPolinomio)
{
    for (int i = 0; i < grauPolinomio; i++)
    {
        for (int j = 0; j < grauPolinomio; j++)
        {
            printf("[%1.8e, %1.8e] ", matriz[i][j].menor, matriz[i][j].maior);
        }
        printf("\n");
    }
}

void imprimeVetorIntervalar(intervalo_t *vetor, int grauPolinomio)
{
    for (int i = 0; i < grauPolinomio; i++)
    {
        printf("[%1.8e, %1.8e] ", vetor[i].menor, vetor[i].maior);
    }
    printf("\n");
}

intervalo_t **alocaMatrizIntervalar(int grauPolinomio)
{
    intervalo_t **matriz;
    matriz = (intervalo_t **)calloc(grauPolinomio, sizeof(intervalo_t *));
    for (int i = 0; i < grauPolinomio; i++)
        matriz[i] = (intervalo_t *)calloc(grauPolinomio, sizeof(intervalo_t));
    return matriz;
}

intervalo_t *alocaVetorIntervalar(int grauPolinomio)
{
    intervalo_t *vetor;
    vetor = (intervalo_t *)calloc(grauPolinomio, sizeof(intervalo_t));
    return vetor;
}

void desalocaMatrizIntervalar(intervalo_t **matriz, int grauPolinomio)
{
    for (int i = 0; i < grauPolinomio; i++)
        free(matriz[i]);
    free(matriz);
}

void desalocaVetorIntervalar(intervalo_t *vetor)
{
    free(vetor);
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