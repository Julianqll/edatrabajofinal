#pragma once
#include "../models/Tutor.h"
#include "VentanaCurso.h"
#include <iostream>
using namespace std;

class VentanaTutorInicio {
public:
  Tutor tutor;

public:
  VentanaTutorInicio() {}
  Tutor getTutor() { return tutor; }
  void setTutor(Tutor tutor) { this->tutor = tutor; }
  void Inicio(Tutor tutor) {
   
    cout << "\033[2J\033[0;0H"; //Clear screen
    cout << "=============================" << endl;
    cout << "        Portada Tutor   " << endl;
    cout << "=============================" << endl;
    cout << "Nombre: " << tutor.getNombre() << endl;
    cout << "Seleccionar Curso: " << endl;
    cout << "1." << endl;
    cout << "2." << endl;
    cout << "3." << endl;
    cout << "Opcion: ";

    system("cls");
    VentanaCurso ventanaCurso;
    Curso curso;
    ventanaCurso.inicio(curso);

    // guardar la opcion como un indexido de la lista
  }
};