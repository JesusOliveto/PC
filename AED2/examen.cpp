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

const int INF=999999;

using namespace std;

struct Ciudad
{
    int id;
    string nombre;
    int importancia;
};



class Mapa{
    private:
        Ciudad* localidad;
        int** arista;
        int V;
        bool dirigido;
        bool ponderado;

    public:
        Mapa(int,bool,bool);
        ~Mapa();
        void insertarCiudades();
        void insertarCiudad(int, int, string);
        void cargaAristas(int);
        void insertarArista(int,int,int);
        void mostrar(int,int);
        void imprimir();
        void imprimirCiudades();
        int peso();
        void Dijkstra (int);
        int DistanciaMinima(int*,bool*);
        void FloydWarshall(int, int);

};

Mapa::Mapa(int vertices, bool d,bool p){
    ponderado=p;
    dirigido=d;
    V=vertices;
    
    localidad = new Ciudad [V];
    for(int i = 0; i< V; i++){
        localidad[i].id = 0;
        localidad[i].nombre="NULL";
        localidad[i].importancia=0;
    }



    arista = new int* [V];
    for(int i=0; i<V; i++) 
        arista[i] = new int[V];

    if (ponderado)
    {
       for (int i = 0; i < V; i++)
     {
        for (int j = 0; j < V; j++)
         {
             arista[i][j]=-1;
         }
        
        }
    }
    
    
}

Mapa::~Mapa(){
    
      for(int i = 0; i < V; i++)
            delete[] arista[i];
    delete[] arista;
}

void Mapa::insertarCiudades(){
    int input;
    string texto;

    for (int i = 0; i < V; i++)
    {
        cout<<"ID: "<<i<<endl;
        localidad[i].id=i;
        cout<<"inserte el nombre de la ciudad: "<<endl;
        cin>>texto;
        localidad[i].nombre=texto;
        cout<<"inserte la importancia turistica de la ciudad (valor entre 1 y 10): "<<endl;
        cin>>input;
        while (input<1||input>10)
        {
            cout<<"importancia no valida, reingrese el dato"<<endl;
            cin>>input;
        }
        
        localidad[i].importancia=input;
    }
}

void Mapa::insertarCiudad(int num,int input, string texto){
   
        localidad[num].id=num;
        localidad[num].nombre=texto;
        localidad[num].importancia=input;
}


void Mapa::cargaAristas(int nodos)
{
    int i=0;
	int opcion=1;
    cout<<"-----------------------------------------------------------"<<endl;
	cout<<"Puede ingresar "<<(nodos*(nodos-1)/2)<<" caminos."<<endl;
	cout<<"Las ID de las ciudades van del 0 al "<<nodos-1<<endl;
    while(((nodos*(nodos-1))/2)>i and opcion==1)
	{
		int origen=0;
		int destino=0;
		int peso=0;
		cout<<"Camino "<<i<<endl;
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
			opcion=1;
		}
		else if (arista[origen][destino]!=-1)
        {
            cout<<"Estas ciudades ya tienen un camino."<<endl;
			opcion=1; 
        }
        else if (arista[origen][destino]==-1)
        {
            insertarArista(origen,destino,peso);
            i++;
			cout<<"Desea ingresar otra ruta? (1=Si, 0=No)"<<endl;
			cout<<"Opcion: ";
			cin>>opcion;
			while (opcion!=1 and opcion!=0)
			{
				cout<<"Ingrese una opcion valida: ";
				cin>>opcion;
			}
        }
	}
    cout<<"-----------------------------------------------------------"<<endl;
}

void Mapa::insertarArista(int a, int b, int peso){
    if (dirigido==true && ponderado==true)
    {
        if(a >=0 && a <V && b>= 0 && b <V)
        arista[a][b]=peso;
    }
    else if (ponderado==true)
    {
        if(a >=0 && a <V && b>= 0 && b <V){
        arista[a][b]=peso; arista[b][a]=peso;
        }
    }

}



void Mapa::mostrar(int a, int b){
    cout<<"["<<arista[a][b]<<"]   ";
}

void Mapa::imprimir(){
    cout<<"-----------------------------------------------------------"<<endl;
    cout<<"MAPA DE RUTAS"<<endl;
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
             cout<<"["<<arista[i][j]<<"]   ";
        }

        cout<<endl;
    }
}

void Mapa::imprimirCiudades(){
    cout<<"-----------------------------------------------------------"<<endl;
    cout<<"LISTA DE CIUDADES"<<endl;
    for (int i = 0; i < V; i++)
    {
    cout<<"-----------------------------------------------------------"<<endl;
    cout<<"id: "<<localidad[i].id<<endl;
    cout<<"Nombre: "<<localidad[i].nombre<<endl;
    cout<<"importancia turística: "<<localidad[i].importancia<<endl;
    cout<<"-----------------------------------------------------------"<<endl;
    }
}



int Mapa::peso(){
    int r=0;

    r=V*V*(sizeof(int))+V*8;
    return r;
}





