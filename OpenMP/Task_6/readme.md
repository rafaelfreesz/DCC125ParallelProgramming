# TASK 6

a) Mude o código omp_sin_sum de forma que a função f(i) aumente o tempo de execução com i. Ex.: f(i) = i!.

Teste o desempenho dele para diferentes schedules (Static, Dynamic, Guided) e tamanhos de blocos (1, 2, 10, etc.).


b) Mude o código omp_sin_sum de forma que a função f(i) dependa de um número aleatório k. Por exemplo, f(i) = k!. 
Implemente a geração do número aleatório usando rand() padrão. Observe que o código paralelo não gera o mesmo resultado do sequencial. Ou seja, o código paralelo não funciona pois usa uma função que não é thread safe!


Altere esse código usando uma versão de gerador de número aleatório preparada para multi_thread. Ex.: rand_r.
Observe que agora o código paralelo está funcionando.


Teste o desempenho dele para diferentes schedules (Static, Dynamic, Guided) e tamanhos de blocos (1, 2, 10, etc.).

OBS.:

Outras funções para gerar números aleatórios são bastante utilizadas:

struct drand48_data randBuffer;

       srand48_r(myrank, &randBuffer);
       drand48_r(&randBuffer, &r);

## SOLUÇÃO

Ambiente de execução:
Processador AMD Ryzen 5 2600 3.4Ghz, 6 cores e 12 threads;
Memória DDR4 16.0GB.

Foram executados os casos Static, Dynamic e Guide.
O tamanho de bloco n foi testado com os valores 1, 2, 4 e 10.
Foram executadas estas combinações com o tamanhos de entrada de 20000, 40000, 80000, 160000, e 320000 com 1, 2, 4, 8 e 16 threads.
Foi executada separadamente a configuração em blocos.

### a)
#### Considerando a distribuição em blocos:
A tabela a seguir demonstra os resultados de tempo:

![text](https://github.com/rafaelfreesz/DCC125ParallelProgramming/blob/master/OpenMP/Task_6/stats_a_1.jpg)

Resultado:

Os dois melhores resultados são dynamic,2, dynamic,4 e guided,1. Vale ressaltar o bom desempenho de todas as configurações dynamic,x, e guided,x para x={1,2,4,10}

A divisão em blocos foi a pior na maioria dos casos.

De forma mais detalhada, segue o score das configurações:

![text](https://github.com/rafaelfreesz/DCC125ParallelProgramming/blob/master/OpenMP/Task_6/stats_a_2.jpg)

#### Donsiderando a distribuição em blocos:

A tabela a seguir demonstra os resultados de tempo:

![text](https://github.com/rafaelfreesz/DCC125ParallelProgramming/blob/master/OpenMP/Task_6/stats_a_3.jpg)

Resultado:

Os dois melhores resultados são dynamic,2, dynamic,4 e guided,1. Vale ressaltar o bom desempenho de todas as configurações dynamic,x, e guided,x para x={1,2,4,10}

os piores casos foram dynamic,1, static,10, e static,1.

De forma mais detalhada, segue o score das configurações:

![text](https://github.com/rafaelfreesz/DCC125ParallelProgramming/blob/master/OpenMP/Task_6/stats_a_4.jpg)


Resultados detalhados estão no arquivo [Task6_a_Statistics_OMP.ods](https://github.com/rafaelfreesz/DCC125ParallelProgramming/blob/master/OpenMP/Task_6/Task6_a_Statistics_OMP.ods)

### b)

Foram realizadas execuções utilizando rand() e rand_r() considerando 1, 2 e 4 threads, com entradas de tamanho 100000000.

Como pode ser observado, a função rand() não é capaz de fornecer desempenho adequadao para parametrização;
A função rand_r() é thread safety, fornecendo o desempenho esperado.

![text](https://github.com/rafaelfreesz/DCC125ParallelProgramming/blob/master/OpenMP/Task_6/stats_b.jpg)
