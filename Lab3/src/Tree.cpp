//
// Created by referencecat on 23.11.23.
//

#include "Tree.h"

Tree::Tree(char nm, char mnm, int mxr) :
        tagCounter(nm), tagMaxValue(mnm), maxDepth(mxr), rootOffset(40), rootNode(nullptr),
        screenMatrix(new char *[maxDepth]) { for (int i = 0; i < maxDepth; ++i) screenMatrix[i] = new char[80]; }


Tree::~Tree() {
    for (int i = 0; i < maxDepth; ++i) delete[]screenMatrix[i];
    delete[] screenMatrix;
    delete rootNode;
}

Node *Tree::MakeNode(int depth) {
    Node *newNode = nullptr;
    int Y = (depth < rand() % 6 + 1) && (tagCounter <= 'z');
//Вариант: cout << "Node (" << tagCounter << ',' << depth << ")1/0: "; cin >> Y;
    if (Y) {    // создание узла, если Y = 1
        newNode = new Node;
        // newNode->tag = tagCounter++;     // разметка в прямом порядке (= «в глубину»)
        newNode->leftNode = MakeNode(depth + 1);
        newNode->tag = tagCounter++;          //вариант — во внутреннем
        newNode->rightNode = MakeNode(depth + 1);
        //	 newNode->tag = tagCounter++;		// вариант — в обратном
    }
    return newNode;
}

void Tree::OutTree() {
    clrscr();
    OutNodes(rootNode, 1, rootOffset);
    for (int i = 0; i < maxDepth; i++) {
        screenMatrix[i][79] = 0;
        std::cout << '\n' << screenMatrix[i];
    }
    std::cout << '\n';
}

void Tree::clrscr() {
    for (int i = 0; i < maxDepth; i++)
        memset(screenMatrix[i], '.', 80);
}

void Tree::OutNodes(Node *currentNode, int row, int column) {
    if (row && column && (column < 80)) screenMatrix[row - 1][column - 1] = currentNode->tag; // вывод метки
    if (row < maxDepth) {
        if (currentNode->leftNode) OutNodes(currentNode->leftNode, row + 1, column - (rootOffset >> row)); //левый сын
        if (currentNode->rightNode) OutNodes(currentNode->rightNode, row + 1, column + (rootOffset >> row)); //правый сын
    }
}