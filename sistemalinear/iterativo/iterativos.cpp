#include<iostream>
#include<stdlib.h>
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
    int i,j;
    double *b;

    b = (double *)malloc(nl*sizeof(double));

    for(i=0;i<nl;i++){
        b[i] = m[i][nc-1]/m[i][i];
        for(j=0;j<nl;j++){
            if(i!=j) b[i] -= (m[i][j]*v[j])/m[i][i]; 
        }
        v[i] = b[i];
    }

    free(b);
}


main(int argc,char **argv){
    double **m, j[3] = {2,3,5}, s[3] = {2,3,5};
    int nl, nc;

    m = lermatriz(argv[1],&nl,&nc);
    imprimir(m,nl,nc);

    
    printf("---------------------------Jacobi-------------------------\n");
    for(int i=0;i<10;i++){
        printf("%d\t",i);
        for(int k=0;k<nl;k++) printf("%g\t",j[k]);
        jacobi(m,j,nl,nc);
        puts("");
    }
    
    printf("---------------------------Gauss-Seidel-------------------------\n");
    for(int i=0;i<10;i++){
        printf("%d\t",i);
        for(int k=0;k<nl;k++) printf("%g\t",s[k]);
        gauss_seidel(m,s,nl,nc);
        puts("");
    }

}