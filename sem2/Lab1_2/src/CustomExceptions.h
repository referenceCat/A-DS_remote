//
// Created by referencecat on 21.02.24.
//

#ifndef A_DS_REMOTE_CUSTOMEXCEPTIONS_H
#define A_DS_REMOTE_CUSTOMEXCEPTIONS_H

#include "string"
#include "exception"

class ShapeParametersException : public std::exception {
    std::string msg= "Wrong parameters for shape initialisation: ";

public:
    ShapeParametersException(const std::string& s) {
        msg += s;
    };

    const char * what() const noexcept override {
        return msg.c_str();
    }
};

class ScreenProcessingException : public std::exception {
    std::string msg= "Error during drawing on screen: ";

public:
    ScreenProcessingException(const std::string& s) {
        msg += s;
    };

    const char * what() const noexcept override {
        return msg.c_str();
    }
};

#endif //A_DS_REMOTE_CUSTOMEXCEPTIONS_H
