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
	int i,s,f,e,valori;
	for(i=1;i<n;i++)
	{
		e=v[i].num;
		s=i;
		f=(s-1)/2;
		while(s>0 && v[f].num<e)
		{
			v[s].num=v[f].num;
			s=f;
			f=(s-1)/2;
		}
		v[s].num=e;
	}
	for(i=n-1;i>0;i--)
	{
		valori=v[i].num;
		v[i].num=v[0].num;
		f=0;
		if(i==1)s=-1;else s=1;
		if(i>2 && v[2].num>v[1].num)s=2;
		while(s>=0 && valori<v[s].num)
		{
			v[f].num=v[s].num;
			f=s;
			s=2*f+1;
			if(s+1<=i-1 && v[s].num<v[s+1].num)s++;
			if(s>i-1)s=-1;
		}
		v[f].num=valori;
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
