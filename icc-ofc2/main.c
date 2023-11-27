/* Autores:
    Lucas Néia Torres - GRR20210570
    Leonardo Becker de Oliveira - GRR20211779
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "auxiliar.h"
#include "utils.h"
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
    grauPolinomio++;

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

    startTime = timestamp();
    intervalo_t *mmIntervalo = sistemaLinearIntervalar(xintervalo, qntPontos, grauPolinomio);
    intervalo_t *vetorIntervalo = vetorResultadoIntervalar(xintervalo, fxintervalo, qntPontos, grauPolinomio);
    geraTime = timestamp() - startTime;

    startTime = timestamp();
    intervalo_t *coeficientes = eliminacaoGaussIntervalar(mmIntervalo, vetorIntervalo, grauPolinomio);
    intervalo_t *residuo = calculaResiduoIntervalar(xintervalo, fxintervalo, coeficientes, grauPolinomio, qntPontos);
    solTime = timestamp() - startTime;


    imprimeVetorIntervalar(coeficientes, grauPolinomio);
    imprimeVetorIntervalar(residuo, qntPontos);
    printf("geraTime: %1.8e\n", geraTime);
    printf("solTime:%1.8e\n", solTime);

    desalocaVetorIntervalar(xintervalo);
    desalocaVetorIntervalar(fxintervalo);

    // desalocaVetorIntervalar(vetorIntervalo);
    // desalocaVetorIntervalar(coeficientes);
    // desalocaVetorIntervalar(residuo);
    // desalocaMatrizIntervalar(matrizIntervalo, grauPolinomio);
}