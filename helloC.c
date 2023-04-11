#include <stdio.h>                                                                //Includes.
#include <pthread.h>                                                              
int vector[10000];                                                                //Vetor de 10000 posições em escopo global
void *mult(void *thread_id) {                                                     //Mesma função do primeiro exercício apenas com o nome alterado
  for ( int i = (long)thread_id ; i < 10000 ; i+=2){                              //Laço para multiplicação de 2 em 2 para ser executado de forma intercalada pelas duas threads
    vector[i]*=2;                                                                 //Multiplicação
    printf("%ldº thread multiplicou o valor %i\n",(long)thread_id, vector[i]);    //Print no terminal para verificação das execuções
  }
  pthread_exit(NULL);
}

int main() {
  pthread_t threads[2];                                                           //Vetor para guardar o id das threads
  for (int i = 0 ; i < 10000 ; i++){                                              //Inicialização de valores consecutivos no vetor  
    vector[i]= i;
  }
  for (long i = 0; i < 2; i++) {                                                  //Criação das threads
    pthread_create(&threads[i], NULL, mult, (void *) i);
  }

  for (int i = 0; i < 2; i++) {                                                   //Aguradar a finalização das threads
    pthread_join(threads[i], NULL);
  }

  for (int i = 0 ; i < 10000 ; i++){                                              //Verificação final
    if(vector[i] != i*2){
      printf("\nOPA\n\n");
      return 0;                                                                   //Print com return caso encontre algo errado com os valores esperados
    }
  } 
  printf("Tudo certo!\n");                                                        //Print indicando tudo certo caso passe na verificação                                                       
  return 0;
}
