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
	for(int i=0;i<n;i++)
	{
		cout<<v[i]<<" ";
	}
	cout<<endl;
}

// void faltantes(int *a, int n){
	
// 	int x;

// 	for (int i = 0; i < n; i++)
// 	{
// 		x=1;
// 		while(a[i]+x<a[i+1]){
// 			cout<<"valor faltante: "<<a[i]+x<<endl;
// 			x++;
// 		}
// 	}
		
// }








int main ()
{
	int a[10];
	int total;

	for (int i = 0; i < 10; i++)
	{
		a[i] = i+(rand() % 9+1)+i*(rand() % 9+1);
	}
	total=sizeof(a)/sizeof(a[0]);
	cout<<total<<endl;
	cout<<"Sistema de ordenamiento de registros"<<endl;
	quicksort (a,0,total-1);
	cout<<"orden completado"<<endl;
	mostrar (a,total);
	// faltantes(a,total);

	
	return 0;
}



