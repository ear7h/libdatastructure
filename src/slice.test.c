#include <stdio.h>

#include <test/test.h>

void my_test_fn(T * t) {
    printf("woo a test\n");
}

void my_test_fn_fail(T * t) {
    test_failf(t, "oh noooo");
    printf("woo a test\n");
}

void my_test_fn_fatal(T * t) {
    test_fatalf(t, "oh noooo");
    printf("woo a test\n");
}

DECL_TESTS(my_test_fn, my_test_fn_fail, my_test_fn_fatal);
