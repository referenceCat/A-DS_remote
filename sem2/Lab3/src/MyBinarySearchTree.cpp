//
// Created by referencecat on 29.04.24.
//

#include "MyBinarySearchTree.h"



MBSTNode* Build(int a, int b, std::vector<int> data)
//Сборка ДДП из отрезка [a, b] упорядоченного вектора ключей data
{   if (b <= a) return nullptr;
    int  c = (a + b) /2;
    auto* s = new MBSTNode(data[ c ]);
    s->left = Build(a, c, data);
    s->right = Build(c+1, b, data);
    s->size += s->left->size;
    s->size += s->right->size;
    return s;
}

bool Search(int item, MBSTNode* node) {
    if (node == nullptr) return false;
    if (node->value == item) return true;
    if (node->value > item) return Search(item, node->left);
    return Search(item, node->right);
}

int Add(int item, MBSTNode* node) {
    if (item == node->value) return 0;
    MBSTNode** next;
    if (item < node->value) next = &node->left;
    else next = &node->right;

    if (*next == nullptr) {
        *next = new MBSTNode(item);
        node->size++;
        return 1;
    }
    else {
        int added = Add(item, *next);
        node->size += added;
        return added;
    }
}

void Clear(MBSTNode* node) {
    if (node->left != nullptr) Clear(node->left);
    if (node->right != nullptr) Clear(node->right);
    delete node;
}

void Remove(int item, MBSTNode* node) {

}

MBSTNode::MBSTNode(int i) {
    value = i;
    left = nullptr;
    right = nullptr;
    size = 1;
}

void MyBinarySearchTree::build(int a, int b, std::vector<int> data) {
    root = Build(a, b, data);
}

bool MyBinarySearchTree::contains(int item) {
    if (empty()) return false;
    return Search(item, root);
}

void MyBinarySearchTree::add(int item) {
    if (empty()) {
        root = new MBSTNode(item);
    } else {
        Add(item, root);
    }
}

int MyBinarySearchTree::size() {
    if (root == nullptr) return 0;
    return root->size;
}

bool MyBinarySearchTree::empty() {
    return size() == 0;
}

void printBT(const std::string& prefix, const MBSTNode* node, bool isLeft) {
    if (node != nullptr) {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──");

        // print the value of the node
        std::cout << node->value << "(" << node->size << ")" << std::endl;

        // enter the next tree level - left and right branch
        printBT(prefix + (isLeft ? "│   " : "    "), node->left, true);
        printBT(prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

void MyBinarySearchTree::print() {
    if (empty()) std::cout << "Tree is empty" << std::endl;
    else printBT("", root, false);
}

void MyBinarySearchTree::remove(int item) {

}

void MyBinarySearchTree::clear() {
    if (empty()) return;
    Clear(root);
}
