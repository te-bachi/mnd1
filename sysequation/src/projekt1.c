
#include "forward.h"
#include "backward.h"
#include "lu.h"
#include "print.h"

#define N 4

int
main(int argc, const char *argv[])
{
    double  A[N][N] = {
        {   2,  -1,  -3,   3 },
        {   4,   1,  -3,   1 },
        {   6,   1,  -1,   6 },
        {  -2,  -5,   4,   1 }
    };
    
    double b[N] = {
          1,
         -8,
        -16,
        -12
    };
    
    double y[N] = {
        0,
        0,
        0,
        0
    };
    
    double x[N] = {
        0,
        0,
        0,
        0
    };
    
    double L[N][N];
    double U[N][N];
    double P[N][N];
    
    printmat("A", N, A);
    printvec("b", N, b);
    
    lu(N, A, L, U, P);
    forward(N, L, y, b);
    backward(N, U, x, y);
    
    printvec("x", N, x);
    
    return 0;
}