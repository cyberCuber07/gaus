#ifndef _GAUSS_H
#define _GAUSS_H

#include "mat_io.h"

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b);

int check_col(double **data, int col, int size);

int check_row(double **data, int row, int size);

void swal_cols(Matrix *A, int mx_idx, int act_idx);

void swap_rows(Matrix *A, int mx_idx, int act_idx);

int mx_val_idx_cols(double **data, int idx, int r);

int mx_val_idx_rows(double **data, int idx, int r);

void swap(double *a, double *b);

int swap_run(Matrix *A, int act_idx, Matrix *b, char a);

#endif
