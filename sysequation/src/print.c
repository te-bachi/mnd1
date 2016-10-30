#include "print.h"

#define FORMAT  "%12.8f"
void
printvec(const char *var, const int n, double x[n])
{
    int j;
    
    printf("%s = [\n", var);
    for(j = 0; j < n; j++) {
        printf("\t" FORMAT ";\n",x[j]);
    }
    printf("]\n");
}

void
printmat(const char *var, const int n, double A[n][n])
{
    int i;
    int j;
    
    printf("%s = [\n", var);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf(FORMAT "\t", A[i][j]);
        }
        printf(";\n");
    }
    printf("]\n");
}

void
printmat_ab(const int n, double A[n][n], double *b)
{
    int i;
    int j;
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf(FORMAT "\t", A[i][j]);
        }
        printf("\t" FORMAT "\n", b[i]);
    }
    printf("\n");
}
