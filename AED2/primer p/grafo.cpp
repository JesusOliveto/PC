#include <iostream>
#include <sstream>
#include <climits>
#include <queue>
#include <stack>

const int INF=999999;

using namespace std;


class Grafo{
    private:
        int** arista;
        int V;
        bool dirigido;
        bool ponderado;
        void profundidad(int, bool*);
        void Topologico(int, bool*, stack<int>&);

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
        void amplitud(int);
        int peso();
        void profundidad(int);
        void Topologico();
        void Dijkstra (int);
        void Prim ();
        int minDistance(int dist[],bool sptSet[]);
        int valorMin(int valor[],bool mst[]);
        void FloydWarshall();
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
             arista[i][j]=0;
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
            if (i==0)
            {
                cout<<"{"<<j<<"}   ";
            }
            else if (j==0)
            {
                cout<<"{"<<i<<"}   ";
            }
            else
            {
               cout<<"["<<arista[i][j]<<"]   ";
            }

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
    int** m;
    m = new int* [V];
    for(int i=0; i<V; i++) 
        m[i] = new int[V];

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
            } 
        }
    }

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (i==0)
            {
                cout<<"{"<<j<<"}   ";
            }
            else if (j==0)
            {
                cout<<"{"<<i<<"}   ";
            }
            else
            {
               cout<<"["<<m[i][j]<<"]   ";
            }
            
            
            

        }
        cout<<endl;
    }
    
} 

void Grafo::amplitud(int inicial) { 
    bool* visitado = new bool[V];  //vector de visitados 
    for(int i = 0; i < V; i++) { 
        visitado[i] = false;       //los pongo en falso
    } 
 
    queue<int> pendiente; 
    pendiente.push(inicial);  //encolar el vértice origen
    visitado[inicial] = true;  //marcarlo como visitado
 
    while(!pendiente.empty())  //procesarlo hasta que no haya más vértices
    {
        int actual = pendiente.front(); 
        pendiente.pop();
        cout << actual << "->";       //extraer el actual y procesarlo
        for(int i = 0; i < V; i++) 
        { 
            if(arista[actual][i] == 1 && !visitado[i])  //si no fue visitado, encolar y visitar
            {
                pendiente.push(i); 
                visitado[i] = true; 
            } 
        } 
    } 
    cout<<"[FIN]"<<endl;
    delete [] visitado;   //destructor del vector
}




void Grafo::profundidad(int inicial){
    bool* visitado = new bool[V];  //vector de visitados 
    for(int i = 0; i < V; i++) { 
        visitado[i] = false;       //los pongo en falso
    } 
    
    profundidad(inicial, visitado);

    cout<<"[FIN]"<<endl;
    delete [] visitado; 
}

void Grafo::profundidad(int actual, bool* visitado) { 
    
    visitado[actual] = true;  //marcarlo como visitado
    cout << actual << "->"; 

      for(int i = 0; i < V; i++) 
      { 
         if(arista[actual][i] == 1 && !visitado[i])  //si no fue visitado, encolar y visitar
         {
             profundidad(i, visitado);
         } 
     } 
    
}


void Grafo::Topologico(){
    stack<int> pila;
    bool* visitado = new bool[V];
    for (int i = 0; i < V; i++)
    {
        visitado[i]=false;
    }
    

    for (int i = 0; i < V; i++)
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



    for(int i = 0; i < V; i++) 
      { 
         if(arista[u][i] == 1 && !visitado[i])  //si no fue visitado, encolar y visitar
         {
            Topologico(i,visitado,pila);
         } 
     } 
    
    pila.push(u);
}

int Grafo::minDistance(int dist[],bool sptSet[]){
    // Initialize min value 
    int min = INT_MAX, min_index; 
  
    for (int v = 0; v < V; v++) 
        if (sptSet[v] == false && dist[v] <= min) 
            min = dist[v], min_index = v; 
  
    return min_index; 
}

void Grafo::Dijkstra (int origen){
    int dist[V];
    bool sptSet[V];
    for (int i = 0; i < V; i++) 
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[origen] = 0;

    for (int count = 0; count < V - 1; count++) { 
        
        int u = minDistance(dist, sptSet); 

        sptSet[u] = true; 
  
        for (int v = 0; v < V; v++) 
            if (!sptSet[v] && arista[u][v] && dist[u] != INT_MAX && dist[u] + arista[u][v] < dist[v]) 
                dist[v] = dist[u] + arista[u][v]; 
    } 

    printf("Vertex \t\t Distance from Source\n"); 
    for (int i = 0; i < V; i++) 
        printf("%d \t\t %d\n", i, dist[i]); 
}

