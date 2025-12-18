#ifndef LIMPIEZA_H
#define LIMPIEZA_H

#include "Empleado.h"

class Limpieza : public Empleado {
public:
    Limpieza(string n, string d, string p, int id, float sal);

    void realizarTarea() override;
    void limpiarHabitacion(int numHab);
    void marcarDisponibilidad(int numHab);
};

#endif
