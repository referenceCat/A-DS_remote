//
// Created by referencecat on 23.11.23.
//

#include "iostream"
#include "Tree.h"

int main( )
{ int n = 0;
    Tree Tr('a', 'z', 8);
    srand(time(nullptr));
    setlocale(LC_ALL, "Russian");
    Tr.MakeTree();
    if(Tr.exist()) {
        Tr.OutTree();
    }

    std::cin.get();
}