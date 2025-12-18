#include "Stock.h"

Stock::Stock(string nombre, int cant, string t, float p) 
    : nombreProducto(nombre), cantidadDisponible(cant), tipo(t), precio(p) {}

bool Stock::verificarDisponibilidad(int cant) const {
    return cantidadDisponible >= cant;
}

void Stock::descontar(int cant) {
    if (verificarDisponibilidad(cant)) cantidadDisponible -= cant;
}

void Stock::agregar(int cant) {
    cantidadDisponible += cant;
}

void Stock::verStock() const {
    cout << "Item: " << nombreProducto << " | Cantidad: " << cantidadDisponible 
         << " | Tipo: " << tipo << " | Precio u.: $" << precio << endl;
}

string Stock::getNombre() const { return nombreProducto; }
int Stock::getCantidad() const { return cantidadDisponible; }
string Stock::getTipo() const { return tipo; }
float Stock::getPrecio() const { return precio; }
