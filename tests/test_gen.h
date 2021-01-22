
#ifndef _TEST_GEN_H_
#define _TEST_GEN_H_

#include "../src/mat_io.h"


void draw_matix(Matrix *test_mat, int check);

void write_into(char *fpath, Matrix *A);

Matrix *cr_mat(int r, int c);

void iter_util_kill_me(Matrix *test_mat, int r, int c);

void iter_util_kill_me_second_case_____(Matrix *test_mat, int r, int c);

char *get_name__(char *name, int j);

int **cr_nums(int n, int mat_size);

#endif