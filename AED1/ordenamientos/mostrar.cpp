#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

struct numeros {
		int num;
};


int main()
{
	numeros v[100];
	int n;
	cout<<"Sistema de Muestra de registros"<<endl;
	
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
			cout<<r.num<<" ";
		
			n++;
			fread (&r, sizeof(numeros), 1, m);
		}
		
	}
	
		
}


