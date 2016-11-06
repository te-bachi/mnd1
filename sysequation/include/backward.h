#ifndef __BACKWARD_H__
#define __BACKWARD_H__

void backward(const int n, const double U[n][n], const double y[n], double x[n]);
void backward_multi(const int n, const double U[n][n], const int r, const double y[r][n], double x[r][n]);

#endif
