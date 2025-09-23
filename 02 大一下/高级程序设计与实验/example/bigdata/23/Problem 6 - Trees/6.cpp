/*
 * File: Trees & Recursion Problem
 * -------------------------------------------------------------------------
 *  Given binary trees A and B, decide whether a subtree of A is isomorphic to B.
 */
#include <iostream>
#include <string>
#include "console.h"
#include "vector.h"
using namespace std;

const int NULLVALUE = -1;

struct Node {
    int value;
    Node *left;
    Node *right;
};

bool containsSubtree(Node * rootA, Node * rootB);
void printTree(Node* node, string indent);
Node* makeTree(const Vector<int>& preOrderVector, int& index);

string frontOrder(Node *root)
{
    if (root == nullptr)
        return "";
    return ("0" + root->value) + frontOrder(root->left) + frontOrder(root->right);
}

string middleOrder(Node *root)
{
    if (root == nullptr)
        return "";
    return middleOrder(root->left) + ("0" + root->value) + middleOrder(root->right);
}

bool isomorphic(Node *rootA, Node *rootB)
{
    return frontOrder(rootA) == frontOrder(rootB) && middleOrder(rootA) == middleOrder(rootB);
}

bool containsSubtree(Node * rootA, Node * rootB)
{
    if (rootA == nullptr)
        return rootB == nullptr;

    return isomorphic(rootA, rootB) || containsSubtree(rootA->left, rootB)
           || containsSubtree(rootA->right, rootB);
}

int main() {
    cout << "Problem - Trees & Recursion Test:" << endl<<endl;
    Vector<int> preOrderA = {1, 5, 3, NULLVALUE, NULLVALUE, 4, NULLVALUE, NULLVALUE, 2, NULLVALUE, NULLVALUE};
    Vector<int> preOrderB = {5, 3, NULLVALUE, NULLVALUE, 4, NULLVALUE, NULLVALUE};

    int index = 0;
    cout<<"Make tree:"<<endl;
    Node* treeA = makeTree(preOrderA, index);
    index = 0;
    printTree(treeA, "");
    cout << endl << endl;
    Node* treeB = makeTree(preOrderB, index);
    printTree(treeB, "");

    cout<< endl <<"Tree A contains ";
    if (!containsSubtree(treeA, treeB)) cout << "not ";
    cout << "a subtree isomorphic to tree B." << endl << endl;
    cout << "---------------" << endl;

     preOrderA = {5, 3, NULLVALUE, NULLVALUE, 4, NULLVALUE, NULLVALUE};
     preOrderB = {5, 4, NULLVALUE, NULLVALUE, 3, NULLVALUE, NULLVALUE};

    index = 0;
    cout<<"Make tree:"<<endl;
    treeA = makeTree(preOrderA, index);
    index = 0;
    printTree(treeA, "");
    cout << endl << endl;
    treeB = makeTree(preOrderB, index);
    printTree(treeB, "");

    cout<< endl <<"Tree A contains ";
    if (!containsSubtree(treeA, treeB)) cout << "not ";
   cout << "a subtree isomorphic to tree B." << endl << endl;

    return 0;
}

Node* makeTree(const Vector<int>& preOrderVector, int& index){
    if(index >= preOrderVector.size())
        return nullptr;
    int n = preOrderVector[index++];
    if(n == NULLVALUE)
        return nullptr;
    Node* treeNode = new Node{n, nullptr, nullptr};
    treeNode->left = makeTree(preOrderVector,index);
    treeNode->right = makeTree(preOrderVector,index);
    return treeNode;
}

void printTree(Node* node, string indent) {
    if (node != nullptr) {
        printTree(node->right,indent + "  ");
        cout << indent;
        cout << "{"<< node->value<< "}";
        cout << endl;
        printTree(node->left, indent + "  ");
    }
}



