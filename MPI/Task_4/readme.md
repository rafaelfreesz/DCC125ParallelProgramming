# TASK 4

Analisar runtime, speedup e eficiência da soma de vetores.

## SOLUÇÃO


Foram realizadas execuções de tamanho n={800, 1600, 3200, 6400, 128000}, com as quantidades de processos m={1,2,4,8,16}.


A tabela abaixo apresenta os runtimes, speedups e eficiências;

![text](https://github.com/rafaelfreesz/DCC125ParallelProgramming/blob/master/MPI/Task_4/Stats_1.jpg)


## Conclusão:

É possível observar a pouca variação de eficiência ao aumentar na mesma proporção o número de processos e o tamanho da entrada. Logo, o programa é fracamente escalável.