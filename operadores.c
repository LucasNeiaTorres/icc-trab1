#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fenv.h>
#include <float.h>
#include "operacoes.h"

intervalo_t calculaIntervalo(double originalValue)
{
    intervalo_t intervalo;
    fesetround(FE_UPWARD);
    intervalo.maior = nextafter(originalValue, INFINITY);

    fesetround(FE_DOWNWARD);
    intervalo.menor = nextafter(originalValue, -INFINITY);

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

intervalo_t divisao(intervalo_t primeiro_valor, intervalo_t segundo_valor)
{
    intervalo_t erro0 = calculaIntervalo(0); 
    if (((segundo_valor.menor > erro0.menor) && (segundo_valor.menor < erro0.maior)) || ((segundo_valor.maior > erro0.menor) && (segundo_valor.maior < erro0.maior)))
    {
        primeiro_valor.maior = INFINITY;
        primeiro_valor.menor = -INFINITY;
    }
    else
    {
        intervalo_t valor_auxiliar;
        valor_auxiliar.menor = 1 / segundo_valor.maior;
        valor_auxiliar.maior = 1 / segundo_valor.menor;
        primeiro_valor = multiplicacao(primeiro_valor, valor_auxiliar);
    }
    return primeiro_valor;
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
