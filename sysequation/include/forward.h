#ifndef __FORWARD_H__
#define __FORDWARD_H__

void forward(const int n, const double P[n][n], const double L[n][n], double b[n], double y[n]);
void forward_multi(const int n, const double P[n][n], const double L[n][n], const int r, double b[r][n], double y[r][n]);

#endif