#include <iostream>
#include <sstream>

using namespace std;

struct nodo{
    int dato;
    nodo* siguiente;
};

class Lista{
    private:
        nodo* inicio;
        void mostrarRecursivo(nodo* n);
        int longitudRecursiva(nodo* n);
    public:
        Lista();
        ~Lista();
        void agregarNodo(int);
        void remover();
        void mostrar();
        int longitud();
        void invertir();
        void insertarUltimo(int);
        nodo* buscar(int);
        void mostrarRecursivo();
        int longitudRecursiva();
        void ordenar();
        void repetidos();
        void insertarElemento(int, int);
        void eliminarElemento(int);
        bool comparar(Lista l1, Lista l2);
        void eliminarCada2();
};

// Implementación de los métodos de Lista
Lista::Lista(){
    inicio = NULL;
}

Lista::~Lista(){
    nodo *n=inicio, *siguiente=NULL;
    while (n!=NULL)
    {
       siguiente=n->siguiente;
       delete n;
       n=siguiente;
    }
    
}



bool Lista::comparar(Lista l1, Lista l2){
    nodo* p=l1.inicio;
    nodo* o=l2.inicio;
    if (l1.longitudRecursiva() != l2.longitudRecursiva()) return false;
    while(p!=NULL){
        if(p->dato != o->dato) return false;
        p=p->siguiente;
        o=o->siguiente;
    }
    return true;
    
    
}




int Lista::longitudRecursiva(nodo* n){
    
    if (n != NULL){
        return longitudRecursiva(n->siguiente)+1;
    }
    else{
        return 0;
    }
}


int Lista::longitudRecursiva(){
    return longitudRecursiva(inicio);
}




void Lista::invertir()
{
        nodo *current = inicio;     //establezco el actual al inicio
        nodo *prev = NULL, *next = NULL; //seteo siguiente y anterior en null
  
        while (current) {  //mientras exista un actual
            next = current->siguiente; //almaceno al siguiente
            current->siguiente = prev; //invierto el puntero del actual
  
            //muevo los punteros una posición
            prev = current; 
            current = next; 
        } 
        inicio = prev; //establezco el nuevo inicio
}


int Lista::longitud(){
    nodo* n = inicio;
    int r=0;
    while (n != NULL){
        r++;
        n = n->siguiente;
    }
    return r;
}

void Lista::mostrarRecursivo(nodo* n){
    if (n != NULL){
        cout << "[" << n->dato << "]-->";
        mostrarRecursivo(n->siguiente);
    }
    return;
}


void Lista::mostrarRecursivo(){
    mostrarRecursivo(inicio);
    cout << "[FIN REC]" << endl;
}


void Lista::agregarNodo(int dato){
    nodo* n = new nodo();
    n->dato = dato;
    n->siguiente = inicio;
    inicio = n;
}

void Lista::insertarUltimo(int dato){
    
    nodo* n = new nodo();
    n->dato = dato;
    n->siguiente = NULL;

    if(inicio==NULL){
    inicio=n;
    }else{
    nodo* actual=inicio;
    while (actual->siguiente)
    {
       actual=actual->siguiente;
    }
    actual->siguiente = n;
    }
}


void Lista::remover(){
    if(inicio != NULL){
        nodo* n = inicio;
        inicio = n->siguiente;
        delete n;
    }
}

void Lista::mostrar(){
    nodo* n = inicio;
    while (n != NULL){
        cout << "[" << n->dato << "] --> ";
        n = n->siguiente;
    }
    cout << "[FIN]" << endl;
}


nodo* Lista::buscar(int num){
    nodo* n = inicio;
    while ((n != NULL)&& (n->dato != num)){
       n = n->siguiente;
        
    }
    return n;
}


void Lista::ordenar(){
    nodo*actual=inicio;
    nodo*siguiente=NULL;
    while (actual)
    {
        siguiente=actual->siguiente;
        while (siguiente)
        {
            if (actual->dato>siguiente->dato)
            {
                swap(actual->dato,siguiente->dato);
            }
            siguiente=siguiente->siguiente;
        }
        actual=actual->siguiente;
    }
    
}


