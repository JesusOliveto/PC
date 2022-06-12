#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>


using namespace std;




int particion(int *a, int principio, int fin){
	int pivot=a[fin];
	int p=principio;

	for (int i = principio; i < fin; i++)
	{
		if (a[i]<pivot){
			swap(a[i],a[p]);
			p++;
		}
		
	}
	swap(a[p], a[fin]);
	return p;
	
}

void quicksort (int *a, int principio, int fin){
	if(principio<fin){
		int p=particion(a,principio,fin);
		quicksort(a,principio,p-1);
		quicksort(a,p+1,fin);
	}
}


void mostrar (int *v, int n)
{
	cout<<"ordenados: "<<endl;
	// for(int i=0;i<n;i++)
	// {
	// 	cout<<"0"<<i<<" ";
	// }
	// cout<<endl;
	for(int i=0;i<n;i++)
	{
		cout<<v[i]<<" ";
	}
	cout<<endl;
}

void faltantes(int *a, int n){
	
	int x;

	for (int i = 0; i < n-1; i++)
	{
		x=1;
		while((a[i]+x)<a[i+1]){
			cout<<"valor faltante: "<<a[i]+x<<endl;
			x++;
		}
	}
		
}


void ordfrecuencia(int *a, int n){
	int f[100];
	int m[100];
	for (int i = 0; i < n; i++)
	{
		f[i]=0;
		m[i]=i;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if(a[j]==i)f[i]=f[i]+1;
		}
	}
	mostrar(a,n);
	for (int i = 0; i < n; i++)
	{
		cout<<f[i]<<"-";
	}
	cout<<endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = i+1; j < n; j++)
		{
			if(f[i]<f[j]){
				swap(f[i],f[j]);
				swap(m[i],m[j]);
			}
		}
	}
	for (int i = 0; i < n; i++) cout<<m[i]<<"-";
	cout<<endl;

	
}

int busquedabinaria(int x, int*a, int n){
	int inicio=0;
	int fin= n-1;

	while (inicio <= fin)
	{
		int medio= inicio + ((fin-inicio)/2);
		if(x==a[medio]){ 
			return medio+1;
		}
		else if (x<a[medio]){
			fin=medio-1;
		}
		else{
			inicio=medio+1;
		}
		
	}
	
	return -1;

}

int recursivaBinaria(int *a, int inicio, int fin, int x) 
{ 
   if (inicio <= fin) 
   { 
        int medio = inicio + (fin - inicio)/2; 

        if (a[medio] == x)  return medio; 
        if (a[medio] > x) return recursivaBinaria(a, inicio, medio-1, x); 
        return recursivaBinaria(a, medio+1, fin, x); 
   } 
 
   return -1; 
} 

// -----------------PARCIAL-----------------------
// -----------------PARCIAL-----------------------
// -----------------PARCIAL-----------------------

int particion2(int *a, int principio, int fin){
	int pivot=0;
	int p=principio;

	for (int i = principio; i < fin; i++)
	{
		if (a[i]>pivot){
			swap(a[i],a[p]);
			p++;
		}
		
	}
	swap(a[p], a[fin]);
	return p;
	
}
  
// void cerofin (int *a, int principio, int fin){
// 	if(principio<fin){
// 		int p=particion2(a,principio,fin);
// 		cerofin(a,principio,p-1);
// 		cerofin(a,p+1,fin);
// 	}
// }


// -----------------PARCIAL-----------------------
// -----------------PARCIAL-----------------------
// -----------------PARCIAL-----------------------

int main ()
{
	int a[10]={0,9,2,0,7,0,6,0,8,0};
	int total;

	// for (int i = 0; i < 10; i++)
	// {
	// 	a[i] = 10+i+(rand() % 9+1)+i*(rand() % 9+1);
	// }
	total=sizeof(a)/sizeof(a[0]);
	cout<<total<<endl;

	

	cout<<"Sistema de ordenamiento de registros"<<endl;
	particion2 (a,0,total-1);
	cout<<"orden completado"<<endl;
	mostrar (a,total);
	//faltantes(a,total);
	
	
	// int x=a[rand() % 9];
	// cout<<"buscado: "<<x<<endl;
	// if(busquedabinaria(x,a,total)==-1) cout<<"no se encontró el valor"<<endl;
	// else cout<<"posición: "<<busquedabinaria(x,a,total)<<endl;

	// cout<<"buscado: "<<x<<endl;
	// if(recursivaBinaria(a,0,total,x)==-1) cout<<"no se encontró el valor"<<endl;
	// else cout<<"posición: "<<recursivaBinaria(a,0,total-1,x)<<endl;

	//ordfrecuencia(a,total);

	return 0;
}



