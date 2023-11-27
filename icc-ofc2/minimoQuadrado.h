/* Autores:
    Lucas Néia Torres - GRR20210570
    Leonardo Becker de Oliveira - GRR20211779
*/
#ifndef __MINIMO_QUADRADO_H__
#define __MINIMO_QUADRADO_H__
#include "auxiliar.h"
#include "operacoes.h"

// calcula e retorna a matriz de coeficientes para um sistema linear de mínimos quadrados
intervalo_t *sistemaLinearIntervalar(intervalo_t *xintervalo, int qntPontos, int grauPolinomio);

// calcula e retorna o vetor de resultados para um sistema de mínimos quadrados
intervalo_t *vetorResultadoIntervalar(intervalo_t *xintervalo, intervalo_t *fxintervalo, int qntPontos, int grauPolinomio);

#endif