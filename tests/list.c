#include "test_suite.h"
#include <ads.h>

ads_list_declare(s32, int, struct ads_alloc);
ads_list_declare(u8, unsigned char, struct ads_alloc);

test_decl(list_init_creates_empty_list)
{
  struct ads_list_s32 list;
  ads_list_init_s32(&list, ads_alloc_default());
  test_assert_equals(0, list.size);
  test_passed();
}

test_decl(list_init_head_is_null)
{
  struct ads_list_s32 list;
  ads_list_init_s32(&list, ads_alloc_default());
  test_assert_equals(NULL, list.head);
  test_passed();
}

test_decl(list_push_returns_ok)
{
  struct ads_list_s32 list;
  ads_list_init_s32(&list, ads_alloc_default());
  test_assert_equals(ads_result_ok, ads_list_push_s32(&list, 5));
  test_passed();
}

test_decl(list_push_changes_size)
{
  struct ads_list_s32 list;
  ads_list_init_s32(&list, ads_alloc_default());
  ads_list_push_s32(&list, 5);
  test_assert_equals(1, list.size);
  ads_list_push_s32(&list, 25);
  test_assert_equals(2, list.size);
  test_passed();
}
