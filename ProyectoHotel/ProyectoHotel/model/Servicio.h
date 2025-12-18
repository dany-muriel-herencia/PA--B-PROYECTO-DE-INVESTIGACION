#ifndef SERVICIO_H
#define SERVICIO_H

#include <string>
#include "Stock.h" // Connection
#include "Cocinero.h" // Connection
#include "Recibo.h" // Connection

using namespace std;

class Servicio {
private:
    string nombreServicio;
    float precio;
    
    // New associations
    Stock* stockAsociado;
    Cocinero* cocineroAsignado;

public:
    Servicio(string nombre = "", float p = 0.0);
    
    void verServicio() const;
    float getPrecio() const;
    string getNombre() const;

    // Connectors
    void setStock(Stock* s) { stockAsociado = s; }
    void setCocinero(Cocinero* c) { cocineroAsignado = c; }
    
    void usarRecibo(Recibo& r) {
        // Example usage
        r.imprimir();
    }
    
    void consultarStock() {
        if(stockAsociado) stockAsociado->verStock();
    }
    
    void enviarPedido(string plato) {
        if(cocineroAsignado) cocineroAsignado->prepararPedido(plato);
    }
};

#endif
