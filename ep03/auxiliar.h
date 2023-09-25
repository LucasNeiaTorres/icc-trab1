#ifndef __AUXILIAR_H__
#define __AUXILIAR_H__

void copiaMatriz(double **A, double **B, int qntPontos);

void copiaVetorResultado(double *A, double *B, int qntPontos);

void imprimeMatriz(double **A, int qntPontos);

void imprimeVetorResultado(double *A, int qntPontos);

double **alocaMatriz(int qntPontos);

double *alocaVetor(int qntPontos);

void desalocaMatriz(double **matriz, int qntPontos);

void desalocaVetor(double *vetor);

#endif