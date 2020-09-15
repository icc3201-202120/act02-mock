#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include "common_threads.h"
#include "barrier.h"
#include "rand.h"
#include "util.h"

struct threadargs {               // Arguments for thread execution
  int                 num;        // Number of thread
  int                 incr;       // Number of iterations in loop (part 1)
  barrier_t*          pbarrier;   // Barrier instance
  volatile int*       pcountera;  // Counter A (part 1)
  volatile int*       pcounterb;  // Counter B (part 1)
  pthread_mutex_t*    plock;      // Lock 

  long*               pvalues;    // Array with long values (part 2)
  int*                pszvalues;  // Size of array (part 2)
  int*                pready;     // Ready flag (part 2) 
  pthread_cond_t*     pcond;      // Condition variable (part 2)
};

void part2(struct threadargs* args) {  
  printf("Thread '%d' starting part 2\n", args->num);
  
  // TODO
  // Thread 1 (see 'else' block) must initialize the array
  // args->pvalues BEFORE threads 2 and 3 access it to determine 
  // minimum and maximum values:
  if (args->num > 1) {
    if (args->num == 2) {
      long minval = minvalue(args->pvalues, *(args->pszvalues));
      printf("[Thread %d] Minimum: '%ld'\n", args->num, minval);
    }
    else if(args->num == 3) {
      long maxval = maxvalue(args->pvalues, *(args->pszvalues));
      printf("[Thread %d] Maximum: '%ld'\n", args->num, maxval);
    }
  }
  else { // Thread 1
    // TODO
    // Use args->pcond, args->pready and args->plock to 
    // ensure that this thread is done initializing the
    // array before threads 2 and 3 attempt to read from
    // it.
    initrandarray(args->pvalues, *(args->pszvalues), 1000000);
  }
}

void* part1(void* arg) {
  struct threadargs* args = (struct threadargs*)arg;
  int i;

  printf("Thread '%d' starting part 1\n", args->num);

  for (i = 0; i < args->incr; i++) {
    (*args->pcountera)++;
  }

  // Using the barrier for the first time
  wait_in_barrier(args->pbarrier);

  for (i = 0; i < args->incr; i++) {
    Mutex_lock(args->plock);
    (*args->pcounterb)++;
    Mutex_unlock(args->plock);
  }

  printf("Thread '%d' finished part 1\n", args->num);
  
  // See if barrier can be reused!
  wait_in_barrier(args->pbarrier);

  if (args->num == 1) {
    printf("[Thread %d] counter A: '%d' counter B: '%d'\n",
      args->num, *(args->pcountera), *(args->pcounterb));    
  }

  // TODO: Uncomment the next line to proceed to part 2.
  // part2(args);

  return arg;
}

int main(int argc, char** argv) {
  int             i;                // Loop counter
  const int       numthreads = 3;   // Number of threads to be created
  barrier_t       barrier;          // Barrier
  pthread_mutex_t lock;             // Lock
  volatile int    countera = 0, 
                  counterb = 0;     // Counters (part 1)

  long*           pvalues;          // Array with long values (part 2)
  int             szvalues;         // Size of array (part 2)
  int             ready;            // Ready flag (part 2) 
  pthread_cond_t  cond;             // Condition variable (part 2) 

  Mutex_init(&lock);
  init_barrier(&barrier, numthreads, "barrier");
  sgenrand(123123);

  pthread_t* threads = malloc(sizeof(pthread_t)*numthreads);
  
  szvalues = 1000;
  pvalues = malloc(sizeof(long)*szvalues);

  ready = 0;
  Cond_init(&cond);
  
  for (i = 0; i < numthreads; i++) {
    struct threadargs* ta = malloc(sizeof(struct threadargs));

    ta->pbarrier = &barrier;
    ta->pcountera = &countera;
    ta->pcounterb = &counterb;
    ta->num = i + 1;
    ta->plock = &lock;
    ta->incr = 10000;

    ta->pvalues = pvalues;
    ta->pszvalues = &szvalues;
    ta->pcond = &cond;
    ta->pready = &ready;

    Pthread_create(&threads[i], NULL, part1, ta);
  }

  for (i = 0; i < numthreads; i++) {
    struct threadargs* ta = NULL;
    Pthread_join(threads[i], (void**)&ta);
    free(ta);
  }

  destroy_barrier(&barrier);
  Mutex_destroy(&lock);
  Cond_destroy(&cond);

  free(threads);
  free(pvalues);

  exit(0);
}