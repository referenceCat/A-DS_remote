//
// Created by referencecat on 06.10.23.
//

#ifndef A_DS_REMOTE_CHARARRAYSET_H
#define A_DS_REMOTE_CHARARRAYSET_H

#include <iostream>

class CharArraySet {
private: // Закрытая часть класса — данные
    static int N, cnt; // мощность универсума и счётчик множеств
    int n;// мощность множества
    char S;
    char *char_array; // тег и память для множества
public: // Открытая часть — функции для работы с множеством
    CharArraySet operator|(const CharArraySet &) const; // объединение
    CharArraySet operator&(const CharArraySet &) const; // пересечение
    CharArraySet operator~() const; // дополнение до универсума
    void Show(); // вывод множества на экран
    int power() { return n; } // получение мощности
    CharArraySet(char); // конструктор множества
    CharArraySet(); // ещё конструктор — по умолчанию
    CharArraySet(const CharArraySet &); // конструктор копии
    CharArraySet operator=(const CharArraySet &); // оператор присваивания
    ~CharArraySet() { delete[] char_array; } // деструкторконстру

    friend std::ostream &operator<<(std::ostream &, const CharArraySet &); // вывод множества на экран
};


#endif //A_DS_REMOTE_CHARARRAYSET_H
