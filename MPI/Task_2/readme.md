# TASK 2

Modificar o Código mpi_trap3 para aceitar valores de n tal que n%comm_sz!=0;
Rodar no modo normal e com a diretiva de otimização -O3;
Analisar resultados, medir runtime, desvio padrão de tempo, speedup e eficiência.

## SOLUÇÃO

A definição dos limites foi modificado da forma original:
```c
   local_a = a + my_rank*local_n*h;
   local_b = local_a + local_n*h;
   local_int = Trap(local_a, local_b, local_n, h);
```
de forma a permitir a distribuição balanceada entre os processos quando n%comm_sz!=0:

```c
int buildLimits(int my_rank, double* local_a, double* local_b, double* before_b, int a,double h, int comm_sz, int n){
   int local_n = n/comm_sz;

if(my_rank==0){
      *local_a = a + my_rank* local_n*h;
      *local_b = *local_a + local_n*h;

   }else{
      MPI_Recv(before_b,1,MPI_DOUBLE,my_rank-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      *local_a=*before_b;
      *local_b=*local_a+local_n*h;

      if(my_rank>=comm_sz-n%comm_sz){
         local_n++;
         *local_b+=h;
      }

   }

   if(my_rank!=(comm_sz-1)){
      MPI_Send(&local_b,1,MPI_DOUBLE,my_rank+1,0,MPI_COMM_WORLD);
   }

   return local_n;

}
```

Foram realizadas execuções de tamanho n={1000, 2000, 4000, 8000, 16000}, com as quantidades de processos m={1,2,4,8,16}.

### Para a execução normal

A tabela abaixo apresenta os runtimes, speedups e eficiências;

![text](https://github.com/rafaelfreesz/DCC125ParallelProgramming/blob/master/MPI/Task_2/Stats_1.jpg)

A tabela a seguir apresenta os valores médios e desvio padrão dos resultados

![text](https://github.com/rafaelfreesz/DCC125ParallelProgramming/blob/master/MPI/Task_2/Stats_2.jpg)

### Para a execução com o parâmetro -O3

A tabela abaixo apresenta os runtimes, speedups e eficiências;

![text](https://github.com/rafaelfreesz/DCC125ParallelProgramming/blob/master/MPI/Task_2/Stats_1_O3.jpg)

A tabela a seguir apresenta os valores médios e desvio padrão dos resultados

![text](https://github.com/rafaelfreesz/DCC125ParallelProgramming/blob/master/MPI/Task_2/Stats_2_O3.jpg)


## Conclusão:

Em ambas exeuções foi possível observar corretude nos resultados devido aos desvio padrão zero dos resultados;
Para a execução normal observa-se efciência com pouca variação ao acrescentar mais processadores. Pode-se afirmar que o algoritmo é proximo de uma escalabilidade forte.
Observa-se, por fim, uma melhora significativa do desempenho do algoritmo no uso do parâmetro -O3, de modo que, mantendo os mesmos parâmetros de entrada, não é possível analisar sua escalabilidade.






