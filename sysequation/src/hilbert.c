
#include "hilbert.h"

/**
 * Erstelle eine Hilbert-Matrix
 *
 * @param[in]       n       Dimension
 * @param[out]      A       Hilbert-Matrix
 */
void
hilbert(const int n, double A[n][n])
{
    int i;
    int j;
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            A[i][j] = 1.0 / (((double) i) + ((double) j) + 1);
        }
    }
}

#ifdef __HILBERT_MAIN__

#include "print.h"
#include "matmath.h"
#include "scale.h"
#include "lu.h"

#include <string.h>
#include <stdlib.h>

#define N 5

int
main(int argc, const char *argv[])
{
    double  A[N][N];
    double  L[N][N];
    double  U[N][N];
    double  P[N][N];
    double  E[N][N];
    double  Lcopy[N][N];
    double  Ucopy[N][N];
    
    hilbert(N, A);
    printmat("A", N, A);
    scale(N, A);
    lu(N, A, L, U, P);
    
    memcpy(Lcopy, L, N*N*sizeof(double));
    memcpy(Ucopy, U, N*N*sizeof(double));
    
    eye(N, E);
    subtract_mat_mat(N, E, Lcopy);
    add_mat_mat(N, Lcopy, Ucopy);
    printmat("A_LU", N, Ucopy);
    printmat("P", N, P);
    
    multiply_mat_mat(N, P, A);
    multiply_mat_mat(N, L, U);
    
    printmat("P * A", N, A);
    printmat("L * U", N, U);
    
    printf("=================\n");
    printf("Result\n");
    subtract_mat_mat(N, U, A);
    printmat("P * A - L * U", N, A);
    
    return 0;
}
#endif