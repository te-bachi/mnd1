
#include "projekt1.h"

#define N   4
#define N_H 5

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

    double H[N_H][N_H];
    double HI[N_H][N_H];
    double HE[N_H][N_H];
    
    printf("========================================\n");
    printf("Inverse A\n");
    
    inverse(N, A, I);

    printmat("A", N, A);
    printmat("I", N, I);

    printf("\nHilbert 5x5\n");;

    hilbert(N_H, H);
    inverse(N_H, H, HI);
    eye(N_H, HE);

    printmat("H", N_H, H);
    printmat("HI", N_H, HI);

    multiply_mat_mat(N_H, HI, H);
    subtract_mat_mat(N_H, HE, H);
    printmat("HI * H - HE", N_H, H);
    printf("max. error: %g\n", error_max(N_H, H));

}
