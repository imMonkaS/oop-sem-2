#include "LinkedListSequence.h"

LinkedListSequence::LinkedListSequence() {
    head = nullptr;
    tail = nullptr;
}

LinkedListSequence::~LinkedListSequence() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

int LinkedListSequence::get(int index) {
    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->value;
}

int LinkedListSequence::get_size() {
    Node* current = head;
    int i = 0;
    while (current != nullptr) {
        Node* next = current->next;
        current = next;
        i++;
    }
    return i;
}

void LinkedListSequence::set(int index, int value) {
    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    current->value = value;
}

void LinkedListSequence::add(int value) {
    Node* new_node = new Node;
    new_node->value = value;
    new_node->next = nullptr;

    if (head == nullptr) {
        head = new_node;
        tail = new_node;
    }
    else {
        tail->next = new_node;
        tail = new_node;
    }
}
