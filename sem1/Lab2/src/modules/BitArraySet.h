//
// Created by referencecat on 06.10.23.
//

#ifndef A_DS_REMOTE_BITARRAYSET_H
#define A_DS_REMOTE_BITARRAYSET_H


#include <iostream>

class BitArraySet {
private:              // Закрытая часть класса — данные
    static int N, cnt;// мощность универсума и счётчик множеств
    int n;            // мощность множества
    char S;
    bool *bit_array;                                      // тег и память для множества
public:                                                   // Открытая часть — функции для работы с множеством
    BitArraySet operator|(const BitArraySet &other) const;// объединение
    BitArraySet operator&(const BitArraySet &other) const;// пересечение
    BitArraySet operator~() const;                        // дополнение до универсума
    int power() { return n; }                             // получение мощности
    explicit BitArraySet(char);                           // конструктор множества
    BitArraySet();                                        // ещё конструктор — по умолчанию
    BitArraySet(const BitArraySet &other);                // конструктор копии
    BitArraySet(BitArraySet &&other) noexcept;
    BitArraySet &operator=(const BitArraySet &other);// оператор присваивания
    BitArraySet &operator=(BitArraySet &&other) noexcept;
    ~BitArraySet();
    explicit BitArraySet(char *str);

    friend std::ostream &operator<<(std::ostream &stream, const BitArraySet &other);// вывод множества на экран
private:
    int to_cstring(char *result) const;
};


#endif//A_DS_REMOTE_BITARRAYSET_H
