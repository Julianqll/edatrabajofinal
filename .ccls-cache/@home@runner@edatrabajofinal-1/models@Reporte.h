#include <string>
using namespace std;

class Reporte {
private:
  string titulo;
  string descripcion;
  string dia, mes;
  string alumno;
  string firma;

public:
  Reporte() {
    // Constructor por defecto
  }

  Reporte(const string &tituloReporte, const string &descripcionReporte) {
    titulo = tituloReporte;
    descripcion = descripcionReporte;
  }
  string getDia() { return dia; }
  void setDia(const string &dia) { this->dia = dia; }
  string getMes() { return mes; }
  void setMes(const string &mes) { this->mes = mes; }
  // Getter para el título del reporte
  string getTitulo() { return titulo; }

  // Setter para el título del reporte
  void setTitulo(const string &nuevoTitulo) { titulo = nuevoTitulo; }

  // Getter para la descripción del reporte
  string getDescripcion() { return descripcion; }

  // Setter para la descripción del reporte
  void setDescripcion(const string &nuevaDescripcion) {
    descripcion = nuevaDescripcion;
  }

  void setAlumno(const string alumno) { this->alumno = alumno; }
  string getAlumno() { return this->alumno; }

  void setFirma(const string firma) { this->firma = firma; }
  string getFirma() { return this->firma; }
};