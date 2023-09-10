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

void retroSubstituicao(double A[N][N], double *b)
{
    for (int i = N - 1; i >= 0; i--)
    {
        double soma = 0.0;
        for (int j = i + 1; j < N; j++)
        {
            soma += A[i][j] * b[j];
        }
        b[i] = (b[i] - soma) / A[i][i];
    }
}

// Forma alternativa onde não usa pivoteamento e que consiste em:

//         Para cada linha  do pivô, dividir todos os  coeficientes pelo pivô  (que fica com o valor 1)
//         Proceder com  a eliminação,  zerando a coluna  do pivô,  sem fazer pivoteamento.
//         Completada   a  triangularização,   calcular  as   incógnitas  por retro-substituição.

void eliminacaoGaussAlternativa(double A[N][N], double *b)
{
    for (int i = 0; i < N; i++)
    {
        double pivo = A[i][i];
        for (int j = 0; j < N; j++)
        {
            A[i][j] /= pivo;
        }
        b[i] /= pivo;
        for (int k = i + 1; k < N; k++)
        {
            double m = A[k][i];
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

void imprimeVetorResultado(double *b)
{
    for (int i = 0; i < N; i++)
    {
        printf("| %lf |", b[i]);
    }
    printf("\n");
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

void copiaMatriz(double A[N][N], double B[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            B[i][j] = A[i][j];
        }
    }
}

void copiaVetorResultado(double *b, double *bBackup)
{
    for (int i = 0; i < N; i++)
    {
        bBackup[i] = b[i];
    }
}

int main()
{
    double backup[N][N] = {
        {0.004, 15.73},
        {0.423, -24.72}};   

    double backupResultado[N] = {15.77, -20.49};

    double vetorResultado[N];
    double matrix[N][N];

    copiaMatriz(backup, matrix);
    copiaVetorResultado(backupResultado, vetorResultado);
    eliminicaoGauss(matrix, vetorResultado);
    imprimeMatriz(matrix, vetorResultado);
    retroSubstituicao(matrix, vetorResultado);
    imprimeVetorResultado(vetorResultado);
    printf("\n\n");

    copiaVetorResultado(backupResultado, vetorResultado);
    copiaMatriz(backup, matrix);
    eliminacaoGaussAlternativa(matrix, vetorResultado);
    imprimeMatriz(matrix, vetorResultado);
    retroSubstituicao(matrix, vetorResultado);
    imprimeVetorResultado(vetorResultado);

    return 0;
}
