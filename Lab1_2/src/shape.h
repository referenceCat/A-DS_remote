//
// Created by referencecat on 15.02.24.
//

#ifndef A_DS_REMOTE_SHAPE_H
#define A_DS_REMOTE_SHAPE_H

//======== Файл Shape.h — библиотека фигур =========
#include <list>
#include <iostream>
#include "screen.h"

//==1. Поддерж­ка экрана в форме матрицы символов ==
char screen[Y_MAX][X_MAX];
enum color {
    black = '*', white = '.'
};

void screen_init() {
    for (auto y = 0; y < Y_MAX; ++y)
        for (auto &x: screen[y]) x = white;
}

void screen_destroy() {
    for (auto y = 0; y < Y_MAX; ++y)
        for (auto &x: screen[y]) x = black;
}

bool on_screen(int a, int b) // проверка попадания точки на экран
{ return 0 <= a && a < X_MAX && 0 <= b && b < Y_MAX; }

void put_point(int a, int b) { if (on_screen(a, b)) screen[b][a] = black; }

void put_line(int x0, int y0, int x1, int y1)
/* Алгоритм Брезенхэма для прямой:
рисование отрезка прямой от (x0, y0) до (x1, y1).
Уравнение прямой: b(x–x0) + a(y–y0) = 0.
Минимизируется величина abs(eps), где eps = 2*(b(x–x0)) + a(y–y0).  */
{
    int dx = 1;
    int a = x1 - x0;
    if (a < 0) dx = -1, a = -a;
    int dy = 1;
    int b = y1 - y0;
    if (b < 0) dy = -1, b = -b;
    int two_a = 2 * a;
    int two_b = 2 * b;
    int xcrit = -b + two_a;
    int eps = 0;
    for (;;) { //Формирование прямой линии по точкам
        put_point(x0, y0);
        if (x0 == x1 && y0 == y1) break;
        if (eps <= xcrit) x0 += dx, eps += two_b;
        if (eps >= a || a < b) y0 += dy, eps -= two_a;
    }
}

void screen_clear() { screen_init(); } //Очистка экрана
void screen_refresh() // Обновление экрана
{
    for (int y = Y_MAX - 1; 0 <= y; --y) { // с верхней строки до нижней
        for (auto x: screen[y])                 // от левого столбца до правого
            std::cout << x;
        std::cout << '\n';
    }
}

//== 2. Библиотека фигур ==
struct Shape {   // Виртуальный базовый класс «фигура»
    static std::list<Shape *> shapes;       // Список фигур (один на все фигуры!)
    Shape() { shapes.push_back(this); } //Фигура присоединяется к списку
    virtual Point north() const = 0;  //Точки для привязки
    virtual Point south() const = 0;

    virtual Point east() const = 0;

    virtual Point west() const = 0;

    virtual Point neast() const = 0;

    virtual Point seast() const = 0;

    virtual Point nwest() const = 0;

    virtual Point swest() const = 0;

    virtual void draw() = 0;        //Рисование
    virtual void move(int, int) = 0;    //Перемещение
    virtual void resize(double) = 0;        //Изменение размера
    virtual ~Shape() { shapes.remove(this); } //Деструктор
};

std::list<Shape *> Shape::shapes;   // Размещение списка фигур
void shape_refresh()    // Перерисовка всех фигур на экране
{
    screen_clear();
    for (auto p: Shape::shapes) p->draw(); //Динамическое связывание!!!
    screen_refresh();
}

class Rotatable : virtual public Shape { //Фигуры, пригодные к повороту
public:
    virtual void rotate_left() = 0;    //Повернуть влево
    virtual void rotate_right() = 0;    //Повернуть вправо
};

class Reflectable : virtual public Shape { // Фигуры, пригодные
public:                         // к зеркальному отражению
    virtual void flip_horisontally() = 0;    // Отразить горизонтально
    virtual void flip_vertically() = 0;               // Отразить вертикально
};

