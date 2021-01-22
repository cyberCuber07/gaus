
/*
    there are also some util functions here,
    but just didnt want to make a separete file for them
    just wrote some code not to waste time on it
*/


#include "test_gen.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void iter_util_kill_me(Matrix *test_mat, int r, int c){
    int i, j;
    for(i = 0; i < r; ++i){
        for(j = 0; j < c; ++j)
            test_mat -> data[i][j] = (double)(rand()%100) / 61;
    }
    if(rand()%100 < 10)
        test_mat -> data[0][0] = 0; // just to make the third test..
}


void iter_util_kill_me_second_case_____(Matrix *test_mat, int r, int c){
    int i, j;
    double *val_col = malloc(c * sizeof(double));
    // double *val_row = malloc(c * sizeof(double));
    for(i = 0; i < c; ++i)
        val_col[i] = 0; //, val_row[i] = 0;

    double val_row;

    for(i = 0; i < r; ++i){
        val_row = 0;
        for(j = 0; j < c; ++j){
            double tmp = (double)(rand()%100) / 8;
            test_mat -> data[i][j] = tmp;
            val_col[j] += tmp, val_row += tmp;
        }
        test_mat -> data[i][c] = val_row;
    }
    
    ++r, ++c;

    val_row = 0;
    for(i = 0; i < c-1; ++i)
        test_mat -> data[r-1][i] = val_col[i], val_row += val_col[i];
    test_mat -> data[r-1][c-1] = val_row;
}

void draw_matix(Matrix *test_mat, int check){
    /*if check = 1 then singular case
      if check = 0 then regular case*/

    int r = test_mat->r - check, c = test_mat->c - check;
    if(!check)
        iter_util_kill_me(test_mat, r, c);
    else
        iter_util_kill_me_second_case_____(test_mat, r, c);
}


void write_into(char *fpath, Matrix *A){

    FILE *file = fopen(fpath, "w");

    int r = A->r, c = A->c;
    int i, j;
    fprintf(file, "%d %d\n", r, c);
    for(i = 0; i < r; ++i){
        for(j = 0; j < c; ++j)
            fprintf(file, "%lf ", A->data[i][j]);
        fprintf(file, "\n");
    }
}


Matrix *cr_mat(int r, int c){
    Matrix *A = malloc(sizeof(Matrix));
    A -> r = r, A -> c = c;
    A -> data = malloc(sizeof(double*) * r);
    int i;
    for(i = 0; i < r; ++i)
        A->data[i] = malloc(sizeof(double) * c);
    return A;
}



int **cr_nums(int n, int mat_size){

    int n1 = (int)(n * 0.7), n2 = (int)(n * 0.2), n3 = (int)((n - n1 - n2)/2), n4 = n - n1 - n2 - n3;

    int **nums = malloc(sizeof(int*) * n);
    int i;
    for(i = 0; i < n; ++i)
        nums[i] = malloc(sizeof(int) * 2);

    int iter = 0;
    // tests for regular matrices
    // tests for singular matrices
    // tests for matrices with "1" at mat[0][0]
    for(i = 0; i < n1+n2+n3; ++i){
        int size = rand() % mat_size + 3;
        nums[iter][0] = size, nums[iter][1] = size;
        ++iter;
    }

    // tests for matrices of r != c
    for(i = 0; i < n4; ++i){
        int r = rand() % mat_size + 3;
        int c = rand() % mat_size + 3;
        nums[iter][0] = r, nums[iter][1] = c;
        ++iter;
    }

    return nums;
}


char *get_name__(char *name, int j){
    int cnt = 0, k = j;
    char *tmp = malloc(3 * sizeof(char));
    while(k > 0){
        int val = k % 10;
        k /= 10;
        tmp[cnt++] = val + '0';
    }
    --cnt;
    char a_temp = tmp[0];
    tmp[0] = tmp[cnt];
    tmp[cnt] = a_temp; // this is enough for up to 3 obviously..

    char *ptr = malloc(sizeof(char) * (strlen(name) + strlen(tmp) + 40));
    strcpy(ptr, name);
    strcat(ptr, tmp);
    // strcat(ptr, ".txt");
    return ptr;
}
