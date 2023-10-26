//
// Created by referencecat on 06.10.23.
//

#include "BitArraySet.h"
#include <cstring>

std::ostream &operator<<(std::ostream &o, const BitArraySet &object) {
    char result[11];
    object.to_cstring(result);
    o << result;
    return o;
}
int BitArraySet::to_cstring(char *result) const {
    static constexpr char digits[] = "0123456789";
    int size = 0;
    for (int i = 0; i < 10; i++) {
        if (this->bit_array[i]) {
            *result = digits[i];
            result++;
            size++;
        }
    }
    *result = 0;
    return size;
}
BitArraySet::BitArraySet(char) : S('A' + cnt++), n(0), bit_array(new bool[N]) {
    for (int i = 0; i < N; i++) {
        bit_array[i] = (rand() % 2);
    }
}
BitArraySet::BitArraySet() : S('A' + cnt++), n(0), bit_array(new bool[N]) {
    bit_array = {};
}
BitArraySet::BitArraySet(const BitArraySet &other) : S('A' + cnt++), n(other.n) {
    bit_array = new bool[N];
    for (int i = 0; i < N; i++) {
        bit_array[i] = other.bit_array[i];
    }
}
BitArraySet::BitArraySet(BitArraySet &&other) noexcept : S('A' + cnt++), n(other.n) {
    bit_array = other.bit_array;
    other.bit_array = nullptr;
}
BitArraySet &BitArraySet::operator=(BitArraySet &&other) noexcept {
    if (this != &other) {
        n = other.n;
        std::memcpy(bit_array, other.bit_array, N);
        delete[] other.bit_array;
    }
    return *this;
}
BitArraySet BitArraySet::operator|(const BitArraySet &other) const {
    BitArraySet result(*this);
    for (int i = 0; i < N; ++i) {
        result.bit_array[i] |= other.bit_array[i];
    }
    return result;
}
BitArraySet BitArraySet::operator&(const BitArraySet &other) const {
    BitArraySet result(*this);
    for (int i = 0; i < N; ++i) {
        result.bit_array[i] &= other.bit_array[i];
    }
    return result;
}
BitArraySet BitArraySet::operator~() const {
    BitArraySet result(*this);
    for (int i = 0; i < N; ++i) {
        result.bit_array[i] = !bit_array[i];
    }
    return result;
}
BitArraySet &BitArraySet::operator=(const BitArraySet &other) {
    if (this != &other) {
        n = other.n;
        std::memcpy(bit_array, other.bit_array, N);
    }
    return *this;
}
