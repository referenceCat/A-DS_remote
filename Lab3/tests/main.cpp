//
// Created by referencecat on 23.11.23.
//

#include "iostream"
#include "Tree.h"

int main( )
{ int n = 0;
    Tree tree('a', 'z', 8);
    srand(time(nullptr));
    setlocale(LC_ALL, "Russian");
    tree.makeRandomTree();
    if(tree.exist()) {
        tree.printTree();
        std::cout << '\n' << "Обход в ширину: ";
        n = tree.breadthFirstSearch();
        std::cout << " Пройдено узлов = " << n;
    }

    std::cin.get();
}