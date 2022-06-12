#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <ctime>
#include <math.h>
#include <fstream>
#include <sstream>
#include <cmath>
#include <climits>
#include <queue>
#include <stack>
const int infinito=999999;
using namespace std;
class Grafo
{
    private:
        int v;
        int** m;
        bool dirigido;
        bool ponderado;
    public:
        Grafo(int,bool,bool);
        ~Grafo();
        void Agregar(int,int,int);
        void Agregar(int,int);
        void Dijkstra(int); //Llenamos con -1
        int DistanciaMinima(int*,bool*);
        void Mostrar();
        void Matematica(int);
};
Grafo::Grafo(int v, bool dirigido, bool ponderado)
{
	this->v=v;
	this->dirigido=dirigido;
	this->ponderado=ponderado;
	this->m=new int*[v];
	for (int i=0;i<v;i++)
	{
		m[i]=new int[v];
		for (int j=0;j<v;j++)
		{
			if (!ponderado)
			{
				m[i][j]=0;	
			}
			else
			{
				//m[i][j]=infinito;
				m[i][j]=-1;
			}
		}		
	}
}
Grafo::~Grafo()
{
	for(int i=0;i<v;i++)
	{
		delete[] m[i];
	}
	delete[] m;
}
void Grafo::Agregar(int o,int d,int a)
{
	if (o>=0 and o<v and d>=0 and d<v)
	{
		if (dirigido)
		{
			m[o][d]=a;
		}
		if (!dirigido)
		{
			m[o][d]=a;
			m[d][o]=a;
		}
	}
	else
	{
		cout<<"ERROR con los vertices de la matriz"<<endl;
	}
}
void Grafo::Agregar(int o, int d)
{
	if (o>=0 and o<v and d>=0 and d<v)
	{
		if (dirigido)
		{
			m[o][d]=1;
		}
		if (!dirigido)
		{
			m[o][d]=1;
			m[d][o]=1;
		}
	}
	else
	{
		cout<<"ERROR con los vertices de la matriz"<<endl;
	}
}
void Grafo::Dijkstra(int origen)
{
	int* distancia=new int[v];
	bool* spt=new bool[v];
	int* padre=new int[v];
	for (int i=0;i<v;i++)
	{
		distancia[i]=infinito;
		spt[i]=false;
		padre[i]=0;
	}
	distancia[origen]=0;
	padre[origen]=origen;
	for (int i=0;i<v-1;i++)
	{
		int d=DistanciaMinima(distancia,spt);
		spt[d]=true;
		for (int j=0;j<v;j++)
		{
			if (m[d][j]!=-1 and !spt[j] and distancia[d]+m[d][j]<distancia[j]) 
			{
				distancia[j]=distancia[d]+m[d][j];
				padre[j]=d; 
			}      
		}     
	}
	cout<<"Algoritmo de Dijkstra"<<endl;
	for (int i=0;i<v;i++)
	{
		if (padre[i]!=i)
		{
			cout<<i<<": Distancia: "<<distancia[i]<<" Padre: "<<padre[i]<<endl;
		}	
	}
	cout<<"Aristas de arbol de Dijkstra"<<endl;  
	for (int i = 0; i < v; i++)     
	{                
		if(padre[i]!=i)
		{
			cout<<padre[i]<<"---"<<i<<endl;
		}	     
	}
	delete []distancia;
	delete []spt;
	delete []padre;
}
int Grafo::DistanciaMinima(int* distancia, bool* spt)
{
	int distanciaMinima=infinito;
	int indiceDistanciaMinima=0;
	for (int i=0;i<v;i++)
	{
		if (spt[i]==false and distancia[i]<=distanciaMinima)
		{
			distanciaMinima=distancia[i];
			indiceDistanciaMinima=i;
		}
	}
	return indiceDistanciaMinima;
}
void Grafo::Mostrar()
{
	cout<<"Matriz de Adyacencia"<<endl;
	for (int i=0;i<v;i++)
	{
		for (int j=0;j<v;j++)
		{
			if (m[i][j] == infinito or m[i][j]==-1)
			{
				cout<<"-"<<"\t";
			}	
			else
			{
				cout<<m[i][j]<<"\t";
			}
		}
		cout<<endl;
	}
}
void Grafo::Matematica(int nodos)
{
    int i=0;
	int opcion=1;
	cout<<"Puede ingresar "<<(nodos*(nodos-1)/2)<<" aristas."<<endl;
	cout<<"Los nodos van desde el 0 hasta el "<<nodos-1<<endl;
	getch();
    while(((nodos*(nodos-1))/2)>i and opcion==1)
	{
		system("CLS");
		int origen=0;
		int destino=0;
		int peso=0;
		cout<<"Arista "<<i<<endl;
        cout<<"Introduzca origen: ";
        cin>>origen;
        while(origen>nodos-1 or origen<0)
        {
            cout<<"Origen no valido, ingrese otro: ";
            cin>>origen;
        }
        cout<<"Introduzca destino: ";
        cin>>destino;
        while(destino>nodos-1 or destino<0)
        {
            cout<<"Destino no valido, ingrese otro: ";
            cin>>destino;
        }
        cout<<"Introduzca peso: ";
        cin>>peso;
        while(peso<0)
        {
            cout<<"Peso no valido, ingrese otro: ";
            cin>>peso;
        }
        if (origen==destino)
		{
			cout<<"No se admiten bucles."<<endl;
			opcion==1;
		}
		else if (m[origen][destino]!=-1)
        {
            cout<<"Estos nodos ya tienen una arista."<<endl;
			opcion==1; 
        }
        else if (m[origen][destino]==-1)
        {
            Agregar(origen,destino,peso);
            i++;
			cout<<"Desea ingresar otra arista? (1=Si, 0=No)"<<endl;
			cout<<"Opcion: ";
			cin>>opcion;
			while (opcion!=1 and opcion!=0)
			{
				cout<<"Ingrese una opcion valida: ";
				cin>>opcion;
			}
        }
	}
}
int main() 
{
    int nodos=0;
	int origen=0;
	int opcion=0;
	cout<<"UBP - MATEMATICA DISCRETA II 2020"<<endl;
	cout<<"Integrantes: Franco Geremia, Facundo Facello y Jesus Olariaga Oliveto"<<endl;
	cout<<"ADVERTENCIA, ESTE PROGRAMA FUNCIONA UNICAMENTE CON NUMEROS NATURALES, SI INGRESA UNA LETRA SE ROMPERA."<<endl;
	cout<<"1) Ingresar un grafo"<<endl;
	cout<<"2) Ver un ejemplo"<<endl;
	cout<<"Opcion: ";
	cin>>opcion;
	if (opcion==1)
	{
		cout<<"Ingrese la cantidad de nodos de su grafo: ";
		cin>>nodos;
		while(nodos<=0)
		{
			cout<<"Un grafo no puede tener una cantidad de nodos negativa, ingrese una cantidad valida: ";
			cin>>nodos;
		}
		Grafo g(nodos, false, true);
		g.Matematica(nodos);
		system("CLS"); //ROMPE COMO LO MUESTRA EL VISUAL, COMENTAR PARA VERLO BIEN
		g.Mostrar(); 
		cout<<"Ingrese el nodo de origen para Dijkstra: ";
		cin>>origen;
		g.Dijkstra(origen);
		getch();
	}
	else if (opcion==2)
	{
		cout<<"Grafo de 6 nodos."<<endl;
		Grafo e(6, false, true);
		e.Agregar(0,1,10);
		e.Agregar(0,4,8);
		e.Agregar(0,3,2);
		e.Agregar(1,2,2);
		e.Agregar(1,4,3);
		e.Agregar(2,4,5);
		e.Agregar(2,5,1);
		e.Agregar(3,4,6);
		e.Agregar(4,5,3);
		system("CLS"); //ROMPE COMO LO MUESTRA EL VISUAL, COMENTAR PARA VERLO BIEN
		e.Mostrar(); 
		cout<<"Origen para algoritmo de Dijkstra = 0."<<endl;
		e.Dijkstra(0);
		getch();
	}
	else
	{
		cout<<"No ingreso una opcion valida."<<endl;
	}
	return 0;
} 