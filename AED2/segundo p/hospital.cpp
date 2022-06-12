#include <iostream>
#include <climits>

using namespace std;


struct paciente
{
	int grav;
	string nombre;
	int dni;
};


class MaxHeap
{
	private:
		paciente *h;			//array que soporta el minheap
		int capacidad;	// tamaño del array que contiene la estructura
		int n; 			//cantidad de elementos del minheap
		int padre(int i) {return (i-1)/2;}
        int hijoI(int i) {return (2*i)+1;}
        int hijoD(int i) {return (2*i)+2;}
	public:
		MaxHeap(int);
		void Heapify(int);
		paciente obtenerMaximo();
		paciente extraerMaximo();
		void insertarclave(int,string,int);
		bool control();		
};

MaxHeap::MaxHeap(int capacidad)
{
	this->capacidad=capacidad;
	this->n=0;
	this->h=new paciente[capacidad];
}

void MaxHeap::insertarclave(int clave,string A, int B)
{
	if(n==capacidad)
	{
		cout<<"Ya no entrarn mas"<<endl;
		return;
	}
	h[this->n].grav=clave;
	h[this->n].nombre=A;
	h[this->n].dni=B;
	int i=n;
	this->n++;
	while(i!=0 and h[padre(i)].grav<h[i].grav)
	{
		swap(h[padre(i)],h[i]);
		i=padre(i);
	}
}

paciente MaxHeap::obtenerMaximo()
{
	if(this->n>0)
	{
		return this->h[0];
	}
	else
	{
		cout<<"ta vacio"<<endl;	
		
	}
}

paciente MaxHeap::extraerMaximo()
{
	if(n<=0)
	{
		cout<<"ta vacio"<<endl;	
	}
	if(n==0)
	{
		return h[--n];
	}
	paciente maximo=h[0];
	h[0]=h[n-1];
	n--;
	Heapify(0);
	
	return maximo;
}

void MaxHeap::Heapify(int i)
{
	int hi=hijoI(i);
	int hd=hijoD(i);
	int mayor=i;
	if(h[hi].grav>h[i].grav and hi<n)
	{
		mayor=hi;	
	}
	if(h[hd].grav>h[mayor].grav and hd<n)
	{
		mayor=hd;
	}
	if(mayor!=i)
	{
		swap(h[i],h[mayor]);
		Heapify(mayor);
	}
}

bool MaxHeap::control(){
    bool minheap=true;
    for (int i = 0; i < n; i++)
    {
        if (h[padre(i)].grav<h[i].grav)
        {
            minheap=false;
            cout<<"  error: "<<h[i].nombre<< "  padre: "<<h[padre(i)].nombre<<endl;
        }
        
    }
    return minheap;
}



int main()
{
	MaxHeap h1(100);
	h1.insertarclave(51,"pepe1",42260501);
	h1.insertarclave(2,"pepe2",42260502);
	h1.insertarclave(9,"pepe3",42260503);
	h1.insertarclave(14,"pepe4",42260504);
	h1.insertarclave(1,"pepe5",42260505);
	h1.insertarclave(25,"pepe6",42260506);
	bool g=h1.control();
	if(g==true)
	{
		cout<<"Es un max heap"<<endl;
	}
	
	
	for (int i = 0; i < 6; i++)
	{
		paciente p=h1.extraerMaximo();
		cout<<"----------------------------------"<<endl;
		cout<<"paciente "<<i+1<<": "<<endl;
		cout<<"nombre: "<<p.nombre<<endl;
		cout<<"dni: "<<p.dni<<endl;
		cout<<"gravedad: "<<p.grav<<endl;
		cout<<"----------------------------------"<<endl;
		
	}
	
	return 0;
}
