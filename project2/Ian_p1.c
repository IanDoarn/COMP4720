#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

void* randN(void* args) {

  double x = ( (double)rand() / (double)RAND_MAX );
  double y = ( (double)rand() / (double)RAND_MAX );

  printf("(%f, %f)\n", x, y );

}


int main() {

  pthread_t tid[5];

  int i = 0;
  int error;
  srand(time(NULL));

  while (i < 5) {
    error = pthread_create(&(tid[i]), NULL, &randN, NULL);
    i++;
  }

  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);
  pthread_join(tid[2], NULL);
  pthread_join(tid[3], NULL);
  pthread_join(tid[4], NULL);

  return 0;

}