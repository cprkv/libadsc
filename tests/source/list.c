#include "test_suite.h"
#include <ads.h>

ads_list_declare(s32l, int, struct ads_alloc);
ads_list_declare(u8l, unsigned char, struct ads_alloc);

test_decl(list_init_creates_empty_list)
{
  struct s32l list;
  s32l_init(&list, ads_alloc_default());
  test_assert_equals(0, list.size);
  test_passed();
}

test_decl(list_init_head_is_null)
{
  struct s32l list;
  s32l_init(&list, ads_alloc_default());
  test_assert_equals(NULL, list.head);
  test_passed();
}

test_decl(list_push_returns_ok)
{
  struct s32l list;
  s32l_init(&list, ads_alloc_default());
  test_assert_equals(ads_result_ok, s32l_push(&list, 5));
  test_passed();
}

test_decl(list_push_changes_size)
{
  struct s32l list;
  s32l_init(&list, ads_alloc_default());
  s32l_push(&list, 5);
  test_assert_equals(1, list.size);
  s32l_push(&list, 25);
  test_assert_equals(2, list.size);
  test_passed();
}
