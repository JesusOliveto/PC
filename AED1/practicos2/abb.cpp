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
        nodo* buscar(int, nodo*);
        void inOrden(nodo*);
        void preOrden(nodo*);
        void postOrden(nodo*);
        int Altura(nodo* n);
        void destructor(nodo*);
        nodo* borrar(nodo*, int);  
        nodo* Minimo(nodo* );
        nodo* Maximo(nodo* );
        bool esBinario(nodo*,int,int);
        int cantidadHojas(nodo* );
        bool Balanceado(nodo* ); 
        int Profundidad(nodo*, int, int);
        int Distancia(nodo*, int, int);
        int DistanciaMinimoMaximo(nodo*, int, int);
        nodo* BuscarAncestro(nodo*, int, int);
        nodo* BuscarAncestro2(nodo*, int, int);
    public:
        Abb();
        void inOrden();
        void preOrden();
        void postOrden();
        void insertar(int);
        nodo* buscar(int);
        void recorrerAmplitud();
        int Altura();
        nodo* Maximo();
        nodo* Minimo();
        nodo* borrar(int); 
        bool esBinario();
        int cantidadHojas();
        int Profundidad(int);
        bool Balanceado(); 
        int Distancia(int, int);
        int DistanciaMinimoMaximo(); 
        nodo* BuscarAncestro(int, int);
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



nodo* Abb::buscar(int dato){
    return buscar(dato, raiz);
}

nodo* Abb::buscar(int dato, nodo* hoja){

     if (hoja == NULL){
        return NULL;
    }

    if (dato== hoja->dato){
        return hoja;
    }
    else if (dato < hoja->dato){
       return buscar(dato, hoja->izquierdo);
    }
    else {
        return buscar(dato, hoja->derecho);
    } 
    
}



void Abb::inOrden(nodo* hoja){
    if(hoja){
        inOrden(hoja->izquierdo);
        cout<< hoja->dato <<"--";
        inOrden(hoja->derecho);
    }
}

void Abb::inOrden(){
    cout<<"Recorrido inorden: "<<endl;
    inOrden(raiz);
    cout<<endl;
}


void Abb::preOrden(nodo* hoja){
    if(hoja){
        cout<< hoja->dato <<"--";
        preOrden(hoja->izquierdo);
        preOrden(hoja->derecho);
    }
}

void Abb::preOrden(){
    cout<<"Recorrido preorden: "<<endl;
    preOrden(raiz);
    cout<<endl;
}


void Abb::postOrden(nodo* hoja){
    if(hoja){
        postOrden(hoja->izquierdo);
        postOrden(hoja->derecho);
        cout<< hoja->dato <<"--";
    }
}

void Abb::postOrden(){
    cout<<"Recorrido postorden: "<<endl;
    postOrden(raiz);
    cout<<endl;
}

void Abb::recorrerAmplitud(){
    cout<<"Recorrido por amplitud: "<<endl;
    queue<nodo*> c;
    nodo* nodoActual = raiz;
    while (nodoActual) {
        cout << nodoActual->dato <<"--";
        if (nodoActual->izquierdo) c.push(nodoActual->izquierdo);
        if (nodoActual->derecho) c.push(nodoActual->derecho);
        nodoActual = c.front();
        c.pop();
    }
    cout << endl;
}


//------------------------------------------------------------------------------------------------------
//EJERCICIO 22

int Abb::cantidadHojas(){
    return cantidadHojas(raiz);
}

int Abb::cantidadHojas(nodo* hoja){
    if(hoja==NULL)return 0;
    if(hoja->derecho==NULL&&hoja->derecho==NULL)
         return 1;
    else return cantidadHojas(hoja->derecho)+cantidadHojas(hoja->izquierdo);
}

//------------------------------------------------------------------------------------------------------
//EJERCICIO 23
int Abb::Profundidad(int dato){
    return Profundidad(raiz,dato,1);
}

int Abb::Profundidad(nodo* hoja, int dato, int nivel){
    if(hoja==NULL) return 0;
    if (hoja->dato==dato) return nivel;                         //si es el dato, retorno el nivel

    int nuevoNivel= Profundidad(hoja->izquierdo,dato,nivel+1);      //sino, busco por derecha
    if (nuevoNivel!=0) return nuevoNivel;
    //si no está en el izquierdo, busco en el derecho
    nuevoNivel=Profundidad(hoja->derecho,dato,nivel+1);
    return nuevoNivel;             
}

//------------------------------------------------------------------------------------------------------
//EJERCICIO 24
bool Abb::Balanceado(){
    return Balanceado(raiz);
}

