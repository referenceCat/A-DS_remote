//
// Created by referencecat on 06.10.23.
//

#ifndef A_DS_REMOTE_CHARARRAYSET_H
#define A_DS_REMOTE_CHARARRAYSET_H

#include <iostream>

class CharArraySet {
private:              // Закрытая часть класса — данные
    static int N, cnt;// мощность универсума и счётчик множеств
    int n;            // мощность множества
    char S;
    char *char_array;                                       // тег и память для множества
public:                                                     // Открытая часть — функции для работы с множеством
    CharArraySet operator|(const CharArraySet &other) const;// объединение
    CharArraySet operator|=(const CharArraySet &other);     // объединение с присваиванием
    CharArraySet operator&(const CharArraySet &other) const;// пересечение
    CharArraySet operator&=(const CharArraySet &other);     // пересечение с присваиванием
    CharArraySet operator~() const;                         // дополнение до универсума
    int power() const { return n; }                         // получение мощности
    explicit CharArraySet(char);                            // конструктор множества
    CharArraySet();                                         // ещё конструктор — по умолчанию
    CharArraySet(const CharArraySet &other);                // конструктор копии
    CharArraySet &operator=(const CharArraySet &other);     // оператор присваивания
    CharArraySet &operator=(CharArraySet &&other) noexcept;
    CharArraySet(CharArraySet &&other) noexcept;
    ~CharArraySet();

    friend std::ostream &operator<<(std::ostream &, const CharArraySet &other);// вывод множества на экран
};


#endif//A_DS_REMOTE_CHARARRAYSET_H
