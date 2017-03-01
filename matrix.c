#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"


/*-------------- void print_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

print the matrix
*/
void print_matrix(struct matrix *m) {
  int i, j;
  for (i = 0; i < (*m).rows; i++){
    for (j = 0; j < (*m).cols; j++){
      printf("%f ", (*m).m[i][j]);        
    }
    printf("\n");
  }
}

/*-------------- void ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix
Returns: 

turns m in to an identity matrix
*/
void ident(struct matrix *m) {
  int i, j;
  for (i = 0; i < (*m).rows; i++){
    for (j = 0; j < (*m).cols; j++){
      if (i == j) (*m).m[i][j] = 1.0;
      else (*m).m[i][j] = 0.0;
    }
  }
}


/*-------------- void scalar_mult() --------------
Inputs:  double x
         struct matrix *m 
Returns: 

multiply each element of m by x
*/
void scalar_mult(double x, struct matrix *m) {
  int i, j;
  for(i = 0; i < (*m).rows; i++){
    for (j = 0; j < (*m).rows; j++){
      (*m).m[i][j] *= x;
    }
  }
}


/*-------------- void matrix_mult() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

a*b -> b
*/
void matrix_mult(struct matrix *a, struct matrix *b) {
  if ((*a).cols != (*b).rows) return;
  int i, j, k;
  struct matrix *c;
  c = new_matrix((*b).rows, (*b).cols);
  for(i = 0; i < (*b).rows; i++)
    for(j = 0; j < (*b).cols; j++)
      for (k = 0; k < (*a).rows; k++)
	(*c).m[i][j] += (*a).m[i][k] * (*b).m[k][j];
  //printf("printing product...\n"), print_matrix(c);
  copy_matrix(c, b);
  free_matrix(c);
}

/*===============================================
  These Functions do not need to be modified
  ===============================================*/

/*-------------- struct matrix *new_matrix() --------------
Inputs:  int rows
         int cols 
Returns: 

Once allocated, access the matrix as follows:
m->m[r][c]=something;
if (m->lastcol)... 
*/
struct matrix *new_matrix(int rows, int cols) {
  double **tmp;
  int i;
  struct matrix *m;

  tmp = (double **)malloc(rows * sizeof(double *));
  for (i=0;i<rows;i++) {
      tmp[i]=(double *)malloc(cols * sizeof(double));
    }

  m=(struct matrix *)malloc(sizeof(struct matrix));
  m->m=tmp;
  m->rows = rows;
  m->cols = cols;
  m->lastcol = 0;

  return m;
}


/*-------------- void free_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

1. free individual rows
2. free array holding row pointers
3. free actual matrix
*/
void free_matrix(struct matrix *m) {

  int i;
  for (i=0;i<m->rows;i++) {
      free(m->m[i]);
    }
  free(m->m);
  free(m);
}


/*======== void grow_matrix() ==========
Inputs:  struct matrix *m
         int newcols 
Returns: 

Reallocates the memory for m->m such that it now has
newcols number of collumns
====================*/
void grow_matrix(struct matrix *m, int newcols) {
  
  int i;
  for (i=0;i<m->rows;i++) {
      m->m[i] = realloc(m->m[i],newcols*sizeof(double));
  }
  m->cols = newcols;
}


/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {

  int r, c;

  for (r=0; r < a->rows; r++) 
    for (c=0; c < a->cols; c++)  
      b->m[r][c] = a->m[r][c];  
}

int main(){

  struct matrix *a, *b;
  a = new_matrix(2, 2), b = new_matrix(2, 2);
  (*a).m[0][0] = 1.0, (*a).m[0][1] = 2.0;
  (*a).m[1][0] = 3.0, (*a).m[1][1] = 4.0;
  (*b).m[0][0] = 1.0, (*b).m[0][1] = 2.0;
  (*b).m[1][0] = 3.0, (*b).m[1][1] = 4.0;
  printf("printing matrix a...\n"), print_matrix(a);
  printf("printing matrix b...\n"), print_matrix(b);
  matrix_mult(a, b);
  printf("printing product...\n"), print_matrix(b);
  
  return 0;
}