bool Abb::Balanceado(nodo* hoja){

    if (hoja==NULL) return true;

//  por no poner esto gasté 48 minutos 
//        |
//        V          
    if ( abs(Altura(hoja->izquierdo)-(Altura(hoja->derecho)))<=1 && Balanceado(hoja->izquierdo) && Balanceado(hoja->derecho) ) return true; 
    else return false;
}
//------------------------------------------------------------------------------------------------------
//EJERCICIO 24 
//tiempo gastado pensando en como implementarlo: 46 + 38 + 25 + 34 minutos TOTAL: 2 horas y media xD 
//estado anterior: no encuentra el ancestro común (hecho)
//estado actual: funcional
nodo* Abb::BuscarAncestro(int a, int b){
    
    return BuscarAncestro2(raiz, a, b);
}

nodo* Abb::BuscarAncestro(nodo* hoja, int a, int b){
    if(hoja==NULL){
        return NULL;
    }

    //si uno de los dos está presente, entonces ese es el Ancestro común
    if(hoja->dato == a || hoja->dato== b) return hoja;

    //controlo que se encuentre uno a la izquierda y otro a la derecha
    nodo* AncestroIzq = BuscarAncestro (hoja->izquierdo, a, b);
    nodo* AncestroDer = BuscarAncestro (hoja->derecho, a, b);

    //si se encuentra uno de cada lado, ese es el Ancestro común
    if(AncestroIzq != NULL && AncestroDer != NULL){
        return hoja;
    }
 
    return (AncestroIzq!= NULL)? AncestroIzq : AncestroDer;    
}


int Abb::Distancia(int a, int b){
    return Distancia(raiz, a, b);
}

int Abb::Distancia(nodo* hoja, int a, int b){
    if (hoja==NULL){
        return -1;
    }

    nodo* AncestroComun = BuscarAncestro2(hoja, a, b);

    int d1 = Profundidad (AncestroComun, a, 0);
    int d2 = Profundidad (AncestroComun, b, 0);

    return d1+d2;
    
}
//------------------------------------------------------------------------------------------------------
int Abb::Altura(){
    return Altura(raiz);
}
  +
int Abb::Altura(nodo* n)  
{  
    if (n == NULL)  
        return 0;  
    else
    {  
        int altoIzq = Altura(n->izquierdo);  
        int altoDer = Altura(n->derecho);  
      
        if (altoIzq > altoDer)  
            return(altoIzq + 1);  
        else return(altoDer + 1);  
    }  
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

bool Abb::esBinario(){
    return esBinario(raiz,0,1000);
}

bool Abb::esBinario(nodo* hoja, int min,int max){
    if(hoja==NULL) return false;
    if(hoja->dato<min || hoja->dato>max) return false;
    return esBinario(hoja->izquierdo,min,hoja->dato-1) && esBinario(hoja->derecho,hoja->dato+1,max);
}


//_________________________________________________________________________________________________________________________
//_________________________________________________________________________________________________________________________
//EJERCICIO DE PARCIAL

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
    
    // nodo* n1=abb1.buscar(6);
    // nodo* n2=abb1.buscar(16);
    // cout << "El valor 6 " << (n1 ? " si ": " no ") << "está" << endl;
    // cout << "El valor 16 " << (n2 ? " si ": " no ") << "está" << endl;
    
    // abb1.inOrden();
    // abb1.preOrden();
    // abb1.postOrden();
    // abb1.recorrerAmplitud();

    // cout<< "altura: " << abb1.Altura()<<endl;
    // cout<< "max: " << abb1.Maximo()<<endl;
    // cout<< "min: " << abb1.Minimo()<<endl;

    // abb1.preOrden();
    // abb1.borrar(7);
    // abb1.preOrden();

    // abb1.buscar(6)->dato=30;
    // cout << "El arbol " << (abb1.esBinario ? " si ": " no ") << "es binario" << endl;
    // return 0;
    // abb1.recorrerAmplitud();
    // cout<<"cantidad de hojas: " <<abb1.cantidadHojas()<<endl;
    // cout<<"Profundidad del nodo 15:" <<abb1.Profundidad(15)<<endl;
    // cout << "El arbol " << (abb1.Balanceado() ? " si ": " no ") << "está balanceado" << endl;

     //cout<<"ancestro en común: "<< abb1.BuscarAncestro(6,1)->dato<<endl;
     //cout<<"distancia entre 1 y 15: "<< abb1.Distancia(1,15)<<endl;
     
     cout<<"distancia entre minimo y maximo: "<<abb1.DistanciaMinimoMaximo()<<endl;


    

}