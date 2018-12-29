#include <criterion/criterion.h>

int main(int argc, char** argv)
{
  // https://criterion.readthedocs.io/en/master/internal.html
  struct criterion_test_set* tests = criterion_initialize();

  int exit_code = 0;
  if (criterion_handle_args(argc, argv, true))
    exit_code = !criterion_run_all_tests(tests);

  criterion_finalize(tests);

  return exit_code;
}
