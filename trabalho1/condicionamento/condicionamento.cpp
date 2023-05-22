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

double max(double *v1, int n){
    double x;

    x = abs(v1[0]);
    for(int i=1;i<n;i++) x = (x >= abs(v1[i])) ? x : abs(v1[i]);
    return x;
    
}

double m_norma(double **m, int nl, int nc){
    double *aux, norma;
    aux = (double*)calloc(nl,sizeof(double));

    for(int i=0;i<nl;i++){
        for(int j=0;j<nc;j++) aux[i] += m[i][j];
    }

    norma = max(aux,nl);
    return norma;
}

double l_norma(double **m, int nl, int nc){
    double *aux, norma;
    aux = (double*)calloc(nl,sizeof(double));

    for(int i=0;i<nl;i++){
        for(int j=0;j<nc;j++) aux[i] += m[j][i];
    }

    norma = max(aux,nl);
    return norma;
}

double k_norma(double **m, int nl, int nc){
    double cont = 0;
    
    for(int i=0;i<nl;i++){
        for(int j=0;j<nc;j++) cont += abs(m[i][j]);
    }

    return sqrt(cont);
}


main(int argc, char **argv){
    double **m, **inv;
    int nl1, nc1, nl2, nc2;

    m = lerMatriz(argv[1],&nl1,&nc1);
    inv = lerMatriz(argv[2],&nl2,&nc2);

    cout << "Normas ||A||:\nm-norma: " << m_norma(m,nl1,nc1) << "\nl-norma: " << l_norma(m,nl1,nc1) << "\nk-norma: " << k_norma(m,nl1,nc1) << endl;
    cout << "Normas ||A^1||:\nm-norma: " << m_norma(inv,nl2,nc2) << "\nl-norma: " << l_norma(inv,nl2,nc2) << "\nk-norma: " << k_norma(inv,nl2,nc2) << endl;

    cout << "\n";
    cout << "Usando m-norma: ||A|| ||A^-1|| = " << m_norma(m,nl1,nc1) * m_norma(inv,nl2,nc2) << endl; 
    cout << "Usando l-norma: ||A|| ||A^-1|| = " << l_norma(m,nl1,nc1) * l_norma(inv,nl2,nc2) << endl;
    cout << "Usando k-norma: ||A|| ||A^-1|| = " << k_norma(m,nl1,nc1) * k_norma(inv,nl2,nc2) << endl;

}