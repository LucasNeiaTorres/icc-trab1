#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "utils.h"

double styblinskiTang(double x[], int n)
{
    double sum = 0.0;
    for (int i = 0; i < n; i++)
    {
        sum += (pow(x[i], 4) - 16 * pow(x[i], 2) + 5 * x[i]) / 2.0;
    }
    return sum;
}

double random_double(double a, double b)
{
    return a + ((double)random() / RAND_MAX) * (b - a);
}

double retangulos_nD(double a, double b, int npontos, int n)
{
    double h = (b - a) / npontos;
    double resultado = 0.0;
    double soma = 0.0;

    printf("Método dos Retângulos (%d dimensões).\n", n);

    srandom(20232);

    double t_inicial = timestamp();

    for (int i = 0; i < npontos; i++)
    {
        double x[n];
        for (int j = 0; j < n; j++)
        {
            x[j] = a + i * h;
        }
        soma += h * styblinskiTang(x, n);
    }

    resultado = fabs(soma);

    double t_final = timestamp();
    printf("Tempo decorrido: %f seg.\n", (t_final - t_inicial) / 1000);

    return resultado;
}

double monteCarlo_nD(double a, double b, int namostras, int n)
{
    double resultado = 0.0;
    double soma = 0.0;

    printf("Método de Monte Carlo (%d dimensões).\n", n);

    srandom(20232);

    double t_inicial = timestamp();

    for (int i = 0; i < namostras; i++)
    {
        double x[n];
        for (int j = 0; j < n; j++)
            x[j] = random_double(a, b);
        soma += styblinskiTang(x, n);
    }

    resultado = fabs((soma / namostras) * (b - a));

    double t_final = timestamp();
    printf("Tempo decorrido: %f seg.\n", (t_final - t_inicial) / 1000);

    return resultado;
}

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        printf("Utilização: %s n a b\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    double a = atof(argv[2]);
    double b = atof(argv[3]);
    int npontos = 10000000;   // 10^7 pontos para o Método dos Retângulos
    int namostras = 10000000; // 10^7 amostras para o Método de Monte Carlo

    double resultRetangulos = retangulos_nD(a, b, npontos, n);
    printf("Resultado do Método dos Retângulos: %f\n", resultRetangulos);

    printf("----------------------------------------------------------\n");

    double resultMonteCarlo = monteCarlo_nD(a, b, namostras, n);
    printf("Resultado do Método de Monte Carlo: %f\n", resultMonteCarlo);

    printf("----------------------------------------------------------\n");

    if (n != 2)
    {
        resultRetangulos = retangulos_nD(a, b, npontos, 2);
        printf("Resultado do Método dos Retângulos: %f\n", resultRetangulos);

        printf("----------------------------------------------------------\n");

        resultMonteCarlo = monteCarlo_nD(a, b, namostras, 2);
        printf("Resultado do Método de Monte Carlo: %f\n", resultMonteCarlo);

        printf("----------------------------------------------------------\n");
    }

    resultMonteCarlo = monteCarlo_nD(a, b, namostras, 4);
    printf("Resultado do Método de Monte Carlo: %f\n", resultMonteCarlo);

    printf("----------------------------------------------------------\n");

    resultMonteCarlo = monteCarlo_nD(a, b, namostras, 8);
    printf("Resultado do Método de Monte Carlo: %f\n", resultMonteCarlo);

    return 0;
}
