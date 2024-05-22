#include "../src/WeightedTree.h"


void generateRandomTree(WeightedTree& tree, int maxValue, int maxSize) {
    for (int i = 0; i < maxSize; i++) {
        tree.insert(rand() % maxValue);
    }
}

int main() {
    srand(time(nullptr));
    WeightedTree treeA;
    WeightedTree treeB;
    WeightedTree treeC;
    WeightedTree treeD;
    WeightedTree treeE;

    generateRandomTree(treeA, 10, 7);
    generateRandomTree(treeB, 10, 7);
    generateRandomTree(treeC, 10, 7);
    generateRandomTree(treeD, 10, 7);
    generateRandomTree(treeE, 10, 7);

    std::cout << "Tree A structure: " << std::endl;
    treeA.print();

    std::cout << "A: ";
    treeA.printElements();
    std::cout << "B: ";
    treeB.printElements();
    std::cout << "C: ";
    treeC.printElements();
    std::cout << "D: ";
    treeD.printElements();
    std::cout << "E: ";
    treeE.printElements();

    std::cout << std::endl;
    WeightedTree CuD;
    CuD.unionSet(treeC);
    CuD.unionSet(treeD);
    std::cout << "C ∪ D: ";
    CuD.printElements();

    WeightedTree result;
    result.unionSet(treeA);
    result.s_difference(treeB);
    std::cout << "A ⊕ B: ";
    result.printElements();

    result.difference(CuD);
    std::cout << "A ⊕ B \\ (C ∪ D): ";
    result.printElements();

    result.difference(treeE);
    std::cout << "A ⊕ B \\ (C ∪ D) \\ E: ";
    result.printElements();

    std::cout << std::endl << "Weighed tree as sequence:" << std::endl;
    treeA.clear();
    generateRandomTree(treeA, 10, 5);
    treeB.clear();
    generateRandomTree(treeB, 10, 5);
    std::cout << "A: ";
    treeA.printSequence();
    std::cout << "B: ";
    treeB.printSequence();

    result.clear();
    result.unionSet(treeA);
    result.concat(treeB);
    std::cout << "A.concat(B): ";
    result.printSequence();

    result.clear();
    result.unionSet(treeA);
    result.merge(treeB);
    std::cout << "A.merge(B): ";
    result.printSequence();

    result.clear();
    result.unionSet(treeA);
    result.subst(treeB, 2);
    std::cout << "A.subst(B, 2): ";
    result.printSequence();

}