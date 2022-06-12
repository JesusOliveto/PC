#include <iostream>
#include <sstream>

using namespace std;

class Figura{
    protected:
        int b;
        int h;

    public:
        Figura(int,int);
       virtual float getSuperficie();

};

Figura::Figura(int b, int h):b(b),h(h){}

float Figura::getSuperficie(){
    return -1.0;
}

class Rectangulo: public Figura{
    public:
        Rectangulo(int,int);
        virtual float getSuperficie();
};
  
Rectangulo::Rectangulo(int b, int h):Figura(b, h){
    cout << "Construyendo rectangulo ..."<< endl; 
}

float Rectangulo::getSuperficie(){
    return b*h;
}

class Triangulo: public Figura{
    public:
        Triangulo(int,int);
        virtual float getSuperficie();
};



Triangulo::Triangulo(int b, int h):Figura(b, h){
    cout << "Construyendo triangulo ..."<< endl; 
}

float Triangulo::getSuperficie(){
    return b*h/2;
}

class Cuadrado: public Figura{
    public:
        Cuadrado(int);
        virtual float getSuperficie();
};

Cuadrado::Cuadrado(int lado):Figura(lado, lado){
    cout << "Construyendo cuadrado ..."<< endl; 
}

float Cuadrado::getSuperficie(){
    return b * b;
}


int main (){

    Triangulo t1(4,5);
    cout<< "Sup t1: "<< t1.getSuperficie()<< endl;

    Cuadrado c1(7);
    cout<< "Sup c1: "<< c1.getSuperficie()<< endl;

    Rectangulo r1(7,9);
    cout<< "Sup r1: "<< r1.getSuperficie()<< endl;


    Figura* f;
    Triangulo t2(4,9);
    f = &t2;
    cout << "Sup de t2: " << f->getSuperficie() << endl;

    Rectangulo r2(10,5);
    f = &r2;
    cout << "Sup de r2: " << f->getSuperficie() << endl;

    return 0;
}