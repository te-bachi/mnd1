
#include "hilbert.h"

/**
 * Erstelle eine Hilbert-Matrix
 *
 * @param[in]       n       Dimension
 * @param[out]      A       Hilbert-Matrix
 */
void
hilbert(const int n, double A[n][n])
{
    int i;
    int j;
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            A[i][j] = 1.0 / (((double) i) + ((double) j) + 1);
        }
    }
}

#ifdef __HILBERT_MAIN__

#include "print.h"

#define N 5

int
main(int argc, const char *argv[])
{
    double  A[N][N];
    
    hilbert(N, A);
    printmat("A", N, A);
    
    return 0;
}
#endif
