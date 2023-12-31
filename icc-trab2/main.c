#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "likwid.h"

void copiaMatriz(double **A, double **B, int ordem)
{
    for (int i = 0; i < ordem; i++)
    {
        for (int j = 0; j < ordem; j++)
        {
            B[i][j] = A[i][j];
        }
    }
}

void copiaVetorResultado(double *b, double *bBackup, int ordem)
{
    for (int i = 0; i < ordem; i++)
    {
        bBackup[i] = b[i];
    }
}

void imprimeMatriz(double **A, double *b, int ordem)
{
    for (int i = 0; i < ordem; i++)
    {
        printf("| ");
        for (int j = 0; j < ordem; j++)
        {
            printf("%lf ", A[i][j]);
        }
        printf("| | %lf |\n", b[i]);
    }
}

void imprimeVetorResultado(double *b, int ordem)
{
    for (int i = 0; i < ordem; i++)
    {
        printf("x%d= %lf \n", (i + 1), b[i]);
    }
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

double **alocaMatriz(int ordem)
{
    double **matriz;
    matriz = (double **)calloc(ordem, sizeof(double *));
    for (int i = 0; i < ordem; i++)
        matriz[i] = (double *)calloc(ordem, sizeof(double));
    return matriz;
}

double *alocaVetor(int ordem)
{
    double *vetor;
    vetor = (double *)calloc(ordem, sizeof(double));
    return vetor;
}

void desalocaMatriz(double **matriz, int ordem)
{
    for (int i = 0; i < ordem; i++)
        free(matriz[i]);
    free(matriz);
}

void desalocaVetor(double *vetor)
{
    free(vetor);
}

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

void eliminacaoGauss(double **A, double *b, int ordem)
{

    double **matrizFuncao = alocaMatriz(ordem);
    double *resultadoFuncao = alocaVetor(ordem);
    copiaMatriz(A, matrizFuncao, ordem);
    copiaVetorResultado(b, resultadoFuncao, ordem);

    double startTime = timestamp();
    printf("1. Eliminação Gauss\n");
    LIKWID_MARKER_START("EliminacaoGauss");
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
    LIKWID_MARKER_STOP("EliminacaoGauss");
    double endTime = timestamp();
    double residuo = calculaResiduo(A, resultadoFuncao, b, ordem);

    imprimeVetorResultado(resultadoFuncao, ordem);
    printf("Tempo de execução: %lf\n", (endTime - startTime));
    printf("Residuo: %lf\n\n", residuo);
    desalocaMatriz(matrizFuncao, ordem);
    desalocaVetor(resultadoFuncao);
}

void eliminacaoGaussSemMultiplicador(double **A, double *b, int ordem)
{
    double **matrizFuncao = alocaMatriz(ordem);
    double *resultadoFuncao = alocaVetor(ordem);
    copiaMatriz(A, matrizFuncao, ordem);
    copiaVetorResultado(b, resultadoFuncao, ordem);

    double startTime = timestamp();
    printf("2. Eliminação Gauss sem multplicador\n");
    LIKWID_MARKER_START("EliminacaoGaussSemMultiplicador");
    for (int i = 0; i < ordem; i++)
    {
        int iPivo = encontraMax(matrizFuncao, i, ordem);
        if (iPivo != i)
            trocaLinha(matrizFuncao, resultadoFuncao, i, iPivo, ordem);
        for (int k = i + 1; k < ordem; k++)
        {
            for (int j = i + 1; j < ordem; j++)
                matrizFuncao[k][j] = (matrizFuncao[k][j] * matrizFuncao[i][i]) - (matrizFuncao[i][j] * matrizFuncao[k][i]);
            resultadoFuncao[k] = (resultadoFuncao[k] * matrizFuncao[i][i]) - (resultadoFuncao[i] * matrizFuncao[k][i]);
        }
    }

    retroSubstituicao(matrizFuncao, resultadoFuncao, ordem);
    LIKWID_MARKER_STOP("EliminacaoGaussSemMultiplicador");
    double endTime = timestamp();
    double residuo = calculaResiduo(A, resultadoFuncao, b, ordem);

    imprimeVetorResultado(resultadoFuncao, ordem);
    printf("Tempo de execução: %lf\n", (endTime - startTime));
    printf("Residuo: %lf\n\n", residuo);
    desalocaMatriz(matrizFuncao, ordem);
    desalocaVetor(resultadoFuncao);
}

void eliminacaoGaussAlternativa(double **A, double *b, int ordem)
{
    double **matrizFuncao = alocaMatriz(ordem);
    double *resultadoFuncao = alocaVetor(ordem);
    copiaMatriz(A, matrizFuncao, ordem);
    copiaVetorResultado(b, resultadoFuncao, ordem);

    double startTime = timestamp();
    printf("3. Eliminação Gauss Alternativa\n");
    LIKWID_MARKER_START("EliminacaoGaussAlternativa");
    for (int i = 0; i < ordem; i++)
    {
        double pivo = matrizFuncao[i][i];
        for (int j = 0; j < ordem; j++)
            matrizFuncao[i][j] /= pivo;
        resultadoFuncao[i] /= pivo;

        for (int k = i + 1; k < ordem; k++)
        {
            double m = matrizFuncao[k][i];
            matrizFuncao[k][i] = 0.0;
            for (int j = i + 1; j < ordem; j++)
                matrizFuncao[k][j] -= m * matrizFuncao[i][j];
            resultadoFuncao[k] -= m * resultadoFuncao[i];
        }
    }

    retroSubstituicao(matrizFuncao, resultadoFuncao, ordem);
    LIKWID_MARKER_STOP("EliminacaoGaussAlternativa");
    double endTime = timestamp();
    double residuo = calculaResiduo(A, resultadoFuncao, b, ordem);

    imprimeVetorResultado(resultadoFuncao, ordem);
    printf("Tempo de execução: %lf\n", (endTime - startTime));
    printf("Residuo: %lf\n\n", residuo);
    desalocaMatriz(matrizFuncao, ordem);
    desalocaVetor(resultadoFuncao);
}

int main()
{

    int ordem, i, j;
    double teste;

    if (scanf("%d", &ordem) != 1)
    {
        perror("Erro ao ler entrada");
        exit(EXIT_FAILURE);
    }
    double **matrizEntrada = alocaMatriz(ordem);
    double *resultadoEntrada = alocaVetor(ordem);

    // Leitura da entrada
    for (i = 0; i < ordem; i++)
        for (j = 0; j < (ordem + 1); j++)
            if (j == ordem)
                teste = scanf("%lf", &resultadoEntrada[i]);
            else
                teste = scanf("%lf", &matrizEntrada[i][j]);

    LIKWID_MARKER_INIT;
    eliminacaoGauss(matrizEntrada, resultadoEntrada, ordem);
    eliminacaoGaussSemMultiplicador(matrizEntrada, resultadoEntrada, ordem);
    eliminacaoGaussAlternativa(matrizEntrada, resultadoEntrada, ordem);
    LIKWID_MARKER_CLOSE;
    desalocaMatriz(matrizEntrada, ordem);
    desalocaVetor(resultadoEntrada);

    return 0;
}