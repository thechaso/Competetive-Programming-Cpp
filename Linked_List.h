#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;
};

Node *head = NULL;

void addFirst(int d) {
    Node *ptr = new Node();
    ptr->data = d;
    ptr->next = head;
    head = ptr;
}

void addLast(int d) {
    Node *ptr = new Node();
    ptr->data = d;
    ptr->next = NULL;
    if (head == NULL) head = ptr;
    else {
        Node *cur = head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = ptr;
    }
}

void deleteLast() {
    Node *secondLast = head;
    while (secondLast->next->next != NULL) {
        secondLast = secondLast->next;
    }
    secondLast->next = NULL;
}

int getSize() {
    int listSize = 0;
    Node *cur = head;
    while (cur != NULL) {
        listSize++;
        cur = cur->next;
    }
    return listSize;
}

void deleteFirst() {
    Node *second = head->next;
    head->next = NULL;
    head = second;
}

void deleteAtIndex(int ind) {
    if (ind == 0) {
        deleteFirst();
        return;
    }
    if (ind == getSize() - 1) {
        deleteLast();
        return;
    }
    Node *cur = head;
    if (ind > getSize() - 1){
        cout << "Error, Index out of bounds" << endl;
        return;
    }
    for (int index = 0; index < ind - 1; index++) {
        cur = cur->next;
    }
    //cur -> nodeToDelete ->nextToDelete
    Node *nodeToDelete = cur->next;
    Node *nextToDelete = nodeToDelete->next;
    nodeToDelete->next = NULL;
    cur->next = NULL;
    cur->next = nextToDelete;
}

void reverseListIteratively() {
    Node *prevNode, *curNode, *nextNode;
    prevNode = NULL;
    curNode = head;
    while (curNode != NULL) {
        nextNode = curNode->next;
        curNode->next = prevNode;
        prevNode = curNode;
        curNode = nextNode;
    }
    head = prevNode;
}

Node* reverseListRecursively(Node *cur) {
    if (cur == NULL) return NULL;
    if (cur->next == NULL)  {
            head = cur;
            return cur;
    }
    else {
        Node *nextNode = cur->next;
        cur->next = NULL;
        Node *rest = reverseListRecursively(nextNode);
        nextNode->next = cur;
        head = nextNode;
        return rest;
    }
}

void print() {
    Node *cur = head;
    while (cur != NULL) {
        cout << cur->data << " ";
        cur = cur->next;
    }
}

int linked_list() {
    Node *pointer = new Node();
    pointer->data = 2;
    pointer->next = NULL;
    head = pointer;
    addFirst(1);
    addLast(3);
    print();
}

