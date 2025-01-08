#include <stdio.h>

// The function under test.
int fib (unsigned int n);

// If we are running the unit tests,
// then we need someplace to declare them first!
#ifdef RUN_UNIT_TESTS
#include "../tests/unit_test.h"
void declare_tests ();
#endif
