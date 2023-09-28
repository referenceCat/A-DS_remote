// Created by Mikhail Buyanov on 22/09/2023.

#include <chrono>
#include <iomanip>
#include <iostream>

#include "utils/generator.h"
#include "utils/utils.h"

struct ListNode {
    char digit;
    ListNode *next = nullptr;
};

struct ListHead {
    int size = 0;
    ListNode *node = nullptr;
};

bool search(ListHead *list, char value) {
    if (list->size == 0) return false;
    ListNode *node;
    for (node = list->node; node->next != nullptr; node = node->next) {
        if (node->digit == value) return true;
    }
    return node->digit == value;
}

void cstring_to_char_list(char *str, ListHead *result) {
    bool in_result;
    result->size = 0;
    result->node = nullptr;
    ListNode *node;
    for (int i = 0; str[i]; i++) {
        if (!search(result, str[i])) {
            if (result->size == 0) {
                result->node = new ListNode;
                node = result->node;
            } else {
                node->next = new ListNode;
                node = node->next;
            }
            node->digit = str[i];
            result->size++;
        }
    }
}

void char_list_to_cstring(ListHead *list, char *result) {
    ListNode *node = list->node;
    for (int i = 0; i < list->size; i++) {
        result[i] = node->digit;
        node = node->next;
    }
    result[list->size] = '\0';
}

void example_function_for_char_list(ListHead *a, ListHead *b, ListHead *c, ListHead *d, ListHead *result) {
    char *digits = "0123456789";
    result->size = 0;
    result->node = nullptr;
    ListNode *node = result->node;
    for (int i = 0; i < 10; i++) {
        if ((search(a, digits[i]) && !(search(b, digits[i]) || search(c, digits[i]))) || search(d, digits[i])) {
            if (result->size == 0) {
                result->node = new ListNode;
                node = result->node;
            } else {
                node->next = new ListNode;
                node = node->next;
            }
            node->digit = digits[i];
            result->size++;
        }
    }
}

void business_logic(char *input_a, char *input_b, char *input_c, char *input_d, char *output_str) {
    ListHead a;
    ListHead b;
    ListHead c;
    ListHead d;

    cstring_to_char_list(input_a, &a);
    cstring_to_char_list(input_b, &b);
    cstring_to_char_list(input_c, &c);
    cstring_to_char_list(input_d, &d);

    ListHead result;

    example_function_for_char_list(&a, &b, &c, &d, &result);


    char_list_to_cstring(&result, output_str);
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
    std::cout << "Time for all cases: " << std::setprecision(10) << average_time * count << "ms" << std::endl;
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


int main() {
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