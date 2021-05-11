#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};
Node* head = NULL;

void addFirst(int d) {
    Node* node = new Node();
    node->data = d;
    node->prev = NULL;
    if (head == NULL) {
        node->next = NULL;
        head = node;
        return;
    }
    node->next = head;
    head = node;
}

void addLast(int d) {
    Node* tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    Node* node = new Node();
    node->data = d;
    node->next = NULL;
    if (head == NULL) {
        node->prev = NULL;
        head = node;
        return;
    }
    tail->next = node;
    node->prev = tail;
}

void printInOrder() {
    Node* cur = head;
    while (cur != NULL) {
        cout << cur->data << " ";
        cur = cur->next;
    }
}

void deleteFirst() {
    Node* second = head->next;
    head->next = NULL;
    second->prev = NULL;
    head = second;
}

void deleteLast() {
    Node* secondLast = head;
    while (secondLast->next->next != NULL) {
        secondLast = secondLast->next;
    }
    secondLast->next = NULL;
}

void printReverseOrder() {
    Node* tail = head;
    while (tail != NULL) {
        tail = tail->next;
    }
    while (tail != head) {
        cout << tail->data;
        tail = tail->prev;
    }
}

void doubly_linked_list() {
    Node* pointer = new Node();
    pointer->data =  2;
    pointer->next = NULL;
    pointer->prev = NULL;
    head = pointer;
    addFirst(1);
    addLast(3);
    printInOrder();
    printReverseOrder();
}


