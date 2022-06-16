#include "Paciente.h"
#include "datosPacientes.h"
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

int opcionp();
void imprimirRegistrop( fstream& );
void crearArchivoCreditop();
void mostrarLineap( ostream&, const datosPacientes & );
void nuevoRegistrop( fstream& );
int obtenernCodigop( const char * const );
void modificarRegistrop( fstream& );
void eliminarRegistrop( fstream& );
void consultarRegistrop( fstream& );
void mostrarLineaPantallap( const datosPacientes &);

using namespace std;

Paciente::Paciente()
{
    fstream creditoEntradaSalida( "pacientes.dat", ios::in | ios::out | ios::binary);
    if ( !creditoEntradaSalida ) {
        cerr << "No se pudo abrir el archivo." << endl;
        crearArchivoCreditop();
        cout <<  "Archivo creado satisfactoriamente, pruebe de nuevo\n";
        exit ( 1 );
    }
    enum Opciones { agregar = 1, altas, modificar, bajas, lectura, FIN };
   int opcion;
    while ( ( opcion = opcionp() ) != FIN ) {
        switch ( opcion ) {
            case agregar:
                imprimirRegistrop( creditoEntradaSalida );
            break;
            case altas:
                nuevoRegistrop( creditoEntradaSalida );
            break;
            case modificar:
                modificarRegistrop( creditoEntradaSalida );
            break;
            case bajas:
                eliminarRegistrop( creditoEntradaSalida );
            break;
            case lectura:
                consultarRegistrop( creditoEntradaSalida );
            break;
            default:
            cerr << "Opcion incorrecta" << endl;
            break;

      } //FIN SWITCH

       creditoEntradaSalida.clear();

   } //FIN WHILE
}
int opcionp(){
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
	cout<<"\t\t\t\t     |   Pacientes - 9959-21-1395 - Daniel Alexander Hall Alvarez  |"<<endl;
	cout<<"\t\t\t\t     ---------------------------------------------------------------"<<endl;

    cout<< "\n\n\t\t\t 1. Guardar archivo de texto para Imprimirlo" << endl
        << "\t\t\t 2. Altas" << endl
        << "\t\t\t 3. Modificar Paciente" << endl
        << "\t\t\t 4. Bajas" << endl
        << "\t\t\t 5. Lectura de Lista de Paciente" << endl
        << "\t\t\t 6. Regresar al Menu Principal" << endl

        << "\n\t\t\tIngrese su opcion: ";
    int opcionMenu ;

    cin >> opcionMenu;

   return opcionMenu;
}

