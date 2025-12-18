#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <iostream>
using namespace std;

class Stock {
private:
    string nombreProducto; 
    int cantidadDisponible; 
    string tipo;
    float precio;

public:
    Stock(string nombre = "", int cant = 0, string t = "", float p = 0.0);

    bool verificarDisponibilidad(int cant) const;
    void descontar(int cant);
    void agregar(int cant);
    void verStock() const;
    
    // Getters
    string getNombre() const;
    int getCantidad() const;
    string getTipo() const;
    float getPrecio() const;

    // Legacy support
    void agregarItem(int cant) { agregar(cant); }
    void quitarItem(int cant) { descontar(cant); }
};

#endif
