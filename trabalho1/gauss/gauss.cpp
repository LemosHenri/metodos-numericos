#include<iostream>
#include<stdlib.h>
#include<math.h>
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
    for(int i=0;i<nl;i++){
        for(int j=0;j<nc;j++) cout << m[i][j] << "\t";
        cout << "\n";
    }
    cout << "\n";
}

void imprimir_vetor(double *v, int n){
    for(int i=0;i<n;i++) cout << v[i] << "\t";
    cout << "\n";
}

double *substituicao_retroativa(double **m, int nl, int nc){
    double *s;
    s = (double*)malloc(nl*sizeof(double));

    for(int i=nl-1;i>=0;i--){
        s[i] = m[i][nc-1];
        for(int j=nl-1;j>i;j--) s[i] -= s[j]*m[i][j];
        s[i] = s[i]/m[i][i]; 
    }

    return s;
}

double *eli_gauss(double **m, int nl, int nc){
    double p;

    for(int k=0;k<nl;k++){
        for(int i=k+1;i<nl;i++){
            p = m[i][k]/m[k][k];
            for(int j=0;j<nc;j++) m[i][j] -= p*m[k][j];
        }
        imprimir_matriz(m,nl,nc);
    }
    return substituicao_retroativa(m,nl,nc);
     
}

main(int argc, char **argv){
    double **m;
    int nl, nc;
    
    //resolução pelo método exato: eliminação de gauss
    double *gauss;
    m = lerMatriz(argv[1],&nl,&nc);
    imprimir_matriz(m,nl,nc);

    gauss = eli_gauss(m,nl,nc);
    imprimir_vetor(gauss,nl);
    
}

