#ifndef BOLETA_H
#define BOLETA_H

#include "Recibo.h"

class Boleta : public Recibo {
private:
    string dniCliente;

public:
    Boleta(string id, string f, string c, string dni) 
        : Recibo(id, f, c), dniCliente(dni) {}

    void imprimir() const override {
        cout << "--- BOLETA ---\n";
        Recibo::imprimir();
        cout << "DNI Cliente: " << dniCliente << endl;
        cout << "--------------\n";
    }
};

#endif
