#pragma once
#include "../models/Tarea.h"
#include <iostream>

using namespace std;

class LinkedListTarea {
private:
  class Node {
  public:
    Tarea Value;
    Node *Next;
  };

public:
  Node *head; // Puntero al primer nodo de la lista

  LinkedListTarea() {
    head = nullptr; // Inicializar el puntero a nulo al crear la lista
  }

  void printList(Node *n, string curso, string usuario) {
    int counter = 1; // Variable de contador
    while (n != nullptr) {
      if (n->Value.getCurso() == curso) {
        if (usuario == "alumno") {
          if (n->Value.getEstado() == "Hecho") {
            cout << counter << ". " << n->Value.getNombre() << " \u2713 (Hecho)"
                 << endl;

          } else {
            cout << counter << ". " << n->Value.getNombre() << " (Pendiente)"
                 << endl;
          }
        } else {
          cout << counter << ". " << n->Value.getNombre()
               << " - Deadline: " << n->Value.getFecha() << endl;
        }
      }
      n = n->Next;
      counter++;
    }
  }

  void insertAtTheFront(Node **head, Tarea newValue) {
    // 1.Prepare a newNode
    Node *newNode = new Node();
    newNode->Value = newValue;
    // 2. Put it in front of the current head
    newNode->Next = *head;
    // 3. Move head of the list to point to the newNode
    *head = newNode;
  }

  void insertAtTheEnd(Node **head, Tarea newValue) {
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

  void insertAfter(Node *previous, Tarea newValue) {
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

  Tarea searchByPosition(Node *head, int position) {
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
      Tarea tarea;
      return tarea; // No se encontró el nodo en la posición deseada
    }
  }
};
