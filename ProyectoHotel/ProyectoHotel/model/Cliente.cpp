#include "Cliente.h"
#include <iostream>

Cliente::Cliente(string n, string d, string c, string p) 
    : Usuario(n, d, c, p) {}

void Cliente::hacerReserva() {
    cout << "El cliente inicia proceso de reserva." << endl;
}

void Cliente::solicitarServicio() {
    cout << "El cliente solicita un servicio." << endl;
}

void Cliente::verFactura() {
    for (const auto& f : facturas) {
        f.imprimirFactura();
    }
}

void Cliente::agregarFactura(Factura f) {
    facturas.push_back(f);
}
