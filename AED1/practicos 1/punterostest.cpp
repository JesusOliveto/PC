#include <iostream>
#include <sstream>

using namespace std;

void cambiar(int *a,int *b);


void cambiar(int* a,int* b){
int aux= *a;
*a=*b;
*b=aux;
}

int main(){
    int a=10;
    int b=20;
    cout<<"a: "<<a<<"\n b: "<<b<<endl;
    cambiar(&a,&b);

    cout<<"a: "<<a<<"\n b: "<<b<<endl;
    
    return 0;
}

