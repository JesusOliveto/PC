#include<iostream>
#include <sstream>

using namespace std;

struct nodo{
       char dato;
       nodo* siguiente;
};

class Pila{
      private:
              nodo* inicio;
      public:
             Pila();
             void Push(char);
             char Pop();
             bool vacia();
             ~Pila();
             char ultimo();
} ; 
      
Pila::Pila(){
     inicio=NULL;
}



void Pila::Push(char p_dato){
     nodo*nuevoNodo = new nodo;
     nuevoNodo->dato = p_dato;
     nuevoNodo->siguiente = inicio;
     inicio = nuevoNodo;
}

char Pila::Pop(){
     nodo* aux = inicio;
     char p = inicio->dato;
     inicio= inicio->siguiente;
     delete aux;
     return p;
}

bool Pila::vacia(){
     return !inicio;
}

char Pila::ultimo(){
     nodo*nodoActual = inicio;
    if(vacia()!=true)return nodoActual->dato;
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



void encapsulamiento(char input[4]){
    Pila p;
    for (int i = 0; i < 4; i++)
    {
        if (input[i]=='[' || input[i]=='(')p.Push(input[i]);
        else if (input[i]==']' && p.ultimo()=='[')p.Pop();
        else if (input[i]==')' && p.ultimo()=='(')p.Pop();
    }
    if (p.vacia()==true) cout<<input<<" ESTÁ BIEN ENCAPSULADA"<<endl;
    else cout<<input<<" ESTÁ MAL ENCAPSULADA"<<endl;
   
    
    
    
}

  
int main()
{

     char input[4];
     cout<<"ingrese la palabra a analizar: ";
     cin>>input;
     encapsulamiento(input);
    
}