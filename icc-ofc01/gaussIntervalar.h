#ifndef __GAUSSINTERVALAR_H__
#define __GAUSSINTERVALAR_H__
#include "utils.h"
#include "operacoes.h"
#include "auxiliar.h"

int encontraMaxIntervalar(intervalo_t **A, int i, int ordem);

void trocaLinhaIntervalar(intervalo_t **A, intervalo_t *b, int i, int iPivo, int ordem);

void eliminacaoGaussIntervalar(intervalo_t **A, intervalo_t *b, int ordem);

#endif