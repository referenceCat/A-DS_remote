//
// Created by referencecat on 06.10.23.
//

#ifndef A_DS_REMOTE_MACHINEWORDSET_H
#define A_DS_REMOTE_MACHINEWORDSET_H
#include <iostream>

#include <iostream>

class MachineWordSet {
private:
    static int N, cnt;// мощность универсума и счётчик множеств
    int n;            // мощность множества
    char S;
    unsigned short data;

public:                                                         // Открытая часть — функции для работы с множеством
    MachineWordSet operator|(const MachineWordSet &other) const;// объединение
    MachineWordSet operator&(const MachineWordSet &other) const;// пересечение
    MachineWordSet operator~() const;                           // дополнение до универсума
    int power() { return n; }                                   // получение мощности
    explicit MachineWordSet(char);                                       // конструктор множества
    MachineWordSet();                                           // ещё конструктор — по умолчанию
    MachineWordSet(const MachineWordSet &other);                // конструктор копии
    MachineWordSet& operator=(const MachineWordSet &other);      // оператор присваивания
    MachineWordSet(MachineWordSet &&other)noexcept;                      // конструктор перемещения
    MachineWordSet& operator=(MachineWordSet &&other)noexcept;         // оператор перемещения

    friend std::ostream &operator<<(std::ostream &stream, const MachineWordSet &object);// вывод множества на экран
private:
    int to_cstring(char *result) const;
};

#endif//A_DS_REMOTE_MACHINEWORDSET_H
