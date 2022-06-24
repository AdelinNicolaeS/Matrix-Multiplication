/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"
#include "cblas.h"
#include <string.h>

/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {
	double* C = calloc(N * N, sizeof(*C));
	if(!C) {
		exit(EXIT_FAILURE);
	}

	memcpy(C, B, N * N * sizeof(*C));

	// C = B =>  C = alpha * C * op(A) => C = B * A
	cblas_dtrmm(
		CblasRowMajor,
		CblasRight,
		CblasUpper,
		CblasNoTrans,
		CblasNonUnit,
		N,
		N,
		1.0,
		A,
		N,
		C,
		N
	);

	// C = B * A => C = alpha * C * op(A) => C = B * A * A'
	cblas_dtrmm(
		CblasRowMajor,
		CblasRight,
		CblasUpper,
		CblasTrans,
		CblasNonUnit,
		N,
		N,
		1.0,
		A,
		N,
		C,
		N
	);

	// C = alpha * op(B) * op(B) + beta * C => C = B' * B + B * A * A'
	cblas_dgemm(
		CblasRowMajor,
		CblasTrans,
		CblasNoTrans,
		N,
		N,
		N,
		1.0,
		B,
		N,
		B,
		N,
		1.0,
		C,
		N
	);
	return C;
}
