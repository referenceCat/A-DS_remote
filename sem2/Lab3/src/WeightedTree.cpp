//
// Created by referencecat on 29.04.24.
//

#include <algorithm>
#include "WeightedTree.h"

bool Search(int item, Node* node) {
    if (node == nullptr) return false;
    if (node->key == item) return true;
    if (node->key > item) return Search(item, node->left);
    return Search(item, node->right);
}

void Clear(Node* node) {
    if (node->left != nullptr) Clear(node->left);
    if (node->right != nullptr) Clear(node->right);
    delete node;
}

Node::Node(int i) {
    key = i;
    left = nullptr;
    right = nullptr;
    size = 1;
}

bool WeightedTree::contains(int item) {
    if (empty()) return false;
    return Search(item, root);
}

int WeightedTree::size() {
    if (root == nullptr) return 0;
    return root->size;
}

bool WeightedTree::empty() {
    return size() == 0;
}

void printInorder(Node* node) {
    if (node == nullptr)
        return;
    printInorder(node->left);
    std::cout << node->key << "(" << node->size << ") ";
    printInorder(node->right);
}

void printBT(const std::string& prefix, const Node* node, bool isLeft, bool lastHasRight) {
    if (node != nullptr) {
        std::cout << prefix;

        std::cout << (isLeft ? "├──────" : "└──────");

        // print the key of the node
        std::cout << node->key << "(" << node->size << ")" << std::endl;

        // enter the next tree level - left and right branch
        printBT(prefix + ((isLeft && lastHasRight) ? "│       " : "        "), node->left, true, node->right!= nullptr);
        printBT(prefix + ((isLeft && lastHasRight) ? "│       " : "        "), node->right, false, node->right!= nullptr);
    }
}

void WeightedTree::print(int mode=1) {
    if (empty()) std::cout << "Tree is empty" << std::endl;
    else if (mode == 0) printBT("", root, false, true);
    else if (mode == 1) printInorder(root);

    std::cout << std::endl;
}

void WeightedTree::clear() {
    if (empty()) return;
    Clear(root);
}

void calculateSize(Node* node) {
    node->size = 1 + (node->left ? node->left->size : 0) + (node->right ? node->right->size : 0);
}

void rotateRight(Node* &h){ //Поворот вправо
    Node* x = h->left;
    h->left = x->right;
    calculateSize(h);
    x->right = h;
    h = x;
    calculateSize(h);
}
void rotateLeft(Node* &h) { //Поворот влево
    Node *x = h->right;
    h->right = x->left;
    calculateSize(h);
    x->left = h;
    h = x;
    calculateSize(h);
}

bool recursiveInsert(Node* &h, int x) { //Вставка в корень
    if (!h) {
        h = new Node(x);
        return true;
    }
    if (x < h->key) {
        recursiveInsert(h->left, x);
        rotateRight(h); }
    else if (x > h->key) {
        recursiveInsert(h->right, x);
        rotateLeft(h); }
    else return false;
    return true;
}


void WeightedTree::insert(int x) { //Вставка нового узла в корень (оболочка)
    recursiveInsert(root, x);
}

void partR(Node*&h, int k) //Разбиение по k-му ключу
{
    int t = (h->left == nullptr) ? 0 : h->left->size;
    if (t > k) { partR(h->left, k);
        rotateRight(h); }
    if (t < k) { partR(h->right, k-t-1);
        rotateLeft(h); }
}
void recursiveBalance(Node *& h) //Балансировка
{
    if (!h || (h->size == 1)) return;
    partR(h, h->size / 2);
    recursiveBalance(h->left);
    recursiveBalance(h->right);
}

void WeightedTree::balance( ) { recursiveBalance(root); }; //Балансировка (оболочка)\

Node* joinLR(Node* a, Node*b) { //Объединение поддеревьев
    if (!b) return a;
    partR(b, 0);
    b->left = a;
    calculateSize(b);
    return b;
}


bool recursiveRemove(Node*& h, int v) { //Рекурсивное удаление с объединением поддеревьев
    if (!h) return false;
    int w = h->key;
    if (v < w) recursiveRemove(h->left, v);
    if (w < v) recursiveRemove(h->right, v);
    if (v == w) { Node* t = h;
        h = joinLR(h->left, h->right);
        if(h) calculateSize(h);
        t->left = t->left = nullptr;
        delete t;
    }
    return true;
}

bool WeightedTree::erase(int k) { return recursiveRemove(root, k); } //Рекурсивное удаление

bool recursiveRandomInsert(Node*&h, int x) { //Рандомизированная вставка
    if (!h) {
        h = new Node(x);
        return true;
    }
    ++h->size;
    if (rand( ) < RAND_MAX / (h->size + 1)) {
        recursiveInsert(h, x); return true;
    }
    if (x < h->key)
        recursiveRandomInsert(h->left, x);
    else if (x > h->key)
        recursiveRandomInsert(h->right, x);
    else return false;
    return true;
}

bool WeightedTree::randomInsert(int x) { recursiveRandomInsert(root, x); return true;  }


