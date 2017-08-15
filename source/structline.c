#include "settings.h"

extern bool search_structline(int a[N1][N2][N3], bool match(int), int *pk, int *pj, int *pi) {
	int i, j, k;
	i = 0;
	j = 0;
	k = 0;
	while ((k < N1) && !match(a[k][j][i])) {
		if (i < N3 - 1) {
			i += 1;
		} else {
			i = 0;
			if (j < N2 - 1) {
				j += 1;
			} else {
				j = 0;
				k += 1;
			}
		}
	}
	*pi = i;
	*pj = j;
	*pk = k;
	return k < N1;
}
