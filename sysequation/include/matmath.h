#ifndef __MATMATH_H__
#define __MATMATH_H__

double signum(double x);

void eye_square(const int n, double A[n][n]);
void zeros_square(const int n, double A[n][n]);
void ones_square(const int n, double A[n][n]);

void transpose_square(const int n, double A[n][n]);
double scalarproduct(const int n, const double v[n], const double w[n]);
double euklid_norm_vec(const int n, const double v[n]);

void duplicate_mat(const int n, const double A[n][n], double B[n][n]);

void add_mat_mat(const int n, const double A[n][n], double B[n][n]);
void add_vec_vec(const int n, const double u[n], double v[n]);

void subtract_mat_mat(const int n, const double A[n][n], double B[n][n]);
void subtract_vec_vec(const int n, const double u[n], double v[n]);

void multiply_mat_mat_square(const int n, const double A[n][n], double B[n][n]);
void multiply_mat_vec_square(const int n, const double A[n][n], double v[n]);

void multiply_mat_mat(const int m, const int o, const int n, const double A[m][o], const double B[o][n], double C[m][n]);
void multiply_vec_vec_to_mat(const int m, const double v[m], const int n, const double w[n], double C[m][n]);

#endif
