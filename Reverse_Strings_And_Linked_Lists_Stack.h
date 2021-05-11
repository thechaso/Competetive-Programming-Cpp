#include <iostream>
#include <stack>
using namespace std;

//reverse string using stack
string reverse_string(string word) {
    stack<char> s;
    for (char i : word) {
        s.push(i);
    }
    int index = 0;
    while (!s.empty()) {
        char cur = s.top();
        word[index++] = cur;
        s.pop();
    }
    return word;
}

//reverse linked list using stack
struct Node {
    int data;
    Node* next;
};

Node* head = NULL;

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

void deleteFirst() {
    Node *second = head->next;
    head->next = NULL;
    head = second;
}

void print_reverse_linked_list() {
    stack<Node*> s;
    Node* cur = head;
    while (cur != NULL) {
        s.push(cur);
        cur = cur->next;
    }
    while (!s.empty()) {
        Node* curStackElem = s.top();
        cout << curStackElem->data << " ";
        s.pop();
    }
}

void reverse_linked_list() {
    stack<Node*> s;
    Node* cur = head;
    while (cur != NULL) {
        s.push(cur);
        cur = cur->next;
    }
    Node* temp = s.top();
    head = temp;
    s.pop();
    while (!s.empty()) {
        temp->next = s.top();
        s.pop();
        temp = temp->next;
    }
    temp->next = NULL;
}

int run() {
    cout << reverse_string("abcd") << endl;
    Node* ptr = new Node();
    ptr->data = 1;
    ptr->next = NULL;
    head = ptr;
    addFirst(0);
    addLast(2);
    reverse_linked_list();
    print_reverse_linked_list();
}

