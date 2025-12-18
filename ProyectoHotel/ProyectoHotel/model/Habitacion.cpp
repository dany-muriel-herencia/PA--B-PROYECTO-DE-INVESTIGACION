#include "Habitacion.h"
#include "Cliente.h"
#include <iostream>

Habitacion::Habitacion(int n, string t, float p) 
    : numero(n), tipo(t), estado("Disponible"), precio(p), clienteAsignado(nullptr) {}

void Habitacion::asignarCliente(Cliente* c) {
    if (estado == "Disponible") {
        clienteAsignado = c;
        estado = "Ocupada";
        cout << "Habitacion " << numero << " asignada a " << c->getNombre() << endl;
    } else {
        cout << "La habitacion no esta disponible." << endl;
    }
}

void Habitacion::liberar() {
    clienteAsignado = nullptr;
    estado = "Disponible";
    cout << "Habitacion " << numero << " liberada." << endl;
}

void Habitacion::verEstado() const {
    cout << "Hab: " << numero << " | Tipo: " << tipo << " | Estado: " << estado << " | Precio: " << precio << endl;
}

int Habitacion::getNumero() const {
     return numero; 
    }
string Habitacion::getEstado() const {
     return estado; 
    }
float Habitacion::getPrecio() const {
     return precio; 
    }
string Habitacion::getTipo() const {
     return tipo; 
    }
void Habitacion::setEstado(string e) {
     estado = e; 
    }
