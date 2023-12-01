//
// Created by referencecat on 23.11.23.
//

#include "iostream"
#include "Tree.h"

int main( )
{ int n = 0;
    Tree tree('a', 'z', 8);
    srand(time(nullptr));
    tree.makeByInput(std::cout, std::cin);
    if(tree.exist()) {
        tree.printTree();
        std::cout << '\n' << "BF search: ";
        n = tree.breadthFirstSearch();
        std::cout << " Nodes with less than 1 child = " << n;
    }

    std::cin.get();
}