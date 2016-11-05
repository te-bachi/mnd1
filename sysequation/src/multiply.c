
#include "multiply.h"
#include <string.h>
#include <stdlib.h>

/**
 * Multipliziert eine Matrix A mit einer Matrix B.
 * Das Resultat wird in B gespeichert.
 *
 * @param[in]       n       Dimension
 * @param[in]       A       Matrix
 * @param[in,out]   B       Matrix
 */
void
multiply_mat_mat(const int n, const double A[n][n], double B[n][n])
{
    int i;
    int j;
    int k;
    double sum;
    double T[n][n];
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            sum = 0.0;
            for (k = 0; k < n; k++) {
                sum += A[i][k] * B[k][j];
            }
            T[i][j] = sum;
        }
    }
    
    memcpy(B, T, n*n*sizeof(double));
}

/**
 * Multipliziert eine Matrix A mit einem Vektor v.
 * Das Resultat wird in v gespeichert.
 *
 * @param[in]       n       Dimension
 * @param[in]       A       Matrix
 * @param[in,out]   v       Vektor
 */
void
multiply_mat_vec(const int n, const double A[n][n], double v[n])
{
    int i;
    int k;
    double sum;
    double T[n];
    
    for (i = 0; i < n; i++) {
        sum = 0.0;
        for (k = 0; k < n; k++) {
            sum += A[i][k] * v[k];
        }
        T[i] = sum;
    }
    
    memcpy(v, T, n*sizeof(double));
}

#ifdef __MULTIPLY_MAIN__

#include "print.h"

#define N 3

int
main(int argc, const char *argv[])
{
    
    double A[N][N] = {
        {   1,   2,   3 },
        {   2,   3,   4 },
        {   3,   4,   5 }
    };
    
    double B[N][N] = {
        {   2,   2,   2 },
        {   2,   2,   2 },
        {   2,   2,   2 }
    };
    
    double v[N] = {
        1,
        2,
        3
    };
    
    printmat("A", N, A);
    printmat("B", N, B);
    printvec("v", N, v);
    
    multiply_mat_mat(N, A, B);
    multiply_mat_vec(N, A, v);
    
    printf("====================\n");
    printmat("A", N, A);
    printmat("B", N, B);
    printvec("v", N, v);
    
    return 0;
}

#endif
