#include "../src/MyBinarySearchTree.h"

//todo
void generateRandomTree(MyBinarySearchTree* tree) {
    tree->add(1);
    tree->add(5);
    tree->add(2);
    tree->add(8);
    tree->add(1);
    tree->add(14);
    tree->add(11);
    tree->add(12);
    tree->add(17);
    tree->add(12);
}

int main() {
    MyBinarySearchTree tree;
    generateRandomTree(&tree);
    tree.print();
    std::cout<< tree.contains(8);
}