#include "Limpieza.h"
#include <iostream>

Limpieza::Limpieza(string n, string d, string p, int id, float sal)
    : Empleado(n, d, p, id, sal, "Limpieza") {}

void Limpieza::realizarTarea() {
    cout << nombre << " esta limpiando areas comunes." << endl;
}

void Limpieza::limpiarHabitacion(int numHab) {
    cout << "Limpiando habitacion " << numHab << "..." << endl;
}

void Limpieza::marcarDisponibilidad(int numHab) {
    cout << "Marcando habitacion " << numHab << " como disponible." << endl;
}
