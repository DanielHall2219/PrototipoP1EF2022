#include "datosPacientes.h"
#include <cstring>
#include <iostream>

using std::string;

datosPacientes::datosPacientes(int valorCodigo, string valorApellido, string valorNombre, string valorCorreo, double valorSueldo)
{
    establecerCodigo( valorCodigo );
    establecerApellido( valorApellido );
    establecerNombre( valorNombre );
    establecerCorreo( valorCorreo );
    establecerSueldo( valorSueldo );

    }
int datosPacientes::obtenerCodigo() const
{
   return codigo;
}
void datosPacientes::establecerCodigo( int valorCodigo )
{
   codigo = valorCodigo;
}
string datosPacientes::obtenerApellido() const
{
   return apellido;

}
void datosPacientes::establecerApellido( string apellidoString )
{
    const char *valorApellido = apellidoString.data();
    int longitud = strlen( valorApellido );
    longitud = ( longitud < 15 ? longitud : 14 );
    strncpy( apellido, valorApellido, longitud );

    apellido[ longitud ] = '\0';

}
string datosPacientes::obtenerNombre() const
{
   return nombre;
}
void datosPacientes::establecerNombre( string primerNombre )
{
    const char *valorNombre = primerNombre.data();
    int longitud = strlen( valorNombre );
    longitud = ( longitud < 10 ? longitud : 9 );
    strncpy( nombre, valorNombre, longitud );

    primerNombre[ longitud ] = '\0';

}
double datosPacientes::obtenerSueldo() const
{
   return sueldo;
}
void datosPacientes::establecerSueldo( double valorSueldo )
{
   sueldo = valorSueldo;
}
string datosPacientes::obtenerCorreo() const
{
   return correo;
}
void datosPacientes::establecerCorreo( string correostring )
{
    const char *valorCorreo = correostring.data();
    int longitud = strlen( valorCorreo );
    longitud = ( longitud < 15 ? longitud : 14 );
    strncpy( correo, valorCorreo, longitud );

    correostring[ longitud ] = '\0';

}


datosPacientes::~datosPacientes()
{
    //dtor
}
