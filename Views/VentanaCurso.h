#pragma once
#include "../models/Curso.h"
#include "../utilities/LinkedListCurso.h"
#include "../utilities/LinkedListTarea.h"
#include "VentanaTarea.h"
#include "iostream"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

std::vector<std::string> stringToList(const std::string &input) {
  std::vector<std::string> result;

  // Eliminar los corchetes "[" y "]" del string de entrada
  std::string data = input.substr(1, input.length() - 2);

  // Utilizar un stringstream para separar los elementos individuales por ","
  std::stringstream ss(data);
  std::string item;
  while (getline(ss, item, ',')) {
    // Eliminar los espacios en blanco alrededor de cada elemento
    item.erase(0, item.find_first_not_of(" "));
    item.erase(item.find_last_not_of(" ") + 1);

    // Agregar el elemento a la lista de strings
    result.push_back(item);
  }

  return result;
}

class VentanaCurso {
public:
  LinkedListTarea listaTareas = LinkedListTarea();
  LinkedListCurso listaCursos = LinkedListCurso();

  Curso curso;

  VentanaCurso() {}

  Curso getCurso() { return curso; }

  void setCurso(Curso curso) { this->curso = curso; }

  void inicio(string nombreCurso, string tipoUsuario) {

    // vectores alumnos, tutores
    vector<Alumno> alumnosLista;
    vector<Tutor> tutoresLista;

    // VECTORES DE ALUMNOS
    std::ifstream archivoAlumno("db/alumno.txt");

    if (archivoAlumno.is_open()) {
      std::string linea;

      // Leer cada línea del archivo
      while (std::getline(archivoAlumno, linea)) {
        std::istringstream iss(linea);
        std::string nombre, contra, aula, grado, dni;

        // Leer los valores separados por espacios en la línea
        if (iss >> nombre >> contra >> aula >> grado >> dni) {
          // Crear un objeto Tarea con los valores leídos
          Alumno nuevoAlumno;
          nuevoAlumno.setNombre(nombre);
          nuevoAlumno.setAula(aula);
          nuevoAlumno.setGrado(grado);
          nuevoAlumno.setDni(dni);

          alumnosLista.push_back(nuevoAlumno);
        }
      }

      // Cerrar el archivo
      archivoAlumno.close();
    } else {
      std::cout << "No se pudo abrir el archivo." << std::endl;
    }

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

    // rellenar linkedL de tareas con las del curso correspondiente
    //  Abrir el archivo de tareas
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
          if (nombre == nombreCurso) {
            curso.setNombre(nombreCurso);
            vector<Alumno> alumnosListaCurso;
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
            std::vector<std::string> alumnosListString = stringToList(alumnos);
            for (const auto &itemString : alumnosListString) {
              for (auto &item : alumnosLista) {
                if (itemString == item.getNombre()) {
                  alumnosListaCurso.push_back(item);
                }
              }
            }
            curso.setAlumnosMatriculados(alumnosListaCurso);
            curso.setTutores(tutoresListaCurso);
          }
        }
      }

      // Cerrar el archivo
      archivo.close();
    } else {
      std::cout << "No se pudo abrir el archivo." << std::endl;
    }

    std::ifstream archivoTarea("db/tarea.txt");

    if (archivoTarea.is_open()) {
      std::string linea;

      // Leer cada línea del archivo
      while (std::getline(archivoTarea, linea)) {
        std::istringstream iss(linea);
        std::string nombre, descripcion, fecha, curso, estado;

        // Leer los valores separados por espacios en la línea
        if (iss >> nombre >> descripcion >> fecha >> curso >> estado) {
          // Crear un objeto Tarea con los valores leídos
          Tarea nuevaTarea;
          nuevaTarea.setNombre(nombre);
          nuevaTarea.setDescripcion(descripcion);
          nuevaTarea.setFecha(fecha);
          nuevaTarea.setCurso(curso);
          nuevaTarea.setEstado(estado);

          // Insertar la tarea en la LinkedListTarea
          listaTareas.insertAtTheEnd(&listaTareas.head, nuevaTarea);
        }
      }

      // Cerrar el archivo
      archivoTarea.close();
    } else {
      std::cout << "No se pudo abrir el archivo." << std::endl;
    }

    cout << "  Curso seleccionado: " << curso.getNombre() << "      " << endl;
    cout << "================================" << endl << endl;

    if (tipoUsuario == "alumno") {
      // Imprimir cada elemento en forma de lista

      cout << "     Profesores    " << endl;
      cout << "=========================" << endl;
      int counter = 1;
      for (auto &item : curso.getTutores()) {
        cout << counter << ". " << item.getNombre() << endl;
        counter++;
      }

      cout << endl << endl;
      cout << "     Tareas    " << endl;
      cout << "=========================" << endl;
      listaTareas.printList(listaTareas.head, curso.getNombre());
      int opcion;
      cout << "Ingrese su la tarea que desea ver: ";
      cin >> opcion;
      cout << "\033[2J\033[0;0H";
      // buscar y asignar el nombnre de la tarea de acuerdo a la posición
      Tarea tareaBuscada =
          listaTareas.searchByPosition(listaTareas.head, opcion);
      VentanaTarea ventanaTarea;
      ventanaTarea.inicio(tareaBuscada.getNombre());
      
    } else {

      cout << "     Alumnos    " << endl;
      cout << "=========================" << endl;
      int counter = 1;
      for (auto &item : curso.getAlumnosMatriculados()) {
        cout << counter << ". " << item.getNombre() << endl;
        counter++;
      }
      cout << endl;
      // Imprimir cada elemento en forma de lista
      cout << "1. Generar reportes: " << endl;
      cout << "2. Generar notas: " << endl;
    }
  }
};