
#include "projekt1.h"

#define N 4

void
main_single(void)
{
    
    double  A[N][N] = {
        {   2,  -1,  -3,   3 },
        {   4,   0,  -3,   1 },
        {   6,   1,  -1,   6 },
        {  -2,  -5,   4,   1 }
    };
    
    /*
    double b[N] = {
          1,
         -8,
        -16,
        -12
    };
    */
    double b[N] = {
          1,
          2,
          3,
          4
    };
    
    double d[N];
    double y[N];
    double x[N];
    double L[N][N];
    double U[N][N];
    double P[N][N];

    printf("=== main_single() =======================================\n");
    printf("Eine Rechte Seite\n");
    
    printmat("Matrix A", N, A);
    printvec("Loesung b", N, b);
    
    scale_ab(N, A, b, d);
    printvec("Skalierung d", N, d);
    printmat("A_scale", N, A);
    printvec("b_scale", N, b);
    
    lu(N, A, L, U, P);
    printmat("L", N, L);
    printmat("U", N, U);
    
    forward(N, P, L, b, y);
    backward(N, U, y, x);
    
    printmat("P", N, P);
    printvec("x", N, x);
    
}
