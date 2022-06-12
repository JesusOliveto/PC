#include<iostream>
using namespace std;

struct nodo{
       int dato;
       nodo* siguiente;
};

class Pila{
      private:
              nodo* inicio;
      public:
             Pila();
             ~Pila();
             void Apilar(int);
             int Desapilar();
             int leer();
             bool estaVacia();
             void mostrar();
             int ultimo();
             
};

Pila::Pila(){
     inicio=NULL;
}

void Pila::Apilar(int p_dato){
     nodo*nuevoNodo = new nodo;
     nuevoNodo->dato = p_dato;
     nuevoNodo->siguiente = inicio;
     inicio = nuevoNodo;
}

int Pila::Desapilar(){
     nodo* aux = inicio;
     inicio= inicio->siguiente;
     delete aux;
}

bool Pila::estaVacia(){
     return !inicio;
}

Pila::~Pila(){
     nodo* nodoActual=inicio;
     while(nodoActual!=NULL)
     {
          nodo* aux=nodoActual->siguiente;
          delete nodoActual;
          nodoActual=aux;                  
     }           
}

void Pila::mostrar(){
     nodo*nodoActual = inicio;
     while(nodoActual!=NULL)
     {
          cout<<" ["<<nodoActual->dato<<"]"<<"--"; 
          nodoActual = nodoActual->siguiente;        
     }
     cout<<" NULL"<<endl<<endl;
}

int Pila::ultimo(){
     nodo*nodoActual = inicio;
    if(vacia!=true)return n->dato;
}






int main()
{
 
 Pila A; 
 A.Apilar(10);  
 A.Apilar(20); 
 A.Apilar(30); 

 A.mostrar(); 
 cout<<endl;
 A.Desapilar();
 A.mostrar();
 
 if(A.estaVacia()){
    
    cout<<"vacia";               
    }
    else{
    cout<<"No esta vacia"<<endl<<endl;
    };
 
return 0;   
      
    
}