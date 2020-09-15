#include <stdio.h>
#include <assert.h>
#include <pthread.h>

#ifndef __barrier_h
#define __barrier_h

typedef struct _barrier_t {
  unsigned int    expected; // Expected number of threads in barrier
  unsigned int    count;    // Number of threads that are waiting
  unsigned int    awaken;   // Number of threads awaken
  pthread_mutex_t mutex;    // Barrier mutex
  pthread_cond_t  cond;     // Condition variable
  char*           name;     // Name (for debugging)
}barrier_t;

void init_barrier(barrier_t* barrier, 
                  const unsigned int expected,
                  char *name);

void wait_in_barrier(barrier_t* barrier);

void destroy_barrier(barrier_t* barrier);

#endif