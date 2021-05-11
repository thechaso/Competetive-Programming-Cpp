#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Node
{
    char data;
    map<char, Node*> children;
    bool is_word;
};

Node* newNode(char data, bool is_word)
{
    Node* node = new Node();
    node->data = data;
    node->is_word = is_word;
    map<char, Node*> children;
    node->children = children;
    return node;
}

Node* root = newNode('\0', false);

void insertWord(string word)
{
    Node* cur = root;
    for (char c : word) {
        if (!cur->children[c]) cur->children[c] = newNode(c, false);
        cur = cur->children[c];
    }
    cur->is_word = true;
}

Node* getNode(string word)
{
    Node* cur = root;
    for (char c : word) {
        if (!cur->children[c]) return NULL;
        cur = cur->children[c];
    }
    return cur;
}

//return true if Trie contains the given word
bool contains(string word)
{
    Node* node = getNode(word);
    return node!= NULL && node->is_word;
}

//return true if a word starts with the given prefix
bool startsWith(string prefix)
{
    return getNode(prefix) != NULL;
}

//print all words in the Trie
//dfs
void printAllWords(Node* cur = root, string word = "")
{
    if (cur->is_word) {
        cout << word << endl;
    }
    for (pair<char, Node*> p : cur->children) {
        printAllWords(p.second, word + p.first);
    }
}

//print all words which start with the given prefix
void printPrefixedWords(string prefix)
{
    Node* cur = root;
    for (char c : prefix) {
        if(!cur->children[c]) {
            cout << "No such prefix input found";
            return;
        }
        cur = cur->children[c];
    }
    //cur will be root of sub-Trie containing all prefixed words
    printAllWords(cur, prefix);
}

int run()
{
    vector<string> words = {"floor", "flight", "flower", "dog", "door", "floors"};
    for (string i : words) insertWord(i);
    printPrefixedWords("flo");
}

