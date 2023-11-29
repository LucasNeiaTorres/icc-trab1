/* Autores:
    Lucas Néia Torres - GRR20210570
    Leonardo Becker de Oliveira - GRR20211779
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minimoQuadrado.h"

/*
 * calcula e retorna a matriz de coeficientes para um sistema linear de mínimos quadrados.
 * Esta função recebe um vetor de pontos x no formato de intervalo_t, a quantidade de pontos
 * 'qntPontos' e o grau do polinômio 'grauPolinomio' a ser ajustado aos pontos. Ela calcula
 * a matriz de coeficientes para o sistema linear de mínimos quadrados, onde os coeficientes
 * representam as potências cruzadas dos pontos x. A matriz resultante é retornada como uma
 * matriz de intervalo_t.
 */

intervalo_t *sistemaLinearIntervalar(intervalo_t *xintervalo, int qntPontos, int grauPolinomio)
{
    int i = 0;
    int j = 0;
    int ponto = 0;
    int indice = 0;
    intervalo_t primeiroValor;
    intervalo_t segundoValor;
    intervalo_t multIntervalar;
    intervalo_t *mmIntervalo = alocaVetorIntervalar(grauPolinomio * grauPolinomio);

    // Mover o laço que itera os pontos para o mais externo, a fim de reduzir miss caching
    for (ponto = 0; ponto < qntPontos; ponto++)
    {
        // Preenche a primeira linha
        for (i = 0; i < grauPolinomio-1; i++)
        {
            primeiroValor = potenciacao(xintervalo[ponto], i);
            mmIntervalo[i] = soma(mmIntervalo[i], primeiroValor);
        }

        segundoValor = potenciacao(xintervalo[ponto], grauPolinomio-1); // Calculado fora do laço para reduzir quantidade de operação ponto flutuante
        
        // Preenche a ultima coluna
        for (j = 0; j < grauPolinomio; j++)
        {
            primeiroValor = potenciacao(xintervalo[ponto], j);
            multIntervalar = multiplicacao(primeiroValor, segundoValor);
            indice = grauPolinomio * j + grauPolinomio - 1;
            mmIntervalo[indice] = soma(mmIntervalo[indice], multIntervalar);
        }

        // Preenche o restante da matriz sem precisar refazer os cálculos de ponto fluante
        for(i = 1; i < grauPolinomio; i++){
            for(j = 0; j < grauPolinomio-1; j++) {
                mmIntervalo[i * grauPolinomio + j] = mmIntervalo[(i-1) * grauPolinomio + j+1];                
            }
        }
    }

    // imprimeMMIntervalar(mmIntervalo, grauPolinomio);
    return mmIntervalo;
}

/*
 * calcula e retorna o vetor de resultados para um sistema de mínimos quadrados.
 * Esta função recebe um vetor de pontos x no formato de intervalo_t, um vetor de valores
 * de função fxintervalo, a quantidade de pontos 'qntPontos' e o grau do polinômio
 * 'grauPolinomio'. Ela calcula o vetor de resultados para um sistema de mínimos quadrados,
 * onde cada elemento do vetor representa um coeficiente a ser encontrado para ajustar
 * o polinômio aos pontos. O vetor resultante é retornado como um vetor de intervalo_t.
 */

// Mover o laço que itera os pontos para o mais externo, a fim de reduzir miss caching
intervalo_t *vetorResultadoIntervalar(intervalo_t *xintervalo, intervalo_t *fxintervalo, int qntPontos, int grauPolinomio)
{
    int i = 0;
    int j = 0;
    int ponto;
    int UF = 4;
    intervalo_t *vetorResultado = alocaVetorIntervalar(grauPolinomio);
    intervalo_t primeiroValor;
    intervalo_t multIntervalar;

    for (ponto = 0; ponto < qntPontos; ponto+=UF)
    {
        for (i = 0; i < grauPolinomio; i++)
        {
            primeiroValor = potenciacao(xintervalo[ponto], i);
            multIntervalar = multiplicacao(primeiroValor, fxintervalo[ponto]);
            vetorResultado[i] = soma(vetorResultado[i], multIntervalar);

            primeiroValor = potenciacao(xintervalo[ponto+1], i);
            multIntervalar = multiplicacao(primeiroValor, fxintervalo[ponto+1]);
            vetorResultado[i] = soma(vetorResultado[i], multIntervalar);

            primeiroValor = potenciacao(xintervalo[ponto+2], i);
            multIntervalar = multiplicacao(primeiroValor, fxintervalo[ponto+2]);
            vetorResultado[i] = soma(vetorResultado[i], multIntervalar);

            primeiroValor = potenciacao(xintervalo[ponto+3], i);
            multIntervalar = multiplicacao(primeiroValor, fxintervalo[ponto+3]);
            vetorResultado[i] = soma(vetorResultado[i], multIntervalar);
            // testar com 8
        }
    }
    // imprimeVetorIntervalar(vetorResultado, grauPolinomio);
    return vetorResultado;
}