#include <iostream>
#include <sstream>
#include <string>
using namespace std;


//calse para ingresar matrices
class Matrix{
private:
    int largo;
    int ancho;
    int matriz[100][100];
public:
    Matrix(int largo, int ancho, int matriz[100][100]);
    ~Matrix();
    void setLargo(int);
    void setAncho(int);
    void setMatriz(int M[100][100]);
    void setMatriz2();
    int getAncho();
    int getLargo();
    string toString(); 
};


//clase para ingresar vectores
class Vector{
private:
    int largo;
    int vector[100];
public:
    Vector(int largo, int vector[100]);
    ~Vector();
    void setLargo(int);
    void setVector(int V[100]);
    void setVector2();
    int getLargo();
    string toString(); 
};


//Clase genérica para colocar cualquier variable utilizando un to_string();
class Generic{                                     
private:
    string tipo;
    string contenido;
public:
    Generic(string tipo,string contenido);
    ~Generic();
    void setContenido(string);
    string getContenido();
    void setTipo(string);
    string getTipo();
    string toString(); 
};

//CONSTRUCTORES Y DESTRUCTORES
Matrix::Matrix(int largo, int ancho, int matriz[100][100]){   
    setLargo(largo);
    setAncho(ancho);
    setMatriz(matriz);
}


Vector::Vector(int largo, int vector[100]){   
    setLargo(largo);
    setVector(vector);
}

Generic::Generic(string tipo,string contenido){
    setContenido(contenido);
    setTipo(tipo);
}

Matrix::~Matrix(){}
Vector::~Vector(){}
Generic::~Generic(){}

//GETTERS

int Matrix::getAncho(){return ancho;}
int Matrix::getLargo(){return largo;}

int Vector::getLargo(){return largo;}

string Generic::getContenido(){return contenido;}
string Generic::getTipo(){return tipo;}


//SETTERS
void Vector::setLargo(int input){
    largo=input;
}

void Matrix::setLargo(int input){
    largo=input;
}

void Matrix::setAncho(int input){
    ancho=input;
}


void Vector::setVector(int V[100]){
    //carga de un vector ya existente
    for (int i = 0; i < getLargo(); i++)
    {
        vector[i]=V[i];
    }
}

void Vector::setVector2(){
    int input;
    //carga de un vector nuevo
    for (int i = 0; i < getLargo(); i++)
    {
        cout<<"ingrese el valor deseado: ";
        cin>>input;
        cout<<endl;
        vector[i]=input;
    }
}

void Matrix::setMatriz(int M[100][100]){
    //carga de una matriz ya existente
    for (int i = 0; i < getLargo(); i++)
    {
        for (int j = 0; j < getAncho(); j++)
        {
            matriz[i][j]=M[i][j];
        }
    }
}
void Matrix::setMatriz2(){
    //carga matriz nueva
    int input;
    for (int i = 0; i < getLargo(); i++)
    {
        for (int j = 0; j < getAncho(); j++)
        {
            cout<<"ingrese el valor deseado: ";
            cin>>input;
            cout<<endl;
            matriz[i][j]=input;
        }
    }
}


void Generic::setContenido(string input){contenido= input;}
void Generic::setTipo(string input){tipo= input;}





//TOSTRINGS 

string Matrix::toString(){
     stringstream s;
     s<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    for (int i = 0; i < getLargo(); i++)
    {
        for (int j = 0; j < getAncho(); j++)
        {
            s<<matriz[i][j]<<" ";
        }
        s<<endl;
    }
    s<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    return s.str();
}

string Vector::toString(){
     stringstream s;
     s<<"----------------------------"<<endl;
    for (int i = 0; i < getLargo(); i++)
    {
        s<<vector[i]<<" ";

    }
     s<<endl;
    s<<"----------------------------"<<endl;
    return s.str();
}

string Generic::toString(){
    stringstream s;
    s<<"____________________________"<<endl;
    s<<getTipo()<<": "<<getContenido()<<endl;
    return s.str();
}

//MAIN
int main(){
    int mtest[100][100];
    int vtest[100];
    // for (int i = 0; i < 100; i++)
    // {
    //     for (int j = 0; j < 100; j++)
    //     {
    //         mtest[i][j]=i+j+10;
    //     }
    // }

    // for (int i = 0; i < 100; i++)
    //     {
    //         vtest[i]=i+10;
    //     }
    
    Vector v1(100,vtest);
    Matrix m1(100,100,mtest);

    Generic mtz("matriz 1", "");
    Generic vctr("vector 1", "");

    cout<<"ingresa tu largo "<<endl;
    int input;
    cin>>input;
    m1.setLargo(input);
    cout<<"ingresa tu ancho "<<endl;
    cin>>input;
    m1.setAncho(input);
     m1.setMatriz2();
    
    cout<<mtz.toString()<<m1.toString()<<endl;

    cout<<"ingresa tu largo "<<endl;
    cin>>input;
    v1.setLargo(input);
    v1.setVector2();
    cout<<vctr.toString()<<v1.toString()<<endl;

    float papa=145.429993;
    Generic test("papas", to_string(papa)) ;
    cout<<test.toString();
    return 0;
}