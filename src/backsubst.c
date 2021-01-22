#include "backsubst.h"
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
int  backsubst(Matrix *x, Matrix *A, Matrix *b) {
	
	int i;
	int r = A -> r;
	for(i = r-1; i >= 0; --i){
		x->data[i][0] = b->data[i][0];
		int j;
		for(j = i+1; j < r; ++j)
			x->data[i][0] -= A->data[i][j] * x->data[j][0];
		x->data[i][0] /= A->data[i][i];
	}

	return 0;
}


