#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

struct numeros {
		int num;
};

int main ()
{
 FILE *m;
 cout<<"Programa de carga "<<endl;
 m = fopen ("numeros.dat" , "wb");
 if (m == NULL) {
		  cout << "Error en la apertura del archivo";
		  cout << "Presione una tecla... ";
		  exit (1);
		}
    else
     {
       numeros r;
       
       for(int i=100;i>0;i--)
       {
       	r.num=i;
       	fwrite (&r, sizeof (numeros), 1, m);
	   }
     }
     cout<<"registro escrito"<<endl;
 fclose(m);
}

