//
// Created by referencecat on 06.10.23.
//

#include "MachineWordSet.h"


int MachineWordSet::N = 10;
int MachineWordSet::cnt = 0;

MachineWordSet MachineWordSet::operator|(const MachineWordSet &other) const {
    std::cout << S << " MachineWordSet::operator|" << std::endl;
    MachineWordSet set;
    set.data = data | other.data;
    return set;
}

MachineWordSet MachineWordSet::operator&(const MachineWordSet &other) const {
    std::cout << S << " MachineWordSet::operator&" << std::endl;
    MachineWordSet set;
    set.data = data & other.data;
    return set;
}

MachineWordSet MachineWordSet::operator~() const {
    std::cout << S << " MachineWordSet::operator~" << std::endl;
    MachineWordSet set;
    set.data = ~data;
    return set;
}


MachineWordSet::MachineWordSet(char) : S('A' + cnt++), n(0), data(0) {
    std::cout << S << " MachineWordSet::MachineWordSet(char)" << std::endl;
    for (int i = 0; i < N; ++i) {
        data |= (rand() % 2) << i;
    }
    std::cout << *this << std::endl;
}

MachineWordSet::MachineWordSet() : S('A' + cnt++), n(0), data(0) {
    std::cout << S << " MachineWordSet::MachineWordSet()" << std::endl;
}

MachineWordSet::MachineWordSet(const MachineWordSet &other) : data(other.data), n(other.n), S('A' + cnt++) {
    std::cout << S << " MachineWordSet::MachineWordSet(const MachineWordSet &)" << std::endl;
}

MachineWordSet &MachineWordSet::operator=(const MachineWordSet &other) {
    std::cout << S << " MachineWordSet::operator=(const MachineWordSet &)" << std::endl;
    if (this != &other) {
        n = other.n;
        data = other.data;
    }
    return *this;
}


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
    o << "[" << object.S << "] " << result;
    return o;
}
MachineWordSet::MachineWordSet(MachineWordSet &&other) noexcept {
    std::cout << S << " MachineWordSet::MachineWordSet(MachineWordSet &&)" << std::endl;
    data = other.data;
    n = other.n;
    S = other.S;
}
MachineWordSet &MachineWordSet::operator=(MachineWordSet &&other) noexcept {
    std::cout << S << " MachineWordSet::operator=(MachineWordSet &&)" << std::endl;
    if (this != &other) {
        n = other.n;
        data = other.data;
        S = 'A' + cnt++;
    }
    return *this;
}
