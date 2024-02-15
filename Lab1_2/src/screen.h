//
// Created by referencecat on 15.02.24.
//

#ifndef A_DS_REMOTE_SCREEN_H
#define A_DS_REMOTE_SCREEN_H

//=== Файл screen.h -- поддержка работы с экраном
const int X_MAX = 100;  //Размер экрана
const int Y_MAX = 100;

class Point {    //Точка на экране
public:
    int x, y;

    Point(int a = 0, int b = 0) : x(a), y(b) {}
};

// Набор утилит для работы с экраном
void put_point(int a, int b);    // Вывод точки (2 варианта)
void put_point(Point p) { put_point(p.x, p.y); } //
void put_line(int, int, int, int); // Вывод линии (2 варианта)
void put_line(Point a, Point b) { put_line(a.x, a.y, b.x, b.y); }

void screen_init();        // Создание экрана
void screen_destroy();    // Удаление
void screen_refresh();    // Обновление
void screen_clear();               // Очистка

#endif //A_DS_REMOTE_SCREEN_H
