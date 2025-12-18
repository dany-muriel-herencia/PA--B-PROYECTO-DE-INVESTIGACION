#include "Mecanico.h"
#include <iostream>

Mecanico::Mecanico(string n, string d, string c, string p, int id, float sal)
    : Empleado(n, d, c, p, id, sal, "Mecanico") {}

void Mecanico::realizarTarea() {
    cout << "Mecanico listo para reparaciones." << endl;
}

void Mecanico::revisarInstalaciones(vector<Habitacion*>& habitaciones) {
    cout << "Reporte de Estado de Habitaciones:\n";
    for(auto h : habitaciones) {
        cout << "- Hab " << h->getNumero() << ": " << h->getEstado() << endl;
    }
}

void Mecanico::realizarMantenimiento(vector<Habitacion*>& habitaciones) {
    int num;
    cout << "Ingrese habitacion a poner en Mantenimiento: ";
    cin >> num;
    bool found = false;
    for(auto h : habitaciones) {
        if(h->getNumero() == num) {
            h->setEstado("Mantenimiento");
            cout << "Habitacion " << num << " ahora esta en Mantenimiento.\n";
            found = true;
            break;
        }
    }
    if(!found) cout << "Habitacion no encontrada.\n";
}
