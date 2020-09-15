#ifndef __util_h
#define __util_h

void initrandarray(long* array, int sz, long maxval);
void printarray(long* array, int sz);

inline long minvalue(long* values, int sz) 
{
  long *p = values;
  long min = *p;
  for (; p < values + sz; p++) {
    if (*p < min) {
      min = *p;
    }
  }
  return min;
}

inline long maxvalue(long* values, int sz) 
{
  long *p = values;
  long max = *p;
  for (; p < values + sz; p++) {
    if (*p > max) {
      max = *p;
    }
  }
  return max;
}

#endif