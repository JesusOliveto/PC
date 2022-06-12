#include <iostream>
#include <algorithm>

using namespace std;

struct Arista{
    int origen;
    int destino;
    int peso;
    bool operator < (const Arista& a1) const {
		return (peso < a1.peso);
	}   
};

class Grafo {
	private:
		int v; 
		int a;
		int na;
		Arista* aristas;
		int Find(int* padre, int i);
		void Union(int* padre, int x, int y);
	public:
		Grafo(int,int);
		~Grafo();
		void AgregarArista(int,int,int);
		void Mostrar();
		void Kruskal();
};


Grafo::Grafo(int v, int a){
	this->v = v;
	this->a = a;
	this->na = 0;
	this->aristas = new Arista[a];
}

Grafo::~Grafo(){
	delete[] aristas;
}

void Grafo::AgregarArista(int origen, int destino, int peso){
	aristas[na].origen = origen;
	aristas[na].destino = destino;
	aristas[na].peso = peso;
	na++;
}

void Grafo::Mostrar(){
	cout << "Lista de Aristas" << endl;
	cout << "Origen\tDestino\tPeso" << endl;
	for (int i = 0; i < na; i++){
		cout << aristas[i].origen << "\t";
		cout << aristas[i].destino << "\t";
		cout << aristas[i].peso << "\n";
	}
	cout<<endl;	
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

int compararArista(const void* a, const void* b)
{
    Arista* pa = (Arista*)a;
    Arista* pb = (Arista*)b;
    return pa->peso > pb->peso;
}

void Grafo::Kruskal(){

    Arista resultado[v];  
    int r = 0;  // indice resultado
    int o = 0;  // indice para las aristas ordenadas
    
    int* padre = new int[a];
	for (int i = 0; i < a; i++){
		padre[i] = -1;
	}
	
	sort(aristas, aristas+a);	
	
	while (r < v - 1){
		 Arista aristaCandidata = aristas[o++];
		 
		int x = Find(padre, aristaCandidata.origen); //busca el conjunto del origen
		int y = Find(padre, aristaCandidata.destino); //busca el conjunto del destino
		
		
		if (x != y){
			resultado[r++] = aristaCandidata; //si los conjuntos son diferentes, no hay ciclo y lo suma al resultado
			Union(padre, x, y);	
		}
	}
	
	cout << "Arbol de recubrimiento mínimo" << endl;
    int pesoTotal=0;
    for (int i = 0; i < r; ++i){
        pesoTotal=pesoTotal+resultado[i].peso;
        cout << resultado[i].origen <<" --- " << resultado[i].destino <<" = " << resultado[i].peso << endl;
    }
    cout<<"peso total: "<<pesoTotal<<endl;
    return;
}


int main()
{
	Grafo g(9, 15);
	
	g.AgregarArista(0,1,4);
	g.AgregarArista(0,7,8);
	g.AgregarArista(1,2,8);  
	g.AgregarArista(1,7,11);
	g.AgregarArista(2,3,7);
	g.AgregarArista(2,5,4);
	g.AgregarArista(2,8,2);
	g.AgregarArista(3,4,9);
	g.AgregarArista(3,5,14);
	g.AgregarArista(4,5,10);
	g.AgregarArista(5,6,2);
	g.AgregarArista(6,8,6);
	g.AgregarArista(6,8,6);
	g.AgregarArista(6,7,1);
	g.AgregarArista(7,8,7);

	g.Mostrar();
	
	g.Kruskal();
	
	return 0;
}