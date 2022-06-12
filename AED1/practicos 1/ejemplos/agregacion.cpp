#include<iostream>
#include<sstream>

using namespace std;
  
class Autor{
    private:
        string nombre;
        string apellido;
        string email;
    public:
        Autor(string, string, string);
        string toString();
};

class Libro{
    private:
        string titulo;
        Autor* autor;
        double precio;
        int cantidad;
    public:
        Libro(string, Autor*, double, int);
        string toString();
};


Autor::Autor(string nombre, string apellido, string email):nombre(nombre), apellido(apellido), email(email){}

string Autor::toString(){
    stringstream s;
    s << nombre << " " << apellido << "(" << email << ")";
    return s.str();
}

Libro::Libro(string titulo, Autor* autor,double precio, int cantidad){
    this->titulo = titulo;
    this->autor = autor;
    this->precio = precio;
    this->cantidad = cantidad;
}

string Libro::toString(){
    stringstream s;
    s << "Titulo: " << titulo << endl;
    s << "Autor: " << autor->toString() << endl;
    s << "Precio: $" << precio << endl;
    s << "Cantidad: " << cantidad << endl;
    return s.str();
}

int main(){

    Autor jlb("Jorge Luis", "Borges", "jlb@test.com");
    Autor ggm("Gabriel", "Garcia Marquez", "ggm@test.com");
    cout << jlb.toString() << endl;
    cout << ggm.toString() << endl;

    Libro l1("El Aleph", &jlb, 516.78, 10 );
    Libro l2("Cien años de soledad", &ggm, 454.78, 40 );
    Libro l3("El fin", &jlb, 232.78, 50 );

    cout << l1.toString() << endl;
    cout << l2.toString() << endl;
    cout << l3.toString() << endl;

    return 0;
}