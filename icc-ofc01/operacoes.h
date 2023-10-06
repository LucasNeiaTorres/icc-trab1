#ifndef __OPERACOES_H__
#define __OPERACOES_H__

#define QNT_TERMOS 5
#define QNT_LEITURAS QNT_TERMOS * 2
#define TAM_LINHA 1024
#define ERRO 1

typedef struct intervalo_t
{
    double menor;
    double maior;
} intervalo_t;

intervalo_t calculaIntervalo(double originalValue);

intervalo_t soma(intervalo_t primeiro_valor, intervalo_t segundo_valor);

intervalo_t subtracao(intervalo_t primeiro_valor, intervalo_t segundo_valor);

intervalo_t multiplica(double menor, double maior);

void comparaValor(intervalo_t *resultado, intervalo_t aux);

intervalo_t multiplicacao(intervalo_t primeiro_valor, intervalo_t segundo_valor);

intervalo_t divisao(intervalo_t primeiro_valor, intervalo_t segundo_valor);

intervalo_t potenciacao(intervalo_t valor, int expoente);

int ulps_between_floats(float a, float b);

#endif