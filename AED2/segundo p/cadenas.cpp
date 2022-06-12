#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <math.h>
#include <fstream>
#include <sstream>
#include <cmath>
#include <stack>

using namespace std;


int buscar(string texto, string patron){
    int n=texto.size();
    int m=patron.size();


    int i=0;
    int j=0;

    while (i < n){
        if (texto[i]==patron[j]){
            i++;
            j++;

            if (j==m){
                cout<<"concurrencia en "<< i-m<<endl;
                j=0;
                i=i-m+1;
            }
        }
        else{
            i=i-j+1;
            j=0;
        }
        
        
    }
    
    return -1;
}



void reemplazar(string ubp){
    int n=ubp.size();
    int contador[128];
    for (int i = 0; i < 128; i++)
    {
        contador[i]=0;
    }
    
    
    for (int i = 0; i < n; i++)
    {
        contador[ubp[i]]++;
        if (contador[ubp[i]]>1)
        {
            ubp[i]='_';
        }
        

    }

    cout<<ubp<<endl;
    
}


int buscarpatron(string texto, string patron){
    int n = texto.size();
    int m = patron.size();

    int i=0;
    int j=0;

    while(i < n){
        if(texto[i] == patron[j] || patron[j] == '*'){
            i++;
            j++;
            if(j == m){
                cout<<"Hay una ocurrencia en: "<<i-m<<endl;
                j = 0;
                i = i - m + 1;
            }
        }
        else{
            i = i - j + 1;
            j=0;
        }
    }

    return -1;
}

void palindromos(string texto,int largo)
{
    int l=texto.size();
    int i=0;
    int k=0;
    while (i<l-largo+1)
    {
        char cadena[largo];
        stack<char> s;
        k=i;
        cout<<"Cadena actual: ";
        for (int j=0;j<largo;j++)
        {
            cadena[j]=texto[k];
            s.push(texto[k]);
            cout<<cadena[j];
            k++;
        }
        cout<<endl;
        for (int j=0;j<largo;j++)
        {
            if (cadena[j]==s.top())
            {
                s.pop();
            }
        }
        if (s.empty()==true)
        {
            cout<<endl<<"Esta cadena es palindroma."<<endl<<endl;
        }
        else if (s.empty()==false)
        {
            cout<<endl<<"Esta cadena no es palindroma."<<endl<<endl;
        }
        i++;
    }
}

void palindromosParcial(string texto)
{
    int largo=6;
    int l=texto.size();
    int i=0;
    int k=0;
    while (i<l-largo+1)
    {
        char cadena[largo];
        stack<char> s;
        k=i;
        for (int j=0;j<largo;j++)
        {
            cadena[j]=texto[k];
            s.push(texto[k]);
            k++;
        }
        for (int j=0;j<largo;j++)
        {
            if (cadena[j]==s.top())
            {
                s.pop();
            }
        }
        if (s.empty()==true)
        {
            cout<<endl<<"Encontrada en la posicion "<<i<<endl;
            return;
        }
        
        i++;
    }
    cout<<"no posee palindromos de largo 6"<<endl;
}


int main(){
    // string texto ="BAABBAABBAABBAABBAABBAAB";
    // string patron ="BAAB";
    // buscar(texto,patron);
    
    // string ubp = "UNIVERSIDAD BLAS PASCAL";
    // reemplazar(ubp);
    // cout<<ubp<<endl;

    // string texto2 = "lo masa sobre la mesa";
    // string patron2 = "m*sa";
    // buscarpatron(texto2,patron2);

    // string texto3 = "rallaradgtaddagtadbbbgaattbaadtattabsugus";
    // //string texto = "dabale arroz a la zorra el abad";
    // int largo=0;
    // while (largo>6 or largo<3)
    // {
    //     cout<<"Ingrese el largo del palindromo: ";
    //     cin>>largo;
    // }
    // palindromos(texto3,largo);

    string texto="ABSAATRAGEEGATTLASSIAANHKTR";
    cout<<"cadena: "<<texto<<endl<<"buscando palindromos..."<<endl;
    palindromosParcial(texto);
    
    
    return 0;
}