#ifndef __SCALE_H__
#define __SCALE_H__

void scale(const int n, double A[n][n], double d[n]);
void scale_ab(const int n, double A[n][n], double b[n], double d[n]);
void scale_ab_multi(const int n, double A[n][n], const int r, double b[r][n], double d[n]);

#endif
