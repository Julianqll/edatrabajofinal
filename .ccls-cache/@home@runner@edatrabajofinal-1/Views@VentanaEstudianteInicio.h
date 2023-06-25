#pragma once
#include "../models/Alumno.h"
#include "../utilities/LinkedListCurso.h"
#include "VentanaCurso.h"
#include <iostream>
using namespace std;

class VentanaEstudianteInicio {

public:
  Alumno alumno;
  LinkedListCurso listaCursos = LinkedListCurso();

public:
  VentanaEstudianteInicio() {}
  Alumno getAlumno() { return alumno; }
  void setAlumno(Alumno alumno) { this->alumno = alumno; }
  void Inicio(Alumno alumno) {

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
    cout << "        Portada estudiante    " << endl;
    cout << "=============================" << endl;
    cout << "Nombre: " << alumno.getNombre() << endl;
    cout << "Aula: " << alumno.getAula() << endl;
    cout << "Grado: " << alumno.getGrado() << endl;
    cout << "DNI: " << alumno.getDni() << endl << endl << endl;
    cout << "        Cursos    " << endl;
    cout << "======================" << endl;
    cout << "Seleccionar Curso: " << endl;
    listaCursos.printList(listaCursos.head);
    int opcion;
    cout << "Ingrese su opción: ";
    cin >> opcion;
    cout << "\033[2J\033[0;0H";
    // Procesar la opción seleccionada
    // switch (opcion) {
    //}
    VentanaCurso ventanaCurso;
    Curso curso;
    ventanaCurso.inicio(curso);

    // guardar la opcion como un indexido de la lista
  }
};