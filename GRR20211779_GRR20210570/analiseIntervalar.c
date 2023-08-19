#include <stdio.h>
#include <stdlib.h>
#include "operacoes.h"

int main(int argc, char *argv[])
{
    int i;
    char operador;
    intervalo_t segundo_valor;
    intervalo_t primeiro_valor;
    float erro_absoluto;
    float erro_relativo;
    char valores_entrada[QNT_LEITURAS][TAM_LINHA];

    for (i = 0; i < QNT_LEITURAS; i++)
    {
        scanf("%s", valores_entrada[i]);
    }

    primeiro_valor = calculaIntervalo(atof(valores_entrada[0]));

    for (i = 2; i < QNT_LEITURAS; i += 2)
    {
        operador = valores_entrada[i - 1][0];
        segundo_valor = calculaIntervalo(atof(valores_entrada[i]));

        printf("%d:\n[%1.8e,%1.8e] %c [%1.8e,%1.8e] = \n", i / 2, primeiro_valor.menor, primeiro_valor.maior, operador, segundo_valor.menor, segundo_valor.maior);
        switch (operador)
        {
        case '+':
            primeiro_valor = soma(primeiro_valor, segundo_valor);
            break;
        case '-':
            primeiro_valor = subtracao(primeiro_valor, segundo_valor);
            break;
        case '*':
            primeiro_valor = multiplicacao(primeiro_valor, segundo_valor);
            break;
        case '/':
            primeiro_valor = divisao(primeiro_valor, segundo_valor);
            break;
        default:
            break;
        }
        erro_absoluto = primeiro_valor.maior - primeiro_valor.menor;
        erro_relativo = erro_absoluto / primeiro_valor.menor;
        int ulps = ulps_between_floats(primeiro_valor.menor, primeiro_valor.maior);
        printf("[%1.8e,%1.8e]\nEA: %1.8e; ER: %1.8e; ULPs: %d\n", primeiro_valor.menor, primeiro_valor.maior, erro_absoluto, erro_relativo, ulps);
    }
    
    return 0;
}