void Grafo::FloydWarshall(){
    int** sp;
    sp = new int* [V];
    for(int i=0; i<V; i++) 
        sp[i] = new int[V];



    for (int i = 0; i < V; i++){
        for (int j = 0; j < V; j++){
            if (arista[i][j] > 0){
                sp[i][j] = arista[i][j];
            }
            else{
                sp[i][j] = INF;
            }
        }
    }
    for (int k = 0; k < V; k++){
        for (int i = 0; i < V; i++){
            for (int j = 0; j < V; j++){
                if (sp[i][k] + sp[k][j] < sp[i][j])
                    sp[i][j] = sp[i][k] + sp[k][j];
            }
        }
    }


    cout << "Caminos Minimos" << endl;
	for (int i = 0; i < V; i++){
		for (int j = 0; j < V; j++){
			if (sp[i][j] == INF)
				cout<<"-"<<"\t";
			else
				cout<<sp[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;	
}

int Grafo::valorMin(int valor[],bool mst[]){
    int min=INF , actual;
    for (int i = 0; i < V; i++){
        if (mst[i]==false && valor[i]<min){
            min=valor[i], actual=i;
        }
    }
    return actual;
    
}

void Grafo::Prim (){
    int padre[V];
    int valor[V];
    bool mst[V];

    for (int i = 0; i < V; i++)
    {
        valor[i]=INF;
        mst[i]=false;
    }

    valor[0]=0;
    padre[0]=-1;

    for (int i = 0; i < V-1; i++)
    {
        int u=valorMin(valor, mst);
        mst[u]=true;

        for (int j = 0; j < V; j++)
        {
            if (arista[u][j]!= 0 && mst[j]==false && arista[u][j] < valor[j])
            {
                padre[j]=u;
                valor[j]=arista[u][j];
            }
            
        }
        
    }
    
    cout << "Arbol de recubrimiento mínimo" << endl;
    int pesoTotal=0;
    for (int i = 1; i < V; ++i){
        pesoTotal=pesoTotal+valor[i];
        cout << padre[i] <<" --- " << i <<" = " << valor[i] << endl;
    }
    cout<<"peso total: "<<pesoTotal<<endl;
    return;
    

}



int main(){
    // int N;
    // cout<<"ingrese los vertices:"<<endl;
    // cin>>N;
    // N++;

    Grafo   g(4,false,true);
    g.insertarArista(0,1,10);
	g.insertarArista(0,2,15);
    g.insertarArista(0,3,20);
    g.insertarArista(1,2,35);
    g.insertarArista(1,3,25);
    g.insertarArista(2,3,30);

    // Grafo   g(9,true,true);
    // g.insertarArista(0,1,4);
	// g.insertarArista(0,7,8);
	// g.insertarArista(1,2,8);  
	// g.insertarArista(1,7,11);
	// g.insertarArista(2,3,7);
	// g.insertarArista(2,5,4);
	// g.insertarArista(2,8,2);
	// g.insertarArista(3,4,9);
	// g.insertarArista(3,5,14);
	// g.insertarArista(4,5,10);
	// g.insertarArista(5,6,2);
	// g.insertarArista(6,8,6);
	// g.insertarArista(6,8,6);
	// g.insertarArista(6,7,1);
	// g.insertarArista(7,8,7);


    // Grafo g(8,true,false);
    // g.insertarArista(0,2);
    // g.insertarArista(1,2);
    // g.insertarArista(1,3);
    // g.insertarArista(2,4);
    // g.insertarArista(3,6);
    // g.insertarArista(4,5);
    // g.insertarArista(4,6);
    // g.insertarArista(6,7);

    // Grafo a1(N,false,false);

    // a1.insertarArista(1,3);
    // a1.insertarArista(1,2);
    // a1.insertarArista(2,4);

    // Grafo a2(N,true,false);

    // a2.insertarArista(4,1);
    // a2.insertarArista(2,4);
    // a2.insertarArista(2,3);
    // a2.insertarArista(4,3);
    // a2.insertarArista(3,2);
    

    // Grafo a3(N,false,true);
    // a3.insertarArista(1,3,5);
    // a3.insertarArista(1,2,6);
    // a3.insertarArista(2,4,8);

    // cout<<"Grafo no dirigido: "<<endl;
    // a1.imprimir();

    // cout<<"Grafo dirigido: "<<endl;
    // a2.imprimir();

    // cout<<"Grafo ponderado: "<<endl;
    // a3.imprimir();
    
    // cout<<"matriz transitiva"<<endl;
    // a2.transitiva();
    //cout<<"peso total: "<<a1.peso()<<" bytes "<<endl;

    // cout<<"Matriz: "<<endl;
    // amp.imprimir();

    // cout<<"amplitud desde 1: "<<endl;
    // amp.amplitud(1);

    //g.imprimir();
    //g.Prim();

    //g.imprimir();

    

    return 0;
}