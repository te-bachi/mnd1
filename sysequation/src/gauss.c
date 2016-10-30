
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>

#include "gauss.h"
#include "backward.h"
#include "print.h"


void
gauss(int n, double A[n][n], double b[n])
{
    int i;
    int j;
    int k;
    double l;
    
    for (j = 0; j < (n - 1); j++) {
        printf("=== %d ====================\n", j);
        if (A[j][j] != 0) {
            for (i = j + 1; i < n; i++) {
                l = A[i][j] / A[j][j];
                printf("l[%d] = %5.2f\n", i, l);
                for (k = j; k < n; k++) {
                    A[i][k] = A[i][k] - (l * A[j][k]);
                }
                b[i] = b[i] - (l * b[j]);
            }
        }
        
        printmat("A", n, A);
        printvec("b", n, b);
        
        //printmat_ab(n, A, b);
    }
}


#ifdef __GAUSS_MAIN__

#define N 4

int
main(int argc, const char *argv[])
{
    double  A[N][N] = {
        {   2,  -1,  -3,   3 },
        {   4,   0,  -3,   1 },
        {   6,   1,  -1,   6 },
        {  -2,  -5,   4,   1 }
    };
    
    double b[N] = {
          1,
         -8,
        -16,
        -12
    };
    
    double x[N] = {
        0,
        0,
        0,
        0
    };
    
    printmat_ab(N, A, b);
    gauss(N, A, b);
    backward(N, A, b, x);
    printvec("x", N, x);
    
    return 0;
}
#endif
