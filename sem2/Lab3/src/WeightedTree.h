//
// Created by referencecat on 29.04.24.
//

#ifndef A_DS_REMOTE_WEIGHTEDTREE_H
#define A_DS_REMOTE_WEIGHTEDTREE_H

#include "iostream"
#include "vector"
#include <iterator>
#include <stack>
#include <string>

struct Node {
    Node(int i);
    int size;
    int key;
    Node* left,* right;
    ~Node() {delete left; delete right;}

private:
    Node();
};

class WeightedTree {
private:
    Node* root = nullptr;
public:
    void print();
    int size();
    void insert(int item);
    bool contains(int item);
    bool empty();
    void clear();
    void balance();
    bool erase(int k);
    bool randomInsert(int x);
    ~WeightedTree() { delete root; }
    WeightedTree() = default;
//    WeightedTree (const WeightedTree & other): WeightedTree() {
//        for (auto x : other) insert(x);
//    }
};






#endif //A_DS_REMOTE_WEIGHTEDTREE_H
