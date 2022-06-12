#include<iostream>
using namespace std;
#include <queue>
#include <stack>


struct nodo{
    int destino;
    nodo* siguiente;
};

class Grafo{
    private:
        int v;
        nodo** l;
        void profundidad(int, bool*);
        void Topologico(int, bool*, stack<int>&);
    public:
        Grafo(int);
        ~Grafo();
        void agregar(int,int);
        void mostrar();
        void amplitud(int);
        void profundidad(int);
        void Khan();
        void Topologico();
};

Grafo::Grafo(int v){
    this->v = v;
    l = new nodo*[v];
    for(int i = 0; i< v; i++){
        l[i] = NULL;
    }
}

Grafo::~Grafo(){
    
    for (int i = 0; i < v; i++)
    {
        nodo* n=l[i];
        while (n!=NULL)
        {
            nodo* aux=n->siguiente;
            delete n;
            n=aux;
        }
        
    }
    delete[] l;
}

void Grafo::agregar(int o,int d){
    if(o>=0 && o<v && d>=0 && d<v){
        
        nodo*n = new nodo();
        n->destino=d;
        n->siguiente=l[o];
        l[o]=n;
        
    }
    
}

void Grafo::mostrar(){
    cout<<"lista de adyacencia:"<<endl;
    for (int i = 0; i < v; i++)
    {
        nodo* n=l[i];
        cout<<"["<<i<<"]->";
        while (n!=NULL)
        {
            cout<<"["<<n->destino<<"]---->";
            n=n->siguiente;
        }
        cout<<"[FIN]"<<endl;
    }

}


void Grafo::amplitud(int inicial) { 
    bool* visitado = new bool [v];
    for(int i=0; i<v; i++){
        visitado[i]=false;
    }
    queue <int> cola;
    cola.push(inicial);
    while(!cola.empty()){
        cout<<cola.front()<<"->";
        cola.pop();
        nodo* n = l[inicial];
        visitado[inicial] = true;
        while(n != NULL){
            if(visitado[n->destino]==false){
                cola.push(n->destino);
                visitado[n->destino] = true;
            }
            n=n->siguiente;
        }
        inicial = cola.front();
    }
    cout<<"[FIN]"<<endl;
    delete [] visitado;   
} 


void Grafo::profundidad(int inicial){
    bool* visitado = new bool[v];  //vector de visitados 
    for(int i = 0; i < v; i++) { 
        visitado[i] = false;       //los pongo en falso
    } 
    
    profundidad(inicial, visitado);

    cout<<"[FIN]"<<endl;
}

void Grafo::profundidad(int actual, bool* visitado) { 
    
    visitado[actual] = true;  //marcarlo como visitado
    cout << actual << "->"; 

    nodo* n = l[actual];
      while (n)
      {
        if(!visitado[n->destino]) profundidad(n->destino, visitado);
        n=n->siguiente;
      }

}

void Grafo::Khan(){
    //vector en el que almacenamos el grado de incidencia
    int *grados= new int[v];
    for (int i = 0; i < v; i++)
    {
        grados[i]=0;
    }
    
    //calculamos el grado inicial
    for (int i = 0; i < v; i++)
    {
        nodo* n= l[i];
        while (n)
        {
            grados[n->destino]++;
            n= n->siguiente;
        }
    }

    queue<int> cola;
    //buscar v con grado 0 y meterlo en la cola
    for (int i = 0; i < v; i++)
    {
        if (grados[i]==0)
        {
            cola.push(i);
        }
        
    }
    

    int* ot = new int[v];
    int cnt=0;

    //iteramos hasta vaciar la cola
    while (!cola.empty())
    {
        //w va al orden topologico
        int w=cola.front();
        cola.pop();
        ot[cnt]=w;

        nodo* n= l[w];
        while (n)
        {
            if (--grados[n->destino]==0)
            {
                cola.push(n->destino);
            }
            n=n->siguiente;
        }
        cnt++;
    }
    
    cout<<"orden topologico"<<endl; 
    for (int i = 0; i < v; i++)
    {
        cout<<ot[i]<<" - ";
    }
    cout<<endl;
    
}

void Grafo::Topologico(){
    stack<int> pila;
    bool* visitado = new bool[v];
    for (int i = 0; i < v; i++)
    {
        visitado[i]=false;
    }
    

    for (int i = 0; i < v; i++)
    {
        if (!visitado[i])
        {
            Topologico(i,visitado,pila);
        }
        
    }
    

    cout<<"orden topologico"<<endl; 
    while (!pila.empty())
    {
        cout<<pila.top()<<"-";
        pila.pop();
    }
    cout<<endl;

}

void Grafo::Topologico(int u, bool* visitado, stack<int>& pila){

    visitado [u]=true;

    nodo* n= l[u];
    while (n){
        if (!visitado[n->destino])
        {
            Topologico(n->destino,visitado,pila);
        }
        n=n->siguiente;
    }
    
    pila.push(u);
}

int main(){


    Grafo g(8);
    g.agregar(0,2);
    g.agregar(1,2);
    g.agregar(1,3);
    g.agregar(2,4);
    g.agregar(3,6);
    g.agregar(4,5);
    g.agregar(4,6);
    g.agregar(6,7);

    // g.mostrar();
    // cout<<"amplitud :"<<endl;   
    // g.amplitud(1);
    // cout<<"prof :"<<endl;
    // g.profundidad(1);
    g.Topologico();
    
    return 0;
}