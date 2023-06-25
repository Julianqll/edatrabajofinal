#pragma once
#include "Alumno.h"
#include "Tutor.h"
class Curso {
private:
  string nombre;
  vector<Tutor> tutores;
  vector<Alumno> alumnosMatriculados;

public:
  Curso() {
    // Constructor por defecto
  }

  Curso(const string &nombreCurso, const vector<Tutor> &tutoresCurso,
        const vector<Alumno> &alumnos) {
    nombre = nombreCurso;
    tutores = tutoresCurso;
    alumnosMatriculados = alumnos;
  }

  // Getter para el nombre del curso
  string getNombre() { return nombre; }

  // Setter para el nombre del curso
  void setNombre(const string &nuevoNombre) { nombre = nuevoNombre; }

  // Getter para los tutores del curso
  vector<Tutor> getTutores() { return tutores; }

  // Setter para los tutores del curso
  void setTutores(const vector<Tutor> &nuevosTutores) {
    tutores = nuevosTutores;
  }

  // Getter para los alumnos matriculados
  vector<Alumno> getAlumnosMatriculados() { return alumnosMatriculados; }

  // Setter para los alumnos matriculados
  void setAlumnosMatriculados(const vector<Alumno> &nuevosAlumnos) {
    alumnosMatriculados = nuevosAlumnos;
  }

  // Agregar un alumno a la lista de matriculados
  void agregarAlumno(const Alumno &alumno) {
    alumnosMatriculados.push_back(alumno);
  }
};