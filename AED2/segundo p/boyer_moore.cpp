#include<iostream>
#include<cstring>
#define N_ALFABETO 256
using namespace std;

void obtenerTablaMalCaracter(string patron, int m, int* f);

void buscarBMH(string patron, string texto){
	int n = texto.size();
	int m = patron.size();
	
	int mc[N_ALFABETO];
	obtenerTablaMalCaracter(patron, m, mc);

	int i = 0; // texto
	int j = 0; // patron
	while (i <= n-m){
		j = m-1;
		while (patron[j] == texto[i+j])
			j--;

		if (j < 0){
		       	cout << endl << "Patrón encontrado en posición: " << i << endl;
			i ++; 
		}
		else{
			i += mc[texto[i]];
		}
		
	}
}

void obtenerTablaMalCaracter(string patron, int m, int* mc){
	for(int i = 0; i < N_ALFABETO; i++) mc[i] = m;
	for(int i = 0; i < m - 1; i++) mc[patron[i]] = m - i - 1;
}

int main(){
	string texto = "ABABDABACDABABCABAB"; //"AABAACAADAABAAABAA";
	string patron = "BAB";//"ADAA";

	buscarBMH(patron, texto);

	return 0;
}
