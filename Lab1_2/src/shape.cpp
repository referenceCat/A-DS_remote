//
// Created by referencecat on 15.02.24.
//

//========== Файл Shape.cpp (прикладная программа) ==========
// Пополнение и использование библиотеки фигур
#include "shape.h"

void HalfCircle::draw()   //Алгоритм Брезенхэма для окружностей
{            // (выдаются два сектора, указываемые значением reflected)
    int x0 = (sw.x + ne.x) / 2, y0 = reflected ? sw.y : ne.y;
    int radius = (ne.x - sw.x) / 2;
    int x = 0, y = radius, delta = 2 - 2 * radius, error = 0;
    while (y >= 0) { // Цикл рисования
        if (reflected) {
            put_point(x0 + x, y0 + y * 0.7);
            put_point(x0 - x, y0 + y * 0.7);
        }
        else {
            put_point(x0 + x, y0 - y * 0.7);
            put_point(x0 - x, y0 - y * 0.7);
        }
        error = 2 * (delta + y) - 1;
        if (delta < 0 && error <= 0) {
            ++x;
            delta += 2 * x + 1;
            continue;
        }
        error = 2 * (delta - x) - 1;
        if (delta > 0 && error > 0) {
            --y;
            delta += 1 - 2 * y;
            continue;
        }
        ++x;
        delta += 2 * (x - y);
        --y;
    }
}

MyShape::MyShape(Point a, Point b)
        : Rectangle(a, b),    //Инициализация базового класса
          w(neast().x - swest().x + 1), // Инициализация данных
          h(neast().y - swest().y + 1), // – строго в порядке объявления!
          l_eye(Point(swest().x + 2, swest().y + h * 3 / 4), 2),
          r_eye(Point(swest().x + w - 4, swest().y + h * 3 / 4), 2),
          mouth(Point(swest().x + 2, swest().y + h / 4), w - 4) {}

void MyShape::draw() {
    Rectangle::draw();      //Контур лица (глаза и нос рисуются сами!)
    int a = (swest().x + neast().x) / 2;
    int b = (swest().y + neast().y) / 2;
    put_point(Point(a, b));   // Нос – существует только на рисунке!
}

void MyShape::move(int a, int b) {
    Rectangle::move(a, b);
    l_eye.move(a, b);
    r_eye.move(a, b);
    mouth.move(a, b);
}

