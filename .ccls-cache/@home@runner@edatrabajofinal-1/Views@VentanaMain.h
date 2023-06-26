#pragma once
#include "../models/Alumno.h";
#include "../models/Tutor.h";
#include "VentanaEstudianteInicio.h"
#include "VentanaTutorInicio.h"
#include <algorithm>
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
  ////////////////////////// VALIDACIONES ///////////////////////////
  // Función para validar y obtener el grado correcto
  string validarGrado() {
    string grado;
    cout << "Ingrese el grado [Ejemplo: Primer]: ";
    cin >> grado;

    // Convertir el grado a mayúsculas
    transform(grado.begin(), grado.end(), grado.begin(), ::toupper);

    // Validar y obtener el grado correcto
    if (grado == "PRIMER" || grado == "SEGUNDO" || grado == "TERCERO" ||
        grado == "CUARTO" || grado == "QUINTO" || grado == "SEXTO") {
      return grado;
    } else {
      std::cout
          << "\n=> Grado inválido. Por favor, ingrese uno de los siguientes: "
             "=> Primer, Segundo, Tercero, Cuarto, Quinto, Sexto.\n"
          << std::endl;
      // Llamar recursivamente a la función para obtener un grado válido
      return validarGrado();
    }
  }

  // Validar DNI, que tenga 8 digitos y todos sean numeros enteros
  bool validarDNI(const std::string &dni) {
    if (dni.length() != 8)
      return false;

    for (char c : dni) {
      if (!isdigit(c))
        return false;
    }

    return true;
  }

  Alumno iniciarSesionAlumno() {
    std::string nombreUsuario;
    std::string contraseña;
    // cout << "\033[2J\033[0;0H";
    std::cout << "\nIngrese su nombre de usuario: ";
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
    std::cout << "\nIngrese su nombre de usuario: ";
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
    bool dniValido = false;

    std::cout << "Ingrese un nombre de usuario: ";
    std::cin >> nombreUsuario;

    std::cout << "Ingrese una contraseña: ";
    std::cin >> contraseña;

    std::cout << "Ingrese el aula: ";
    std::cin >> aula;

    // Validar el grado correcto
    grado = validarGrado();

    // Validar el ingreso del DNI
    do {
      std::cout << "Ingrese el DNI: ";
      std::cin >> dni;

      if (!validarDNI(dni)) {
        std::cout
            << "\n=> DNI inválido. El DNI debe contener 8 dígitos enteros."
            << std::endl;
      } else {
        dniValido = true;
      }
    } while (!dniValido);

    cout << "Importante!!!";
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
    int opcion;
    int contador = 0;

    do {
      cout << "\033[2J\033[0;0H";
      cout << "=============================" << endl;
      cout << "      AGENDA ESTUDIANTIL      " << endl;
      cout << "=============================" << endl;
      // Mostrar las opciones
      cout << "  1. Login - Alumno" << endl;
      cout << "  2. Login - Tutor" << endl;
      cout << "  3. Registrar nueva cuenta" << endl;
      cout << "  4. Salir" << endl;
      cout << "=============================" << endl;
      // Obtener la opción seleccionada
      cout << "\nIngrese su opción: ";
      cin >> opcion;
      cin.ignore(); // Limpiar el búfer de entrada

      cout << "\033[2J\033[0;0H";

      // Procesar la opción seleccionada
      switch (opcion) {
      case 1: {
        cout << "Has seleccionado 'Iniciar sesión Alumno'." << endl;
        Alumno alumno;
        int intentos = 0;

        while (intentos < 3) {
          alumno = iniciarSesionAlumno();

          if (alumno.getError() == "error") {
            cout << "\n=> Inicio de sesión fallido. Verifique sus credenciales."
                 << endl;
            intentos++;

            if (intentos == 2) {
              cout << "\n¡Último intento!" << endl;
            }

            cout << "=> Intentos: " << intentos << endl;
          } else {
            intentos =
                0; // Reiniciar el contador si el inicio de sesión fue exitoso
            break; // Salir del bucle si el inicio de sesión fue exitoso
          }
        }

        if (intentos == 3) {
          cout << "\nHas excedido el número máximo de intentos. Saliendo del "
                  "programa."
               << endl;
          exit(0);

        } else {
          VentanaEstudianteInicio ventanaEstudiante;
          ventanaEstudiante.setAlumno(alumno);
          ventanaEstudiante.Inicio(alumno);
        }

        break;
      }

      case 2: {
        cout << "Has seleccionado 'Iniciar sesión Tutor'." << endl;

        Tutor tutor;
        int intentos = 0;

        while (intentos < 3) {
          tutor = iniciarSesionTutor();

          if (tutor.getError() == "error") {
            cout << "\n=> Inicio de sesión fallido. Verifique sus credenciales."
                 << endl;
            intentos++;

            if (intentos == 2) {
              cout << "\n¡Último intento!" << endl;
            }

            cout << "=> Intentos: " << intentos << endl;
          } else {
            intentos =
                0; // Reiniciar el contador si el inicio de sesión fue exitoso
            break; // Salir del bucle si el inicio de sesión fue exitoso
          }
        }
        if (intentos == 3) {
          cout << "\nHas excedido el número máximo de intentos. Saliendo del "
                  "programa."
               << endl;
          exit(0);

        } else {
          VentanaTutorInicio ventanaTutor;
          ventanaTutor.setTutor(tutor);
          ventanaTutor.Inicio(tutor);
        }

        break;
      }

      case 3: {
        cout << "Has seleccionado 'Registrarse'." << endl;
        registrarUsuario();
      } break;
      case 4:
        cout << "Gracias por utilizar nuestro sistema. ¡Hasta luego!" << endl;
        break;
      default:
        cout << "=> Opción inválida. Por favor, selecciona una opción válida."
             << endl;
        contador++;
        cout << "=> Intento " << contador << endl;
        break;
      }

      if (contador >= 3) {
        cout << "=> Has excedido el número máximo de intentos. Saliendo del "
                "programa."
             << endl;
        break;
      }
    } while (opcion < 1 || opcion > 4);
  }
};