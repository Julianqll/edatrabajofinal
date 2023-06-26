#pragma once
#include <string>

using namespace std;

class Nota {
private:
  string alumno, curso;
  int nota1, nota2, nota3;
  float promedio;

public:
  Nota(){};
  Nota(string alumno, string curso, int nota1, int nota2, int nota3,
       float promedio) {
    this->alumno = alumno;
    this->curso = curso, 
    this->nota1 = nota1;
    this->nota2 = nota2;
    this->nota3 = nota3;
    this->promedio = promedio;
  }
  string getAlumno() { return alumno; }
  void setAlumno(const string &alumno) { this->alumno = alumno; }

  string getCurso() { return curso; }
  void setCurso(const string &curso) { this->curso = curso; }

  int getNota1() { return nota1; }
  void setNota1(int nota1) { this->nota1 = nota1; }

  int getNota2() { return nota2; }
  void setNota2(int nota2) { this->nota2 = nota2; }

  int getNota3() { return nota3; }
  void setNota3(int nota3) { this->nota3 = nota3; }

  float getPromedio() { return promedio; }
  void setPromedio(float promedio) { this->promedio = promedio; }
  
};