#ifndef __QR_H__
#define __QR_H__

void qr_householder(const int m, const int n, const double A[m][n], double Q[m][m], double R[m][n]);
void qr_householder_b(const int m, const int n, const double A[m][n], double Q[m][n], double R[m][n], double QTb[n], double b[m], double d[n]);
void qr_givens(const int m, const int n, const double A[m][n], double Q[m][n], double R[m][n]);

#endif
