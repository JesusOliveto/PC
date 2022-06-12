# include<iostream>

using namespace std;


void mostrar(int* a, int n){
	
	for(int i = 0; i < n; i++){
		cout << a[i] << " "; 
	}
	cout << endl;
}

void heapify(int* a, int n, int i){
    int menor = i;
    int izq = 2 * i + 1; 
    int der = 2 * i + 2;  
  
    if (izq < n && a[izq] < a[menor]) 
        menor = izq; 
  
    if (der < n && a[der] < a[menor]) 
        menor = der; 
  
    if (menor != i) { 
        swap(a[i], a[menor]); 
        heapify(a, n, menor); 
    } 	
}

void heapSort(int* a, int n){
	for (int i = n/2-1; i >= 0 ; i--){
		heapify(a, n, i);
	}

	for (int i = n-1; i >= 0 ; i--){
		swap(a[0], a[i]);
		heapify(a, i, 0);
	}

}

int main(){
	int a[] = {21,12,4,7,32,2,18,99,40,5,8};
	int n = sizeof(a)/sizeof(a[0]);

	mostrar(a,n);
	heapSort(a,n);
	mostrar(a,n);
}