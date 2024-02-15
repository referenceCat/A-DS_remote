//
// Created by referencecat on 15.02.24.
//

//========== Файл Shape.cpp (прикладная программа) ==========
// Пополнение и использование библиотеки фигур
// #include "pch.h"	//связь с ОС (пример для Visual C++2017)
#include "../src/screen.h"
#include "../src/shape.h"

// ПРИМЕР ДОБАВКИ: дополнительный фрагмент – полуокружность
class HalfCircle : public Rectangle, public Reflectable {
    int direction; // 0 - right, 1 - up, 2 - left, 3 - down;
public:
    HalfCircle(Point a, int radius) : Rectangle(a, Point(a.x + radius * 2, a.y + radius)), direction(1) {}

    void draw();

    void flip_horizontally() {
        if (direction == 0) direction = 2;
        else if (direction == 2) direction = 0;
    }

    void flip_vertically() {
        if (direction == 1) direction = 3;
        else if (direction == 3) direction = 1;
    }

    void rotate_right() {
        Rectangle::rotate_right();
        direction = (direction - 1) % 4;
    }

    void rotate_left() {
        Rectangle::rotate_left();
        direction = (direction + 1) % 4;
    }
};

void HalfCircle::draw()   //Алгоритм Брезенхэма для окружностей
{            // (выдаются два сектора, указываемые значением reflected_horizontally)
    int x0, y0, radius, x, y, delta, error;
    if (direction == 0 || direction == 2) { // направления вверх и вниз
        y0 = (sw.y + ne.y) / 2;
        x0 = direction == 0 ? sw.x : ne.x;
        // put_point(x0, y0);
        radius = (ne.y - sw.y) / 2;
        x = radius;
        y = 0;
        delta = 2 - 2 * radius;
        error = 0;
        while (x >= 0) { // Цикл рисования
            if (direction == 0) {
                put_point(x0 + x, y0 + y * 0.7);
                put_point(x0 + x, y0 - y * 0.7);
            } else {
                put_point(x0 - x, y0 + y * 0.7);
                put_point(x0 - x, y0 - y * 0.7);
            }
            error = 2 * (delta + x) - 1;
            if (delta < 0 && error <= 0) {
                ++y;
                delta += 2 * y + 1;
                continue;
            }
            error = 2 * (delta - y) - 1;
            if (delta > 0 && error > 0) {
                --x;
                delta += 1 - 2 * x;
                continue;
            }
            ++y;
            delta += 2 * (-x + y);
            --x;
        }
    } else {

        x0 = (sw.x + ne.x) / 2;
        y0 = direction == 1 ? sw.y : ne.y;
        // put_point(x0, y0);
        radius = (ne.x - sw.x) / 2;
        x = 0;
        y = radius;

        delta = 2 - 2 * radius;
        error = 0;
        while (y >= 0) { // Цикл рисования
            if (direction == 3) {
                put_point(x0 + x, y0 - y);
                put_point(x0 - x, y0 - y);
            } else {
                put_point(x0 + x, y0 + y);
                put_point(x0 - x, y0 + y);
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
}

// ПРИМЕР ДОБАВКИ: дополнительная функция присоединения…
void down(Shape &p, const Shape &q) {
    Point n = q.south();
    Point s = p.north();
    p.move(n.x - s.x, n.y - s.y - 1);
}

void align_up_right(Shape &moved, const Shape &reference) {
    Point ne = reference.neast();
    Point sw = moved.swest();
    moved.move(ne.x - sw.x + 1, ne.y - sw.y + 1);
}


void align_up_left(Shape &moved, const Shape &reference) {
    Point nw = reference.nwest();
    Point se = moved.seast();
    moved.move(nw.x - se.x - 1, nw.y - se.y + 1);
}


// Cборная пользовательская фигура – физиономия
class MyShape : public Rectangle {      // Моя фигура ЯВЛЯЕТСЯ
    int w, h;                         //        прямоугольником
    Line l_eye;    // левый глаз – моя фигура СОДЕРЖИТ линию
    Line r_eye;   // правый глаз
    Line mouth;  // рот
public:
    MyShape(Point, Point);

    void draw();

    void move(int, int);

    void resize(int) {}
};

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

int main() {
    setlocale(LC_ALL, "Rus");
    screen_init();
//== 1. Объявление набора фигур ==
    Rectangle hat(Point(0, 0), Point(7, 5));
    Line brim(Point(0, 15), 11);
    MyShape face(Point(15, 10), Point(27, 18));
    HalfCircle beard(Point(40, 10), 10);
    HalfCircle bakenbards_l(Point(40, 20), 2);
    HalfCircle bakenbards_r(Point(50, 25), 2);
    HalfCircle horn_l(Point(40, 30), 2);
    HalfCircle horn_r(Point(50, 35), 2);
    shape_refresh();
    std::cout << "=== Generated... ===\n";
//== 2. Подготовка к сборке ==
    brim.resize(2.0);
    face.resize(2.0);
    beard.flip_vertically();
    beard.resize(0.5);
    horn_l.rotate_left();
    horn_r.rotate_left();
    horn_r.flip_horizontally();
    bakenbards_l.rotate_right();
    bakenbards_r.rotate_right();
    bakenbards_l.flip_horizontally();
    shape_refresh();
    std::cout << "=== Prepared... ===\n";
//== 3. Сборка изображения ==
//	face.move(0, -10); // Лицо – в исходное положение (если нужно!)
    up(brim, face);
    up(hat, brim);
    down(beard, face);
    align_up_right(bakenbards_r, beard);
    align_up_right(horn_r, face);
    align_up_left(bakenbards_l, beard);
    align_up_left(horn_l, face);
    shape_refresh();
    std::cout << "=== Ready! ===\n";
    std::cin.get();       //Смотреть результат
    screen_destroy();
    return 0;
}