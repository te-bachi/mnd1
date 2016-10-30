
#include "lu.h"
#include "print.h"

#include <string.h>
#include <math.h>

void
lu(int n, double A[n][n], double L[n][n], double U[n][n], double P[n][n])
{
    int i;
    int j;
    int k;
    int p;
    double d[n];
    
    memset(d, 0, n*sizeof(double));
    memset(L, 0, n*n*sizeof(double));
    memcpy(U, A, n*n*sizeof(double));
    memset(P, 0, n*n*sizeof(double));
    
    /* Permutation */
    //for (i = 0; i < n; i++) {
    //    P[i][i] = 1;
    //}
    //printmat("P", n, P);
    
    /* Skalierung */
    ///*
    printf("=== SCALE =================\n");
    for (i = 0; i < n; i++) {
        d[i] = 0;
        for (k = 0; k < n; k++) {
            d[i] += abs(A[i][k]);
        }
        d[i] = 1.0 / d[i];
        for (k = 0; k < n; k++) {
            A[i][k] *= d[i];
        }
    }
    printmat("A", n, A);
    //*/
    
    for (j = 0; j < n; j++) {
        L[j][j] = 1;
        /* Spaltenmaximum */
        p = j + 1;
        for (i = j + 1; i < n; i++) {
            if (abs(A[p][j]) < abs(A[i][j])) {
                p = i;
            }
        }
        P[j][p] = 1;
        printmat("P", n, P);
        
        /* LU */
        printf("=== %d ====================\n", j);
        if (j < (n - 1) && A[j][j] != 0) {
            for (i = j + 1; i < n; i++) {
                L[i][j] = A[i][j] / A[j][j];
                printf("l[%d] = %5.2f\n", i, L[i][j]);
                for (k = j; k < n; k++) {
                    U[i][k] = A[i][k] - (L[i][j] * A[j][k]);
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
#define N 3

int
main(int argc, const char *argv[])
{
    ///*
    double  A[N][N] = {
        {   1,   2,   3 },
        {   1,   1,   1 },
        {   3,   3,   1 }
    };
    //*/
    
    /*
    double A[N][N] = {
        { 0.00031,  1 },
        {       1,  1 }
    };
    */
    
    double L[N][N];
    double U[N][N];
    double P[N][N];
    
    printmat("A", N, A);
    lu(N, A, L, U, P);
    
    return 0;
}
#endif