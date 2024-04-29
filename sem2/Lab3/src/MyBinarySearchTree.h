//
// Created by referencecat on 29.04.24.
//

#ifndef A_DS_REMOTE_MYBINARYSEARCHTREE_H
#define A_DS_REMOTE_MYBINARYSEARCHTREE_H

#include "iostream"
#include "vector"

struct MBSTNode {
    MBSTNode(int i);
    int size;
    int value;
    MBSTNode* left,* right;

private:
    MBSTNode();
};


class MyBinarySearchTree {
private:
    MBSTNode* root = nullptr;
public:
    void build(int a, int b, std::vector<int> data);
    void print();
    int size();
    void add(int item);
    bool contains(int item);
    bool empty();
    void remove(int item);
    void clear();
};


#endif //A_DS_REMOTE_MYBINARYSEARCHTREE_H
