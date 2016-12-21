
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include "print.h"

#define M 16
#define N 4


double  f(double x, double param[N]);
void    df(double x, double param[N], double dfi[N]);
void    F(double param[N], double data[M][2], double vecF[M]);
void    dF(double param[N], double data[M][2], double jacF[M][N]);
double  scalarproduct(double *vecA, double *vecB, int n);
double  norm(double *vecA, int n);
void    qrdecompose(double a[M+N][N], double b[M+N], double d[N], double QTb[N]);
void    backward(double jacFLM[M+N][N], double d[N],double QTb[N], double x[N]);
void    calcSystem(double a[M+N][N], double b[M+N], double jacF[M][N], double vecF[M], double mu);
double  calcMaxNormGradPhi(double jacF[M][N], double vecF[M]);

// Modell Funktion
// f: R x R^N -> R
double
f(double x, double param[N])
{
    double  x0      = param[0];
    double  sigma   = param[1];
    double  a       = param[2];
    double  b       = param[3];
    double  s       = (x - x0);
    double  s2      = s*s;
    double  s3      = s*s*s;
    double  exps2   = exp(-s2/sigma);

    return exps2 * (a * s3 + b * s);
}

// Modell Funktion
// grad_x f: R x R^N -> R^N
// der Gradient wird im Vektor dfi gespeichert
void
df(double x, double param[N], double dfi[N])
{
    double  x0      = param[0];
    double  sigma   = param[1];
    double  a       = param[2];
    double  b       = param[3];
    double  s       = (x - x0);
    double  s2      = s*s;
    double  s3      = s*s*s;
    double  exps2   = exp(-s2/sigma);

    dfi[0] = (exps2 * (2*x - 2*x0) * (b*s + a*s3)) / sigma - exps2 * (b + 3*a*s2);
    dfi[1] = (exps2 * (b*s + a*s3) * s2) / (sigma*sigma);
    dfi[2] = exps2 * s3;
    dfi[3] = exps2 * s;
}

// Differenz Modell - Messung
// F: R^N -> R^M
// die Differenz wird im Vektor vecF gespeichert
void
F(double param[N], double data[M][2], double vecF[M])
{
    int     i;
    for (i = 0; i < M; i++) {
        //printf("data[%02d][0] = %6.2f, data[%02d][1] = %6.2f\n", i, data[i][0], i, data[i][1]);
        vecF[i] = f(data[i][0], param) - data[i][1];
    }
}

// Jacobimatrix der Differenz Modell - Messung
// F': R^N -> R^(M x N)
// die Differenz wird im Vektor vecF gespeichert
void
dF(double param[N], double data[M][2], double jacF[M][N])
{
    int     i;
    int     j;
    double  x[N];

    for (i = 0; i < M; i++) {
        // Gradient von f für gegebenes xi = data[i][0]
        df(data[i][0], param, x);
        for (j = 0; j < N; j++) {
            jacF[i][j] = x[j];
        }
    }
}

// Skalarprodukt
double
scalarproduct(double *vecA, double *vecB, int n)
{
    int     i;
    double  sum=0.0;

    for (i = 0; i < n; i++) {
        sum += vecA[i] * vecB[i];
    }

    return sum;
}

// Euklidische Norm
double
norm(double *vecA, int n)
{
    return sqrt(scalarproduct(vecA,vecA,n));
}

// QR-Zerlegung
// R ist (ohne Diagonale) in a gespeichert, Diagonale von R in d
// Das Produkt Q^T b wird direkt ausgerechnet und in QTb gespeichert.
void
qrdecompose(double a[M+N][N], double b[M+N], double d[N], double QTb[N])
{
    // Berechnung von R
    for(int j=0; j<N; j++){
        double s = 0.0;
        for(int i=j; i<M+N; i++) s+= a[i][j]*a[i][j];
        s = sqrt(s);
        d[j] = (a[j][j]>0) ? -s : s;
        double alpha = sqrt(s*(s+fabs(a[j][j])));
        a[j][j] -= d[j];
        for(int k=j; k<M+N; k++) a[k][j] /= alpha;
        for(int i=j+1; i<N;i++){
            s=0;
            for(int k=j; k<M+N; k++) s += a[k][j]*a[k][i];
            for(int k=j; k<M+N; k++) a[k][i] -= a[k][j]*s;
        }
    }

    // Berechnung von Q^T b
    for(int j=0;j<N;j++){
        double s=0;
        for(int k=j;k<M+N;k++) s += a[k][j]*b[k];
        for(int k=j;k<M+N;k++) b[k] -= a[k][j]*s;
        QTb[j] = b[j];
    }
}

// Rueckwaerts Einsetzen
// angepasst fuer R (ohne Diagnonale) in a und Diagonale in d gespeichert.
void
backward(double jacFLM[M+N][N], double d[N],double QTb[N], double x[N])
{
    int     i;
    int     j;
    double  sum=0.0;

    for (i = (N - 1); i >= 0; i--) {
        sum = 0.0;
        for (j = (i + 1); j < N; j++) {
            sum += jacFLM[i][j] * x[j];
        }
        x[i] = (QTb[i] - sum) / d[i];
    }
}

// Zusammensetzen der Normalengleichung mit
//F'(x) + lambda Id und b = -F(x).
void
calcSystem(double a[M+N][N], double b[M+N], double jacF[M][N], double vecF[M], double mu)
{
    int i;
    int j;

    for (i = 0; i < (M + N); i++) {
        for (j = 0; j < N; j++) {
            if (i < M) {
                a[i][j] = jacF[i][j];
            } else {
                if( j == (i - M)) {
                    a[i][j] = mu;
                } else {
                    a[i][j] = 0.0;
                };
            }
        }
        if (i < M) {
            b[i] = -vecF[i];
        } else {
            b[i] = 0.0;
        }
    }
}

