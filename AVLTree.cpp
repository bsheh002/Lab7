#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <iostream>

#include "AVLTree.h"
using namespace std;


int AVLTree::balanceFactor(Node* balancingNode) const { //calculates the balance factor of the tree
    int leftHeight = -1;
    int rightHeight = -1;
    int totalBalance;
    if (balancingNode->left != nullptr) { //checks if left exists
        leftHeight = balancingNode->left->height;
    }
    if (balancingNode->right != nullptr) { //checks if right exists
        rightHeight = balancingNode->right->height;
    }
    totalBalance = leftHeight - rightHeight;
    return totalBalance;
}
void AVLTree::changeHeight(Node* heightChangeNode) const{ //updates the height of the tree
    int leftHeight = -1;
    int rightHeight = -1;
    int maxHeight = 0;
    if (heightChangeNode->left) { //checks if left exists
        leftHeight = heightChangeNode->left->height;
    }
    if (heightChangeNode->right) { //checks if right exists
        rightHeight = heightChangeNode->right->height;
    }
    maxHeight = leftHeight;
    if (rightHeight > leftHeight) { //checks if right is bigger
        maxHeight = rightHeight;
    }
    heightChangeNode->height = maxHeight + 1;
}
void AVLTree::rotateRight(Node* rightNode) { //does a right rotation on tree
    Node* leftChild = rightNode->left;
    rightNode->left = leftChild->right;
    if (leftChild->right) { //checks if right exists
        leftChild->right->parent = rightNode;
    }
    leftChild->right = rightNode;
    leftChild->parent = rightNode->parent;
    rightNode->parent = leftChild;
    if (leftChild->parent) { //checks if parent exists
        if (leftChild->parent->left == rightNode) { //compares left parent to right node
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
void AVLTree::rotateLeft(Node* leftNode) { //does a left rotation on a node in the tree
    Node* theRightNode = leftNode->right;
    leftNode->right = theRightNode->left;
    if (theRightNode->left) { //checks if left exists
        theRightNode->left->parent = leftNode;
    }
    theRightNode->left = leftNode;
    theRightNode->parent = leftNode->parent;
    leftNode->parent = theRightNode;
    if (theRightNode->parent) { //checks if parent exists
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
void AVLTree::rebalanceCheck(Node* rebalanceNode) { //checks if tree needs rebalancing
    changeHeight(rebalanceNode);
    int leftHeight = (rebalanceNode->left) ? rebalanceNode->left->height : -1;
    int rightHeight = (rebalanceNode->right) ? rebalanceNode->right->height : -1;
    if (leftHeight - rightHeight == -2) { //checks if height of left is smaller than right
        int rightLeftHeight = (rebalanceNode->right && rebalanceNode->right->left) ? rebalanceNode->right->left->height : -1;
        int rightRightHeight = (rebalanceNode->right && rebalanceNode->right->right) ? rebalanceNode->right->right->height : -1;
        if (rightLeftHeight > rightRightHeight) { //checks if right left is bigger than right right 
            rotateRight(rebalanceNode->right);
        }
        rotateLeft(rebalanceNode);
    }
    else if (leftHeight - rightHeight == 2) { //checks if left height is bigger
        int leftLeftHeight = (rebalanceNode->left && rebalanceNode->left->left) ? rebalanceNode->left->left->height : -1;
        int leftRightHeight = (rebalanceNode->left && rebalanceNode->left->right) ? rebalanceNode->left->right->height : -1;
        if (leftRightHeight > leftLeftHeight) { //checks if left right is bigger than left left
            rotateLeft(rebalanceNode->left);
        }
        rotateRight(rebalanceNode);
    }
}
void AVLTree::insert(const string &insertNode) { //inserts a new node into tree
    Node* newNodeToInsert = new Node(insertNode);
    if (root == nullptr) { //checks if root is empty
        root = newNodeToInsert;
        newNodeToInsert->parent = nullptr;
        return;
    }
    Node* theParentNode = nullptr;
    Node* theRightNowNode = root;
    while (theRightNowNode != nullptr) { //checks if node is empty
        theParentNode = theRightNowNode;
        if (newNodeToInsert->key < theRightNowNode->key) { //compares key sizes
            theRightNowNode = theRightNowNode->left;
        }
        else if (newNodeToInsert->key > theRightNowNode->key) { //compares key sizes
            theRightNowNode = theRightNowNode->right;
        }
        else {
            delete newNodeToInsert;
            return;
        }
    }
    newNodeToInsert->parent = theParentNode;
    if (newNodeToInsert->key < theParentNode->key) { //compares key sizes
        theParentNode->left = newNodeToInsert;
    }
    else {
        theParentNode->right = newNodeToInsert;
    }
    Node* balancingNode = newNodeToInsert->parent;
    while (balancingNode != nullptr) { //checks if node is empty
        rebalanceCheck(balancingNode);
        balancingNode = balancingNode->parent;
    }
}
void AVLTree::visualizeTree(const string &outputFilename){ //generates a representation of tree visually
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){ //checks if file opens
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
void AVLTree::visualizeTree(ofstream & outFS, Node *n){ //generates a representation of tree visually
    if(n){
        if(n->left){ //checks if left exists
            visualizeTree(outFS,n->left);
            outFS<<n->key <<" -> " <<n->left->key<<";"<<endl;
        }

        if(n->right){ //checks if right exists
            visualizeTree(outFS,n->right);
            outFS<<n->key <<" -> " <<n->right->key<<";"<<endl;
        }
    }
}
void AVLTree::balanceFactorHelper(Node *node) const { //helper function for the balance factor
    if (node != nullptr) { //checks if node is empty
        balanceFactorHelper(node->left);
        cout << node->key << "(" << balanceFactor(node) << "), ";
        balanceFactorHelper(node->right);
    }
}
void AVLTree::printBalanceFactors() const { //prints the balance factor
    balanceFactorHelper(root);
    cout << endl;
}

