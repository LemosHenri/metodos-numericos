#include<iostream>
#include<string.h>
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

double max(double *v, int n){
    double x = abs(v[0]);
    for(int i=1;i<n;i++) x = (x >= abs(v[i])) ? x : abs(v[i]);
    return x;
}

double norma_max(double *v1, double *v2, int n){
    double *x;

    x = (double*)malloc(n*sizeof(double));
    for(int i=0;i<n;i++) x[i] = v1[i] - v2[i];

    return max(x,n)/max(v1,n);   
}

void imprimir(double **m, int nl, int nc){
    int i,j;

    for(i=0;i<nl;i++){
        for(j=0;j<nc;j++) printf("%g\t",m[i][j]);
        puts("");
    }
}

void jacobi(double **m,  double *v, int nl, int nc){
    double *b;

    b = (double *)malloc(nl*sizeof(double));

    for(int i=0;i<nl;i++){
        b[i] = m[i][nc-1]/m[i][i];
        for(int j=0;j<nc-1;j++){
            if(i!=j) b[i] -= (m[i][j]*v[j])/m[i][i]; 
        }
    }

    for(int i=0;i<nl;i++) v[i] = b[i];
    free(b);
}

void gauss_seidel(double **m,double *v, int nl, int nc){
    double *b;

    b = (double *)malloc(nl*sizeof(double));

    for(int i=0;i<nl;i++){
        b[i] = m[i][nc-1]/m[i][i];
        for(int j=0;j<nl;j++){
            if(i!=j) b[i] -= (m[i][j]*v[j])/m[i][i]; 
        }
        v[i] = b[i];
    }

    free(b);
}


main(int argc,char **argv){
    double **m, j[3] = {-1.5,0.2,0}, s[3] = {-1.5,0.2,0}, aux[3], tolerance = 1e-2;
    int nl, nc, i = 0;

    m = lermatriz(argv[1],&nl,&nc);
    imprimir(m,nl,nc);

    printf("---------------------------Jacobi-------------------------\n");
    do{
        for(int k=0;k<nl;k++) aux[k] = j[k];
        printf("%d\t",i);
        for(int k=0;k<nl;k++) printf("%g\t",j[k]);
        jacobi(m,j,nl,nc);
        puts("");
        i++;
    }while(norma_max(j,aux,3) >= tolerance);
    
    printf("---------------------------Gauss-Seidel-------------------------\n");
    i = 0;
    do{
        for(int k=0;k<nl;k++) aux[k] = s[k];
        printf("%d\t",i);
        for(int k=0;k<nl;k++) printf("%g\t",s[k]);
        gauss_seidel(m,s,nl,nc);
        puts("");
        i++;
    }while(norma_max(s,aux,3) >= tolerance);

}
