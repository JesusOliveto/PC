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
        string valor;
    public: 
        Dato(int,string);    
        int getClave();
        string getValor();
};

Dato::Dato( int clave, string valor){
    this->clave = clave;
    this->valor = valor;
}   

int Dato::getClave(){
    return clave;
}

string Dato::getValor(){
    return valor;
}

class TablaHash{
    private:
        Dato** tabla;
        int funcionHash(int);
    public:
        TablaHash();
        ~TablaHash();
        string buscar(int);
        void insertar(int, string);
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

void TablaHash::insertar(int clave, string valor){
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

string TablaHash::buscar(int clave){
    int indice = funcionHash(clave);

    while (tabla[indice] != NULL && tabla[indice]->getClave() != clave ){
        indice = funcionHash(indice + 1);        
    }    

    if (tabla[indice] == NULL) 
        return "NULL";
    else
        return tabla[indice]->getValor();
}

int main(){
    TablaHash h1;
    h1.insertar(3200004, "Santos");
    h1.insertar(3200132, "Ravenna");
    h1.insertar(3232336, "Medina");
    h1.insertar(3232592, "Lamponne");

    cout << h1.buscar(3200004) << endl;
    cout << h1.buscar(3200132) << endl;
    cout << h1.buscar(3232336) << endl;
    cout << h1.buscar(3232592) << endl;

    return 0;
}