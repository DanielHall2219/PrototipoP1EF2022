#include "Empleados.h"
#include "datosEmpleados.h"
#include <iostream>
#include <ctime>
#include <vector>

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::ios;
using std::left;
using std::right;
using std::fixed;
using std::showpoint;

#include <fstream>
using std::ofstream;
using std::ostream;
using std::fstream;

#include <iomanip>
using std::setw;
using std::setprecision;
#include <cstdlib>

int opcionEmp();
void imprimirRegistroEmp( fstream& );
void crearArchivoCreditoEmp();
void mostrarLineaEmp( ostream&, const datosEmpleados & );
void nuevoRegistroEmp( fstream& );
int obtenernCodigoEmp( const char * const );
void modificarRegistroEmp( fstream& );
void eliminarRegistroEmp( fstream& );
void consultarRegistroEmp( fstream& );
void mostrarLineaPantallaEmp( const datosEmpleados &);

using namespace std;

Empleados::Empleados()
{
    fstream creditoEntradaSalida( "emp.dat", ios::in | ios::out | ios::binary);
    if ( !creditoEntradaSalida ) {
        cerr << "No se pudo abrir el archivo." << endl;
        crearArchivoCreditoEmp();
        cout <<  "Archivo creado satisfactoriamente, pruebe de nuevo\n";
        exit ( 1 );
    }
    enum Opciones { agregar = 1, altas, modificar, bajas, lectura, FIN };
   int opcion;
    while ( ( opcion = opcionEmp() ) != FIN ) {
        switch ( opcion ) {
            case agregar:
                imprimirRegistroEmp( creditoEntradaSalida );
            break;
            case altas:
                nuevoRegistroEmp( creditoEntradaSalida );
            break;
            case modificar:
                modificarRegistroEmp( creditoEntradaSalida );
            break;
            case bajas:
                eliminarRegistroEmp( creditoEntradaSalida );
            break;
            case lectura:
                consultarRegistroEmp( creditoEntradaSalida );
            break;
            default:
            cerr << "Opcion incorrecta" << endl;
            break;

      } //FIN SWITCH

       creditoEntradaSalida.clear();

   } //FIN WHILE
}
int opcionEmp(){
    system("cls");

    time_t now = time(0);
    tm * time = localtime(&now);

    vector<string> dia_semana;
    dia_semana.push_back("Domingo");
    dia_semana.push_back("Lunes");
    dia_semana.push_back("Martes");
    dia_semana.push_back("Miercoles");
    dia_semana.push_back("Jueves");
    dia_semana.push_back("Viernes");
    dia_semana.push_back("Sabado");

    vector<string> mes;
    mes.push_back("Enero");
    mes.push_back("Febrero");
    mes.push_back("Marzo");
    mes.push_back("Abril");
    mes.push_back("Mayo");
    mes.push_back("Junio");
    mes.push_back("Julio");
    mes.push_back("Agosto");
    mes.push_back("Septiembre");
    mes.push_back("Octubre");
    mes.push_back("Noviembre");
    mes.push_back("Diciembre");

    int year = 1900 + time->tm_year;

    //Formato=hoy miercoles, 27 de mayo del 2015
    cout<< "\n";
    cout << "Hoy " << dia_semana[time->tm_wday] << ", ";
    cout << time->tm_mday << " de " << mes[time->tm_mon] << " del " << year << endl;
    cout << time->tm_hour << ":" << time->tm_min << ":" << time->tm_sec << endl;



    cout<<"\n\t\t\t\t   ---------------------------------------------------------------"<<endl;
	cout<<"\t\t\t\t     |   EMPLEADOS - 9959-21-1395 - Daniel Alexander Hall Alvarez  |"<<endl;
	cout<<"\t\t\t\t     ---------------------------------------------------------------"<<endl;

    cout<< "\n\n\t\t\t 1. Guardar archivo de texto para Imprimirlo" << endl
        << "\t\t\t 2. Altas" << endl
        << "\t\t\t 3. Modificar Empleado" << endl
        << "\t\t\t 4. Bajas" << endl
        << "\t\t\t 5. Lectura de Lista de Empleados" << endl
        << "\t\t\t 6. Regresar al Menu Principal" << endl

        << "\n\t\t\tIngrese su opcion: ";
    int opcionMenu ;

    cin >> opcionMenu;

   return opcionMenu;
}

