#include "settings.h"

extern bool search_return(int a[N1][N2][N3], bool match(int), int *pk, int *pj, int *pi) {
	int i, j, k;
	for (k = 0; k < N1; k += 1) {
		for (j = 0; j < N2; j += 1) {
			for (i = 0; i < N3; i += 1) {
				if (match(a[k][j][i])) {
					*pk = k;
					*pj = j;
					*pi = i;
					return true;
				}
			}
		}
	}
	return false;
}
