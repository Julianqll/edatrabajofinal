#pragma once

#include "../models/Reporte.h"
#include <fstream>
#include <iostream>
using namespace std;

class VentanaReporte {
private:
  Reporte reporte;

public:
  VentanaReporte() {}
  void Inicio() {
    //  Abrir el archivo de reporte
    ofstream archivo("db/reporte.txt", ios::app);
    string titulo, descripcion, dia, mes, alumno, firma;
    cout << "\033[2J\033[0;0H";
    cout << "===========================" << endl;
    cout << "\t\tVentana - Reporte" << endl;
    cout << "===========================" << endl;
    cin.ignore();
    cout << "->  Nombre de alumno: ";
    cin >> alumno;
    cout << "->  Titulo del reporte: ";
    cin >> titulo;
    cin.ignore();
    cout << "->  Descripcion: ";
    cin.ignore();
    cin >> descripcion;
    cin.ignore();
    cout << "->  Dia: ";
    cin >> dia;
    cout << "->  Mes: ";
    cin >> mes;
    cout << "->  Firma: ";
    cin.ignore();
    cin >> firma;
    
    reporte.setTitulo(titulo);
    reporte.setDescripcion(descripcion);
    reporte.setDia(dia);
    reporte.setMes(mes);
    reporte.setAlumno(alumno);
    if (archivo.is_open()) {
      // El archivo se abrió correctamente
      archivo << alumno << " " << titulo << " " << descripcion << " " << dia
              << " " << mes << " " << firma << endl;
    } else {
      // Error al abrir el archivo
      cout << "No se puedo abrir el archivo";
    }
  }
};