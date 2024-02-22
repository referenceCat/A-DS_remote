//
// Created by referencecat on 21.02.24.
//

#ifndef A_DS_REMOTE_RESOURCEEXCEPTION_H
#define A_DS_REMOTE_RESOURCEEXCEPTION_H

#include <string>
#include <utility>
#include "exception"

class ResourceException: public std::runtime_error {
public:
    ResourceException(const char*  s): std::runtime_error(s) {};
};


#endif //A_DS_REMOTE_RESOURCEEXCEPTION_H
