//
// Created by referencecat on 21.02.24.
//

#ifndef A_DS_REMOTE_ERRORSIGN_H
#define A_DS_REMOTE_ERRORSIGN_H
#include "shape.h"
#include "ResourceException.h"
#include <iostream>


class ErrorSign: public Shape {
    const int width = 50, height = 50;
    int x, y;
public:
    Point north() const {
        return Point(x, y);
    }

    //Точки для привязки
    Point south() const {
        return Point(x, y);
    }

    Point east() const {
        return Point(x, y);
    }

    Point west() const {
        return Point(x, y);
    }

    Point neast() const {
        return Point(x, y);
    }

    Point seast() const {
        return Point(x, y);
    }

    Point nwest() const {
        return Point(x, y);
    }

    Point swest() const {
        return Point(x, y);
    }


    void move(int, int) {};
    void resize(double) {};
    ~ErrorSign() override {
        al_destroy_bitmap(error_image_bitmap);
    }

    ErrorSign(int x, int y): x(x), y(y) {
        try {
            error_image_bitmap = al_load_bitmap(path_to_error_image);
            if (!error_image_bitmap) {
                throw ResourceException(path_to_error_image);
            }
        } catch (ResourceException e) {
            std::cerr << "could not load given resource: " << e.what() << std::endl;
        }
    }

    void draw() {
        put_bitmap(x, y, error_image_bitmap);
    }
};


#endif //A_DS_REMOTE_ERRORSIGN_H
