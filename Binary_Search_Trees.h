#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* getNewNode(int n) {
    Node* node = new Node();
    node->data = n;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* insertNode(Node* root, int x) {
    if (root == NULL) {
        root = getNewNode(x);
    }
    else if (root->data >= x) {
        root->left = insertNode(root->left, x);
    }
    else {
        root->right = insertNode(root->right, x);
    }
    return root;
}

bool searchNode(Node* root, int x) {
     if (root == NULL) return false;
     if (root->data == x) return true;
     else if (root->data <= x) return searchNode(root->left, x);
     else return searchNode(root->right, x);
}

int getminValue(Node* root) {
    Node* cur = root;
    while (cur->left != NULL) {
        cur = cur->left;
    }
    return cur->data;
}

int getMaxValue(Node* root) {
    Node* cur = root;
    while (cur->right != NULL) {
        cur = cur->right;
    }
    return cur->data;
}

//longest path from leaf to node
int getHeight(Node* node) {
    if (node == NULL) return -1;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return max(leftHeight, rightHeight) + 1;
}

//BFS
void LevelOrder(Node* root) {
    if (root == NULL) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* cur = q.front();
        cout << cur->data << " ";
        if (cur->left != NULL) {
            q.push(cur->left);
        }
        if (cur->right != NULL)  {
            q.push(cur->right);
        }
        q.pop();
    }
}

//forms of DFS Traversal

//root, left, right
void preOrder(Node* root) {
    if (root == NULL) return;
    cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
}
//left, root, right
void inOrder(Node* root) {
    if (root == NULL) return;
    inOrder(root->left);
    cout << root->data << " ";
    inOrder(root->right);
}
//left, right, root
void postOrder(Node* root) {
    if (root == NULL) return;
    inOrder(root->left);
    inOrder(root->right);
    cout << root->data << " ";
}

Node* deleteValue(Node* root, int value) {
    if (root == NULL) return root;
    else if (value < root->data) root->left = deleteValue(root->left, value);
    else if (value > root->data) root->right =  deleteValue(root->right, value);
    else {//we have found node to delete
        //0 children
        if (root->left == NULL && root->right == NULL) {
            delete root;
            root = NULL;
            return root;
        }
    //1 child
        else if (root->left == NULL) {
            Node* temp = root;
            root = root->right;
            delete temp;
            return root;
        }
        //1 child
        else if (root->right == NULL) {
            Node* temp = root;
            root = root->left;
            delete temp;
            return root;
        }
        //2 children
        else {
            //Node* temp = getminValue(root->right);
            //root->data = temp->data;
            //root->right = deleteValue(root->right, temp->data);
        }
    }
    return root;
}


int run() {
    Node* root = new Node();
    root->data = 11;
    root->left = NULL;
    root->right = NULL;
    insertNode(root, 15);
    insertNode(root, 10);
    insertNode(root, 20);
    insertNode(root, 8);
}


