#ifndef __LU_H__
#define __LU_H__

void scale(int n, double A[n][n], double b[n], double d[n]);
void lu(int n, double A[n][n], double L[n][n], double U[n][n], double P[n][n]);
void lu_gauss(int n, double A[n][n], double L[n][n], double U[n][n], double b[n]);

#endif
