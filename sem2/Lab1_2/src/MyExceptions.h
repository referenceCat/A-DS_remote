//
// Created by referencecat on 21.02.24.
//

#ifndef A_DS_REMOTE_MYEXCEPTIONS_H
#define A_DS_REMOTE_MYEXCEPTIONS_H

#include <string>
#include <utility>
#include "exception"

class ShapeParametersException: public std::runtime_error {
public:
    ShapeParametersException(const char*  s): std::runtime_error(s) {};
};

class DrawException: public std::runtime_error {
public:
    DrawException(const char*  s): std::runtime_error(s) {};
};


#endif //A_DS_REMOTE_MYEXCEPTIONS_H
