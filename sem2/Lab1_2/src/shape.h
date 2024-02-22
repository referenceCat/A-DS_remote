//
// Created by referencecat on 15.02.24.
//

#ifndef A_DS_REMOTE_SHAPE_H
#define A_DS_REMOTE_SHAPE_H

//======== Файл Shape.h — библиотека фигур =========
#include <list>
#include <iostream>
#include "screen.h"
#include "allegro5/allegro5.h"
#include "allegro5/allegro5.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_image.h"
#include "MyExceptions.h"
//==1. Поддерж­ка экрана ==

ALLEGRO_DISPLAY* screen;
ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_FONT* font;

void screen_init() {

    // Initialize allegro
    if (!al_init()) {
        fprintf(stderr, "Failed to initialize allegro.\n");
    }

    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    screen = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
    al_clear_to_color(al_map_rgb(0, 0, 0));

    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(screen));
    al_install_keyboard();
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    font = al_load_font("/home/referencecat/CLionProjects/A&DS/sem2/Lab1_2/resources/clacon2.ttf", 20, false); // todo relative path
}

void screen_destroy() {
    al_destroy_display(screen);
    al_destroy_event_queue(event_queue);
}

bool on_screen(int a, int b) // проверка попадания точки на экран
{ return 0 <= a && a < SCREEN_WIDTH && 0 <= b && b < SCREEN_HEIGHT; }

void put_line(int x0, int y0, int x1, int y1) {
    if (x0 == x1 && y0 == y1) throw DrawException("abobus");
    al_draw_line(x0, SCREEN_HEIGHT - y0, x1, SCREEN_HEIGHT - y1, al_map_rgb(255, 255, 255), 1);
}

void put_error(int x0, int y0) {
    al_draw_text(font, al_map_rgb(255, 0, 0), x0 - 20, SCREEN_HEIGHT - y0 - 10, false, "ERROR");
}

void screen_clear() {
    al_clear_to_color(al_map_rgb(0, 0, 0));
} //Очистка экрана

class ErrorSign;

//== 2. Библиотека фигур ==
struct Shape {   // Виртуальный базовый класс «фигура»
    static std::list<Shape *> shapes;
protected:
    Point position;
    Shape() {
        try{
            shapes.push_back(this);
        } catch (std::runtime_error e) {
        std::cerr << "ERROR" << std::endl;
    }

    } //Фигура присоединяется к списку

public:
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
    virtual ~Shape(); //Деструктор
};

std::list<Shape *> Shape::shapes;   // Размещение списка фигур
void shape_refresh()    // Перерисовка всех фигур на экране
{
    screen_clear();
    for (auto p: Shape::shapes) {
        try {
            p->draw(); //Динамическое связывание!!!
        } catch (std::exception exception) {
            std::cerr << exception.what() << std::endl;
            put_error(p->north().x, p->west().y);
        }

    }
    al_flip_display();
}

class Rotatable : virtual public Shape { //Фигуры, пригодные к повороту
public:
    virtual void rotate_left() = 0;    //Повернуть влево
    virtual void rotate_right() = 0;    //Повернуть вправо
};

class Reflectable : virtual public Shape { // Фигуры, пригодные
public:                         // к зеркальному отражению
    virtual void flip_horizontally() = 0;    // Отразить горизонтально
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
    Rectangle(Point a, Point b) : sw(a), ne(b) {
        if (a.x >= b.x || a.y >= b.y) throw ShapeParametersException("wrong points positions for rectangle initialisation");
    }

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
        sw.x = ne.x - h;
        ne.y = sw.y + w;
    }

    void rotate_left() // Поворот влево относительно sw
    {
        int w = ne.x - sw.x, h = ne.y - sw.y;
        ne.x = sw.x + h;
        ne.y = sw.y + w;
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
