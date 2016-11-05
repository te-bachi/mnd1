
#include "scale.h"
#include "print.h"

#include <string.h>
#include <math.h>
#include <stdlib.h>

/**
 * Skaliert die Matrix A|b so, dass pro Zeile die Summe aller Spalten-Elemente
 * gleich 1 sein sollen.
 *
 * @param[in]       n       Dimension
 * @param[in,out]   A       Koeffizienten-Matrix
 * @param[in,out]   b       Rechte Seite Vektor
 * @param[out]      d       Skalierungs-Vektor
 */
void
scale(const int n, double A[n][n], double b[n], double d[n])
{
    int i;
    int k;
    
    for (i = 0; i < n; i++) {
        d[i] = 0;
        for (k = 0; k < n; k++) {
            d[i] += fabs(A[i][k]);
        }
        d[i] = 1.0 / d[i];
        for (k = 0; k < n; k++) {
            A[i][k] *= d[i];
        }
        b[i] *= d[i];
    }
}

#ifdef __SCALE_MAIN__

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
    
    double d[N];
    
    printf("Vorher:\n");
    printmat_ab(N, A, b);
    
    scale(N, A, b, d);
    
    printf("==============\n");
    printvec("d", N, d);
    printf("==============\n");
    
    printf("Nachher:\n");
    printmat_ab(N, A, b);
    
    return 0;
}
#endif
