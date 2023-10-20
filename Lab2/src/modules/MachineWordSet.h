//
// Created by referencecat on 06.10.23.
//

#ifndef A_DS_REMOTE_MACHINEWORDSET_H
#define A_DS_REMOTE_MACHINEWORDSET_H
#include <iostream>


class MachineWordSet {
private:
    static int N, cnt; // мощность универсума и счётчик множеств
    int n;// мощность множества
    char S;
    unsigned short data;
public: // Открытая часть — функции для работы с множеством
    MachineWordSet operator|(const MachineWordSet &) const; // объединение
    MachineWordSet operator&(const MachineWordSet &) const; // пересечение
    MachineWordSet operator~() const; // дополнение до универсума
    void Show(); // вывод множества на экран
    int power() { return n; } // получение мощности
    MachineWordSet(char); // конструктор множества
    MachineWordSet(); // ещё конструктор — по умолчанию
    MachineWordSet(const MachineWordSet &); // конструктор копии
    MachineWordSet operator=(const MachineWordSet &); // оператор присваивания
    ~MachineWordSet(); // деструкторконстру
};

#endif //A_DS_REMOTE_MACHINEWORDSET_H
