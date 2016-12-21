#ifndef __PRINT_H__
#define __PRINT_H__

#include <stdio.h>

/* vector */
void printvec(const char *var, const int n, const double x[n]);
void printvec_multi(const char *var, const int n, const int r, double x[r][n]);

/* square matrix */
void printmat_square(const char *var, const int n, double A[n][n]);
void printmat_ab_square(const int n, double A[n][n], double b[n]);

/* m x n matrix */
void printmat(const char *var, const int m, const int n, double A[m][n]);

#endif
