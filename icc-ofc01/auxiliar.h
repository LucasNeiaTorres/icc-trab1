#ifndef __AUXILIAR_H__
#define __AUXILIAR_H__
#include "operacoes.h"

void copiaMatriz(double **A, double **B, int qntPontos);

void copiaVetorResultado(double *A, double *B, int qntPontos);

void imprimeMatriz(double **A, int qntPontos);

void imprimeVetorResultado(double *A, int qntPontos);

double **alocaMatriz(int qntPontos);

double *alocaVetor(int qntPontos);

void desalocaMatriz(double **matriz, int qntPontos);

void desalocaVetor(double *vetor);

void copiaMatrizIntervalar(intervalo_t **A, intervalo_t **B, int qntPontos);

void copiaVetorIntervalar(intervalo_t *b, intervalo_t *bBackup, int qntPontos);

intervalo_t **alocaMatrizIntervalar(int grauPolinomio);

intervalo_t *alocaVetorIntervalar(int grauPolinomio);

#endif