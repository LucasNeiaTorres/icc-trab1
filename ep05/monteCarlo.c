#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "utils.h"

#define NRAND    ((double)rand() / RAND_MAX)
#define SRAND(a) srand(a)

// Função Styblinski-Tang de n variáveis
double styblinskiTang(double x[], int n)
{
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += (pow(x[i], 4) - 16 * pow(x[i], 2) + 5 * x[i]) / 2.0;
    }
    return sum;
}


// Função para calcular a integral pelo Método dos Retângulos (n dimensões)
double retangulos_nD(double a, double b, int npontos, int n)
{
    double h = (b - a) / npontos;
    double resultado;
    double soma = 0;

    printf("Método dos Retângulos (%d dimensões).\n", n);
    printf("a = (%f), b = (%f), n = (%d), h = (%lg)\n", a, b, npontos, h);

    double t_inicial = timestamp();

    // Cálculo da integral pelo Método dos Retângulos
    for (int i = 0; i < npontos; i++)
    {
        double x[n];
        for (int j = 0; j < n; j++) {
            x[j] = a + i * h;
        }
        soma += h * styblinskiTang(x, n);
    }

    resultado = soma;

    double t_final = timestamp();
    printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);

    return resultado;
}

// Função para calcular a integral pelo Método de Monte Carlo (n dimensões)
double monteCarlo_nD(double a, double b, int namostras, int n)
{
    double resultado;
    double soma = 0.0;

    printf("Método de Monte Carlo (%d dimensões).\n", n);
    printf("a = (%f), b = (%f), n = (%d), variáveis = %d\n", a, b, namostras, n);

    double t_inicial = timestamp();

    // Cálculo da integral pelo Método de Monte Carlo
    for (int i = 0; i < namostras; i++)
    {
        double x[n];
        for (int j = 0; j < n; j++) {
            x[j] = a + NRAND * (b - a);
        }
        soma += styblinskiTang(x, n);
    }

    resultado = (soma / namostras) * (b - a);

    double t_final = timestamp();
    printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);

    return resultado;
}



int main(int argc, char **argv)
{
    if (argc < 4) {
        printf("Utilização: %s n a b\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    double a = atof(argv[2]);
    double b = atof(argv[3]);
    int npontos = 10000000;  // 10^7 pontos para o Método dos Retângulos
    int namostras = 10000000;  // 10^7 amostras para o Método de Monte Carlo

    SRAND(time(NULL));

    // Chamada da função dos Retângulos
    double resultRetangulos = retangulos_nD(a, b, npontos, n);
    printf("Resultado do Método dos Retângulos: %f\n", resultRetangulos);

    // Chamada da função de Monte Carlo
    double resultMonteCarlo = monteCarlo_nD(a, b, namostras, n);
    printf("Resultado do Método de Monte Carlo: %f\n", resultMonteCarlo);

    return 0;
}
