#ifndef RECEPCIONISTA_H
#define RECEPCIONISTA_H

#include "Empleado.h"
#include <vector>
#include "Habitacion.h" 

class Recepcionista : public Empleado {
public:
    Recepcionista(string n, string d, string c, string p, int id, float sal);

    void realizarTarea() override;
    
    void registrarCheckIn(vector<Habitacion*>& habitaciones); 
    void registrarCheckOut(vector<Habitacion*>& habitaciones);
    void crearReservaPresencial(vector<Habitacion*>& habitaciones);
};

#endif
