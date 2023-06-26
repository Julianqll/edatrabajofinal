#pragma once

#include "../models/Nota.h"
#include <fstream>
#include <iostream>
using namespace std;

class VentanaNota {
private:
  Nota nota;

public:
  VentanaNota() {}
  void Inicio() {
    //  Abrir el archivo de nota
    // Alumno Curso n1 n2 n3 prom
    ofstream archivo("db/nota.txt", ios::app);
    string alumno, curso;
    int n1, n2, n3;
    float prom;
    cout << "\033[2J\033[0;0H";
    cout << "===========================" << endl;
    cout << "\t\tVentana - Nota" << endl;
    cout << "===========================" << endl;
    cin.ignore();
    cout << "\nNombre de alumno: ";
    cin >> alumno;
    cout << "Curso: ";
    cin >> curso;
    cout << "Nota 1: ";
    cin >> n1;
    cin.ignore();
    cout << "Nota 2: ";
    cin.ignore();
    cin >> n2;
    cin.ignore();
    cout << "Nota 3: ";
    cin >> n3;
    float promedio = (n1 + n2 + n3) / 3.0;
    cout << "Promedio: " << promedio;

    nota.setAlumno(alumno);
    nota.setCurso(curso);
    nota.setNota1(n1);
    nota.setNota2(n2);
    nota.setNota3(n3);
    nota.setPromedio(promedio);

    if (archivo.is_open()) {
      // El archivo se abrió correctamente
      archivo << alumno << " " << curso << " " << n1 << " " << n2 << " " << n3
              << " " << promedio << endl;
    } else {
      // Error al abrir el archivo
      cout << "No se puedo abrir el archivo";
    }
  }
};