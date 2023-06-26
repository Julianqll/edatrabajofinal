#pragma once
#include "../models/Alumno.h"
#include "../utilities/LinkedListCurso.h"
#include "VentanaCurso.h"
#include <cstdlib>
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

  vector<string> buscarValoresPorNombre(const string &nombre) {
    vector<string> lineasEncontradas;

    ifstream archivoEntrada("db/reporte.txt");
    if (!archivoEntrada.is_open()) {
      cerr << "No se pudo abrir el archivo." << endl;
      return lineasEncontradas;
    }

    string linea;
    while (getline(archivoEntrada, linea)) {
      istringstream iss(linea);
      string elemento;

      while (iss >> elemento) {
        if (elemento == nombre) {
          lineasEncontradas.push_back(linea);
          break;
        }
      }
    }

    archivoEntrada.close();

    return lineasEncontradas;
  }

  vector<string> buscarNotaPorNombre(const string &nombre) {
    vector<string> lineasEncontradas;

    ifstream archivoEntrada("db/nota.txt");
    if (!archivoEntrada.is_open()) {
      cerr << "No se pudo abrir el archivo." << std::endl;
      return lineasEncontradas;
    }

    string linea;
    while (getline(archivoEntrada, linea)) {
      std::istringstream iss(linea);
      std::string elemento;

      while (iss >> elemento) {
        if (elemento == nombre) {
          lineasEncontradas.push_back(linea);
          break;
        }
      }
    }

    archivoEntrada.close();

    return lineasEncontradas;
  }
  void Inicio(Alumno alumno) {
    vector<Alumno> alumnosLista;
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
          vector<Alumno> alumnosListaCurso;
          std::vector<std::string> alumnosListString = stringToList(alumnos);
          for (const auto &itemString : alumnosListString) {
            for (auto &item : alumnosLista) {
              if (itemString == item.getNombre()) {
                alumnosListaCurso.push_back(item);
              }
            }
          }
          nuevoCurso.setAlumnosMatriculados(alumnosListaCurso);
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

    system("clear");

    cout << "=============================" << endl;
    cout << "    Bienvenido estudiante    " << endl;
    cout << "=============================" << endl;
    cout << "    Nombre: " << alumno.getNombre() << endl;
    cout << "    Aula: " << alumno.getAula() << endl;
    cout << "    Grado: " << alumno.getGrado() << endl;
    cout << "    DNI: " << alumno.getDni() << endl;
    cout << "=============================" << endl;
    int opcion;
    cout << "------------------------------" << endl;
    cout << "          Opciones   " << endl;
    cout << "------------------------------" << endl;
    cout << "    1.Ver reportes" << endl;
    cout << "    2.Ver cursos" << endl;
    cout << "    3.Ver notas" << endl;
    cout << "------------------------------" << endl;
    cout << "\nSelecciona una opcion: ";
    cin >> opcion;
    // Creando las opciones

    switch (opcion) {
    case 1: {
      cout << "------------------------------" << endl;
      cout << "         Reportes" << endl;
      cout << "------------------------------" << endl;
      cout << "  Lista de reportes: " << endl;
      cout << endl;
      // logica reportes
      vector<std::string> lineasEncontradas =
          buscarValoresPorNombre(alumno.getNombre());
      if (lineasEncontradas.empty()) {
        std::cout << "\n=>  No se encontró ningún reporte." << std::endl;
      } else {
        for (const std::string &linea : lineasEncontradas) {
          std::cout << linea << std::endl;
        }
      }
    } break;

    case 2: {

      cout << "------------------------------" << endl;
      cout << "           Cursos" << endl;
      cout << "------------------------------" << endl;
      cout << endl;
      cout << "  Seleccionar Curso: " << endl;
      listaCursos.printList(listaCursos.head, "alumno", alumno.getNombre());
      int opcion;
      cout << "\n  Ingrese su opción: ";
      cin >> opcion;
      system("clear");
      // buscar y asignar el nombnre del curso de acuerdo a la posición
      Curso cursoBuscado =
          listaCursos.searchByPosition(listaCursos.head, opcion);
      VentanaCurso ventanaCurso;
      ventanaCurso.inicio(cursoBuscado.getNombre(), "alumno");

      // guardar la opcion como un indexido de la lista
    } break;
    case 3: {
      cout << "------------------------------" << endl;
      cout << "           Notas" << endl;
      cout << "------------------------------" << endl;
      cout << "  Lista de notas: " << endl;
      // logica notas
      std::vector<std::string> lineasEncontradas =
          buscarNotaPorNombre(alumno.getNombre());
      if (lineasEncontradas.empty()) {
        std::cout << "\n=>  No se encontró ninguna notas." << std::endl;
      } else {
        for (const std::string &linea : lineasEncontradas) {
          std::cout << linea << std::endl;
        }
      }
    } break;
    default:
      break;
    }
  }
};