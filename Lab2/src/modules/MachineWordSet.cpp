//
// Created by referencecat on 06.10.23.
//

#include "MachineWordSet.h"
int MachineWordSet::to_cstring(char *result) const {
    static constexpr char digits[] = "0123456789";
    int size = 0;
    for (int i = 0; i < 10; i++) {
        if (this->data & 1 << i) {
            *result = digits[i];
            result++;
            size++;
        }
    }
    *result = 0;
    return size;
}
std::ostream &operator<<(std::ostream &o, const MachineWordSet &object) {
    char result[11];
    object.to_cstring(result);
    o << result;
    return o;
}
