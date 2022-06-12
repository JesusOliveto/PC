#include <iostream>
#include <sstream>

using namespace std;

class Persona{
    private:
        string nombre;
        string apellido;
        int edad;
    public:
        Persona(string, string);
        Persona(string, string, int);
        ~Persona();
        string toString();        
        int getEdad(); // Leer edad
        void setEdad(int); // Asignar edad
};

// Constructor
Persona::Persona(string _nombre, string _apellido){
    //cout<<"Se ejecuta el constructor de Persona";
    nombre = _nombre;
    apellido = _apellido;
    edad = 0;
}

// Sobrecarga del constructor
Persona::Persona(string nombre, string apellido, int edad){
    this->nombre = nombre;    
    this->apellido = apellido;
    setEdad(edad);  // Doble encapsulamiento
}

// Destructor
Persona::~Persona(){
    cout << "Se ejecuta el destructor";    
}

int Persona::getEdad(){
    return edad;
}

void Persona::setEdad(int edad){
    if (edad < 0 || edad > 100){
        throw 20;
    }
    else{
    
        this->edad = edad;
    }
}

string Persona::toString(){
    stringstream s;
    s << endl << "Nombre:" << nombre << " " << apellido << endl;
    s << "Edad: " << getEdad() << endl;
    return s.str();
}



int main() {
  
    try
    {
        // Persona p1;
        // p1.nombre = "Juan";
        // p1.apellido = "Perez";
        // p1.edad = 21;

        Persona p1("Juan", "Perez");
        p1.setEdad(22);
        cout << p1.toString();
        
        Persona p2("Maria", "Sanchez", 30);
        cout << p2.toString();
    }
    catch(int e)
    {
        if (e == 20) {cout << "ERROR: Debe asignar una edad entre 0 y 100!" << endl;}
        else if (e == 30){cout << "ERROR: Debe ingresar un apellido de más de 3 letras" << endl;}
    }
    catch(...)
    {
        cout << "ERROR: ocurrio un error desconocido!" << endl;
    }

    return 0;
}   
