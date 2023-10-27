//
// Created by referencecat on 06.10.23.
//

#include "modules/BitArraySet.h"
#include "modules/CharArraySet.h"
#include "modules/CharListSet.h"
#include "modules/MachineWordSet.h"

#include "modules/utils/utils.h"

void bitArray();
void charArray();
void charList();
void machineWord();

int main() {
    auto time = utils::measure_execution_time(bitArray);
    std::cout << "Measured execution time: " << time << " ms" << std::endl;
    std::cout << "==============================================" << std::endl;
    time = utils::measure_execution_time(charList);
    std::cout << "Measured execution time: " << time << " ms" << std::endl;
    std::cout << "==============================================" << std::endl;
    time = utils::measure_execution_time(machineWord);
    std::cout << "Measured execution time: " << time << " ms" << std::endl;
    std::cout << "==============================================" << std::endl;
    time = utils::measure_execution_time(charArray);
    std::cout << "Measured execution time: " << time << " ms" << std::endl;


    return 0;
}

void bitArray() {
    BitArraySet a('A');
    BitArraySet b('B');
    BitArraySet c('C');
    BitArraySet d('D');


    BitArraySet e = (a & ~(b | c)) | d;
    std::cout << e << std::endl;
}

void charArray() {
    CharArraySet a('A');
    CharArraySet b('B');
    CharArraySet c('C');
    CharArraySet d('D');

    CharArraySet e = (a & ~(b | c)) | d;
    std::cout << e << std::endl;
}

void charList() {
    CharListSet a('A');
    CharListSet b('B');
    CharListSet c('C');
    CharListSet d('D');

    CharListSet e = (a & ~(b | c)) | d;
    std::cout << e << std::endl;
}

void machineWord() {
    MachineWordSet a('A');
    MachineWordSet b('B');
    MachineWordSet c('C');
    MachineWordSet d('D');

    MachineWordSet e = (a & ~(b | c)) | d;
    std::cout << e << std::endl;
}