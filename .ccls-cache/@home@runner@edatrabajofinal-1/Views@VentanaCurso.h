#pragma once
#include "../models/Curso.h"
#include "../utilities/LinkedListTarea.h"
#include "iostream"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class VentanaCurso {
public:
  LinkedListTarea listaTareas = LinkedListTarea();
  Curso curso;

  VentanaCurso() {}

  Curso getCurso() { return curso; }

  void setCurso(Curso curso) { this->curso = curso; }

  void inicio(Curso curso) {
    // rellenar linkedL de tareas con las del curso correspondiente
    //  Abrir el archivo de tareas
    std::ifstream archivo("db/tarea.txt");

    if (archivo.is_open()) {
      std::string linea;

      // Leer cada línea del archivo
      while (std::getline(archivo, linea)) {
        std::istringstream iss(linea);
        std::string nombre, descripcion, fecha, curso;

        // Leer los valores separados por espacios en la línea
        if (iss >> nombre >> descripcion >> fecha >> curso) {
          // Crear un objeto Tarea con los valores leídos
          Tarea nuevaTarea;
          nuevaTarea.setNombre(nombre);
          nuevaTarea.setDescripcion(descripcion);
          nuevaTarea.setFecha(fecha);
          nuevaTarea.setCurso(curso);

          // Insertar la tarea en la LinkedListTarea
          listaTareas.insertAtTheEnd(&listaTareas.head, nuevaTarea);
        }
      }

      // Cerrar el archivo
      archivo.close();
    } else {
      std::cout << "No se pudo abrir el archivo." << std::endl;
    }
    cout << "  Curso seleccionado: (<Curso>)    " << endl;
    cout << "================================" << endl;
    // Imprimir cada elemento en forma de lista
    listaTareas.printList(listaTareas.head);
    cout << endl << endl;
    cout << "     Lista pendientes    " << endl;
    cout << "=========================" << endl;
    cout << "1." << endl;
    cout << "2." << endl;
  }
};