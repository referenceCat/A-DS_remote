//
// Created by referencecat on 06.10.23.
//

#include "CharListSet.h"


int CharListSet::N = 10;
int CharListSet::cnt = 0;

std::ostream &operator<<(std::ostream &o, const CharListSet &object) {
    char result[11] = {0};
    object.to_cstring(result);
    o << "[" << object.S << "] " << result;
    return o;
}
int CharListSet::to_cstring(char *result) const {
    // TODO: test this for nullptr and iteration
    int i = 0;
    for (const Node *node = first; node; node = node->next) {
        result[i] = node->value + '0';
        i++;
    }
        result[i] = '\0';
}
CharListSet CharListSet::operator|(const CharListSet &other) const {
    std::cout << "operator|(const CharListSet &other) " << std::endl;
    CharListSet result(*this);
    for (Node *node = other.first; node; node = node->next) {
        bool found = false;
        for (Node *node2 = first; node2; node2 = node2->next) {
            if (node2->value == node->value) {
                found = true;
            }
        }
        if (!found) {
            result.add(node->value);
        }
    }
    return result;
}
void CharListSet::add(const char &value) {
    Node *node = new Node{nullptr, value};
    if (!first) {
        first = node;
    } else {
        Node *iter = first;

        while (iter && iter->next) {
            iter = iter->next;
        }
        iter->next = node;
    }
}
CharListSet CharListSet::operator&(const CharListSet &other) const {
    std::cout << "operator&(const CharListSet &other) " << std::endl;
    CharListSet result;
    for (Node *node = other.first; node; node = node->next) {
        bool found = false;
        for (Node *node2 = first; node2; node2 = node2->next) {
            if (node2->value == node->value) {
                found = true;
                break;
            }
        }
        if (found) {
            result.add(node->value);
        }
    }
    return result;
}
CharListSet CharListSet::operator~() const {
    std::cout << "operator~()" << std::endl;
    CharListSet result;
    for (int i = 0; i < 10; ++i) {
        bool found = false;
        for (Node *node = first; node; node = node->next) {
            if (node->value == i) {
                found = true;
            }
        }
        if (!found) {
            result.add(i);
        }
    }

    return result;
}
CharListSet::CharListSet(char) : S('A' + cnt++), n(0) {
    std::cout << "CharListSet::CharListSet(char)" << std::endl;
    first = nullptr;
    for (int i = 0; i < 9; ++i) {
        if (rand() % 2) {
            add(i);
        }
    }
    std::cout << *this << std::endl;
}
CharListSet::CharListSet() : S('A' + cnt++), n(0) {
    std::cout << "CharListSet::CharListSet()" << std::endl;
    first = nullptr;
    std::cout << *this << std::endl;
}
CharListSet::CharListSet(const CharListSet &other) : S('A' + cnt++), n(other.n) {
    std::cout << "CharListSet::CharListSet(const CharListSet &other)" << std::endl;
    this->first = nullptr;
    for (Node *node = other.first; node; node = node->next) {
        add(node->value);
    }
}
CharListSet::CharListSet(CharListSet &&other) noexcept {
    std::cout << "CharListSet::CharListSet(CharListSet &&other) noexcept" << std::endl;
    S = other.S;
    n = other.n;
    first = other.first;
    other.first = nullptr;
}
CharListSet &CharListSet::operator=(CharListSet &&other) noexcept {
    std::cout << "CharListSet &CharListSet::operator=(CharListSet &&other) noexcept" << std::endl;
    if (this != &other) {
        S = other.S;
        n = other.n;
        first = other.first;
        other.first = nullptr;
    }
    return *this;
}
CharListSet::~CharListSet() {
    std::cout << "CharListSet::~CharListSet() " << S << std::endl;
    for (Node *node = first; node; node = first) {
        first = node->next;
        delete node;
    }
}
CharListSet &CharListSet::operator=(const CharListSet &other) {
    std::cout << "CharListSet &CharListSet::operator=(const CharListSet &other)" << std::endl;
    if (this != &other) {
        n = other.n;
        first = nullptr;
        for (Node *node = other.first; node; node = node->next) {
            add(node->value);
        }
    }
    return *this;
}
