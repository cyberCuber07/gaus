
#include <time.h>
#include "test_gen.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define draw_number(r) ((r) > 70 ? 1 : 0)


char *cr_str1(char *name, char *add, int i){
    return get_name__(name, i+1);
}

char *cr_str2(char *name, char *add, int i){
    char *str1 = get_name__(name, i+1);
    return strcat(str1, add);
}


void run(int r, int c, int cnt, char *name, char *add, int i, char *(*fptr)(char*, char *, int)){
    char *fpath = fptr(name, add, i);
    
    Matrix *A = cr_mat(r, c);

    draw_matix(A, cnt);

    write_into(fpath, A);    
}


int main()
{
    srand(time(NULL));
    char *name = "data/test_";
    int n = 100;
    int mat_size = 7; // nominal is: r(:=max_size) + 3 -> max := 10

    int **nums = cr_nums(n, mat_size);
    
    int i;  
    for(i = 0; i < n; ++i){
        int cnt = draw_number(rand()%100);
        run(nums[i][0], nums[i][1], cnt, name, "", i, cr_str1);
        run(nums[i][0], 1, cnt, name, "_b_", i, cr_str2); /* thought this is enough to create singular matrix
                                                            but unfortunately it's not*/
    }

    return 0;
}