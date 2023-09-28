#include <chrono>
#include <iomanip>
#include <iostream>

#include "utils/utils.h"

unsigned short cstring_to_machine_word(const char *str) {
    unsigned short result = 0;

    for (int j = 0; str[j]; j++) {
        result |= 1 << (str[j] - '0');
    }

    return result;
}

int machine_word_to_cstring(unsigned short word, char *result) {
    char digits[] = "0123456789";
    int size = 0;
    for (int i = 0; i < 10; i++) {
        if (word & 1 << i) {
            *result = digits[i];
            result++;
            size++;
        }
    }
    *result = 0;
    return size;
}

unsigned short example_function_for_machine_word(unsigned short a, unsigned short b, unsigned short c, unsigned short d) {
    return (a & ~(b | c)) | d;
}


void business_logic(char *input_a, char *input_b, char *input_c, char *input_d, char *output_str) {
    unsigned short a = cstring_to_machine_word(input_a);
    unsigned short b = cstring_to_machine_word(input_b);
    unsigned short c = cstring_to_machine_word(input_c);
    unsigned short d = cstring_to_machine_word(input_d);

    unsigned short result = example_function_for_machine_word(a, b, c, d);

    machine_word_to_cstring(result, output_str);
}

int main() {
    char input_a[80];
    char input_b[80];
    char input_c[80];
    char input_d[80];

    std::cout << "A=";
    std::cin >> input_a;
    std::cout << "B=";
    std::cin >> input_b;
    std::cout << "C=";
    std::cin >> input_c;
    std::cout << "D=";
    std::cin >> input_d;

    char result_str[80];

    auto elapsed = utils::measure_execution_time(business_logic, input_a, input_b, input_c, input_d, result_str);
    std::cout << "E=" << result_str << "\n";
    std::cout << "Execution time: " << std::setprecision(10) << elapsed << "ms\n";
    return 0;
}
