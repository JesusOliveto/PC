#include<iostream>
#include<sstream>
  
using namespace std;

class Punto{
    private: 
        int x;
        int y;
    public:
        Punto(int, int);
        string toString();
};





class Vehiculo{
    private: 
        string nombre;
        Punto posicion;
    public:
        Vehiculo(string);
        Vehiculo(string, int, int);
        string toString();
};

// Alternativa para esta sobrecarga
// Vehiculo::Vehiculo(string nombre, int x, int y):posicion(x,y){
//     this->nombre = nombre;
// }

Punto::Punto(int x, int y): x(x), y(y){}

string Punto::toString(){
    stringstream s;
    s << "[" << x << ", " << y <<"]";
    return s.str();
}

Vehiculo::Vehiculo(string nombre, int x, int y):nombre(nombre),posicion(x,y){}

Vehiculo::Vehiculo(string nombre):Vehiculo(nombre, 0, 0){}

string Vehiculo::toString(){
    stringstream s;
    s << "Nombre: " << nombre << endl;
    s << "Posición: " << posicion.toString() << endl;
    s << endl;
    return s.str();
}

int main(){

    Vehiculo v1("moto");
    Vehiculo v2("tren", 4,6);
    Vehiculo v3("avion", 6, 40);

    cout << v1.toString();
    cout << v2.toString();
    cout << v3.toString();


    return 0;
}