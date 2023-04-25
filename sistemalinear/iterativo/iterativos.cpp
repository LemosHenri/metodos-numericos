#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 10
using namespace std;

double **lermatriz(char *v,int *nl, int *nc){
    FILE *arq;
    double **m;
    int a,b,i,j;

    arq = fopen("matriz.dat","r");
    fscanf(arq,"%d %d",&a,&b);
    *nl = a;
    *nc = b;

    *m = new double[*nl];
    for(i=0;i<*nc;i++) m[i] = new double[*nc];

    for(i=0;i<*nl;i++){
        for(j=0;j<*nc;j++) fscanf(arq,"%lf",&m[i][j]);
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

double norma(double *x, double *y, int nl){
    int i;
    double norma, dx;

    for(i=0;i<nl;i++){
        dx = fabs(x[i]-y[i]);
        if(dx>norma) norma = dx;
    }

    return norma;
}

double *jacobi(double **m,  double *v, int nl){
    int i,j;
    double *b;

    b = new double[nl];

    for(i=0;i<nl;i++) b[i] = m[i][nl]/m[i][i];

    for(i=0;i<nl;i++){
        for(j=0;j<nl;j++){
            if(i!=j) b[i] -= (m[i][j]*v[j])/m[i][i]; 
        }
    }

    for(i=0;i<nl;i++) printf("%g\t",b[i]);
    puts("");

    return b;
}
/*

void gauss_seidel(double **m,double *v, int nl, int nc){
    int i,j;
    double *b;

    b = new double[nl];

    for(i=0;i<nl;i++) b[i] = m[i][nc-1];

    for(i=0;i<nl;i++){
        for(j=0;j<nl;j++){
            if(i!=j) b[i] -= (m[i][j]*v[j]); 
        }
        v[i] = b[i]/m[i][i];
    }

    for(i=0;i<nl;i++) printf("%g\t",v[i]);
    puts("");

    delete(b);
}
*/

main(int argc,char **argv){
    double **m, *x1,x[3] = {1,1,-1},s[3] = {1,1,-1};
    int nl, nc, i;

    m = lermatriz(argv[1],&nl,&nc);
    //imprimir(m,nl,nc);
    //printf("---------------------------Jacobi-------------------------\n");
    x1 = jacobi(m,x,nl);
    for(i=0;i<nl;i++) printf("%g\t",x1[i]);
    

    //printf("\n\n---------------------------Gauss-Seidel-------------------------\n");
    //for(i=0;i<MAX;i++) gauss_seidel(m,s,nl,nc);

}