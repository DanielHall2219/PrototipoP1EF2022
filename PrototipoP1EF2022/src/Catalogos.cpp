#include "Catalogos.h"
#include "Paciente.h"
#include "Examen.h"
#include "Empleados.h"
#include "Usuarios.h"
#include <iostream>
#include <ctime>
#include <vector>

using namespace std;


int escribirOpcionD();
enum Opciones { empleados = 1, paciente, examen, FIN };

Catalogos::Catalogos()
{
    int opcion=0;
    while (( opcion = escribirOpcionD() ) != FIN)
    {
        switch ( opcion ) {
            case empleados:
                {
                    Empleados claseEmpleados;
                }
            break;
            case paciente:
                {
                    Paciente clasePaciente;
                }
            break;
            case examen:
                {
                    Examen clasePaciente;
                }
            break;
        }
    }
}

int escribirOpcionD(){
    system("cls");
    system("color F");

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
    cout << "Hoy " << dia_semana[time->tm_wday] << ", ";
    cout << time->tm_mday << " de " << mes[time->tm_mon] << " del " << year << endl;
    cout << time->tm_hour << ":" << time->tm_min << ":" << time->tm_sec << endl;

    cout<<"\t\t\t---------------------------------------------------------------"<<endl;
	cout<<"\t\t\t |   SUBMENU 9959-21-1395 - Daniel Alexander Hall Alvarez  |"<<endl;
	cout<<"\t\t\t---------------------------------------------------------------"<<endl;

    cout<< "\n\t\t\t  1. Empleado" << endl
        << "\t\t\t  2. Paciente" << endl
        << "\t\t\t  3. Examen" << endl
        << "\t\t\t  4. Salir del Sistema" << endl
        <<"\n\t\t\t---------------------------------"<<endl
        << "\n\t\t\tIngrese su opcion: ";
   int opcionMenu;
   cin >> opcionMenu;

   return opcionMenu;

}

Catalogos::~Catalogos()
{
    //dtor
}
