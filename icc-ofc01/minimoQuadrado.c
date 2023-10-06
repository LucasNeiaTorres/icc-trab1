#include <stdio.h>
#include <stdlib.h>
#include "minimoQuadrado.h"

intervalo_t **sistemaLinearIntervalar(intervalo_t *xintervalo, int qntPontos, int grauPolinomio)
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
    // imprimeMatrizIntervalar(matrizIntervalo, grauPolinomio);
    return matrizIntervalo;
}

intervalo_t *vetorResultadoIntervalar(intervalo_t *xintervalo, intervalo_t *fxintervalo, int qntPontos, int grauPolinomio)
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
    // imprimeVetorIntervalar(vetorResultado, grauPolinomio);
    return vetorResultado;
}