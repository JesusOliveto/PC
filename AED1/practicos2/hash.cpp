#include <iostream>
#include <sstream>

using namespace std;

// Implementación de la tabla hash con
// direccionamiento abierto - exploración lineal
  

// Tamaño de la tabla de dispersión
const int N = 128;

class Dato{
    private:
        int clave;
        int valor;
    public: 
        Dato(int,int);    
        int getClave();
        int getValor();
};

Dato::Dato( int clave, int valor){
    this->clave = clave;
    this->valor = valor;
}   

int Dato::getClave(){
    return clave;
}

int Dato::getValor(){
    return valor;
}

class TablaHash{
    private:
        Dato** tabla;
        int funcionHash(int);
    public:
        TablaHash();
        ~TablaHash();
        int buscar(int);
        void insertar(int, int);
};

TablaHash::TablaHash(){
    tabla = new Dato* [N];
    for(int i=0; i<N; i++) 
        tabla[i] = NULL;
}

TablaHash::~TablaHash(){
    for(int i = 0; i < N; i++){
        if (tabla[i] != NULL){
            delete tabla[i];
        }
    }

    delete[] tabla;
}


int TablaHash::funcionHash(int clave){
    return clave % N;
}

void TablaHash::insertar(int clave, int valor){
    int indice = funcionHash(clave);

    // Mientras no este vacío y la clave sea distinta a la que queremos insertar    
    while (tabla[indice] != NULL && tabla[indice]->getClave() != clave ){
        indice = funcionHash(indice + 1);        
    }    

    // Si encontró el elemento con la misma clave: 
    // actualización del valor de una clave
    if (tabla[indice] != NULL){ 
        delete tabla[indice];
    }

    tabla[indice] = new Dato(clave, valor);    
}

int TablaHash::buscar(int clave){
    int indice = funcionHash(clave);

    while (tabla[indice] != NULL && tabla[indice]->getClave() != clave ){
        indice = funcionHash(indice + 1);        
    }    

    if (tabla[indice] == NULL) 
        return -1;
    else
        return tabla[indice]->getValor();
}

int main(){
    TablaHash h1;
    h1.insertar(3200004, 10);
    h1.insertar(3200132, 11);
    h1.insertar(3232336, 12);
    h1.insertar(3232592, 13);

    cout << h1.buscar(3200004) << endl;
    cout << h1.buscar(3200132) << endl;
    cout << h1.buscar(3232336) << endl;
    cout << h1.buscar(3232592) << endl;

    return 0;
}