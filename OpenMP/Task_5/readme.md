# TASK 4

Leia, entenda e rode o código omp_mat_vect (codigo para multiplicacao de matriz vetor).
Compare o desempenho desse código openmp usando diferentes tamanhos de matriz, semelhante ao slide do autor (8x 8000000, 8000 x 8000, 8000000 x 8). Mude sempre os tamanhos da matriz e o número de multiplicações matriz-vetor para conseguir tempos paralelos próximos de 1 seg.

Por que existe diferença (dica false sharing)?
Tente usar o gprof para ver o que está acontecendo nas caches (https://linuxhint.com/gprof-linux-command/).

## SOLUÇÃO

É possível observar uma depreciação no desempenho, principalmente nas configurações 8x8000000 e 8000000x8.

Na primeira existe uma grande quantidade de false sharing, onde boa parte do conteudo das linhas de cash carregadas para cada thread compartilha conteúdo com a demais, invalidando-as no caso de atualização. Existe tambem uma grande quantidade de read-miss, pelo fato de o vetor x ser grande.

A segunda contem uma quantidade consideraval de write-miss, pelo fato do tamanho vetor resultante.




![text](https://github.com/rafaelfreesz/DCC125ParallelProgramming/blob/master/OpenMP/Task_5/stats.jpg)

![text](https://github.com/rafaelfreesz/DCC125ParallelProgramming/blob/master/OpenMP/Task_4/stats2.jpg)
