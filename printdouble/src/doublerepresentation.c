//
//  doublerepresentation.c
//  numberrepresentation
//
//  Created by Simon Iwan Stingelin on 27/07/15.
//  Copyright (c) 2015 ZHAW. All rights reserved.
//

#include <stdio.h>
#include <math.h>

// Achtung Loesung haengt vom Betriebssystem ab:
// Windows unsigned long lond => 8bit
// Linux, MacOS unsigned long => 8bit

void printbin(unsigned long long x, int n)
{
    if (--n) printbin(x>>1,n);
    if ((n==1)||(n==12)) putchar(' ');
    putchar("01"[x & 1]);
}

int main(int argc, const char * argv[]) {
    double x=0.1; //123.75; //(1.+(double)1/3);
	
    //unsigned long lu;
    unsigned long long lu;
    
    
    lu = *(unsigned long long *)&x;
    
    printf("sizeof unsigned long: %lu Bytes\n",sizeof(lu));
    printf("sizeof double: %lu Bytes\n",sizeof(x));
    
    printf("number: %f\n",x);
    printf("number big: %50.49f\n",x);
    printf("number bin: ");
    
    printbin(lu,8*sizeof(double));
    
    printf("\n\n/*********/\n\n");
    x = pow(10.0, 308);
    lu = *(unsigned long long *)&x;
    printf("number: %f\n",x);
    printf("number big: %50.49f\n",x);
    printf("number bin: ");
    printbin(lu,8*sizeof(double));
    
    
    printf("\n\n");
    
    return 0;
}