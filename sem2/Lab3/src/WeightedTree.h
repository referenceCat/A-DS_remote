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

struct Node {
    Node(int i);
    int size;
    int key;
    Node* left,* right;
    ~Node() {delete left; delete right;}

private:
    Node();
};

using TreeStack = std::stack<std::pair<Node*, int>>; //Тип стека для обхода дерева

//ИТЕРАТОР ЧТЕНИЯ
//template<class Container = Set> — настройка на контейнер не требуется
struct IteratorForward : public std::iterator<std::forward_iterator_tag, int>
{
    Node * Ptr;   //Реальный указатель
    TreeStack St;  //Стек с путём от корня дерева
    IteratorForward(Node *p = nullptr) : Ptr(p) { }
    IteratorForward(Node *p, const TreeStack &&St) : Ptr(p), St(move(St)) { }
    bool operator == (const IteratorForward & Other) const { return Ptr == Other.Ptr; }
    bool operator != (const IteratorForward & Other) const { return !(*this == Other); }
    IteratorForward & operator++( );
    IteratorForward operator++(int) { IteratorForward temp(*this); ++*this; return temp; }
    pointer operator->( ) { return &Ptr->key; }
    reference operator*( ) { return Ptr->key; }
};

//ИТЕРАТОР ВСТАВКИ (универсальный)
template <typename Container, typename Iter = IteratorForward>
class IteratorOutput : public std::iterator<std::output_iterator_tag, typename Container::value_type> {
protected:
    Container& container;    // Контейнер для вставки элементов
    Iter iter;                           // Текущее значение итератора чтения
public:
    IteratorOutput(Container& c, Iter it) : container(c), iter(it) { } // Конструктор
    const IteratorOutput<Container>& // Присваивание — вставка ключа в контейнер
    operator = (const typename Container::value_type& value) {
        iter = container.insert(iter, value);
        return *this;
    }
    const IteratorOutput<Container>& //Присваивание копии — фиктивное
    operator = (const IteratorOutput<Container>&) { return *this; }
    IteratorOutput<Container>& operator* ( ) { return *this; } // Разыменование — пустая операция
    IteratorOutput<Container>& operator++ ( ) { return *this; } // Инкремент — пустая операция
    IteratorOutput<Container>& operator++ (int) { return *this; }
};

// Функция для создания итератора вставки
template <typename Container, typename Iter>
inline IteratorOutput<Container, Iter> inserter(Container& c, Iter it)
{ return IteratorOutput<Container, Iter>(c, it); }

class WeightedTree {
private:
    Node* root = nullptr;
public:
    using key_type = int;
    using value_type = int;
    using key_compare = std::less<int> ;
    void print();
    int size();
    // void insert(int item);
    bool contains(int item);
    bool empty();
    void clear();
    void balance();
    bool erase(int k);
    bool randomInsert(int x);
    void swap(WeightedTree & other) {std::swap(root, other.root);} //Обмен содержимого двух ДДП
    IteratorForward insert(const IteratorForward& where, const int& k);
    IteratorForward insert(const int& k, const IteratorForward& where = IteratorForward(nullptr)) {
        return insert(where, k);
    }
    IteratorForward begin( )const;
    IteratorForward end( )const { return IteratorForward(nullptr); }
    ~WeightedTree() { delete root; }
    IteratorForward find(int) const;           // Поиск по ключу
    WeightedTree() {};
    WeightedTree (const WeightedTree & other): WeightedTree() {
        for (auto x : other) insert(x);
    }
    WeightedTree(WeightedTree && other): WeightedTree() { swap(other); }
    WeightedTree & operator = (const WeightedTree & other) {
        WeightedTree temp;
        for (auto x : other) temp.insert(x);
        swap(temp);
        return *this;
    }
    WeightedTree & operator = (WeightedTree && rgt) { swap(rgt); return *this; }
    WeightedTree & operator |= (const WeightedTree &);
    WeightedTree operator | (const WeightedTree & rgt) const
    {  WeightedTree result(*this); return (result |= rgt); }
    WeightedTree & operator &= (const WeightedTree &);
    WeightedTree operator & (const WeightedTree & rgt) const
    {  WeightedTree result(*this); return (result &= rgt); }
    WeightedTree & operator -= (const WeightedTree &);
    WeightedTree operator - (const WeightedTree & rgt) const
    {  WeightedTree result(*this); return (result -= rgt); }
    WeightedTree & operator ^= (const WeightedTree &);
    WeightedTree operator ^ (const WeightedTree & rgt) const
    {  WeightedTree result(*this); return (result ^= rgt); }
};






#endif //A_DS_REMOTE_WEIGHTEDTREE_H
