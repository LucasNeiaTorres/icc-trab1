/* Autores:
    Lucas Néia Torres - GRR20210570
    Leonardo Becker de Oliveira - GRR20211779
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fenv.h>
#include <float.h>
#include "operacoes.h"

// dado o valor de originalValue, calcula e retorna o intervalo que o representa
intervalo_t calculaIntervalo(double originalValue)
{
    intervalo_t intervalo;
    intervalo.maior = nextafter(originalValue, INFINITY);

    intervalo.menor = nextafter(originalValue, -INFINITY);

    return intervalo;
}

// calcula e retorna a soma de dois intervalos
intervalo_t soma(intervalo_t primeiro_valor, intervalo_t segundo_valor)
{
    intervalo_t resultado;
    resultado.maior = primeiro_valor.maior + segundo_valor.maior;
    resultado.menor = primeiro_valor.menor + segundo_valor.menor;
    return resultado;
}

// calcula e retorna a subtracao de dois intervalos
intervalo_t subtracao(intervalo_t primeiro_valor, intervalo_t segundo_valor)
{
    intervalo_t resultado;
    resultado.maior = primeiro_valor.maior - segundo_valor.menor;
    resultado.menor = primeiro_valor.menor - segundo_valor.maior;
    return resultado;
}

// calcula a multiplicacao de dois numeros e retorna o intervalo que o representa
intervalo_t multiplica(double menor, double maior)
{
    intervalo_t resultado;
    resultado.menor = menor * maior;
    resultado.maior = menor * maior;
    return resultado;
}

// compara o intervalo passado como parâmetro com o intervalo resultado, atualizando o intervalo 'resultado' caso necessário
void comparaValor(intervalo_t *resultado, intervalo_t aux)
{
    if (aux.maior > resultado->maior)
        resultado->maior = aux.maior;
    if (aux.menor < resultado->menor)
        resultado->menor = aux.menor;
}

// calcula e retorna a multiplicacao de dois intervalos
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

// calcula e retorna a divisao de dois intervalos
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

// calcula e retorna a potenciacao de um intervalo de acordo com o expoente passado como parâmetro
intervalo_t potenciacao(intervalo_t valor, int expoente)
{
    intervalo_t resultado;
    if (expoente == 0)
    {
        resultado.menor = 1;
        resultado.maior = 1;
    }
    else if ((expoente % 2) != 0)
    {
        resultado.menor = pow(valor.menor, expoente);
        resultado.maior = pow(valor.maior, expoente);
    }
    else
    {
        if (valor.menor >= 0)
        {
            resultado.menor = pow(valor.menor, expoente);
            resultado.maior = pow(valor.maior, expoente);
        }
        else if (valor.maior < 0)
        {
            resultado.menor = pow(valor.maior, expoente);
            resultado.maior = pow(valor.menor, expoente);
        }
        else
        {
            resultado.menor = 0;
            if (pow(valor.menor, expoente) > pow(valor.maior, expoente))
            {
                resultado.maior = pow(valor.menor, expoente);
            }
            else
            {
                resultado.maior = pow(valor.maior, expoente);
            }
        }
    }
    return resultado;
}