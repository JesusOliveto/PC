#include <fstream>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

int main()
{
	int x;
	cout<<"ONICHAN DAISKIIIIII BIENVENIDO AL MENU DE APLICACIONES!!!!!!!!! UwU\n\n Vamos a ejecutar un programa! OwO me dices cual? *w*\n"<<endl;
	cout<<"           |`-.._____..-'|"<<endl;
	cout<<"           :  > .  ,  <  :"<<endl;
	cout<<"           `./ __`' __ \,'"<<endl;
	cout<<"            | (|_) (|_) |"<<endl;
	cout<<"            ; _  .  __  :"<<endl;
	cout<<"            `.,' - `-. ,'"<<endl;
	cout<<"              `, `_  .'"<<endl;
	cout<<"              /       \\ "<<endl;
	cout<<"             /         :"<<endl;
	cout<<"            :          |_"<<endl;
	cout<<"           ,|  .    .  | \\ "<<endl;
	cout<<"          |  \   :`-;  ;  |"<<endl;
	cout<<"          :   :  | /  /   ;"<<endl;
	cout<<"           :-.'  ;'  / _,'`------."<<endl;
	cout<<"           `'`''-`'''-'-''--.---  )"<<endl;
	cout<<"                        SSt `----'"<<endl;
	
	do
	{
	cout<<"Te dire la lista de ejercicios Oniichan :3"<<endl;
	cout<<"1 para cargar los registros con numeros del 100 al 1 n.n"<<endl;
	cout<<"2 para mostrar lo que tienes guardado OwO"<<endl;
	cout<<"3 para ejecutar ordenamiento burbuja UwU"<<endl;
	cout<<"4 para ejecutar ordenamiento por seleccion directa *w*"<<endl;
	cout<<"5 para ejecutar ordenamiento por insercion directa :O"<<endl;
	cout<<"6 para ejecutar ordenamiento por quicksort"<<endl;
	cout<<"7 para ejecutar ordenamiento por monticulo"<<endl;
	cout<<"8 para ejecutar ordenamiento de shell"<<endl;
	cout<<"9 para salir UnU"<<endl;
	cout<<"Ingresa aqui el numero de programa que quieras reproducir UwU \n Siiii!! Aquiiii ---->";
	cin>>x;
	switch(x)
	{
	case 1:
		system("cls");
		cout<<"Elegiste Cargar!! :3 espera a que se ejecute UwU"<<endl;
		system("C:\\Users\\Usuario\\Desktop\\UNIVERSIDAD\\PP\\codigos\\ordenamientos\\carga.exe");
		break;
	case 2:
		system("cls");
		cout<<"Elegiste Mostrar tu archivo guardado!! :3 espera a que se ejecute UwU"<<endl;
		system("C:\\Users\\Usuario\\Desktop\\UNIVERSIDAD\\PP\\codigos\\ordenamientos\\mostrar.exe");
		break;
	case 3:
		system("cls");
		cout<<"Elegiste ordenamiento burbuja!! :3 espera a que se ejecute UwU"<<endl;
		system("C:\\Users\\Usuario\\Desktop\\UNIVERSIDAD\\PP\\codigos\\ordenamientos\\burbuja.exe");
		break;
	case 4:
		system("cls");
		cout<<"Elegiste ordenamiento por seleccion directa!! :3 espera a que se ejecute UwU"<<endl;
		system("C:\\Users\\Usuario\\Desktop\\UNIVERSIDAD\\PP\\codigos\\ordenamientos\\seleccion.exe");
		break;
	case 5:
		system("cls");
		cout<<"Elegiste ordenamiento por insercion directa!! :3 espera a que se ejecute UwU"<<endl;
		system("C:\\Users\\Usuario\\Desktop\\UNIVERSIDAD\\PP\\codigos\\ordenamientos\\insercion.exe");
		break;
	case 6:
		system("cls");
		cout<<"Elegiste ordenamiento por quicksort!! :3 espera a que se ejecute UwU"<<endl;
		system("C:\\Users\\Usuario\\Desktop\\UNIVERSIDAD\\PP\\codigos\\ordenamientos\\quicksort.exe");
		break;
	case 7:
		system("cls");
		cout<<"Elegiste ordenamiento por monticulo!! :3 espera a que se ejecute UwU"<<endl;
		system("C:\\Users\\Usuario\\Desktop\\UNIVERSIDAD\\PP\\codigos\\ordenamientos\\monticulo.exe");
		break;
	case 8:
		system("cls");
		cout<<"Elegiste ordenamiento de shell!! :3 espera a que se ejecute UwU"<<endl;
		system("C:\\Users\\Usuario\\Desktop\\UNIVERSIDAD\\PP\\codigos\\ordenamientos\\shell.exe");
		break;
	case 9: ;
	}
	}while (x!=9);
	
}

