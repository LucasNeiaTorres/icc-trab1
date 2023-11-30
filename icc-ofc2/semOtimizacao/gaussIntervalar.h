/* Autores:
    Lucas Néia Torres - GRR20210570
    Leonardo Becker de Oliveira - GRR20211779
*/
#ifndef __GAUSSINTERVALAR_H__
#define __GAUSSINTERVALAR_H__
#include "utils.h"
#include "operacoes.h"
#include "auxiliar.h"

//  retorna vetor do tipo intervalo_t com a distancia de fx para o polinomio calculado para cada ponto x informado, aplicando cada valor do vetor coeficientes no polinomio
intervalo_t *calculaResiduoIntervalar(intervalo_t *xintervalo, intervalo_t *fxintervalo, intervalo_t *coeficientes, int grauPolinomio, int qntPontos);

// retorna indice da linha com o maior valor absoluto na coluna i
int encontraMaxIntervalar(intervalo_t **A, int i, int ordem);

// troca linhas i e iPivo da matriz A e o elemento b[i] pelo elemento b[iPivo]
void trocaLinhaIntervalar(intervalo_t **A, intervalo_t *b, int i, int iPivo, int ordem);

// aplica a substituicao retroativa em um sistema triangular superior com valores intervalares
void retroSubstituicaoIntervalar(intervalo_t **A, intervalo_t *b, int ordem);

// calcula a eliminacao de gauss com pivoteamento parcial
intervalo_t *eliminacaoGaussIntervalar(intervalo_t **A, intervalo_t *b, int ordem);

#endif