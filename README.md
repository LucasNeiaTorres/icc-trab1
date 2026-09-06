# icc-trab1 — exercícios de computação científica em C

> **Atenção ao nome:** apesar do `icc`, este repositório **não** é de introdução à
> ciência da computação. É uma coletânea de exercícios de **computação científica /
> métodos numéricos** em C — ponto flutuante, sistemas lineares, interpolação,
> integração numérica e otimização de desempenho de baixo nível medida com LIKWID.
> Trabalhos feitos em dupla ao longo da disciplina.

Cada pasta é um exercício independente, com seu próprio `makefile`/`Makefile` e um
`LEIAME`. Vários trazem, além da resolução, **medição de desempenho** (tempo, FLOPS,
cache) via [LIKWID](https://github.com/RRZE-HPC/likwid) e gráficos em gnuplot.

## Índice dos exercícios

| Pasta | Tema | O que faz |
|---|---|---|
| `GRR20211779_GRR20210570/` | **EP-01 — Representação numérica e erros** | Aritmética **intervalar** (soma, subtração, multiplicação, divisão de intervalos) para acompanhar a propagação do erro de ponto flutuante; comparação de floats por ULPs. |
| `ep03/` | **Interpolação polinomial** | Interpolação de **Newton** e de **Lagrange**; instrumentado com LIKWID (`FLOPS_DP`) para comparar versão sem e com `-O3`. |
| `ep04/` | **Otimização de multiplicação de matrizes** | Multiplicação matriz-vetor e matriz-matriz com **unroll & jam + blocking** (fatores de desenrolamento e de bloco = 4); mede tempo, FLOPS DP, energia e cache L2/L3 e plota os gráficos. |
| `ep05/` | **Integração numérica** | Integração por **Monte Carlo** comparada ao **método dos retângulos**; o LEIAME registra a comparação de convergência entre os dois. |
| `icc-ofc01/` | **Ajuste polinomial (versão base)** | Ajuste de curva por **mínimos quadrados** resolvendo o sistema normal por **eliminação de Gauss** com pivoteamento parcial, em aritmética intervalar. |
| `icc-ofc2/` | **Ajuste polinomial (versão otimizada)** | Mesmo problema do `icc-ofc01`, agora com foco em desempenho (`-O3 -mavx -march=native`, laço com desenrolamento) e um gerador de entrada próprio; inclui os gráficos de LIKWID e o relatório em PDF. A subpasta `semOtimizacao/` guarda a versão de referência para a comparação. |
| `icc-trab2/` | **Variantes de eliminação de Gauss** | Três variantes da **eliminação de Gauss** (tradicional, sem multiplicador e alternativa), cada uma marcada com LIKWID, comparadas por desempenho; inclui os logs `FLOPS_DP_*`. |

Não há EP-02 neste repositório.

## A linha que une os exercícios

Dois fios reaparecem em quase todos:

1. **Confiabilidade numérica** — o mesmo cálculo em ponto flutuante pode dar
   resultados diferentes conforme a ordem das operações e o condicionamento do
   sistema. A aritmética intervalar (EP-01, `icc-ofc*`) e a comparação por ULPs são a
   forma de **enxergar o erro**, não escondê-lo. Os LEIAME registram honestamente os
   limites: valores extremos viram `Infinity`/`NaN`, e matriz esparsa grande degrada
   a eliminação de Gauss.
2. **Desempenho medido, não presumido** — `ep03`, `ep04`, `icc-ofc2` e `icc-trab2`
   não afirmam que uma versão é mais rápida: elas **medem** com LIKWID (FLOPS, cache,
   energia) e comparam versão base contra versão otimizada, com os gráficos no
   repositório.

## Como compilar e rodar

Requisito comum: **gcc** (C99). Os exercícios com medição de desempenho dependem do
**LIKWID** instalado e de acesso para fixar a frequência da CPU — sem LIKWID, dá para
compilar e rodar a versão funcional, mas não reproduzir as métricas.

Cada pasta se compila e roda por conta própria; leia o `LEIAME` de dentro dela. Em
geral:

```bash
cd <pasta>
make            # ou: make -f makefile
./<programa> < entrada     # ver o LEIAME para os argumentos de cada um
```

Exemplos, conforme os LEIAME:

```bash
# ep05 — Monte Carlo
./monteCarlo n a b

# ep04 — multiplicação de matrizes (ordem múltipla de 4)
./matmult <ordem>

# icc-ofc01 — ajuste polinomial
./ajustePol < entrada > saida
```

Os scripts `executa.sh` / `testes.sh` / `teste.sh` de cada pasta rodam a bateria de
medição com LIKWID; eles alteram o *governor* da CPU (`performance`/`powersave`), o
que exige privilégio e um ambiente adequado.

## Limitações conhecidas (dos próprios LEIAME)

- Resultados fora da faixa representável em ponto flutuante saem como
  `Infinity`/`NaN`; a aritmética intervalar torna isso visível, não o corrige.
- `ep04` só aceita ordem de matriz **múltipla de 4**, por causa dos fatores de unroll
  e de blocking.
- Matriz esparsa grande degrada a precisão da eliminação de Gauss.
- A reprodução das métricas depende de LIKWID e de uma máquina com os contadores de
  desempenho acessíveis; os scripts referem um ambiente de laboratório específico.

## Estrutura

```
GRR20211779_GRR20210570/   EP-01 — aritmética intervalar e erros
ep03/                      interpolação de Newton e Lagrange
ep04/                      multiplicação de matrizes com unroll & jam + blocking
ep05/                      integração por Monte Carlo vs. retângulos
icc-ofc01/                 ajuste polinomial (mínimos quadrados) — base
icc-ofc2/                  ajuste polinomial otimizado + relatório e gráficos
icc-trab2/                 variantes de eliminação de Gauss
```