void Lista::insertarElemento( int valor, int pos)
{
    nodo*q= new nodo();
    int i;
    q->dato = valor;
    nodo*t;
    
    if(pos==1)
    {
        q->siguiente = inicio;
        inicio = q;
        return;
    }
    else
    {
        t = inicio;
 
        for(i=1; t!=NULL; i++)
        {
            if(i==pos)
            {
                q->siguiente = t->siguiente;
                t->siguiente = q;
                return;
            }
            t = t->siguiente;
        }
    }
    if (longitudRecursiva()<pos)insertarUltimo(valor);

}

void Lista::eliminarElemento( int valor)
{
    nodo* p;
    nodo* ant;
    p = inicio;
 
    if(inicio!=NULL)
    {
        while(p!=NULL)
        {
            if(p->dato==valor)
            {
                if(p==inicio)
                    inicio = inicio->siguiente;
                else
                    ant->siguiente = p->siguiente;
 
                delete(p);
                return;
            }
            ant = p;
            p = p->siguiente;
        }
    }
    else
        cout<<" Lista vacia..!";
}

void Lista::repetidos(){
    nodo*buscado=inicio;
    nodo*actual=inicio;
    nodo*aux=inicio;
    int valor;
    while(buscado){
    valor=buscado->dato;
        while(actual)
        {
        if(actual->dato==valor)
        {
            if(actual==inicio) 
            {
            inicio = inicio->siguiente;
            delete(actual);
            actual = inicio;
            }
        else
        {
                aux-> siguiente= actual->siguiente;
            delete(actual);
                actual = aux->siguiente;
        }
        }
        else
        {
            aux = actual;
            actual = actual->siguiente;
        }
            
        }
        buscado=buscado->siguiente;
        actual=buscado->siguiente;
        }
 }




void Lista::eliminarCada2(){
   
 
 if (inicio == NULL)  return;  
  
    nodo *ant = inicio;  
    nodo *actual = inicio->siguiente;  
  
    while (ant != NULL && actual != NULL)  
    {  
        ant->siguiente = actual->siguiente;  
        free(actual);  
        ant = ant->siguiente->siguiente;  
        if (ant != NULL)  
            actual = ant->siguiente;  
    } 


}




//  if (inicio == NULL)  return;  
  
//     nodo *ant = inicio;  
//     nodo *actual = inicio->siguiente;  
  
//     while (ant != NULL && actual != NULL)  
//     {  
//         ant->siguiente = actual->siguiente;  
//         free(actual);  
//         ant = ant->siguiente->siguiente;  
//         if (ant != NULL)  
//             actual = ant->siguiente;  
//     } 


int main(){



    Lista l;
    Lista m;
    for (int i = 0; i < 20; i++)
    {
         //l.agregarNodo(rand() % 100 + 1);
        l.insertarUltimo(i);
        // m.agregarNodo(i);
    }
    
    // l.mostrarRecursivo();
    // l.invertir();
    // l.mostrarRecursivo();
    // int buscar=rand() % 100 + 1;
    // cout<<"buscando a "<<buscar<<endl;
    // nodo* buscado= l.buscar(buscar);
    // if (buscado != NULL){cout<<"valos buscado: "<<buscado->dato<<endl<<"ubicación: "<<&buscado<<endl;}
    // else {cout<<"valor no encontrado"<<endl;}
    //  l.remover();
    //  l.mostrar();
    //  l.remover();
    //  l.mostrar();
    //int total=l.longitudRecursiva();
    //cout<<"largo1: "<<total<<endl;
    // l.insertarUltimo(14);
    // l.mostrarRecursivo();
    // Lista n;
    // n.insertarUltimo(69);
    // n.mostrar();
    // total=n.longitudRecursiva();
    // cout<<"largo2: "<<total<<endl;
    //l.ordenar();
    //l.insertarUltimo(22);
    //l.insertarElemento(100,11);
    // l.insertarElemento(100,5);
    l.mostrarRecursivo();
    l.eliminarElemento(15);
    l.eliminarElemento(17);
    l.mostrarRecursivo();
    //l.repetidos();
    // l.mostrarRecursivo();
    //l.eliminarCada2();
    // l.remover();
    // l.remover();
    // l.remover();
    // l.mostrarRecursivo();
    // m.mostrarRecursivo();
    
    // if(l.comparar(l,m)==true) cout<<"son iguales"<<endl;
    // else cout<<"son diferentes"<<endl;

    return 0;
}