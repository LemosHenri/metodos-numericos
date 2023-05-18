// Exemplo Livro: B.P. Demidovich - Pag 310

#include<iostream>
#include<stdio.h>
using namespace std;

double **lerMatriz(char *v, int *nl, int *nc){
    FILE *arq = fopen(v,"r");
    double **m;

    fscanf(arq,"%d %d",nl,nc);
    m = (double **)malloc(*nl*sizeof(double*));
    for(int i=0;i<*nl;i++) m[i] = (double*)malloc(*nc*sizeof(double));

    for(int i=0;i<*nl;i++){
        for(int j=0;j<*nc;j++) fscanf(arq, "%lf", &m[i][j]);
    }

    fclose(arq);
    return m;
}

void imprimi_matriz(double **m, int nl, int nc){
    for(int i=0;i<nl;i++){
        for(int j=0;j<nc;j++) cout << m[i][j] << "\t";
        cout << "\n";
    }
    cout << "\n";
}

void imprimi_vetor(double *v, int n){
    for(int i=0;i<n;i++) cout << v[i] << "\t";
    cout << "\n";
}

double norma_max(double *v1, double *v2, int n){
    double x,y;

    x = abs(v1[0] - v2[0]);
    y = abs(v1[0]);
    for(int i=1;i<n;i++) x = (x >= abs(v1[i] - v2[i])) ? x : abs(v1[i] - v2[i]);
    for(int i=1;i<n;i++) y = (y >= abs(v1[i])) ? x : abs(v1[i]);

    return x/y;
}

double seidel(double **m, double *v, int nl, int nc){
    double *x, *aux, dx;
    x = (double *)malloc(nl*sizeof(double));
    
    aux = (double *)malloc(nl*sizeof(double));
    for(int i=0;i<nl;i++) aux[i] = v[i];

    for(int i=0;i<nl;i++){
        x[i] = m[i][nc-1];
        for(int j=0;j<nl;j++){
            if(i != j) x[i] -= m[i][j]*v[j];
        } 
        x[i] = x[i]/m[i][i];
        v[i] = x[i];
    }

    dx = norma_max(v,aux,nl);
    return dx;
}


main(int argc, char **argv){
    double **m, dx;
    int nl,nc;

    m = lerMatriz(argv[1],&nl,&nc);
    //imprimi_matriz(m,nl,nc);

    double v[nl] = {1.2,0,0};
    int i=0;
    do{
        cout << i << "\t";
        imprimi_vetor(v,nl);
        dx = seidel(m,v,nl,nc);
        i++;
    }while(dx > 1e-4);

    cout << "-------- solução ----------" << endl;
    for(int i=0;i<nl;i++) cout << v[i] << "\t";
    cout << "\n";
}