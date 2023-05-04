/* Disciplina: Computacao Concorrente */
/* Aluno: Breno Curvello dos Santos Breves */
/* Laboratório: 5 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NTHREADS  5
/* Variaveis globais */
int x = 0;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;
pthread_cond_t terceira;
pthread_cond_t ultimas;
// Thread A
void *A (void *t) {
  printf("Oi José!\n");
  pthread_mutex_lock(&x_mutex);
  x++;
  if (x==2) {
      pthread_cond_signal(&terceira);
  }
  pthread_mutex_unlock(&x_mutex);

  pthread_exit(NULL);
}
//Thread B
void *B (void *t) {
  printf("Oi Maria!\n");
  pthread_mutex_lock(&x_mutex);
  x++;
  if (x==2) {
      pthread_cond_signal(&terceira);
  }
  pthread_mutex_unlock(&x_mutex);

  pthread_exit(NULL);
}
//Thread C
void *C (void *t) {
  pthread_mutex_lock(&x_mutex);
  if (x < 2) { 
     pthread_cond_wait(&terceira, &x_mutex);
  }
  printf("Sente-se por favor.\n");
  x++;
  pthread_cond_broadcast(&ultimas);
  pthread_mutex_unlock(&x_mutex);
  pthread_exit(NULL);
}
//Thread D
void *D (void *t) {
  pthread_mutex_lock(&x_mutex);
  if (x <3) {
     pthread_cond_wait(&ultimas, &x_mutex);
  }
  pthread_mutex_unlock(&x_mutex); 
  printf("Até mais José!\n");
  pthread_exit(NULL);
}
//Thread E
void *E (void *t) {
  pthread_mutex_lock(&x_mutex);
  if (x <3) {
     pthread_cond_wait(&ultimas, &x_mutex);
  }
  pthread_mutex_unlock(&x_mutex);
  printf("Até mais Maria!\n");
  pthread_exit(NULL);
}

/* Funcao principal */
int main(int argc, char *argv[]) {
  int i;
  pthread_t threads[NTHREADS];

  /* Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao */
  pthread_mutex_init(&x_mutex, NULL);
  pthread_cond_init (&x_cond, NULL);

  /* Cria as threads */
  pthread_create(&threads[0], NULL, A, NULL);
  pthread_create(&threads[1], NULL, B, NULL);
  pthread_create(&threads[2], NULL, C, NULL);
  pthread_create(&threads[3], NULL, D, NULL);
  pthread_create(&threads[4], NULL, E, NULL);
  /* Espera todas as threads completarem */
  for (i = 0; i < NTHREADS; i++) {
    pthread_join(threads[i], NULL);
  }
  /* Desaloca variaveis e termina */
  pthread_mutex_destroy(&x_mutex);
  pthread_cond_destroy(&x_cond);
}
