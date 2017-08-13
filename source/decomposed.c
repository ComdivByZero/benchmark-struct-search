#include "settings.h"

static bool search1d(int a[N3], bool match(int), int *i) {
	*i = 0;
	while ((*i < N3) && !match(a[*i])) {
		*i += 1;
	}
	return *i < N3;
}
static bool search2d(int a[N2][N3], bool match(int), int *j, int *i) {
	*j = 0;
	while ((*j < N2) && !search1d(a[*j], match, i)) {
		*j += 1;
	}
	return *j < N2;
}
extern bool search_decomposed(int a[N1][N2][N3], bool match(int), int *k, int *j, int *i) {
	*k = 0;
	while ((*k < N1) && !search2d(a[*k], match, j, i)) {
		*k += 1;
	}
	return *k < N1;
}
