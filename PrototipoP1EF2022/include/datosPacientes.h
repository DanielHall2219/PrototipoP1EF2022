#ifndef DATOSPACIENTES_H
#define DATOSPACIENTES_H
#include <cstring>
#include <iostream>

using std::string;

class datosPacientes
{
    public:
        virtual ~datosPacientes();
        datosPacientes( int = 0, string = "", string = "", string = "", double = 0.0 );

        void establecerCodigo( int );
        int obtenerCodigo() const;

        void establecerApellido( string );
        string obtenerApellido() const;

        void establecerNombre( string );
        string obtenerNombre() const;

        void establecerSueldo( double );
        double obtenerSueldo() const;

        void establecerCorreo( string );
        string obtenerCorreo() const;

    protected:

    private:
        int codigo;
        char apellido[ 15 ];
        char nombre[ 10 ];
        char correo[ 15 ];
        double sueldo;

};


#endif // DATOSPACIENTES_H
