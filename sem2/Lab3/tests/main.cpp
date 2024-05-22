#include "../src/WeightedTree.h"

//todo
void generateRandomTree(WeightedTree* tree) {
    tree->randomInsert(1);
    tree->randomInsert(5);
    tree->randomInsert(17);
    tree->randomInsert(2);
    tree->randomInsert(8);
    tree->randomInsert(1);
    tree->randomInsert(12);
    tree->randomInsert(14);
    tree->randomInsert(11);
    tree->randomInsert(12);

}

int main() {
    WeightedTree tree;
    generateRandomTree(&tree);
    tree.print(0);

    tree.balance();
    tree.print(0);

    for (auto x: tree) {
        std::cout << x << " ";
    }
}