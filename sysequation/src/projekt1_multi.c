
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
    
    double d[N];
    double y[R][N];
    double x[R][N];
    double L[N][N];
    double U[N][N];
    double P[N][N];
    
    printf("=== main_multi() ========================================\n");
    printf("Mehrere Rechte Seiten\n");
    
    
    printmat_square("A", N, A);
    printvec_multi("b", N, R, b);
    
    scale_ab_multi(N, A, R, b, d);
    printvec("d", N, d);
    printmat_square("A_scale", N, A);
    printvec_multi("b_scale", N, R, b);
    
    lu(N, A, L, U, P);
    printmat_square("L", N, L);
    printmat_square("U", N, U);
    
    forward_multi(N, P, L, R, b, y);
    backward_multi(N, U, R, y, x);
    
    printmat_square("P", N, P);
    printvec_multi("x", N, R, x);
}
