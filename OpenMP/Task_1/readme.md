# TASK 4

Analisar runtime, speedup e eficiência da soma de vetores.

## SOLUÇÃO


Foram realizadas execuções de tamanho n={160, 320, 640, 1280, 2560}, com as quantidades de processos m={1,2,4,8,16}.


A tabela abaixo apresenta os runtimes, speedups e eficiências;

![text](https://github.com/rafaelfreesz/DCC125ParallelProgramming/blob/master/OpenMP/Task_1/Stats.jpg)


## Conclusão:

É possível observar a pouca variação de eficiência ao aumentar na mesma proporção o número de processos e o tamanho da entrada. Logo, o programa é fracamente escalável.