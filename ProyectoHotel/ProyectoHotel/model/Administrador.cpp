#include "Administrador.h"
#include <iostream>
#include <algorithm>

Administrador::Administrador(string n, string d, string p) 
    : Usuario(n, d, p) {}

void Administrador::gestionarHabitaciones() {
    cout << "Entrando a modulo de gestion de habitaciones..." << endl;
}

void Administrador::gestionarEmpleados() {
    cout << "Entrando a modulo de gestion de empleados..." << endl;
}

void Administrador::gestionarStock() {
    cout << "Entrando a modulo de stock..." << endl;
}

Habitacion* Administrador::buscarHabitacion(const vector<Habitacion*>& habitaciones, int numero) {
    for (auto h : habitaciones) {
        if (h->getNumero() == numero) {
            return h;
        }
    }
    return nullptr;
}

Empleado* Administrador::buscarEmpleado(const vector<Empleado*>& empleados, string dni) {
    for (auto e : empleados) {
        if (e->getDni() == dni) {
            return e;
        }
    }
    return nullptr;
}

Stock* Administrador::buscarProducto(const vector<Stock*>& inventario, string nombre) {
    for (auto s : inventario) {
        if (s->getNombre() == nombre) {
            return s;
        }
    }
    return nullptr;
}

void Administrador::ordenarHabitacionesPorPrecio(vector<Habitacion*>& habitaciones, bool ascendente) {
    if (ascendente) {
        sort(habitaciones.begin(), habitaciones.end(), [](Habitacion* a, Habitacion* b) {
            return a->getPrecio() < b->getPrecio();
        });
    } else {
        sort(habitaciones.begin(), habitaciones.end(), [](Habitacion* a, Habitacion* b) {
            return a->getPrecio() > b->getPrecio();
        });
    }
    cout << "Habitaciones ordenadas por precio (" << (ascendente ? "ascendente" : "descendente") << ")." << endl;
}

void Administrador::ordenarEmpleadosPorNombre(vector<Empleado*>& empleados, bool ascendente) {
    if (ascendente) {
        sort(empleados.begin(), empleados.end(), [](Empleado* a, Empleado* b) {
            return a->getNombre() < b->getNombre();
        });
    } else {
        sort(empleados.begin(), empleados.end(), [](Empleado* a, Empleado* b) {
            return a->getNombre() > b->getNombre();
        });
    }
    cout << "Empleados ordenados por nombre (" << (ascendente ? "ascendente" : "descendente") << ")." << endl;
}

void Administrador::ordenarStockPorCantidad(vector<Stock*>& inventario, bool ascendente) {
    if (ascendente) {
        sort(inventario.begin(), inventario.end(), [](Stock* a, Stock* b) {
            return a->getCantidad() < b->getCantidad();
        });
    } else {
        sort(inventario.begin(), inventario.end(), [](Stock* a, Stock* b) {
            return a->getCantidad() > b->getCantidad();
        });
    }
    cout << "Inventario ordenado por cantidad (" << (ascendente ? "ascendente" : "descendente") << ")." << endl;
}
