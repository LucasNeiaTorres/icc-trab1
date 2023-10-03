#ifndef __ELIMINACAO_GAUSS_H__
#define __ELIMINACAO_GAUSS_H__
#include "utils.h"
#include "auxiliar.h"
#include "operacoes.h"

double calculaResiduo(double **A, double *vetorSolucao, double *b, int ordem);

int encontraMax(double **A, int i, int ordem);

void trocaLinha(double **A, double *b, int i, int iPivo, int ordem);

void retroSubstituicao(double **A, double *b, int ordem);

void eliminacaoGauss(double **A, double *b, int ordem);

#endif // __ELIMINACAO_GAUSS_H__