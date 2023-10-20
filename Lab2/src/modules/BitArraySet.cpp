//
// Created by referencecat on 06.10.23.
//

#include "BitArraySet.h"

std::ostream &operator<<(std::ostream &o, const BitArraySet &object) {
    char result[11];
    object.bit_array_to_cstring(result);
    o << result;
    return o;
}
int BitArraySet::bit_array_to_cstring(char *result) const {
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
