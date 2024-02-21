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

Node *Tree::makeRandomSubtree(int depth) {
    Node *newNode = nullptr;
    int Y = (depth < rand() % 6 + 1) && (tagCounter <= 'z');
//    std::cout << "Node (" << tagCounter << ',' << depth << ")1/0: ";
//    std::cin >> Y;
    if (Y) {    // создание узла, если Y = 1
        newNode = new Node;
        // newNode->tag = tagCounter++;     // разметка в прямом порядке (= «в глубину»)
        newNode->leftNode = makeRandomSubtree(depth + 1);
        newNode->tag = tagCounter++;          //вариант — во внутреннем
        newNode->rightNode = makeRandomSubtree(depth + 1);
        //	 newNode->tag = tagCounter++;		// вариант — в обратном
    }
    return newNode;
}

void Tree::printTree() {
    clrscr();
    printSubtree(rootNode, 1, rootOffset);
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

void Tree::printSubtree(Node *currentNode, int row, int column) {
    if (row && column && (column < 80)) screenMatrix[row - 1][column - 1] = currentNode->tag; // вывод метки
    if (row < maxDepth) {
        if (currentNode->leftNode) printSubtree(currentNode->leftNode, row + 1, column - (rootOffset >> row)); //левый сын
        if (currentNode->rightNode)
            printSubtree(currentNode->rightNode, row + 1, column + (rootOffset >> row)); //правый сын
    }
}

int Tree::breadthFirstSearch() {
    const int MaxQ = 20; //максимальный размер очереди
    int count = 0;
    Queue<Node *> queue(MaxQ);  //создание очереди указателей на узлы
    queue.push(rootNode); // Queue <- root поместить в очередь корень дерева
    while (!queue.empty()) {
        Node *currentNode = queue.pop();// взять из очереди,
        std::cout << currentNode->tag << '_';
        if (currentNode->leftNode == nullptr && currentNode->rightNode == nullptr) // task: less than 1 child
            count++; // выдать тег, счёт узлов
        if(currentNode->rightNode == nullptr && currentNode->leftNode && (currentNode->leftNode->leftNode == nullptr && currentNode->leftNode->rightNode == nullptr)) {
            count++;
        }
        if(currentNode->leftNode == nullptr && currentNode->rightNode && (currentNode->rightNode->leftNode == nullptr && currentNode->rightNode->rightNode == nullptr)){
            count++;
        }
        if (currentNode->leftNode) queue.push(currentNode->leftNode); // Queue <- (левый сын)
        if (currentNode->rightNode) queue.push(currentNode->rightNode); // Queue <- (правый сын)
    }
    return count;
}

Node *Tree::enter_node(std::ostream &out, std::istream &in) {
    Node *node = new Node();
    char ans;
    out << "Enter node value:" << std::endl;
    in >> node->tag;
    out << "Do you want to enter left branch (y/n)?" << std::endl;
    in >> ans;
    if (ans == 'y') {
        node->leftNode = enter_node(out, in);
    }
    out << "Do you want to enter right branch (y/n)?" << std::endl;
    in >> ans;
    if (ans == 'y') {
        node->rightNode = enter_node(out, in);
    }
    return node;
}

void Tree::makeByInput(std::ostream &out, std::istream &in) {
    out << "Enter tree:" << std::endl;
    rootNode = enter_node(out, in);
}