#ifndef UNITTEST_H_
#define UNITTEST_H_
#include <stdio.h>

extern int UNITTEST_count;
extern int UNITTEST_pass;
extern int UNITTEST_assert;

#define UNITTEST_SUCCESS 0
#define UNITTEST_FAIL 1

#define UNITTEST_RESULT (UNITTEST_assert > 0 ? UNITTEST_FAIL : UNITTEST_SUCCESS)
#define UNITTEST_ASSERT(predicate) \
{  \
  if(!(predicate)) { \
    printf("[  ASSERT  ] - In:%s:%d:%s Assertion Failed: %s\n", __FILE__, __LINE__, __FUNCTION__, #predicate); \
    UNITTEST_assert++; \
  } \
}
#define UNITTEST_WRAP(testname) UNITTEST_ ## testname ## _impl
#define UNITTEST_NAME(testname) UNITTEST_ ## testname
#define UNITTEST_DECL(testname) int UNITTEST_NAME(testname)()
#define UNITTEST_RUN(testname) \
{ \
  UNITTEST_count++; \
  int result = UNITTEST_NAME(testname)(); \
  UNITTEST_pass += result ? 0 : 1; \
  printf("[%s] - %s\n", result ? "  FAILED  " : "  SUCCESS ", #testname); \
}
#define UNITTEST_IMPL(testname) \
void UNITTEST_WRAP(testname)(); \
int UNITTEST_NAME(testname)() { \
  UNITTEST_assert = 0; \
  UNITTEST_WRAP(testname)(); \
  return UNITTEST_RESULT; \
} \
void UNITTEST_WRAP(testname)()

void UnitTest_RunAllTests();

#endif

