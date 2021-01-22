
#include "gauss.h"
#include "backsubst.h"
#include "run.h"
#include "tests.h"

#include "../tests/test_gen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



int run_multi(char *dpath, char *tpath){

    int i, ret_val;
    for(i = 1; i <= 100; ++i){

        char *d1 = get_name__(dpath, i);
        char *d2 = malloc(sizeof(char) * 100);
        strcpy(d2, d1);
        strcat(d2, "_b_");

        // printf("%s %s %s\n", d1, d2, tpath);

        printf("%d# ", i);

        ret_val = __run__(d1, d2, i, tpath, 1, test_x);
    }

    return ret_val;
}


int run_one(int argc, char **argv){
    return __run__(argv[3], argv[4], 1, argv[2], 0, test_x);
}


int __run__(char *d1, char *d2, int i, char *tpath, int check, int (*fptr)(Matrix *, char *, int, int )){

    Matrix *A = readFromFile(d1);
    Matrix *b = readFromFile(d2);
    Matrix * x;

    if (A == NULL) return -1;
    if (b == NULL) return -2;


    /*check for 1 at A[0][0]*/
    if(A->data[0][0] == 0){
        printf("Found 0.0 at the cell[0,0]\nInput error in test %d\n", i);
        return 1;
    }

    /* check if matrix is OK*/
    if(check_dim(A) != 0){
        printf("### Input error in test %d\n", i);
        printf("    Matrix is not a square!\n");
        return 1;
    }

    int res = eliminate(A,b);


    int j;
    int r = A->r;
    for(j = 0; j < r; ++j){
        if(check_col(A->data, j, r)){
            printf("### Matrix is singular\n");
            return 1;
        }
    }
    for(j = 0; j < r; ++j){
        if(check_row(A->data, j, r)){
            printf("### Matrix is singular\n");
            return 1;
        }
    }

    /* check the diagonal values after elimination*/
    if(check_diag(A) != 0){
        printf("### Input error in test %d \n", i);
        printf("    Matrix contains at least one 0 on diagonal!\n");
        return 1;
    }


    x = createMatrix(b->r, 1);
    if (x != NULL) {
        res = backsubst(x,A,b);

        res = fptr(x, tpath, i, check);

    // freeMatrix(x);
    } else {
                    fprintf(stderr,"Błąd! Nie mogłem utworzyć wektora wynikowego x.\n");
    }

    freeMatrix(A);
    // freeMatrix(b); // this caused the program to crash when wanted all tests at once 
    
    return res;
}


int test_x(Matrix *x, char *tpath, int idx, int check){

    char *tmp = malloc(sizeof(char) * 123);
    if(check){
        tmp = get_name__(tpath, idx);
        strcat(tmp,"_x_");
    }
    else
        strcpy(tmp, tpath);

    Matrix *corr_x = readFromFile(tmp);
    
    int r = x -> r;
    int i;


    double eps = 10e-8;
    for(i = 0; i < r; ++i){
        if(fabs(x->data[i][0] - corr_x->data[i][0]) > eps){
            printf("%lf %lf\n", x->data[i][0], corr_x->data[i][0]);
            printf("Wrong solution in test %d\n", idx);
            return 1;
        }
    }
    printf("The solution is correct!\n");
    return 0;
}
