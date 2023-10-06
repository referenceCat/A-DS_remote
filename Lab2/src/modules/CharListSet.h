//
// Created by referencecat on 06.10.23.
//

#ifndef A_DS_REMOTE_CHARLISTSET_H
#define A_DS_REMOTE_CHARLISTSET_H


class CharListSet {
private:
    struct Node {
        Node *next;
        char value;
    };// Закрытая часть класса — данные
    static int N, cnt; // мощность универсума и счётчик множеств
    int n;// мощность множества
    char S;
    Node *first; // тег и память для множества
public: // Открытая часть — функции для работы с множеством
    CharListSet operator|(const CharListSet &) const; // объединение
    CharListSet operator&(const CharListSet &) const; // пересечение
    CharListSet operator~() const; // дополнение до универсума
    void Show(); // вывод множества на экран
    int power() { return n; } // получение мощности
    CharListSet(char); // конструктор множества
    CharListSet(); // ещё конструктор — по умолчанию
    CharListSet(const CharListSet &); // конструктор копии
    CharListSet operator=(const CharListSet &); // оператор присваивания
    ~CharListSet(); // деструкторконстру
};


#endif //A_DS_REMOTE_CHARLISTSET_H
