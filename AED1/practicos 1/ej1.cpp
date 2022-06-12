#include <iostream>
#include <sstream>

using namespace std;

class cuentaBancaria{
    private:
        int cuenta;
        float balance;
    public:
    	cuentaBancaria(int cuenta);
		cuentaBancaria(int cuenta, float balance);
        ~cuentaBancaria();
        string toString();        
        int getCuenta(); 
        float getBalance(); 
        void setBalance(float balance); 
        void credito(float monto);
        void debito(float monto);
};

// Constructor
cuentaBancaria::cuentaBancaria(int _cuenta){
    cuenta = _cuenta;
    balance = 0;
}

// Sobrecarga del constructor
cuentaBancaria::cuentaBancaria(int cuenta, float balance){
    this->cuenta = cuenta;    
    setBalance(balance);  // Doble encapsulamiento
}

// Destructor
cuentaBancaria::~cuentaBancaria(){
    cout << "\n\nSe ejecuta el destructor";    
}

int cuentaBancaria::getCuenta(){
    return cuenta;
}

float cuentaBancaria::getBalance(){
    return balance;
}

void cuentaBancaria::setBalance(float balance){
    if (balance < 0 ){
        throw 20;
    }
    else{
    
        this->balance = balance;
    }
}

string cuentaBancaria::toString(){
    stringstream s;
    s << endl << "Cuenta:" << cuenta << endl;
    s << "Balance: " << getBalance() << endl;
    return s.str();
}

void cuentaBancaria::credito(float monto){
	if (monto < 0 ){
        throw 20;
    }
    else{
    
        balance = balance+monto;
    }
}

void cuentaBancaria::debito(float monto){
	balance=balance-monto;
	if (balance < 0 ){
        throw 30;
        balance=balance+monto;
    }
    else{
    
        balance = balance;
    }
}

int main() {
    try
    {
        cuentaBancaria p1(1324);
        p1.setBalance(220.25);
        cout << p1.toString();
        
        cuentaBancaria p2(4563, 4532.1);
        cout << p2.toString();
        
        cout<<"\n\n1324: +$200\n\n";
        p1.credito(200);
        cout << p1.toString();
        
        cout<<"\n\n4563: -$4000\n\n";
        p2.debito(4000);
         cout << p2.toString();
        
    }
    catch(int e)
    {
        if (e == 20) {cout << "ERROR: Debe agregar una cantidad mayor a 0" << endl;}
        else if (e == 30){cout << "ERROR: El saldo es insuficiente" << endl;}
    }
    catch(...)
    {
        cout << "ERROR: ocurrio un error desconocido!" << endl;
    }

    return 0;
}   
