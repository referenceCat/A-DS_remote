#include "../src/WeightedTree.h"

//todo
void generateRandomTree(WeightedTree* tree) {
    tree->insert(1);
    tree->insert(5);
    tree->insert(2);
    tree->insert(8);
    tree->insert(1);
    tree->insert(14);
    tree->insert(11);
    tree->insert(12);
    tree->insert(17);
    tree->insert(12);
}

int main() {
    WeightedTree tree;
    generateRandomTree(&tree);
    tree.print();
    std::cout<< tree.contains(8);
}