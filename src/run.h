
#ifndef _RUN_H_
#define _RUN_H_

#include "mat_io.h"

int run_one(int argc, char **argv);

int run_multi(char *dpath, char *tpath);

int __run__(char *d1, char *d2, int i, char *tpath, int check, int (*fptr)(Matrix *, char *, int, int ));

int test_x(Matrix *x, char *tpath, int idx, int check);


#endif