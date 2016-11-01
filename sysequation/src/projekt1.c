
#include "forward.h"
#include "backward.h"
#include "lu.h"
#include "multiply.h"
#include "print.h"

#define N 4

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
    
    /*
    double  A[N][N] = {
        {   1,   0,   0,   0 },
        {   2,   1,   0,   0 },
        {   4,   2,   1,   0 },
        {   6,   4,   2,   1 }
    };
    
    double b[N] = {
          1,
          3,
          5,
          7
    };
    */
    
    double d[N];
    double y[N];
    double x[N];
    double L[N][N];
    double U[N][N];
    double P[N][N];
    
    printmat("A", N, A);
    printvec("b", N, b);
    
    scale(N, A, b, d);
    lu(N, A, L, U, P);
    multiply_mat_vec(N, P, b);
    forward(N, L, y, b);
    backward(N, U, x, y);
    
    printmat("P", N, P);
    printvec("x", N, x);
    
    return 0;
}