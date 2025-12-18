#ifndef USUARIO_H
#define USUARIO_H

#include <string>
using namespace std;

class Usuario {
protected:
    string nombre;
    string dni;
    string password;

public:
    Usuario(string n = "", string d = "", string p = "");
    virtual ~Usuario();

    virtual void verInformacion() const;
    void iniciarSesion();

    string getNombre() const;
    string getDni() const;
    string getPassword() const;
};

#endif