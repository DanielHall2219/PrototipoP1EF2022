#ifndef DATOSUSUARIO_H
#define DATOSUSUARIO_H

#include <iostream>
using std::string;

class DatosUsuario
{
    public:
        virtual ~DatosUsuario();
        DatosUsuario( int = 0, int = 0 );

        void establecerUsuario( int );
        int obtenerUsuario() const;

        void establecerContra( int );
        int obtenerContra() const;

    protected:

    private:
        int usuario;
        int contra;
};

#endif // DATOSUSUARIO_H
