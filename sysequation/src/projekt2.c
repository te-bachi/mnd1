
#include "projekt2.h"

#define M 8
#define N 5

int
main(int argc, const char *argv[])
{
    double A[M][N] = {
        {  2,  2,  3,  6,  2 },
        {  1,  7,  5,  2,  7 },
        {  4,  1,  2,  3,  1 },
        {  6,  2,  2,  4,  8 },
        {  1,  3,  7,  2,  9 },
        {  1,  2,  3,  4,  5 },
        {  9,  8,  7,  5,  4 },
        {  5,  4,  5,  4,  5 }

    };
    double Q[M][M];
    double R[M][N];

    /*
    double A[M][N] = {
        {  3,  7 },
        {  0, 12 },
        {  4,  1 }
    };
    double Q[M][N];
    double R[M][N];
    double d[N];
    double b[M] = {
        1,
        1,
        1
    };
    double QTb[N];
    */
    //double x[N];

    printf("A[0][3] = 6? %s\n", A[0][3] == 6 ? "yes" : "no");
    printf("A[2][0] = 4? %s\n", A[2][0] == 4 ? "yes" : "no");
    printf("A[3][1] = 2? %s\n", A[3][1] == 2 ? "yes" : "no");

    qr_householder(M, N, A, Q, R);
    //qr_householder_b(M, N, A, Q, R, QTb, b, d);
    //backward()
    printmat("A", M, N, A);
    printmat("Q", M, M, Q);
    printmat("R", M, N, R);


    multiply_mat_mat(M, M, N, Q, R, R);
    printmat("Q * R = A", M, N, R);

    //printvec("QTb", N, QTb);

    return 0;

}
