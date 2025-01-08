#include "../src/example.h"

static void setup ()
{
    printf("Do work to before the test.\n");
}

static void teardown ()
{
    printf("Do work to after the test.\n");
}

static void test_basecase_0 ()
{
    assertEqual(0, fib(0));
}

static void test_basecase_1 ()
{
    assertEqual(1, fib(1));
}

static void test_additive_case ()
{
    assertEqual(1, fib(2));
    assertEqual(2, fib(3));
    assertEqual(3, fib(4));

    // One can pass arguments to printf...
    assertEqual(5, fib(5), "5 != %d", fib(5));
}

void declare_tests ()
{
    UNIT_TEST_CASE_WITH (ExampleSuite, test_basecase_0, setup, teardown);
    UNIT_TEST_CASE_WITH (ExampleSuite, test_basecase_1, setup, teardown);

    // If no setup/teardown is needed, then simply...
    UNIT_TEST_CASE (ExampleSuite, test_additive_case);
}
