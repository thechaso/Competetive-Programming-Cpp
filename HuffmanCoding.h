#include <bits/stdc++.h>
using namespace std;
#define ll long long

//Binary Tree Node
struct Node
{
    int data;//the number of times char occurs in string
    char ch;//char value of node, sometimes it will be blank
    Node* left;
    Node* right;
};

//returns a new node
Node* createNewNode(char ch, int data, Node* left, Node* right)
{
    Node* node = new Node();
    node->ch = ch;
    node->data = data;
    node->left = left;
    node->right = right;
    return node;
}

map<char, string> huffmanCodes;//will store answers to compression of each char
//will fill out map containing compressed codes
void encode(Node* root, string str, map<char, string> huffmanCode)
{
    if (root == NULL) return;//if the root itself is NULL, stop
    if (!root->right && !root->left) {//if we have reached a leaf node
        huffmanCodes[root->ch] = str;//update map
        return;
    }
    encode(root->left, str + "0", huffmanCode);//traverse left
    encode(root->right, str + "1", huffmanCode);//traverse right
}

//use the coded and compressed string to backtrack and derive original string
void decode(Node* root, int ind, string str)
{
    if (root == NULL) return;
    if (!root->left && !root->right) {
        cout << root->ch;
        return;
    }
    ind++;
    if(str[ind] == 0) decode(root->left, ind, str);
    else decode(root->right, ind, str);
}

//compare nodes for priority
struct comp
{
    bool operator()(Node* node, Node* other)
    {
        node->data > other->data;
    }
};

int run()
{
    string text;
    cin >> text;
    map<char, int> freq;
    for (char i : text) {
        if (!freq[i]) freq[i] = 1;
        else freq[i]++;
    }
    priority_queue<Node*, vector<Node*>, comp> pq;
    for (auto p : freq) {
        Node* newNode = createNewNode(p.first, p.second, NULL, NULL);
        pq.push(newNode);
    }
    while (pq.size() != 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        int sum = left->data + right->data;//sum up minimum weighted nodes
        Node* newNode = createNewNode('\0', sum, left, right);//create new node with blank ch attribute
        pq.push(newNode);//push new node into pq
    }
    Node* root = pq.top();
    map<char, string> huffmanCode;
    encode(root, "", huffmanCode);
    cout << "Huffman Codes are: " << endl;
    for (auto p: huffmanCodes) {
        cout << p.first << " " << p.second << endl;
    }
    cout << "Original String was: " << endl << text << endl;
    string str = "";
    for (char ch : text) str += huffmanCodes[ch];
    cout << "Encoded string is: " << endl << str << endl;
    int ind = -1;
	cout << "Decoded string is: " << endl;
	while (ind < str.size() - 2) {
		decode(root, ind, str);
	}
}

