#include <iostream>
#include <sstream>
#include <climits>

const int INF=INT_MAX;

using namespace std;


class Grafo{
    private:
        int** arista;
        int V;
        bool dirigido;
        bool ponderado; 
    public:
        Grafo(int,bool,bool);
        ~Grafo();
        void insertarArista(int,int);
        void quitarArista(int,int);
        void insertarArista(int,int,int);
        void quitarArista(int,int,bool);
        void transitiva();
        void mostrar(int,int);
        void imprimir();
        int peso();
};

Grafo::Grafo(int vertices, bool d,bool p){
    ponderado=p;
    dirigido=d;
    V=vertices;
    arista = new int* [V];
    for(int i=0; i<V; i++) 
        arista[i] = new int[V];

    if (ponderado)
    {
       for (int i = 0; i < V; i++)
     {
        for (int j = 0; j < V; j++)
         {
             arista[i][j]=INF;
         }
        
        }
    }
    
    
}

Grafo::~Grafo(){
    
      for(int i = 0; i < V; i++)
            delete[] arista[i];
    delete[] arista;
}

void Grafo::insertarArista(int a, int b){
    if (dirigido==true && ponderado==false)
    {
        if(a >=0 && a <V && b>= 0 && b <V)
        arista[a][b]=1;
    }
    else if (ponderado==false)
    {
        if(a >=0 && a <V && b>= 0 && b <V)
        arista[a][b]=1; arista[b][a]=1;
    }

}

void Grafo::insertarArista(int a, int b, int peso){
    if (dirigido==true && ponderado==true)
    {
        if(a >=0 && a <V && b>= 0 && b <V)
        arista[a][b]=peso;
    }
    else if (ponderado==true)
    {
        if(a >=0 && a <V && b>= 0 && b <V)
        arista[a][b]=peso; arista[b][a]=peso;
    }

}

void Grafo::quitarArista(int a, int b){
    if (dirigido==true && ponderado==false)
    {
        if(a >=0 && a <V && b>= 0 && b <V)
        arista[a][b]=0;
    }
    else if (ponderado==false)
    {
        if(a >=0 && a <V && b>= 0 && b <V)
        arista[a][b]=0; arista[b][a]=0;
    }

}

void Grafo::quitarArista(int a, int b, bool p){
    if (dirigido==true && ponderado==true)
    {
        if(a >=0 && a <V && b>= 0 && b <V)
        arista[a][b]=INF;
    }
    else if (ponderado==true)
    {
        if(a >=0 && a <V && b>= 0 && b <V)
        arista[a][b]=INF; arista[b][a]=INF;
    }

}

void Grafo::mostrar(int a, int b){
    cout<<"["<<arista[a][b]<<"]   ";
}

void Grafo::imprimir(){
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            mostrar(i,j);

        }
        cout<<endl;
    }
}



int Grafo::peso(){
    int r=0;

    r=V*V*(sizeof(int))+V*8;
    return r;
}

void Grafo::transitiva(){
    int m[v][v];

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            m[i][j]=arista[i][j];

        }
    }

    for (int k = 0; k < V; k++){
        for (int i = 0; i < V; i++){
            for (int j = 0; j < V; j++){
                if (m[i][j]==1 || (m[i][k]==1 && m[k][j]==1)) m[i][j]=1;
                else m[i][j]=0;
            }
            
        }
        
    }

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            cout<<m[i][j];

        }
        cout<<endl;
    }
    
}   



int main(){
    int N;
    cout<<"ingrese los vertices:"<<endl;
    cin>>N;
    // Grafo a1(N,false,false);

    // a1.insertarArista(1,3);
    // a1.insertarArista(1,2);
    // a1.insertarArista(2,4);

    Grafo a2(N,true,false);

    a2.insertarArista(1,3);
    a2.insertarArista(1,2);
    a2.insertarArista(2,4);
    a2.insertarArista(3,4);

    // Grafo a3(N,false,true);
    // a3.insertarArista(1,3,5);
    // a3.insertarArista(1,2,6);
    // a3.insertarArista(2,4,8);

    // cout<<"Grafo no dirigido: "<<endl;
    // a1.imprimir();

    cout<<"Grafo dirigido: "<<endl;
    a2.imprimir();

    // cout<<"Grafo ponderado: "<<endl;
    // a3.imprimir();
    
    
    cout<<"matriz transitiva"<<endl;
    a2.transitiva();

    //cout<<"peso total: "<<a1.peso()<<" bytes "<<endl;


    return 0;
}

---------------------------------------------------------













#include <iostream>
#include <sstream>
#include <climits>

const int INF=INT_MAX;

using namespace std;


class Grafo{
    private:
        int** arista;
        int V;
        bool dirigido;
        bool ponderado; 
    public:
        Grafo(int,bool,bool);
        ~Grafo();
        void insertarArista(int,int);
        void quitarArista(int,int);
        void insertarArista(int,int,int);
        void quitarArista(int,int,bool);
        void mostrar(int,int);
        void imprimir();
        int peso();
};

Grafo::Grafo(int vertices, bool d,bool p){
    ponderado=p;
    dirigido=d;
    V=vertices;
    arista = new int* [V];
    for(int i=0; i<V; i++) 
        arista[i] = new int[V];

    if (ponderado)
    {
       for (int i = 0; i < V; i++)
     {
        for (int j = 0; j < V; j++)
         {
             arista[i][j]=INF;
         }
        
        }
    }
    
    
}

