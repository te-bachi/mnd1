

//
//  main.c
//  Rueckwaertseinsetzen
//
//  Created by Simon Iwan Stingelin on 12/08/15.
//  Copyright (c) 2015 ZHAW. All rights reserved.
//

#include <stdio.h>

/*
void
backward(int dim, )
{

    
};
*/

#ifdef __BACKWARD_MAIN__
int main(int argc, const char * argv[]) {
    int n = 3;  /* dimension */
    int j;
    int i;
    double A[3][3] = {
        {  3, -1,  2 },
        {  0,  1,  3 },
        {  0,  0,  2 }
    };
    double b[3] = { 0, 1, 4 };
    double x[3];
    double sum;
    
    /* set last variable */
    /* dimension n=3, array index 0..2 */
    x[n - 1] = b[n - 1] / A[n - 1][n - 1];
        
    for (j = n - 2; j >= 0; j--) {
        sum = 0;
        for (i = j + 1; i < n; i++) {
            sum += A[j][i] * x[i];
        }
        
        x[j] = (b[j] - sum) / A[j][j];
    }
    
    /* print x[j] */
    for(j = 0; j < n; j++) {
        printf("%f\n",x[j]);
    }
    
    return 0;
}
#endif
