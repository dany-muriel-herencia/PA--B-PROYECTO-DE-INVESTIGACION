#include "Reserva.h"
#include "Cliente.h"
#include "Habitacion.h"
#include <iostream>

Reserva::Reserva(string codigo, string entrada, string salida, Cliente* c, Habitacion* h)
    : codigoReserva(codigo), fechaEntrada(entrada), fechaSalida(salida), cliente(c), habitacion(h) {}

void Reserva::verDetalles() const {
    cout << "Reserva: " << codigoReserva << endl;
    if(cliente) cout << "Cliente: " << cliente->getNombre() << endl;
    if(habitacion) cout << "Habitacion: " << habitacion->getNumero() << endl;
    cout << "Fecha: " << fechaEntrada << " a " << fechaSalida << endl;
}

void Reserva::cancelarReserva() {
    cout << "Reserva " << codigoReserva << " cancelada." << endl;
    if (habitacion) habitacion->liberar();
}

string Reserva::getCodigo() const { return codigoReserva; }