class Line : public Shape {        // ==== Прямая линия ====
/* отрезок прямой ["w", "e"].
   north( ) определяет точку «выше центра отрезка и так далеко
   на север, как самая его северная точка», и т. п. */
protected:
    Point w, e;
public:
    Line(Point a, Point b) : w(a), e(b) {}; //Произвольная линия (по двум точкам)
    Line(Point a, int L) : w(Point(a.x + L - 1, a.y)), e(a) {}; //Горизонтальная линия
    Point north() const { return Point((w.x + e.x) / 2, e.y < w.y ? w.y : e.y); }

    Point south() const { return Point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }

    Point east() const { return Point(e.x < w.x ? w.x : e.x, (w.y + e.y) / 2); }

    Point west() const { return Point(e.x < w.x ? e.x : w.x, (w.y + e.y) / 2); }

    Point neast() const { return Point(w.x < e.x ? e.x : w.x, e.y < w.y ? w.y : e.y); }

    Point seast() const { return Point(w.x < e.x ? e.x : w.x, e.y < w.y ? e.y : w.y); }

    Point nwest() const { return Point(w.x < e.x ? w.x : e.x, e.y < w.y ? w.y : e.y); }

    Point swest() const { return Point(w.x < e.x ? w.x : e.x, e.y < w.y ? e.y : w.y); }

    void move(int a, int b) {
        w.x += a;
        w.y += b;
        e.x += a;
        e.y += b;
    }

    void draw() { put_line(w, e); }

    void resize(double d)                // Изменение длины линии в (d) раз
    {
        e.x = w.x + (e.x - w.x) * d;
        e.y = w.y + (e.y - w.y) * d;
    }
};

class Rectangle : public Rotatable {      // ==== Прямоугольник ====
/* nw ------ n ------ ne
   |		       |
   |		       |
   w	   c            e
   |		       |
   |		       |
   sw ------- s ------ se */
protected:
    Point sw, ne;
public:
    Rectangle(Point a, Point b) : sw(a), ne(b) {}

    Point north() const { return Point((sw.x + ne.x) / 2, ne.y); }

    Point south() const { return Point((sw.x + ne.x) / 2, sw.y); }

    Point east() const { return Point(ne.x, (sw.y + ne.y) / 2); }

    Point west() const { return Point(sw.x, (sw.y + ne.y) / 2); }

    Point neast() const { return ne; }

    Point seast() const { return Point(ne.x, sw.y); }

    Point nwest() const { return Point(sw.x, ne.y); }

    Point swest() const { return sw; }

    void rotate_right()           // Поворот вправо относительно se
    {
        int w = ne.x - sw.x, h = ne.y - sw.y; // (учитывается масштаб по осям)
        sw.x = ne.x - h * 2;
        ne.y = sw.y + w / 2;
    }

    void rotate_left() // Поворот влево относительно sw
    {
        int w = ne.x - sw.x, h = ne.y - sw.y;
        ne.x = sw.x + h * 2;
        ne.y = sw.y + w / 2;
    }

    void move(int a, int b) {
        sw.x += a;
        sw.y += b;
        ne.x += a;
        ne.y += b;
    }

    void resize(double d) {
        ne.x = sw.x + (ne.x - sw.x) * d;
        ne.y = sw.y + (ne.y - sw.y) * d;
    }

    void draw() {
        put_line(nwest(), ne);
        put_line(ne, seast());
        put_line(seast(), sw);
        put_line(sw, nwest());
    }
};

void up(Shape &p, const Shape &q) // поместить фигуру p над фигурой q
{    //Это ОБЫЧНАЯ функция, не член класса! Динамическое связывание!!
    Point n = q.north();
    Point s = p.south();
    p.move(n.x - s.x, n.y - s.y + 1);
}

#endif //A_DS_REMOTE_SHAPE_H
