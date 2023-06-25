#pragma once
#include <string>
#include <vector>
using namespace std;

class Alumno {
private:
  string nombre;
  string contra;
  string aula;
  string grado;
  string dni;
  string ExisteError;
  vector<string> cursos;

public:
  Alumno() {
    // Constructor por defecto
  }
  Alumno(const string &error) { this->ExisteError = error; }
  Alumno(const string &nombre, const string &contra, const string &aula,
         const string &grado, const string &dni) {
    this->nombre = nombre;
    this->contra = contra;
    this->aula = aula;
    this->grado = grado;
    this->dni = dni;
  }
  Alumno(const string &nombreAlumno, const string &contrasena,
         const string &aulaAlumno, int gradoAlumno, const string &dniAlumno,
         const vector<string> &cursosAlumno) {
    nombre = nombreAlumno;
    aula = aulaAlumno;
    grado = gradoAlumno;
    dni = dniAlumno;
    cursos = cursosAlumno;
    contra = contrasena;
  }

  // Getters y setters para los atributos

  string getError() { return ExisteError; }
  string getNombre() { return nombre; }

  void setNombre(const string &nuevoNombre) { nombre = nuevoNombre; }
  string getContra() { return contra; }
  void setContra(const string &contrasena) { contra = contrasena; }

  string getAula() { return aula; }

  void setAula(const string &nuevaAula) { aula = nuevaAula; }

  string getGrado() { return grado; }

  void setGrado(string nuevoGrado) { grado = nuevoGrado; }

  string getDni() { return dni; }

  void setDni(const string &nuevoDni) { dni = nuevoDni; }

  vector<string> getCursos() { return cursos; }

  void setCursos(const vector<string> &nuevosCursos) { cursos = nuevosCursos; }
};
