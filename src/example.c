#include "example.h"

// A simple function that we will create unit tests for.
int fib (unsigned int n)
{
    switch (n)
    {
        case 0: return 0;
        case 1: return 1;
        default: return fib(n - 1) + fib(n - 2);
    }
}

// Entrypoint of both the production and unit-test programs.
int main (int argc, const char** argv)
{
#ifdef RUN_UNIT_TESTS
    declare_tests();
    return unit_test_run(argc, argv);
#else
    printf("Hello World!\n");
    printf("fib(0) = %d\n", fib(0));
    printf("fib(1) = %d\n", fib(1));
    printf("fib(2) = %d\n", fib(2));
    printf("fib(3) = %d\n", fib(3));
    printf("fib(4) = %d\n", fib(4));
    printf("fib(5) = %d\n", fib(5));
    return 0;
#endif
}
