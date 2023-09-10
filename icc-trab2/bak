#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 2

int encontraMax(double **A, int i)
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

void trocaLinha(double **A, double *b, int i, int iPivo)
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

void eliminicaoGauss(double **A, double *b)
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

void retroSubstituicao(double **A, double *b)
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

void eliminacaoGaussAlternativa(double **A, double *b)
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

void imprimeMatriz(double **A, double *b)
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
void eliminacaoGaussSemMultiplicador(double **A, double *b)
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

void copiaMatriz(double **A, double **B)
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

    int tamanho=0;
    scanf("%d", &tamanho);

    double **matrizEntrada;
    matrizEntrada=(double **)calloc(tamanho,sizeof(double*));
    for(int i=0; i<tamanho; i++)
        matrizEntrada[i]=(double *)calloc(tamanho,sizeof(double));
    double *resultadoEntrada;
    resultadoEntrada=(double *)calloc(tamanho,sizeof(double));

    // Leitura da entrada
    for(int i=0; i<tamanho; i++)
        for(int j=0; j<(tamanho+1); j++)
            if(j==tamanho)
                scanf("%lf", &resultadoEntrada[i]);
            else
                scanf("%lf", &matrizEntrada[i][j]);
    

    double **matrix;
        matrix=(double **)calloc(tamanho,sizeof(double*));
    for(int i=0; i<tamanho; i++)
        matrix[i]=(double *)calloc(tamanho,sizeof(double));

    double *vetorResultado;
    vetorResultado=(double *)calloc(tamanho,sizeof(double));


    copiaMatriz(matrizEntrada, matrix);
    copiaVetorResultado(resultadoEntrada, vetorResultado);
    eliminicaoGauss(matrix, vetorResultado);
    imprimeMatriz(matrix, vetorResultado);
    retroSubstituicao(matrix, vetorResultado);
    imprimeVetorResultado(vetorResultado);
    printf("\n\n");

    copiaVetorResultado(resultadoEntrada, vetorResultado);
    copiaMatriz(matrizEntrada, matrix);
    eliminacaoGaussAlternativa(matrix, vetorResultado);
    imprimeMatriz(matrix, vetorResultado);
    retroSubstituicao(matrix, vetorResultado);
    imprimeVetorResultado(vetorResultado);

    return 0;
}
