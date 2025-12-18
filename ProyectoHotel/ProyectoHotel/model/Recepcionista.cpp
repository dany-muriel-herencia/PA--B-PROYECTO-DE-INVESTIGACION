#include "Recepcionista.h"
#include <iostream>

Recepcionista::Recepcionista(string n, string d, string c, string p, int id, float sal)
    : Empleado(n, d, c, p, id, sal, "Recepcionista") {}

void Recepcionista::realizarTarea() {
    cout << "Atendiendo en recepcion..." << endl;
}

void Recepcionista::registrarCheckIn(vector<Habitacion*>& habitaciones) {
    int num;
    cout << "Ingrese numero de habitacion para Check-In: ";
    cin >> num;
    bool found = false;
    for(auto h : habitaciones) {
        if(h->getNumero() == num) {
            if(h->getEstado() == "Disponible") {
                h->setEstado("Ocupada");
                cout << "Check-In exitoso. Habitacion " << num << " marcada como Ocupada.\n";
            } else {
                cout << "Error: La habitacion no esta disponible (Estado: " << h->getEstado() << ").\n";
            }
            found = true;
            break;
        }
    }
    if(!found) cout << "Habitacion no encontrada.\n";
}

void Recepcionista::registrarCheckOut(vector<Habitacion*>& habitaciones) {
    int num;
    cout << "Ingrese numero de habitacion para Check-Out: ";
    cin >> num;
    bool found = false;
    for(auto h : habitaciones) {
        if(h->getNumero() == num) {
            if(h->getEstado() == "Ocupada") {
                h->setEstado("Limpieza"); 
                h->liberar();
                cout << "Check-Out exitoso. Habitacion " << num << " enviada a Limpieza.\n";
            } else {
                cout << "Error: Check-out invalido (Estado actual: " << h->getEstado() << ").\n";
            }
            found = true;
            break;
        }
    }
    if(!found) cout << "Habitacion no encontrada.\n";
}

void Recepcionista::crearReservaPresencial(vector<Habitacion*>& habitaciones) {
    cout << "--- RESERVA PRESENCIAL ---\n";
    registrarCheckIn(habitaciones); 
}
