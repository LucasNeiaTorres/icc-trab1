#ifndef __MINIMO_QUADRADO_H__
#define __MINIMO_QUADRADO_H__
#include "auxiliar.h"
#include "operacoes.h"

intervalo_t **sistemaLinearIntervalar(intervalo_t *xintervalo, int qntPontos, int grauPolinomio);

intervalo_t *vetorResultadoIntervalar(intervalo_t *xintervalo, intervalo_t *fxintervalo, int qntPontos, int grauPolinomio);

#endif