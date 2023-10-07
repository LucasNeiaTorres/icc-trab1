/* Autores:
    Lucas Néia Torres - GRR20210570
    Leonardo Becker de Oliveira - GRR20211779
*/
#ifndef __AUXILIAR_H__
#define __AUXILIAR_H__
#include "operacoes.h"

// atribui valores da matriz A para a matriz B
void copiaMatriz(double **A, double **B, int qntPontos);

// atribui valores do vetor b para bBackup
void copiaVetorResultado(double *b, double *bBackup, int qntPontos);

void imprimeMatriz(double **A, int qntPontos);

void imprimeVetorResultado(double *A, int qntPontos);

// aloca dinamicamente matriz de tamanho qntPontos x qntPontos
double **alocaMatriz(int qntPontos);

// aloca dinamicamente vetor de tamanho qntPontos 
double *alocaVetor(int qntPontos);

// desaloca dinamicamente matriz de tamanho qntPontos x qntPontos
void desalocaMatriz(double **matriz, int qntPontos);

// desaloca dinamicamente vetor de tamanho qntPontos 
void desalocaVetor(double *vetor);

// atribui valores da matriz A para a matriz B, sendo A e B matrizes com valores intervalares
void copiaMatrizIntervalar(intervalo_t **A, intervalo_t **B, int qntPontos);

// atribui valores do vetor b para bBackup, sendo A e B vetores com valores intervalares
void copiaVetorIntervalar(intervalo_t *b, intervalo_t *bBackup, int qntPontos);

// aloca dinamicamente matriz intervalar de tamanho qntPontos x qntPontos
intervalo_t **alocaMatrizIntervalar(int grauPolinomio);

// aloca dinamicamente vetor intervalar de tamanho qntPontos 
intervalo_t *alocaVetorIntervalar(int grauPolinomio);

// desaloca dinamicamente matriz intervalar de tamanho qntPontos x qntPontos
void desalocaMatrizIntervalar(intervalo_t **matriz, int grauPolinomio);

// desaloca dinamicamente vetor intervalar de tamanho qntPontos 
void desalocaVetorIntervalar(intervalo_t *vetor);

void imprimeMatrizIntervalar(intervalo_t **matriz, int grauPolinomio);

void imprimeVetorIntervalar(intervalo_t *vetor, int grauPolinomio);

#endif