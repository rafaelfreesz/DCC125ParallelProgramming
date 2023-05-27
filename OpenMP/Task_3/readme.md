# TASK 3

Leia, entenda e rode os códigos omp_odd_even1 e omp_odd_even2. (para ordenação).
Explique a diferença dos dois códigos.

Compare o desempenho dos dois códigos paralelos.
Qual o código paralelo mais rápido?

Explique por que.

## SOLUÇÃO

No código presente em omp_odd_even1.c, dois paralell for são responsáveis por distribuir o vetor entre threads em cada fase. O problema neste método se dá ao excesso de forks e joins, necessários a cada iteração do loop.

No código presente em omp_odd_even2.c, a diretiva paralell é inserida fora do laço externo, mantendo puramente as diretivas "# pragma omp for " nos laços internos. Este recurso permite que as k iterações necessárias dos laços internos sejam feitas mantendo os mesmos threads, evitando forks and joins.

Diante do preposto, estima-se que o omp_odd_even2. seja mais otimizado 
que o omp_odd_even1.c.

A tabela a seguir demonstra os resultados de tempo:

Resultado:

Com esperado, os runtimes do omp_odd_even2 são mais otimizados na maioria dos casos. A otimização é mais evidente em instâncias grandes, bem como para maiores quantidade de threads. Isso de dá pelo fato de o programa omp_odd_even1 demandar excesso de forks e joins de forma diretamente proporcional a quantidade de threads e o tamanho de entrada do problema.


