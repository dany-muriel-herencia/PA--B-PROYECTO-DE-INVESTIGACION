#include "Empleado.h"
#include <iostream>

Empleado::Empleado(string n, string d, string c, string p, int id, float sal, string pto)
    : Usuario(n, d, c, p), idEmpleado(id), salario(sal), puesto(pto) {}

void Empleado::verDatos() const {
    verInformacion();
    cout << "ID: " << idEmpleado << " | Puesto: " << puesto << " | Salario: $" << salario << endl;
    horario.verHorario();
}
