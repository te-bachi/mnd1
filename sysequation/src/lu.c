
#include "lu.h"
#include "swap.h"
#include "print.h"

#include <string.h>
#include <math.h>
#include <stdlib.h>

void
lu(int n, double A[n][n], double L[n][n], double U[n][n], double P[n][n])
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
    printmat("P", n, P);
    
    for (j = 0; j < n; j++) {
        L[j][j] = 1;
        
#if PIVOT
        /* Spaltenmaximum */
        p = j;
        for (i = j + 1; i < n; i++) {
            if (fabs(A[p][j]) < fabs(A[i][j])) {
                p = i;
            }
        }
        printf("p = %d\n", p);
        if (p != j) {
            swap(n, P, j, p);
            swap(n, A, j, p);
            printmat("P", n, P);
        }
#else
        if (A[j][j] == 0) {
            printf("A[%d][%d] = 0, Exit!\n", j, j);
            exit(-1);
        }
#endif
        
        /* LU */
        printf("=== %d ====================\n", j);
        if (j < (n - 1)) {
            for (i = j + 1; i < n; i++) {
                L[i][j] = U[i][j] / U[j][j];
                printf("l[%d] = %5.2f\n", i, L[i][j]);
                for (k = j; k < n; k++) {
                    U[i][k] = U[i][k] - (L[i][j] * U[j][k]);
                }
            }
        }
        
        printmat("L", n, L);
        printmat("U", n, U);
    }
}

void
lu_gauss(int n, double A[n][n], double L[n][n], double R[n][n], double b[n])
{
    
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
    
    double d[N];
    double L[N][N];
    double U[N][N];
    double P[N][N];
    
    printmat("A", N, A);
    scale(N, A, b, d);
    lu(N, A, L, U, P);
    
    return 0;
}
#endif
