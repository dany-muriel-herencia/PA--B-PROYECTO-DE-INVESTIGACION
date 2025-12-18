#include "Cocinero.h"
#include <iostream>

Cocinero::Cocinero(string n, string d, string c, string p, int id, float sal)
    : Empleado(n, d, c, p, id, sal, "Cocinero") {}

void Cocinero::realizarTarea() {
    cout << nombre << " esta cocinando." << endl;
}

void Cocinero::prepararComida() {
    cout << "Preparando platillo especial..." << endl;
}

void Cocinero::prepararPedido(string plato) {
    cout << "Cocinero " << nombre << " preparando pedido: " << plato << endl;
}

bool Cocinero::verificarStock(string ingrediente, int cantidad) {
    for(auto s : inventarioCocina) {
        if(s->getNombre() == ingrediente) {
            return s->verificarDisponibilidad(cantidad);
        }
    }
    return false;
}
