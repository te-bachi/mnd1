
#include "projekt1.h"

#define N 5

void
main_permutation(void)
{
    /*
    double  A[N][N] = {
        {   4,   0,   1,   0,   0 },
        {   3,   0,   0,   0,   1 },
        {   6,   0,   0,   1,   0 },
        {   5,   1,   0,   0,   0 },
        {   6,   0,   0,   0,   0 },
    };
    */

    double  A[N][N] = {
        {   0,   0,   1,   0,   0 },
        {   0,   0,   0,   0,   1 },
        {   0,   0,   0,   1,   0 },
        {   0,   1,   0,   0,   0 },
        {   1,   0,   0,   0,   0 },
    };

    /*
    double  A[N][N] = {
        {   1,   0,   0,   0,   0 },
        {   0,   1,   0,   0,   0 },
        {   0,   0,   1,   0,   0 },
        {   0,   0,   0,   1,   0 },
        {   0,   0,   0,   0,   1 },
    };
    */
    double L[N][N];
    double U[N][N];
    double P[N][N];

    printf("=== main_permutation() ==================================\n");

    printmat_square("A", N, A);

    lu(N, A, L, U, P);
    printmat_square("L", N, L);
    printmat_square("U", N, U);
    printmat_square("P", N, P);

}
