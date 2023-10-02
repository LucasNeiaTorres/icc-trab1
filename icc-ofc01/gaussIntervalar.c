#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gaussIntervalar.h"

// Arrumar residuo intervalar!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
double calculaResiduoIntervalar(intervalo_t **A, intervalo_t *vetorSolucao, intervalo_t *b, int ordem)
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

int encontraMaxIntervalar(intervalo_t **A, int i, int ordem)
{
    int max = i;
    for (int j = i + 1; j < ordem; j++)
        if (A[j][i].maior > A[max][i].maior)
            max = j;
    return max;
}

void trocaLinhaIntervalar(intervalo_t **A, intervalo_t *b, int i, int iPivo, int ordem)
{
    intervalo_t aux;
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

void retroSubstituicaoIntervalar(intervalo_t **A, intervalo_t *b, int ordem)
{
    for (int i = ordem - 1; i >= 0; i--)
    {
        intervalo_t somatorio;
        somatorio.menor = 0;
        somatorio.maior = 0;
        for (int j = i + 1; j < ordem; j++)
            somatorio = soma(somatorio, multiplicacao(A[i][j], b[j]));
        b[i] = divisao(subtracao(b[i], somatorio), A[i][i]);
    }
}

void eliminacaoGaussIntervalar(intervalo_t **A, intervalo_t *b, int ordem)
{
    printf("\n\n====================>\n");
    intervalo_t **matrizIntevalar = alocaMatrizIntervalar(ordem);
    intervalo_t *resultadoIntervalar = alocaVetorIntervalar(ordem);
    copiaMatrizIntervalar(A, matrizIntevalar, ordem);
    copiaVetorIntervalar(b, resultadoIntervalar, ordem);

    rtime_t startTime = timestamp();
    int i, k, j;
    for (i = 0; i < ordem; i++)
    {
        int iPivo = encontraMaxIntervalar(matrizIntevalar, i, ordem);
        if (iPivo != i)
            trocaLinhaIntervalar(matrizIntevalar, resultadoIntervalar, i, iPivo, ordem);
        for (j = i + 1; j < ordem; j++)
        {
            intervalo_t m = divisao(matrizIntevalar[j][i], matrizIntevalar[i][i]);
            matrizIntevalar[j][i].menor = 0.0;
            matrizIntevalar[j][i].maior = 0.0;
            for (k = i + 1; k < ordem; k++)
            {
                matrizIntevalar[j][k] = subtracao(matrizIntevalar[j][k], multiplicacao(m, matrizIntevalar[i][k]));
            }
            resultadoIntervalar[j] = subtracao(resultadoIntervalar[j], multiplicacao(m, resultadoIntervalar[i]));
        }
    }
    retroSubstituicaoIntervalar(matrizIntevalar, resultadoIntervalar, ordem);
    imprimeMatrizIntervalar(matrizIntevalar, ordem);
    imprimeVetorIntervalar(resultadoIntervalar, ordem);
    rtime_t endTime = timestamp();
    printf("\n\n====================\n");
    // retroSubstituicao(matrizFuncao, resultadoFuncao, ordem);
    // rtime_t endTime = timestamp();
    // double residuo = calculaResiduo(A, resultadoFuncao, b, ordem);

    // imprimeVetorResultado(resultadoFuncao, ordem);
    // printf("Tempo de execução: %lf\n", (endTime - startTime));
    // printf("Residuo: %lf\n\n", residuo);
    // desalocaMatriz(matrizFuncao, ordem);
    // desalocaVetor(resultadoFuncao);
}