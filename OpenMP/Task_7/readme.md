# TASK 7

Suponha que joguemos dardos aleatoriamente em um alvo de dardos quadrado, cujo alvo está no origem e cujos lados têm 2 m de comprimento.
Suponha também que há um círculo inscrito no alvo de dardos quadrado. O raio do círculo é de 1 m e sua área é π m quadrados. Se os pontos atingidos pelos dardos estão uniformemente distribuídos (e sempre acertamos o quadrado), então o número de dardos que acertam dentro do círculo deve satisfazer aproximadamente a equação

número no círculo / número total de jogadas = π / 4,

já que a razão entre a área do círculo e a área do quadrado é π / 4.


Podemos usar esta fórmula para estimar o valor de π com um Gerador de número aleatório:

    número no círculo = 0;

    para (lançamento = 0; lançamento <número de lançamentos; lançamento ++) {


        x = duplo aleatório entre -1 e 1;
        y = duplo aleatório entre -1 e 1;


        distância ao quadrado = x ∗ x + y ∗ y;


       if (distância ao quadrado <= 1) número no círculo ++;


    }  

    estimativa de pi = 4 ∗ número no círculo / ((double) número de lançamentos);

Isso é chamado de método “Monte Carlo”, uma vez que usa aleatoriedade (os lançamentos de dardo).

Escreva um programa OpenMP que use um método de Monte Carlo para estimar π.

O número total de lançamentos é um parâmetro do código. Use uma cláusula de redução para encontrar o número total de dardos atingindo dentro do círculo. Imprima o resultado depois de executar o bloco paralelo.
Você pode querer usar int long long para o número de acertos no círculo e o número de jogadas, uma vez que ambos podem ter que ser muito grande para obter uma estimativa razoável de π.

Atenção lembre-se do problema “thread safe”.

Rode com diferentes valores de “número de lançamentos”  e threads p. Monte uma tabela com os speedups e eficiencias.
Use as funcoes abaixo:

struct drand48_data randBuffer;

       srand48_r(seed, &randBuffer);
       drand48_r(&randBuffer, &r);

## SOLUÇÃO

Foram executadas as quantidades de lançamentos n, n={500000000, 1000000000, 2000000000, 4000000000, 8000000000}, com as quantidades de thread m={1,2,4,8,16}.

A tabela abaixo apresenta os runtimes, speedups e eficiências;

![text](https://github.com/rafaelfreesz/DCC125ParallelProgramming/blob/master/OpenMP/Task_7/Stats_1.jpg)

A tabela a seguir apresenta os valores médios de pi

![text](https://github.com/rafaelfreesz/DCC125ParallelProgramming/blob/master/OpenMP/Task_7/Stats_2.jpg)

Por fim, a tabela a seguir apresenta os valores médios de acerto

![text](https://github.com/rafaelfreesz/DCC125ParallelProgramming/blob/master/OpenMP/Task_7/Stats_3.jpg)






