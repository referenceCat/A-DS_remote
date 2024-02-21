//
// Created by referencecat on 23.11.23.
//

#ifndef A_DS_REMOTE_NODE_H
#define A_DS_REMOTE_NODE_H


class Node {
    char tag;
    Node *leftNode;
    Node *rightNode;    // правый сын
public:
    Node() : leftNode(nullptr), rightNode(nullptr) {}

    ~Node() {
        if (leftNode) delete leftNode;
        if (rightNode) delete rightNode;
    }

    friend class Tree;    // дружественный класс «дерево»
};


#endif //A_DS_REMOTE_NODE_H
