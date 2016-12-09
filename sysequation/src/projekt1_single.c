
#include "projekt1.h"

#define N 5

void
main_single(void)
{
    double  A[N][N] = {
        {   2,  -1,  -3,   3,   5 },
        {   4,   0,  -3,   1,   2 },
        {   6,   1,  -1,   6,   7 },
        {  -2,  -5,   4,   1,   0 },
        {   1,   7,   2,   9,   6 },
    };
    double b[N] = {
            9,
           10,
          102,
          -29,
          189
    };
    
    double y[N];
    double x[N];
    double L[N][N];
    double U[N][N];
    double P[N][N];
    double PI[N][N];
    double RES[N][N];

    printf("=== main_single() =======================================\n");
    printf("Eine Rechte Seite\n");
    
    printmat("Matrix A", N, A);
    printvec("Loesung b", N, b);
    
    lu(N, A, L, U, P);
    printmat("L", N, L);
    printmat("U", N, U);
    printmat("P", N, P);
    
    forward(N, P, L, b, y);
    backward(N, U, y, x);
    
    printvec("x", N, x);
    
    inverse(N, P, PI);
    printmat("PI", N, PI);
    duplicate_mat(N, U, RES);
    multiply_mat_mat(N, L, RES);
    multiply_mat_mat(N, PI, RES);
    printmat("inv(P) * L * U", N, RES);

}
