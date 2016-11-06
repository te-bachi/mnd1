
#include "forward.h"
#include "matmath.h"

#include <string.h>

/**
 * Vorwärtseinsetzen: berechne die Lösung y von L * y = b
 *
 * @param[in]       n       Dimension
 * @param[in]       L       Untere Dreiecksmatrix
 * @param[in]       b       Rechte Seite Vektor
 * @param[out]      y       Lösungsvektor
 */
void
forward(const int n, const double P[n][n], const double L[n][n], double b[n], double y[n])
{
    int i;
    int j;
    double sum;
    
    /* Vertausche Zeilen von Vektor b, da Matrix L
     * bei der LU-Zerlegung die Zeilen vertauscht hat. */
    multiply_mat_vec(n, P, b);
    
    /* Setze erste Variable von der ersten Zeile einfach ein */
    y[0] = b[0];
    
    /* Iteriere über alle Zeilen:
     * - beginnend mit der zweiten Zeile
     * - Löse Lösungsvektor nach y[i] auf */
    for (i = 1; i < n; i++) {
        sum = 0;
        
        /* Iteriere über alle Spalten:
         * Summiere alle Multiplikationen von
         * Spalten-Elemente L[i][j] einer Zeile mit dem
         * schon gelösen Lösungsvektor y[j] auf */
        for (j = 0; j < i; j++) {
            sum += (L[i][j] * y[j]);
        }
        
        /* Löse Lösungsvektor y[i] */
        y[i] = (b[i] - sum) / L[i][i];
    }
}

/**
 * Vorwärtseinsetzen mit mehreren rechten Seiten:
 * berechne die Lösung y von L * y(n) = b(n)
 *
 * @param[in]       n       Dimension
 * @param[in]       L       Untere Dreiecksmatrix
 * @param[in]       b       Rechte Seite Vektor
 * @param[out]      y       Lösungsvektor
 */
void
forward_multi(const int n, const double P[n][n], const double L[n][n], const int r, double b[r][n], double y[r][n])
{
    int i;
    
    for (i = 0; i < r; i++) {
        forward(n, P, L, b[i], y[i]);
    }
}

#ifdef __FORWARD_MAIN__

#include "print.h"

#define N 4

int
main(int argc, const char *argv[])
{
    /*
    double  A[N][N] = {
        {   1,   0,   0,   0 },
        {   1,   2,   0,   0 },
        {   1,   2,   4,   0 },
        {   1,   2,   4,   6 }
    };
    
    double b[N] = {
          1,
          2,
          4,
          6
    };
    */
    
    double A[N][N] = {
        {   1,   0,   0,   0 },
        {   2,   1,   0,   0 },
        {   4,   2,   1,   0 },
        {   6,   4,   2,   1 }
    };
    
    double P[N][N] = {
        {   1,   0,   0,   0 },
        {   0,   1,   0,   0 },
        {   0,   0,   1,   0 },
        {   0,   0,   0,   1 }
    };
    
    double b[N] = {
          1,
          3,
          5,
          7
    };
    
    double y[N];
    
    printmat("A", N, A);
    printvec("b", N, b);
    
    multiply_mat_vec(N, P, b);
    forward(N, P, A, b, y);
    
    printvec("y", N, y);
    
    return 0;
}

#endif
