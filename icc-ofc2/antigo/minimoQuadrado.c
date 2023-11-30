/* Autores:
    Lucas Néia Torres - GRR20210570
    Leonardo Becker de Oliveira - GRR20211779
*/
#include <stdio.h>
#include <stdlib.h>
#include "minimoQuadrado.h"

/*
 * calcula e retorna a matriz de coeficientes para um sistema linear de mínimos quadrados.
 * Esta função recebe um vetor de pontos x no formato de intervalo_t, a quantidade de pontos
 * 'qntPontos' e o grau do polinômio 'grauPolinomio' a ser ajustado aos pontos. Ela calcula
 * a matriz de coeficientes para o sistema linear de mínimos quadrados, onde os coeficientes
 * representam as potências cruzadas dos pontos x. A matriz resultante é retornada como uma
 * matriz de intervalo_t.
 */
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
                // Calcula os valores de potência cruzada para o ponto x
                primeiroValor = potenciacao(xintervalo[ponto], i);
                segundoValor = potenciacao(xintervalo[ponto], j);

                // Multiplica os valores de potência cruzada e acumula na matriz
                multIntervalar = multiplicacao(primeiroValor, segundoValor);
                matrizIntervalo[i][j] = soma(matrizIntervalo[i][j], multIntervalar);
            }
        }
    }
    // imprimeMatrizIntervalar(matrizIntervalo, grauPolinomio);
    return matrizIntervalo;
}

/*
 * calcula e retorna o vetor de resultados para um sistema de mínimos quadrados.
 * Esta função recebe um vetor de pontos x no formato de intervalo_t, um vetor de valores
 * de função fxintervalo, a quantidade de pontos 'qntPontos' e o grau do polinômio
 * 'grauPolinomio'. Ela calcula o vetor de resultados para um sistema de mínimos quadrados,
 * onde cada elemento do vetor representa um coeficiente a ser encontrado para ajustar
 * o polinômio aos pontos. O vetor resultante é retornado como um vetor de intervalo_t.
 */
intervalo_t *vetorResultadoIntervalar(intervalo_t *xintervalo, intervalo_t *fxintervalo, int qntPontos, int grauPolinomio)
{
    int i = 0;
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