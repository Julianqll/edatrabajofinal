#pragma once
#include "string"
using namespace std;
class Tarea {
private:
  string nombre;
  string Descripcion;
  string fecha;
  string curso;
  string estado;

public:
  Tarea() {}
  string getNombre() { return nombre; }

  // Setter para la descripción
  void setNombre(const string &nombre) { this->nombre = nombre; }
  string getDescripcion() { return Descripcion; }

  // Setter para la descripción
  void setDescripcion(const string &nuevaDescripcion) {
    Descripcion = nuevaDescripcion;
  }

  // Getter para el fecha
  string getFecha() { return fecha; }

  // Setter para el fecha
  void setFecha(const string &nuevaFecha) { fecha = nuevaFecha; }

  string getCurso() { return curso; }

  // Setter para el mes
  void setCurso(const string &nuevoCurso) { curso = nuevoCurso; }

  string getEstado() { return estado; }

  // Setter para el estado
  void setEstado (const string &nuevoEstado) {estado = nuevoEstado;}
};