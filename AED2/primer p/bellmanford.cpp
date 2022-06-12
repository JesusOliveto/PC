#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

const int INF=999999;

struct nodo{
    int origen;
    int destino;
    int peso;
    nodo* siguiente;
    
};

class Grafo
{
private:
    int V;
    int E;
    nodo* aristas;
    int Find(int* padre, int i);
    void Union(int* padre, int x, int y);
public:
    Grafo(int);
    ~Grafo();
    void agregar(int,int,int);
    void BellmanFord(int);
    void mostrar();
    bool TieneCiclos();

};

Grafo::Grafo(int V)
{
    this->V = V;
    this->E=0;
    aristas = NULL;
    
}

Grafo::~Grafo()
{
    nodo *n=aristas, *siguiente=NULL;
    while (n!=NULL)
    {
       siguiente=n->siguiente;
       delete n;
       n=siguiente;
    }
}

void Grafo::agregar(int origen, int destino, int peso){
    nodo* n = new nodo();
    n->origen = origen;
    n->destino=destino;
    n->peso=peso;
    n->siguiente = aristas;
    aristas = n;
    E++;
}

void Grafo::mostrar(){
    nodo* n = aristas;
    while (n != NULL){
        cout <<"origen:"<<n->origen<< " destino:"<<n->destino<<" peso:("<<n->peso<<")"<<endl;
        n = n->siguiente;
    }
    cout << "[FIN]" << endl;
}


void Grafo::BellmanFord(int src){
    int dist[V]; 

    for (int i = 0; i < V; i++) 
        dist[i] = INF; 
    dist[src] = 0;

    for (int i = 1; i <= V - 1; i++) {
        nodo* n=aristas; 
        while (n)
        {
            if (dist[n->origen] != INF && dist[n->origen] + n->peso < dist[n->destino]) 
                dist[n->destino] = dist[n->origen] + n->peso; 

            n=n->siguiente;
        }
    } 


    cout<<"distancia desde el origen:"<<endl;
    for (int i = 0; i < V; ++i) 
        printf("%d \t\t %d\n", i, dist[i]); 

}

int Grafo::Find(int* padre, int i){
    if (padre[i] == -1)
        return i;
    return Find (padre, padre[i]);
}

void Grafo::Union(int* padre, int x, int y){
    int conjuntox = Find(padre, x);
    int conjuntoy = Find(padre, y);
    padre[conjuntox] = conjuntoy;
}

bool Grafo::TieneCiclos(){
    int* padre = new int[V];
    for (int i = 0; i < V; i++){
        padre[i] = -1;
    }
    nodo* a = aristas;

    while (a){
        int x = Find(padre, a->origen);
        int y = Find(padre, a->destino);

        if (x == y)
            return true;
        Union(padre, x, y);

        a = a->siguiente;
    }
    return false;
}

}

int main(){
    Grafo g(9);
    g.agregar(0,1,4);
    g.agregar(0,7,8);
    g.agregar(1,2,8);
    g.agregar(1,7,11);
    g.agregar(2,3,7);
    g.agregar(2,5,4);
    g.agregar(2,8,2);
    g.agregar(3,4,9);
    g.agregar(3,5,14);
    g.agregar(4,5,10);
    g.agregar(5,6,2);
    g.agregar(6,8,6);
    g.agregar(6,7,1);
    g.agregar(7,8,7);

    g.mostrar();
    // g.BellmanFord(0);
    // if(g.TieneCiclos()==true) cout<<"g tiene ciclos"<<endl;
    // else cout<<"g no tiene ciclos"<<endl;

    //g.Kruskal();

    return 0;
}