
#include "projekt1.h"

#define N 5

void
main_single_scale(void)
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

    double d[N];
    double y[N];
    double x[N];
    double L[N][N];
    double U[N][N];
    double P[N][N];
    double PI[N][N];
    double RES[N][N];

    printf("=== main_single_scale() =================================\n");
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

    inverse(N, P, PI);
    printmat("PI", N, PI);
    duplicate_mat(N, U, RES);
    multiply_mat_mat(N, L, RES);
    multiply_mat_mat(N, PI, RES);
    printmat("A*", N, RES);

}
