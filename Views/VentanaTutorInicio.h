#pragma once
#include "../models/Tutor.h"
#include "../utilities/LinkedListCurso.h"
#include "VentanaCurso.h"
#include <iostream>
using namespace std;

class VentanaTutorInicio {
public:
  Tutor tutor;
  LinkedListCurso listaCursos = LinkedListCurso();


public:
  VentanaTutorInicio() {}
  Tutor getTutor() { return tutor; }
  void setTutor(Tutor tutor) { this->tutor = tutor; }
  void Inicio(Tutor tutor) {

        std::ifstream archivo("db/curso.txt");

    if (archivo.is_open()) {
      std::string linea;

      // Leer cada línea del archivo
      while (std::getline(archivo, linea)) {
        std::istringstream iss(linea);
        std::string nombre, tutores, alumnos;

        // Leer los valores separados por espacios en la línea
        if (iss >> nombre >> tutores >> alumnos) {
          // Crear un objeto Tarea con los valores leídos
          Curso nuevoCurso;
          nuevoCurso.setNombre(nombre);
          // falta añadir filtros de cursos por alumno

          // Insertar la tarea en la LinkedListTarea
          listaCursos.insertAtTheEnd(&listaCursos.head, nuevoCurso);
        }
      }

      // Cerrar el archivo
      archivo.close();
    } else {
      std::cout << "No se pudo abrir el archivo." << std::endl;
    }

    cout << "\033[2J\033[0;0H"; // Clear screen
    cout << "=============================" << endl;
    cout << "      Bienvenido Tutor   " << endl;
    cout << "=============================" << endl;
    cout << "Nombre: " << tutor.getNombre() << endl;
    cout << "Aula: " << tutor.getAula() << endl;
    cout << "Grado: " << tutor.getGrado() << endl;
    cout << "DNI: " << tutor.getDni() << endl << endl << endl;
    cout << "        Cursos    " << endl;
    cout << "======================" << endl;
    cout << "Seleccionar Curso: " << endl;
    listaCursos.printList(listaCursos.head);
    int opcion;
    cout << "Ingrese su opción: ";
    cin >> opcion;
    cout << "\033[2J\033[0;0H";
    // buscar y asignar el nombnre del curso de acuerdo a la posición
    Curso cursoBuscado = listaCursos.searchByPosition(listaCursos.head, opcion);
    VentanaCurso ventanaCurso;
    ventanaCurso.inicio(cursoBuscado.getNombre(), "tutor");

    // guardar la opcion como un indexido de la lista
  }
};