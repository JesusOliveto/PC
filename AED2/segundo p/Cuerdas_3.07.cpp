#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <math.h>
#include <fstream>
#include <sstream>
#include <cmath>
#include <climits>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;
const int INFINITO = 99;//INT_MAX

class grafo
{
	private:
		int v;
		int** a;
		bool dirigido;
		bool ponderado;
		void Union(int* padre, int x, int y);
		int Find(int* padre, int i);
	public:
		grafo(int,bool,bool);
		~grafo();
		void agregarArista(int,int,int);
		void mostrar();
		void Dijstra(int);
        int  DistanciaMinima(int*,bool*);
};

grafo::grafo(int v,bool dirigido,bool ponderado)
{
	this->v=v;
	this->dirigido=dirigido;
	this->ponderado=ponderado;
	a=new int*[v];
	for(int i=0;i<v;i++)
	{
		a[i]=new int[v];
		if(!ponderado)
		{
			for(int j=0;j<v;j++)
			{
				a[i][j]=0;
			}
		}
		else
		{
			for(int j=0;j<v;j++)
			{
				a[i][j]=INFINITO;
			}
		}	
	}
}

grafo::~grafo()
{
	for(int i=0;i<v;i++)
	{
		delete[] a[i];
	}
	delete[] a;
}

void grafo::agregarArista(int origen,int destino,int num)
{
	if(origen>=0 && origen < v && destino >=0 && destino<v)
	{
		
		if(!dirigido && !ponderado)
		{
			a[destino][origen]=1;
			a[origen][destino]=1;
		}
		else if(dirigido && !ponderado)
		{
			a[origen][destino]=1;
		}
		else if(!dirigido && ponderado)
		{
			a[origen][destino]=num;
			a[destino][origen]=num;
		}
		else if(dirigido && ponderado)
		{
			a[origen][destino]=num;
		}	
	}
}

void grafo::mostrar()
{
	cout<<"Matriz normal: "<<endl;
	for (int i = 0; i < v; i++)
	{
		for (int j = 0; j < v; j++)
		cout << a[i][j] << "\t";
		cout << endl;
	}
}

int grafo::DistanciaMinima(int* distancia,bool* spt)
{
	int distanciaMinima=INFINITO;
	int indiceDM=0;
	for(int i=0;i<v;i++)
	{
		if(spt[i]==false && distancia[i]<=distanciaMinima)
		{
			distanciaMinima=distancia[i];
			indiceDM=i;
		}
	}
	return indiceDM;
}

void grafo::Dijstra(int origen)
{
	int distancia[v];
	bool spt[v];
	int padre[v]; 
	for(int i=0;i<v;i++)
	{
		distancia[i]=INFINITO;
		spt[i]=false;
		padre[i]=0;
	}
	distancia[origen]=0;
	padre[origen]=-1;
	for(int i=0;i<v-1;i++)//seleccionar el vertce con menos peso y agregarlo al mst
	{
		int u=DistanciaMinima(distancia,spt);
		spt[u]=true;
		for(int j=0;j<v;j++)
		{
			if(!spt[j] && a[u][j] && distancia[u]!=INFINITO && distancia[j]>distancia[u]+a[u][j])
			{
				distancia[j]=distancia[u]+a[u][j];
				padre[j]=u;
			}
		}	
	}
	cout<<"Dijstra: "<<endl;
	cout<<"Vertice\tDsitancia\tPadre"<<endl;
    int  costo=0;
	for(int i=0;i<v;i++)
	{
		cout<<"\n"<<i<<" \t"<<distancia[i]<<" \t"<<padre[i];
        costo=costo+distancia[i];
	}
    cout<<endl<<"Costo: "<<costo-distancia[1]<<endl;
	cout<<endl;
}



int main()
{
    int  n=0;
    cout<<"cuantos tramos de soga habra presente?"<<endl;
    cin>>n;
    while (n>10 or n<2)
    {
        cout<<"Introduzca un numero valido (entre 2 y 10)"<<endl;
        cin>>n;
    }
    grafo g(n+1,false,true);//cantidad de sogas/dirigido/ponderado
    int a=0;
    int b=0;
    int c=1;
    int ord[n];
    for(int i=0;i<n;i++)//de ejemplo utilice 2,4,3,6. deberia dar costo=29
    {
        cout<<"El valor del tramo "<<i<<" de soga:"<<endl;
        cin>>a;
        ord[i]=a;
    }
    sort(ord,ord+n);
    for (int i = 0; i < n; i++)
    {
        g.agregarArista(b,c,ord[i]);
        b++;
        c++;
    }
	g.mostrar();
	cout<<endl;
	g.Dijstra(0);
}
