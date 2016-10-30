
#include "lu.h"
#include "print.h"

#include <string.h>

void
lu(int n, double A[n][n], double L[n][n], double R[n][n])
{
    int i;
    int j;
    int k;
    
    memset(L, 0, n*n*sizeof(double));
    memcpy(R, A, n*n*sizeof(double));
    
    for (j = 0; j < n; j++) {
        L[j][j] = 1;
        printf("=== %d ====================\n", j);
        if (j < (n - 1) && A[j][j] != 0) {
            for (i = j + 1; i < n; i++) {
                L[i][j] = A[i][j] / A[j][j];
                printf("l[%d] = %5.2f\n", i, L[i][j]);
                for (k = j; k < n; k++) {
                    R[i][k] = A[i][k] - (L[i][j] * A[j][k]);
                }
            }
        }
        
        printmat(n, L);
        printmat(n, R);
    }
}

#ifdef __LU_MAIN__
#define N 3

int
main(int argc, const char *argv[])
{
    double  A[N][N] = {
        {   1,   2,   3 },
        {   1,   1,   1 },
        {   3,   3,   1 }
    };
    
    double L[N][N];
    double U[N][N];
    
    printmat(N, A);
    lu(N, A, L, U);
    
    return 0;
}
#endif