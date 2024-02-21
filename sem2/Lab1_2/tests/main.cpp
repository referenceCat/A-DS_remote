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
#define SCREEN_SIZE_COEFFICIENT 10
#define PHI_STEP 0.1

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
    for (double phi = phi_first; phi <= phi_last + PHI_STEP; phi += PHI_STEP) {
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

    Rectangle hat(Point(0, 0), Point(70, 50));
    Line brim(Point(0, 150), 110);
    MyShape face(Point(150, 100), Point(270, 180));
    HalfCircle beard(Point(400, 100), 100);
    HalfCircle bakenbards_l(Point(400, 200), 20);
    HalfCircle bakenbards_r(Point(500, 250), 20);
    HalfCircle horn_l(Point(400, 300), 20);
    HalfCircle horn_r(Point(500, 350), 20);

    // Initialize allegro
    if (!al_init()) {
        fprintf(stderr, "Failed to initialize allegro.\n");
        return 1;
    }


    setlocale(LC_ALL, "Rus");
    screen_init();


    bool running = true;
    int counter = 0;

    while (running) {
        ALLEGRO_EVENT event;
        ALLEGRO_TIMEOUT timeout;

        // Initialize timeout
        al_init_timeout(&timeout, 0.06);

        // Fetch the event (if one exists)
        bool get_event = al_wait_for_event_until(event_queue, &event, &timeout);

        // Handle the event
        if (get_event) {
            switch (event.type) {
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    running = false;
                    break;
                case ALLEGRO_EVENT_KEY_DOWN:
                    if (counter == 0) {
                        shape_refresh();
                    } else if (counter == 1) {
                        brim.resize(2.0);
                        face.resize(2.0);
                        beard.flip_vertically();
                        beard.resize(0.6);
                        horn_l.rotate_left();
                        horn_r.rotate_left();
                        horn_r.flip_horizontally();
                        bakenbards_l.rotate_right();
                        bakenbards_r.rotate_right();
                        bakenbards_l.flip_horizontally();
                        shape_refresh();
                    } else if (counter == 2) {
                        up(brim, face);
                        up(hat, brim);
                        down(beard, face);
                        align_up_right(bakenbards_r, beard);
                        align_up_right(horn_r, face);
                        align_up_left(bakenbards_l, beard);
                        align_up_left(horn_l, face);
                        shape_refresh();
                    }
                    counter += 1;
                default:
                    fprintf(stderr, "Unsupported event received: %d\n", event.type);
                    break;
            }
        }
    }
    screen_destroy();
    return 0;
}