Grafo::~Grafo(){
    
      for(int i = 0; i < V; i++)
            delete[] arista[i];
    delete[] arista;
}

void Grafo::insertarArista(int a, int b){
    if (dirigido==true && ponderado==false)
    {
        if(a >=0 && a <V && b>= 0 && b <V)
        arista[a][b]=1;
    }
    else if (ponderado==false)
    {
        if(a >=0 && a <V && b>= 0 && b <V)
        arista[a][b]=1; arista[b][a]=1;
    }

}

void Grafo::insertarArista(int a, int b, int peso){
    if (dirigido==true && ponderado==true)
    {
        if(a >=0 && a <V && b>= 0 && b <V)
        arista[a][b]=peso;
    }
    else if (ponderado==true)
    {
        if(a >=0 && a <V && b>= 0 && b <V)
        arista[a][b]=peso; arista[b][a]=peso;
    }

}

void Grafo::quitarArista(int a, int b){
    if (dirigido==true && ponderado==false)
    {
        if(a >=0 && a <V && b>= 0 && b <V)
        arista[a][b]=0;
    }
    else if (ponderado==false)
    {
        if(a >=0 && a <V && b>= 0 && b <V)
        arista[a][b]=0; arista[b][a]=0;
    }

}

void Grafo::quitarArista(int a, int b, bool p){
    if (dirigido==true && ponderado==true)
    {
        if(a >=0 && a <V && b>= 0 && b <V)
        arista[a][b]=INF;
    }
    else if (ponderado==true)
    {
        if(a >=0 && a <V && b>= 0 && b <V)
        arista[a][b]=INF; arista[b][a]=INF;
    }

}

void Grafo::mostrar(int a, int b){
    cout<<"["<<arista[a][b]<<"]   ";
}

void Grafo::imprimir(){
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            mostrar(i,j);

        }
        cout<<endl;
    }
}



int Grafo::peso(){
    int r=0;

    r=V*V*(sizeof(int))+V*8;
    return r;
}




int main(){
    int N;
    cout<<"ingrese los vertices:"<<endl;
    cin>>N;
    Grafo a1(N,false,false);

    a1.insertarArista(1,3);
    a1.insertarArista(1,2);
    a1.insertarArista(2,4);

    Grafo a2(N,true,false);

    a2.insertarArista(1,3);
    a2.insertarArista(1,2);
    a2.insertarArista(2,4);

    Grafo a3(N,false,true);
    a3.insertarArista(1,3,5);
    a3.insertarArista(1,2,6);
    a3.insertarArista(2,4,8);

    cout<<"Grafo no dirigido: "<<endl;
    a1.imprimir();

    cout<<"Grafo dirigido: "<<endl;
    a2.imprimir();

    cout<<"Grafo ponderado: "<<endl;
    a3.imprimir();
    
    //cout<<"peso total: "<<a1.peso()<<" bytes "<<endl;


    return 0;
}



----------------------------------------------------
amplitud 

void Grafo::amplitud(int inicial) { 
    bool* visitado = new bool[V]; 
	for(int i = 0; i < V; i++) { 
		visitado[i] = false; 
	} 
 
	queue<int> pendiente; 
	pendiente.push(inicial);  //encolar el vértice origen
	visitado[inicial] = true;  //marcarlo como visitado
 
	while(pendiente.size() != 0) {    //procesarlo hasta que no haya más vértices
		int actual = pendiente.front(); 
		pendiente.pop();      
		cout << actual << " ";       //extraer el actual y procesarlo
		for(int i = 0; i < V; i++) { 
			// if(i == actual) { 
			// 	continue; 
			// } 
			if(arista[actual][i] == 1 && !visitado[i]) {  //si no fue visitado, encolar y visitar
				pendiente.push(i); 
				visitado[i] = true; 
			} 
		} 
	} 
	delete [] visitado;   //destructor
} 







void Grafo::TSP(int ciudad){
    int ciudadCercana;
    int visitadas[V];
    int costo=0;
    for (int i = 0; i < V; i++)
    {
        visitadas[i]=0;
    }
    
    visitadas[ciudad]=1;

    cout<<ciudad+1;
    ciudadCercana = CiudadCercana(ciudad,visitadas,costo);

    if (ciudadCercana==INF)
    {
        ciudadCercana=0;
        cout<<ciudadCercana+1;
        costo=costo+ arista[ciudad][ciudadCercana];
        return;
    }
    TSP(ciudadCercana);
}

int Grafo::CiudadCercana(int ciudad, int visitadas[],int costo){
    int ciudadCercana=INF;
    int minimo=INF;
    int temp;

    for (int i = 0; i < V; i++)
    {
        if ((arista[ciudad][i]!=0) && (visitadas[i]==0))
        {
            if (arista[ciudad][i]<minimo)
            {
                minimo=arista[i][0]+arista[ciudad][i];
            }
            temp=arista[ciudad][i];
            ciudadCercana=i;
        }
        
    }
    if (minimo!=INF)
        costo=costo+temp;
    
    return ciudadCercana;
}


void TSP (int);
        int CiudadCercana(int ciudad, int visitadas[], int costo);