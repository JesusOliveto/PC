#include <iostream>
#include <sstream>

using namespace std;


class Array{
    private:
        int** dato;
        int N; 
        int M;
    public:
        Array(int, int);
        ~Array();
        void insertar(int,int,int);
        void mostrar(int,int);
        void imprimir();
        int sumar();
        int peso();
};

Array::Array(int filas, int columnas){
    N=filas;
    M=columnas;
    dato = new int* [filas];
    for(int i=0; i<filas; i++) 
        dato[i] = new int[columnas];
}

Array::~Array(){
    
      for(int i = 0; i < N; i++)
            delete[] dato[i];
    delete[] dato;
}

void Array::insertar(int a, int b,int input){
    dato[a][b]=input;

}

void Array::mostrar(int a, int b){
    cout<<"["<<dato[a][b]<<"]   ";
}

void Array::imprimir(){
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            mostrar(i,j);

        }
        cout<<endl;
    }
}

int Array::sumar(){
    int r=0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            r=r+dato[i][j];

        }
    }
    return r;
}

int Array::peso(){
    int r=0;
    r=M*N*(sizeof(int))+N*8;
    return r;
}




int main(){
    int N,M;
    cout<<"ingrese filas y columnas:"<<endl;
    cin>>N;cin>>M;
    Array a1(N,M);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            //a1.insertar(i,j,1);
            a1.insertar(i,j,i+j); //cout<<"insertado "<<i+j<<" en "<<i<<","<<j<<endl;
        }
        
    }
    cout<<"array: "<<endl;
    a1.imprimir();
    
    cout<<"suma: "<<a1.sumar()<<endl;
    cout<<"peso total: "<<a1.peso()<<" bytes "<<endl;


    return 0;
}