#ifndef __INTERPOLACAO_H__
#define __INTERPOLACAO_H__

double **tabelaInterpolacao(double *x, double *fx, int qntPontos);
double interpolacaoLagrange(double xe, double *x, double *fx, int qntPontos);
double interpolacaoNewton(double xe, double *x, double *fx, int qntPontos);

#endif