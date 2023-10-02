#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "auxiliar.h"
#include "utils.h"
#include "eliminacaoGauss.h"
#include "operacoes.h"

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

intervalo_t **alocaMatrizIntervalo(int grauPolinomio)
{
    intervalo_t **matriz;
    matriz = (intervalo_t **)calloc(grauPolinomio, sizeof(intervalo_t *));
    for (int i = 0; i < grauPolinomio; i++)
        matriz[i] = (intervalo_t *)calloc(grauPolinomio, sizeof(intervalo_t));
    return matriz;
}

intervalo_t *alocaVetorIntervalo(int grauPolinomio)
{
    intervalo_t *vetor;
    vetor = (intervalo_t *)calloc(grauPolinomio, sizeof(intervalo_t));
    return vetor;
}

void imprimeMatrizIntervalo(intervalo_t **matriz, int grauPolinomio)
{
    for (int i = 0; i < grauPolinomio; i++)
    {
        for (int j = 0; j < grauPolinomio; j++)
        {
            printf("[%lf, %lf] ", matriz[i][j].menor, matriz[i][j].maior);
        }
        printf("\n");
    }
}

void imprimeVetorIntervalo(intervalo_t *vetor, int grauPolinomio)
{
    for (int i = 0; i < grauPolinomio; i++)
    {
        printf("[%lf, %lf] ", vetor[i].menor, vetor[i].maior);
    }
    printf("\n");
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

intervalo_t **newSL(intervalo_t *xintervalo, int qntPontos, int grauPolinomio)
{
    int i = 0;
    int j = 0;
    int ponto = 0;
    intervalo_t primeiroValor;
    intervalo_t segundoValor;
    intervalo_t multIntervalar;
    intervalo_t **matrizIntervalo = alocaMatrizIntervalo(grauPolinomio);
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
    imprimeMatrizIntervalo(matrizIntervalo, grauPolinomio);
    return matrizIntervalo;
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

    intervalo_t *xintervalo = alocaVetorIntervalo(qntPontos);
    intervalo_t *fxintervalo = alocaVetorIntervalo(qntPontos);

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
    imprimeVetorIntervalo(xintervalo, qntPontos);
    intervalo_t **matrizIntervalo = newSL(xintervalo, qntPontos, grauPolinomio);

    double **matriz = sistemaLinear(x, qntPontos, grauPolinomio);
    double *vetorRs = vetorResultado(x, fx, qntPontos, grauPolinomio);
    imprimeMatriz(matriz, grauPolinomio);
    imprimeVetorResultado(vetorRs, grauPolinomio);
    eliminacaoGauss(matriz, vetorRs, grauPolinomio);

    desalocaMatriz(matriz, grauPolinomio);
    desalocaVetor(vetorRs);
    desalocaVetor(x);
    desalocaVetor(fx);
}