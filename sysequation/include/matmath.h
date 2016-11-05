#ifndef __MATMATH_H__
#define __MATMATH_H__

void add_mat_mat(const int n, const double A[n][n], double B[n][n]);
void add_vec_vec(const int n, const double u[n], double v[n]);

void multiply_mat_mat(const int n, const double A[n][n], double B[n][n]);
void multiply_mat_vec(const int n, const double A[n][n], double v[n]);

#endif
