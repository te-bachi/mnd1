
#include "error.h"

#include <math.h>

double
error_max(const int n, const double A[n][n])
{
    int     i;
    int     j;
    double  error = 0.0;
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (error < fabs(A[i][j])) {
                error = fabs(A[i][j]);
            }
        }
    }
    
    return error;
}
