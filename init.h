#include <stdlib.h>
#include <stdio.h>

void init_uniform(double *A, long A_len)
{
  srand48(1337);
  while (A_len--) {
    A[A_len] = drand48();
  }
}