void imprimirRegistrop( fstream &leerDeArchivo )
{
    ofstream archivoImprimirSalida( "ImprimirFacultad.txt", ios::out );
    if ( !archivoImprimirSalida ) {
        cerr << "No se pudo crear el archivo." << endl;
        exit( 1 );

    } //FIN DE INSTRUCCION if

    archivoImprimirSalida << left << setw( 10 ) << "Codigo" << setw( 16 )<< "Genero" << setw( 14 ) << "Nombre" << setw( 16 ) << "fecha"<< right
       << setw( 10 ) << "telefono" << endl;
    leerDeArchivo.seekg( 0 );

    datosPacientes pacientess;
    leerDeArchivo.read( reinterpret_cast< char * >( &pacientess ), sizeof( datosPacientes ) );

    while ( !leerDeArchivo.eof() ) {
        if ( pacientess.obtenerCodigo() != 0 )
        mostrarLineap( archivoImprimirSalida, pacientess );
        leerDeArchivo.read( reinterpret_cast< char * >( &pacientess ), sizeof( datosPacientes ) );
    } //FIN DE WHILE

} //FIN DE LA FUNCION -IMPRIMIR REGISTRO-
void mostrarLineap( ostream &salida, const datosPacientes &registro )
{
   salida << left << setw( 10 ) << registro.obtenerCodigo()
          << setw( 16 ) << registro.obtenerApellido().data()
          << setw( 14 ) << registro.obtenerNombre().data()
          << setw( 16 ) << registro.obtenerCorreo().data()
          << setw( 10 ) << setprecision( 2 ) << right << fixed<< showpoint << registro.obtenerSueldo() << endl;

}//FIN -MOSTRARLINEA-
void crearArchivoCreditop()
{
    ofstream creditoSalida( "pacientes.dat", ios::out | ios::binary );
    if ( !creditoSalida ) {
      cerr << "No se pudo abrir el archivo." << endl;
      exit( 1 );
    }
    datosPacientes empleadoEnBlanco;
    for ( int i = 0; i < 100; i++ )
        creditoSalida.write(reinterpret_cast< const char * >( &empleadoEnBlanco ), sizeof( datosPacientes ) );
}
void nuevoRegistrop( fstream &insertarEnArchivo )
{
    int codigo = obtenernCodigop( "\nEscriba el Codigo del empleado " );
    insertarEnArchivo.seekg( ( codigo - 1 ) * sizeof( datosPacientes ) );
    datosPacientes pacientess;
    insertarEnArchivo.read( reinterpret_cast< char * >( &pacientess ), sizeof( datosPacientes ) );

    if ( pacientess.obtenerCodigo() == 0 ) {
        char apellido[ 15 ];
        char nombre[ 10 ];
        char correo[ 15 ];
        int sueldo;
        cout<<"Escriba el Genero del paciente: ";
        cin>> setw( 15 ) >> apellido;
        cout<<"Escriba el Nombre del paciente: ";
        cin>> setw( 10 ) >> nombre;
        cout<<"Escriba el Fecha de nacimiento del paciente ";
        cin>> setw( 15 ) >> correo;
        cout<<"Escriba el telefono del paciente ";
        cin>> sueldo;
        pacientess.establecerApellido( apellido );
        pacientess.establecerNombre( nombre );
        pacientess.establecerCorreo( correo );
        pacientess.establecerSueldo( sueldo );
        pacientess.establecerCodigo( codigo );

        insertarEnArchivo.seekp( ( codigo - 1 ) * sizeof( datosPacientes ) );
        insertarEnArchivo.write( reinterpret_cast< const char * >( &pacientess ), sizeof( datosPacientes ) );
        cout<<"\n Empleado agregado Exitosamente..."<<endl;

    } //FIN IF
    else
        cerr << "El paciente con codigo #" << codigo << " ya contiene informacion.\n" << endl;

} //FIN REGISTRO
int obtenernCodigop( const char * const indicador )
{
   int codigo;
    do {
      cout << indicador << "(1 - 100): ";
      cin >> codigo;

    } while ( codigo < 1 || codigo > 100 );

   return codigo;

} //FIN -OBTENERCODIGO-
void modificarRegistrop( fstream &actualizarArchivo )
{
    int opcionAc=0;
    cout<<"\nEscoja opcion a Actualizar: \n 1. Telefono\n 2. Nombre\n 3. Estatus \n 4. Fecha\n  R - ";
    cin>>opcionAc;

    if (opcionAc == 1){
        int codigo = obtenernCodigop( "\nEscriba el codigo del empleado que desea Modifcar" );

        actualizarArchivo.seekg(( codigo - 1 ) * sizeof( datosPacientes ));

        datosPacientes pacientess;
        actualizarArchivo.read( reinterpret_cast< char * >( &pacientess ), sizeof( datosPacientes ) );

        if (pacientess.obtenerCodigo() != 0 ) {
            mostrarLineap( cout, pacientess );
            cout << "\nEscriba aumento (+) o descuento (-): ";
            double cambiosu;
            cin >> cambiosu;
            double sueldoAnterior = pacientess.obtenerSueldo();
            pacientess.establecerSueldo( sueldoAnterior + cambiosu );
            mostrarLineap( cout, pacientess );

            actualizarArchivo.seekp(( codigo - 1 ) * sizeof( datosPacientes ));

            actualizarArchivo.write(reinterpret_cast< const char * >( &pacientess ), sizeof( datosPacientes ) );
        }

    }else if (opcionAc== 2){
        int codigo = obtenernCodigop( "\nEscriba el codigo del empleado que desea Modifcar" );

        actualizarArchivo.seekg(( codigo - 1 ) * sizeof( datosPacientes ));

        datosPacientes pacientess;
        actualizarArchivo.read( reinterpret_cast< char * >( &pacientess ), sizeof( datosPacientes ) );

        //ACTUALIZAR EL REGISTRO
        if (pacientess.obtenerCodigo() != 0 ) {
            mostrarLineap( cout, pacientess );
            cout << "\nEscriba el nuevo Nombre: ";
            string nombre;
            cin >> nombre;

            string nombreAnterior = pacientess.obtenerNombre();
            pacientess.establecerNombre( nombre );
            mostrarLineap( cout, pacientess );

            actualizarArchivo.seekp(( codigo - 1 ) * sizeof( datosPacientes ));
            actualizarArchivo.write(reinterpret_cast< const char * >( &pacientess ), sizeof( datosPacientes ) );
        }
    }else if(opcionAc == 3){
        int codigo = obtenernCodigop( "\nEscriba el codigo del paciente que desea Modifcar" );

        actualizarArchivo.seekg(( codigo - 1 ) * sizeof( datosPacientes ));

        datosPacientes pacientess;
        actualizarArchivo.read( reinterpret_cast< char * >( &pacientess ), sizeof( datosPacientes ) );

        if (pacientess.obtenerCodigo() != 0 ) {
                mostrarLineap( cout, pacientess );
                cout << "\nEscriba el nuevo Estatus: ";
                string apellido;
                cin >> apellido;

                string apellidoAnterior = pacientess.obtenerApellido();
                pacientess.establecerApellido( apellido );
                mostrarLineap( cout, pacientess );

                actualizarArchivo.seekp(( codigo - 1 ) * sizeof( datosPacientes ));

                actualizarArchivo.write(reinterpret_cast< const char * >( &pacientess ), sizeof( datosPacientes ) );
        }
    }else if(opcionAc == 4){
        int codigo = obtenernCodigop( "\nEscriba el codigo del paciente que desea Modifcar" );

        actualizarArchivo.seekg(( codigo - 1 ) * sizeof( datosPacientes ));

        datosPacientes pacientess;
        actualizarArchivo.read( reinterpret_cast< char * >( &pacientess ), sizeof( datosPacientes ) );

        if (pacientess.obtenerCodigo() != 0 ) {
                mostrarLineap( cout, pacientess );
                cout << "\nEscriba el nuevo Correo: ";
                string correo;
                cin >> correo;

                string correoAnterior = pacientess.obtenerCorreo();
                pacientess.establecerCorreo( correo );
                mostrarLineap( cout, pacientess );

                actualizarArchivo.seekp(( codigo - 1 ) * sizeof( datosPacientes ));

                actualizarArchivo.write(reinterpret_cast< const char * >( &pacientess ), sizeof( datosPacientes ) );
        }
    }

} //FIN DE -ACTUALIZAR REGISTRO-
void eliminarRegistrop( fstream &eliminarDeArchivo )
{
    int codigo = obtenernCodigop( "\nEscriba el codigo del paciente a Eliminar" );
    eliminarDeArchivo.seekg( ( codigo - 1 ) * sizeof( datosPacientes ) );
    datosPacientes pacientess;
    eliminarDeArchivo.read( reinterpret_cast< char * >( &pacientess ), sizeof( datosPacientes ) );

    if ( pacientess.obtenerCodigo() != 0 ) {
        datosPacientes clienteEnBlanco;
        eliminarDeArchivo.seekp( ( codigo - 1 ) * sizeof( datosPacientes ) );
        eliminarDeArchivo.write( reinterpret_cast< const char * >( &clienteEnBlanco ), sizeof( datosPacientes ) );

      cout << " El paciente con #" << codigo << " eliminada Exitosamente.\n";

   } //FIN IF

   //ERROR SI NO EXISTE
   else
      cerr << "El paciente con #" << codigo << " esta vacia.\n";

} //FIN -ELIMINARREGISTRO-
void consultarRegistrop( fstream &leerDeArchivo )
{
    cout << left << setw( 10 ) << "\nCodigo" << setw( 16 ) << " Genero" << setw( 14 ) << " Nombre" << setw( 16 ) << " fecha" << right << setw( 10 ) << " telefono" << endl;
    leerDeArchivo.seekg( 0 );
    datosPacientes pacientess;
    leerDeArchivo.read( reinterpret_cast< char * >( &pacientess ), sizeof( datosPacientes ) );
    while ( !leerDeArchivo.eof() ) {
        if ( pacientess.obtenerCodigo() != 0 )
            mostrarLineaPantallap(pacientess);
            leerDeArchivo.read( reinterpret_cast< char * >( &pacientess ), sizeof( datosPacientes ) );

   } //FIN WHILE
 cout<<"\n";
    system("pause");
} //FIN CONSULTAR REGISTRO
void mostrarLineaPantallap( const datosPacientes &registro )
{
   cout << left <<" "<< setw( 10 ) << registro.obtenerCodigo()
          << setw( 16 ) << registro.obtenerApellido().data()
          << setw( 14 ) << registro.obtenerNombre().data()
          << setw( 16 ) << registro.obtenerCorreo().data()
          << setw( 10 ) << setprecision( 2 ) << right << fixed
          << showpoint << registro.obtenerSueldo() << endl;

} //FIN -MOSTRARLINEAENOANTALLA-

Paciente::~Paciente()
{
    //dtor
}
