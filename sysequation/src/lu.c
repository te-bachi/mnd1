
#include "lu.h"
#include "swap.h"
#include "scale.h"
#include "print.h"

#include <string.h>
#include <math.h>
#include <stdlib.h>

/**
 * Zerlegt eine Matrix A in eine untere Matrix L und
 * eine obere Matrix U. Durch Spaltenpivotisierung
 * k�nnen Zeilen in L und U vertauscht werden, sodass
 * L * U = P * A
 *
 * @param[in]       n       Dimension
 * @param[in]       A       Matrix
 * @param[out]      L       Untere (Lower) Dreiecksmatrix 
 * @param[out]      U       Obere (Upper) Dreiecksmatrix
 * @param[out]      P       Permutationsmatrix
 */
void
lu(const int n, const double A[n][n], double L[n][n], double U[n][n], double P[n][n])
{
    int i;
    int j;
    int k;
#if PIVOT
    int p;
#endif
    
    memset(L, 0, n*n*sizeof(double));
    memcpy(U, A, n*n*sizeof(double));
    memset(P, 0, n*n*sizeof(double));
    for (j = 0; j < n; j++) {
        P[j][j] = 1;
    }
    
#if PIVOT
    for (j = 0; j < n; j++) {
        /* Spaltenmaximum */
        p = j;
        for (i = j + 1; i < n; i++) {
            if (fabs(A[p][j]) < fabs(A[i][j])) {
                p = i;
            }
        }
        if (p != j) {
            swap(n, P, j, p);
            swap(n, U, j, p);
        }
    }
#endif
    
    for (j = 0; j < n; j++) {
        L[j][j] = 1;
        
#if !PIVOT
        if (A[j][j] == 0) {
            printf("A[%d][%d] = 0, Exit!\n", j, j);
            exit(-1);
        }
#endif
        
        /* LU */
        if (j < (n - 1)) {
            for (i = j + 1; i < n; i++) {
                L[i][j] = U[i][j] / U[j][j];
                for (k = j; k < n; k++) {
                    U[i][k] = U[i][k] - (L[i][j] * U[j][k]);
                }
            }
        }
    }
}

#ifdef __LU_MAIN__
#define N 4

int
main(int argc, const char *argv[])
{
    double  A[N][N] = {
        {   2,  -1,  -3,   3 },
        {   4,   1,  -3,   1 },
        {   6,   1,  -1,   6 },
        {  -2,  -5,   4,   1 }
    };
    
    /*
    double  A[N][N] = {
        {   1,   2,   3 },
        {   1,   1,   1 },
        {   3,   3,   1 }
    };
    */
    
    /*
    double  A[N][N] = {
        {   1,   2,   3 },
        {   1,   1,   1 },
        {   3,   3,   1 }
    };
    */
    
    /*
    double A[N][N] = {
        { 0.00031,  1 },
        {       1,  1 }
    };
    */
    
    double b[N] = {
        0,
        0,
        0
    };
    
    double L[N][N];
    double U[N][N];
    double P[N][N];
    
    printmat("A", N, A);
    scale_ab(N, A, b);
    lu(N, A, L, U, P);
    
    return 0;
}
#endif
