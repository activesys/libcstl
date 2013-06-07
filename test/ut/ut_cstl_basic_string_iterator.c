#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/cvector.h"
#include "cstl/cstl_basic_string_iterator.h"
#include "cstl/cstl_basic_string_private.h"
#include "cstl/cstl_basic_string.h"
#include "cstl/cstring.h"
#include "cstl/clist.h"

#include "ut_def.h"
#include "ut_cstl_basic_string_iterator.h"

UT_SUIT_DEFINATION(cstl_basic_string_iterator, _create_basic_string_iterator)

/*
 * test _create_basic_string_iterator
 */
UT_CASE_DEFINATION(_create_basic_string_iterator)
void test__create_basic_string_iterator__successfully(void** state)
{
    basic_string_iterator_t it_iter = _create_basic_string_iterator();
    assert_true(it_iter._pt_container == NULL);
    assert_true(it_iter._t_containertype == _BASIC_STRING_CONTAINER);
    assert_true(it_iter._t_iteratortype == _RANDOM_ACCESS_ITERATOR);
    assert_true(it_iter._t_pos._pby_corepos == NULL);
}

/*
 * test _basic_string_iterator_equal
 */
UT_CASE_DEFINATION(_basic_string_iterator_equal)
void test__basic_string_iterator_equal__different_container_type(void** state)
{
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    it_first._t_containertype = _LIST_CONTAINER;
    it_second._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_basic_string_iterator_equal(it_first, it_second));
}

void test__basic_string_iterator_equal__different_iterator_type(void** state)
{
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    it_first._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_basic_string_iterator_equal(it_first, it_second));
}

