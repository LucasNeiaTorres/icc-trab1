#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int encontraMax(double **A, int i, int ordem)
{
    int max = i;
    for (int j = i + 1; j < ordem; j++)
        if (fabs(A[j][i]) > fabs(A[max][i]))
            max = j;
    return max;
}

void trocaLinha(double **A, double *b, int i, int iPivo, int ordem)
{
    double aux;
    for (int j = 0; j < ordem; j++)
    {
        aux = A[i][j];
        A[i][j] = A[iPivo][j];
        A[iPivo][j] = aux;
    }
    aux = b[i];
    b[i] = b[iPivo];
    b[iPivo] = aux;
}

void eliminacaoGauss(double **A, double *b, int ordem)
{
    int i, k, j;
    for (i = 0; i < ordem; i++)
    {
        int iPivo = encontraMax(A, i, ordem);
        if (iPivo != i)
            trocaLinha(A, b, i, iPivo, ordem);

        for (k = i + 1; k < ordem; k++)
        {
            double m = A[k][i] / A[i][i];
            A[k][i] = 0.0;
            for (j = i + 1; j < ordem; j++)
                A[k][j] -= m * A[i][j];
            b[k] -= m * b[i];
        }
    }
}

void retroSubstituicao(double **A, double *b, int ordem)
{
    for (int i = ordem - 1; i >= 0; i--)
    {
        double soma = 0.0;
        for (int j = i + 1; j < ordem; j++)
            soma += A[i][j] * b[j];
        b[i] = (b[i] - soma) / A[i][i];
    }
}

// Forma alternativa onde não usa pivoteamento e que consiste em:

//         Para cada linha  do pivô, dividir todos os  coeficientes pelo pivô  (que fica com o valor 1)
//         Proceder com  a eliminação,  zerando a coluna  do pivô,  sem fazer pivoteamento.
//         Completada   a  triangularização,   calcular  as   incógnitas  por retro-substituição.

void eliminacaoGaussAlternativa(double **A, double *b, int ordem)
{
    for (int i = 0; i < ordem; i++)
    {
        double pivo = A[i][i];
        for (int j = 0; j < ordem; j++)
            A[i][j] /= pivo;
        b[i] /= pivo;

        for (int k = i + 1; k < ordem; k++)
        {
            double m = A[k][i];
            A[k][i] = 0.0;
            for (int j = i + 1; j < ordem; j++)
                A[k][j] -= m * A[i][j];
            b[k] -= m * b[i];
        }
    }
}

void imprimeMatriz(double **A, double *b, int ordem)
{
    for (int i = 0; i < ordem; i++)
    {
        printf("| ");
        for (int j = 0; j < ordem; j++)
        {
            printf("%lf ", A[i][j]);
        }
        printf("| | %lf |\n", b[i]);
    }
}

void imprimeVetorResultado(double *b, int ordem)
{
    for (int i = 0; i < ordem; i++)
    {
        printf("| %lf |", b[i]);
    }
    printf("\n");
}

// As duas eliminações são iguais???????????
void eliminacaoGaussSemMultiplicador(double **A, double *b, int ordem)
{
    for (int i = 0; i < ordem; i++)
    {
        int iPivo = encontraMax(A, i, ordem);
        if (iPivo != i)
            trocaLinha(A, b, i, iPivo, ordem);
        for (int k = i + 1; k < ordem; k++)
        {
            for (int j = i + 1; j < ordem; j++)
                A[k][j] = (A[k][j] * A[i][i]) - (A[i][j] * A[k][i]);
            b[k] = (b[k] * A[i][i]) - (b[i] * A[k][i]);
        }
    }
}

void copiaMatriz(double **A, double **B, int ordem)
{
    for (int i = 0; i < ordem; i++)
    {
        for (int j = 0; j < ordem; j++)
        {
            B[i][j] = A[i][j];
        }
    }
}

void copiaVetorResultado(double *b, double *bBackup, int ordem)
{
    for (int i = 0; i < ordem; i++)
    {
        bBackup[i] = b[i];
    }
}

int main()
{

    int ordem, i, j;
    double teste;
    
    if (scanf("%d", &ordem) != 1) {
        perror("Erro ao ler entrada");
        exit(EXIT_FAILURE);
    }
    double **matrizEntrada;
    matrizEntrada = (double **)calloc(ordem, sizeof(double*));
    for(i=0; i<ordem; i++)
        matrizEntrada[i] = (double *)calloc(ordem, sizeof(double));
    double *resultadoEntrada;
    resultadoEntrada = (double *)calloc(ordem, sizeof(double));

    // Leitura da entrada
    for(i=0; i < ordem; i++)
        for(j=0; j < (ordem+1); j++)
            if(j == ordem)
                teste = scanf("%lf", &resultadoEntrada[i]);
            else
                teste = scanf("%lf", &matrizEntrada[i][j]);
    

    double **matrix;
        matrix = (double **)calloc(ordem, sizeof(double*));
    for(int i=0; i<ordem; i++)
        matrix[i] = (double *)calloc(ordem, sizeof(double));

    double *vetorResultado;
    vetorResultado =(double *)calloc(ordem, sizeof(double));


    copiaMatriz(matrizEntrada, matrix, ordem);
    copiaVetorResultado(resultadoEntrada, vetorResultado, ordem);
    // eliminacaoGaussAlternativa(matrix, vetorResultado, ordem);
    // eliminacaoGauss(matrix, vetorResultado, ordem);
    eliminacaoGaussSemMultiplicador(matrix, vetorResultado, ordem);
    imprimeMatriz(matrix, vetorResultado, ordem);
    retroSubstituicao(matrix, vetorResultado, ordem);
    // imprimeVetorResultado(vetorResultado, ordem);
    printf("\n\n");

    // copiaVetorResultado(resultadoEntrada, vetorResultado, ordem);
    // copiaMatriz(matrizEntrada, matrix, ordem);
    // eliminacaoGaussAlternativa(matrix, vetorResultado, ordem);
    // imprimeMatriz(matrix, vetorResultado, ordem);
    // retroSubstituicao(matrix, vetorResultado, ordem);
    imprimeVetorResultado(vetorResultado, ordem);

    for (i=0; i < ordem; i++)
        free(matrizEntrada[i]);
    free(matrizEntrada);

    for (i=0; i < ordem; i++)
        free(matrix[i]);
    free(matrix);

    free(resultadoEntrada);
    free(vetorResultado);
    return 0;
}
