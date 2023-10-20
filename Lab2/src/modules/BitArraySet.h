//
// Created by referencecat on 06.10.23.
//

#ifndef A_DS_REMOTE_BITARRAYSET_H
#define A_DS_REMOTE_BITARRAYSET_H


#include <iostream>

class BitArraySet {
private: // Закрытая часть класса — данные
    static int N, cnt; // мощность универсума и счётчик множеств
    int n;// мощность множества
    char S;
    bool *bit_array; // тег и память для множества
public: // Открытая часть — функции для работы с множеством
    BitArraySet operator|(const BitArraySet &) const; // объединение
    BitArraySet operator&(const BitArraySet &) const; // пересечение
    BitArraySet operator~() const; // дополнение до универсума
    int power() { return n; } // получение мощности
    BitArraySet(char); // конструктор множества
    BitArraySet(); // ещё конструктор — по умолчанию
    BitArraySet(const BitArraySet &); // конструктор копии
    BitArraySet operator=(const BitArraySet &); // оператор присваивания
    ~BitArraySet() { delete[] bit_array; } // деструкторконстру

    friend std::ostream &operator<<(std::ostream &, const BitArraySet &); // вывод множества на экран
private:
    int bit_array_to_cstring(char *result) const;
};


#endif //A_DS_REMOTE_BITARRAYSET_H
