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
    bool reflected;
public:
    HalfCircle(Point a, Point b, bool r = true) : Rectangle(a, b), reflected(r) {}

    void draw();

    void flip_horisontally() {};   // Отразить горизонтально (пустая функция)
    void flip_vertically() { reflected = !reflected; };    // Отразить вертикально
};

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

// ПРИМЕР ДОБАВКИ: дополнительная функция присоединения…
void down(Shape &p, const Shape &q) {
    Point n = q.south();
    Point s = p.north();
    p.move(n.x - s.x, n.y - s.y - 1);
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
    Rectangle hat(Point(0, 0), Point(14, 5));
    Line brim(Point(0, 15), 17);
    MyShape face(Point(15, 10), Point(27, 18));
    HalfCircle beard(Point(40, 10), Point(50, 20));
    shape_refresh();
    std::cout << "=== Generated... ===\n";
//== 2. Подготовка к сборке ==
    hat.rotate_right();
    brim.resize(2.0);
    face.resize(2.0);
    beard.flip_vertically();
    shape_refresh();
    std::cout << "=== Prepared... ===\n";
//== 3. Сборка изображения ==
//	face.move(0, -10); // Лицо – в исходное положение (если нужно!)
    up(brim, face);
    up(hat, brim);
    down(beard, face);
    shape_refresh();
    std::cout << "=== Ready! ===\n";
    std::cin.get();       //Смотреть результат
    screen_destroy();
    return 0;
}