//
// Created by referencecat on 06.10.23.
//

#include "CharArraySet.h"
#include <cstring>

#include "utils/generator.h"


int CharArraySet::N = 10;
int CharArraySet::cnt = 0;

std::ostream &operator<<(std::ostream &o, const CharArraySet &object) {
    o << "[" << object.S << "] " << object.char_array;
    return o;
}
CharArraySet CharArraySet::operator&(const CharArraySet &other) const {
    std::cout << "CharArraySet::operator&(const CharArraySet &other)\n";
    CharArraySet tmp(*this);
    auto res = (tmp &= other);
    return res;
}
CharArraySet CharArraySet::operator&=(const CharArraySet &other) {
    std::cout << "CharArraySet::operator&=(const CharArraySet &other)\n";
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
    std::cout << "CharArraySet::operator|(const CharArraySet &other)\n";
    CharArraySet tmp(*this);
    auto res = (tmp |= other);
    return res;
}
CharArraySet CharArraySet::operator|=(const CharArraySet &other) {
    std::cout << "CharArraySet::operator|=(const CharArraySet &other)\n";
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
    return *this;
}
CharArraySet CharArraySet::operator~() const {
    std::cout << "CharArraySet::operator~()\n";
    CharArraySet tmp;
    for (int i = 0; i < N; ++i) {
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
    std::cout << "CharArraySet::CharArraySet()\n";
    char_array = new char[N + 1];
    char_array[n++] = 0;
}

char *generate_char_set(size_t size, int *generated) {
    bool mask[10];
    char *result = new char[size + 1];

    std::random_device rd;                        // obtain a random number from hardware
    std::mt19937 gen(rd());                       // seed the generator
    std::uniform_int_distribution<> distr(25, 63);// define the range

    for (size_t i = 0; i < size; i++) {
        mask[i] = distr(gen) % 2;
    }
    int index = 0;
    for (size_t i = 0; i < size; i++) {
        if (mask[i]) {
            result[index++] = '0' + i;
            *generated += 1;
        }
    }
    result[index] = '\0';
    return result;
}

CharArraySet::CharArraySet(char) : S('A' + cnt++), n(0) {
    std::cout << "CharArraySet::CharArraySet(char)\n";
    // fill randomly

    char_array = generate_char_set(10, &n);
    std::cout << "Generated set: " << S << "\n";
    std::cout << *this << std::endl;
}
CharArraySet::CharArraySet(const CharArraySet &other) : S('A' + cnt++), n(other.n) {
    std::cout << "CharArraySet::CharArraySet(const CharArraySet &other)\n";
    char_array = new char[N + 1];
    std::memcpy(char_array, other.char_array, N);
}
CharArraySet &CharArraySet::operator=(const CharArraySet &other) {
    std::cout << "CharArraySet::operator=(const CharArraySet &other)\n";
    if (this != &other) {
        n = other.n;
        std::memcpy(char_array, other.char_array, N);
        char_array[n] = 0;
    }
    return *this;
}
CharArraySet::CharArraySet(CharArraySet &&other) noexcept : S(other.S), n(other.n) {
    std::cout << "CharArraySet::CharArraySet(CharArraySet &&other)\n";
    char_array = other.char_array;
    other.char_array = nullptr;
}
CharArraySet &CharArraySet::operator=(CharArraySet &&other) noexcept {
    std::cout << "CharArraySet::operator=(CharArraySet &&other)\n";
    if (this != &other) {
        n = other.n;
        std::memcpy(char_array, other.char_array, n);
        S = other.S;
        delete[] other.char_array;
    }
    return *this;
}
CharArraySet::~CharArraySet() {
    std::cout << S << " CharArraySet::~CharArraySet()\n";
    delete[] char_array;
}
