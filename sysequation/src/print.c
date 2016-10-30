#include "print.h"


void
printvec(const int n, double x[n])
{
    int j;
    
    for(j = 0; j < n; j++) {
        printf("%f\n",x[j]);
    }
}

void
printmat(const int n, double A[n][n], double *b)
{
    int i;
    int j;
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%6.2f\t", A[i][j]);
        }
        printf("\t%6.2f\n", b[i]);
    }
    printf("\n");
}
