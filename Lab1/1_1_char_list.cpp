// Created by Mikhail Buyanov on 22/09/2023.

#include <iostream>

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


    char result_str[11];
    char_list_to_cstring(&result, result_str);
    std::cout << "E=" << result_str << "\n";
    return 0;
}