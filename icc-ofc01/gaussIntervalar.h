#ifndef __GAUSSINTERVALAR_H__
#define __GAUSSINTERVALAR_H__
#include "utils.h"
#include "operacoes.h"
#include "auxiliar.h"

intervalo_t* calculaResiduoIntervalar(intervalo_t *xintervalo, intervalo_t *fxintervalo, intervalo_t *vetorSolucao, int grauPolinomio, int qntPontos);

void trocaLinhaIntervalar(intervalo_t **A, intervalo_t *b, int i, int iPivo, int ordem);

void eliminacaoGaussIntervalar(intervalo_t **A, intervalo_t *b, int ordem);


#endif