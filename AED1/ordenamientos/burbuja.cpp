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
	int aux;
	bool ordenado=false;
	for(int i=0;i<n-1&&!ordenado;i++)
	{
		ordenado=true;
		for(int j=0;j<n-i-1;j++)
		{
			if(v[j].num>v[j+1].num)
			{
				ordenado=false;
				aux=v[j].num;
				v[j].num=v[j+1].num;
				v[j+1].num=aux;
			}
		}
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
