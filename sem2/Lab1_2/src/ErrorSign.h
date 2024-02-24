//
// Created by referencecat on 21.02.24.
//

#ifndef A_DS_REMOTE_ERRORSIGN_H
#define A_DS_REMOTE_ERRORSIGN_H
#include "shape.h"
#include <iostream>


class ErrorSign: public Shape {
    int x, y;
public:
    Point north() const override {
        return Point(x, y);
    }

    Point south() const override {
        return Point(x, y);
    }

    Point east() const override {
        return Point(x, y);
    }

    Point west() const {
        return Point(x, y);
    }

    Point neast() const override {
        return Point(x, y);
    }

    Point seast() const override {
        return Point(x, y);
    }

    Point nwest() const override {
        return Point(x, y);
    }

    Point swest() const override {
        return Point(x, y);
    }


    void move(int x0, int y0) override { x = x0; y = y0; };
    void resize(double) override {};

    ErrorSign(int x, int y): x(x), y(y) {}

    ErrorSign(): x(50), y(50) {}

    void draw() override {
        put_error(x, y);
    }
};


#endif //A_DS_REMOTE_ERRORSIGN_H
