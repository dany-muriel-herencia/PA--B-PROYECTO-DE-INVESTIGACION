#ifndef MECANICO_H
#define MECANICO_H

#include "Empleado.h"
#include <vector>
#include "Habitacion.h"

class Mecanico : public Empleado {
public:
    Mecanico(string n, string d, string c, string p, int id, float sal);

    void realizarTarea() override;
    
    void revisarInstalaciones(vector<Habitacion*>& habitaciones);
    void realizarMantenimiento(vector<Habitacion*>& habitaciones);
};

#endif