void Mapa::FloydWarshall(int origen, int destino){
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

    cout<<"-----------------------------------------------------------"<<endl;
    cout << "Ciudad de origen: " << endl;
    cout<<"id: "<<localidad[origen].id<<endl;
    cout<<"Nombre: "<<localidad[origen].nombre<<endl;
    cout<<"importancia turística: "<<localidad[origen].importancia<<endl;
    cout<<"-----------------------------------------------------------"<<endl;
	 cout << "Ciudad destino: " << endl;
    cout<<"id: "<<localidad[destino].id<<endl;
    cout<<"Nombre: "<<localidad[destino].nombre<<endl;
    cout<<"importancia turística: "<<localidad[destino].importancia<<endl;
    cout<<"-----------------------------------------------------------"<<endl;
    cout<<"DISTANCIA ENTRE AMBAS: "<<sp[origen][destino]<<" Km."<<endl;
    cout<<"-----------------------------------------------------------"<<endl;
    cout<<"distancias entre todas las ciudades: "<<endl;
     for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
             cout<<"["<<sp[i][j]<<"]   ";

        }
        cout<<endl;
    }
    cout<<"-----------------------------------------------------------"<<endl;
	
}




int main() 
{
    int nodos=0;
	int origen=0;
    int destino=0;
	int opcion=0;
	cout<<"UBP - FINAL AED2"<<endl;
	cout<<"Jesus Oliveto"<<endl;
	cout<<"1) Ingresar un mapa"<<endl;
	cout<<"2) Ver un ejemplo con distancias de 1 digito"<<endl;
    cout<<"3) Ver un ejemplo con distancias mayores"<<endl;
	cout<<"Opcion: ";
	cin>>opcion;
	if (opcion==1)
	{
		cout<<"Ingrese la cantidad de ciudades de su mapa: ";
		cin>>nodos;
		while(nodos<=0)
		{
			cout<<"Un mapa no puede tener una cantidad de ciudades negativa, ingrese una cantidad valida: ";
			cin>>nodos;
		}
		Mapa g(nodos, false, true);
        g.insertarCiudades();
		g.cargaAristas(nodos);
        g.imprimirCiudades();
        g.imprimir(); 
		cout<<"Ingrese la ciudad de origen: ";
		cin>>origen;
         while (origen<0||origen>=nodos)
        {
            cout<<"origen no valido, reingrese el dato"<<endl;
            cin>>origen;
        }
        cout<<"Ingrece la ciudad destino";
        cin>>destino;
         while (destino<0||destino>=nodos)
        {
            cout<<"destino no valido, reingrese el dato"<<endl;
            cin>>destino;
        }
		g.FloydWarshall(origen,destino);
	}
	else if (opcion==2)
	{
		cout<<"Mapa de 6 ciudades(pesos de 1 digito)."<<endl;
		Mapa e(6, false, true);
        e.insertarCiudad(0,8,"Jesus Maria");
        e.insertarCiudad(1,6,"Colonia Caroya");
        e.insertarCiudad(2,5,"Cordoba");
        e.insertarCiudad(3,4,"Agua de Oro");
        e.insertarCiudad(4,6,"Sinsacate");
        e.insertarCiudad(5,3,"La Granja");
		e.insertarArista(0,1,3);
		e.insertarArista(0,4,5);
		e.insertarArista(0,3,2);
		e.insertarArista(1,2,2);
		e.insertarArista(1,4,3);
		e.insertarArista(2,4,5);
		e.insertarArista(2,5,1);
		e.insertarArista(3,4,6);
		e.insertarArista(4,5,3);
        e.imprimirCiudades();
		e.imprimir(); 
		cout<<"Ingrese la ciudad de origen: ";
		cin>>origen;
         while (origen<0||origen>=6)
        {
            cout<<"origen no valido, reingrese el dato"<<endl;
            cin>>origen;
        }
        cout<<"Ingrece la ciudad destino";
        cin>>destino;
         while (destino<0||destino>=6)
        {
            cout<<"destino no valido, reingrese el dato"<<endl;
            cin>>destino;
        }
		e.FloydWarshall(origen,destino);
	}
    else if (opcion==3)
	{
		cout<<"Mapa de 5 ciudades (pesos grandes)."<<endl;
		Mapa e(5, false, true);
        e.insertarCiudad(0,8,"Cordoba");
        e.insertarCiudad(1,6,"Rio Primero");
        e.insertarCiudad(2,5,"Rio Segundo");
        e.insertarCiudad(3,4,"Rio Tercero");
        e.insertarCiudad(4,6,"Rio Cuarto");
		e.insertarArista(0,1,124);
		e.insertarArista(0,3,156);
		e.insertarArista(1,2,201);
		e.insertarArista(1,4,97);
		e.insertarArista(3,4,61);
		e.insertarArista(4,5,199);
        e.imprimirCiudades();
		e.imprimir(); 
		cout<<"Ingrese la ciudad de origen: ";
		cin>>origen;
         while (origen<0||origen>=5)
        {
            cout<<"origen no valido, reingrese el dato"<<endl;
            cin>>origen;
        }
        cout<<"Ingrece la ciudad destino";
        cin>>destino;
         while (destino<0||destino>=5)
        {
            cout<<"destino no valido, reingrese el dato"<<endl;
            cin>>destino;
        }
		e.FloydWarshall(origen,destino);
	}
	else
	{
		cout<<"No ingreso una opcion valida."<<endl;
	}
	return 0;
} 