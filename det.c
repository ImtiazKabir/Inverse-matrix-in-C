#include <stdlib.h>
#include <stdbool.h>

void swap(int *x, int *y) {
  int t = *x;
  *x = *y;
  *y = t;
}

bool next_perm(int const n, int * a) {
  int k = n-2;
  while (a[k] >= a[k+1]) {
    k -= 1;
  }
  if (k < 0) {
    return false;
  }

  int l = n-1;
  while (a[k] >= a[l]) {
    l -= 1;
  }

  swap(a+k, a+l);
  for (int i=k+1,j=n-1; i<j; ++i,--j) {
    swap(a+i, a+j);
  }
  return true;
}

double determinant(
  double const * const * const matrix,
  int const dim
) {
  int arr[dim];
  for (int i = 0; i < dim; ++i) {
    arr[i] = i;
  }

  double det = 0.0;
  int count = 0;
  do {
    double term = 1.0;
    for (int i = 0; i < dim; ++i) {
      term *= matrix[i][arr[i]];
    }
    if (count == 0 || count == 3) {
      det += term;
    } else {
      det -= term;
    }
    count = (count+1) % 4;
  } while (next_perm(dim, arr) == true);
  return det;
}
