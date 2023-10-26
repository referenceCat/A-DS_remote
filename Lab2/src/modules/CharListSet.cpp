//
// Created by referencecat on 06.10.23.
//

#include "CharListSet.h"

std::ostream &operator<<(std::ostream &o, const CharListSet &object) {
    char result[11];
    object.to_cstring(result);
    o << result;
    return o;
}
int CharListSet::to_cstring(char *result) const {
    // TODO: test this for nullptr and iteration
    int i = 0;
    for (Node *node = first; node && node->next; node = node->next) {
        result[i] = node->value;
        i++;
    }
    result[i] = '\0';
}
CharListSet CharListSet::operator|(const CharListSet &other) const {
    CharListSet result(*this);
    for (Node *node = other.first; node && node->next; node = node->next) {
        bool found = false;
        for (Node *node2 = first; node2 && node2->next; node2 = node2->next) {
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
    }
    Node *iter = first;
    while (iter && iter->next) {
        iter = iter->next;
    }
    iter->next = node;
}
CharListSet CharListSet::operator&(const CharListSet &other) const {
    CharListSet result;
    for (Node *node = other.first; node && node->next; node = node->next) {
        bool found = false;
        for (Node *node2 = first; node2 && node2->next; node2 = node2->next) {
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
    CharListSet result;
    for (int i = 0; i < 9; ++i) {
        bool found = false;
        for (Node *node = first; node && node->next; node = node->next) {
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
    for (int i = 0; i < 9; ++i) {
        if (rand() % 2) {
            add(i);
        }
    }
}
CharListSet::CharListSet() : S('A' + cnt++), n(0) {
}
CharListSet::CharListSet(const CharListSet &other) : S('A' + cnt++), n(other.n) {
    for (Node *node = other.first; node && node->next; node = node->next) {
        add(node->value);
    }
}
CharListSet::CharListSet(CharListSet &&other) noexcept {
    S = other.S;
    n = other.n;
    first = other.first;
    other.first = nullptr;
}
CharListSet &CharListSet::operator=(CharListSet &&other) noexcept {
    if (this != &other) {
        S = other.S;
        n = other.n;
        first = other.first;
        other.first = nullptr;
    }
    return *this;
}
CharListSet::~CharListSet() {
    for (Node *node = first; node; node = first) {
        first = node->next;
        delete node;
    }
}
CharListSet &CharListSet::operator=(const CharListSet &other) {
    if (this != &other) {
        n = other.n;
        for (Node *node = other.first; node && node->next; node = node->next) {
            add(node->value);
        }
    }
    return *this;
}
