/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"

/*
 * Add your optimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	double* BA = calloc(N * N, sizeof(*BA));
	if(!BA) {
		exit(EXIT_FAILURE);
	}
	double* C = calloc(N * N, sizeof(*C));
	if(!C) {
		exit(EXIT_FAILURE);
	}

	// BA = B * A
	for(register int i = 0; i < N; i++) {
		register double *B_orig = B + i * N;

		for(register int j = 0; j < N; j++) {
			register double sum = 0.0;
			register double* pb = B_orig;
			register double* pa = A + j;
			for(register int k = 0; k <= j; k++, pb++, pa += N) {
				sum += *pb * *pa;
			}
			BA[i * N + j] = sum;
		}
	}

	// BAA_t = BA * A'
	for(register int i = 0; i < N; i++) {
		register double *BA_orig = BA + i * N;
		for(register int j = 0; j < N; j++) {
			register double sum = 0.0;
			register double* p_ba = BA_orig + j;
			register double* pa_t = A + j * N + j;
			for(register int k = j; k < N; k++, p_ba++, pa_t++) {
				sum += *p_ba * *pa_t;
			}
			C[i * N + j] = sum;
		}
	}

	// B_tB = B' * B
	for(register int i = 0; i < N; i++) {
		register double *B_t_orig = B + i;
		for(register int j = 0; j < N; j++) {
			register double sum = 0.0;
			register double* pb_t = B_t_orig;
			register double* pb = B + j;
			for(register int k = 0; k < N; k++, pb_t += N, pb += N) {
				sum += *pb_t * *pb;
			}
			C[i * N + j] += sum;
		}
	}

	free(BA);
	return C;	
}
