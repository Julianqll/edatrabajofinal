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

std::string reemplazarGuionesConEspacios(const std::string& texto) {
    std::string resultado = texto;
    size_t posicion = resultado.find('-');

    while (posicion != std::string::npos) {
        resultado.replace(posicion, 1, " ");
        posicion = resultado.find('-', posicion + 1);
    }

    return resultado;
}

std::string reemplazarEspaciosConGuiones(const std::string& texto) {
    std::string resultado = texto;
    size_t posicion = resultado.find(' ');

    while (posicion != std::string::npos) {
        resultado.replace(posicion, 1, "-");
        posicion = resultado.find(' ', posicion + 1);
    }

    return resultado;
}

class VentanaTarea {
public:
  Tarea tarea;

  VentanaTarea() {}

  Tarea getTarea() { return tarea; }

  void setTarea(Tarea newTarea) { this->tarea = newTarea; }

  void inicio(string nombreTarea, string tipoUsuario) {
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
      std::cout << "=> No se pudo abrir el archivo." << std::endl;
    }

    cout << "=====================================" << endl;
    cout << "  Tarea seleccionada: " << tarea.getNombre() << "      " << endl;
    cout << "=====================================" << endl;
    // Imprimir cada elemento en forma de lista
    cout << " Descripción: " << reemplazarGuionesConEspacios(tarea.getDescripcion()) << endl;
    cout << " Deadline: " << tarea.getFecha() << endl;
    cout << " Curso: " << tarea.getCurso() << endl;
    cout << " Estado: " << tarea.getEstado() << endl;
    cout << "=====================================" << endl;
    cout << endl;
    cout << " 1. Modificar estado de tarea" << endl;
    cout << " 2. Cerrar programa" << endl;
    int opcion;
    cout << "\nSeleccionar opcion: ";
    cin >> opcion;
    switch (opcion) {
    case 1: {
      if (tarea.getEstado() == "Hecho") {
        tarea.setEstado("Pendiente");
      } else {
        tarea.setEstado("Hecho");
      }
      // sobreescribir en el archivo y cambiar estado, donde el nombre de tarea
      // sea igual
      std::ifstream inputFile("db/tarea.txt");
      std::ofstream outputFile("db/tarea_mod.txt");

      if (inputFile && outputFile) {
        std::string line;
        while (std::getline(inputFile, line)) {
          std::istringstream iss(line);
          std::vector<std::string> fields;
          std::string field;
          while (iss >> field) {
            fields.push_back(field);
          }

          // Modifica los campos deseados
          // Ejemplo: cambia el estado a "Realizado" si la asignatura es "EDA"
          if (fields.size() >= 5 && fields[0] == tarea.getNombre()) {
            fields[4] = tarea.getEstado();
          }

          // Escribe los campos modificados en el archivo de salida
          for (const auto &field : fields) {
            outputFile << field << ' ';
          }
          outputFile << '\n';
        }

        std::cout << "Nota actualizada correctamente.\n";
      } else {
        std::cerr << "No se pudo abrir el archivo.\n";
      }
      inputFile.close();
      outputFile.close();

      std::remove("db/tarea.txt");
      std::rename("db/tarea_mod.txt", "db/tarea.txt");

      cout << "\033[2J\033[0;0H";

      VentanaTarea ventanaTarea;
      ventanaTarea.inicio(tarea.getNombre(), tipoUsuario);

    } break;
    case 2: {
      break;
    } break;
    default:
      break;
    }
  }
};