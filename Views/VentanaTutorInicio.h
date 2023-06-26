#pragma once
#include "../models/Tutor.h"
#include "../utilities/LinkedListCurso.h"
#include "VentanaCurso.h"
#include "VentanaNota.h"
#include "VentanaReporte.h"
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

    vector<Tutor> tutoresLista;
    // vectores de TUTORES
    std::ifstream archivoTutores("db/tutor.txt");

    if (archivoTutores.is_open()) {
      std::string linea;

      // Leer cada línea del archivo
      while (std::getline(archivoTutores, linea)) {
        std::istringstream iss(linea);
        std::string nombre, contra, aula, grado, dni;

        // Leer los valores separados por espacios en la línea
        if (iss >> nombre >> contra >> aula >> grado >> dni) {
          // Crear un objeto Tarea con los valores leídos
          Tutor nuevoTutor;
          nuevoTutor.setNombre(nombre);
          nuevoTutor.setAula(aula);
          nuevoTutor.setGrado(grado);
          nuevoTutor.setDni(dni);

          tutoresLista.push_back(nuevoTutor);
        }
      }

      // Cerrar el archivo
      archivoTutores.close();
    } else {
      std::cout << "No se pudo abrir el archivo." << std::endl;
    }

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

          vector<Tutor> tutoresListaCurso;
          // asignar tutores
          std::vector<std::string> tutoresListString = stringToList(tutores);
          // mejorar busqueda
          for (const auto &itemString : tutoresListString) {
            for (auto &item : tutoresLista) {
              if (itemString == item.getNombre()) {
                tutoresListaCurso.push_back(item);
              }
            }
          }
          nuevoCurso.setTutores(tutoresListaCurso);

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
    cout << "=============================" << endl;

    int opcion;
    // Aca El tutor escogera que ventana va a elegir
    cout << "\n1.Generar reporte para alumno " << endl;
    cout << "2.Seleccionar curso " << endl;
    cout << "3.Subir notas " << endl;
    cout << "\nSeleccionar opcion: ";
    cin >> opcion;
    switch (opcion) {
    case 1: {
      cout << "\033[2J\033[0;0H";
      VentanaReporte ventanareporte;
      ventanareporte.Inicio();
    } break;
    case 2: {
      cout << "\033[2J\033[0;0H";
      cout << "        Cursos    " << endl;
      cout << "======================" << endl;
      cout << "Seleccionar Curso: " << endl;
      listaCursos.printList(listaCursos.head, "tutor", tutor.getNombre());
      int opcion;
      cout << "Ingrese su opción: ";
      cin >> opcion;
      cout << "\033[2J\033[0;0H";
      // buscar y asignar el nombnre del curso de acuerdo a la posición
      Curso cursoBuscado =
          listaCursos.searchByPosition(listaCursos.head, opcion);
      VentanaCurso ventanaCurso;
      ventanaCurso.inicio(cursoBuscado.getNombre(), "tutor");
    } break;
    case 3: {
      cout << "\033[2J\033[0;0H";
      cout << "        Notas    " << endl;
      cout << "======================" << endl;
      VentanaNota ventanaNota;
      ventanaNota.Inicio();
      cout << "\033[2J\033[0;0H";
    } 
      break;
    default:
      break;
    }
  }
};