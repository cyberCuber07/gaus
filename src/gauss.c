
#include "gauss.h"
#include <stdio.h>
#include <math.h>

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */

double eps = 10e-8;

int check_col(double **data, int col, int size){
	/*no vertical slices in C so passing 2d array*/
	int i, iter = 0;
	for(i = 0; i < size; ++i){
		if(fabs(data[i][col]) <= eps)
			++iter;
	}
	return (iter == size ? 1 : 0);
}

int check_row(double **data, int row, int size){
	/*no vertical slices in C so passing 2d array*/
	int i, iter = 0;
	for(i = 0; i < size; ++i){
		if(fabs(data[row][i]) <=eps)
			++iter;
	}
	return (iter == size ? 1 : 0);
}

void swap(double *a, double *b){
	double tmp = *a;
	*a = *b;
	*b = tmp;
}

int mx_val_idx_cols(double **data, int idx, int r){
	int i;
	int max_idx = idx;
	double mx_val = data[idx][idx];
	for(i = idx+1; i < r; ++i){
		if(fabs(data[i][idx]) > fabs(mx_val))
			mx_val = data[i][idx], max_idx = i;
	}
	return max_idx;
}

int mx_val_idx_rows(double **data, int idx, int r){
	int i;
	int max_idx = idx;
	double mx_val = data[idx][idx];
	for(i = idx+1; i < r; ++i){
		if(fabs(data[idx][i]) > fabs(mx_val))
			mx_val = data[idx][i], max_idx = i;
	}
	return max_idx;
}

void swap_cols(Matrix *A, int mx_idx, int act_idx){
	int i, r = A->r;
	for(i = act_idx; i < r; ++i) // going by diagonal, so x = y -> starter for x := act_idx のわけです。。。
		swap(&A->data[mx_idx][i], &A->data[act_idx][i]);
}

void swap_rows(Matrix *A, int mx_idx, int act_idx){
	int i, r = A->r;
	for(i = 0; i < r; ++i) // going by diagonal, so x = y -> starter for x := act_idx のわけです。。。
		swap(&A->data[i][mx_idx], &A->data[i][act_idx]);
}

int swap_run(Matrix *A, int act_idx, Matrix *b, char a){
	int mx_idx;
	switch (a){
	case 'r':
		printToScreen(A);
		mx_idx = mx_val_idx_rows(A->data, act_idx, A->r);
		swap_rows(A, mx_idx, act_idx);
		printToScreen(A);
		return 0;
	case 'c':
		mx_idx = mx_val_idx_cols(A->data, act_idx, A->r);
		swap_cols(A, mx_idx, act_idx);
		swap(&b->data[mx_idx][0], &b->data[act_idx][0]);
		return 0;
	
	default:
		printf("Incorrect method\n");
		break;
	}
	return 1;
}

int eliminate(Matrix *A, Matrix *b){

    int i, j, k;
    int r = A->r;
    for(i = 0; i < r; ++i){
		if(swap_run(A, i, b, 'c')) return 1;
	    for(j = i+1; j < r; ++j){
			if(A->data[i][i] == 0){
				printf("Wrong input matrix!\nFound zero at diagonal\n");
				return 1;
			}
            double fct = A->data[j][i] / A->data[i][i];
            for(k = 0; k < r; ++k)
                A->data[j][k] -= A->data[i][k] * fct;
			b->data[j][0] -= fct * b->data[i][0];
        }
    }

	/*so for now: not sure if each column or row should be checked for full zeros
	so skipping --- zero-diaganal still works*/

	return 0;
}

