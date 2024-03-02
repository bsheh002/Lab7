#ifndef Lab_7
#define Lab_7


#include "Node.h"
#include <ostream>
using namespace std;

class AVLTree {
private:
    Node* root = nullptr;
public:
    int balanceFactor(Node* balancingNode) const;
    void insert(const string &insertNode);
    void printBalanceFactors() const;
    void visualizeTree(const string &outputFilename);
private:
    void changeHeight(Node* heightChangeNode) const;
    void rotateRight(Node* rightNode);
    void rotateLeft(Node* leftNode);
    void rebalanceCheck(Node* rebalanceNode);
    void balanceFactorHelper(Node* balancingNode) const;
    void visualizeTree(ofstream& outFS, Node *n);
};


#endif
