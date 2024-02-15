//
// Created by referencecat on 15.02.24.
//

#include "../src/shape.h"
#include "../src/screen.h"

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
    std::cin.get(); //Смотреть исходный набор
//== 2. Подготовка к сборке ==
    hat.rotate_right();
    brim.resize(2.0);
    face.resize(2.0);
    beard.flip_vertically();
    shape_refresh();
    std::cout << "=== Prepared... ===\n";
    std::cin.get(); //Смотреть результат поворотов/отражений
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