#include "Horario.h"
#include <iostream>

Horario::Horario(string entrada, string salida) 
    : horaEntrada(entrada), horaSalida(salida) {}

void Horario::verHorario() const {
    cout << "Horario: " << horaEntrada << " - " << horaSalida << endl;
}

string Horario::getHoraEntrada() const { return horaEntrada; }
string Horario::getHoraSalida() const { return horaSalida; }
