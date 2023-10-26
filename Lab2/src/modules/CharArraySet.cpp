//
// Created by referencecat on 06.10.23.
//

#include "CharArraySet.h"
#include <cstring>

#include "utils/generator.h"

std::ostream &operator<<(std::ostream &o, const CharArraySet &object) {
    for (int i = 0; i < object.n; ++i) {
        o << "[" << object.S << "]"
          << " " << object.char_array[i] << "\n";
    }
    return o << object.char_array;
}
CharArraySet CharArraySet::operator&(const CharArraySet &other) const {
    CharArraySet tmp(*this);
    return (tmp &= other);
}
CharArraySet CharArraySet::operator&=(const CharArraySet &other) {
    CharArraySet tmp(*this);
    n = 0;
    for (int i = 0; i < tmp.n; ++i) {
        for (int j = 0; j < other.n; ++j) {
            if (tmp.char_array[i] == other.char_array[j])
                this->char_array[n++] = tmp.char_array[i];
        }
    }
    this->char_array[n] = 0;
    return *this;
}
CharArraySet CharArraySet::operator|(const CharArraySet &other) const {
    CharArraySet tmp(*this);
    return (tmp |= other);
}
CharArraySet CharArraySet::operator|=(const CharArraySet &other) {
    for (int i = 0; i < other.n; ++i) {
        bool found = false;
        for (int j = 0; j < this->n; ++j) {
            if (this->char_array[j] == other.char_array[i]) {
                found = true;
            }
        }
        if (!found) {
            this->char_array[n++] = other.char_array[i];
        }
    }
    this->char_array[n] = 0;
    return *this;
}
CharArraySet CharArraySet::operator~() const {
    CharArraySet tmp;
    for (int i = 0; i < 9; ++i) {
        bool found = false;
        for (int j = 0; j < n; ++j) {
            if (this->char_array[j] == i + '0') {
                found = true;
                break;
            }
        }
        if (!found) {
            tmp.char_array[tmp.n++] = i + '0';
        }
    }
    tmp.char_array[tmp.n] = 0;
    return tmp;
}
CharArraySet::CharArraySet() : n(0), S('A' + cnt++) {
    char_array = new char[N + 1];
    char_array[n++] = 0;
}
CharArraySet::CharArraySet(char) : S('A' + cnt++) {
    char_array = utils::generate_char_set(10);
    std::cout << "Generated set: " << S << "\n";
    std::cout << this;
}
CharArraySet::CharArraySet(const CharArraySet &other) : S('A' + cnt++), n(other.n) {
    char_array = new char[N + 1];
    std::memcpy(char_array, other.char_array, n);
    char_array[n] = 0;
}
CharArraySet &CharArraySet::operator=(const CharArraySet &other) {
    if (this != &other) {
        n = other.n;
        std::memcpy(char_array, other.char_array, n);
        char_array[n] = 0;
    }
    return *this;
}
CharArraySet::CharArraySet(CharArraySet &&other) noexcept : S('A' + cnt++), n(other.n) {
    char_array = other.char_array;
    other.char_array = nullptr;
}
CharArraySet &CharArraySet::operator=(CharArraySet &&other) noexcept {
    if (this != &other) {
        n = other.n;
        std::memcpy(char_array, other.char_array, n);
        // I think it should be copied, but I'm not sure.
        S = 'A' + cnt++;
        delete[] other.char_array;
    }
    return *this;
}