//
// Created by referencecat on 28.05.24.
//
#include <fstream>
#include "iostream"
#include "chrono"
#include "../src/WeightedTree.h"
#define POWER_MIN 10
#define POWER_MAX 1000
#define UNIVERSUM_SIZE 10000

void generateRandomSequence(WeightedTree& tree, int power, int universum_size) { // как в методичке
    tree.clear();
    for(int i = 0; i < power; ++i) {
        tree.insert(std::rand() % universum_size);
    }
}

int main( )
{  using std::cout;
    using namespace std::chrono;
    setlocale(LC_ALL, "Russian");
    srand((unsigned int)7);      //Пока здесь константа, данные повторяются
//    srand((unsigned int)time(nullptr)); //Разблокировать для случайных данных
    auto rand = [ ] (int d) { return std::rand( )%d; }; //Лямбда-функция!
    std::ofstream fout(R"(C:\Users\referenceCat\CLionProjects\A-DS_remote\sem2\Lab3\tests\in.txt)");   //Открытие файла для результатов
    //=== Данные ===
    WeightedTree sequenceA;
    WeightedTree sequenceB;
    WeightedTree sequenceC;
    WeightedTree sequenceD;
    WeightedTree sequenceE;
    WeightedTree sequenceF;
    WeightedTree sequenceG;
    WeightedTree result;
    for (int power = POWER_MIN; power <= POWER_MAX; power++) {
        std::cout<<"test: "<<power<<std::endl;
        generateRandomSequence(sequenceA, power, UNIVERSUM_SIZE);
        generateRandomSequence(sequenceB, power, UNIVERSUM_SIZE);
        generateRandomSequence(sequenceC, power, UNIVERSUM_SIZE);
        generateRandomSequence(sequenceD, power, UNIVERSUM_SIZE);
        generateRandomSequence(sequenceE, power, UNIVERSUM_SIZE);
        generateRandomSequence(sequenceF, power, UNIVERSUM_SIZE);
        generateRandomSequence(sequenceG, power, UNIVERSUM_SIZE);

        result.clear();
        auto t1 = std::chrono::high_resolution_clock::now( );
        result.unionSet(sequenceA);
        result.unionSet(sequenceB);
        result.difference(sequenceC);
        result.s_difference(sequenceD);
        result.merge(sequenceE);
        result.concat(sequenceF);
        result.subst(sequenceG, rand(result.size()));
        auto t2 = std::chrono::high_resolution_clock::now( );
        auto dt = duration_cast<duration<double,std::micro>>(t2-t1).count( );
        fout << power << '\t' << dt << std::endl; //Выдача в файл
    }
    fout.flush();
    fout.close();
    return 0;
}
