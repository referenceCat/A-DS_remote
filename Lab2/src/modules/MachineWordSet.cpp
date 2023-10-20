//
// Created by referencecat on 06.10.23.
//

#include "MachineWordSet.h"

MachineWordSet MachineWordSet::operator|(const MachineWordSet & other) const {
    MachineWordSet set;
    set.data = data | other.data;
    return set;
}

MachineWordSet MachineWordSet::operator&(const MachineWordSet & other) const {
    MachineWordSet set;
    set.data = data & other.data;
    return set;
}

MachineWordSet MachineWordSet::operator~() const {
    MachineWordSet set;
    set.data = ~data;
    return set;
}