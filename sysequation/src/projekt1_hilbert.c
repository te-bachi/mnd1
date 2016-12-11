
#include "projekt1.h"

#define N 3

void
main_hilbert(void)
{
    double H[N][N];
    double HI[N][N];
    double HE[N][N];
    double d[N];
    double y[N];
    double x[N];
    double L[N][N];
    double U[N][N];
    double P[N][N];
    double b[N];
    int i;


    printf("=== main_hilbert() ======================================\n");
    printf("Hilbert-Matrix mit Loesung und max. Fehler\n");

    hilbert(N, H);
    scale(N, H, d);
    inverse(N, H, HI);
    eye_square(N, HE);
    for (i = 0; i < N; i++) {
        b[i] = 1.0/(N+i);
    }
    printmat_ab_square(N, H, b);

    lu(N, H, L, U, P);
    printmat_square("L", N, L);
    printmat_square("U", N, U);

    forward(N, P, L, b, y);
    backward(N, U, y, x);

    printvec("x", N, x);


    multiply_mat_mat_square(N, HI, H);
    subtract_mat_mat(N, HE, H);

    printmat_square("HI * H - HE", N, H);
    printf("max. error: %g\n", error_max(N, H));

}
