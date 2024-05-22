//
// Created by referencecat on 29.04.24.
//

#ifndef A_DS_REMOTE_WEIGHTEDTREE_H
#define A_DS_REMOTE_WEIGHTEDTREE_H

#include "iostream"
#include "vector"
#include <iterator>
#include <stack>
#include <string>
#include "list"

struct Node {
    Node(int i);
    int size;
    int key;
    Node* left,* right;
    //~Node() {delete left; delete right;}

private:
    Node();
};

using MyStack = std::stack<std::pair<Node*, int>>; //Тип стека для обхода дерева
//ИТЕРАТОР ЧТЕНИЯ
//template<class Container = Set> — настройка на контейнер не требуется
struct ReadIterator : public std::iterator<std::forward_iterator_tag, int>
{
    Node * Ptr;   //Реальный указатель
    MyStack St;  //Стек с путём от корня дерева
    ReadIterator(Node *p = nullptr) : Ptr(p) { }
    ReadIterator(Node *p, const MyStack &&St) : Ptr(p), St(move(St)) { }
    bool operator == (const ReadIterator & Other) const { return Ptr == Other.Ptr; }
    bool operator != (const ReadIterator & Other) const { return !(*this == Other); }
    ReadIterator & operator++( );
    ReadIterator operator++(int) { ReadIterator temp(*this); ++*this; return temp; }
    pointer operator->( ) { return &Ptr->key; }
    reference operator*( ) { return Ptr->key; }
};


class WeightedTree {
protected:
    Node* root = nullptr;
    std::list<Node*> sequence {};
public:
    void print();
    void printElements();
    void printSequence();
    int size();
    void insert(int item);
    bool contains(int item);
    bool empty();
    void clear();
    void balance();
    bool erase(int k);
    bool randomInsert(int x);
    ~WeightedTree() { delete root; }
    WeightedTree() = default;
//    WeightedTree (const WeightedTree & other): WeightedTree() {
//        for (auto x : other) insert(x);
//    }

    ReadIterator begin( )const;
    ReadIterator end( )const { return ReadIterator(nullptr); }
    void concat(WeightedTree& tree);
    void merge(WeightedTree& other);
    void subst(WeightedTree& other, int position);
    void unionSet(WeightedTree& other);
    void difference(WeightedTree& other);
    void s_difference(WeightedTree& other);

};





#endif //A_DS_REMOTE_WEIGHTEDTREE_H
