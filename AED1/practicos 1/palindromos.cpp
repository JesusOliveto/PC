#include<iostream>

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
             void mostrar();
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

void Pila::mostrar(){
     nodo*nodoActual = inicio;
     while(nodoActual!=NULL)
     {
          cout<<" ["<<nodoActual->dato<<"]"<<endl; 
          cout<<"  | "<<endl;
          nodoActual = nodoActual->siguiente;        
     }
     cout<<" NULL"<<endl<<endl;
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

bool testP(string input)
{
     bool p=true;
     Pila p1;
     
     for(int i=0;i<input.length();i++) p1.Push(input[i]);                   
     for(int i=0;i<input.length();i++) if(p1.Pop()!=input[i]) p=false;     

     return p;
}

void palindromo(string input){
      if(testP(input))   cout<<"La palabra "<< input <<" es palíndroma"<<endl;            
     else cout<<"La palabra "<< input <<" no es palíndroma"<<endl;
}


int main()
{
//   string A="menem"; 
//   string B="wasd";
//   palindromo(A);
//   palindromo(B);
     string input;
     cout<<"ingrese la palabra a analizar: ";
     cin>>input;
     palindromo(input);
     cout<<"ingrese la palabra a analizar: ";
     cin>>input;
     palindromo(input);
}