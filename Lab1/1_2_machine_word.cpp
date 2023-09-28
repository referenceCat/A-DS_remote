#include <chrono>
#include <iomanip>
#include <iostream>

#include "utils/generator.h"
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

void run_tests(int count) {
    double average_time = 0;
    for (int i = 0; i < count; i++) {
        auto input_a = utils::generate_char_set(10);
        auto input_b = utils::generate_char_set(10);
        auto input_c = utils::generate_char_set(10);
        auto input_d = utils::generate_char_set(5);

        char result_str[80] = {0};
        auto elapsed = utils::measure_execution_time(business_logic, input_a, input_b, input_c, input_d, result_str);
        std::cout << "----------------------\n";
        std::cout << "Case " << i << ":\n";
        std::cout << "A=" << input_a << "\n";
        std::cout << "B=" << input_b << "\n";
        std::cout << "C=" << input_c << "\n";
        std::cout << "D=" << input_d << "\n";
        std::cout << "E=" << result_str << "\n";
        std::cout << "Execution time: " << std::setprecision(10) << elapsed << "ms" << std::endl;
        delete[] input_a;
        delete[] input_b;
        delete[] input_c;
        delete[] input_d;
        average_time += elapsed / count;
    }
    std::cout << "======================\n";
    std::cout << "Average time: " << std::setprecision(10) << average_time << "ms" << std::endl;
}
void user_input() {
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
}


int main(int argc, char *argv[]) {

    std::cout << "Select mode: 1 - user input, 2 - random: ";

    int mode = 1;
    std::cin >> mode;
    switch (mode) {
        case 1:
            user_input();
            break;
        case 2:
            std::cout << "Enter number of tests: ";
            int count;
            std::cin >> count;
            std::cout << "Running tests..." << std::endl;
            run_tests(count);
            break;
    }


    return 0;
}
