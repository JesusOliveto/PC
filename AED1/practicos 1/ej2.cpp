#include <iostream>
#include <sstream>

using namespace std;

class fecha{
    private:
        int dia;
        int mes;
        int ano;
    public:
    	fecha(int dia,int mes, int ano);
        ~fecha();
        string toString();        
        int getDia(); 
        int getMes();
        int getAno();
        void setDia(int dia); 
        void setMes(int mes); 
        void setAno(int ano); 
        void agregarDias(int dia);
        void agregarMeses(int mes);
        void agregarAnos(int ano);
};

// Constructor
fecha::fecha(int _dia,int _mes,int _ano){
    dia = _dia;
    mes = _mes;
    ano=_ano;
}


// Destructor
fecha::~fecha(){
    cout << "\n\nSe ejecuta el destructor";    
}

int fecha::getDia(){
    return dia;
}

int fecha::getMes(){
    return mes;
}

int fecha::getAno(){
    return ano;
}


void fecha::setDia(int dia){
    if (dia <0 || dia>30 ){
        throw 20;
    }
    else{
    
        this->dia = dia;
    }
}

void fecha::setMes(int mes){

    if (mes <0 || mes>12 ){
        throw 20;
    }
    else{
    
        this->mes = mes;
    }
}

void fecha::setAno(int ano){
        this->ano = ano;
}

string fecha::toString(){
    stringstream s;
    s << endl << "Fecha:" << dia <<"/"<<mes<<"/"<<ano << endl;
    return s.str();
}

void fecha::agregarDias(int cantidad){
   	dia=dia+cantidad;
   	if (dia>30){
   		mes=mes+(dia/30);
   		dia=dia%30;
   		
	}
	if (mes>12){
   		ano=ano+(mes/12);
   		mes=(mes%12);
	}

}

void fecha::agregarMeses(int cantidad){

   	mes=mes+cantidad;
   	
	if (mes>12){
   		ano=ano+(mes/12);
   		mes=(mes%12);
	}
}

void fecha::agregarAnos(int cantidad){
	if (cantidad < 0 ){
        throw 20;
    }
    else{
    	ano=ano+cantidad;        
    }
}



int main() {
	int cantidad=0;
    try
    {
        fecha f1(1,1,2000);
        cout << f1.toString();
        
        f1.setDia(15);
        f1.setMes(5);
        f1.setAno(2015);
        cout<<"Fecha cambiada \n";
        cout << f1.toString();
        
        
        cout<<"agregue dias: ";
        cin>>cantidad;
        cout<<endl;
        f1.agregarDias(cantidad);
        cout << f1.toString();
        
        cout<<"agregue meses: ";
        cin>>cantidad;
        cout<<endl;
        f1.agregarMeses(cantidad);
        cout << f1.toString();
        
        cout<<"agregue anos: ";
        cin>>cantidad;
        cout<<endl;
        f1.agregarAnos(cantidad);
        cout << f1.toString();
        
        
    }
    catch(int e)
    {
        if (e == 20) {cout << "ERROR: Cantidad incorrecta" << endl;}
    }
    catch(...)
    {
        cout << "ERROR: ocurrio un error desconocido!" << endl;
    }

    return 0;
}   
