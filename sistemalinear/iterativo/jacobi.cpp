#include<iostream>
#include<stdlib.h>
#include<math.h>
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

double norma(double *v,double *v2, int nl){
    int i;
    double cont=0;

    for(i=0;i<nl;i++) cont += pow(v2[i]-v[i],2);
    return sqrt(cont); 
}

double *jacobi(double **m,  double *v, int nl, int nc){
    int i,j;
    double *b,*c;

    b = new double[nl];
    c = new double[nl];
    for(i=0;i<nl;i++) b[i] = m[i][nc-1];

    for(i=0;i<nl;i++){
        for(j=0;j<nl;j++){
            if(i!=j) b[i] -= (m[i][j]*v[j]);
        }
    }

    for(i=0;i<nl;i++) c[i] = v[i];
    for(i=0;i<nl;i++) v[i] *= b[i]/m[i][i];

    for(i=0;i<nl;i++) printf("%g\t",b[i]);
    puts("");

    return c;
}

main(int argc,char **argv){
    double **m, v[3] = {1,1,-1}, tol = 1e-3, *v2;
    int nl, nc, i=0;

    m = lermatriz(argv[1],&nl,&nc);

    do{
        v2 = jacobi(m,v,nl,nc);
        i++;
    }while(norma(v,v2,nl) > tol);

}