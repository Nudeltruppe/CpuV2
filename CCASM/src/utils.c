#include "include/utils.h"
#include <stdio.h>

void print_tokens(int token_len, token_t* tokens) {
    for (int i = 0; i < token_len; i++) {
        if (tokens[i].type == NUMBER) printf("T: %d V: %d\n", tokens[i].type, tokens[i].imm16_data);
        else printf("T: %d V: %s\n", tokens[i].type, tokens[i].string_data);
    }
}

bool in_bounds(char a, char b, char c) {
    return (a >= b) && (a <= c);
}

void print_labels(size_t label_len, label_t* labels) {
    for (int i = 0; i < (int)label_len; i++) {
        printf("Label: %s -> %d\n", labels[i].name, labels[i].value);
    }
}