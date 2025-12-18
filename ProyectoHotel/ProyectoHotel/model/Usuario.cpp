#include "Usuario.h"
#include <iostream>

Usuario::Usuario(string n, string d, string p) 
    : nombre(n), dni(d), password(p) {}

Usuario::~Usuario() {}

void Usuario::verInformacion() const {
    cout << "Usuario: " << nombre << " | DNI: " << dni << endl;
}

void Usuario::iniciarSesion() {
    cout << "Iniciando sesion para " << nombre << "..." << endl;
}

string Usuario::getNombre() const { return nombre; }
string Usuario::getDni() const { return dni; }
string Usuario::getPassword() const { return password; }
