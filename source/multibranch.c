#include "settings.h"

#define While while (1) if (
#define Do ) {
#define Elsif } else if (
#define End } else break;

extern bool search_multibranch(int a[N1][N2][N3], bool match(int), int *pk, int *pj, int *pi) {
	int i, j, k;
	i = 0;
	j = 0;
	k = 0;
	While (i < N3) && !match(a[k][j][i]) Do
		i += 1;
	Elsif (i >= N3) && (j < N2 - 1)      Do
		i  = 0;
		j += 1;
	Elsif (i >= N3) && (k < N1 - 1)      Do
		i  = 0;
		j  = 0;
		k += 1;
	End
	*pi = i;
	*pj = j;
	*pk = k;
	return i < N3;
}
