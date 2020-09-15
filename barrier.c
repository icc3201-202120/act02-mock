#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "barrier.h"
#include "common_threads.h"

void init_barrier(barrier_t* barrier, 
                  unsigned int expected,
                  char *name) {
  barrier->expected = expected;
  barrier->name = name;
  barrier->count = 0;
  barrier->awaken = 0;

  Mutex_init(&barrier->mutex);
  Cond_init(&barrier->cond);
}

void destroy_barrier(barrier_t* barrier) {
  Mutex_destroy(&barrier->mutex);
  Cond_destroy(&barrier->cond);
}

void wait_in_barrier(barrier_t* barrier) {
  // TODO: Implement

  // 1. Use barrier->count to count the threads that
  // call on the given barrier.

  // 2. Use the condition variable barrier->cond and the
  // barrier->mutex lock as synchronization primitives
  // to implement the barrier behavior.

  // 3. When barrier->count == barrier->expected
  // all the threads sleeping on the condition variable
  // must resume execution past the barrier.

  // 4. The barrier should be reusable. That is,
  // barrier->count must be reset once all the 
  // threads in the barrier have been awaken. 
  // Use barrier->awaken to count the awaken
  // threads before resetting barrier->count.
}
