#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/cstl_list_iterator.h"
#include "cstl/clist.h"
#include "cstl/cvector.h"
#include "cstl/cstring.h"

#include "ut_def.h"
#include "ut_cstl_list_iterator.h"

UT_SUIT_DEFINATION(cstl_list_iterator, _create_list_iterator);

/*
 * test _create_list_iterator
 */
UT_CASE_DEFINATION(_create_list_iterator)
void test__create_list_iterator__successfully(void** state)
{
    list_iterator_t it_iter = _create_list_iterator();
    assert_true(it_iter._t_pos._pby_corepos == NULL);
    assert_true(it_iter._pt_container == NULL);
    assert_true(it_iter._t_containertype == _LIST_CONTAINER);
    assert_true(it_iter._t_iteratortype == _BIDIRECTIONAL_ITERATOR);
}

/*
 * test _list_iterator_get_value
 */
UT_CASE_DEFINATION(_list_iterator_get_value)
void test__list_iterator_get_value__invalid_iterator(void** state)
{
    int n_value = 0;
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_begin(plist);
    it_iter._t_pos._pby_corepos = NULL;
    expect_assert_failure(_list_iterator_get_value(it_iter, &n_value));

    list_destroy(plist);
}

void test__list_iterator_get_value__invalid_iterator_container_type(void** state)
{
    int n_value = 0;
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_begin(plist);
    it_iter._t_containertype = 2199;
    expect_assert_failure(_list_iterator_get_value(it_iter, &n_value));

    list_destroy(plist);
}

void test__list_iterator_get_value__invalid_iterator_iterator_type(void** state)
{
    int n_value = 0;
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_begin(plist);
    it_iter._t_iteratortype = 24455;
    expect_assert_failure(_list_iterator_get_value(it_iter, &n_value));

    list_destroy(plist);
}

void test__list_iterator_get_value__invalid_iterator_end(void** state)
{
    int n_value = 0;
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_end(plist);
    expect_assert_failure(_list_iterator_get_value(it_iter, &n_value));

    list_destroy(plist);
}

void test__list_iterator_get_value__invalid_data_buffer(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_end(plist);
    expect_assert_failure(_list_iterator_get_value(it_iter, NULL));

    list_destroy(plist);
}

void test__list_iterator_get_value__successfully(void** state)
{
    int n_value = 0;
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_begin(plist);
    _list_iterator_get_value(it_iter, &n_value);
    assert_true(n_value == 100);

    list_destroy(plist);
}

void test__list_iterator_get_value__successfully_cstr(void** state)
{
    char* s_str = NULL;
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init_elem(plist, 10, "abcdefg");
    it_iter = list_begin(plist);
    _list_iterator_get_value(it_iter, &s_str);
    assert_true(strcmp(s_str, "abcdefg") == 0);

    list_destroy(plist);
}

/*
 * test _list_iterator_set_value
 */
UT_CASE_DEFINATION(_list_iterator_set_value)
void test__list_iterator_set_value__invalid_iter(void** state)
{
    int n_value = 0;
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_begin(plist);
    it_iter._t_pos._pby_corepos = NULL;
    expect_assert_failure(_list_iterator_set_value(it_iter, &n_value));

    list_destroy(plist);
}

void test__list_iterator_set_value__invalid_iter_container_type(void** state)
{
    int n_value = 0;
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_begin(plist);
    it_iter._t_containertype = 224;
    expect_assert_failure(_list_iterator_set_value(it_iter, &n_value));

    list_destroy(plist);
}

void test__list_iterator_set_value__invalid_iter_iterator_type(void** state)
{
    int n_value = 0;
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_begin(plist);
    it_iter._t_iteratortype = 9999;
    expect_assert_failure(_list_iterator_set_value(it_iter, &n_value));

    list_destroy(plist);
}

void test__list_iterator_set_value__invalid_iter_end(void** state)
{
    int n_value = 0;
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_end(plist);
    expect_assert_failure(_list_iterator_set_value(it_iter, &n_value));

    list_destroy(plist);
}

