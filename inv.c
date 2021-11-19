#include <stdio.h>
#include <stdlib.h>

double determinant(
  double const * const * const matrix,
  int const dim
);

void inv_mat(
  double const * const * const mat,
  int const dim,
  double * * inv
) {
  double det = determinant(
    (double const * const * const) mat,
    dim
  );

  double * * eliminated = (double * *) calloc(dim-1, sizeof(double *));
  for (int i = 0; i < dim; ++i) {
    eliminated[i] = (double *) calloc(dim, sizeof(double));
  }

  int sign = 1;
  for (int i = 0; i < dim; ++i) {
    for (int j = 0; j < dim; ++j) {

      for (int r = 0; r < dim; ++r) {
        if (r==i) continue;
        for (int c = 0; c < dim; ++c) {
          if (c==j) continue;
          const int row = r<i? r : r-1;
          const int col = c<j? c : c-1;
          eliminated[row][col] = mat[r][c];
        }
      }

      double el_det = determinant(
        (double const * const * const) eliminated,
        dim-1
      );

      inv[j][i] = sign * el_det / det;
      sign *= -1;

    }
  }
}