// Methode berechnet |grad Phi(x)|_infty fuer Stopkriterium
// wobei grad Phi = jacF(x)^T * F(x)
double
calcMaxNormGradPhi(double jacF[M][N], double vecF[M])
{
    double  max = 0.0;
    double  sum = 0.0;
    int     i;
    int     j;

    // grad Phi = jacF(x)^T * F(x)
    for (i = 0; i < N; i++) {
        sum = 0.0;

        for (j = 0; j < M; j++) {
            sum += jacF[j][i] * vecF[j];
        }
        if (i == 0) {
            max = fabs(sum);
        } else if (max < fabs(sum)) {
            max = fabs(sum);
        }
    }
    return max;
}

int
main(int argc, const char * argv[])
{
    int     i;
    int     j;

    printf("MND Projekt 2: Nichtlineare Ausgleichrechnung\n");

    // Messdaten
    double  xsensor[] = {-11., -9., -7., -5., -3., -1., 1., 3. ,5., 7., 9., 11., 13., 15., 17., 19.};
    double  deltai[] = {-0.49, -1.86, -4.93, -9.02, -10.91, -8.25, -3.47, 0.29,4.25, 8.98, 10.90, 8.36, 4.28, 1.51, 0.38, 0.07};

    // etwas Kosmetik fuer die Ausgabe
    char    labels[4][20]={"x0","sigma","a","b"};

    // speichere die Messung als Matix
    double  data[M][2];
    for (i = 0; i < M; i++) {
        data[i][0] = xsensor[i];
        data[i][1] = deltai[i];
    }

    double  jacF[M][N];
    double  vecF[M];

//    double jacFLM[M+N][N];
    double  a[M+N][N];   // Matrix für die QR Zerlegung (wird überschrieben)
    double  b[M+N];

    double  d[N];
    double  QTb[N];
    double  sk[N];
    double  xn[M];

    // Paramtervektor mit Startwerten
    double  x[] = {3,1,1,1};

    bool    ok      = true;
    double  tol     = 1e-12;    // Toleranz fuer Levenberg-Marquardt beenden
    double  muMin   = 1e-5;     // minimales mu
    double  muMax   = 1e8;      // maximales mu
    double  beta0   = 0.2;      // untere Grenze fuer rho
    double  beta1   = 0.8;      // obere Grenze fuer rho
    double  mu      = 1.0;      // mu mit Startwert 1
    int     iter    = 0;
    int     maxIter = 50;       // maximal 50 Iterationen
    double  rho     = 0;

    // initiale Berechnung der Differenzen
    F(x, data, vecF);
    //printvec("vecF", M, vecF);

    double normF = norm(vecF,M);

    // initiale Berechnung der Jacobimatrix der Differenzen
    dF(x, data, jacF);
    //printmat("jacF", M, N, jacF);

    // Levenberg-Marquardt Verfahren
    while(ok && (iter++ < maxIter)){
        printf("Iteration : %d\n",iter);
        /*** DEBUG ***/
        do {
            // Matrix / Rechteseite fuer Normalengleichung berechnen
            calcSystem(a, b, jacF, vecF,  mu);
            //printmat("a", M+N, N, a);
            //printvec("b", M+N, b);
            //printmat("jacF", M, N, jacF);

            // QR-Zerlegung
            qrdecompose(a, b, d, QTb);

            // Loesen des Systems durch Rueckwartseinsetzen
            backward(a, d, QTb, sk);

            // neuer Parametersatz berechnen
            for(i = 0; i < N; i++) {
                xn[i] = x[i] + sk[i];
            }
            // rho fuer die Bewertung von mu berechnen (vgl. Skript)
            double vecFn[M];
            for(i = 0; i < M; i++){
                vecFn[i]=vecF[i];
                for(j= 0 ; j < N; j++){
                    vecFn[i] += jacF[i][j] * sk[j];
                }
            }
            double normFns = norm(vecFn,M);
            F(xn, data, vecFn);
            double normxn = norm(vecFn,M);

            rho = (normF-normxn)/(normF-normFns);

            printf("rho = %g\tmu = %g\n",rho,mu);

            // Falls rho > beta1, Loesung behalten und mu verkleinern
            if (rho > beta1 && mu > muMin) {
                mu = mu / 2.0;

            // Falls rho < beta0, neue Schritt mit groesserem rho wiederholen
            } else if(rho < beta0 && mu < muMax) {
                mu = mu * 2.0;
            }

        /*** DEBUG ***/
        } while (rho < beta0  && mu > muMin);

        for (int i = 0; i < N; i++){
            x[i] = xn[i];
            printf("%-5s=%10.6g\ts_%-5s=%10.6g\n",labels[i],x[i],labels[i],sk[i]);
        }

        // neuer Vektor F
        F(x, data, vecF);
        double normF =norm(vecF,M);
        // neue Jacobi Matrix von F
        dF(x, data, jacF);

        // Stopkriterium: |grad Phi(x)|_infty < tol
        double maxgradphi = calcMaxNormGradPhi(jacF, vecF);
        if(maxgradphi < tol) {
            ok = false;
        }
        /*** DEBUG ***/
        //ok = false;

        printf("normF = %g\tmaxgradphi = %g\n\n",normF,maxgradphi);
    }

    return 0;
}
