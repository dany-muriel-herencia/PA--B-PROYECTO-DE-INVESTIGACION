#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include "Usuario.h"
#include "Habitacion.h"
#include "Empleado.h"
#include "Stock.h"
#include <vector>
#include <algorithm>

class Administrador : public Usuario {
public:
    Administrador(string n, string d, string c, string p);

    void gestionarHabitaciones();
    void gestionarEmpleados();
    void gestionarStock();

    // Funciones de busqueda
    Habitacion* buscarHabitacion(const vector<Habitacion*>& habitaciones, int numero);
    Empleado* buscarEmpleado(const vector<Empleado*>& empleados, string dni);
    Stock* buscarProducto(const vector<Stock*>& inventario, string nombre);

    // Funciones de ordenacion
    void ordenarHabitacionesPorPrecio(vector<Habitacion*>& habitaciones, bool ascendente = true);
    void ordenarEmpleadosPorNombre(vector<Empleado*>& empleados, bool ascendente = true);
    void ordenarStockPorCantidad(vector<Stock*>& inventario, bool ascendente = true);
};

#endif
