
#include "swap.h"

/**
 * Tauscht zwei Zeilen einer Matrix A
 *
 * @param[in]       n       Dimension
 * @param[in,out]   A       Koeffizienten-Matrix
 * @param[in]       i       Erste Zeile
 * @param[in]       p       Zweite Zeile
 */
void
swap(const int n, double A[n][n], const int i, const int p)
{
    int     k;
    double  t;
    
    /* Zeilen sind bekannt. Tausche nur Spalten. */
    for (k = 0; k < n; k++) {
        t       = A[i][k];
        A[i][k] = A[p][k];
        A[p][k] = t;
    }
}

#ifdef __SWAP_MAIN__

#include "print.h"

#define N 4

int
main(int argc, const char *argv[])
{
    /*
    A = [
      1   1   1   1;
      1   2   3   4;
      5   5   5   5;
      6   7   8   9;
    ];
    */
    double  A[N][N] = {
        {   1,   1,   1,   1 },
        {   1,   2,   3,   4 },
        {   5,   5,   5,   5 },
        {   6,   7,   8,   9 }
    };
    
    printmat_square("A", N, A);
    
    /*
    A = [
      6   7   8   9;
      1   2   3   4;
      5   5   5   5;
      1   1   1   1;
    ];
    */
    swap(N, A, 0, 3);
    printmat_square("A", N, A);
    
    
    /*
    A = [
      1   1   1   1;
      5   5   5   5;
      1   2   3   4;
      6   7   8   9;
    ];
    */
    swap(N, A, 1, 2);
    printmat_square("A", N, A);
    
    return 0;
}
#endif
