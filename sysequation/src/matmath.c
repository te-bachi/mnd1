
#include "matmath.h"

#include <string.h>
#include <stdlib.h>
#include <math.h>

/**
 * Signum-Funktion
 *
 */
double
signum(double x)
{
    if (x  > 0.0) return  1.0;
    if (x  < 0.0) return -1.0;
    return 0.0;
}

/**
 * Erstelle eine Einheitsmatrix
 *
 * @param[in]       n       Dimension
 * @param[out]      A       Matrix
 */
void
eye_square(const int n, double A[n][n])
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

void
zeros_square(const int n, double A[n][n])
{
    int i;
    int j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            A[i][j] = 0.0;
        }
    }
}

void
ones_square(const int n, double A[n][n])
{
    int i;
    int j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            A[i][j] = 1.0;
        }
    }
}

/**
 * Transponiert die Matrix
 * Das Resultat wird wieder in Matrix A zurückgespeichert!
 *
 * @param[in]       n       Dimension
 * @param[in,out]   A       Matrix, die transponiert wird
 */
void
transpose_square(const int n, double A[n][n])
{
    int     i;
    int     j;
    double  a;
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < i; j++) {
            a       = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = a;
        }
    }
}

/**
 * Berechne das Skalarprodukt von Vektor v mit Vektor w
 *
 * @param[in]       n       Dimension
 * @param[in]       v       Erster Vektor
 * @param[in]       w       Zweiter Vektor
 * @return                  Das Skalarprodukt
 */
double
scalarproduct(const int n, const double v[n], const double w[n])
{
    double  sum = 0.0;
    int     i;

    for(i = 0; i < n; i++) {
        sum += v[i] * w[i];
    }
    return sum;
}

/**
 * Berechne die Euklidische Norm vom Vektor v
 *
 * @param[in]       n       Dimension
 * @param[in]       v       Vektor
 * @return                  Die Euklidische Norm
 */
double
euklid_norm_vec(const int n, const double v[n])
{
    double  d = 0.0;
    int     i;

    /* Gehe über die Zeilen und addiere
     * jedes Quadrat-Element auf */
    for (i = 0; i < n; i++) {
        d += v[i] * v[i];
    }
    /* Ziehe die Wurzel */
    d = sqrt(d);

    return d;
}

/**
 * Dupliziere die Matrix A und speichere sie
 * in Matrix B
 *
 * @param[in]       n       Dimension
 * @param[in]       A       Eingabe Matrix
 * @param[in,out]   B       Ausgabe Matrix
 */
void
duplicate_mat(const int n, const double A[n][n], double B[n][n])
{
    memcpy(B, A, n*n*sizeof(double));
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
multiply_mat_mat_square(const int n, const double A[n][n], double B[n][n])
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
multiply_mat_vec_square(const int n, const double A[n][n], double v[n])
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

/**
 * Multipliziert eine Matrix A[m][o] mit einer Matrix B[o][n]
 *
 * @param[in]       m       Anzahl Zeilen Matrix A
 * @param[in]       o       Anzahl Spalten Matrix A / Anzahl Zeilen Matrix B
 * @param[in]       n       Anzahl Spalten Matrix B
 * @param[in]       A       Matrix
 * @param[in]       B       Matrix
 * @param[out]      C       Matrix;
 */
void
multiply_mat_mat(const int m, const int o, const int n, const double A[m][o], const double B[o][n], double C[m][n])
{
    int i;
    int j;
    int k;
    double T[m][n];

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            T[i][j] = 0.0;
            for (k = 0; k < o; k++) {
                T[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    memcpy(C, T, m*n*sizeof(double));
}

/**
 * Multipliziert ein Vektor v mit einem Vektor w.
 * Das Resultat wird in C gespeichert.
 *
 * @param[in]       m       Dimension
 * @param[in]       A       Vektor v[m]
 * @param[in]       n       Dimension
 * @param[in]       w       Vektor w[n]
 * @param[out]      C       Matrix C[m][n]
 */
void
multiply_vec_vec_to_mat(const int m, const double v[m], const int n, const double w[n], double C[m][n])
{
    int     i;
    int     j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            C[i][j] = v[i] * w[j];
        }
    }
}

#ifdef __MATMATH_MAIN__

#include "print.h"

#define N 3

void main_add(const int n, double A[n][n], double B[n][n], double u[n], double v[n]);
void main_multiply(void);
void main_multiply_square(const int n, double A[n][n], double B[n][n], double v[n]);
void main_scalarproduct(const int n, const double u[n], const double v[n]);
void main_vec_to_mat(const int m, const double x[m], const int n, const double y[n]);

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
    
    printmat_square("Y", N, Y);
    printmat_square("Z", N, Z);
    printvec("w", N, w);
    printvec("x", N, x);
    
    add_mat_mat(N, Y, Z);
    add_vec_vec(N, w, x);
    
    printf("------\n");
    printmat_square("Y", N, Y);
    printmat_square("Z", N, Z);
    printvec("w", N, w);
    printvec("x", N, x);
}

void
main_multiply_square(const int n, double A[n][n], double B[n][n], double v[n])
{
    double Y[n][n];
    double Z[n][n];
    double x[n];
    
    memcpy(Y, A, n*n*sizeof(double));
    memcpy(Z, B, n*n*sizeof(double));
    memcpy(x, v, n*sizeof(double));
    
    printf("====================\n");
    printf("Multiplikation Quadratisch:\n");
    
    printmat_square("Y", N, Y);
    printmat_square("Z", N, Z);
    printvec("x", N, x);
    
    multiply_mat_mat_square(N, Y, Z);
    multiply_mat_vec_square(N, Y, x);
    
    printf("------\n");
    printmat_square("Y * Z", N, Z);
    printvec("Y * x", N, x);
}

void
main_multiply(void)
{
    double X[3][5] = {
        {  1,  2,  3,  4,  5 },
        {  2,  3,  4,  5,  6 },
        {  1,  1,  1,  1,  1 }
    };
    double Y[5][2] = {
        {  2,  3 },
        {  3,  4 },
        {  4,  5 },
        {  5,  6 },
        {  6,  7 }
    };
    double Z[3][2];

    printf("====================\n");
    printf("Multiplikation:\n");

    printmat("X", 3, 5, X);
    printmat("Y", 5, 2, Y);

    multiply_mat_mat(3, 5, 2, X, Y, Z);

    printf("------\n");
    printmat("X * Y = Z", 3, 2, Z);
}

void
main_scalarproduct(const int n, const double u[n], const double v[n])
{
    double s;

    printf("====================\n");
    printf("Skalarprodukt:\n");
    printvec("u", n, u);
    printvec("v", n, v);
    s = scalarproduct(n, u, v);
    printf("s = %12.8f\n", s);

}

void
main_vec_to_mat(const int m, const double x[m], const int n, const double y[n])
{
    double C[m][n];

    printf("====================\n");
    printf("Vektorprodukt als Matrix:\n");
    printvec("x", m, x);
    printvec("y", n, y);
    multiply_vec_vec_to_mat(m, x, n, y, C);
    printmat("C", m, n, C);

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
    
    double x[6] = {
        1,
        2,
        3,
        4,
        5,
        6
    };

    double y[4] = {
        2,
        3,
        4,
        5,
    };


    main_add(N, A, B, u, v);
    main_multiply();
    main_multiply_square(N, A, B, v);
    main_scalarproduct(N, u, v);
    main_vec_to_mat(6, x, 4, y);

    return 0;
}

#endif
