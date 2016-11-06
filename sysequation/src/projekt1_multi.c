
#include "projekt1.h"

#define N 4
#define R 2

void
main_multi(void)
{
    /*
    double  A[N][N] = {
        {   1,   0,   0,   0 },
        {   2,   1,   0,   0 },
        {   4,   2,   1,   0 },
        {   6,   4,   2,   1 }
    };
    
    double b[N] = {
          1,
          3,
          5,
          7
    };
    */
    double  A[N][N] = {
        {   2,  -1,  -3,   3 },
        {   4,   0,  -3,   1 },
        {   6,   1,  -1,   6 },
        {  -2,  -5,   4,   1 }
    };
    
    double b[R][N] = {
        {
              1,
             -8,
            -16,
            -12
        },
        {
            1,
            2,
            3,
            4
        }
    };
    
    double y[R][N];
    double x[R][N];
    double L[N][N];
    double U[N][N];
    double P[N][N];
    
    printf("========================================\n");
    printf("Verschiedene Rechte Seiten\n");
    
    
    /*
    printmat("A", N, A);
    printvec("b", N, b);
    scale_ab(N, A, b);
    lu(N, A, L, U, P);
    forward_multi(N, P, L, b, y);
    backward(N, U, y, x);
    
    printmat("P", N, P);
    printvec("x", N, x);
    */
}
