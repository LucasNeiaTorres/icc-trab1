#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 2

int encontraMax(double A[N][N], int i)
{
    int max = i;
    for (int j = i + 1; j < N; j++)
    {
        if (fabs(A[j][i]) > fabs(A[max][i]))
        {
            max = j;
        }
    }
    return max;
}

void trocaLinha(double A[N][N], double *b, int i, int iPivo)
{
    double aux;
    for (int j = 0; j < N; j++)
    {
        aux = A[i][j];
        A[i][j] = A[iPivo][j];
        A[iPivo][j] = aux;
    }
    aux = b[i];
    b[i] = b[iPivo];
    b[iPivo] = aux;
}

void eliminicaoGauss(double A[N][N], double *b)
{
    for (int i = 0; i < N; i++)
    {
        int iPivo = encontraMax(A, i);
        if (iPivo != i)
        {
            trocaLinha(A, b, i, iPivo);
        }
        for (int k = i + 1; k < N; k++)
        {
            double m = A[k][i] / A[i][i];
            A[k][i] = 0.0;
            for (int j = i + 1; j < N; j++)
            {
                A[k][j] -= m * A[i][j];
            }
            b[k] -= m * b[i];
        }
    }
}

void imprimeMatriz(double A[N][N], double *b)
{
    for (int i = 0; i < N; i++)
    {
        printf("| ");
        for (int j = 0; j < N; j++)
        {
            printf("%lf ", A[i][j]);
        }
        printf("| | %lf |\n", b[i]);
    }
}

// As duas eliminações são iguais???????????
void eliminacaoGaussSemMultiplicador(double A[N][N], double *b)
{
    for (int i = 0; i < N; i++)
    {
        int iPivo = encontraMax(A, i);
        if (iPivo != i)
        {
            trocaLinha(A, b, i, iPivo);
        }
        for (int k = i + 1; k < N; k++)
        {
            double m = A[k][i] / A[i][i];
            A[k][i] = 0.0;
            for (int j = i + 1; j < N; j++)
            {
                A[k][j] -= m * A[i][j];
            }
            b[k] -= m * b[i];
        }
    }
}

int main()
{
    double matrix[N][N] = {
        {0.004, 15.73},
        {0.423, -24.72}};

    double vetorResultado[N] = {15.77, -20.49};

    eliminicaoGauss(matrix, vetorResultado);

    imprimeMatriz(matrix, vetorResultado);

    return 0;
}
