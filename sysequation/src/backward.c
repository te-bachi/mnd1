
#include <stdio.h>

#include "backward.h"
#include "print.h"

/**
 * Rückwärtseinsetzen: berechne die Lösung x von R * x = y
 *
 * @param[in]       n       Dimension
 * @param[in]       U       Obere Dreiecksmatrix
 * @param[in]       y       Rechte Seite Vektor
 * @param[out]      x       Lösungsvektor
 */
void
backward(const int n, const double U[n][n], const double y[n], double x[n])
{
    double sum;
    int i;
    int j;
    
    /* Setze letzte Variable von der letzten Zeile einfach ein */
    x[n - 1] = y[n - 1] / U[n - 1][n - 1];
    
    /* Iteriere über alle Zeilen:
     * - beginnend mit der vorletzten Zeile
     * - Löse Lösungsvektor nach x[i] auf */
    for (i = n - 2; i >= 0; i--) {
        sum = 0;
        
        /* Iteriere über alle Spalten:
         * Summiere alle Multiplikationen von
         * Spalten-Elemente U[i][j] einer Zeile mit dem
         * schon gelösen Lösungsvektor x[j] auf */
        for (j = i + 1; j < n; j++) {
            sum += U[i][j] * x[j];
        }
        
        /* Löse Lösungsvektor x[i] */
        x[i] = (y[i] - sum) / U[i][i];
    }
    
    
};


#ifdef __BACKWARD_MAIN__

#define N 3

int main(int argc, const char * argv[]) {
    double A[N][N] = {
        {  3, -1,  2 },
        {  0,  1,  3 },
        {  0,  0,  2 }
    };
    double b[N] = { 0, 1, 4 };
    double x[N];
    
    printmat("A", N, A);
    printvec("b", N, b);
    backward(N, A, b, x);
    printvec("x", N, x);
    
    return 0;
}
#endif
