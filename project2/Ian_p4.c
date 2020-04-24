#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int C = 0;
pthread_mutex_t lock;

void* randN(void* args) {

  pthread_mutex_lock(&lock);

  unsigned long k = 0;
  for(k = 0; k < 100001; k++) {
    double x = ( (double)rand() / (double)RAND_MAX );
    double y = ( (double)rand() / (double)RAND_MAX );

    if(sqrt( pow(x, 2.0) + pow(y, 2.0) ) > 1) {
      //
    }
    else {
      //
      C++;
    }
  }

  pthread_mutex_unlock(&lock);

}


int main() {

  pthread_t tid[5];

  int i = 0;
  int error;
  srand(time(NULL));

  if(pthread_mutex_init(&lock, NULL) != 0)  {
    printf("\nBruh, mutex broken");
    return 1;
  }

  while (i < 5) {
    error = pthread_create(&(tid[i]), NULL, &randN, NULL);
    i++;
  }

  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);
  pthread_join(tid[2], NULL);
  pthread_join(tid[3], NULL);
  pthread_join(tid[4], NULL);

  pthread_mutex_destroy(&lock);

  printf("Final value of C = %d\n", C);

  double pi = (4*C) / 500000.0f;
  printf(" PI = %.6f\n", pi);

  return 0;

}