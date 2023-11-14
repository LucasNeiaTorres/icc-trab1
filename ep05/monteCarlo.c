#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"

#define SRAND(a) srand(a)

// double styblinskiTang(double a, double b, int namostras) {
//     double resultado;
//     double soma = 0.0;

//     printf("Método de Monte Carlo (x, y).\n");
//     printf("a = (%f), b = (%f), n = (%d), variáveis = 2\n", a, b, namostras);

//     double t_inicial = timestamp();

//     SRAND(20232); // Semente 20232

//     for (int i = 0; i < namostras; i++) {
//         double x = a + (b - a) * UNIFORM_RAND;
//         double y = a + (b - a) * UNIFORM_RAND;
//         soma += pow(x, 4) - 16 * pow(x, 2) + 5 * pow(x, 2);
//     }

//     resultado = soma / namostras * pow(b - a, 2);

//     double t_final = timestamp();
//     printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);

//     return resultado;
// }

double styblinskiTang(double a, double b, int namostras, int n_variaveis) {
    double resultado;
    double soma = 0.0;

    printf("Método de Monte Carlo (%d variáveis).\n", n_variaveis);
    printf("a = (%f), b = (%f), n = (%d), variáveis = %d\n", a, b, namostras, n_variaveis);

    double t_inicial = timestamp();

    SRAND(20232);

    for (int i = 0; i < namostras; i++) {
        double x_sum = 0.0;
        for (int j = 0; j < n_variaveis; j++) {
            double valor_randomico = a + (b - a) * rand();
            x_sum += pow(valor_randomico, 4) - 16 * pow(valor_randomico, 2) + 5 * valor_randomico;
        }
        x_sum /= 2;
        soma += x_sum;
    }

    resultado = soma / namostras;

    double t_final = timestamp();
    printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);

    return resultado;
}

double retangulos_xy(double a, double b, int npontos) {
    double h = (b - a) / npontos;
    double resultado;
    double soma = 0.0;

    printf("Método dos Retângulos (x, y).\n");
    printf("a = (%f), b = (%f), n = (%d), h = (%lg)\n", a, b, npontos, h);

    double t_inicial = timestamp();

    for (int i = 0; i < npontos; i++) {
        for (int j = 0; j < npontos; j++) {
            double x = a + (i + 0.5) * h;
            double y = a + (j + 0.5) * h;
            soma += pow(x, 4) - 16 * pow(x, 2) + 5 * pow(x, 2);
        }
    }

    resultado = pow(h, 2) * soma;

    double t_final = timestamp();
    printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);

    return resultado;
}

int main(int argc, char **argv) {

    if (argc < 4) {
        printf("Utilização: %s inicial final n_variaveis\n", argv[0]);
        return 1;
    }

    int n_variaveis = atoi(argv[1]);
    double a = atof(argv[2]);
    double b = atof(argv[3]);
    int n_amostras = pow(10, 2);

    if (n_variaveis == 2) {
        double resultado_monte_carlo = styblinskiTang(a, b, n_amostras, n_variaveis);
        printf("Resultado (Monte Carlo): %f\n", resultado_monte_carlo);

    } else if(n_variaveis == 4) {
        // double resultado_monte_carlo = styblinskiTang4(a, b, n_amostras); FAZER COM 4 
    } else if(n_variaveis == 8) {
        // double resultado_monte_carlo = styblinskiTang8(a, b, n_amostras); FAZER COM 8
    }

    double resultado_retangulos = retangulos_xy(a, b, n_amostras);
    printf("Resultado (Retângulos): %f\n", resultado_retangulos);
    return 0;
}
