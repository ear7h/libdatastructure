//TODO: write test output to a tmp file
//TODO: command line arguments for regex match of test names
//      in the makefile, an "A" (arg) variable will propagate
//      arguments to this program; like `make test T=src/unit.test A=unit1`

#include "test.h"

#include <setjmp.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct T {
    const char * test_name;
    bool failed;
    jmp_buf fatal_ret;
} T;

void test_failf(T * t, const char * fmt, ...) {
    t->failed = true;
    va_list args;
    va_start(args, fmt);
    printf("fail: %s\n\t", t->test_name);
    printf(fmt, args);
    printf("\n");
    va_end(args);
}

void test_fatalf(T * t, const char * fmt, ...) {
    va_list args;
    va_start(args, fmt);
    printf("fail: %s\n\t", t->test_name);
    printf(fmt, args);
    printf("\n");
    longjmp(t->fatal_ret, 0);
    va_end(args);
}

void test_logf(T * t, const char * fmt, ...) {
    va_list args;
    va_start(args, fmt);
    printf("log: %s: ", t->test_name);
    printf(fmt, args);
    printf("\n");
    va_end(args);
}

static void test_pass(T * t) {
    printf("passed: %s\n", t->test_name);
}

int main() {
    size_t name_start = 0;
    size_t name_end = 0;
    size_t fn_idx = 0;
    size_t passes = 0;

    while (test_names[name_end] && test_fn[fn_idx]) {
        name_start = name_end;

        while(true) {
            char c = test_names[name_start];
            switch (c) {
            case ' ':
            case ',':
            case '\n':
            case '\r':
            case '\t':
                name_start++;
                break;
            default:
                goto found_start;
            }
        }
found_start:

        name_end = name_start;

        while(true) {
            char c = test_names[name_end];
            switch (c) {
            case ' ':
            case ',':
            case '\n':
            case '\r':
            case '\t':
                goto found_end;
            default:
                name_end++;
            }
        }
found_end: {};


        // initiallize T
        T t = {0};

        // allocate and store test name
        size_t buflen = name_end - name_start + 1;
        char * buf = (char *) malloc(buflen * sizeof(char));
        strncpy(buf, &test_names[name_start], buflen);
        buf[buflen - 1] = '\0';

        // set testname
        t.test_name = buf;

        // run the test
        if (!setjmp(t.fatal_ret)) {
            test_fn[fn_idx++](&t);
            if (!t.failed) {
                test_pass(&t);
                passes++;
            }
        }
    }

    if (!fn_idx) {
        printf("no tests to be run\n");
    } else {
        printf("passed %ld/%ld tests\n", passes, fn_idx);
    }

    printf("done\n");
}


