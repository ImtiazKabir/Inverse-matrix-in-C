#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#define DELIM ","

void setup(
  FILE * * const in_file_p,
  char const * const in_path,
  int * const dim_p,
  double * * * const matrix,
  FILE * * const out_file_p,
  char const * const out_path
);

void clean_up(
  FILE * in_file,
  int const dim,
  double * * matrix,
  FILE * out_file,
  double * * inverse
);

void check_square_err(
  int const dim,
  double * * matrix
);

void parse_matrix(
  FILE * file,
  double * * * const matrix_p
);

void inv_mat(
  double const * const * const mat,
  int const dim,
  double * * inv
);

int main(
  int const argc,
  char const * const * const argv
) {

  // example usage
  if (argc != 3) {
    fprintf(stderr, "ERROR: Example usage: %s input.txt output.txt\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  FILE * mat_file;
  double * * matrix;
  int dim;

  FILE * inv_file;

  setup(&mat_file, argv[1], &dim, &matrix, &inv_file, argv[2]);

  // prepare the inverse matrix
  double * * inverse = (double * *) calloc(dim, sizeof(double *));
  for (int i = 0; i < dim; ++i) {
    inverse[i] = (double *) calloc(dim, sizeof(double));
  }

  inv_mat(
    (double const * const * const) matrix,
    dim,
    inverse
  );

  // output the inverse
  for (int i = 0; i < dim; ++i) {
    for (int j = 0; j < dim; ++j) {
      fprintf(inv_file, "%lf, ", inverse[i][j]);
    }
    fprintf(inv_file, "\n");
  }

  printf("DONE\n");

  clean_up(mat_file, dim, matrix, inv_file, inverse);

  return EXIT_SUCCESS;
}

void setup(
  FILE * * const in_file_p,
  char const * const in_path,
  int * const dim_p,
  double * * * const matrix_p,
  FILE * * const out_file_p,
  char const * const out_path
) {
  // opening the file
  *in_file_p = fopen(in_path, "r");
  if (*in_file_p == NULL) {
    perror(NULL);
    fprintf(stderr, "Could not find %s\n", in_path);
    exit(EXIT_FAILURE);
  }


  // parsing the matrix
  parse_matrix(*in_file_p, matrix_p);

  // checking if it is square
  int const dim = arrlen(*matrix_p);
  *dim_p = dim;
  check_square_err(dim, *matrix_p);

  *out_file_p = fopen64(out_path, "w");
}

void clean_up(
  FILE * in_file,
  int const dim,
  double * * matrix,
  FILE * out_file,
  double * * inverse
) {
  for (int i = 0; i < dim; ++i) {
    arrfree(matrix[i]);
  }
  arrfree(matrix);
  fclose(in_file);

  for (int i = 0; i < dim; ++i) {
    free(inverse[i]);
  }
  free(inverse);
  fclose(out_file);
}

void check_square_err(
  int const dim,
  double * * matrix
) {
  for (int i = 0; i < dim; ++i) {
    if (arrlen(matrix[i]) != dim) {
      fprintf(stderr,
        "Try with a square matrix (comma separated)\n"
        "For example:\n"
        "1.01  ,  -0.02,   0\n"
        " 4    ,  -5   , 5.05\n"
        " 0    ,  -3   , 1\n"
      );
      exit(EXIT_FAILURE);
    }
  }
}

void parse_matrix(
  FILE * file,
  double * * * const matrix_p
) {
  char line[20];
  *matrix_p = NULL;
  while (fgets(line, 20, file)) {
    char *token = strtok(line, DELIM);
    double *row = NULL;
    while (token != NULL) {
      double number = atof(token);
      arrput(row, number);
      token = strtok(NULL, DELIM);
    }
    arrput(*matrix_p, row);
    printf("\n");
  }
}
