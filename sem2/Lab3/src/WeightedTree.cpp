//
// Created by referencecat on 29.04.24.
//

#include <algorithm>
#include "WeightedTree.h"

bool Search(int item, Node* node) {
    if (node == nullptr) return false;
    if (node->key == item) return true;
    if (node->key > item) return Search(item, node->left);
    return Search(item, node->right);
}

void Clear(Node* node) {
    if (node->left != nullptr) Clear(node->left);
    if (node->right != nullptr) Clear(node->right);
    delete node;
}

Node::Node(int i) {
    key = i;
    left = nullptr;
    right = nullptr;
    size = 1;
}

bool WeightedTree::contains(int item) {
    if (empty()) return false;
    return Search(item, root);
}

int WeightedTree::size() {
    if (root == nullptr) return 0;
    return root->size;
}

bool WeightedTree::empty() {
    return size() == 0;
}

void printInorder(Node* node) {
    if (node == nullptr)
        return;
    printInorder(node->left);
    std::cout << node->key << "(" << node->size << ") ";
    printInorder(node->right);
}

void printBT(const std::string& prefix, const Node* node, bool isLeft, bool lastHasRight) {
    if (node != nullptr) {
        std::cout << prefix;

        if (!isLeft) std::cout << "└─R────";
        else if (lastHasRight) std::cout << "├─L────";
        else std::cout << "└─L────";

        // print the key of the node
        std::cout << node->key << "(" << node->size << ")" << std::endl;

        // enter the next tree level - left and right branch
        printBT(prefix + ((isLeft && lastHasRight) ? "│       " : "        "), node->left, true, node->right!= nullptr);
        printBT(prefix + ((isLeft && lastHasRight) ? "│       " : "        "), node->right, false, node->right!= nullptr);
    }
}

void WeightedTree::print() {
    if (empty()) std::cout << "Tree is empty" << std::endl;
    else printBT("", root, false, true);

    std::cout << std::endl;
}

void WeightedTree::clear() {
    if (empty()) return;
    delete root;
    root = nullptr;
    sequence.clear();
}

void calculateSize(Node* node) {
    node->size = 1 + (node->left ? node->left->size : 0) + (node->right ? node->right->size : 0);
}

void rotateRight(Node* &h){ //Поворот вправо
    Node* x = h->left;
    h->left = x->right;
    calculateSize(h);
    x->right = h;
    h = x;
    calculateSize(h);
}
void rotateLeft(Node* &h) { //Поворот влево
    Node *x = h->right;
    h->right = x->left;
    calculateSize(h);
    x->left = h;
    h = x;
    calculateSize(h);
}

bool recursiveInsert(Node* &h, int x) { //Вставка в корень
    if (!h) {
        h = new Node(x);
        return true;
    }
    if (x < h->key) {
        recursiveInsert(h->left, x);
        rotateRight(h); }
    else if (x > h->key) {
        recursiveInsert(h->right, x);
        rotateLeft(h); }
    else return false;
    return true;
}


void WeightedTree::insert(int x) { //Вставка нового узла в корень (оболочка)
    recursiveInsert(root, x);
    sequence.push_back(root);
}

void partR(Node*&h, int k) //Разбиение по k-му ключу
{
    int t = (h->left == nullptr) ? 0 : h->left->size;
    if (t > k) { partR(h->left, k);
        rotateRight(h); }
    if (t < k) { partR(h->right, k-t-1);
        rotateLeft(h); }
}
void recursiveBalance(Node *& h) //Балансировка
{
    if (!h || (h->size == 1)) return;
    partR(h, h->size / 2);
    recursiveBalance(h->left);
    recursiveBalance(h->right);
}

void WeightedTree::balance( ) { recursiveBalance(root); }; //Балансировка (оболочка)\

Node* joinLR(Node* a, Node*b) { //Объединение поддеревьев
    if (!b) return a;
    partR(b, 0);
    b->left = a;
    calculateSize(b);
    return b;
}


