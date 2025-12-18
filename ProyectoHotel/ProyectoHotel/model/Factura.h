#ifndef FACTURA_H
#define FACTURA_H

#include "Recibo.h"
#include "Servicio.h" 

class Factura : public Recibo {
private:
    string ruc;
    string razonSocial;

public:
    // Adapted constructor to be compatible with main.cpp usage but use Recibo base
    Factura(string codigo = "", string r = "N/A", string rs = "Empresa");
    
    // Compatibility method for existing code
    void agregarServicio(const Servicio& s); 

    void imprimirFactura() const; // Old method alias
    void imprimir() const override;
};

#endif
