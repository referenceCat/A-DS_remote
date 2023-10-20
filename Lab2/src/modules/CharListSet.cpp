//
// Created by referencecat on 06.10.23.
//

#include "CharListSet.h"

std::ostream &operator<<(std::ostream &o, const CharListSet &object) {
    char result[11];
    object.list_to_cstring(result);
    o << result;
    return o;
}
int CharListSet::list_to_cstring(char *result) const {
    // TODO: test this for nullptr and iteration
    int i = 0;
    for (Node *node = first; node && node->next; node = node->next) {
        result[i] = node->value;
        i++;
    }
    result[i] = '\0';
}
