
#include "projekt1.h"

#define N 4

void
main_inv(void)
{
    double  A[N][N] = {
        {   2,  -1,  -3,   3 },
        {   4,   0,  -3,   1 },
        {   6,   1,  -1,   6 },
        {  -2,  -5,   4,   1 }
    };
    
    double I[N][N];
    
    printf("========================================\n");
    printf("Inverse\n");
    
    inverse(N, A, I);
    printmat("A", N, A);
    printmat("A", N, A);
    printmat("I", N, I);
}
