# EP-04 - Otimização de Código utilizando Unroll & Jam com Blocking
## Leonardo Becker de Oliveira - GRR20211779
## Lucas Néia Torres - GRR20210570

### Limitações
As possíveis limitações apresentadas pelo programa se dão justamente por não aceitar tamanhos de matriz não múltiplos de 4, pelo fato do fator de blocking e do fator de unroll serem 4. Entretanto, para fins de análise dos algoritmos, se faz necessário.

### Modo de usar
Para rodar apenas o programa com algum tamanho específico, dê make e ./matmult <ordem>
Para rodar com as métricas do likwid e valores de teste definidos no enunciado, utilize o comando ./testes.sh.
Para plotar gráfico por gráfico, dê gnuplot plot<métrica>
Para plotar os gráficos com base nas métricas do likwid, dê ./plota.sh