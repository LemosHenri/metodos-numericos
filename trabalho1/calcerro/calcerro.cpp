#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std;

double integral(double *v){
    double cont = 0;
    double *poli;
    poli = (double*)malloc(7*sizeof(double));
    poli[0] = pow(v[3],2);
    poli[1] = -2.0*v[2];
    poli[2] = pow(v[2],2) -2.0*v[1]*v[3];
    poli[3] = 2*v[0]*v[3]+2.0*v[1]*v[2];
    poli[4] = pow(v[1],2)-2.0*v[0]*v[2];
    poli[5] = -2.0*v[0]*v[1];
    poli[6] = pow(v[0],2);

    for(int i=1;i<=7;i++) poli[i-1] = poli[i-1]/((double)i);
    for(int i=0;i<7;i++) cont += poli[i];
}
main(){
    double v[4] = {-0.00403,-0.04318,-0.101153,-0.064609};
    long double soma;
    soma = integral(v);

    cout << "resultado = " << sqrt(soma) << endl;

    if(2.16523e-155 < 2.16288e-155) cout << "relax < seidel" << endl;
    else cout << "relax > seidel" << endl;

}