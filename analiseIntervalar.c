#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fenv.h>
#include <float.h>

#define QNT_TERMOS 10
#define TAM_LINHA 1024
#define ERRO 1

typedef struct intervalo_t
{
    float menor;
    float maior;
} intervalo_t;

intervalo_t calculaIntervalo(double originalValue)
{
    intervalo_t intervalo;
    fesetround(FE_UPWARD);
    intervalo.maior = nextafter(originalValue, INFINITY);

    fesetround(FE_DOWNWARD);
    intervalo.menor = nextafter(originalValue, INFINITY);

    return intervalo;
}

intervalo_t soma(intervalo_t primeiro_valor, intervalo_t segundo_valor)
{
    intervalo_t resultado;
    fesetround(FE_UPWARD);
    resultado.maior = primeiro_valor.maior + segundo_valor.maior;
    fesetround(FE_DOWNWARD);
    resultado.menor = primeiro_valor.menor + segundo_valor.menor;
    return resultado;
}

intervalo_t subtracao(intervalo_t primeiro_valor, intervalo_t segundo_valor)
{
    intervalo_t resultado;
    fesetround(FE_UPWARD);
    resultado.maior = primeiro_valor.maior - segundo_valor.menor;
    fesetround(FE_DOWNWARD);
    resultado.menor = primeiro_valor.menor - segundo_valor.maior;
    return resultado;
}

intervalo_t multiplica(double menor, double maior)
{
    intervalo_t resultado;
    fesetround(FE_DOWNWARD);
    resultado.menor = menor * maior;
    fesetround(FE_UPWARD);
    resultado.maior = menor * maior;
    return resultado;
}

void comparaValor(intervalo_t *resultado, intervalo_t aux)
{
    if (aux.maior > resultado->maior)
        resultado->maior = aux.maior;
    if (aux.menor < resultado->menor)
        resultado->menor = aux.menor;
}

intervalo_t multiplicacao(intervalo_t primeiro_valor, intervalo_t segundo_valor)
{
    intervalo_t resultado;
    intervalo_t aux;

    resultado = multiplica(primeiro_valor.menor, segundo_valor.menor);
    aux = multiplica(primeiro_valor.menor, segundo_valor.maior);
    comparaValor(&resultado, aux);
    aux = multiplica(primeiro_valor.maior, segundo_valor.menor);
    comparaValor(&resultado, aux);
    aux = multiplica(primeiro_valor.maior, segundo_valor.maior);
    comparaValor(&resultado, aux);
    return resultado;
}

int ulps_between_floats(float a, float b)
{
    int ia = *((int *)&a);
    int ib = *((int *)&b);

    if (ia < 0)
        ia = 0x80000000 - ia; // Converte para positivo (complemento de 2)
    if (ib < 0)
        ib = 0x80000000 - ib; // Converte para positivo e corrige falha
    // printf("((%d %d))",ia,ib);
    return ib - ia - ERRO;
}

int main(int argc, char *argv[])
{
    int i;
    char operador;
    intervalo_t segundo_valor;
    intervalo_t primeiro_valor;
    float erro_absoluto;
    float erro_relativo;
    intervalo_t erro0 = calculaIntervalo(0);
    printf("erro menor: %1.8e\n", erro0.menor);
    printf("erro maior: %1.8e\n", erro0.maior);

    char valores_entrada[QNT_TERMOS][TAM_LINHA];
    for (i = 0; i < QNT_TERMOS; i++)
    {
        scanf("%s", valores_entrada[i]);
    }

    primeiro_valor = calculaIntervalo(atof(valores_entrada[0]));
    for (i = 2; i < QNT_TERMOS; i += 2)
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
            if (((segundo_valor.maior > erro0.menor) && (segundo_valor.maior < erro0.maior)) && ((segundo_valor.menor > erro0.menor) && (segundo_valor.menor < erro0.maior)))
            {
                intervalo_t valor_auxiliar;
                valor_auxiliar.menor = 1 / segundo_valor.maior;
                valor_auxiliar.maior = 1 / segundo_valor.menor;
                primeiro_valor = multiplicacao(primeiro_valor, valor_auxiliar);
            }
            else
            {
                primeiro_valor.maior = INFINITY;
                primeiro_valor.menor = -INFINITY;
            }
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