#include "test_suite.h"
#include <string.h>
#include <stdio.h>

int main(int, char**);

void test_run_all(void)
{
  const int func_name_shift = strlen("test_func_");
  char func_name[256];
  long base;
  scanf("%lx %s", &base, func_name);
  long shift = (long)main - base;
  
  printf("--- tests run all ---\n");
  for (long addr, idx = 1; 
       scanf("%lx %s", &addr, func_name) == 2;
       idx++)
  {
    test_t func = (test_t) (addr + shift);
    enum test_result res = func();
    printf(
      "[%ld] %s: %s\n",
      idx,
      func_name + func_name_shift,
      (res == TEST_RESULT_OK ? "OK" : "FAILED")
    );
  }
  printf("--- tests ended ---\n");
}