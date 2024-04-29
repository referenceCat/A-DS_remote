//
// Created by referencecat on 15.02.24.
//

//========== Файл main.cpp (прикладная программа) ==========
// Пополнение и использование библиотеки фигур
// #include "pch.h"	//связь с ОС (пример для Visual C++2017)
#include "../src/screen.h"
#include "../src/shape.h"
#include "allegro5/allegro5.h"
#include <cmath>
#include "../src/ErrorSign.h"
#include "iostream"
#define SCREEN_SIZE_COEFFICIENT 10
#define PHI_STEP 0.1

// ПРИМЕР ДОБАВКИ: дополнительный фрагмент – полуокружность
class HalfCircle : public Rectangle, public Reflectable {
    int direction; // 0 - right, 1 - up, 2 - left, 3 - down;
public:
    HalfCircle(Point a, int radius) : Rectangle(a, Point(a.x + radius * 2, a.y + radius)), direction(1) {
        if (radius <= 0) throw ShapeParametersException("wrong radius value for half_circle initialisation");
    }

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

void HalfCircle::draw() {
    int x0, y0;
    double phi_first, phi_last;
    switch (direction) {
        case 0:
            x0 = west().x;
            y0 = (north().y + south().y) / 2;
            phi_first = M_PI * -1/2;
            phi_last = M_PI * 1/2;
            break;

        case 1:
            x0 = (east().x + west().x) / 2;
            y0 = south().y;
            phi_first = M_PI * 0;
            phi_last = M_PI * 1;
            break;

        case 2:
            x0 = east().x;
            y0 = (north().y + south().y) / 2;
            phi_first = M_PI * 1/2;
            phi_last = M_PI * 3/2;
            break;

        case 3:
            x0 = (east().x + west().x) / 2;
            y0 = north().y;
            phi_first = M_PI * 1;
            phi_last = M_PI * 2;
            break;
    }

    int radius = (ne.x - sw.x) < (ne.y - sw.y) ? ne.x - sw.x : ne.y - sw.y;

    double last_phi = phi_first;
    for (double phi = phi_first + PHI_STEP; phi <= phi_last + PHI_STEP; phi += PHI_STEP) {
        put_line(x0 + cos(last_phi) * radius, y0 + sin(last_phi)  * radius, x0 + cos(phi)  * radius, y0 + sin(phi)  * radius);
        last_phi = phi;
    }
    // Rectangle::draw();
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
          l_eye(Point(swest().x + 2*SCREEN_SIZE_COEFFICIENT, swest().y + h * 3 / 4), 2*SCREEN_SIZE_COEFFICIENT),
          r_eye(Point(swest().x + w - 4*SCREEN_SIZE_COEFFICIENT, swest().y + h * 3 / 4), 2*SCREEN_SIZE_COEFFICIENT),
          mouth(Point(swest().x + 2*SCREEN_SIZE_COEFFICIENT, swest().y + h / 4), w - 4*SCREEN_SIZE_COEFFICIENT) {}

void MyShape::draw() {
    Rectangle::draw();      //Контур лица (глаза и нос рисуются сами!)
    int a = (swest().x + neast().x) / 2;
    int b = (swest().y + neast().y) / 2;
    put_line(Point(a, b), Point(a+2, b+2));
}

void MyShape::move(int a, int b) {
    Rectangle::move(a, b);
    l_eye.move(a, b);
    r_eye.move(a, b);
    mouth.move(a, b);
}

int main() {
    Shape* hat;
    Shape* face;
    Shape* brim;
    Shape* beard;

    try {
        auto* init = new Rectangle(Point(0, 50), Point(70, 50)); // should be Point(0, 0), Point(70, 50)
        init->rotate_left();
        hat = init;

    } catch (ShapeParametersException exception) {
        std::cerr << exception.what() << std::endl;
        hat = new ErrorSign(0, 0);
     }

    try {
        auto* init = new MyShape(Point(100, 120), Point(220, 220));
        face = init;

    } catch (ShapeParametersException exception) {
        std::cerr << exception.what() << std::endl;
        face = new ErrorSign(0, 0);
    }

    try {
        auto* init = new Line(Point(0, 150), 110);
        brim = init;

    } catch (ShapeParametersException exception) {
        std::cerr << exception.what() << std::endl;
        brim = new ErrorSign(0, 0);
    }

    try {
        auto* init = new HalfCircle(Point(400, 100), -100);
        init->flip_vertically();

        beard = init;

    } catch (ShapeParametersException exception) {
        std::cerr << exception.what() << std::endl;
        beard = new ErrorSign(0, 0);
    }


    brim->resize(2.0);
    beard->resize(0); // should be 0.6
    // face->resize(2.0);
    up(*brim, *face);
    up(*hat, *brim);
    down(*beard, *face);

    setlocale(LC_ALL, "Rus");
    screen_init();
    shape_refresh();

    // catching ALLEGRO_EVENT_DISPLAY_CLOSE
    bool running = true;
    while (running) {
        ALLEGRO_EVENT event;
        ALLEGRO_TIMEOUT timeout;

        // Initialize timeout
        al_init_timeout(&timeout, 0.06);

        // Fetch the event (if one exists)
        bool get_event = al_wait_for_event_until(event_queue, &event, &timeout);

        if (get_event && event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }
    }
    screen_destroy();
    return 0;
}