void imprimirRegistroEmp( fstream &leerDeArchivo )
{
    ofstream archivoImprimirSalida( "ImprimirFacultad.txt", ios::out );
    if ( !archivoImprimirSalida ) {
        cerr << "No se pudo crear el archivo." << endl;
        exit( 1 );

    } //FIN DE INSTRUCCION if

    archivoImprimirSalida << left << setw( 10 ) << "Codigo" << setw( 16 )<< "Apellido" << setw( 14 ) << "Nombre" << setw( 16 ) << "Correo"<< right
       << setw( 10 ) << "Sueldo" << endl;
    leerDeArchivo.seekg( 0 );

    datosEmpleados empleadoss;
    leerDeArchivo.read( reinterpret_cast< char * >( &empleadoss ), sizeof( datosEmpleados ) );

    while ( !leerDeArchivo.eof() ) {
        if ( empleadoss.obtenerCodigo() != 0 )
        mostrarLineaEmp( archivoImprimirSalida, empleadoss );
        leerDeArchivo.read( reinterpret_cast< char * >( &empleadoss ), sizeof( datosEmpleados ) );
    } //FIN DE WHILE

} //FIN DE LA FUNCION -IMPRIMIR REGISTRO-
void mostrarLineaEmp( ostream &salida, const datosEmpleados &registro )
{
   salida << left << setw( 10 ) << registro.obtenerCodigo()
          << setw( 16 ) << registro.obtenerApellido().data()
          << setw( 14 ) << registro.obtenerNombre().data()
          << setw( 16 ) << registro.obtenerCorreo().data()
          << setw( 10 ) << setprecision( 2 ) << right << fixed<< showpoint << registro.obtenerSueldo() << endl;

}//FIN -MOSTRARLINEA-
void crearArchivoCreditoEmp()
{
    ofstream creditoSalida( "emp.dat", ios::out | ios::binary );
    if ( !creditoSalida ) {
      cerr << "No se pudo abrir el archivo." << endl;
      exit( 1 );
    }
    datosEmpleados empleadoEnBlanco;
    for ( int i = 0; i < 100; i++ )
        creditoSalida.write(reinterpret_cast< const char * >( &empleadoEnBlanco ), sizeof( datosEmpleados ) );
}
void nuevoRegistroEmp( fstream &insertarEnArchivo )
{
    int codigo = obtenernCodigoEmp( "\nEscriba el Codigo del empleado " );
    insertarEnArchivo.seekg( ( codigo - 1 ) * sizeof( datosEmpleados ) );
    datosEmpleados empleadoss;
    insertarEnArchivo.read( reinterpret_cast< char * >( &empleadoss ), sizeof( datosEmpleados ) );

    if ( empleadoss.obtenerCodigo() == 0 ) {
        char apellido[ 15 ];
        char nombre[ 10 ];
        char correo[ 15 ];
        double sueldo;
        cout<<"Escriba el Area del empleado: ";
        cin>> setw( 15 ) >> apellido;
        cout<<"Escriba el Nombre del empleado: ";
        cin>> setw( 10 ) >> nombre;
        cout<<"Escriba el Correo del empleado ";
        cin>> setw( 15 ) >> correo;
        cout<<"Escriba el Sueldo del empleado ";
        cin>> sueldo;
        empleadoss.establecerApellido( apellido );
        empleadoss.establecerNombre( nombre );
        empleadoss.establecerCorreo( correo );
        empleadoss.establecerSueldo( sueldo );
        empleadoss.establecerCodigo( codigo );

        insertarEnArchivo.seekp( ( codigo - 1 ) * sizeof( datosEmpleados ) );
        insertarEnArchivo.write( reinterpret_cast< const char * >( &empleadoss ), sizeof( datosEmpleados ) );
        cout<<"\n Empleado agregado Exitosamente..."<<endl;

    } //FIN IF
    else
        cerr << "El Empleado con codigo #" << codigo << " ya contiene informacion.\n" << endl;

} //FIN REGISTRO
int obtenernCodigoEmp( const char * const indicador )
{
   int codigo;
    do {
      cout << indicador << "(1 - 100): ";
      cin >> codigo;

    } while ( codigo < 1 || codigo > 100 );

   return codigo;

} //FIN -OBTENERCODIGO-
void modificarRegistroEmp( fstream &actualizarArchivo )
{
    int opcionAc=0;
    cout<<"\nEscoja opcion a Actualizar: \n 1. Sueldo\n 2. Nombre\n 3. Estatus \n 4. Correo\n  R - ";
    cin>>opcionAc;

    if (opcionAc == 1){
        int codigo = obtenernCodigoEmp( "\nEscriba el codigo del empleado que desea Modifcar" );

        actualizarArchivo.seekg(( codigo - 1 ) * sizeof( datosEmpleados ));

        datosEmpleados empleadoss;
        actualizarArchivo.read( reinterpret_cast< char * >( &empleadoss ), sizeof( datosEmpleados ) );

        if (empleadoss.obtenerCodigo() != 0 ) {
            mostrarLineaEmp( cout, empleadoss );
            cout << "\nEscriba aumento (+) o descuento (-): ";
            double cambiosu;
            cin >> cambiosu;
            double sueldoAnterior = empleadoss.obtenerSueldo();
            empleadoss.establecerSueldo( sueldoAnterior + cambiosu );
            mostrarLineaEmp( cout, empleadoss );

            actualizarArchivo.seekp(( codigo - 1 ) * sizeof( datosEmpleados ));

            actualizarArchivo.write(reinterpret_cast< const char * >( &empleadoss ), sizeof( datosEmpleados ) );
        }

    }else if (opcionAc== 2){
        int codigo = obtenernCodigoEmp( "\nEscriba el codigo del empleado que desea Modifcar" );

        actualizarArchivo.seekg(( codigo - 1 ) * sizeof( datosEmpleados ));

        datosEmpleados empleadoss;
        actualizarArchivo.read( reinterpret_cast< char * >( &empleadoss ), sizeof( datosEmpleados ) );

        //ACTUALIZAR EL REGISTRO
        if (empleadoss.obtenerCodigo() != 0 ) {
            mostrarLineaEmp( cout, empleadoss );
            cout << "\nEscriba el nuevo Nombre: ";
            string nombre;
            cin >> nombre;

            string nombreAnterior = empleadoss.obtenerNombre();
            empleadoss.establecerNombre( nombre );
            mostrarLineaEmp( cout, empleadoss );

            actualizarArchivo.seekp(( codigo - 1 ) * sizeof( datosEmpleados ));
            actualizarArchivo.write(reinterpret_cast< const char * >( &empleadoss ), sizeof( datosEmpleados ) );
        }
    }else if(opcionAc == 3){
        int codigo = obtenernCodigoEmp( "\nEscriba el codigo del empleado que desea Modifcar" );

        actualizarArchivo.seekg(( codigo - 1 ) * sizeof( datosEmpleados ));

        datosEmpleados empleadoss;
        actualizarArchivo.read( reinterpret_cast< char * >( &empleadoss ), sizeof( datosEmpleados ) );

        if (empleadoss.obtenerCodigo() != 0 ) {
                mostrarLineaEmp( cout, empleadoss );
                cout << "\nEscriba el nuevo Estatus: ";
                string apellido;
                cin >> apellido;

                string apellidoAnterior = empleadoss.obtenerApellido();
                empleadoss.establecerApellido( apellido );
                mostrarLineaEmp( cout, empleadoss );

                actualizarArchivo.seekp(( codigo - 1 ) * sizeof( datosEmpleados ));

                actualizarArchivo.write(reinterpret_cast< const char * >( &empleadoss ), sizeof( datosEmpleados ) );
        }
    }else if(opcionAc == 4){
        int codigo = obtenernCodigoEmp( "\nEscriba el codigo del empleado que desea Modifcar" );

        actualizarArchivo.seekg(( codigo - 1 ) * sizeof( datosEmpleados ));

        datosEmpleados empleadoss;
        actualizarArchivo.read( reinterpret_cast< char * >( &empleadoss ), sizeof( datosEmpleados ) );

        if (empleadoss.obtenerCodigo() != 0 ) {
                mostrarLineaEmp( cout, empleadoss );
                cout << "\nEscriba el nuevo Correo: ";
                string correo;
                cin >> correo;

                string correoAnterior = empleadoss.obtenerCorreo();
                empleadoss.establecerCorreo( correo );
                mostrarLineaEmp( cout, empleadoss );

                actualizarArchivo.seekp(( codigo - 1 ) * sizeof( datosEmpleados ));

                actualizarArchivo.write(reinterpret_cast< const char * >( &empleadoss ), sizeof( datosEmpleados ) );
        }
    }

} //FIN DE -ACTUALIZAR REGISTRO-
void eliminarRegistroEmp( fstream &eliminarDeArchivo )
{
    int codigo = obtenernCodigoEmp( "\nEscriba el codigo del empleado a Eliminar" );
    eliminarDeArchivo.seekg( ( codigo - 1 ) * sizeof( datosEmpleados ) );
    datosEmpleados empleadoss;
    eliminarDeArchivo.read( reinterpret_cast< char * >( &empleadoss ), sizeof( datosEmpleados ) );

    if ( empleadoss.obtenerCodigo() != 0 ) {
        datosEmpleados clienteEnBlanco;
        eliminarDeArchivo.seekp( ( codigo - 1 ) * sizeof( datosEmpleados ) );
        eliminarDeArchivo.write( reinterpret_cast< const char * >( &clienteEnBlanco ), sizeof( datosEmpleados ) );

      cout << " El empleado con #" << codigo << " eliminada Exitosamente.\n";

   } //FIN IF

   //ERROR SI NO EXISTE
   else
      cerr << "El empleado con #" << codigo << " esta vacia.\n";

} //FIN -ELIMINARREGISTRO-
void consultarRegistroEmp( fstream &leerDeArchivo )
{
    cout << left << setw( 10 ) << "\nCodigo" << setw( 16 ) << " Apellido" << setw( 14 ) << " Nombre" << setw( 16 ) << " Correo" << right << setw( 10 ) << " Sueldo" << endl;
    leerDeArchivo.seekg( 0 );
    datosEmpleados empleadoss;
    leerDeArchivo.read( reinterpret_cast< char * >( &empleadoss ), sizeof( datosEmpleados ) );
    while ( !leerDeArchivo.eof() ) {
        if ( empleadoss.obtenerCodigo() != 0 )
            mostrarLineaPantallaEmp(empleadoss);
            leerDeArchivo.read( reinterpret_cast< char * >( &empleadoss ), sizeof( datosEmpleados ) );

   } //FIN WHILE
 cout<<"\n";
    system("pause");
} //FIN CONSULTAR REGISTRO
void mostrarLineaPantallaEmp( const datosEmpleados &registro )
{
   cout << left <<" "<< setw( 10 ) << registro.obtenerCodigo()
          << setw( 16 ) << registro.obtenerApellido().data()
          << setw( 14 ) << registro.obtenerNombre().data()
          << setw( 16 ) << registro.obtenerCorreo().data()
          << setw( 10 ) << setprecision( 2 ) << right << fixed
          << showpoint << registro.obtenerSueldo() << endl;

} //FIN -MOSTRARLINEAENOANTALLA-

Empleados::~Empleados()
{
    //dtor
}
