#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

struct numeros {
		int num;
};

int generar (numeros v[100], int &n);
void ordenar (numeros v[100], int n);
void mostrar (numeros v[100], int n);



int main ()
{
	numeros v[100];
	int n;
	int total;
	cout<<"Sistema de ordenamiento de registros"<<endl;
	total=generar (v,n);
	ordenar (v,total);
	mostrar (v,total);
}

int generar (numeros v[100],int &n)
{
	int total;
	
	
	FILE *m;
 m = fopen ("numeros.dat","rb");
 if (m == NULL)
	{cout <<"Error al abrir archivo registros.dat";
	 cout << "Presione una tecla... ";
	 exit (1); // cancela el programa
	}
 else
	{
		n=0;
		numeros r;
		fread (&r, sizeof(numeros), 1, m);
		while(feof(m)==0)
		{
			v[n].num=r.num;
			n++;
			fread (&r, sizeof(numeros), 1, m);
			total++;
		}
	}
	return total;
}


void ordenar (numeros v[100], int n)
{
	int min;
	
	for(int i=0;i<n;i++)
	{
		min=i;
		for(int j=i+1;j<n;j++)
		{
			if(v[j].num<v[min].num)
			{
				min=j;
			}
		}
		swap (v[i].num,v[min].num);
	}
	cout<<"orden completado"<<endl;
}

void mostrar (numeros v[100], int n)
{
	cout<<"ordenados: "<<endl;
	for(int i=0;i<n;i++)
	{
		cout<<v[i].num<<" ";
	}
}
