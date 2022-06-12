#include <iostream>
#include <sstream>
#include <queue>

using namespace std;

struct nodo{
    int dato;
    nodo* izquierdo;
    nodo* derecho;
};

class Abb{
    private:
        nodo* raiz;
        nodo* crearNodo(int);
        nodo* insertar(int, nodo*);
        void destructor(nodo*);
        nodo* borrar(nodo*, int);  
        nodo* Minimo(nodo* );
        nodo* Maximo(nodo* );
        int Profundidad(nodo*, int, int);
        int DistanciaMinimoMaximo(nodo*, int, int);
        nodo* BuscarAncestro2(nodo*, int, int);
    public:
        Abb();
        void insertar(int);
        nodo* Maximo();
        nodo* Minimo();
        nodo* borrar(int); 
        int DistanciaMinimoMaximo(); 
        ~Abb();
        
};

Abb::Abb(){
    raiz = NULL;
}

Abb::~Abb(){
    destructor(raiz);
}

void Abb::destructor(nodo* hoja){
    if(hoja){
        destructor(hoja->izquierdo);
        destructor(hoja->derecho);
        delete(hoja);
    }
}

nodo* Abb::crearNodo(int dato){
    nodo* n = new nodo;
    n->dato = dato;
    n->izquierdo = NULL;
    n->derecho = NULL;
    return n;
}


nodo* Abb::insertar(int dato, nodo* hoja){
    if (hoja == NULL){
        // Insertar el nuevo elemento
        hoja = crearNodo(dato);
    }
    else if (dato < hoja->dato){
        hoja->izquierdo = insertar(dato, hoja->izquierdo);
    }
    else {
        hoja->derecho = insertar(dato, hoja->derecho);
    } 
    return hoja;
}

void Abb::insertar(int dato){
    raiz = insertar(dato, raiz);
}





nodo* Abb::Maximo(){
    return Maximo(raiz);
} 



nodo* Abb::Minimo(){
    return Minimo(raiz);
} 


  

nodo* Abb::borrar(int dato) 
{ 
    return borrar(raiz,dato);
} 


nodo* Abb::borrar(nodo* hoja, int dato) 
{ 
    if(hoja){
        if(dato<hoja->dato) hoja->izquierdo = borrar(hoja->izquierdo,dato);
        else if(dato>hoja->dato) hoja->derecho = borrar(hoja->derecho,dato);
        else{
            if(hoja->izquierdo==NULL&&hoja->derecho==NULL){
                delete hoja;
                hoja=NULL;
            }

            else if (hoja->izquierdo == NULL)  { 
                 nodo *aux = hoja; 
                hoja=hoja->derecho;
                delete aux; 
            } 
            else if (hoja->derecho == NULL) { 
                 nodo *aux = hoja; 
                hoja=hoja->izquierdo;
                delete aux; 
            } 

            else{
             nodo* aux = Minimo(hoja->derecho); 
            hoja->dato = aux->dato; 
            borrar(hoja->derecho, aux->dato);
            }
        }
    }
    return hoja;
} 



//_________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________
//EJERCICIO DE PARCIAL

int Abb::Profundidad(nodo* hoja, int dato, int nivel){
    if(hoja==NULL) return 0;
    if (hoja->dato==dato) return nivel;
    int nuevoNivel= Profundidad(hoja->izquierdo,dato,nivel+1);  
    if (nuevoNivel!=0) return nuevoNivel;
    nuevoNivel=Profundidad(hoja->derecho,dato,nivel+1);
    return nuevoNivel;             
}


nodo* Abb::Maximo(nodo* hoja) {    
    if (hoja == NULL){
        return NULL;
    }
    else if (hoja->derecho == NULL){
        return hoja;        
    }
    else{
        return Maximo(hoja->derecho);
    }
} 

nodo* Abb::Minimo(nodo* hoja) { 
    if (hoja == NULL){
        return NULL;
    }
    else if (hoja->izquierdo == NULL){
        return hoja;        
    }
    else{
        return Minimo(hoja->izquierdo);
    }
} 

nodo* Abb::BuscarAncestro2(nodo* hoja, int a, int b){
    if(hoja==NULL){
        return NULL;
    }

    if (a>b)  swap(a,b);

    while (a> hoja->dato && b< hoja->dato)
    {
        hoja=hoja->derecho;
    }

    while (a< hoja->dato && b< hoja->dato)
    {
        hoja=hoja->izquierdo;
    }

    return hoja;
    
}

int Abb::DistanciaMinimoMaximo(){
    int a= Minimo(raiz)->dato;
    int b= Maximo(raiz)->dato;
    return DistanciaMinimoMaximo(raiz, a, b);
}

int Abb::DistanciaMinimoMaximo(nodo* hoja, int a, int b){
    if (hoja==NULL){
        return -1;
    }

    nodo* AncestroComun = BuscarAncestro2(hoja, a, b);

    int d1 = Profundidad (AncestroComun, a, 0);
    int d2 = Profundidad (AncestroComun, b, 0);

    return d1+d2;
    
}

//_________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________

int main(){

    Abb abb1;
    abb1.insertar(7);
    abb1.insertar(12);
    abb1.insertar(1);
    abb1.insertar(14);
    abb1.insertar(3);
    abb1.insertar(15);
    abb1.insertar(9);
    abb1.insertar(6);
   
     cout<<"distancia entre minimo y maximo: "<<abb1.DistanciaMinimoMaximo()<<endl;


}