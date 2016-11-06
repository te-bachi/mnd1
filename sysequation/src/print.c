#include "print.h"

#define FORMAT  "%12.8f"

/**
 * Gibt einen Vektor x aus.
 *
 * @param[in]       var     Variable als erster Teil, der ausgegeben wird
 * @param[in]       n       Dimension
 * @param[in]       x       Vektor als zweiter Teil, der ausgegeben wird
 */
void
printvec(const char *var, const int n, double x[n])
{
    int j;
    
    printf("%s = [\n", var);
    for(j = 0; j < n; j++) {
        printf("\t" FORMAT ";\n",x[j]);
    }
    printf("];\n");
}

/**
 * Gibt r Vektor x aus.
 *
 * @param[in]       var     Variable als erster Teil, der ausgegeben wird
 * @param[in]       n       Dimension
 * @param[in]       r       Anzahl Vektoren
 * @param[in]       x       Vektor als zweiter Teil, der ausgegeben wird
 */
void
printvec_multi(const char *var, const int n, const int r, double x[r][n])
{
    int j;
    int k;
    
    printf("%s = [\n", var);
    for(j = 0; j < n; j++) {
        for (k = 0; k < r; k++) {
            printf("\t" FORMAT,x[k][j]);
        }
        printf(";\n");
    }
    printf("];\n");
}

/**
 * Gibt eine Matrix A aus.
 *
 * @param[in]       var     Variable als erster Teil, der ausgegeben wird
 * @param[in]       n       Dimension
 * @param[in]       A       Matrix als zweiter Teil, der ausgegeben wird
 */
void
printmat(const char *var, const int n, double A[n][n])
{
    int i;
    int j;
    
    printf("%s = [\n", var);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf(FORMAT "\t", A[i][j]);
        }
        printf(";\n");
    }
    printf("];\n");
}

/**
 * Gibt eine Matrix A|b aus.
 *
 * @param[in]       n       Dimension
 * @param[in]       A       Matrix
 * @param[in]       b       Vektor
 */
void
printmat_ab(const int n, double A[n][n], double b[n])
{
    int i;
    int j;
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf(FORMAT "\t", A[i][j]);
        }
        printf("\t" FORMAT "\n", b[i]);
    }
    printf("\n");
}
