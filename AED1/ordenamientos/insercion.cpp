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
	int aux,pos;
	
	for(int i=0;i<n;i++)
	{
		pos=i;
		aux= v[i].num;
		
		while((pos>0)&&(v[pos-1].num>aux))
		{
			v[pos].num= v[pos-1].num;
			pos--;
		}
		v[pos].num=aux;
		
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
