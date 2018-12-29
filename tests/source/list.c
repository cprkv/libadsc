#include <ads.h>
#include <criterion/criterion.h>

ads_list_declare(s32l, int, struct ads_alloc);
ads_list_declare(u8l, unsigned char, struct ads_alloc);

Test(list, init_creates_empty_list)
{
  struct s32l list;
  s32l_init(&list, ads_alloc_default());
  cr_assert_eq(0, list.size);
}

Test(list, init_head_is_null)
{
  struct s32l list;
  s32l_init(&list, ads_alloc_default());
  cr_assert_eq(NULL, list.head);
}

Test(list, push_returns_ok)
{
  struct s32l list;
  s32l_init(&list, ads_alloc_default());
  cr_assert_eq(ads_result_ok, s32l_push(&list, 5));
}

Test(list, push_changes_size)
{
  struct s32l list;
  s32l_init(&list, ads_alloc_default());
  s32l_push(&list, 5);
  cr_assert_eq(1, list.size);
  s32l_push(&list, 25);
  cr_assert_eq(2, list.size);
}
