#include<iostream>
#include<stdlib.h>
using namespace std;

double **lerMatriz(char *v){
    FILE *arq = fopen(v,"r");
    int nl, nc,i,j;
    double **m;

    fscanf(arq,"%d %d",&nl,&nc);

    //alocação de memória com base no num de linha e coluna
    *m = new double[nl];
    for(i=0;i<nl;i++) m[i] = new double[nc];

    //leitura dos elementos da matriz
    for(i=0;i<nl;i++){
        for(j=0;j<nc;j++){
            fscanf(arq,"%lg",&m[i][j]);
            printf("%lg\t",m[i][j]);
        } 
        puts("");
    }

    fclose(arq);
    return m;
}

double **eliminacao(double **m, char *v){
    FILE *arq = fopen(v,"r");
    int nl, nc,i,j,k;
    double p;
    fscanf(arq,"%d %d",&nl,&nc);

    for(k=0;k<(nc-1);k++){
        for(i=k+1;i<nl;i++){
            p = -(m[i][k]/m[k][k]);
            for(j=0;j<nc;j++) m[i][j] += m[k][j]*p;
        }
    }

    //imprimir matriz para verificação
    puts("");
    for(i=0;i<nl;i++){
        for(j=0;j<nc;j++) printf("%g\t", m[i][j]);
        puts("");
    }

    fclose(arq);
    
    return m;
}

main(int argc, char **argv){
    FILE *arq;
    double **m;

    m = lerMatriz(argv[1]);
    m = eliminacao(m,argv[1]);
    
}