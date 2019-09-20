#include <stdio.h>
#include <stdlib.h>

#include "parse.h"
#include "init.h" // for init_uniform
#include "rdtsc.h"

void quicksort(double *A, long A_len)
{
  double pivot;
  long ind_bot = 0;
  long ind_top = A_len-1;
  double temp;
  if (A_len > 2) {
    // choose a pivot at "random"
    pivot = A[A_len/2];
    // find the first element that is not less than the pivot
    while (A[ind_bot] < pivot) {
      ++ind_bot;
    }
    // find the last element that is not greater than the pivot
    while (A[ind_top] > pivot) {
      --ind_top;
    }
    // swap elements until the first not less than the pivot is after the last
    // that is not greater than the pivot
    while (ind_bot < ind_top) {
      temp = A[ind_bot];
      A[ind_bot] = A[ind_top];
      A[ind_top] = temp;
      // move on to new elements
      ++ind_bot;
      --ind_top;
      // find the next swapable elements
      while (A[ind_bot] < pivot) {
	++ind_bot;
      }
      while (ind_top && A[ind_top] > pivot) {
	--ind_top;
      }  
    }
    // RECURSE:
    // at this point, all elements before ind_bot must be pivot or less
    quicksort(A,ind_bot);
    // and all elements at or after ind_bot must be pivot or greater
    quicksort(A+ind_bot,A_len-ind_bot);
  }
  // explicit handler for short A_len
  else if (A_len > 1) {
    if (A[0] > A[1]) {
      temp = A[0];
      A[0] = A[1];
      A[1] = temp;
    }
  }
}


int main(int argc, char **argv)
{
  struct args args;
  double *A;
  ticks_t lasttick;
  long ind;

  // argument parsing via parse.h
  parse_args(&args, argc, argv);

  // initialize array
  A = malloc(sizeof(double) * args.array_len);
  init_uniform(A,args.array_len);

  // quicksort
  lasttick = rdtsc();
  quicksort(A,args.array_len);
  lasttick = rdtsc() - lasttick;
  printf("Sorted in %llu ticks\n",lasttick);

  // validate
  for (ind=1; ind<args.array_len; ++ind) {
    // check for out of order
    if (A[ind] < A[ind-1]) {
      fprintf(stderr,"elements %ld and %ld are in the wrong order\n",ind-1,ind);
      break;
    }
  }

  free(A);
  return 0;
}
