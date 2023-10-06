#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "auxiliar.h"
#include "utils.h"
#include "eliminacaoGauss.h"
#include "operacoes.h"
#include "gaussIntervalar.h"
#include "minimoQuadrado.h"
#include "likwid.h"

int main()
{
    int qntPontos, i;
    double pl;
    double pn;
    int grauPolinomio;
    char aux;
    double entrada;
    rtime_t startTime;
    rtime_t geraTime;
    rtime_t solTime;

    if (scanf("%d", &grauPolinomio) != 1)
    {
        perror("Erro ao ler entrada");
        exit(EXIT_FAILURE);
    }

    // Leitura da quantidade de pontos
    if (scanf("%d", &qntPontos) != 1)
    {
        perror("Erro ao ler entrada");
        exit(EXIT_FAILURE);
    }

    intervalo_t *xintervalo = alocaVetorIntervalar(qntPontos);
    intervalo_t *fxintervalo = alocaVetorIntervalar(qntPontos);

    // Leitura da entrada
    for (i = 0; i < qntPontos; i++)
    {
        aux = scanf("%lf", &entrada);
        xintervalo[i] = calculaIntervalo(entrada);
        aux = scanf("%lf", &entrada);
        fxintervalo[i] = calculaIntervalo(entrada);
    }

    LIKWID_MARKER_INIT;
    LIKWID_MARKER_START("EliminacaoGaussIntervalar");

    startTime = timestamp();
    intervalo_t **matrizIntervalo = sistemaLinearIntervalar(xintervalo, qntPontos, grauPolinomio);
    intervalo_t *vetorIntervalo = vetorResultadoIntervalar(xintervalo, fxintervalo, qntPontos, grauPolinomio);
    geraTime = timestamp() - startTime;
    startTime = timestamp();
    intervalo_t *coeficientes = eliminacaoGaussIntervalar(matrizIntervalo, vetorIntervalo, grauPolinomio);
    intervalo_t *residuo = calculaResiduoIntervalar(xintervalo, fxintervalo, coeficientes, grauPolinomio, qntPontos);
    solTime = timestamp() - startTime;

    LIKWID_MARKER_STOP("EliminacaoGaussIntervalar");
    LIKWID_MARKER_CLOSE;

    imprimeVetorIntervalar(coeficientes, grauPolinomio);
    imprimeVetorIntervalar(residuo, qntPontos);
    printf("%lf\n", solTime);
    printf("%lf\n", geraTime);

    desalocaVetorIntervalar(xintervalo);
    desalocaVetorIntervalar(fxintervalo);
    desalocaVetorIntervalar(vetorIntervalo);
    desalocaVetorIntervalar(coeficientes);
    desalocaVetorIntervalar(residuo);
    desalocaMatrizIntervalar(matrizIntervalo, grauPolinomio);
}