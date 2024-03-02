#ifndef LAB7_NODE_H
#define LAB7_NODE_H


#include <string>
using namespace std;

class Node {
public:
    Node(string);
    ~Node();     // rule of three
    Node(const Node &copyOBJ);
    int height;
    string key;
    Node* left;
    Node* right;
    Node* parent;
};


#endif
