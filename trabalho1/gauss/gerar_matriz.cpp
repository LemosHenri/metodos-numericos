#include<iostream>
#include<stdio.h>
using namespace std;

double matriz_a(int i, int j){
    return 1.0/(i+j-1);
} 

double vetor_b(int i){
    return (double)1/(i+3) - (double)1/(i+2) - (double)1/(i+1) + (double)1/i;
}

void imprimir_matriz(double **m, int nl, int nc){
    cout << nl << "\t" << nc << endl;
    for(int i=0;i<nl;i++){
        for(int j=0;j<nc;j++) cout << m[i][j] << "\t";
        cout << "\n";
    }
    cout << "\n";
}

void calcmatriz(int n){
    double **a;
    FILE *arq = fopen("matriz.dat","a");
    

    a = (double **)malloc(n*sizeof(double*));
    
    for(int i=0; i<n; i++){
        a[i] = (double *)malloc((n+1)*sizeof(double));
        for(int j=0; j<n; j++) a[i][j] = matriz_a(i+1,j+1);
    }

    for(int i=0;i<n;i++) a[i][n] = vetor_b(i+1);
    imprimir_matriz(a,n,n+1);

    //liberação da memória alocada pela matriz a
    for(int i=0;i<n;i++) free(a[i]);
    free(a);
}

main(int argc,char **argv){
    double n = stod(argv[1]);
    calcmatriz(n);
}