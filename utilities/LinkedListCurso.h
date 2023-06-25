#pragma once
#include "../models/Curso.h"
#include <iostream>

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

  void printList(Node *n) {
    int counter = 1; // Variable de contador
    while (n != nullptr) {
      cout << counter << ". " << n->Value.getNombre() << endl;
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
};
