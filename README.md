# EP-01 - Representação Numérica e Erros
## Leonardo Becker de Oliveira - GRR20211779
## Lucas Néia Torres - GRR20210570

### Limitações
Claro, peço desculpas pela confusão. Aqui estão os casos em que o seu programa de aritmética intervalar poderia não funcionar corretamente:

    Divisão por Zero: Se você encontrar uma operação de divisão em que o intervalo do denominador inclui o zero, o seu programa deve lidar com isso corretamente. A divisão por zero é indefinida na aritmética convencional e pode levar a resultados incorretos ou infinitos.

    Operações Envolvendo Intervalos de Largura Zero: Se algum dos intervalos que você utiliza tiver largura zero (ou seja, limites inferior e superior são iguais), o seu programa pode produzir resultados incorretos. Isso ocorre porque a aritmética intervalar depende muito da largura do intervalo para representar incerteza ou erro.

    Faixa Extrema de Valores Exponenciais: Embora você tenha testado o seu programa com valores exponenciais grandes, é válido verificar se o seu programa lida corretamente com valores extremamente grandes ou pequenos. A aritmética de ponto flutuante pode perder precisão com números extremamente grandes ou pequenos.

    Manuseio Incorreto de Arredondamento: A aritmética intervalar exige um manuseio cuidadoso dos modos de arredondamento e resultados intermediários. O arredondamento incorreto pode levar a imprecisões nos cálculos de intervalo.

    Operações Não Associativas: A aritmética intervalar assume que as operações são associativas, o que pode não ser verdade para todas as funções matemáticas. Certifique-se de que o seu programa considere esses casos corretamente.

    Funções Além das Operações Básicas: Se o seu programa precisar lidar com funções além das operações aritméticas básicas, você deverá implementá-las cuidadosamente para garantir que as propriedades da aritmética intervalar sejam mantidas.

    Underflow e Overflow: Dependendo da implementação das operações de aritmética intervalar, você pode encontrar problemas de underflow ou overflow que poderiam afetar a precisão dos resultados.

    Manuseio Inadequado de Precisão e Erros de Arredondamento: Devido à natureza da aritmética de ponto flutuante, erros de precisão e arredondamento podem se acumular ao longo de operações repetidas. O seu programa deve ser capaz de lidar e considerar esses erros.

    Manuseio de NaN: Se alguma de suas operações resultar em valores NaN (Não é um Número), certifique-se de que o seu programa trate esses casos adequadamente.

Para lidar com esses possíveis problemas, é essencial testar minuciosamente o seu programa com uma ampla variedade de entradas, incluindo casos limite, valores extremos e expressões complexas. Além disso, considere implementar salvaguardas e verificações para lidar com a divisão por zero, intervalos de largura zero e outros casos excepcionais.
