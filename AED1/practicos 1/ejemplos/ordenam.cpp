#include <iostream>
#include <sstream>

using namespace std;

void seleccion(int* a, int n){
    for (int i = 0; i < n; i++)
    {
        int iMenor = i;
        for (int j = i+1; j < n; j++)
        {
            if (a[j] < a[iMenor]){
                iMenor = j;
            }
        }
        swap(a[i], a[iMenor]);        
    }
}

void insercion(int* a, int n){
    for (int i = 1; i < n; i++){
        int p = i;
        while(p > 0 && a[p-1] > a[p]){
            swap(a[p-1], a[p]);
            p--;    
        }
    }
}

void burbuja(int* a, int n){
    bool ordenado = false;
    while(!ordenado){
        ordenado = true;
        for (int i = 0; i < n-1; i++)
        {
            if (a[i+1] < a[i]){
                swap(a[i+1], a[i]);
                ordenado = false;
            }            
        }
    }
}


void merge(int* izq, int* der, int* a, int nIzq, int nDer, int n){
    int i = 0, j = 0, k = 0;

    while (i < nIzq && j < nDer){
        if (izq[i] < der[j]) {
            a[k] = izq[i];
            k++; 
            i++;
        }
        else
        {
            a[k] = der[j];
            k++;
            j++;
        }
    }

    while(i < nIzq) {
        a[k] = izq[i];
        k++; 
        i++;
    }

    while(j < nDer){
        a[k] = der[j];
        k++;
        j++;
    }        

}


void mergesort(int * a, int n){
    if (n < 2) return;
    int mitad = n/2;

    // Creamos los arreglos izquierdo y derecho
    int* izq = new int[mitad];
    int* der = new int[n-mitad];

    // Trasvasamos el array a a izq y der
    for (int i = 0; i < mitad; i++){izq[i] = a[i];}
    for (int i = mitad; i < n; i++){der[i-mitad] = a[i];}
     
    mergesort(izq, mitad);
    mergesort(der, n-mitad);

    merge(izq, der, a, mitad, n-mitad, n);

    delete[] izq;
    delete[] der;
}

int particion(int* a, int principio, int fin){
    int pivot = a[fin];
    int p = principio;

    for (int i = principio; i <= fin; i++)
    {
        if(a[i] < pivot){
            swap(a[i], a[p]);
            p++;
        }
    }
    swap(a[p], a[fin]);
    return p;  
}


void quicksort(int* a, int principio, int fin){
    // solo si el sub arreglo es de longitud > 1
    if(principio < fin){
        int p = particion(a, principio, fin);
        quicksort(a, principio, p-1);
        quicksort(a, p+1, fin);
    }
}
  
void mostrar(int* a, int n){
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << "\t";
    }
    cout << endl;    
}



int main(){
    int a[] = {5, 10, 2, 6, 15, 21, 12, 3, 7, 16};
    //int a[] = {12, 12, 12, 12, 12, 12, 12, 12, 12, 12};
    int n = sizeof(a)/sizeof(a[0]);

    mostrar(a, n);
    // seleccion(a, n);
    // insercion(a, n);
    // burbuja(a, n);
    // mergesort(a, n);
    quicksort(a, 0, n-1);
    mostrar(a,n);


    return 0;
}