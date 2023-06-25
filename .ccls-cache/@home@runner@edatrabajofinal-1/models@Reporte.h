#include <string>
using namespace std;

class Reporte {
private:
  string titulo;
  string descripcion;
  string dia, mes;

public:
  Reporte() {
    // Constructor por defecto
  }

  Reporte(const string &tituloReporte, const string &descripcionReporte) {
    titulo = tituloReporte;
    descripcion = descripcionReporte;
  }

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
};