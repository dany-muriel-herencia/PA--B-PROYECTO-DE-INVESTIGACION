#include "Servicio.h"
#include <iostream>

Servicio::Servicio(string nombre, float p) 
    : nombreServicio(nombre), precio(p), stockAsociado(nullptr), cocineroAsignado(nullptr) {}

void Servicio::verServicio() const {
    cout << "Servicio: " << nombreServicio << " - $" << precio << endl;
}

float Servicio::getPrecio() const { return precio; }
string Servicio::getNombre() const { return nombreServicio; }
