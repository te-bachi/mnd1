
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>

#include "gauss.h"
#include "backward.h"
#include "print.h"

/**
 * Gauss-Elimination ohne Pivotisierung.
 * Bringt die Matix A auf Dreiecksgestalt durch
 * Umformen von Matrix A und Vektor b pro Zeile.
 * ACHTUNG: Diagonalelemente dürfen keine 0 enthalten!
 * 
 * @param[in]       n       Dimension
 * @param[in,out]   A       Koeffizienten-Matrix
 * @param[in,out]   b       Rechte Seite Vektor
 */
void
gauss(const int n, double A[n][n], double b[n])
{
    int i;
    int j;
    int k;
    double l;
    
    for (j = 0; j < (n - 1); j++) {
        if (A[j][j] == 0) {
            printf("A[%d][%d] = 0, Exit!\n", j, j);
            exit(-1);
        } 
        
        for (i = j + 1; i < n; i++) {
            l = A[i][j] / A[j][j];
            for (k = j; k < n; k++) {
                A[i][k] = A[i][k] - (l * A[j][k]);
            }
            b[i] = b[i] - (l * b[j]);
        }
    }
}


#ifdef __GAUSS_MAIN__

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
    
    double x[N] = {
        0,
        0,
        0,
        0
    };
    
    printmat_ab(N, A, b);
    gauss(N, A, b);
    backward(N, A, b, x);
    printvec("x", N, x);
    
    return 0;
}
#endif
