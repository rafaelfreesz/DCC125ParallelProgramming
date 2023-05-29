# TASK 4

Leia, entenda e rode o código omp_mat_vect (codigo para multiplicacao de matriz vetor).
Compare o desempenho desse código openmp usando diferentes tamanhos de matriz, semelhante ao slide do autor (8x 8000000, 8000 x 8000, 8000000 x 8). Mude sempre os tamanhos da matriz e o número de multiplicações matriz-vetor para conseguir tempos paralelos próximos de 1 seg.

Por que existe diferença (dica false sharing)?
Tente usar o gprof para ver o que está acontecendo nas caches (https://linuxhint.com/gprof-linux-command/).

## SOLUÇÃO

Foram executados os casos Static, Dynamic e Guide.
O tamanho de bloco n foi testado com os valores 1, 2 e 10.
Foram executadas estas combinações com o tamanhos de entrada de 3200, 6400, 128000, 256000, 512000, e com 1, 2, 4, 8 e 16 threads.
Foi executada separadamente a configuração em blocos.

A tabela a seguir demonstra os resultados de tempo:

![text](https://github.com/rafaelfreesz/DCC125ParallelProgramming/blob/master/OpenMP/Task_4/stats.jpg)

Resultado:

A melhor combinação dentre as demais foi o scheduling definido como statyc com tamanho de bloco 10, atingindo o melhor tempo em 10 casos;
A pior combinação foi resultados foi o scheduling em blocos, atindindo o pior tempo em 18 casos.

De forma mais detalhada, segue o score das configurações:

![text](https://github.com/rafaelfreesz/DCC125ParallelProgramming/blob/master/OpenMP/Task_4/stats2.jpg)

Resultados detalhados estão no arquivo [Task4_Statistics_OMP.ods](https://github.com/rafaelfreesz/DCC125ParallelProgramming/blob/master/OpenMP/Task_4/Task4_Statistics_OMP.ods)
