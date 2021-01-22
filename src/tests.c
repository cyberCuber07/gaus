
#include "tests.h"


int check_dim(Matrix *mat){
	return mat->r - mat->c;
}

int check_diag(Matrix *mat){
	int i = mat -> r;
	while(i--){
		if(mat->data[i][i] == 0)
			return 1;
	}
	return 0;
}
