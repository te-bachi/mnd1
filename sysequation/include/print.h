#ifndef __PRINT_H__
#define __PRINT_H__

#include <stdio.h>

void printvec(const char *var, const int n, double x[n]);
void printvec_multi(const char *var, const int n, const int r, double x[r][n]);
void printmat(const char *var, const int n, double A[n][n]);
void printmat_ab(const int n, double A[n][n], double b[n]);

#endif
