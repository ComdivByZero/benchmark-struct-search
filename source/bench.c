#include <stdio.h>
#include <assert.h>
#include <limits.h>

#include <time.h>

#include "settings.h"

typedef bool
       search_f(int a[N1][N2][N3], bool match(int), int *k, int *j, int *i);
extern search_f
	search_decomposed,
	search_multibranch,
	search_return, search_return_p,
	search_linear,
	search_structline,
	search_outlimit;

static int sample;
static bool match(int val) {
	return sample == val;
}

static void start(struct timespec *t) {
	int res;
	res = clock_gettime(CLOCK_MONOTONIC, t);
	assert(0 == res);
}

static long end(struct timespec *st) {
	int res;
	struct timespec end;
	res = clock_gettime(CLOCK_MONOTONIC, &end);
	assert(0 == res);
	return (end.tv_sec - st->tv_sec) * 1000000 + (end.tv_nsec - st->tv_nsec) / 1000;
}

extern int main(int argc, char const *argv[]) {
	int arr[N1][N2][N3];
	int i, j, k, l, m, n;
	struct timespec t;
	long dt;
	search_f *search;
	struct {
		search_f *f;
		char const *n;
		long mintime;
	} fs[] = {
		{ search_return_p   , "return_p"   , LONG_MAX },
		{ search_return     , "return"     , LONG_MAX },
		{ search_linear     , "linear"     , LONG_MAX },
		{ search_decomposed , "decomposed" , LONG_MAX },
		{ search_outlimit   , "outlimit"   , LONG_MAX },
		{ search_structline , "structline" , LONG_MAX },
		{ search_multibranch, "multibranch", LONG_MAX }
	};
	for (l = 0; l < N1 * N2 * N3; l += 1) {
		arr[l / (N2 * N3)][l / N3 % N2][l % N3] = l;
	}
	for (m = 0; m < 10; m += 1) {
		for (n = 0; n < sizeof(fs) / sizeof(fs[0]); n += 1) {
			search = fs[n].f;
			sample = -1;

			start(&t);
			assert(!search(arr, match, &k, &j, &i));
			sample = N1 * N2 * N3;
			assert(!search(arr, match, &k, &j, &i));
			sample -= 1;
			assert(search(arr, match, &k, &j, &i)
			    && (k == N1 - 1) && (j == N2 - 1) && (i == N3 - 1));

			for (l = 0; l < 20000; l += 1) {
				sample = l % (N1 * N2 * N3);
				assert(search(arr, match, &k, &j, &i));
				assert(arr[k][j][i] == sample);
			}

			dt = end(&t);
			if (dt < fs[n].mintime) {
				fs[n].mintime = dt;
			}
		}
	}
	for (n = 0; n < sizeof(fs) / sizeof(fs[0]); n += 1) {
		printf("%12s : %ld ms\n", fs[n].n, fs[n].mintime / 1000);
	}

	for (n = 0; n < sizeof(fs) / sizeof(fs[0]); n += 1) {
		printf("<td>%ld", fs[n].mintime / 1000);
	}
	printf("\n");
	return 0;
}

