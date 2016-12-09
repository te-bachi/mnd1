#ifndef __LU_H__
#define __LU_H__

#include <stdbool.h>

void lu(const int n, const double A[n][n], double L[n][n], double U[n][n], double P[n][n]);

#endif
