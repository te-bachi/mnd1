//
//  main.c
//  MNDProject1
//
//  Created by Simon Iwan Stingelin on 01/10/15.
//  Copyright (c) 2015 ZHAW. All rights reserved.
//

#include <stdio.h>
#include <math.h>

// Dimension der Matrix (statische Matrix, dh. fixe Groesse
// zur Compile-Zeit. Koennte durch dynamische Speicherreservation
// verbessert werden.
#define N 5

// PIVOT 1: mit Spaltenpivotisierung
// PIVOT 0: ohne Spaltenpivotisierung
#define PIVOT 1

// SCALE 1: mit Skalierung des Systems
// SCALE 0: ohne Skalierung des Systems
#define SCALE 1

// Print [A b]
void printsystem(double A[N][N], double *b,int i)
{
    printf("(A b)[%d] = \n",i);
    for(int i=0; i<N;i++){
        for(int k=0; k<N; k++)
            printf("%8.6f\t",A[i][k]);
        printf("\t%8.6f\n",b[i]);
    }
    printf("\n");
}

// Print vector x^T
void printvec(double *xi)
{
    for(int i=0; i<N; i++){
        printf("%8.6f\t",xi[i]);
    }
    printf("\n");
}

// Skalieren des Systems in *d werden die Faktoren gespeichert
void scaleSystem(double A[N][N], double *b, double *d)
{
    for (int i=0; i<N; i++) {
        double di = 0;
        
        << snipp, selber machen >>
        
        d[i] = di;
    }
}

// LR Zerlegung
// Achtung: Die Matrix A wird ueberschrieben mit LR
void ludecompose(double A[N][N], int *rj,int pivot)
{
    // Gauss-Elimination
    for(int j=0;j<N-1;j++){
        if(pivot){
            // Find Pivot Element
            
            << snipp, selber machen >>
            
            // Speichern der Permutationsmatrix
            
            << snipp, selber machen >>
            
            // Zeilen Vertauschen
            
            << snipp, selber machen >>
            
        }else{
            // bei Division durch 0 beenden wir das Programm.
            if(A[j][j]==0){
                printf("ajj==0\n");
                exit(-1);
                break;
            }
        }
        // Gauss-Elimination
        for(int i=j+1;i<N;i++){
            // Faktor fuer Zeile i berechnen
            
            << snipp, selber machen >>
            
            // Zeilen subtrahieren
            
            << snipp, selber machen >>
            
            // Speichern von L
            
            << snipp, selber machen >>
        }
    }
}

// Rueckwaertseinsetzen R x = b
void solveR(double A[N][N], double *x, double *b)
{
    << snipp, selber machen >>
}


// Vorwaertseinsetzen L x = P b
void solveL(double A[N][N], double *x, double *b, int *p)
{
    << snipp, selber machen >>
}

void hilbertmatrix(double A[N][N])
{
    // Hilbertmatrix
    // symmetrische Matrix => nutzen!
    << snipp, selber machen >>
}

// main
int main(int argc, const char * argv[]) {
    double A[N][N];
    
    // Hilbertmatrix als Testmatrix
    hilbertmatrix(A);
    
    // Rechteseite
    double b[N],b1[N];
    for(int i=0;i<N;i++){
        b[i] = (double)1/(N+i);
        b1[i] = b[i];
    }
    
    double x[N],y[N];   // Loesungsvektor
    double d[N];    	// Skalierung
    
    // Permutation P muss in meiner
    // Implementierung initial p=[0,1,...,N-1] sein
    int rj[N];
    for(int i=0;i<N;i++) rj[i]=i;
    
    printsystem(A,b,0);
    
    // Kondition von A ohne Skalierung
    printf("cond=%e\n", estimatecond(A));
    
    // Skalieren des Systems
    if(SCALE){
        scaleSystem(A,b,d);
        printsystem(A,b,0);

        // Kondition von A mit Skalierung
        printf("cond=%e\n", estimatecond(A));
    }
    
    // LR Zerlegung
    ludecompose(A, rj, PIVOT);
    printsystem(A,b,0);
    
    // A x = b loesen
    solveL(A,y,b,rj);
    solveR(A,x,y);
    
    for(int j=0;j<N;j++)
        printf("%f\t%f\n",y[j],x[j]);
    printf("\n");
    
    return 0;
}