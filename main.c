#include <stdio.h>
#include <stdlib.h>

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
        printf("x%d= %lf \n", (i + 1), b[i]);
    }
}

double **alocaMatriz(int ordem)
{
    double **matriz;
    matriz = (double **)calloc(ordem, sizeof(double *));
    for (int i = 0; i < ordem; i++)
        matriz[i] = (double *)calloc(2, sizeof(double));
    return matriz;
}

double *alocaVetor(int ordem)
{
    double *vetor;
    vetor = (double *)calloc(ordem, sizeof(double));
    return vetor;
}

void desalocaMatriz(double **matriz, int ordem)
{
    for (int i = 0; i < ordem; i++)
        free(matriz[i]);
    free(matriz);
}

void desalocaVetor(double *vetor)
{
    free(vetor);
}

double lagrange(double xe, double *x, double *fx, int ordem){double px = 0.0, li; int i, j; for (i = 0; i < ordem; i++){li = 1.0;for (j = 0; j < ordem; j++){if (i != j){li = li * ((xe - x[j]) / (x[i] - x[j]));}}px += li * fx[i]; }return px;}

int main(int argc, char *argv[])
{

    int ordem, i;
    double xe=atof(argv[1]);
    double px;

    if (scanf("%d", &ordem) != 1)
    {
        perror("Erro ao ler entrada");
        exit(EXIT_FAILURE);
    }

    double *x=alocaVetor(ordem);
    double *fx = alocaVetor(ordem);

    // Leitura da entrada
    for (i = 0; i < ordem; i++)
    {
        scanf("%lf", &x[i]);
        scanf("%lf", &fx[i]);
    }

    px=lagrange(xe, x, fx, ordem);
printf("%lf\n", px);

    return 0;
}