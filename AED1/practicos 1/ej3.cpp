#include <iostream>
#include <sstream>
#include <tgmath.h>

using namespace std;

class Punto{
    private:
        int x;
        int y;
    public:
    	Punto();
		Punto(int x, int y);
        ~Punto();
        string toString();        
        int getX(); 
        int getY(); 
        void setX(int x); 
        void setY(int y); 
        float distancia();
        float distanciaOtro(int x2,int y2);
};

// Constructor
Punto::Punto(){
	x=0;
	y=0;
}

// Sobrecarga del constructor
Punto::Punto(int x, int y){
    setX(x);    
    setY(y);  // Doble encapsulamiento

}

// Destructor
Punto::~Punto(){
    cout << "\n\nSe ejecuta el destructor";    
}

int Punto::getX(){
    return x;
}

int Punto::getY(){
    return y;
}


void Punto::setX(int x){
    
    this->x = x;
}

void Punto::setY(int y){
    
    this->y = y;
}

string Punto::toString(){
    stringstream s;
    s << endl << "X:" << x << endl;
    s << "Y:" << y << endl;
    return s.str();
}

float Punto::distancia(){
	float d;
	d=sqrt((x*x)+(y*y));
	return d;
}

float Punto::distanciaOtro(int x2,int y2){
	float d;
	int x=this->x-x2;
	int y=this->y-y2;
	d=sqrt((x*x)+(y*y));
	return d;
}

int main() {
    try
    {
        Punto p1;
        Punto p2;
        p1.setX(4);
        p1.setY(10);
        p2.setX(150);
        p2.setY(200);
        
        cout <<"p1:"<< p1.toString();
        
        cout <<"p2:"<< p2.toString();
        
        cout<<"distancia a origen de p1: "<<p1.distancia()<<endl;
        cout<<"distancia a origen de p2: "<<p2.distancia()<<endl;
        
        cout<<"distancia entre puntos: "<<p1.distanciaOtro(p2.getX(),p2.getY())<<endl;
        
    }
    catch(int e)
    {
    	
    }
    catch(...)
    {
        cout << "ERROR: ocurrio un error desconocido!" << endl;
    }

    return 0;
}   
