
#include "matmath.h"
#include <string.h>
#include <stdlib.h>

/**
 * Erstelle eine Einheitsmatrix
 *
 * @param[in]       n       Dimension
 * @param[out]      A       Matrix
 */
void
eye(const int n, double A[n][n])
{
    int i;
    int j;
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == j) {
                A[i][j] = 1.0;
            } else {
                A[i][j] = 0.0;
            }
        }
    }
}

/**
 * Addiere eine Matrix A mit einer Matrix B.
 * Das Resultat wird in B gespeichert.
 *
 * @param[in]       n       Dimension
 * @param[in]       A       Matrix
 * @param[in,out]   B       Matrix
 */
void
add_mat_mat(const int n, const double A[n][n], double B[n][n])
{
    int i;
    int j;
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            B[i][j] += A[i][j];
        }
    }
}

/**
 * Addiere ein Vektor u mit einem Vektor v.
 * Das Resultat wird in v gespeichert.
 *
 * @param[in]       n       Dimension
 * @param[in]       u       Vektor
 * @param[in,out]   v       Vektor
 */
void
add_vec_vec(const int n, const double u[n], double v[n])
{
    int i;
    
    for (i = 0; i < n; i++) {
        v[i] += u[i];
    }
}

/**
 * Subtrahiere eine Matrix A von einer Matrix B.
 * Das Resultat wird in B gespeichert.
 *
 * @param[in]       n       Dimension
 * @param[in]       A       Matrix
 * @param[in,out]   B       Matrix
 */
void
subtract_mat_mat(const int n, const double A[n][n], double B[n][n])
{
    int i;
    int j;
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            B[i][j] -= A[i][j];
        }
    }
}

/**
 * Subtrahiere ein Vektor u von einem Vektor v.
 * Das Resultat wird in v gespeichert.
 *
 * @param[in]       n       Dimension
 * @param[in]       u       Vektor
 * @param[in,out]   v       Vektor
 */
void
subtract_vec_vec(const int n, const double u[n], double v[n])
{
    int i;
    
    for (i = 0; i < n; i++) {
        v[i] -= u[i];
    }
}

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

#ifdef __MATMATH_MAIN__

#include "print.h"

#define N 3

void main_add(const int n, double A[n][n], double B[n][n], double u[n], double v[n]);
void main_multiply(const int n, double A[n][n], double B[n][n], double v[n]);


void
main_add(const int n, double A[n][n], double B[n][n], double u[n], double v[n])
{
    double Y[n][n];
    double Z[n][n];
    double w[n];
    double x[n];
    
    memcpy(Y, A, n*n*sizeof(double));
    memcpy(Z, B, n*n*sizeof(double));
    memcpy(w, u, n*sizeof(double));
    memcpy(x, v, n*sizeof(double));
    
    printf("====================\n");
    printf("Addition:\n");
    
    printmat("Y", N, Y);
    printmat("Z", N, Z);
    printvec("w", N, w);
    printvec("x", N, x);
    
    add_mat_mat(N, Y, Z);
    add_vec_vec(N, w, x);
    
    printf("------\n");
    printmat("Y", N, Y);
    printmat("Z", N, Z);
    printvec("w", N, w);
    printvec("x", N, x);
}

void
main_multiply(const int n, double A[n][n], double B[n][n], double v[n])
{
    double Y[n][n];
    double Z[n][n];
    double x[n];
    
    memcpy(Y, A, n*n*sizeof(double));
    memcpy(Z, B, n*n*sizeof(double));
    memcpy(x, v, n*sizeof(double));
    
    printf("====================\n");
    printf("Multiplikation:\n");
    
    printmat("Y", N, Y);
    printmat("Z", N, Z);
    printvec("x", N, x);
    
    multiply_mat_mat(N, Y, Z);
    multiply_mat_vec(N, Y, x);
    
    printf("------\n");
    printmat("Y", N, Y);
    printmat("Z", N, Z);
    printvec("x", N, x);
}

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
    
    double u[N] = {
        4,
        6,
        8
    };
    
    double v[N] = {
        1,
        2,
        3
    };
    
    main_add(N, A, B, u, v);
    main_multiply(N, A, B, v);
    
    return 0;
}

#endif
