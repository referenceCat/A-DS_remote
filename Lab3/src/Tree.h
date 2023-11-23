//
// Created by referencecat on 23.11.23.
//

#ifndef A_DS_REMOTE_TREE_H
#define A_DS_REMOTE_TREE_H

#include "Node.h"
#include "iostream"
#include "cstring"
#include "Queue.h"


class Tree {
    Node *rootNode;    // указатель на корень дерева
    char tagCounter, tagMaxValue;        //счётчик тегов и максимальный тег
    int maxDepth, rootOffset;        //максимальная глубина, смещение корня
    char **screenMatrix;    // память для выдачи на экран

    void clrscr();    // очистка рабочей памяти
    Node *makeRandomSubtree(int depth);    // создание поддерева
    void printSubtree(Node *currentNode, int row, int column); // выдача поддерева

    Tree(const Tree &);    // фиктивный конструктор копии
    Tree(Tree &&);        //копия с переносом (С++11)
    Tree operator=(const Tree &) const = delete;    // присваивание
    Tree operator=(Tree &&) const = delete; // то же,  с переносом

public:
    Tree(char num, char maxnum, int maxrow);

    ~Tree();

    // ввод — генерация дерева
    void makeRandomTree() {
        rootNode = makeRandomSubtree(0);
    }

    // проверка «дерево не пусто»
    bool exist() {
        return rootNode != nullptr;
    }

    int breadthFirstSearch();    // обход «в ширину»
    void printTree();    // выдача на экран
};


#endif //A_DS_REMOTE_TREE_H
