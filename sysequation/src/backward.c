
#include <stdio.h>

#include "backward.h"
#include "print.h"

void
backward(int n, double U[n][n], double x[n], double y[n])
{
    double sum;
    int j;
    int i;
    
    /* set last variable */
    /* dimension n=3, array index 0..2 */
    x[n - 1] = y[n - 1] / U[n - 1][n - 1];
        
    for (j = n - 2; j >= 0; j--) {
        sum = 0;
        for (i = j + 1; i < n; i++) {
            sum += U[j][i] * x[i];
        }
        
        x[j] = (y[j] - sum) / U[j][j];
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
    
    backward(N, A, x, b);
    printvec("x", N, x);
    
    return 0;
}
#endif
