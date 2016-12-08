
#include "projekt1.h"

#define N 3

void
main_lu(void)
{
    double H[N][N] = {
        { 1, 2, 3 },
        { 1, 7, 5 },
        { 4, 1, 2 }
    };

    double HI[N][N];
    double d[N];
    double L[N][N];
    double U[N][N];
    double P[N][N];

    printf("=== main_lu() ===========================================\n");
    printf("LU-Zerlegung (mit Inverse und Skalierung)\n");

    inverse(N, H, HI);
    printmat("H", N, H);
    scale(N, H, d);
    printmat("H", N, H);
    lu(N, H, L, U, P);
    printmat("L", N, L);
    printmat("U", N, U);
    printmat("HI", N, HI);
}
