
#include "inverse.h"
#include "matmath.h"
#include "lu.h"
#include "forward.h"
#include "backward.h"
#include "scale.h"
#include "print.h"

#include <string.h>
#include <stdlib.h>

void
inverse(const int n, const double A[n][n], double I[n][n])
{
    double B[n][n];
    double E[n][n];
    double d[n];
    double y[n][n];
    double L[n][n];
    double U[n][n];
    double P[n][n];
    
    memcpy(B, A, n*n*sizeof(double));
    eye_square(n, E);
    
    scale_ab_multi(n, B, n, E, d);
    lu(n, B, L, U, P);

    printmat_square("L", n, L);
    printmat_square("U", n, U);
    printmat_square("P", n, P);
    forward_multi(n, P, L, n, E, y);
    backward_multi(n, U, n, y, I);
    transpose_square(n, I);
}