void test__list_iterator_set_value__successfully(void** state)
{
    int n_value = 0;
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_begin(plist);
    _list_iterator_set_value(it_iter, &n_value);
    assert_true(*(int*)list_front(plist) == 0);

    list_destroy(plist);
}

void test__list_iterator_set_value__successfully_cstr(void** state)
{
    const char* s_str = "mmmmm";
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init_elem(plist, 10, "abcdefg");
    it_iter = list_begin(plist);
    _list_iterator_set_value(it_iter, s_str);
    assert_true(strcmp((char*)list_front(plist), "mmmmm") == 0);

    list_destroy(plist);
}

/*
 * test _list_iterator_get_pointer
 */
UT_CASE_DEFINATION(_list_iterator_get_pointer)
void test__list_iterator_get_pointer__invalid_iter(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_begin(plist);
    it_iter._t_pos._pby_corepos = NULL;
    expect_assert_failure(_list_iterator_get_pointer(it_iter));

    list_destroy(plist);
}

void test__list_iterator_get_pointer__invalid_iter_container_type(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_begin(plist);
    it_iter._t_containertype = 224;
    expect_assert_failure(_list_iterator_get_pointer(it_iter));

    list_destroy(plist);
}

void test__list_iterator_get_pointer__invalid_iter_iterator_type(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_begin(plist);
    it_iter._t_iteratortype = 9999;
    expect_assert_failure(_list_iterator_get_pointer(it_iter));

    list_destroy(plist);
}

void test__list_iterator_get_pointer__successfully(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_begin(plist);
    assert_true(*(int*)_list_iterator_get_pointer(it_iter) == 100);

    list_destroy(plist);
}

void test__list_iterator_get_pointer__successfully_cstr(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init_elem(plist, 10, "abcdefg");
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)_list_iterator_get_pointer(it_iter), "abcdefg") == 0);

    list_destroy(plist);
}

/*
 * test _list_iterator_get_pointer_ignore_cstr
 */
UT_CASE_DEFINATION(_list_iterator_get_pointer_ignore_cstr)
void test__list_iterator_get_pointer_ignore_cstr__invalid_iter(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_begin(plist);
    it_iter._t_pos._pby_corepos = NULL;
    expect_assert_failure(_list_iterator_get_pointer_ignore_cstr(it_iter));

    list_destroy(plist);
}

void test__list_iterator_get_pointer_ignore_cstr__invalid_iter_container_type(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_begin(plist);
    it_iter._t_containertype = 224;
    expect_assert_failure(_list_iterator_get_pointer_ignore_cstr(it_iter));

    list_destroy(plist);
}

void test__list_iterator_get_pointer_ignore_cstr__invalid_iter_iterator_type(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_begin(plist);
    it_iter._t_iteratortype = 9999;
    expect_assert_failure(_list_iterator_get_pointer_ignore_cstr(it_iter));

    list_destroy(plist);
}

void test__list_iterator_get_pointer_ignore_cstr__successfully(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_begin(plist);
    assert_true(*(int*)_list_iterator_get_pointer_ignore_cstr(it_iter) == 100);

    list_destroy(plist);
}

void test__list_iterator_get_pointer_ignore_cstr__successfully_cstr(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init_elem(plist, 10, "abcdefg");
    it_iter = list_begin(plist);
    assert_true(strcmp(string_c_str(_list_iterator_get_pointer_ignore_cstr(it_iter)), "abcdefg") == 0);

    list_destroy(plist);
}

/*
 * test _list_iterator_next
 */
UT_CASE_DEFINATION(_list_iterator_next)
void test__list_iterator_next__invalid_iter(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_begin(plist);
    it_iter._t_pos._pby_corepos = NULL;
    expect_assert_failure(_list_iterator_next(it_iter));

    list_destroy(plist);
}

void test__list_iterator_next__invalid_iter_container_type(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_begin(plist);
    it_iter._t_containertype = 245;
    expect_assert_failure(_list_iterator_next(it_iter));

    list_destroy(plist);
}

void test__list_iterator_next__invalid_iter_iterator_type(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_begin(plist);
    it_iter._t_iteratortype = 999;
    expect_assert_failure(_list_iterator_next(it_iter));

    list_destroy(plist);
}

