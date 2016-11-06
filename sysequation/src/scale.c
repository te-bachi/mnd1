
#include "scale.h"

#include <string.h>
#include <math.h>
#include <stdlib.h>

/**
 * Skaliert die Matrix A so, dass pro Zeile die Summe
 * aller Spalten-Elemente gleich 1 sein sollen.
 *
 * @param[in]       n       Dimension
 * @param[in,out]   A       Koeffizienten-Matrix
 */
void
scale(const int n, double A[n][n])
{
    int     i;
    int     k;
    double  d;
    
    for (i = 0; i < n; i++) {
        d = 0.0;
        for (k = 0; k < n; k++) {
            d += fabs(A[i][k]);
        }
        d = 1.0 / d;
        for (k = 0; k < n; k++) {
            A[i][k] *= d;
        }
    }
}

/**
 * Skaliert die Matrix A und den Vektor b so, dass pro Zeile die Summe
 * aller Spalten-Elemente gleich 1 sein sollen.
 *
 * @param[in]       n       Dimension
 * @param[in,out]   A       Koeffizienten-Matrix
 * @param[in,out]   b       Rechte Seite Vektor
 * @param[out]      d       Skalierungs-Vektor
 */
void
scale_ab(const int n, double A[n][n], double b[n])
{
    int     i;
    int     k;
    double  d;
    
    for (i = 0; i < n; i++) {
        d = 0;
        for (k = 0; k < n; k++) {
            d += fabs(A[i][k]);
        }
        d = 1.0 / d;
        for (k = 0; k < n; k++) {
            A[i][k] *= d;
        }
        b[i] *= d;
    }
}

#ifdef __SCALE_MAIN__

#include "print.h"

#define N 4

int
main(int argc, const char *argv[])
{
    double  A[N][N] = {
        {   2,  -1,  -3,   3 },
        {   4,   0,  -3,   1 },
        {   6,   1,  -1,   6 },
        {  -2,  -5,   4,   1 }
    };
    
    double b[N] = {
          1,
         -8,
        -16,
        -12
    };
    
    
    printf("Vorher:\n");
    printmat_ab(N, A, b);
    
    scale_ab(N, A, b);
    
    printf("==============\n");
    
    printf("Nachher:\n");
    printmat_ab(N, A, b);
    
    return 0;
}
#endif
