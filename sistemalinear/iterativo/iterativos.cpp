#include<iostream>
#include<stdlib.h>
#define MAX 10
using namespace std;

double **lermatriz(char *v,int *nl, int *nc){
    FILE *arq;
    double **m;
    int a,b,i,j;

    arq = fopen("matriz.dat","r");
    fscanf(arq,"%d %d",&a,&b);
    *nl = a;
    *nc = b;

    *m = new double[*nl];
    for(i=0;i<*nc;i++) m[i] = new double[*nc];

    for(i=0;i<*nl;i++){
        for(j=0;j<*nc;j++) fscanf(arq,"%lf",&m[i][j]);
    }

    fclose(arq);
    return m;
}

void imprimir(double **m, int nl, int nc){
    int i,j;

    for(i=0;i<nl;i++){
        for(j=0;j<nc;j++) cout << m[i][j] << "\t";
        puts("");
    }

}

void jacobi(double **m,  double *v, int nl, int nc){
    int i,j;
    double *b;

    b = new double[nl];

    for(i=0;i<nl;i++){
        b[i] = m[i][nc-1]/m[i][i];
        for(j=0;j<nl;j++){
            if(i!=j) b[i] -= (m[i][j]*v[j])/m[i][i]; 
        }
    }

    for(i=0;i<nl;i++) v[i] = b[i];

    delete(b);
}

/*
void gauss_seidel(double **m,double *v, int nl, int nc){
    int i,j;
    double *b;

    b = new double[nl];

    for(i=0;i<nl;i++) b[i] = m[i][nc-1];

    for(i=0;i<nl;i++){
        for(j=0;j<nl;j++){
            if(i!=j) b[i] -= (m[i][j]*v[j]); 
        }
        v[i] = b[i]/m[i][i];
    }

    for(i=0;i<nl;i++) printf("%g\t",v[i]);
    puts("");

    delete(b);
}
*/

main(int argc,char **argv){
    double **m, j[3] = {2,3,5}, s[3] = {1,1,-1};
    int nl, nc, i;

    m = lermatriz(argv[1],&nl,&nc);

    cout << "---------------------------Jacobi-------------------------\n";
    for(int i=0;i<MAX;i++){
        cout << i << "\t";
        for(int k=0;k<nl;k++) cout << j[k] << "\t";
        jacobi(m,j,nl,nc);
        puts("");
    }
    
    
    //printf("\n\n---------------------------Gauss-Seidel-------------------------\n");
    //for(i=0;i<MAX;i++) gauss_seidel(m,s,nl,nc);

}