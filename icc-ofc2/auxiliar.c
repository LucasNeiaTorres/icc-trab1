/* Autores:
    Lucas Néia Torres - GRR20210570
    Leonardo Becker de Oliveira - GRR20211779
*/
#include <stdio.h>
#include <stdlib.h>
#include "auxiliar.h"

// atribui valores da matriz A para a matriz B
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

// atribui valores da matriz A para a matriz B, sendo A e B matrizes com valores intervalares
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

// atribui valores do vetor b para bBackup
void copiaVetorResultado(double *b, double *bBackup, int qntPontos)
{
    for (int i = 0; i < qntPontos; i++)
    {
        bBackup[i] = b[i];
    }
}

// atribui valores do vetor b para bBackup, sendo A e B vetores com valores intervalares
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

// aloca dinamicamente matriz intervalar de tamanho qntPontos x qntPontos
intervalo_t **alocaMatrizIntervalar(int grauPolinomio)
{
    intervalo_t **matriz;
    matriz = (intervalo_t **)calloc(grauPolinomio, sizeof(intervalo_t *));
    for (int i = 0; i < grauPolinomio; i++)
        matriz[i] = (intervalo_t *)calloc(grauPolinomio, sizeof(intervalo_t));
    return matriz;
}

// aloca dinamicamente vetor intervalar de tamanho qntPontos 
intervalo_t *alocaVetorIntervalar(int grauPolinomio)
{
    intervalo_t *vetor;
    vetor = (intervalo_t *)calloc(grauPolinomio, sizeof(intervalo_t));
    return vetor;
}

// desaloca dinamicamente matriz intervalar de tamanho qntPontos x qntPontos
void desalocaMatrizIntervalar(intervalo_t **matriz, int grauPolinomio)
{
    for (int i = 0; i < grauPolinomio; i++)
        free(matriz[i]);
    free(matriz);
}

// desaloca dinamicamente vetor intervalar de tamanho qntPontos 
void desalocaVetorIntervalar(intervalo_t *vetor)
{
    free(vetor);
}

// aloca dinamicamente matriz de tamanho qntPontos x qntPontos
double **alocaMatriz(int qntPontos)
{
    double **matriz;
    matriz = (double **)calloc(qntPontos, sizeof(double *));
    for (int i = 0; i < qntPontos; i++)
        matriz[i] = (double *)calloc(qntPontos, sizeof(double));
    return matriz;
}

// aloca dinamicamente vetor de tamanho qntPontos 
double *alocaVetor(int qntPontos)
{
    double *vetor;
    vetor = (double *)calloc(qntPontos, sizeof(double));
    return vetor;
}

// desaloca dinamicamente matriz de tamanho qntPontos x qntPontos
void desalocaMatriz(double **matriz, int qntPontos)
{
    for (int i = 0; i < qntPontos; i++)
        free(matriz[i]);
    free(matriz);
}

// desaloca dinamicamente vetor de tamanho qntPontos 
void desalocaVetor(double *vetor)
{
    free(vetor);
}


void imprimeMMIntervalar(intervalo_t *mmIntervalo, int grauPolinomio)
{
    for (int i = 0; i < grauPolinomio; i++)
    {
        for (int j = 0; j < grauPolinomio; j++)
        {
            printf("[%1.8e, %1.8e] ", mmIntervalo[i * grauPolinomio + j].menor, mmIntervalo[i * grauPolinomio + j].maior);
        }
        printf("\n");
    }
}