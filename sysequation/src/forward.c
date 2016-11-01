
#include "forward.h"
#include "multiply.h"

#include <string.h>

void
forward(int n, double L[n][n], double y[n], double b[n])
{
    int i;
    int k;
    double sum;
    
    memset(y, 0, n*sizeof(double));
    
    y[0] = b[0];
    
    for (i = 1; i < n; i++) {
        sum = 0;
        for (k = 0; k < i; k++) {
            sum += (L[i][k] * y[k]);
        }
        y[i] = (b[i] - sum) / L[i][i];
    }
}

#ifdef __FORWARD_MAIN__

#include "print.h"

#define N 4

int
main(int argc, const char *argv[])
{
    /*
    double  A[N][N] = {
        {   1,   0,   0,   0 },
        {   1,   2,   0,   0 },
        {   1,   2,   4,   0 },
        {   1,   2,   4,   6 }
    };
    
    double b[N] = {
          1,
          2,
          4,
          6
    };
    */
    
    double A[N][N] = {
        {   1,   0,   0,   0 },
        {   2,   1,   0,   0 },
        {   4,   2,   1,   0 },
        {   6,   4,   2,   1 }
    };
    
    double P[N][N] = {
        {   1,   0,   0,   0 },
        {   0,   1,   0,   0 },
        {   0,   0,   1,   0 },
        {   0,   0,   0,   1 }
    };
    
    double b[N] = {
          1,
          3,
          5,
          7
    };
    
    double y[N];
    
    printmat("A", N, A);
    printvec("b", N, b);
    
    multiply_mat_vec(N, P, b);
    forward(N, A, y, b);
    
    printvec("y", N, y);
    
    return 0;
}

#endif
