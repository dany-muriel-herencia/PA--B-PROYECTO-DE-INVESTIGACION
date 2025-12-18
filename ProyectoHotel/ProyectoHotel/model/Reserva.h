#ifndef RESERVA_H
#define RESERVA_H

#include <string>

// Forward declarations to avoid cyclic includes in headers
class Cliente;
class Habitacion;

using namespace std;

class Reserva {
private:
    string codigoReserva;
    string fechaEntrada;
    string fechaSalida;
    Cliente* cliente;
    Habitacion* habitacion;

public:
    Reserva(string codigo, string entrada, string salida, Cliente* c, Habitacion* h);

    void verDetalles() const;
    void cancelarReserva();
    string getCodigo() const;
};

#endif
