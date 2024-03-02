#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <iostream>

#include "AVLTree.h"
using namespace std;


int AVLTree::balanceFactor(Node* balancingNode) const {
    int leftHeight = -1;
    int rightHeight = -1;
    int totalBalance;
    if (balancingNode->left != nullptr) {
        leftHeight = balancingNode->left->height;
    }
    if (balancingNode->right != nullptr) {
        rightHeight = balancingNode->right->height;
    }
    totalBalance = leftHeight - rightHeight;
    return totalBalance;
}
void AVLTree::changeHeight(Node* heightChangeNode) const{
    int leftHeight = -1;
    int rightHeight = -1;
    int maxHeight = 0;
    if (heightChangeNode->left) {
        leftHeight = heightChangeNode->left->height;
    }
    if (heightChangeNode->right) {
        rightHeight = heightChangeNode->right->height;
    }
    maxHeight = leftHeight;
    if (rightHeight > leftHeight) {
        maxHeight = rightHeight;
    }
    heightChangeNode->height = maxHeight + 1;
}
void AVLTree::rotateRight(Node* rightNode) {
    Node* leftChild = rightNode->left;
    rightNode->left = leftChild->right;
    if (leftChild->right) {
        leftChild->right->parent = rightNode;
    }
    leftChild->right = rightNode;
    leftChild->parent = rightNode->parent;
    rightNode->parent = leftChild;
    if (leftChild->parent) {
        if (leftChild->parent->left == rightNode) {
            leftChild->parent->left = leftChild;
        } else {
            leftChild->parent->right = leftChild;
        }
    } else {
        root = leftChild;
    }
    changeHeight(rightNode);
    changeHeight(leftChild);
}
void AVLTree::rotateLeft(Node* leftNode) {
    Node* theRightNode = leftNode->right;
    leftNode->right = theRightNode->left;
    if (theRightNode->left) {
        theRightNode->left->parent = leftNode;
    }
    theRightNode->left = leftNode;
    theRightNode->parent = leftNode->parent;
    leftNode->parent = theRightNode;
    if (theRightNode->parent) {
        if (theRightNode->parent->left == leftNode) {
            theRightNode->parent->left = theRightNode;
        } else {
            theRightNode->parent->right = theRightNode;
        }
    } else {
        root = theRightNode;
    }
    changeHeight(leftNode);
    changeHeight(theRightNode);
}
void AVLTree::rebalanceCheck(Node* rebalanceNode) {
    changeHeight(rebalanceNode);
    int leftHeight = (rebalanceNode->left) ? rebalanceNode->left->height : -1;
    int rightHeight = (rebalanceNode->right) ? rebalanceNode->right->height : -1;
    if (leftHeight - rightHeight == -2) {
        int rightLeftHeight = (rebalanceNode->right && rebalanceNode->right->left) ? rebalanceNode->right->left->height : -1;
        int rightRightHeight = (rebalanceNode->right && rebalanceNode->right->right) ? rebalanceNode->right->right->height : -1;
        if (rightLeftHeight > rightRightHeight) {
            rotateRight(rebalanceNode->right);
        }
        rotateLeft(rebalanceNode);
    }
    else if (leftHeight - rightHeight == 2) {
        int leftLeftHeight = (rebalanceNode->left && rebalanceNode->left->left) ? rebalanceNode->left->left->height : -1;
        int leftRightHeight = (rebalanceNode->left && rebalanceNode->left->right) ? rebalanceNode->left->right->height : -1;
        if (leftRightHeight > leftLeftHeight) {
            rotateLeft(rebalanceNode->left);
        }
        rotateRight(rebalanceNode);
    }
}
void AVLTree::insert(const string &insertNode) {
    Node* newNodeToInsert = new Node(insertNode);
    if (root == nullptr) {
        root = newNodeToInsert;
        newNodeToInsert->parent = nullptr;
        return;
    }
    Node* theParentNode = nullptr;
    Node* theRightNowNode = root;
    while (theRightNowNode != nullptr) {
        theParentNode = theRightNowNode;
        if (newNodeToInsert->key < theRightNowNode->key) {
            theRightNowNode = theRightNowNode->left;
        }
        else if (newNodeToInsert->key > theRightNowNode->key) {
            theRightNowNode = theRightNowNode->right;
        }
        else {
            delete newNodeToInsert;
            return;
        }
    }
    newNodeToInsert->parent = theParentNode;
    if (newNodeToInsert->key < theParentNode->key) {
        theParentNode->left = newNodeToInsert;
    }
    else {
        theParentNode->right = newNodeToInsert;
    }
    Node* balancingNode = newNodeToInsert->parent;
    while (balancingNode != nullptr) {
        rebalanceCheck(balancingNode);
        balancingNode = balancingNode->parent;
    }
}
void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}
void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->key <<" -> " <<n->left->key<<";"<<endl;
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->key <<" -> " <<n->right->key<<";"<<endl;
        }
    }
}
void AVLTree::balanceFactorHelper(Node *node) const {
    if (node != nullptr) {
        balanceFactorHelper(node->left);
        cout << node->key << "(" << balanceFactor(node) << "), ";
        balanceFactorHelper(node->right);
    }
}
void AVLTree::printBalanceFactors() const {
    balanceFactorHelper(root);
    cout << endl;
}

