#include<iostream>
#include<stdlib.h>
using namespace std;

double **lerMatriz(char *v, int *nl, int *nc){
    FILE *arq = fopen(v,"r");
    int i,j;
    double **m;

    fscanf(arq,"%d %d",nl,nc);

    //alocação de memória com base no num de linha e coluna
    m = (double **)malloc(*nl*sizeof(double*));
    for(i=0;i<*nl;i++) m[i] = (double*)malloc(*nc*sizeof(double));

    //leitura dos elementos da matriz
    for(i=0;i<*nl;i++){
        for(j=0;j<*nc;j++) fscanf(arq,"%lg",&m[i][j]);
    }

    fclose(arq);
    return m;
}

void imprimir_matriz(double **m, int nl, int nc){
    puts("");
    for(int i=0;i<nl;i++){
        for(int j=0;j<nc;j++) cout << m[i][j] << "\t";
        puts("");
    }
}

void eli_gauss(double **m, int nl, int nc){
    double p;

    for(int k=0;k<nl-1;k++){
        for(int i=k+1;i<nl;i++){
            p = m[i][k]/m[k][k];
            for(int j=0;j<nc;j++) m[i][j] -= m[k][j]*p; 
        }
    }
    
    imprimir_matriz(m,nl,nc);
     
}

main(int argc, char **argv){
    int nl, nc;
    double **m;

    m = lerMatriz(argv[1],&nl,&nc);
    imprimir_matriz(m,nl,nc);
    eli_gauss(m, nl, nc);
    //imprimir_matriz(m,nl,nc);
    
}