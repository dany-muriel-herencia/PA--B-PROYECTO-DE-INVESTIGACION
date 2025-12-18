#ifndef HABITACION_H
#define HABITACION_H

#include <string>
#include <iostream>

using namespace std;

// Forward declaration
class Cliente;

class Habitacion {
private:
    int numero;
    string tipo;
    string estado; 
    float precio;
    Cliente* clienteAsignado;

public:
    Habitacion(int n = 0, string t = "", float p = 0.0);

    void asignarCliente(Cliente* c);
    void liberar();
    void verEstado() const;

    int getNumero() const;
    string getEstado() const;
    float getPrecio() const;
    string getTipo() const;
    
    void setEstado(string e);
};

#endif
