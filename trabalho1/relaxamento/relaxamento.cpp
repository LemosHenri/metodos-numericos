#include<iostream>
#include<stdlib.h>
#include<string.h>
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
    double max;

    //valor inicial a ser comparado com as demais diferenças
    max = abs(v1[0] - v2[0]);
    //Comparação e atualização do valor max
    for(int i=1;i<n;i++)
        max = (max >= abs(v1[i] - v2[i])) ? max : abs(v1[i] - v2[i]);

    return max;
}

double relaxamento(double **m, double *v, int nl, int nc, double w){
    double *x, *aux,dx;

    //alocação de memória para o vetor no próximo passo v^(k+1)
    x = (double*)malloc(nl*sizeof(double));

    //alocação de um vetor auxiliar para guardar os elementos de v^k
    aux = (double*)malloc(nl*sizeof(double));
    for(int i=0;i<nl;i++) aux[i] = v[i];

    //calculo do método de gauss para o sistema Ax = b
    for(int i=0;i<nl;i++){
        x[i] = m[i][nc-1];
        for(int j=0;j<nl;j++){
            if(i != j) x[i] -= m[i][j]*v[j];
        } 
        x[i] = x[i]/m[i][i];
        v[i] = (1-w)*v[i] + w*x[i];
    }

    //calculo da norma entre o vetor v^(k+1) e v^(k)
    dx = norma(v,aux,nl);
    return dx;
}

int main(int argc, char **argv) {
    double **m, dx;
    int nl, nc;

    m = lerMatriz(argv[1], &nl, &nc);
    double v[4] = {0,0,0,0};

    int i=0;
    do{
        cout << i << "\t";
        imprimir_vetor(v,nl);
        dx = relaxamento(m,v,nl,nc,1.8);
        i++;
    }while (dx > 1e-4);

    cout << "\n\n------------------Método Relaxamento---------------" << endl;
    cout << i << "\t";
    imprimir_vetor(v,nl);

  return 0;
}