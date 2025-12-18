#ifndef COCINERO_H
#define COCINERO_H

#include "Empleado.h"
#include "Stock.h"
#include <vector>

class Cocinero : public Empleado {
private:
    vector<Stock*> inventarioCocina; // Aggregation

public:
    Cocinero(string n, string d, string c, string p, int id, float sal);

    void realizaTarea() { realizarTarea(); } // Alias if needed
    void realizarTarea() override;
    void prepararComida();
    
    // New methods
    void prepararPedido(string plato);
    bool verificarStock(string ingrediente, int cantidad);
    void agregarStock(Stock* s) { inventarioCocina.push_back(s); }
};

#endif
