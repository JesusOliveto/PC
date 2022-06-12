#include <iostream>
#include <climits>

using namespace std;

class MinHeap{
    private:
        int *h;         // Array que soporta el minheap
        int capacidad;  // Tamaño del array que contiene la estructura
        int n;          // Cantidad de elementos del min heap
        int padre(int i) {return (i-1)/2;}
        int hijoI(int i) {return (2*i)+1;}
        int hijoD(int i) {return (2*i)+2;}
        bool controlR(int);
    
    public: 
        MinHeap(int);
        void insertarClave(int);
        int obtenerMinimo();
        int extraerMinimo();
        void heapify(int);
        void mostrar();
        bool control();
        bool controlR();
        void eliminar(int);
        int buscarI(int);

};

MinHeap::MinHeap(int capacidad){
    this->capacidad = capacidad;
    this->n = 0;
    this->h = new int[capacidad];

}

void MinHeap::insertarClave(int clave){

    if (n == capacidad){
        cout << "Se ha alcanzado la capacidad máxima" << endl;
        return;
    }

    // Insertamos al final del array
    h[this->n] = clave;
    int i = n;  // i es una variable auxiliar
    this->n++;   

    // Asegurar la definición del minheap
    while (i != 0 &&  h[padre(i)] > h[i]){
        swap(h[padre(i)], h[i]);        // Si el padre es mayor que el elemento entonces los intercambio
        i = padre(i);                   // Me muevo hacia la posición del padre
    }

}

int MinHeap::obtenerMinimo(){
    if (this->n > 0)
        return this->h[0];
    else
        return INT_MIN;
}

int MinHeap::extraerMinimo(){

    if (n <= 0)
        return INT_MIN;
    if (n == 1)
        return h[--n]; 

    int minimo = h[0];
    h[0] = h[n-1];
    n--;

    // Hundir el elemento que quedó en la raiz hacia su posición correcta
    heapify(0);
    

    return minimo;

}


// Heapify "hunde" el elemento i hasta su posición correcta
void MinHeap::heapify(int i){
    int hi = hijoI(i);
    int hd = hijoD(i);
    int menor = i;
    if (h[hi] < h[i] && hi < n)
        menor = hi;
    if (h[hd] < h[menor] && hd < n)
        menor = hd;
    if (menor != i){
        swap(h[i], h[menor]);
        heapify(menor);
    }

}


void MinHeap::mostrar(){
	
	for(int i = 0; i < n; i++){
		cout << h[i] << " "; 
	}
	cout << endl;

    // for (int i = 0; i < n; i++)
    // {
    //     cout<<"h[i]: "<<h[i]<< "  padre: "<<h[padre(i)]<<"  hijo der: "<<h[hijoD(i)]<<"  hijo izq: "<<h[hijoI(i)] <<endl;
    // }
    
}

bool MinHeap::control(){
    bool minheap=true;
    for (int i = 0; i < n; i++)
    {
        if (h[padre(i)]>h[i])
        {
            minheap=false;
            cout<<"  error: "<<h[i]<< "  padre: "<<h[padre(i)]<<endl;
        }
        
    }
    return minheap;
}

bool MinHeap::controlR(){
    return controlR(0);
    
}


bool MinHeap::controlR(int i){
    if (h[i] > h[padre(i)] && controlR(i++))
        return false;
 
    return true;
    
}


int MinHeap::buscarI(int clave){

    for (int i = 0; i < n; i++)
    {
        if (h[i]==clave)
        {
            return i;
        }
        
    }
    
    return -1;
}


void MinHeap::eliminar(int clave){

    int i=buscarI(clave);

    h[i]=INT_MIN;
    
    while (i != 0 &&  h[padre(i)] > h[i]){
        swap(h[padre(i)], h[i]);        // Si el padre es mayor que el elemento entonces los intercambio
        i = padre(i);                   // Me muevo hacia la posición del padre
    }
    
    extraerMinimo();

}


int main(){

    MinHeap h1(100);

    h1.insertarClave(51);
    h1.insertarClave(3);
    h1.insertarClave(9);
    h1.insertarClave(14);
    h1.insertarClave(2);
    h1.insertarClave(25);

    
    // h1.mostrar();
    // h1.eliminar(14);
    // h1.mostrar();

    
    cout<<"Es minheap? ";
    h1.control() ? cout<<"si"<<endl : cout<<"no"<<endl;
    h1.mostrar();
    
    

    // cout << endl << "Menor elemento es: " << h1.extraerMinimo() << endl;
    // cout << endl << "Menor elemento es: " << h1.extraerMinimo() << endl;
    // cout << endl << "Menor elemento es: " << h1.extraerMinimo() << endl;
    // cout << endl << "Menor elemento es: " << h1.extraerMinimo() << endl;
    // cout << endl << "Menor elemento es: " << h1.extraerMinimo() << endl;
    // cout << endl << "Menor elemento es: " << h1.extraerMinimo() << endl;
    // cout << endl << "Menor elemento es: " << h1.extraerMinimo() << endl;
    // cout << endl << "Menor elemento es: " << h1.extraerMinimo() << endl;
    // cout << endl << "Menor elemento es: " << h1.extraerMinimo() << endl;

    return 0;
}