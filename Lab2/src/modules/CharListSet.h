//
// Created by referencecat on 06.10.23.
//

#ifndef A_DS_REMOTE_CHARLISTSET_H
#define A_DS_REMOTE_CHARLISTSET_H

#include <iostream>

class CharListSet {
private:
    struct Node {
        Node *next;
        char value;
    };                // Закрытая часть класса — данные
    static int N, cnt;// мощность универсума и счётчик множеств
    int n;            // мощность множества
    char S;
    Node *first;// тег и память для множества


    void add(const char &value);

public:                                                   // Открытая часть — функции для работы с множеством
    CharListSet operator|(const CharListSet &other) const;// объединение
    CharListSet operator&(const CharListSet &other) const;// пересечение
    CharListSet operator~() const;                        // дополнение до универсума
    int power() { return n; }                             // получение мощности
    explicit CharListSet(char);                           // конструктор множества
    CharListSet();                                        // ещё конструктор — по умолчанию
    CharListSet(const CharListSet &other);                // конструктор копии
    CharListSet(CharListSet &&other) noexcept;
    CharListSet &operator=(const CharListSet &other);// оператор присваивания
    CharListSet &operator=(CharListSet &&other) noexcept;
    ~CharListSet();// деструкторконстру

    friend std::ostream &operator<<(std::ostream &, const CharListSet &other);// вывод множества на экран
private:
    int to_cstring(char *result) const;
};


#endif//A_DS_REMOTE_CHARLISTSET_H
