
#include "qr.h"
#include "print.h"
#include "matmath.h"

#include <math.h>
#include <string.h>

double qr_givens_sqn(double x);
double qr_givens_sin(double ajj, double aij);
double qr_givens_cos(double ajj, double aij);

void qr_householder_get_yj(const int m, const int n, const int j, double R[m][n], double yj[n]);
void qr_householder_calc_qj(const int m, const int n, const int j, double I[m][m], const double yj[n], double Qj[m][m]);


/**
 * Hole Vektor yj aus Matrix R.
 *   __ __R__ __
 *  |  |__|  |  |
 *  |  |  |__|  |
 * m|  |  |  |__|
 *  |  |  |  |  |
 *  |y1|y2|y3|y4|
 *  |__|__|__|__|
 *        n
 *
 * @param[in]       m       Anzahl Zeilen von R
 * @param[in]       n       Anzahl Spalten von R
 * @param[in]       j       Welche Sub-Spalte yj extrahiert wird
 * @param[in]       R       Matrix R
 * @param[out]      yj      Vektor yj
 */
void
qr_householder_get_yj(const int m, const int n, const int j, double R[m][n], double yj[n])
{
    int k;

    for (k = j; k < m; k++) {
        yj[k - j] = R[k][j];
    }
    printvec("yi", m - j, yj);
}

/**
 * Berechne Matrix Qj:
 * Qj = I(oben-links) + H(unten-rechts)
 *
 *   ______Qj_____
 *  |             |
 *  |  Io ________|
 * m|    | |      |
 *  |    |w| H    |
 *  |    | |      |
 *  |____|_|______|
 *        m
 *
 *   ______I______
 *  |             |
 *  |  Io ________|
 * m|    | |      |
 *  |    |e| Iu   |
 *  |    | |      |
 *  |____|_|______|
 *        m
 *
 *                w * wT
 * H = Iu - 2 * ---------
 *               wT * w
 *
 * w = y + d * e
 *
 * d = sign(y[1]) * norm(y)
 *
 */
void
qr_householder_calc_qj(const int m, const int n, const int j, double I[m][m], const double yj[n], double Qj[m][m])
{
    double      d;
    double      w[m - j];
    double      H[m - j][m - j];
    double      sp;
    int         k;
    int         q;

    /* Berechne Skalar d */
    d = signum(yj[0]) * euklid_norm_vec(m - j, yj);
    printf("d = %12.8f\n", d);

    /* Berechne Vektor w */
    for (k = j; k < m; k++) {
        w[k - j] = yj[k - j] + d * I[k][j];
    }
    printvec("w", m - j, w);

    /* Berechne die Householder-Matrix */
    multiply_vec_vec_to_mat(m - j, w, m - j, w, H);
    sp = scalarproduct(m - j, w, w);
    printf("sp = %12.8f\n", sp);
    for (k = 0; k < (m - j); k++) {
        for (q = 0; q < (m - j); q++) {
            H[k][q] *= 2;
            H[k][q] /= sp;
            H[k][q]  = I[j + k][j + q] - H[k][q];
        }
    }
    printmat("H", m - j, m - j, H);

    /* Initial ist Einheitsmatrix == Qj */
    memcpy(Qj, I, m * m * sizeof(double));

    /* Berechne Matrix Qj */
    for (k = j; k < m; k++) {
        for (q = j; q < m; q++) {
            Qj[k][q] = H[k - j][q - j];
        }
    }
}

void
qr_householder(const int m, const int n, const double A[m][n], double Q[m][m], double R[m][n])
{
    double  I[m][m];
    double  yj[m];
    double  Qj[m][m];
    int     j;

    /*
    double  s;
    double  d[n];
    double  w[m][n];
    double  alpha;
    int     i;
    int     k;
    */

    eye_square(m, I);
    eye_square(m, Q);
    printmat_square("I", n, I);

    memcpy(R, A, m * n * sizeof(double));

    printmat("R zu beginn", m, n, R);

    /* Berechnung von R */

    /* Gehe über die Spalten */
    for (j = 0; j < n; j++) {
        qr_householder_get_yj(m, n, j, R, yj);
        qr_householder_calc_qj(m, n, j, I, yj, Qj);
        printmat("Qj", m, m, Qj);

        /* R = Qj * R */
        multiply_mat_mat(m, m, n, Qj, R, R);
        printmat("R", m, n, R);
        /* Q = Qj * Q */
        multiply_mat_mat_square(m, Qj, Q);
        printmat("Qtotal", m, m, Q);
    }

    transpose_square(m, Q);
}

void
qr_householder_b(const int m, const int n, const double A[m][n], double Q[m][n], double R[m][n], double QTb[n], double b[m], double d[n])
{
    double  s;
    double  alpha;
    int     j;
    int     i;
    int     k;

    memcpy(R, A, m * n * sizeof(double));

    printmat("R zu beginn", m, n, R);

    /* Berechnung von R */
    for (j = 0; j < n; j++) {
        s                = 0.0;
        for (i = j; i < m; i++) {
            s           += R[i][j] * R[i][j];
        }
        s                = sqrt(s);
        d[j]             = (R[j][j] > 0) ? -s : s;
        alpha            = sqrt(s * (s + fabs(R[j][j])));
        R[j][j]         -= d[j];
        for (k = j; k < m; k++) {
            R[k][j]     /= alpha;
        }
        for (i = j + 1; i < n; i++) {
            s = 0;
            for (k = j; k < m; k++) {
                s       += R[k][j] * R[k][i];
            }
            for (k = j; k < m; k++) {
                R[k][i] -= R[k][j] * s;
            }
        }
    }

    /* Berechnung von Q^T*b */
    for (j = 0; j < n; j++){
        s                = 0;
        for (k = j; k < m; k++) {
            s           += R[k][j] * b[k];
        }
        for (k = j; k < m; k++) {
            b[k]        -= R[k][j] * s;
        }
        QTb[j]           = b[j];
    }

    /* Berechnen von Q */
    for (i = 0; i < n; i++) {
        for (j = n - 1; j >= 0; j--) {
            s            = 0.0;
            for (k = j; k < m; k++) {
                s       += R[k][j] * Q[k][i];
            }
            for (k = j; k < m; k++) {
                Q[k][i] -= R[k][j] * s;
            }
        }
    }
}

double
qr_givens_sqn(double x)
{
    return 0.0;
}

double
qr_givens_sin(double ajj, double aij)
{
    return 0.0;
}

double
qr_givens_cos(double ajj, double aij)
{
    return 0.0;
}

void
qr_givens(const int m, const int n, const double A[m][n], double Q[m][n], double R[m][n])
{
    //double  Qi[m][n];
    //double  B[m][n];
    int     i;
    int     j;
    int     k;

    for (j = 0; j < n; k++) {
        for (i = 0; i < m; i++) {

        }

        for (k = 0; k < n; k++) {

        }
    }
}
