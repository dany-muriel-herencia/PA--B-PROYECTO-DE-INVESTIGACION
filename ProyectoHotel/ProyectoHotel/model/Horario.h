#ifndef HORARIO_H
#define HORARIO_H

#include <string>
using namespace std;

class Horario {
private:
    string horaEntrada;
    string horaSalida;

public:
    Horario(string entrada = "08:00", string salida = "17:00");
    void verHorario() const;
    string getHoraEntrada() const;
    string getHoraSalida() const;
};

#endif
