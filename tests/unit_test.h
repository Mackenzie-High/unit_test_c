// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.
//
// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// For more information, please refer to <https://unlicense.org>
//
#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#ifndef SKIP_UNIT_TESTS

#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <time.h>

#define UNIT_TEST_MAX_COUNT 65536

#define UNIT_TEST_CASE_WITH(SUITE, FUNCTION, SETUP, TEARDOWN) unit_test_declare(#SUITE, #FUNCTION, FUNCTION, SETUP, TEARDOWN);

#define UNIT_TEST_CASE(SUITE, FUNCTION) unit_test_declare(#SUITE, #FUNCTION, FUNCTION, NULL, NULL);

// The varadic arguments to the macro will be passed to printf().
// Creating a varadic printf() call is difficult, when the arity can be zero too.
// Therefore, this macro must play a little bit of a trick.
// First, the varadic arguments are converted to a string and passed to strnlen().
// If the string is non-empty, then we can assume the arity is non-zero.
// In that case, we pass the arguments to a specialized printf wrapper.
// The purpose of the wrapper is to prevent compliation failure in the other case,
// namely when there are no varadic arguments. In that case, we cannot simply
// call printf(). because the first argument thereto must be the format string.
// Moreover, we cannot simply create a wrapper that takes only varadic arguments,
// because C requires that the first argument be non-varadic; therefore,
// we must create a wrapper that accepts, but ignores, its first argument.
#define fail(...) unit_test_fail(__FILE__, __LINE__, 0 != strnlen(#__VA_ARGS__, 3), ##__VA_ARGS__);

// Note that I am aiming for syntax compatibility with JUnit.
#define assertTrue(CONDITION, ...) if (! (CONDITION)) { fail(__VA_ARGS__) }
#define assertFalse(CONDITION, ...) assertTrue(! (CONDITION), ## __VA_ARGS__)

#define assertImplies(LEFT, RIGHT, ...) if (LEFT) { assertTrue(RIGHT, ##__VA_ARGS__); }

#define assertEqual(EXPECTED, ACTUAL, ...) assertTrue((EXPECTED) == (ACTUAL), ## __VA_ARGS__)
#define assertNotEqual(EXPECTED, ACTUAL, ...) assertFalse((EXPECTED) == (ACTUAL), ## __VA_ARGS__)

// Alias, because of how common this is used by accident.
#define assertEquals(EXPECTED, ACTUAL, ...) assertTrue((EXPECTED) == (ACTUAL), ## __VA_ARGS__)
#define assertNotEquals(EXPECTED, ACTUAL, ...) assertFalse((EXPECTED) == (ACTUAL), ## __VA_ARGS__)

#define assertLess(LEFT, RIGHT, ...) assertTrue((LEFT) < (RIGHT), ## __VA_ARGS__)
#define assertLessEqual(LEFT, RIGHT, ...) assertTrue((LEFT) <= (RIGHT), ## __VA_ARGS__)
#define assertGreater(LEFT, RIGHT, ...) assertTrue((LEFT) > (RIGHT), ## __VA_ARGS__)
#define assertGreaterEqual(LEFT, RIGHT, ...) assertTrue((LEFT) >= (RIGHT), ## __VA_ARGS__)

#define assertNull(VALUE, ...) assertTrue(NULL == (VALUE), ## __VA_ARGS__)
#define assertNotNull(VALUE, ...) assertTrue(NULL != (VALUE), ## __VA_ARGS__)

#define assertStrEqual(EXPECTED, ACTUAL, ...) assertEqual(0, strcmp((EXPECTED), (ACTUAL)), ## __VA_ARGS__)
#define assertStrNotEqual(EXPECTED, ACTUAL, ...) assertNotEqual(0, strcmp((EXPECTED), (ACTUAL)), ## __VA_ARGS__)

#define assertStrnEqual(EXPECTED, ACTUAL, LENGTH, ...) assertEqual(0, strcmp((EXPECTED), (ACTUAL), (LENGTH)), ## __VA_ARGS__)
#define assertStrnNotEqual(EXPECTED, ACTUAL, LENGTH, ...) assertNotEqual(0, strcmp((EXPECTED), (ACTUAL), (LENGTH)), ## __VA_ARGS__)

#define assertMemEqual(EXPECTED, ACTUAL, LENGTH, ...) assertEqual(0, memcmp((EXPECTED), (ACTUAL), (LENGTH)), ## __VA_ARGS__)
#define assertMemNotEqual(EXPECTED, ACTUAL, LENGTH, ...) assertNotEqual(0, memcmp((EXPECTED), (ACTUAL), (LENGTH)), ## __VA_ARGS__)

/**
 * Signature of a unit test case function.
 */
typedef void (*unit_test_function_t)();

/**
 * The results of running a single unit test case.
 */
typedef struct
{
    /**
     * True, if the test case passed and did not fail.
     */
    bool passed;

    /**
     * Monotonic time of when the test case began execution.
     */
    time_t start_time_mono_ns;

    /**
     * Monotonic time of when the test case finished execution.
     */
    time_t end_time_mono_ns;

    /**
     * Monotonic execution time of the test case.
     */
    time_t elapsed_time_mono_ns;

} unit_test_case_result_t;

/**
 * Internal structure that describes a single unit test case.
 */
typedef struct
{
    /**
     * Since we are using a globally allocated array of these objects,
     * this is true, only if this object actually represents a test case.
     */
    bool allocated;

    /**
     * True, only if this test shall be run when executing the unit tests.
     */
    bool enabled;

    /**
     * This is the name of the test suite that the test case is a part of.
     */
    const char* suite;

    /**
     * This is the name of the test case itself.
     */
    const char* name;

    /**
     * This is the test case itself, which will be executed.
     */
    unit_test_function_t function;

    /**
     * This is the result of the last execution of the test case, if any.
     */
    unit_test_case_result_t result;

    /**
     * This is a function to invoke immediately before the unit-test,
     * to allocate any global resources used by the unit-test case.
     */
    unit_test_function_t setup;

    /**
     * This is a function to invoke immediately after the unit-test,
     * to deallocate any global resources used by the unit-test case.
     */
    unit_test_function_t teardown;

} unit_test_case_t;

/**
 * A private function used to implement varadic error messages in assertions.
 */
void unit_test_fail (const char* file, int32_t line, bool has_message, ...);

/**
 * A private function used to implement the declaration of test cases.
 */
void unit_test_declare (const char* suite,
                        const char* name,
                        unit_test_function_t function,
                        unit_test_function_t setup,
                        unit_test_function_t teardown);

int32_t unit_test_get_current ();

unit_test_case_t* unit_test_get_cases ();

/**
 * Invoke this function in order to run the unit tests.
 */
int unit_test_run (int argc, const char** argv);

#endif // SKIP_UNIT_TESTS
#endif // UNIT_TEST_H
