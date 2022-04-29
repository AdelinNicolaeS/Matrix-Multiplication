/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	double* BA = calloc(N * N, sizeof(*BA));
	if(!BA) {
		exit(EXIT_FAILURE);
	}
	double* BAA_t = calloc(N * N, sizeof(*BAA_t));
	if(!BAA_t) {
		exit(EXIT_FAILURE);
	}
	double* B_tB = calloc(N * N, sizeof(*B_tB));
	if(!B_tB) {
		exit(EXIT_FAILURE);
	}
	double* C = calloc(N * N, sizeof(*C));
	if(!C) {
		exit(EXIT_FAILURE);
	}

	int i, j, k;
	// BA = B * A
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			for(k = 0; k <= j; k++) {
				BA[i * N + j] += B[i * N + k] * A[k * N + j];
			}
		}
	}

	// BAA_t = BA * A'
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			for(k = j; k < N; k++) {
				BAA_t[i * N + j] += BA[i * N + k] * A[j * N + k];
			}
		}
	}

	// B_tB = B' * B
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			for(k = 0; k < N; k++) {
				B_tB[i * N + j] += B[k * N + i] * B[k * N + j];
			}
		}
	}

	// C = BAA_t + B_tB
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			C[i * N + j] = BAA_t[i * N + j] + B_tB[i * N + j];
		}
	}

	free(BA);
	free(BAA_t);
	free(B_tB);
	return C;
}
