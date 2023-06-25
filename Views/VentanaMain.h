#pragma once
#include "../models/Alumno.h";
#include "../models/Tutor.h";
#include "VentanaEstudianteInicio.h"
#include "VentanaTutorInicio.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class VentanaMain {
public:
  VentanaMain() {}
  template <typename T>
  T iniciarSesion(const std::string &nombreUsuario,
                  const std::string &contrasena,
                  const std::string nombreArchivo) {

    std::ifstream archivo(nombreArchivo); // Abre el archivo en modo lectura

    if (!archivo) {
      std::cerr << "No se pudo abrir el archivo." << std::endl;
      return T("error");
    }

    std::string linea;
    while (std::getline(archivo, linea)) { // Lee una línea del archivo
      // Extrae el nombre de usuario y la contraseña de la línea
      std::istringstream iss(linea);
      std::string usuario;
      std::string clave;
      std::string aula;
      std::string grado;
      std::string dni;
      iss >> usuario >> clave >> aula >> grado >> dni;
      // Compara el nombre de usuario y la contraseña con los datos
      // proporcionados
      if (usuario == nombreUsuario && clave == contrasena) {
        archivo.close(); // Cierra el archivo

        return T(usuario, clave, aula, grado,
                 dni); // Devuelve un objeto Alumno con los datos encontrados
      }
    }

    archivo.close(); // Cierra el archivo

    return T("error"); // Devuelve un objeto Alumno vacío si el inicio de
                       // sesión falló
  }

  Alumno iniciarSesionAlumno() {
    std::string nombreUsuario;
    std::string contraseña;
    // cout << "\033[2J\033[0;0H";
    std::cout << "Ingrese su nombre de usuario: ";
    std::cin >> nombreUsuario;

    std::cout << "Ingrese su contraseña: ";
    std::cin >> contraseña;
    Alumno alumno;
    alumno = iniciarSesion<Alumno>(nombreUsuario, contraseña, "db/alumno.txt");
    return alumno;
  }
  Tutor iniciarSesionTutor() {
    std::string nombreUsuario;
    std::string contraseña;
    // cout << "\033[2J\033[0;0H";
    std::cout << "Ingrese su nombre de usuario: ";
    std::cin >> nombreUsuario;

    std::cout << "Ingrese su contraseña: ";
    std::cin >> contraseña;
    Tutor tutor;
    tutor = iniciarSesion<Tutor>(nombreUsuario, contraseña, "db/tutor.txt");
    return tutor;
  }
  void registrarUsuario() {
    std::string nombreUsuario;
    std::string contraseña;
    std::string aula;
    std::string grado;
    std::string dni;
    std::string eleccion;
    std::string path;

    std::cout << "Ingrese un nombre de usuario: ";
    std::cin >> nombreUsuario;

    std::cout << "Ingrese una contraseña: ";
    std::cin >> contraseña;

    std::cout << "Ingrese el aula: ";
    std::cin >> aula;
    
    std::cout << "Ingrese el grado: ";
    cin.ignore();
    std::cin >> grado;
    
    std::cout << "Ingrese el dni: ";
    std::cin >> dni;

    std::cout << "Ingrese 1 si es Alumno o 2 si es Tutor: ";
    std::cin >> eleccion;

    if (eleccion == "1") {
      path = "db/alumno.txt";
    } else {
      path = "db/tutor.txt";
    }

    std::ofstream archivo(path, std::ios::app);
    if (!archivo) {
      std::cerr << "No se pudo abrir el archivo." << std::endl;
      return;
    }
    // Registrar al nuevo usuario
    archivo << nombreUsuario << " " << contraseña << " " << aula << " " << grado
            << " " << dni << std::endl;
    archivo.close();

    std::cout
        << "Registro exitoso. El usuario ha sido registrado correctamente."
        << std::endl;
  }

  void iniciar() {
    cout << "\033[2J\033[0;0H";

    cout << "=============================" << endl;
    cout << "           AGENDA            " << endl;
    cout << "=============================" << endl;
    // Mostrar las opciones
    cout << "1. Estudiante" << endl;
    cout << "2. Tutor" << endl;
    cout << "3. Registrarse" << endl;
    cout << "4. Salir" << endl;

    // Obtener la opción seleccionada
    int opcion;
    cout << "Ingrese su opción: ";
    cin >> opcion;
    cout << "\033[2J\033[0;0H";
    // Procesar la opción seleccionada
    switch (opcion) {
    case 1: {
      cout << "Has seleccionado 'Iniciar sesión Alumno'." << endl;
      int contador = 0;

      Alumno alumno = iniciarSesionAlumno();
      if (alumno.getError() == "error") {
        std::cout << "Inicio de sesión fallido. Verifique sus credenciales."
                  << std::endl;

        contador++;
        cout << "Intentos :" << contador << endl;
      }

      VentanaEstudianteInicio ventanaEstudiante;
      ventanaEstudiante.setAlumno(alumno);
      ventanaEstudiante.Inicio(alumno);
    } break;
    case 2: {
      cout << "Has seleccionado 'Iniciar sesión Tutor'." << endl;

      Tutor tutor = iniciarSesionTutor();
      if (tutor.getError() == "error") {
        std::cout << "Inicio de sesión fallido. Verifique sus credenciales."
                  << std::endl;
        VentanaTutorInicio ventanaTutor;
        ventanaTutor.setTutor(tutor);
        ventanaTutor.Inicio(tutor);
      }
    } break;
    case 3: {
      cout << "Has seleccionado 'Registrarse'." << endl;
      registrarUsuario();
    } break;
    case 4:
      cout << "Gracias por utilizar nuestro sistema. ¡Hasta luego!" << endl;
      break;
    default:
      cout << "Opción inválida. Por favor, selecciona una opción válida."
           << endl;
      break;
    }
  }
};