void test__basic_string_iterator_equal__different_container_pointer(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    basic_string_init(pt_basic_string);

    it_first = basic_string_begin(pt_basic_string);

    expect_assert_failure(_basic_string_iterator_equal(it_first, it_second));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_equal__first_is_not_belong_to_basic_string(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    basic_string_init_elem(pt_basic_string, 10, 100);

    it_first = it_second = basic_string_begin(pt_basic_string);
    it_first._t_pos._pby_corepos = NULL;

    expect_assert_failure(_basic_string_iterator_equal(it_first, it_second));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_equal__second_is_not_belong_to_basic_string(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    basic_string_init_elem(pt_basic_string, 10, 100);

    it_first = it_second = basic_string_begin(pt_basic_string);
    it_second._t_pos._pby_corepos = NULL;

    expect_assert_failure(_basic_string_iterator_equal(it_first, it_second));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_equal__equal(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    basic_string_init(pt_basic_string);

    it_first = it_second = basic_string_begin(pt_basic_string);

    assert_true(_basic_string_iterator_equal(it_first, it_second));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_equal__not_equal(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    basic_string_init_elem(pt_basic_string, 10, 100);

    it_first = basic_string_begin(pt_basic_string);
    it_second = basic_string_end(pt_basic_string);

    assert_false(_basic_string_iterator_equal(it_first, it_second));

    basic_string_destroy(pt_basic_string);
}

/*
 * test _basic_string_iterator_less
 */
UT_CASE_DEFINATION(_basic_string_iterator_less)
void test__basic_string_iterator_less__different_container_type(void** state)
{
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    it_first._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_basic_string_iterator_less(it_first, it_second));
}

void test__basic_string_iterator_less__different_iterator_type(void** state)
{
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    it_first._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_basic_string_iterator_less(it_first, it_second));
}

void test__basic_string_iterator_less__different_container_pointer(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    basic_string_init(pt_basic_string);

    it_first = basic_string_begin(pt_basic_string);

    expect_assert_failure(_basic_string_iterator_less(it_first, it_second));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_less__first_is_not_belong_to_basic_string(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    basic_string_init_elem(pt_basic_string, 10, 100);

    it_first = it_second = basic_string_begin(pt_basic_string);
    it_first._t_pos._pby_corepos = NULL;

    expect_assert_failure(_basic_string_iterator_less(it_first, it_second));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_less__second_is_not_belong_to_basic_string(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    basic_string_init_elem(pt_basic_string, 10, 100);

    it_first = it_second = basic_string_begin(pt_basic_string);
    it_second._t_pos._pby_corepos = NULL;

    expect_assert_failure(_basic_string_iterator_less(it_first, it_second));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_less__first_greater_than_second(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    basic_string_init_elem(pt_basic_string, 10, 100);

    it_first = basic_string_end(pt_basic_string);
    it_second = basic_string_begin(pt_basic_string);

    assert_false(_basic_string_iterator_less(it_first, it_second));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_less__first_equal_to_second(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    basic_string_init_elem(pt_basic_string, 10, 100);

    it_first = it_second = basic_string_begin(pt_basic_string);

    assert_false(_basic_string_iterator_less(it_first, it_second));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_less__first_less_than_second(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    basic_string_init_elem(pt_basic_string, 10, 100);

    it_first = basic_string_begin(pt_basic_string);
    it_second = basic_string_end(pt_basic_string);

    assert_true(_basic_string_iterator_less(it_first, it_second));

    basic_string_destroy(pt_basic_string);
}

/*
 * test _basic_string_iterator_before
 */
UT_CASE_DEFINATION(_basic_string_iterator_before)
void test__basic_string_iterator_before__different_container_type(void** state)
{
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    it_first._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_basic_string_iterator_before(it_first, it_second));
}

void test__basic_string_iterator_before__different_iterator_type(void** state)
{
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    it_first._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_basic_string_iterator_before(it_first, it_second));
}

void test__basic_string_iterator_before__different_container_pointer(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    basic_string_init(pt_basic_string);

    it_first = basic_string_begin(pt_basic_string);

    expect_assert_failure(_basic_string_iterator_before(it_first, it_second));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_before__first_is_not_belong_to_basic_string(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    basic_string_init_elem(pt_basic_string, 10, 10);

    it_first = it_second = basic_string_begin(pt_basic_string);
    it_first._t_pos._pby_corepos = NULL;

    expect_assert_failure(_basic_string_iterator_before(it_first, it_second));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_before__second_is_not_belong_to_basic_string(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    basic_string_init_elem(pt_basic_string, 10, 100);

    it_first = it_second = basic_string_begin(pt_basic_string);
    it_second._t_pos._pby_corepos = NULL;

    expect_assert_failure(_basic_string_iterator_before(it_first, it_second));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_before__first_after_second(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    basic_string_init_elem(pt_basic_string, 10, 100);

    it_first = basic_string_end(pt_basic_string);
    it_second = basic_string_begin(pt_basic_string);

    assert_false(_basic_string_iterator_before(it_first, it_second));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_before__first_equal_to_second(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    basic_string_init_elem(pt_basic_string, 10, 100);

    it_first = it_second = basic_string_begin(pt_basic_string);

    assert_false(_basic_string_iterator_before(it_first, it_second));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_before__first_before_second(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    basic_string_init_elem(pt_basic_string, 10, 100);

    it_first = basic_string_begin(pt_basic_string);
    it_second = basic_string_end(pt_basic_string);

    assert_true(_basic_string_iterator_before(it_first, it_second));

    basic_string_destroy(pt_basic_string);
}

/*
 * test _basic_string_iterator_get_value
 */
UT_CASE_DEFINATION(_basic_string_iterator_get_value)
void test__basic_string_iterator_get_value__invalid_iterator(void** state)
{
    int value;
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._t_pos._pby_corepos = NULL;

    expect_assert_failure(_basic_string_iterator_get_value(it_iter, &value));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_get_value__invalid_iterator_container_type(void** state)
{
    int value;
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_basic_string_iterator_get_value(it_iter, &value));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_get_value__invalid_iterator_iterator_type(void** state)
{
    int value;
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_basic_string_iterator_get_value(it_iter, &value));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_get_value__invalid_iterator_container_pointer(void** state)
{
    int value;
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._pt_container = NULL;

    expect_assert_failure(_basic_string_iterator_get_value(it_iter, &value));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_get_value__basic_string_end(void** state)
{
    int value;
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_end(pt_basic_string);

    expect_assert_failure(_basic_string_iterator_get_value(it_iter, &value));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_get_value__invalid_value_buffer(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);

    expect_assert_failure(_basic_string_iterator_get_value(it_iter, NULL));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_get_value__successfully(void** state)
{
    int value = 0;
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);

    _basic_string_iterator_get_value(it_iter, &value);
    assert_int_equal(value, 100);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_get_value__successfully_cstr(void** state)
{
    char* str = NULL;
    basic_string_t* pt_basic_string = create_basic_string(char*);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, "abcdefg");
    it_iter = basic_string_begin(pt_basic_string);

    _basic_string_iterator_get_value(it_iter, &str);
    assert_true(strcmp(str, "abcdefg") == 0);

    basic_string_destroy(pt_basic_string);
}
void test__basic_string_iterator_get_value__c_terminator(void** state)
{
    int value = 100;
    basic_string_t* pbstr = create_basic_string(int);
    iterator_t it;

    basic_string_init_elem(pbstr, 1, 0);
    it = basic_string_begin(pbstr);
    _basic_string_iterator_get_value(it, &value);
    assert_true(value == 0);
    basic_string_destroy(pbstr);
}
void test__basic_string_iterator_get_value__cstr_terminator(void** state)
{
    char* str = 0x1111;
    basic_string_t* pbstr = create_basic_string(char*);
    iterator_t it;

    basic_string_init_elem(pbstr, 1, NULL);
    it = basic_string_begin(pbstr);
    _basic_string_iterator_get_value(it, &str);
    assert_true(str == NULL);
    basic_string_destroy(pbstr);
}
void test__basic_string_iterator_get_value__cstl_terminator(void** state)
{
    basic_string_t* pbstr = create_basic_string(list_t<int>);
    list_t l;
    list_t terminator;
    iterator_t it;

    basic_string_init_elem(pbstr, 1, NULL);
    _create_list_auxiliary(&l, "int");
    list_init(&l);
    it = basic_string_begin(pbstr);
    _basic_string_iterator_get_value(it, &l);
    memset(&terminator, 0x00, sizeof(list_t));
    assert_true(memcmp(&terminator, &l, sizeof(list_t)) == 0);
    basic_string_destroy(pbstr);
}
typedef struct _tag_test__basic_string_iterator_get_value__user_define {
    int n_elem;
} _test__basic_string_iterator_get_value__user_define_t;
void test__basic_string_iterator_get_value__user_define_terminator(void** state)
{
    basic_string_t* pbstr = NULL;
    _test__basic_string_iterator_get_value__user_define_t elem;
    _test__basic_string_iterator_get_value__user_define_t terminator;
    iterator_t it;

    type_register(_test__basic_string_iterator_get_value__user_define_t, NULL, NULL, NULL, NULL);
    pbstr = create_basic_string(_test__basic_string_iterator_get_value__user_define_t);
    basic_string_init_elem(pbstr, 1, NULL);
    elem.n_elem = 100;
    memset(&terminator, 0x00, sizeof(_test__basic_string_iterator_get_value__user_define_t));
    it = basic_string_begin(pbstr);
    _basic_string_iterator_get_value(it, &elem);
    assert_true(memcmp(&terminator, &elem, sizeof(_test__basic_string_iterator_get_value__user_define_t)) == 0);

    basic_string_destroy(pbstr);
}

/*
 * test _basic_string_iterator_set_value
 */
UT_CASE_DEFINATION(_basic_string_iterator_set_value)
void test__basic_string_iterator_set_value__invalid_iterator(void** state)
{
    int value;
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._t_pos._pby_corepos = NULL;

    expect_assert_failure(_basic_string_iterator_set_value(it_iter, &value));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_set_value__invalid_iterator_container_type(void** state)
{
    int value;
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_basic_string_iterator_set_value(it_iter, &value));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_set_value__invalid_iterator_iterator_type(void** state)
{
    int value;
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_basic_string_iterator_set_value(it_iter, &value));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_set_value__invalid_iterator_container_pointer(void** state)
{
    int value;
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._pt_container = NULL;

    expect_assert_failure(_basic_string_iterator_set_value(it_iter, &value));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_set_value__basic_string_end(void** state)
{
    int value;
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_end(pt_basic_string);

    expect_assert_failure(_basic_string_iterator_set_value(it_iter, &value));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_set_value__invalid_value_buffer(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);

    expect_assert_failure(_basic_string_iterator_set_value(it_iter, NULL));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_set_value__successfully(void** state)
{
    int value = 0;
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);

    _basic_string_iterator_set_value(it_iter, &value);
    assert_int_equal(*(int*)basic_string_at(pt_basic_string, 0), 0);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_set_value__successfully_cstr(void** state)
{
    const char* str = "AAAAAAAAAAA";
    basic_string_t* pt_basic_string = create_basic_string(char*);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, "abcdefg");
    it_iter = basic_string_begin(pt_basic_string);

    _basic_string_iterator_set_value(it_iter, str);
    assert_true(strcmp(str, (char*)basic_string_at(pt_basic_string, 0)) == 0);

    basic_string_destroy(pt_basic_string);
}
void test__basic_string_iterator_set_value__c_terminator(void** state)
{
    int value = 0;
    basic_string_t* pbstr = create_basic_string(int);
    iterator_t it;

    basic_string_init_elem(pbstr, 1, 100);
    it = basic_string_begin(pbstr);
    _basic_string_iterator_set_value(it, &value);
    assert_true(*(int*)basic_string_at(pbstr, 0) == 0);
    basic_string_destroy(pbstr);
}
void test__basic_string_iterator_set_value__cstr_terminator(void** state)
{
    basic_string_t* pbstr = create_basic_string(char*);
    iterator_t it;

    basic_string_init(pbstr);
    basic_string_push_back(pbstr, "abc");
    basic_string_push_back(pbstr, NULL);
    basic_string_push_back(pbstr, NULL);
    it = basic_string_begin(pbstr);
    _basic_string_iterator_set_value(it, NULL);
    assert_true(basic_string_at(pbstr, 0) == NULL);
    it = iterator_next(it);
    _basic_string_iterator_set_value(it, "xyz");
    assert_true(strcmp((char*)basic_string_at(pbstr, 1), "xyz") == 0);
    it = iterator_next(it);
    _basic_string_iterator_set_value(it, NULL);
    assert_true(basic_string_at(pbstr, 2) == NULL);
    basic_string_destroy(pbstr);
}
void test__basic_string_iterator_set_value__cstl_terminator(void** state)
{
    basic_string_t* pbstr = create_basic_string(list_t<int>);
    iterator_t it;
    list_t* plist = create_list(int);
    list_t terminator;

    list_init(plist);
    basic_string_init(pbstr);
    basic_string_push_back(pbstr, plist);
    basic_string_push_back(pbstr, NULL);
    basic_string_push_back(pbstr, NULL);

    memset(&terminator, 0x00, sizeof(list_t));
    it = basic_string_begin(pbstr);
    _basic_string_iterator_set_value(it, NULL);
    assert_true(memcmp(&terminator, basic_string_at(pbstr, 0), sizeof(list_t)) == 0);
    it = iterator_next(it);
    list_push_back(plist, 100);
    _basic_string_iterator_set_value(it, plist);
    assert_true(*(int*)list_front((list_t*)basic_string_at(pbstr, 1)) == 100);
    it = iterator_next(it);
    _basic_string_iterator_set_value(it, NULL);
    assert_true(memcmp(&terminator, basic_string_at(pbstr, 2), sizeof(list_t)) == 0);

    basic_string_destroy(pbstr);
    list_destroy(plist);
}
typedef struct _tag_test__basic_string_iterator_set_value__user_define {
    int n_elem;
} _test__basic_string_iterator_set_value__user_define_t;
void test__basic_string_iterator_set_value__user_define_terminator(void** state)
{
    basic_string_t* pbstr = NULL;
    _test__basic_string_iterator_set_value__user_define_t elem;
    _test__basic_string_iterator_set_value__user_define_t terminator;
    iterator_t it;

    elem.n_elem = 100;
    type_register(_test__basic_string_iterator_set_value__user_define_t, NULL, NULL, NULL, NULL);
    pbstr = create_basic_string(_test__basic_string_iterator_set_value__user_define_t);
    basic_string_init(pbstr);
    basic_string_push_back(pbstr, &elem);
    basic_string_push_back(pbstr, NULL);
    basic_string_push_back(pbstr, NULL);

    it = basic_string_begin(pbstr);
    _basic_string_iterator_set_value(it, NULL);
    memset(&terminator, 0x00, sizeof(_test__basic_string_iterator_set_value__user_define_t));
    assert_true(memcmp(&terminator, basic_string_at(pbstr, 0), sizeof(_test__basic_string_iterator_set_value__user_define_t)) == 0);
    it = iterator_next(it);
    elem.n_elem = 1111;
    _basic_string_iterator_set_value(it, &elem);
    assert_true(((_test__basic_string_iterator_set_value__user_define_t*)basic_string_at(pbstr, 1))->n_elem == 1111);
    it = iterator_next(it);
    _basic_string_iterator_set_value(it, NULL);
    assert_true(memcmp(&terminator, basic_string_at(pbstr, 2), sizeof(_test__basic_string_iterator_set_value__user_define_t)) == 0);

    basic_string_destroy(pbstr);
}

/*
 * test _basic_string_iterator_get_pointer
 */
UT_CASE_DEFINATION(_basic_string_iterator_get_pointer)
void test__basic_string_iterator_get_pointer__invalid_iterator(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._t_pos._pby_corepos = NULL;

    expect_assert_failure(_basic_string_iterator_get_pointer(it_iter));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_get_pointer__invalid_iterator_container_type(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_basic_string_iterator_get_pointer(it_iter));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_get_pointer__invalid_iterator_iterator_type(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_basic_string_iterator_get_pointer(it_iter));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_get_pointer__invalid_iterator_container_pointer(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._pt_container = NULL;

    expect_assert_failure(_basic_string_iterator_get_pointer(it_iter));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_get_pointer__basic_string_end(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_end(pt_basic_string);

    expect_assert_failure(_basic_string_iterator_get_pointer(it_iter));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_get_pointer__successfully(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);

    assert_int_equal(*(int*)_basic_string_iterator_get_pointer(it_iter), 100);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_get_pointer__successfully_cstr(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, "abcdefg");
    it_iter = basic_string_begin(pt_basic_string);

    assert_true(strcmp("abcdefg", (char*)_basic_string_iterator_get_pointer(it_iter)) == 0);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_get_pointer__terminator(void** state)
{
    basic_string_t* pbstr = create_basic_string(list_t<int>);
    iterator_t it;
    list_t terminator;

    basic_string_init_elem(pbstr, 10, NULL);
    it = basic_string_begin(pbstr);
    memset(&terminator, 0x00, sizeof(list_t));
    assert_true(memcmp(&terminator, _basic_string_iterator_get_pointer(it), sizeof(list_t)) == 0);
    basic_string_destroy(pbstr);
}
void test__basic_string_iterator_get_pointer__cstr_terminator(void** state)
{
    basic_string_t* pbstr = create_basic_string(char*);
    iterator_t it;
    string_t terminator;

    basic_string_init_elem(pbstr, 10, NULL);
    it = basic_string_begin(pbstr);
    memset(&terminator, 0x00, sizeof(string_t));
    assert_true(_basic_string_iterator_get_pointer(it) == NULL);
    basic_string_destroy(pbstr);
}

/*
 * test _basic_string_iterator_get_pointer_ignore_cstr
 */
UT_CASE_DEFINATION(_basic_string_iterator_get_pointer_ignore_cstr)
void test__basic_string_iterator_get_pointer_ignore_cstr__invalid_iterator(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._t_pos._pby_corepos = NULL;

    expect_assert_failure(_basic_string_iterator_get_pointer_ignore_cstr(it_iter));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_get_pointer_ignore_cstr__invalid_iterator_container_type(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_basic_string_iterator_get_pointer_ignore_cstr(it_iter));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_get_pointer_ignore_cstr__invalid_iterator_iterator_type(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_basic_string_iterator_get_pointer_ignore_cstr(it_iter));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_get_pointer_ignore_cstr__invalid_iterator_container_pointer(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._pt_container = NULL;

    expect_assert_failure(_basic_string_iterator_get_pointer_ignore_cstr(it_iter));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_get_pointer_ignore_cstr__basic_string_end(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_end(pt_basic_string);

    expect_assert_failure(_basic_string_iterator_get_pointer_ignore_cstr(it_iter));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_get_pointer_ignore_cstr__successfully(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);

    assert_int_equal(*(int*)_basic_string_iterator_get_pointer_ignore_cstr(it_iter), 100);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_get_pointer_ignore_cstr__successfully_cstr(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, "abcdefg");
    it_iter = basic_string_begin(pt_basic_string);

    assert_true(strcmp("abcdefg", string_c_str(_basic_string_iterator_get_pointer_ignore_cstr(it_iter))) == 0);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_get_pointer_ignore_cstr__cstr_terminator(void** state)
{
    basic_string_t* pbstr = create_basic_string(char*);
    basic_string_iterator_t it;
    string_t terminator;

    memset(&terminator, 0x00, sizeof(string_t));
    basic_string_init_elem(pbstr, 10, NULL);
    it = basic_string_begin(pbstr);
    assert_true(memcmp(&terminator, _basic_string_iterator_get_pointer_ignore_cstr(it), sizeof(string_t)) == 0);
    basic_string_destroy(pbstr);
}
void test__basic_string_iterator_get_pointer_ignore_cstr__terminator(void** state)
{
    basic_string_t* pbstr = create_basic_string(list_t<int>);
    iterator_t it;
    list_t terminator;

    memset(&terminator, 0x00, sizeof(list_t));
    basic_string_init_elem(pbstr, 10, NULL);
    it = basic_string_begin(pbstr);
    assert_true(memcmp(&terminator, _basic_string_iterator_get_pointer_ignore_cstr(it), sizeof(string_t)) == 0);
    basic_string_destroy(pbstr);
}

/*
 * test _basic_string_iterator_next
 */
UT_CASE_DEFINATION(_basic_string_iterator_next)
void test__basic_string_iterator_next__invalid_iterator(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 10);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._t_pos._pby_corepos = NULL;

    expect_assert_failure(_basic_string_iterator_next(it_iter));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_next__invalid_iterator_container_type(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_basic_string_iterator_next(it_iter));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_next__invalid_iterator_iterator_type(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_basic_string_iterator_next(it_iter));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_next__invalid_iterator_container_pointer(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._pt_container = NULL;

    expect_assert_failure(_basic_string_iterator_next(it_iter));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_next__invalid_returned_iterator(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init(pt_basic_string);
    it_iter = basic_string_begin(pt_basic_string);

    expect_assert_failure(_basic_string_iterator_next(it_iter));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_next__successfully(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;
    basic_string_iterator_t it_next;

    basic_string_init(pt_basic_string);
    basic_string_push_back(pt_basic_string, 0);
    basic_string_push_back(pt_basic_string, -355);
    basic_string_push_back(pt_basic_string, 65);
    it_iter = basic_string_begin(pt_basic_string);
    it_next = _basic_string_iterator_next(it_iter);

    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    assert_true(*(int*)iterator_get_pointer(it_next) == -355);


    basic_string_destroy(pt_basic_string);
}

/*
 * test _basic_string_iterator_prev
 */
UT_CASE_DEFINATION(_basic_string_iterator_prev)
void test__basic_string_iterator_prev__invalid_iterator(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._t_pos._pby_corepos = NULL;

    expect_assert_failure(_basic_string_iterator_prev(it_iter));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_prev__invalid_iterator_container_type(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_end(pt_basic_string);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_basic_string_iterator_prev(it_iter));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_prev__invalid_iterator_iterator_type(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_end(pt_basic_string);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_basic_string_iterator_prev(it_iter));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_prev__invalid_iterator_container_pointer(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_end(pt_basic_string);
    it_iter._pt_container = NULL;

    expect_assert_failure(_basic_string_iterator_prev(it_iter));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_prev__invalid_returned_iterator(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init(pt_basic_string);
    it_iter = basic_string_begin(pt_basic_string);

    expect_assert_failure(_basic_string_iterator_prev(it_iter));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_prev__successfully(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;
    basic_string_iterator_t it_prev;

    basic_string_init(pt_basic_string);
    basic_string_push_back(pt_basic_string, 29);
    basic_string_push_back(pt_basic_string, -9);
    basic_string_push_back(pt_basic_string, 99);
    basic_string_push_back(pt_basic_string, 79);
    it_iter = basic_string_end(pt_basic_string);
    it_iter = _basic_string_iterator_prev(it_iter);
    it_prev = _basic_string_iterator_prev(it_iter);

    assert_true(*(int*)iterator_get_pointer(it_iter) == 79);
    assert_true(*(int*)iterator_get_pointer(it_prev) == 99);

    basic_string_destroy(pt_basic_string);
}

/*
 * test _basic_string_iterator_next_n
 */
UT_CASE_DEFINATION(_basic_string_iterator_next_n)
void test__basic_string_iterator_next_n__invalid_iterator(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._t_pos._pby_corepos = NULL;

    expect_assert_failure(_basic_string_iterator_next_n(it_iter, 10));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_next_n__invalid_iterator_container_type(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_basic_string_iterator_next_n(it_iter, 10));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_next_n__invalid_iterator_iterator_type(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_basic_string_iterator_next_n(it_iter, 10));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_next_n__invalid_iterator_container_pointer(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._pt_container = NULL;

    expect_assert_failure(_basic_string_iterator_next_n(it_iter, 10));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_next_n__move_to_end_invalid_returned_iterator(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);

    expect_assert_failure(_basic_string_iterator_next_n(it_iter, 20));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_next_n__move_to_begin_invalid_returned_iterator(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_end(pt_basic_string);

    expect_assert_failure(_basic_string_iterator_next_n(it_iter, -20));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_next_n__move_to_end_successfully(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;
    basic_string_iterator_t it_next_n;

    basic_string_init(pt_basic_string);
    basic_string_push_back(pt_basic_string, 0);
    basic_string_push_back(pt_basic_string, 1);
    basic_string_push_back(pt_basic_string, 2);
    basic_string_push_back(pt_basic_string, 3);
    basic_string_push_back(pt_basic_string, 4);
    basic_string_push_back(pt_basic_string, 5);
    basic_string_push_back(pt_basic_string, 6);
    basic_string_push_back(pt_basic_string, 7);
    basic_string_push_back(pt_basic_string, 8);
    basic_string_push_back(pt_basic_string, 9);
    basic_string_push_back(pt_basic_string, -9);
    it_iter = basic_string_begin(pt_basic_string);
    it_next_n = _basic_string_iterator_next_n(it_iter, 10);

    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    assert_true(*(int*)iterator_get_pointer(it_next_n) == -9);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_next_n__move_to_front_successfully(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;
    basic_string_iterator_t it_next_n;

    basic_string_init(pt_basic_string);
    basic_string_push_back(pt_basic_string, 0);
    basic_string_push_back(pt_basic_string, 1);
    basic_string_push_back(pt_basic_string, 2);
    basic_string_push_back(pt_basic_string, 3);
    basic_string_push_back(pt_basic_string, 4);
    basic_string_push_back(pt_basic_string, 5);
    basic_string_push_back(pt_basic_string, 6);
    basic_string_push_back(pt_basic_string, 7);
    basic_string_push_back(pt_basic_string, 8);
    basic_string_push_back(pt_basic_string, 9);
    basic_string_push_back(pt_basic_string, -9);
    it_iter = basic_string_end(pt_basic_string);
    it_iter = _basic_string_iterator_prev(it_iter);
    it_next_n = _basic_string_iterator_next_n(it_iter, -5);

    assert_true(*(int*)iterator_get_pointer(it_iter) == -9);
    assert_true(*(int*)iterator_get_pointer(it_next_n) == 5);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_next_n__does_not_move_successfully(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;
    basic_string_iterator_t it_next_n;

    basic_string_init(pt_basic_string);
    basic_string_push_back(pt_basic_string, 0);
    basic_string_push_back(pt_basic_string, 1);
    basic_string_push_back(pt_basic_string, 2);
    it_iter = basic_string_begin(pt_basic_string);
    it_next_n = _basic_string_iterator_next_n(it_iter, 0);

    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    assert_true(*(int*)iterator_get_pointer(it_next_n) == 0);

    basic_string_destroy(pt_basic_string);
}

/*
 * test _basic_string_iterator_prev_n
 */
UT_CASE_DEFINATION(_basic_string_iterator_prev_n)
void test__basic_string_iterator_prev_n__invalid_iterator(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._t_pos._pby_corepos = NULL;

    expect_assert_failure(_basic_string_iterator_prev_n(it_iter, 10));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_prev_n__invalid_iterator_container_type(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_end(pt_basic_string);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_basic_string_iterator_prev_n(it_iter, 10));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_prev_n__invalid_iterator_iterator_type(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_end(pt_basic_string);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_basic_string_iterator_prev_n(it_iter, 10));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_prev_n__invalid_iterator_container_pointer(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_end(pt_basic_string);
    it_iter._pt_container = NULL;

    expect_assert_failure(_basic_string_iterator_prev_n(it_iter, 10));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_prev_n__move_to_end_invalid_returned_iterator(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);

    expect_assert_failure(_basic_string_iterator_prev_n(it_iter, -20));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_prev_n__move_to_begin_invalid_returned_iterator(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_end(pt_basic_string);

    expect_assert_failure(_basic_string_iterator_prev_n(it_iter, 20));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_prev_n__move_to_end_successfully(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;
    basic_string_iterator_t it_prev_n;

    basic_string_init(pt_basic_string);
    basic_string_push_back(pt_basic_string, 0);
    basic_string_push_back(pt_basic_string, 1);
    basic_string_push_back(pt_basic_string, 2);
    basic_string_push_back(pt_basic_string, 3);
    basic_string_push_back(pt_basic_string, 4);
    basic_string_push_back(pt_basic_string, 5);
    basic_string_push_back(pt_basic_string, 6);
    basic_string_push_back(pt_basic_string, 7);
    basic_string_push_back(pt_basic_string, 8);
    basic_string_push_back(pt_basic_string, 9);
    basic_string_push_back(pt_basic_string, -9);
    it_iter = basic_string_begin(pt_basic_string);
    it_prev_n = _basic_string_iterator_prev_n(it_iter, -10);

    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    assert_true(*(int*)iterator_get_pointer(it_prev_n) == -9);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_prev_n__move_to_front_successfully(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;
    basic_string_iterator_t it_prev_n;

    basic_string_init(pt_basic_string);
    basic_string_push_back(pt_basic_string, 0);
    basic_string_push_back(pt_basic_string, 1);
    basic_string_push_back(pt_basic_string, 2);
    basic_string_push_back(pt_basic_string, 3);
    basic_string_push_back(pt_basic_string, 4);
    basic_string_push_back(pt_basic_string, 5);
    basic_string_push_back(pt_basic_string, 6);
    basic_string_push_back(pt_basic_string, 7);
    basic_string_push_back(pt_basic_string, 8);
    basic_string_push_back(pt_basic_string, 9);
    basic_string_push_back(pt_basic_string, -9);
    it_iter = basic_string_end(pt_basic_string);
    it_iter = _basic_string_iterator_prev(it_iter);
    it_prev_n = _basic_string_iterator_prev_n(it_iter, 10);

    assert_true(*(int*)iterator_get_pointer(it_iter) == -9);
    assert_true(*(int*)iterator_get_pointer(it_prev_n) == 0);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_prev_n__does_not_move_successfully(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;
    basic_string_iterator_t it_prev_n;

    basic_string_init(pt_basic_string);
    basic_string_push_back(pt_basic_string, 0);
    basic_string_push_back(pt_basic_string, 1);
    basic_string_push_back(pt_basic_string, 2);
    it_iter = basic_string_begin(pt_basic_string);
    it_prev_n = _basic_string_iterator_prev_n(it_iter, 0);

    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    assert_true(*(int*)iterator_get_pointer(it_prev_n) == 0);

    basic_string_destroy(pt_basic_string);
}

/*
 * test _basic_string_iterator_at
 */
UT_CASE_DEFINATION(_basic_string_iterator_at)
void test__basic_string_iterator_at__invalid_iterator(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._t_pos._pby_corepos = NULL;

    expect_assert_failure(_basic_string_iterator_at(it_iter, 10));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_at__invalid_iterator_container_type(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_basic_string_iterator_at(it_iter, 10));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_at__invalid_iterator_iterator_type(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_basic_string_iterator_at(it_iter, 10));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_at__invalid_iterator_container_pointer(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);
    it_iter._pt_container = NULL;

    expect_assert_failure(_basic_string_iterator_at(it_iter, 10));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_at__move_to_end_invalid_returned_iterator(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);

    expect_assert_failure(_basic_string_iterator_at(it_iter, 20));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_at__move_to_begin_invalid_returned_iterator(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_end(pt_basic_string);

    expect_assert_failure(_basic_string_iterator_at(it_iter, -20));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_at__end_invalid_iterator(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pt_basic_string, 10, 100);
    it_iter = basic_string_begin(pt_basic_string);

    expect_assert_failure(_basic_string_iterator_at(it_iter, 10));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_at__move_to_end_successfully(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;
    int i = 0;

    basic_string_init(pt_basic_string);
    for(i = 0; i < 10; ++i)
    {
        basic_string_push_back(pt_basic_string, i);
    }
    it_iter = basic_string_begin(pt_basic_string);

    assert_int_equal(*(int*)_basic_string_iterator_at(it_iter, 5), 5);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_at__move_to_end_cstr_successfully(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);
    basic_string_iterator_t it_iter;
    char* s_at = NULL;

    basic_string_init(pt_basic_string);
    basic_string_push_back(pt_basic_string, "abc");
    basic_string_push_back(pt_basic_string, "def");
    basic_string_push_back(pt_basic_string, "hij");
    basic_string_push_back(pt_basic_string, "klm");
    basic_string_push_back(pt_basic_string, "nop");
    it_iter = basic_string_begin(pt_basic_string);
    s_at = (char*)_basic_string_iterator_at(it_iter, 3);

    assert_true(strcmp(s_at, "klm") == 0);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_at__move_to_front_successfully(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;
    int i = 0;

    basic_string_init(pt_basic_string);
    for(i = 0;i < 10; ++i)
    {
        basic_string_push_back(pt_basic_string, i);
    }
    it_iter = basic_string_end(pt_basic_string);

    assert_int_equal(*(int*)_basic_string_iterator_at(it_iter, -2), 8);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_at__move_to_front_cstr_successfully(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);
    basic_string_iterator_t it_iter;
    char* s_at = NULL;

    basic_string_init(pt_basic_string);
    basic_string_push_back(pt_basic_string, "abc");
    basic_string_push_back(pt_basic_string, "def");
    basic_string_push_back(pt_basic_string, "hij");
    basic_string_push_back(pt_basic_string, "klm");
    basic_string_push_back(pt_basic_string, "nop");
    it_iter = basic_string_end(pt_basic_string);
    s_at = (char*)_basic_string_iterator_at(it_iter, -3);

    assert_true(strcmp(s_at, "hij") == 0);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_at__does_not_move_successfully(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;
    int i = 0;

    basic_string_init(pt_basic_string);
    for(i = 0; i < 10; ++i)
    {
        basic_string_push_back(pt_basic_string, i);
    }
    it_iter = _basic_string_iterator_next_n(basic_string_begin(pt_basic_string), 4);

    assert_int_equal(*(int*)_basic_string_iterator_at(it_iter, 0), 4);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_at__does_not_move_cstr_successfully(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);
    basic_string_iterator_t it_iter;
    char* s_at = NULL;

    basic_string_init(pt_basic_string);
    basic_string_push_back(pt_basic_string, "abc");
    basic_string_push_back(pt_basic_string, "def");
    basic_string_push_back(pt_basic_string, "hij");
    basic_string_push_back(pt_basic_string, "klm");
    basic_string_push_back(pt_basic_string, "nop");
    it_iter = basic_string_begin(pt_basic_string);
    s_at = (char*)_basic_string_iterator_at(it_iter, 0);

    assert_true(strcmp(s_at, "abc") == 0);

    basic_string_destroy(pt_basic_string);
}

/*
 * test _basic_string_iterator_minus
 */
UT_CASE_DEFINATION(_basic_string_iterator_minus)
void test__basic_string_iterator_minus__different_container_type(void** state)
{
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    it_first._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_basic_string_iterator_minus(it_first, it_second));
}

void test__basic_string_iterator_minus__different_iterator_type(void** state)
{
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    it_first._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_basic_string_iterator_minus(it_first, it_second));
}

void test__basic_string_iterator_minus__different_container_pointer(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    basic_string_init(pt_basic_string);

    it_first = basic_string_begin(pt_basic_string);

    expect_assert_failure(_basic_string_iterator_minus(it_first, it_second));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_minus__first_is_not_belong_to_basic_string(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    basic_string_init_elem(pt_basic_string, 10, 100);

    it_first = it_second = basic_string_begin(pt_basic_string);
    it_first._t_pos._pby_corepos = NULL;

    expect_assert_failure(_basic_string_iterator_minus(it_first, it_second));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_minus__second_is_not_belong_to_basic_string(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    basic_string_init_elem(pt_basic_string, 10, 100);

    it_first = it_second = basic_string_begin(pt_basic_string);
    it_second._t_pos._pby_corepos = NULL;

    expect_assert_failure(_basic_string_iterator_minus(it_first, it_second));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_minus__first_less_then_second(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    basic_string_init_elem(pt_basic_string, 10, 100);

    it_first = basic_string_begin(pt_basic_string);
    it_second = basic_string_end(pt_basic_string);

    assert_int_equal(_basic_string_iterator_minus(it_first, it_second), -10);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_minus__first_greater_then_second(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    basic_string_init_elem(pt_basic_string, 10, 100);

    it_first = basic_string_end(pt_basic_string);
    it_second = basic_string_begin(pt_basic_string);

    assert_int_equal(_basic_string_iterator_minus(it_first, it_second), 10);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_iterator_minus__first_equal_to_second(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_iterator_t it_first = _create_basic_string_iterator();
    basic_string_iterator_t it_second = _create_basic_string_iterator();

    basic_string_init_elem(pt_basic_string, 10, 100);

    it_first = basic_string_begin(pt_basic_string);
    it_second = basic_string_begin(pt_basic_string);

    assert_int_equal(_basic_string_iterator_minus(it_first, it_second), 0);

    basic_string_destroy(pt_basic_string);
}

