#ifndef __MULTIPLY_H__
#define __MULTIPLY_H__

void multiply_mat_mat(const int n, const double A[n][n], double B[n][n]);
void multiply_mat_vec(const int n, const double A[n][n], double v[n]);

#endif
