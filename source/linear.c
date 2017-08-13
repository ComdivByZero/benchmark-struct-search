#include "settings.h"

extern bool search_linear(int a[N1][N2][N3], bool match(int), int *pk, int *pj, int *pi) {
	int i;
	for (i = 0; i < (N1 * N2 * N3); i += 1) {
		if (match(((int *)a)[i])) {
			*pk = i / (N3 * N2);
			*pj = i / N3 % N2;
			*pi = i % N3;
			return true;
		}
	}
	return false;
}
