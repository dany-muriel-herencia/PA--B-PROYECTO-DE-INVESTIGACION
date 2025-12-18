#include "Factura.h"
#include <iostream>

Factura::Factura(string codigo, string r, string rs) 
    : Recibo(codigo, "HOY", "Cliente"), ruc(r), razonSocial(rs) {}

void Factura::agregarServicio(const Servicio& s) {
    // Convert Servicio to Item to store in Recibo
    // Asumimos cantidad 1 para servicios individuales
    Item* newItem = new Item(s.getNombre(), 1, s.getPrecio());
    agregarItem(newItem);
}

void Factura::imprimirFactura() const {
    imprimir();
}

void Factura::imprimir() const {
    cout << "=== FACTURA (Hereda Recibo) ===\n";
    cout << "RUC: " << ruc << " | Razon Social: " << razonSocial << endl;
    Recibo::imprimir();
}
