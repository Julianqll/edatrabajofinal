#pragma once
#include "../models/Curso.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class LinkedListCurso {
private:
  class Node {
  public:
    Curso Value;
    Node *Next;
  };

public:
  Node *head; // Puntero al primer nodo de la lista

  LinkedListCurso() {
    head = nullptr; // Inicializar el puntero a nulo al crear la lista
  }

  /*void printList(Node *n) {
    int counter = 1; // Variable de contador
    while (n != nullptr) {
      cout << counter << ". " << n->Value.getNombre() << endl;
      n = n->Next;
      counter++;
    }
  }*/
  void printList(Node *n, string tipoInterfaz, string nombreProfesor) {
    int counter = 1; // Variable de contador
    while (n != nullptr) {
      string nombre = n->Value.getNombre();
      if (tipoInterfaz == "alumno") {
        vector<string> nombresAlumnos;
        for (auto &item : n->Value.getAlumnosMatriculados()) {
          nombresAlumnos.push_back(item.getNombre());
        }
        auto busqueda = std::find(nombresAlumnos.begin(), nombresAlumnos.end(),
                                  nombreProfesor);
        if (busqueda != nombresAlumnos.end()) {
          // Reemplazar los guiones ("-") por espacios (" ")
          replace(nombre.begin(), nombre.end(), '-', ' ');
          cout << counter << ". " << nombre << endl;
        }
      } else {
        vector<string> nombresTutores;
        for (auto &item : n->Value.getTutores()) {
          nombresTutores.push_back(item.getNombre());
        }
        auto busqueda = std::find(nombresTutores.begin(), nombresTutores.end(),
                                  nombreProfesor);
        if (busqueda != nombresTutores.end()) {
          // Reemplazar los guiones ("-") por espacios (" ")
          replace(nombre.begin(), nombre.end(), '-', ' ');
          cout << counter << ". " << nombre << endl;
        }
      }
      n = n->Next;
      counter++;
    }
  }

  void insertAtTheFront(Node **head, Curso newValue) {
    // 1.Prepare a newNode
    Node *newNode = new Node();
    newNode->Value = newValue;
    // 2. Put it in front of the current head
    newNode->Next = *head;
    // 3. Move head of the list to point to the newNode
    *head = newNode;
  }

  void insertAtTheEnd(Node **head, Curso newValue) {
    // 1.Prepare a newNode
    Node *newNode = new Node();
    newNode->Value = newValue;
    newNode->Next = nullptr;
    // 2. If Linked list is empty, newNode will be a head node
    if (*head == nullptr) {
      *head = newNode;
      return;
    }
    // 3. Find the last node
    Node *last = *head;
    while (last->Next != nullptr) {
      last = last->Next;
    }
    // 4. Insert newNode after last node (at the end)
    last->Next = newNode;
  }

  void insertAfter(Node *previous, Curso newValue) {
    // 1.Check if previous node is NULL
    if (previous == nullptr) {
      cout << "Previous can not be NULL";
      return;
    }
    // 2.Prepare a newNode
    Node *newNode = new Node();
    newNode->Value = newValue;
    // 3.Insert newNode after previous
    newNode->Next = previous->Next;
    previous->Next = newNode;
  }

  Curso searchByPosition(Node *head, int position) {
    // Variable para contar la posición actual
    int counter = 1;

    // Recorrer la lista hasta encontrar la posición deseada o llegar al final
    while (head != nullptr && counter < position) {
      head = head->Next;
      counter++;
    }

    // Verificar si se encontró el nodo en la posición deseada
    if (head != nullptr && counter == position) {
      return head->Value;
    } else {
      Curso curso;
      return curso; // No se encontró el nodo en la posición deseada
    }
  }
};
