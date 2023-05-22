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

double norma(double *v1, double *v2, int n){
    double x;

    x = abs(v1[0] - v2[0]);
    for(int i=1;i<n;i++) x = (x >= abs(v1[i] - v2[i])) ? x : abs(v1[i] - v2[i]);

    return x;
    
}

double norma_lina(double **m, int nl, int nc){
    double *x, norma;

    x = (double*)calloc(nl,sizeof(double));
    for(int i=0;i<nl;i++){
        for(int j=0;j<nc;j++) x[i] += m[i][j];
    }

    norma = abs(x[0]);
    for(int i=1;i<nl;i++) norma = (norma >= abs(x[i])) ? norma : abs(x[i]);

    return norma;

}

double norma_sassenfeld(double **m, int nl, int nc){
    double *x, norma, soma;

    x = (double*)malloc(nl*sizeof(double));
    for(int i=0;i<nl;i++) x[i] = 1;

    for(int i=0;i<nl;i++){
        soma = 0;
        for(int j=0;j<nl;j++)
            if(i != j) soma += m[i][j]*x[j];
        x[i] = soma/m[i][i];
    }

    norma = abs(x[0]);
    for(int i=1;i<nl;i++) norma = (norma >= abs(x[i])) ? norma : abs(x[i]);

    return norma;

}

double seidel(double **m, double *v, int nl, int nc){
    double *x, *aux, dx;

    //alocação de memória para o vetor no próximo passo v^(k+1)
    x = (double *)malloc(nl*sizeof(double));
    
    //alocação de um vetor auxiliar para guardar os elementos de v^k
    aux = (double *)malloc(nl*sizeof(double));
    for(int i=0;i<nl;i++) aux[i] = v[i];

    //calculo do método de gauss para o sistema Ax = b
    for(int i=0;i<nl;i++){
        x[i] = m[i][nc-1];
        for(int j=0;j<nl;j++){
            if(i != j) x[i] -= m[i][j]*v[j];
        } 
        x[i] = x[i]/m[i][i];
        v[i] = x[i];
    }

    //calculo da norma entre o vetor v^(k+1) e v^(k)
    dx = norma(v,aux,nl);
    return dx;
}


main(int argc, char **argv){
    double **m;
    int nl, nc;

    //resolução pelo método iterativo: método de Gauss-Seidel
    
    m = lerMatriz(argv[1],&nl,&nc);
    cout << "Verificação de convergência:\n||M||l = " << norma_lina(m,nl,nc) << "\n||M||s = " << norma_sassenfeld(m,nl,nc) << endl;
    if(norma_lina(m,nl,nc) >= 1 || norma_sassenfeld(m,nl,nc) >=1){
        cout << "Convergência não garantida\n\n" << endl;
    }
    
    int i=0;
    double dx, j[nl] = {0,0,0,0};
    do{
        cout << i << "\t";
        imprimir_vetor(j,nl);
        dx = seidel(m,j,nl,nc);
        i++;
    }while(dx > 1e-4);

    cout << "\n\n------------------Método Seidel---------------" << endl;
    cout << i << "\t";
    imprimir_vetor(j,nl);
    
}

