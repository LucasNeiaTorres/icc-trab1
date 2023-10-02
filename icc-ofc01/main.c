#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "auxiliar.h"
#include "utils.h"
#include "eliminacaoGauss.h"

double potencia(double base, int expoente)
{
    double resultado = 1;
    for (int i = 0; i < expoente; i++)
    {
        resultado *= base;
    }
    return resultado;
}

double *vetorResultado(double *x, double *fx, int qntPontos, int grauPolinomio)
{
    int i = 0;
    int j = 0;
    int ponto;
    double *vetorResultado = alocaVetor(grauPolinomio);
    double firstValue;
    double secondValue;

    for (i = 0; i < grauPolinomio; i++)
    {
        for (ponto = 0; ponto < qntPontos; ponto++)
        {
            vetorResultado[i] += fx[ponto] * potencia(x[ponto], i);
        }
    }
    return vetorResultado;
}

double **sistemaLinear(double *x, int qntPontos, int grauPolinomio)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int ponto;
    double **matrizSL = alocaMatriz(grauPolinomio);
    double firstValue;
    double secondValue;

    for (i = 0; i < grauPolinomio; i++)
    {
        for (j = 0; j < grauPolinomio; j++)
        {
            for (ponto = 0; ponto < qntPontos; ponto++)
            {

                firstValue = potencia(x[ponto], i);
                secondValue = potencia(x[ponto], j);
                matrizSL[i][j] += firstValue * secondValue;
            }
        }
    }
    return matrizSL;
}

int main()
{
    int qntPontos, i;
    double pl;
    double pn;
    int grauPolinomio;
    char aux;

    if (scanf("%d", &grauPolinomio) != 1)
    {
        perror("Erro ao ler entrada");
        exit(EXIT_FAILURE);
    }

    // Leitura da quantidade de pontos
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
    double **matriz = sistemaLinear(x, qntPontos, grauPolinomio);
    double *vetorRs = vetorResultado(x, fx, qntPontos, grauPolinomio);
    imprimeMatriz(matriz, grauPolinomio);
    imprimeVetorResultado(vetorRs, grauPolinomio);
    eliminacaoGauss(matriz, vetorRs, grauPolinomio);
}