#include <criterion/criterion.h>

struct arguments
{
  int argc;
  char** argv;
};

void destroy_arguments(struct arguments* arguments)
{
  for (int i = 0; i < arguments->argc; i++)
    free(arguments->argv[i]);

  free(arguments->argv);
  arguments->argv = NULL;
  arguments->argc = 0;
}

struct arguments rebuild_args_with_default(int argc, char** argv)
{
  int new_argc = argc + 1;
  char** new_argv = malloc(sizeof(char*) * new_argc);

  for (int i = 0; i < argc; i++)
    new_argv[i] = strdup(argv[i]);

  new_argv[argc + 0] = strdup("--verbose");
  struct arguments result = {.argc = new_argc, .argv = new_argv};
  return result;
}

int main(int argc, char** argv)
{
  // https://criterion.readthedocs.io/en/master/internal.html
  struct criterion_test_set* tests = criterion_initialize();

  int exit_code = 0;

  __auto_type arguments = rebuild_args_with_default(argc, argv);
  if (criterion_handle_args(arguments.argc, arguments.argv, true))
    exit_code = !criterion_run_all_tests(tests);

  destroy_arguments(&arguments);
  criterion_finalize(tests);

  return exit_code;
}
