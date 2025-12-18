#ifndef RECIBO_H
#define RECIBO_H

#include <string>
#include <vector>
#include <iostream>
#include "Item.h"

using namespace std;

class Recibo {
protected:
    string idRecibo;
    string fecha;
    string cliente;
    vector<Item*> listaItems;
    float total;
    string metodoPago;

public:
    Recibo(string id, string f, string c) 
        : idRecibo(id), fecha(f), cliente(c), total(0.0), metodoPago("Efectivo") {}

    virtual ~Recibo() {
        for(auto i : listaItems) delete i;
    }

    void agregarItem(Item* item) {
        listaItems.push_back(item);
        calcularTotal();
    }

    void calcularTotal() {
        total = 0;
        for(auto i : listaItems) {
            total += i->getSubtotal();
        }
    }

    virtual void imprimir() const {
        cout << "Recibo: " << idRecibo << "\nFecha: " << fecha << "\nCliente: " << cliente << endl;
        cout << "Items:\n";
        for(auto i : listaItems) {
            cout << "- " << i->getDescripcion() << ": $" << i->getSubtotal() << endl;
        }
        cout << "Total: $" << total << endl;
    }
    
    void setMetodoPago(string mp) { metodoPago = mp; }
};

#endif
