#include <stdio.h>
#include "auxiliar.h"

double interpolacaoLagrange(double xe, double *x, double *fx, int qntPontos)
{
    double px = 0.0, li;
    int i, j;
    for (i = 0; i < qntPontos; i++)
    {
        li = 1.0;
        for (j = 0; j < qntPontos; j++)
        {
            if (i != j)
            {
                li = li * ((xe - x[j]) / (x[i] - x[j]));
            }
        }
        px += li * fx[i];
    }
    return px;
}

double **tabelaInterpolacao(double *x, double *fx, int qntPontos)
{
    int i;
    int j;
    double **tabela = alocaMatriz(qntPontos);
    for (j = 0; j < qntPontos; j++)
        tabela[j][0] = fx[j];

    for (j = 1; j < qntPontos; j++)
    {
        for (i = 0; i < (qntPontos - j); i++)
        {
            double valor = (tabela[i + 1][j - 1] - tabela[i][j - 1]) / (x[i + j] - x[i]);
            tabela[i][j] = valor;
        }
    }
    return tabela;
}

double interpolacaoNewton(double xe, double *x, double *fx, int qntPontos)
{

    int i;
    int j;
    double **tabela = tabelaInterpolacao(x, fx, qntPontos);
    double pn = 0;
    for (i = 0; i < qntPontos; i++)
    {
        double dd = 1;
        for (j = 0; j < i; j++)
        {
            dd *= xe - x[j];
        }
        pn += tabela[0][i] * dd;
    }
    desalocaMatriz(tabela, qntPontos);
    return pn;
}