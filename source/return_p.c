#include "settings.h"

extern bool search_return_p(int a[N1][N2][N3], bool match(int), int *k, int *j, int *i) {
	for (*k = 0; *k < N1; *k += 1) {
		for (*j = 0; *j < N2; *j += 1) {
			for (*i = 0; *i < N3; *i += 1) {
				if (match(a[*k][*j][*i])) {
					return true;
				}
			}
		}
	}
	return false;
}
