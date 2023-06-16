# TASK 3

Mudar o Trap3 para
1)Substituir a funcao f por uma funcao de computacao heterogenea, ex. fatorial.
2)testar o speedup, eficiencia, etc
3) Mudar a distribuicao para ciclica (local_a, etc.)
4)testar o speedup, eficiencia, etc

## SOLUÇÃO

Foram realizadas execuções de tamanho n={1600, 3200, 6400, 12800, 25600}, com as quantidades de processos m={1,2,4,8,16}.

### Para a execução normal

A tabela abaixo apresenta os runtimes, speedups e eficiências;

![text](https://github.com/rafaelfreesz/DCC125ParallelProgramming/blob/master/MPI/Task_3/Stats_1.jpg)

A tabela a seguir apresenta os valores médios e desvio padrão dos resultados

![text](https://github.com/rafaelfreesz/DCC125ParallelProgramming/blob/master/MPI/Task_3/Stats_2.jpg)

### Para a distribuição cíclica

A tabela abaixo apresenta os runtimes, speedups e eficiências;

![text](https://github.com/rafaelfreesz/DCC125ParallelProgramming/blob/master/MPI/Task_3/Stats_1_C.jpg)

A tabela a seguir apresenta os valores médios e desvio padrão dos resultados

![text](https://github.com/rafaelfreesz/DCC125ParallelProgramming/blob/master/MPI/Task_3/Stats_2_C.jpg)


## Conclusão:

Dada a computação heterogenea com função fatorial, é possível observar que, na execução normal, o aumento no número de processadores resulta em pouca ou nenhuma melhora no desempenho.

Na distribuição cíclica, é possivel observar uma melhora na eficiência em relação a execução anterior.

Em ambos os casos, os programas não são escaláveis.

Os resultados iguais com desvio padrão 0, ou proximos de 0, indicam a corretude dos resultados.







