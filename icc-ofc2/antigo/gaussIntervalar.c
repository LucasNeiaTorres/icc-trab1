/* Autores:
    Lucas Néia Torres - GRR20210570
    Leonardo Becker de Oliveira - GRR20211779
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gaussIntervalar.h"

/*
 * calcula o vetor de resíduos intervalares para um polinômio aproximado.
 * Esta função recebe um vetor de pontos no formato de intervalo_t, um vetor de valores
 * de função no formato de intervalo_t, um vetor de coeficientes de polinômio,
 * o grau do polinômio e a quantidade de pontos. Ela calcula o vetor de resíduos,
 * que é a diferença entre os valores de função fornecidos e os valores calculados
 * pelo polinômio aproximado.
 * retorna Um vetor intervalo_t contendo os resíduos calculados.
 */
intervalo_t *calculaResiduoIntervalar(intervalo_t *xintervalo, intervalo_t *fxintervalo, intervalo_t *coeficientes, int grauPolinomio, int qntPontos)
{
    intervalo_t *residuo = (intervalo_t *)calloc(qntPontos, sizeof(intervalo_t));
    int i, j;
    for (i = 0; i < qntPontos; i++)
    {
        // Calcula o resíduo para o ponto i
        for (j = 0; j < grauPolinomio; j++)
        {
            // Calcula a contribuição do termo do polinômio para o resíduo multiplicando o coeficiente pelo valor do termo polinomial
            residuo[i] = soma(multiplicacao(potenciacao(xintervalo[i], j), coeficientes[j]), residuo[i]);
        }
        // Subtrai o valor do termo polinomial calculado do valor de função real para obter o resíduo final
        residuo[i] = subtracao(fxintervalo[i], residuo[i]);
    }
    return residuo;
}

// retorna indice da linha com o maior valor absoluto na coluna i da matriz A de ordem ordem
int encontraMaxIntervalar(intervalo_t **A, int i, int ordem)
{
    int max = i;
    for (int j = i + 1; j < ordem; j++)
        if (fabs(A[j][i].maior) > fabs(A[max][i].maior))
            max = j;
    return max;
}

// troca linhas i e iPivo da matriz A e o elemento b[i] pelo elemento b[iPivo]
void trocaLinhaIntervalar(intervalo_t **A, intervalo_t *b, int i, int iPivo, int ordem)
{
    intervalo_t aux;
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

/*
 * aplica a substituição retroativa em um sistema triangular superior com valores intervalares.
 * Esta função assume que a matriz A é triangular superior de ordem 'ordem' e o vetor b
 * contém os termos independentes do sistema. Ela calcula as soluções para o sistema de
 * equações e atualiza o vetor b com os resultados.
 */
void retroSubstituicaoIntervalar(intervalo_t **A, intervalo_t *b, int ordem)
{
    for (int i = ordem - 1; i >= 0; i--)
    {
        intervalo_t somatorio;
        somatorio.menor = 0;
        somatorio.maior = 0;
        for (int j = i + 1; j < ordem; j++)
            somatorio = soma(somatorio, multiplicacao(A[i][j], b[j]));
        b[i] = divisao(subtracao(b[i], somatorio), A[i][i]);
    }
}

/*
 * resolve um sistema linear usando a eliminação de Gauss com pivoteamento parcial.
 * Esta função recebe uma matriz intervalar A de ordem 'ordem' e um vetor intervalar b
 * representando os termos independentes do sistema linear. Ela realiza a eliminação de
 * Gauss com pivoteamento parcial para encontrar a solução do sistema e retorna um vetor
 * intervalar contendo os resultados.
 */
intervalo_t *eliminacaoGaussIntervalar(intervalo_t **A, intervalo_t *b, int ordem)
{
    intervalo_t **matrizIntevalar = alocaMatrizIntervalar(ordem);
    intervalo_t *resultadoIntervalar = alocaVetorIntervalar(ordem);
    copiaMatrizIntervalar(A, matrizIntevalar, ordem);
    copiaVetorIntervalar(b, resultadoIntervalar, ordem);
    int i, k, j;
    for (i = 0; i < ordem; i++)
    {
        int iPivo = encontraMaxIntervalar(matrizIntevalar, i, ordem);
        if (iPivo != i)
            trocaLinhaIntervalar(matrizIntevalar, resultadoIntervalar, i, iPivo, ordem);
        for (j = i + 1; j < ordem; j++)
        {
            intervalo_t m = divisao(matrizIntevalar[j][i], matrizIntevalar[i][i]);
            matrizIntevalar[j][i].menor = 0.0;
            matrizIntevalar[j][i].maior = 0.0;
            for (k = i + 1; k < ordem; k++)
            {
                matrizIntevalar[j][k] = subtracao(matrizIntevalar[j][k], multiplicacao(m, matrizIntevalar[i][k]));
            }
            intervalo_t mult=multiplicacao(m,resultadoIntervalar[i]);
            resultadoIntervalar[j] = subtracao(resultadoIntervalar[j], multiplicacao(m, resultadoIntervalar[i]));

        }
    }
    retroSubstituicaoIntervalar(matrizIntevalar, resultadoIntervalar, ordem);
    // printf("\n\n");
    // imprimeMatrizIntervalar(matrizIntevalar, ordem);
    // printf("\n\n");
    // imprimeVetorIntervalar(resultadoIntervalar, ordem);
    // printf("\n\n");
    desalocaMatrizIntervalar(matrizIntevalar, ordem);
    return resultadoIntervalar;
}