bool recursiveRemove(Node*& h, int v, std::list<Node*> seq) { //Рекурсивное удаление с объединением поддеревьев
    if (!h) return false;
    int w = h->key;
    if (v < w) recursiveRemove(h->left, v, seq);
    if (w < v) recursiveRemove(h->right, v, seq);
    if (v == w) {
        Node* t = h;
        h = joinLR(h->left, h->right);
        if(h) calculateSize(h);
        t->left = t->right = nullptr;
        seq.remove(t);
        delete t;
    }
    return true;
}

bool WeightedTree::erase(int k) {
    return recursiveRemove(root, k, sequence);
} //Рекурсивное удаление

bool recursiveRandomInsert(Node*&h, int x) { //Рандомизированная вставка
    if (!h) {
        h = new Node(x);
        return true;
    }
    ++h->size;
    if (rand( ) < RAND_MAX / (h->size + 1)) {
        recursiveInsert(h, x); return true;
    }
    if (x < h->key)
        recursiveRandomInsert(h->left, x);
    else if (x > h->key)
        recursiveRandomInsert(h->right, x);
    else return false;
    return true;
}

bool WeightedTree::randomInsert(int x) { recursiveRandomInsert(root, x); return true;  }

//Инкремент = шаг по дереву, внутренний обход
ReadIterator& ReadIterator::operator++( )
{
    if (!Ptr) { //Первое обращение?
        return *this; //Не работает без предварительной установки на дерево
    }
    if (Ptr->right) {    // Шаг вправо
        St.push(std::make_pair(Ptr, 1));
        Ptr = Ptr->right;
        while (Ptr->left) { //... и искать крайний левый
            St.push(std::make_pair(Ptr, 0));
            Ptr = Ptr->left;
        }
    }
    else {       // Подъём вверх, пока слева пусто
        std::pair<Node*, int> pp(Ptr, 1);
        while (!St.empty( ) && pp.second) { pp = St.top( ); St.pop( ); }
        if (pp.second) //Шаг вправо — тупик, завершить!
        {  Ptr = nullptr; }
        else Ptr = pp.first;  // Шаг вправо и продолжать
    }
    return (*this);
}

ReadIterator WeightedTree::begin( )const { //Поиск первого элемента множества
    MyStack St;
    Node * p(root);
    if (p) {   //Идём по левой ветви, запоминая путь в стеке
        while (p->left) {
            St.push(std::make_pair(p, 0));
            p = p->left;
        }
    }
    return ReadIterator(p, move(St)); //Создаём итератор, передаём ему стек
}

void WeightedTree::printSequence() {
    for (auto x: sequence) {
        std::cout<<x->key<<" ";
    }
    std::cout<<std::endl;
}

void WeightedTree::concat(WeightedTree &other) {
    for (auto x: other.sequence) insert(x->key);
}

void WeightedTree::merge(WeightedTree &other) {
    for (auto x: other.sequence) insert(x->key);
    sequence.sort();
}

void WeightedTree::subst(WeightedTree &other, int position) {
    if (position >= sequence.size()) concat(other);
    else {
        auto oldSequence = sequence;
        sequence = std::list<Node*> {};
        int i = 0;
        for (auto x: oldSequence) {
            if (i == position) concat(other);
            insert(x->key);
        }
    }
}

void WeightedTree::s_difference(WeightedTree &other) {
    WeightedTree tmp {};
    tmp.unionSet(other);
    tmp.difference(*this);
    difference(other);
    unionSet(tmp);
}

void WeightedTree::difference(WeightedTree &other) {
    for (auto x: other) erase(x);
}

void WeightedTree::unionSet(WeightedTree &other) {
    for (auto x: other) insert(x);
}

void WeightedTree::printElements() {
    for (auto x: *this) std::cout << x << " ";
    std::cout << std::endl;
}
