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

double *resultado_gauss(double **m, int nl, int nc){
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

    for(int k=0;k<nl-1;k++){
        for(int i=k+1;i<nl;i++){
            p = m[i][k]/m[k][k];
            for(int j=0;j<nc;j++) m[i][j] -= m[k][j]*p; 
        }
    }

    //imprimir_matriz(m,nl,nc);
    return resultado_gauss(m,nl,nc);
     
}

double norma_max(double *v1, double *v2, int n){
    double x;

    x = abs(v1[0] - v2[0]);
    for(int i=1;i<n;i++) x = (x >= abs(v1[i] - v2[i])) ? x : abs(v1[i] - v2[i]);

    return x;
    
}

double jacobi(double **m,  double *v, int nl, int nc){
    double *x, variacao;

    x = (double *)malloc(nl*sizeof(double));

    for(int i=0;i<nl;i++){
        x[i] = m[i][nc-1]/m[i][i];
        for(int j=0;j<nc-1;j++){
            if(i!=j) x[i] -= m[i][j]*v[j]; 
        }
        x[i] *= 1/m[i][i];
    }

    variacao = norma_max(x,v,nl);
    for(int i=0;i<nl;i++) v[i] = x[i];

    free(x);
    return variacao;
}

void gauss_seidel(double **m,double *v, int nl, int nc){
    int i,j;
    double *b, norm;

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

main(int argc, char **argv){
    double **m,*gauss;
    int nl, nc;
    
    //resolução pelo método exato: eliminação de gauss
    /*
    
    imprimir_matriz(m,nl,nc);

    gauss = eli_gauss(m,nl,nc);
    imprimir_vetor(gauss,nl);
    */

    //resolução pelo método iterativo: método de jacobi

    m = lerMatriz(argv[1],&nl,&nc);
    int i=0;
    do{
        //for(int k=0;k<n;k++) aux[k] = j[k]; cópia vetor j para o vetor auxiliar
        cout << i << "\t";
        imprimir_vetor(j,n);
        dx = jacobi(m,j,n,n);
        cout << dx << "\n";
        i++;
    }while(i < 10);

    cout << "\n\n------------------Método Jacobi---------------" << endl;
    cout << i << "\t";
    imprimir_vetor(j,n);
    
    /*
    i = 0;
    do{
        for(int k=0;k<n;k++) aux[k] = g[k]; //cópia vetor g para o vetor auxiliar
        cout << i << "\t";
        imprimir_vetor(g,n);
        gauss_seidel(m,g,n,n);
        cout << norma_max(g,aux,n) << "\n";
        i++;
    }while(norma_max(g,aux,n) >= tolerance);
    

    cout << "\n\n------------------Método Gauss-Seidel---------------" << endl;
    cout << i << "\t";
    imprimir_vetor(g,n);
    

    
    */

   
}

