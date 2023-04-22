#include<iostream>
#include<stdlib.h>
using namespace std;

double **lermatriz(char *v){
    FILE *arq;
    double **m;
    int nl,nc,i,j;
    
    arq = fopen("matriz.dat","r");
    fscanf(arq,"%d %d",&nl,&nc);

    *m = new double[nl];
    for(i=0;i<nc;i++) m[i] = new double[nc];

    for(i=0;i<nl;i++){
        for(j=0;j<nc;j++) fscanf(arq,"%lf",&m[i][j]);
    }

    fclose(arq);
    return m;
}

void imprimir(double **m){
    FILE *arq;
    int nl,nc,i,j;
    
    arq = fopen("matriz.dat","r");
    fscanf(arq,"%d %d",&nl,&nc);

    for(i=0;i<nl;i++){
        for(j=0;j<nc;j++) cout << m[i][j] << "\t";
        puts("");
    }

    fclose(arq);
}

double *jacobi(double **m, double *v){
    FILE *arq;
    int nl,nc,i,j;
    double *b;
    
    arq = fopen("matriz.dat","r");
    fscanf(arq,"%d %d",&nl,&nc);
    
    b = new double[nl];
    for(i=0;i<nl;i++) b[i] = m[i][nc-1];

    for(i=0;i<nl;i++){
        for(j=0;j<nc-1;j++){
            if(i!=j) b[i] -= (m[i][j]*v[j])/m[i][i];
        }
    }
    
    fclose(arq);
    return b;
}

main(int argc,char **argv){
    double **m, v[4] = {0,0,0,0};

    m = lermatriz(argv[1]);
    //v = jacobi(m,v);
    //por que raios esse v ta me estressando, tnc
    imprimir(m);
}