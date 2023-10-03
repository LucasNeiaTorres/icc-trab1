#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "auxiliar.h"
#include "utils.h"
#include "eliminacaoGauss.h"
#include "operacoes.h"
#include "gaussIntervalar.h"
#include "likwid.h"

double potencia(double base, int expoente)
{
    double resultado = 1;
    for (int i = 0; i < expoente; i++)
    {
        resultado *= base;
    }
    return resultado;
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
    imprimeMatriz(matrizSL, grauPolinomio);
    return matrizSL;
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

intervalo_t **newSL(intervalo_t *xintervalo, int qntPontos, int grauPolinomio)
{
    int i = 0;
    int j = 0;
    int ponto = 0;
    intervalo_t primeiroValor;
    intervalo_t segundoValor;
    intervalo_t multIntervalar;
    intervalo_t **matrizIntervalo = alocaMatrizIntervalar(grauPolinomio);
    for (i = 0; i < grauPolinomio; i++)
    {
        for (j = 0; j < grauPolinomio; j++)
        {
            for (ponto = 0; ponto < qntPontos; ponto++)
            {
                primeiroValor = potenciacao(xintervalo[ponto], i);
                segundoValor = potenciacao(xintervalo[ponto], j);
                multIntervalar = multiplicacao(primeiroValor, segundoValor);
                matrizIntervalo[i][j] = soma(matrizIntervalo[i][j], multIntervalar);
            }
        }
    }
    imprimeMatrizIntervalar(matrizIntervalo, grauPolinomio);
    return matrizIntervalo;
}

intervalo_t *vetorResultadoIntervalo(intervalo_t *xintervalo, intervalo_t *fxintervalo, int qntPontos, int grauPolinomio)
{
    int i = 0;
    int j = 0;
    int ponto;
    intervalo_t *vetorResultado = alocaVetorIntervalar(grauPolinomio);
    intervalo_t firstValue;
    intervalo_t multIntervalar;

    for (i = 0; i < grauPolinomio; i++)
    {
        for (ponto = 0; ponto < qntPontos; ponto++)
        {
            firstValue = potenciacao(xintervalo[ponto], i);
            multIntervalar = multiplicacao(firstValue, fxintervalo[ponto]);
            vetorResultado[i] = soma(vetorResultado[i], multIntervalar);
        }
    }
    imprimeVetorIntervalar(vetorResultado, grauPolinomio);
    return vetorResultado;
}

int main()
{
    int qntPontos, i;
    double pl;
    double pn;
    int grauPolinomio;
    char aux;
    double entrada;

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

    intervalo_t *xintervalo = alocaVetorIntervalar(qntPontos);
    intervalo_t *fxintervalo = alocaVetorIntervalar(qntPontos);

    // Leitura da entrada
    for (i = 0; i < qntPontos; i++)
    {
        aux = scanf("%lf", &entrada);
        x[i] = entrada;
        xintervalo[i] = calculaIntervalo(entrada);
        aux = scanf("%lf", &entrada);
        fx[i] = entrada;
        fxintervalo[i] = calculaIntervalo(entrada);
    }

    printf("GAUSS INTERVALAR\n");
    LIKWID_MARKER_INIT;

    LIKWID_MARKER_START("EliminacaoGaussIntervalar");
    intervalo_t **matrizIntervalo = newSL(xintervalo, qntPontos, grauPolinomio);
    intervalo_t *vetorIntervalo = vetorResultadoIntervalo(xintervalo, fxintervalo, qntPontos, grauPolinomio);
    eliminacaoGaussIntervalar(matrizIntervalo, vetorIntervalo, grauPolinomio);
    LIKWID_MARKER_STOP("EliminacaoGaussIntervalar");


    // printf("GAUSS\n");
    // double **matriz = sistemaLinear(x, qntPontos, grauPolinomio);
    // double *vetorRs = vetorResultado(x, fx, qntPontos, grauPolinomio);
    // eliminacaoGauss(matriz, vetorRs, grauPolinomio);

    LIKWID_MARKER_CLOSE;
    // desalocaMatriz(matriz, grauPolinomio);
    // desalocaVetor(vetorRs);
    // desalocaVetor(x);
    // desalocaVetor(fx);
}