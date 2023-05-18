#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std;

double **lermatriz(char *v, int *nl, int *nc){
    FILE *arq = fopen(v, "r");
    double **m;

    fscanf(arq, "%d %d", nl, nc);

    m = (double **)malloc(*nl*sizeof(double *));
    for(int i=0;i<*nl;i++) m[i] = (double *)malloc(*nc*sizeof(double));

    for(int i=0; i<*nl;i++){
        for(int j=0;j<*nc;j++){
            fscanf(arq, "%lf", &m[i][j]);   
            //printf("%g\t",m[i][j]);
        }
        //puts("");
    }

    fclose(arq);
    return m;
}

void imprimir(double **m, int nl, int nc){
    int i,j;

    for(i=0;i<nl;i++){
        for(j=0;j<nc;j++) printf("%g\t",m[i][j]);
        puts("");
    }
}

void jacobiana(double **j, double *x, int n){
    j[0][0] = 2*x[0];
    j[0][1] = 2*x[1];
    j[0][2] = 2*x[2];
    j[1][0] = 4*x[0];
    j[1][1] = 2*x[1];
    j[1][2] = -4;
    j[2][0] = 6*x[0];
    j[2][1] = -4;
    j[2][2] = 2*x[2];
}

void f(double *f, double *x, int n){
    f[0] = pow(x[0],2) + pow(x[1],2) + pow(x[2],2) - 1;
    f[1] = 2*pow(x[0],2) + pow(x[1],2) -4*x[2];
    f[2] = 3*pow(x[0],2) - 4*x[1] + pow(x[2],2);
}

double det(double **m, int nl, int nc){
    double cont = 0;

    for(int i=0;i<nl;i++){
        for(int j=i; j<nc; j++) cont += m[j][j];
    }
}

main(int argc, char **argv){
       double **j, x[3] = {0.5,0.5,0.5}; 


}