#ifndef CLIENTE_H
#define CLIENTE_H

#include "Usuario.h"
#include "Factura.h"
#include <vector>

class Cliente : public Usuario {
private:
    vector<Factura> facturas;

public:
    Cliente(string n = "", string d = "", string c = "", string p = "");

    void hacerReserva();
    void solicitarServicio();
    void verFactura();
    void agregarFactura(Factura f);
};

#endif
