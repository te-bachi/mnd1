
#include "scale.h"
#include "print.h"

#include <string.h>
#include <math.h>
#include <stdlib.h>

void
scale(int n, double A[n][n], double b[n], double d[n])
{
#if SCALE == 1
    int i;
    int k;

    printf("=== SCALE =================\n");
    for (i = 0; i < n; i++) {
        d[i] = 0;
        for (k = 0; k < n; k++) {
            d[i] += fabs(A[i][k]);
        }
        d[i] = 1.0 / d[i];
        for (k = 0; k < n; k++) {
            A[i][k] *= d[i];
        }
    }
    printmat("A", n, A);
#endif
}
