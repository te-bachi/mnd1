
#include "forward.h"
#include "matmath.h"

#include <string.h>

/**
 * Vorw�rtseinsetzen: berechne die L�sung y von L * y = b
 *
 * @param[in]       n       Dimension
 * @param[in]       L       Untere Dreiecksmatrix
 * @param[in]       b       Rechte Seite Vektor
 * @param[out]      y       L�sungsvektor
 */
void
forward(const int n, const double L[n][n], const double b[n], double y[n])
{
    int i;
    int j;
    double sum;
    
    /* Setze erste Variable von der ersten Zeile einfach ein */
    y[0] = b[0];
    
    /* Iteriere �ber alle Zeilen:
     * - beginnend mit der zweiten Zeile
     * - L�se L�sungsvektor nach y[i] auf */
    for (i = 1; i < n; i++) {
        sum = 0;
        
        /* Iteriere �ber alle Spalten:
         * Summiere alle Multiplikationen von
         * Spalten-Elemente L[i][j] einer Zeile mit dem
         * schon gel�sen L�sungsvektor y[j] auf */
        for (j = 0; j < i; j++) {
            sum += (L[i][j] * y[j]);
        }
        
        /* L�se L�sungsvektor y[i] */
        y[i] = (b[i] - sum) / L[i][i];
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
    forward(N, A, b, y);
    
    printvec("y", N, y);
    
    return 0;
}

#endif
