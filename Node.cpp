
#include "Node.h"

Node::Node(string str){ //constructor
    height = 0;
    key = str;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

Node::~Node() { //destructor
    delete right;
    delete left;
}
Node::Node(const Node &copyOBJ) {
    key = copyOBJ.key;
    height = copyOBJ.height;
    // this is the beginning of the deep copy for the left side
    if (copyOBJ.left != nullptr) {
        left = new Node(*copyOBJ.left);
        left->parent = nullptr;
    } else {
        left = nullptr;
    }

    // this is the beginning of the deep copy for the right side
    if (copyOBJ.right != nullptr) {
        right = new Node(*copyOBJ.right);
        right->parent = nullptr;
    } else {
        right = nullptr;
    }
    parent = nullptr;
}
