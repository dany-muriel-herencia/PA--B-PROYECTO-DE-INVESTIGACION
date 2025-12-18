#ifndef EMPLEADO_H
#define EMPLEADO_H

#include "Usuario.h"
#include "Horario.h"

class Empleado : public Usuario {
protected:
    int idEmpleado;
    float salario;
    string puesto;
    Horario horario;

public:
    Empleado(string n, string d, string c, string p, int id, float sal, string pto);
    
    virtual void verDatos() const;
    virtual void realizarTarea() = 0; 
    
    // Getters
    float getSalario() const { return salario; }
    string getPuesto() const { return puesto; }
};

#endif
