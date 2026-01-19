#include "unittest.h"
#include <stdio.h>

#include "unittest_decl.h"

int UNITTEST_count = 0;
int UNITTEST_pass = 0;
int UNITTEST_assert = 0;

void UnitTest_RunAllTests() {

  UNITTEST_RUN_ORDER

  puts("--------------------------------------------------------------------------------");
  printf("[ %d / %d ] - Tests passed.\n\n", UNITTEST_pass, UNITTEST_count);
}