void test__list_iterator_next__invalid_iter_end(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_end(plist);
    expect_assert_failure(_list_iterator_next(it_iter));

    list_destroy(plist);
}

void test__list_iterator_next__successfully_end(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 1, 100);
    it_iter = list_begin(plist);
    it_iter = _list_iterator_next(it_iter);
    assert_true(iterator_equal(it_iter, list_end(plist)));

    list_destroy(plist);
}

void test__list_iterator_next__successfully(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 1, 100);
    list_push_back(plist, 200);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    it_iter = _list_iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 200);

    list_destroy(plist);
}

/*
 * test _list_iterator_prev
 */
UT_CASE_DEFINATION(_list_iterator_prev)
void test__list_iterator_prev__invalid_iter(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_begin(plist);
    it_iter._t_pos._pby_corepos = NULL;
    expect_assert_failure(_list_iterator_prev(it_iter));

    list_destroy(plist);
}

void test__list_iterator_prev__invalid_iter_container_type(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_begin(plist);
    it_iter._t_containertype = 245;
    expect_assert_failure(_list_iterator_prev(it_iter));

    list_destroy(plist);
}

void test__list_iterator_prev__invalid_iter_iterator_type(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_begin(plist);
    it_iter._t_iteratortype = 999;
    expect_assert_failure(_list_iterator_prev(it_iter));

    list_destroy(plist);
}

void test__list_iterator_prev__invalid_iter_begin(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    it_iter = list_begin(plist);
    expect_assert_failure(_list_iterator_prev(it_iter));

    list_destroy(plist);
}

void test__list_iterator_prev__successfully_begin(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 1, 100);
    it_iter = list_end(plist);
    it_iter = _list_iterator_prev(it_iter);
    assert_true(iterator_equal(it_iter, list_begin(plist)));

    list_destroy(plist);
}

void test__list_iterator_prev__successfully(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 1, 100);
    list_push_back(plist, 200);
    it_iter = list_end(plist);
    it_iter = _list_iterator_prev(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 200);

    list_destroy(plist);
}

/*
 * test _list_iterator_equal
 */
