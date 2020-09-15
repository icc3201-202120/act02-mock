#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include "rand.h"

void initrandarray(long* array, int sz, long maxval)
{
  long* p = array;
  for(; p < array + sz; p++) {
    *p = random_at_most(maxval);
  }
}

void printarray(long* array, int sz) 
{
  long* p = array;
  for(; p < array + sz; p++) {
    printf("%lu\n", *p);
  }
}