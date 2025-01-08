# unit_test_c

Provides a [unit_test.h](src/unit_test.h) and [unit_test.c](src/unit_test.c) for use in unit-testing of C programs.

## Installation

Simply download the two files into your project.
+ [unit_test.h](src/unit_test.h)
+ [unit_test.c](src/unit_test.c)

## Example

This repo contains an example of unit-testing a hello world application that contains a fibonacci number function.

The [example.c](src/example.c) defines the entrypoint, and for simplicity of the example, the `fib` function too.

The [example.h](src/example.h) declares the `fib` function and the `declare_tests` function.

The [test_example.c](tests/test_example.c) defines the unit tests cases themselves.

### Hello World

First, let us build and run the program **without unit tests**.

```
rm -rf build/*.o build/example build/test_example
mackenzie@caprica: make &> build.log
mackenzie@caprica: ./build/example
Hello World!
fib(0) = 0
fib(1) = 1
fib(2) = 1
fib(3) = 2
fib(4) = 3
fib(5) = 5
mackenzie@caprica:
```

### Run Unit Tests

```
mackenzie@caprica: ./build/test_example --test --all
----------------------------- TEST CASE -----------------------------
Suite: ExampleSuite
Name: test_basecase_0
Do work to before the test.
Do work to after the test.
Elapsed Time: 0.0000 seconds
Result: PASS
--------------------------- END TEST CASE ---------------------------


----------------------------- TEST CASE -----------------------------
Suite: ExampleSuite
Name: test_basecase_1
Do work to before the test.
Do work to after the test.
Elapsed Time: 0.0000 seconds
Result: PASS
--------------------------- END TEST CASE ---------------------------


----------------------------- TEST CASE -----------------------------
Suite: ExampleSuite
Name: test_basecase_0
Elapsed Time: 0.0000 seconds
Result: PASS
--------------------------- END TEST CASE ---------------------------


-------------------------- RESULTS SUMMARY --------------------------
Passed Tests: 3
Failed Tests: 0
Total  Tests: 3
Elapsed Time: 0.0000 seconds
------------------------------ PASSED -------------------------------
mackenzie@caprica:
```

### Other Options

```
mackenzie@caprica: ./build/test_example --test -h
Unit Test Help:
    --test:                        Activate the unit test runner.
    --all, -a:                     Enable all unit test suites and test cases.
    --enable-suite  <suite>:       Enable the named unit test suite.
    --disable-suite <suite>:       Disable the named unit test suite.
    --enable-case  <suite> <name>: Enable the named unit test case.
    --disable-case <suite> <name>: Disable the named unit test case.
    --help, -h:                    Print this help message.
mackenzie@caprica:
```

## Assertion Macros

| Macro Signature                                     | Description                                                                             |
|-----------------------------------------------------|-----------------------------------------------------------------------------------------|
| `fail(...)`                                         | Marks a test as failed and reports the file and line number of the failure.             |
| `assertTrue(CONDITION, ...)`                        | Fails the test if the CONDITION evaluates to false.                                     |
| `assertFalse(CONDITION, ...)`                       | Fails the test if the CONDITION evaluates to true.                                      |
| `assertImplies(LEFT, RIGHT, ...)`                   | Fails the test if LEFT is true and RIGHT is false.                                      |
| `assertEqual(EXPECTED, ACTUAL, ...)`                | Fails the test if EXPECTED is not equal to ACTUAL.                                      |
| `assertNotEqual(EXPECTED, ACTUAL, ...)`             | Fails the test if EXPECTED is equal to ACTUAL.                                          |
| `assertEquals(EXPECTED, ACTUAL, ...)`               | Fails the test if EXPECTED is not equal to ACTUAL (alias for assertEqual).              |
| `assertNotEquals(EXPECTED, ACTUAL, ...)`            | Fails the test if EXPECTED is equal to ACTUAL (alias for assertNotEqual).               |
| `assertLess(LEFT, RIGHT, ...)`                      | Fails the test if LEFT is not less than RIGHT.                                          |
| `assertLessEqual(LEFT, RIGHT, ...)`                 | Fails the test if LEFT is greater than RIGHT.                                           |
| `assertGreater(LEFT, RIGHT, ...)`                   | Fails the test if LEFT is not greater than RIGHT.                                       |
| `assertGreaterEqual(LEFT, RIGHT, ...)`              | Fails the test if LEFT is less than RIGHT.                                              |
| `assertNull(VALUE, ...)`                            | Fails the test if VALUE is not NULL.                                                    |
| `assertNotNull(VALUE, ...)`                         | Fails the test if VALUE is NULL.                                                        |
| `assertStrEqual(EXPECTED, ACTUAL, ...)`             | Fails the test if the strings EXPECTED and ACTUAL are not equal.                        |
| `assertStrNotEqual(EXPECTED, ACTUAL, ...)`          | Fails the test if the strings EXPECTED and ACTUAL are equal.                            |
| `assertStrnEqual(EXPECTED, ACTUAL, LENGTH, ...)`    | Fails the test if the first LENGTH characters of EXPECTED and ACTUAL are not equal.     |
| `assertStrnNotEqual(EXPECTED, ACTUAL, LENGTH, ...)` | Fails the test if the first LENGTH characters of EXPECTED and ACTUAL are equal.         |
| `assertMemEqual(EXPECTED, ACTUAL, LENGTH, ...)`     | Fails the test if the memory blocks EXPECTED and ACTUAL are not equal for LENGTH bytes. |
| `assertMemNotEqual(EXPECTED, ACTUAL, LENGTH, ...)`  | Fails the test if the memory blocks EXPECTED and ACTUAL are equal for LENGTH bytes.     |

The `...` varadic arguments are for passing in arguments to `printf` in case of test failure.
The first argument is the format specified, and the rest are the substitutions thereto.


