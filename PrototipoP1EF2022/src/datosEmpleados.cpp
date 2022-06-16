#include "datosEmpleados.h"
#include <cstring>
#include <iostream>

using std::string;
datosEmpleados::datosEmpleados(int valorCodigo, string valorApellido, string valorNombre, string valorCorreo, double valorSueldo)
{
    establecerCodigo( valorCodigo );
    establecerApellido( valorApellido );
    establecerNombre( valorNombre );
    establecerCorreo( valorCorreo );
    establecerSueldo( valorSueldo );

    }
int datosEmpleados::obtenerCodigo() const
{
   return codigo;
}
void datosEmpleados::establecerCodigo( int valorCodigo )
{
   codigo = valorCodigo;
}
string datosEmpleados::obtenerApellido() const
{
   return apellido;

}
void datosEmpleados::establecerApellido( string apellidoString )
{
    const char *valorApellido = apellidoString.data();
    int longitud = strlen( valorApellido );
    longitud = ( longitud < 15 ? longitud : 14 );
    strncpy( apellido, valorApellido, longitud );

    apellido[ longitud ] = '\0';

}
string datosEmpleados::obtenerNombre() const
{
   return nombre;
}
void datosEmpleados::establecerNombre( string primerNombre )
{
    const char *valorNombre = primerNombre.data();
    int longitud = strlen( valorNombre );
    longitud = ( longitud < 10 ? longitud : 9 );
    strncpy( nombre, valorNombre, longitud );

    primerNombre[ longitud ] = '\0';

}
double datosEmpleados::obtenerSueldo() const
{
   return sueldo;
}
void datosEmpleados::establecerSueldo( double valorSueldo )
{
   sueldo = valorSueldo;
}
string datosEmpleados::obtenerCorreo() const
{
   return correo;
}
void datosEmpleados::establecerCorreo( string correostring )
{
    const char *valorCorreo = correostring.data();
    int longitud = strlen( valorCorreo );
    longitud = ( longitud < 15 ? longitud : 14 );
    strncpy( correo, valorCorreo, longitud );

    correostring[ longitud ] = '\0';

}

datosEmpleados::~datosEmpleados()
{
    //dtor
}