UT_CASE_DEFINATION(_list_iterator_equal)
void test__list_iterator_equal__first_invalid_container_type(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(double);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init(plist_first);
    list_init(plist_second);

    it_first = list_begin(plist_first);
    it_second = list_begin(plist_second);
    it_first._t_containertype = 284923;

    expect_assert_failure(_list_iterator_equal(it_first, it_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_iterator_equal__first_invalid_iterator_type(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(double);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init(plist_first);
    list_init(plist_second);

    it_first = list_begin(plist_first);
    it_second = list_begin(plist_second);
    it_first._t_iteratortype = 284923;

    expect_assert_failure(_list_iterator_equal(it_first, it_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_iterator_equal__second_invalid_container_type(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(double);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init(plist_first);
    list_init(plist_second);

    it_first = list_begin(plist_first);
    it_second = list_begin(plist_second);
    it_second._t_containertype = 284923;

    expect_assert_failure(_list_iterator_equal(it_first, it_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_iterator_equal__second_invalid_iterator_type(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(double);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init(plist_first);
    list_init(plist_second);

    it_first = list_begin(plist_first);
    it_second = list_begin(plist_second);
    it_second._t_iteratortype = 284923;

    expect_assert_failure(_list_iterator_equal(it_first, it_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_iterator_equal__not_same_container(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init(plist_first);
    list_init(plist_second);

    it_first = list_begin(plist_first);
    it_second = list_begin(plist_second);

    expect_assert_failure(_list_iterator_equal(it_first, it_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_iterator_equal__first_not_belong_to_list(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init(plist);
    it_first = list_begin(plist);
    it_second = list_begin(plist);
    it_first._t_pos._pby_corepos = (char*)0x01;

    expect_assert_failure(_list_iterator_equal(it_first, it_second));

    list_destroy(plist);
}

void test__list_iterator_equal__second_not_belong_to_list(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init(plist);
    it_first = list_begin(plist);
    it_second = list_begin(plist);
    it_second._t_pos._pby_corepos = (char*)0x01;

    expect_assert_failure(_list_iterator_equal(it_first, it_second));

    list_destroy(plist);
}

void test__list_iterator_equal__two_vector_iterator(void** state)
{
    vector_t* pvector = create_vector(int);
    vector_iterator_t it_first;
    vector_iterator_t it_second;

    vector_init_n(pvector, 10);
    it_first = vector_begin(pvector);
    it_second = vector_begin(pvector);

    expect_assert_failure(_list_iterator_equal(it_first, it_second));

    vector_destroy(pvector);
}

void test__list_iterator_equal__equal(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init_n(plist, 10);
    it_first = list_begin(plist);
    it_second = list_begin(plist);

    assert_true(_list_iterator_equal(it_first, it_second));

    list_destroy(plist);
}

void test__list_iterator_equal__not_equal(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init_n(plist, 10);
    it_first = list_begin(plist);
    it_second = list_end(plist);

    assert_false(_list_iterator_equal(it_first, it_second));

    list_destroy(plist);
}

/*
 * test _list_iterator_distance
 */
UT_CASE_DEFINATION(_list_iterator_distance)
void test__list_iterator_distance__first_invalid_container_type(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(double);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init(plist_first);
    list_init(plist_second);

    it_first = list_begin(plist_first);
    it_second = list_begin(plist_second);
    it_first._t_containertype = 284923;

    expect_assert_failure(_list_iterator_distance(it_first, it_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_iterator_distance__first_invalid_iterator_type(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(double);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init(plist_first);
    list_init(plist_second);

    it_first = list_begin(plist_first);
    it_second = list_begin(plist_second);
    it_first._t_iteratortype = 284923;

    expect_assert_failure(_list_iterator_distance(it_first, it_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_iterator_distance__second_invalid_container_type(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(double);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init(plist_first);
    list_init(plist_second);

    it_first = list_begin(plist_first);
    it_second = list_begin(plist_second);
    it_second._t_containertype = 284923;

    expect_assert_failure(_list_iterator_distance(it_first, it_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_iterator_distance__second_invalid_iterator_type(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(double);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init(plist_first);
    list_init(plist_second);

    it_first = list_begin(plist_first);
    it_second = list_begin(plist_second);
    it_second._t_iteratortype = 284923;

    expect_assert_failure(_list_iterator_distance(it_first, it_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_iterator_distance__not_same_container(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init(plist_first);
    list_init(plist_second);

    it_first = list_begin(plist_first);
    it_second = list_begin(plist_second);

    expect_assert_failure(_list_iterator_distance(it_first, it_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_iterator_distance__first_not_belong_to_list(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init(plist);
    it_first = list_begin(plist);
    it_second = list_begin(plist);
    it_first._t_pos._pby_corepos = (char*)0x01;

    expect_assert_failure(_list_iterator_distance(it_first, it_second));

    list_destroy(plist);
}

void test__list_iterator_distance__second_not_belong_to_list(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init(plist);
    it_first = list_begin(plist);
    it_second = list_begin(plist);
    it_second._t_pos._pby_corepos = (char*)0x01;

    expect_assert_failure(_list_iterator_distance(it_first, it_second));

    list_destroy(plist);
}

void test__list_iterator_distance__two_vector_iterator(void** state)
{
    vector_t* pvector = create_vector(int);
    vector_iterator_t it_first;
    vector_iterator_t it_second;

    vector_init_n(pvector, 10);
    it_first = vector_begin(pvector);
    it_second = vector_begin(pvector);

    expect_assert_failure(_list_iterator_distance(it_first, it_second));

    vector_destroy(pvector);
}

void test__list_iterator_distance__greater_than_0(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init_n(plist, 10);
    it_first = list_begin(plist);
    it_second = list_end(plist);

    assert_true(_list_iterator_distance(it_first, it_second) == 10);

    list_destroy(plist);
}

void test__list_iterator_distance__empty(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init(plist);
    it_first = list_begin(plist);
    it_second = list_end(plist);

    assert_true(_list_iterator_distance(it_first, it_second) == 0);

    list_destroy(plist);
}

void test__list_iterator_distance__non_empty_equal_to_0(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init_n(plist, 10);
    it_first = iterator_next(list_begin(plist));
    it_second = it_first;

    assert_true(_list_iterator_distance(it_first, it_second) == 0);

    list_destroy(plist);
}

void test__list_iterator_distance__less_than_0(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init_n(plist, 10);
    it_first = list_end(plist);
    it_second = iterator_prev(it_first);

    assert_true(_list_iterator_distance(it_first, it_second) == -1);

    list_destroy(plist);
}

/*
 * test _list_iterator_before
 */
UT_CASE_DEFINATION(_list_iterator_before)
void test__list_iterator_before__first_invalid_container_type(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(double);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init(plist_first);
    list_init(plist_second);

    it_first = list_begin(plist_first);
    it_second = list_begin(plist_second);
    it_first._t_containertype = 284923;

    expect_assert_failure(_list_iterator_before(it_first, it_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_iterator_before__first_invalid_iterator_type(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(double);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init(plist_first);
    list_init(plist_second);

    it_first = list_begin(plist_first);
    it_second = list_begin(plist_second);
    it_first._t_iteratortype = 284923;

    expect_assert_failure(_list_iterator_before(it_first, it_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_iterator_before__second_invalid_container_type(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(double);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init(plist_first);
    list_init(plist_second);

    it_first = list_begin(plist_first);
    it_second = list_begin(plist_second);
    it_second._t_containertype = 284923;

    expect_assert_failure(_list_iterator_before(it_first, it_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_iterator_before__second_invalid_iterator_type(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(double);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init(plist_first);
    list_init(plist_second);

    it_first = list_begin(plist_first);
    it_second = list_begin(plist_second);
    it_second._t_iteratortype = 284923;

    expect_assert_failure(_list_iterator_before(it_first, it_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_iterator_before__not_same_container(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init(plist_first);
    list_init(plist_second);

    it_first = list_begin(plist_first);
    it_second = list_begin(plist_second);

    expect_assert_failure(_list_iterator_before(it_first, it_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test__list_iterator_before__first_not_belong_to_list(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init(plist);
    it_first = list_begin(plist);
    it_second = list_begin(plist);
    it_first._t_pos._pby_corepos = (char*)0x01;

    expect_assert_failure(_list_iterator_before(it_first, it_second));

    list_destroy(plist);
}

void test__list_iterator_before__second_not_belong_to_list(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init(plist);
    it_first = list_begin(plist);
    it_second = list_begin(plist);
    it_second._t_pos._pby_corepos = (char*)0x01;

    expect_assert_failure(_list_iterator_before(it_first, it_second));

    list_destroy(plist);
}

void test__list_iterator_before__two_vector_iterator(void** state)
{
    vector_t* pvector = create_vector(int);
    vector_iterator_t it_first;
    vector_iterator_t it_second;

    vector_init_n(pvector, 10);
    it_first = vector_begin(pvector);
    it_second = vector_begin(pvector);

    expect_assert_failure(_list_iterator_before(it_first, it_second));

    vector_destroy(pvector);
}

void test__list_iterator_before__before(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init_n(plist, 10);
    it_first = list_begin(plist);
    it_second = list_end(plist);

    assert_true(_list_iterator_before(it_first, it_second));

    list_destroy(plist);
}

void test__list_iterator_before__empty(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init(plist);
    it_first = list_begin(plist);
    it_second = list_end(plist);

    assert_false(_list_iterator_before(it_first, it_second));

    list_destroy(plist);
}

void test__list_iterator_before__non_empty_equal(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init_n(plist, 10);
    it_first = iterator_next(list_begin(plist));
    it_second = it_first;

    assert_false(_list_iterator_before(it_first, it_second));

    list_destroy(plist);
}

void test__list_iterator_before__after(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_first;
    list_iterator_t it_second;

    list_init_n(plist, 10);
    it_first = list_end(plist);
    it_second = iterator_prev(it_first);

    assert_false(_list_iterator_before(it_first, it_second));

    list_destroy(plist);
}

