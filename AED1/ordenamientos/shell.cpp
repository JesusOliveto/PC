#include <stdio.h>
#include <iostream>
#include <conio.h>
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
	cout<<"orden completado"<<endl;
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
	 getch();
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
	int k,h;
	int aux;
	for(h=1;h<=n/9;h=3*h+1);
	for(;h>0;h/=3)
	{
		for(int j=h;j<n;j++)
		{
			int aux=v[j].num;
			for(k=j-h;k>=0&&aux<v[k].num;k-=h)
			{
				v[h+k].num=v[k].num;
			}
			v[k+h].num=aux;
		}
	}
	
}

void mostrar (numeros v[100], int n)
{
	cout<<"ordenados: "<<endl;
	for(int i=0;i<n;i++)
	{
		cout<<v[i].num<<" ";
	}
}
