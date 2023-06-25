#pragma once
#include "../models/Curso.h"
#include "../utilities/LinkedListCurso.h"
#include "../utilities/LinkedListTarea.h"
#include "iostream"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class VentanaTarea {
public:
  Tarea tarea;

  VentanaTarea() {}

  Tarea getTarea() { return tarea; }

  void setTarea(Tarea newTarea) { this->tarea = newTarea; }

  void inicio(string nombreTarea) {
    // rellenar linkedL de tareas con las del curso correspondiente
    //  Abrir el archivo de tareas

    std::ifstream archivoTarea("db/tarea.txt");

    if (archivoTarea.is_open()) {
      std::string linea;

      // Leer cada línea del archivo
      while (std::getline(archivoTarea, linea)) {
        std::istringstream iss(linea);
        std::string nombre, descripcion, fecha, curso, estado;

        // Leer los valores separados por espacios en la línea
        if (iss >> nombre >> descripcion >> fecha >> curso >> estado) {
          if (nombre == nombreTarea) {
            tarea.setNombre(nombre);
            tarea.setDescripcion(descripcion);
            tarea.setFecha(fecha);
            tarea.setCurso(curso);
            tarea.setEstado(estado);
          }
        }
      }

      // Cerrar el archivo
      archivoTarea.close();
    } else {
      std::cout << "No se pudo abrir el archivo." << std::endl;
    }

    cout << "  Tarea seleccionado: " << tarea.getNombre() << "      " << endl;
    cout << "================================" << endl;
    // Imprimir cada elemento en forma de lista
    cout << "Descripción: " << tarea.getDescripcion() << endl;
    cout << "Deadline: " << tarea.getFecha() << endl;
    cout << "Curso: " << tarea.getCurso() << endl;
  }
};