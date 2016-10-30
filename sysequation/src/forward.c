
#include "forward.h"

#include <string.h>

void
forward(int n, double L[n][n], double y[n], double b[n])
{
    int i;
    int k;
    double sum;
    
    memset(y, 0, n*sizeof(double));
    
    y[0] = b[0];
    
    for (i = 1; i < n; i++) {
        sum = 0;
        for (k = 0; k < i; k++) {
            sum += L[i][k] * y[k];
        }
        y[i] = b[i] - sum;
    }
}
