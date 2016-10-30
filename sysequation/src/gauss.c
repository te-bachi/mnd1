
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>

#define N 4


void printmat(double A[N][N], double *b);
void gauss(double A[N][N], double *b, double *x);

void
printmat(double A[N][N], double *b)
{
    int i;
    int j;
    
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%6.2f\t", A[i][j]);
        }
        printf("\t%6.2f\n", b[i]);
    }
    printf("\n");
}

void
gauss(double A[N][N], double *b, double *x)
{
    int i;
    int j;
    int k;
    double l;
    
    for (j = 0; j < (N - 1); j++) {
        printf("=== %d ====================\n", j);
        if (A[j][j] != 0) {
            for (i = j + 1; i < N; i++) {
                l = A[i][j] / A[j][j];
                for (k = j; k < N; k++) {
                    A[i][k] = A[i][k] - (l * A[j][k]);
                }
                b[i] = b[i] - (l * b[j]);
            }
        }
        
        printmat(A, b);
    }
}

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
    
    printmat(A, b);
    gauss(A, b, x);
    
    return 0;
}