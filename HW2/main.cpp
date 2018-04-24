#include "tokens.h"
#include "grammar.h"
#include "hw2.h"
#include <cstring>

int main(int argc, char *argv[]) {
    bool parse = true;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-nullable") == 0) {
            compute_nullable();
            parse = false;
            continue;
        }
        if (strcmp(argv[i], "-first") == 0) {
            compute_first();
            parse = false;
            continue;
        }
        if (strcmp(argv[i], "-follow") == 0) {
            compute_follow();
            parse = false;
            continue;
        }
        if (strcmp(argv[i], "-select") == 0) {
            compute_select();
            parse = false;
            continue;
        }
    }
    if (parse) {
        parser();
    }
}