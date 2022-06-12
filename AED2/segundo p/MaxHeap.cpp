#include <iostream>
#include <climits>

using namespace std;

class MaxHeap
{
	private:
		int *h;			//array que soporta el minheap
		int capacidad;	// tamaño del array que contiene la estructura
		int n; 			//cantidad de elementos del minheap
		int padre(int i) {return (i-1)/2;}
        int hijoI(int i) {return (2*i)+1;}
        int hijoD(int i) {return (2*i)+2;}
		bool controlR(int);
	public:
		MaxHeap(int);
		void Heapify(int);
		int obtenerMaximo();
		int extraerMaximo();
		void insertarclave(int);
		bool control();
        bool controlR();			
};

MaxHeap::MaxHeap(int capacidad)
{
	this->capacidad=capacidad;
	this->n=0;
	this->h=new int[capacidad];
}

void MaxHeap::insertarclave(int clave)
{
	if(n==capacidad)
	{
		cout<<"Ya no entrarn mas"<<endl;
		return;
	}
	h[this->n]=clave;
	int i=n;
	this->n++;
	while(i!=0 and h[padre(i)]<h[i])
	{
		swap(h[padre(i)],h[i]);
		i=padre(i);
	}
}

int MaxHeap::obtenerMaximo()
{
	if(this->n>0)
	{
		return this->h[0];
	}
	else
	{
		return INT_MIN;
	}
}

int MaxHeap::extraerMaximo()
{
	if(n<=0)
	{
		return INT_MIN;
	}
	if(n==0)
	{
		return h[--n];
	}
	int maximo=h[0];
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
	if(h[hi]>h[i] and hi<n)
	{
		mayor=hi;	
	}
	if(h[hd]>h[mayor] and hd<n)
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
        if (h[padre(i)]<h[i])
        {
            minheap=false;
            cout<<"  error: "<<h[i]<< "  padre: "<<h[padre(i)]<<endl;
        }
        
    }
    return minheap;
}

bool MaxHeap::controlR(){
    return controlR(0);
    
}


bool MaxHeap::controlR(int i){
    if (h[i] < h[padre(i)] && controlR(i++))
        return false;
 
    return true;
    
}

int main()
{
	MaxHeap h1(100);
	h1.insertarclave(51);
	h1.insertarclave(2);
	h1.insertarclave(9);
	h1.insertarclave(14);
	h1.insertarclave(1);
	h1.insertarclave(25);
	bool g=h1.control();
	if(g==true)
	{
		cout<<"Es un max heap"<<endl;
	}
	
	cout<<h1.extraerMaximo()<<endl;
	cout<<h1.extraerMaximo()<<endl;
	cout<<h1.extraerMaximo()<<endl;
	return 0;
}
