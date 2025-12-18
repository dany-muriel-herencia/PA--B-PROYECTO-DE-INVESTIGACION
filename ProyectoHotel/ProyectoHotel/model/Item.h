#ifndef ITEM_H
#define ITEM_H

#include <string>
using namespace std;

class Item {
private:
    string descripcion;
    int cantidad;
    float precioUnitario;
    float subtotal;

public:
    Item(string desc, int cant, float precio) 
        : descripcion(desc), cantidad(cant), precioUnitario(precio) {
        subtotal = cant * precio;
    }

    float getSubtotal() const { return subtotal; }
    string getDescripcion() const { return descripcion; }
    int getCantidad() const { return cantidad; }
    float getPrecioUnitario() const { return precioUnitario; }
};

#endif
