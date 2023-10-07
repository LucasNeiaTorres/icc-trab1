/* Autores:
    Lucas Néia Torres - GRR20210570
    Leonardo Becker de Oliveira - GRR20211779
*/
#ifndef __OPERACOES_H__
#define __OPERACOES_H__

#define QNT_TERMOS 5
#define QNT_LEITURAS QNT_TERMOS * 2
#define TAM_LINHA 1024
#define ERRO 1

// estrutura para armazenar intervalos, sendo 'menor' o maior valor representável menor que o número e 'maior' o menor valor representável maior que o número
typedef struct intervalo_t
{
    double menor;
    double maior;
} intervalo_t;

// dado um número, calcula e retorna o intervalo que o representa
intervalo_t calculaIntervalo(double originalValue);

// calcula e retorna a soma de dois intervalos
intervalo_t soma(intervalo_t primeiro_valor, intervalo_t segundo_valor);

// calcula e retorna a subtracao de dois intervalos
intervalo_t subtracao(intervalo_t primeiro_valor, intervalo_t segundo_valor);

// calcula a multiplicacao de dois numeros e retorna o intervalo que o representa
intervalo_t multiplica(double menor, double maior);

// compara o intervalo passado como parâmetro com o intervalo resultado, atualizando o intervalo 'resultado' caso necessário
void comparaValor(intervalo_t *resultado, intervalo_t aux);

// calcula e retorna a multiplicacao de dois intervalos 
intervalo_t multiplicacao(intervalo_t primeiro_valor, intervalo_t segundo_valor);

// calcula e retorna a divisao de dois intervalos 
intervalo_t divisao(intervalo_t primeiro_valor, intervalo_t segundo_valor);

// calcula e retorna a potenciacao de um intervalo de acordo com o expoente passado como parâmetro
intervalo_t potenciacao(intervalo_t valor, int expoente);

#endif