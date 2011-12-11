#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/cstl_slist_iterator.h"
#include "cstl/cslist.h"
#include "cstl/cvector.h"
#include "cstl/cstring.h"

#include "ut_def.h"
#include "ut_cstl_slist_iterator.h"

UT_SUIT_DEFINATION(cstl_slist_iterator, _create_slist_iterator);

/*
 * test _create_slist_iterator
 */
UT_CASE_DECLARATION(_create_slist_iterator)
void test__create_slist_iterator__successfully(void** state)
{
    slist_iterator_t it_iter = _create_slist_iterator();
    assert_true(it_iter._t_pos._pby_corepos == NULL);
    assert_true(it_iter._pt_container == NULL);
    assert_true(it_iter._t_containertype == _SLIST_CONTAINER);
    assert_true(it_iter._t_iteratortype == _FORWARD_ITERATOR);
}

/*
 * test _slist_iterator_get_value
 */
UT_CASE_DEFINATION(_slist_iterator_get_value)
void test__slist_iterator_get_value__invalid_iterator(void** state)
{
    int n_value = 0;
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 100);
    it_iter = slist_begin(pslist);
    it_iter._t_pos._pby_corepos = (_byte_t*)0x998;
    expect_assert_failure(_slist_iterator_get_value(it_iter, &n_value));

    slist_destroy(pslist);
}

void test__slist_iterator_get_value__invalid_iterator_container_type(void** state)
{
    int n_value = 0;
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 100);
    it_iter = slist_begin(pslist);
    it_iter._t_containertype = 2199;
    expect_assert_failure(_slist_iterator_get_value(it_iter, &n_value));

    slist_destroy(pslist);
}

void test__slist_iterator_get_value__invalid_iterator_iterator_type(void** state)
{
    int n_value = 0;
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 100);
    it_iter = slist_begin(pslist);
    it_iter._t_iteratortype = 24455;
    expect_assert_failure(_slist_iterator_get_value(it_iter, &n_value));

    slist_destroy(pslist);
}

void test__slist_iterator_get_value__invalid_iterator_end(void** state)
{
    int n_value = 0;
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 100);
    it_iter = slist_end(pslist);
    expect_assert_failure(_slist_iterator_get_value(it_iter, &n_value));

    slist_destroy(pslist);
}

void test__slist_iterator_get_value__invalid_data_buffer(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 100);
    it_iter = slist_end(pslist);
    expect_assert_failure(_slist_iterator_get_value(it_iter, NULL));

    slist_destroy(pslist);
}

void test__slist_iterator_get_value__successfully(void** state)
{
    int n_value = 0;
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 100);
    it_iter = slist_begin(pslist);
    _slist_iterator_get_value(it_iter, &n_value);
    assert_true(n_value == 100);

    slist_destroy(pslist);
}

void test__slist_iterator_get_value__successfully_cstr(void** state)
{
    char* s_str = NULL;
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init_elem(pslist, 10, "abcdefg");
    it_iter = slist_begin(pslist);
    _slist_iterator_get_value(it_iter, &s_str);
    assert_true(strcmp(s_str, "abcdefg") == 0);

    slist_destroy(pslist);
}

/*
 * test _slist_iterator_set_value
 */
UT_CASE_DEFINATION(_slist_iterator_set_value)
void test__slist_iterator_set_value__invalid_iter(void** state)
{
    int n_value = 0;
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 100);
    it_iter = slist_begin(pslist);
    it_iter._t_pos._pby_corepos = (_byte_t*)0x999;
    expect_assert_failure(_slist_iterator_set_value(it_iter, &n_value));

    slist_destroy(pslist);
}

void test__slist_iterator_set_value__invalid_iter_container_type(void** state)
{
    int n_value = 0;
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 100);
    it_iter = slist_begin(pslist);
    it_iter._t_containertype = 224;
    expect_assert_failure(_slist_iterator_set_value(it_iter, &n_value));

    slist_destroy(pslist);
}

void test__slist_iterator_set_value__invalid_iter_iterator_type(void** state)
{
    int n_value = 0;
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 100);
    it_iter = slist_begin(pslist);
    it_iter._t_iteratortype = 9999;
    expect_assert_failure(_slist_iterator_set_value(it_iter, &n_value));

    slist_destroy(pslist);
}

void test__slist_iterator_set_value__invalid_iter_end(void** state)
{
    int n_value = 0;
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 100);
    it_iter = slist_end(pslist);
    expect_assert_failure(_slist_iterator_set_value(it_iter, &n_value));

    slist_destroy(pslist);
}

void test__slist_iterator_set_value__successfully(void** state)
{
    int n_value = 0;
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 100);
    it_iter = slist_begin(pslist);
    _slist_iterator_set_value(it_iter, &n_value);
    assert_true(*(int*)slist_front(pslist) == 0);

    slist_destroy(pslist);
}

void test__slist_iterator_set_value__successfully_cstr(void** state)
{
    const char* s_str = "mmmmm";
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init_elem(pslist, 10, "abcdefg");
    it_iter = slist_begin(pslist);
    _slist_iterator_set_value(it_iter, s_str);
    assert_true(strcmp((char*)slist_front(pslist), "mmmmm") == 0);

    slist_destroy(pslist);
}

/*
 * test _slist_iterator_get_pointer
 */
UT_CASE_DEFINATION(_slist_iterator_get_pointer)
void test__slist_iterator_get_pointer__invalid_iter(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 100);
    it_iter = slist_begin(pslist);
    it_iter._t_pos._pby_corepos = (_byte_t*)0x99;
    expect_assert_failure(_slist_iterator_get_pointer(it_iter));

    slist_destroy(pslist);
}

void test__slist_iterator_get_pointer__invalid_iter_container_type(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 100);
    it_iter = slist_begin(pslist);
    it_iter._t_containertype = 224;
    expect_assert_failure(_slist_iterator_get_pointer(it_iter));

    slist_destroy(pslist);
}

void test__slist_iterator_get_pointer__invalid_iter_iterator_type(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 100);
    it_iter = slist_begin(pslist);
    it_iter._t_iteratortype = 9999;
    expect_assert_failure(_slist_iterator_get_pointer(it_iter));

    slist_destroy(pslist);
}

void test__slist_iterator_get_pointer__successfully(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 100);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)_slist_iterator_get_pointer(it_iter) == 100);

    slist_destroy(pslist);
}

void test__slist_iterator_get_pointer__successfully_cstr(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init_elem(pslist, 10, "abcdefg");
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)_slist_iterator_get_pointer(it_iter), "abcdefg") == 0);

    slist_destroy(pslist);
}

/*
 * test _slist_iterator_get_pointer_ignore_cstr
 */
UT_CASE_DEFINATION(_slist_iterator_get_pointer_ignore_cstr)
void test__slist_iterator_get_pointer_ignore_cstr__invalid_iter(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 100);
    it_iter = slist_begin(pslist);
    it_iter._t_pos._pby_corepos = (_byte_t*)0x99;
    expect_assert_failure(_slist_iterator_get_pointer_ignore_cstr(it_iter));

    slist_destroy(pslist);
}

void test__slist_iterator_get_pointer_ignore_cstr__invalid_iter_container_type(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 100);
    it_iter = slist_begin(pslist);
    it_iter._t_containertype = 224;
    expect_assert_failure(_slist_iterator_get_pointer_ignore_cstr(it_iter));

    slist_destroy(pslist);
}

void test__slist_iterator_get_pointer_ignore_cstr__invalid_iter_iterator_type(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 100);
    it_iter = slist_begin(pslist);
    it_iter._t_iteratortype = 9999;
    expect_assert_failure(_slist_iterator_get_pointer_ignore_cstr(it_iter));

    slist_destroy(pslist);
}

void test__slist_iterator_get_pointer_ignore_cstr__successfully(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 100);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)_slist_iterator_get_pointer_ignore_cstr(it_iter) == 100);

    slist_destroy(pslist);
}

void test__slist_iterator_get_pointer_ignore_cstr__successfully_cstr(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init_elem(pslist, 10, "abcdefg");
    it_iter = slist_begin(pslist);
    assert_true(strcmp(string_c_str(_slist_iterator_get_pointer_ignore_cstr(it_iter)), "abcdefg") == 0);

    slist_destroy(pslist);
}

/*
 * test _slist_iterator_next
 */
UT_CASE_DEFINATION(_slist_iterator_next)
void test__slist_iterator_next__invalid_iter(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 100);
    it_iter = slist_begin(pslist);
    it_iter._t_pos._pby_corepos = (_byte_t*)0x83;
    expect_assert_failure(_slist_iterator_next(it_iter));

    slist_destroy(pslist);
}

void test__slist_iterator_next__invalid_iter_container_type(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 100);
    it_iter = slist_begin(pslist);
    it_iter._t_containertype = 245;
    expect_assert_failure(_slist_iterator_next(it_iter));

    slist_destroy(pslist);
}

void test__slist_iterator_next__invalid_iter_iterator_type(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 100);
    it_iter = slist_begin(pslist);
    it_iter._t_iteratortype = 999;
    expect_assert_failure(_slist_iterator_next(it_iter));

    slist_destroy(pslist);
}

void test__slist_iterator_next__invalid_iter_end(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 100);
    it_iter = slist_end(pslist);
    expect_assert_failure(_slist_iterator_next(it_iter));

    slist_destroy(pslist);
}

void test__slist_iterator_next__successfully_end(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 1, 100);
    it_iter = slist_begin(pslist);
    it_iter = _slist_iterator_next(it_iter);
    assert_true(iterator_equal(it_iter, slist_end(pslist)));

    slist_destroy(pslist);
}

void test__slist_iterator_next__successfully(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 1, 100);
    slist_push_front(pslist, 200);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 200);
    it_iter = _slist_iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 100);

    slist_destroy(pslist);
}

/*
 * test _slist_iterator_equal
 */
UT_CASE_DEFINATION(_slist_iterator_equal)
void test__slist_iterator_equal__first_invalid_container_type(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(double);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init(pslist_first);
    slist_init(pslist_second);

    it_first = slist_begin(pslist_first);
    it_second = slist_begin(pslist_second);
    it_first._t_containertype = 284923;

    expect_assert_failure(_slist_iterator_equal(it_first, it_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_iterator_equal__first_invalid_iterator_type(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(double);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init(pslist_first);
    slist_init(pslist_second);

    it_first = slist_begin(pslist_first);
    it_second = slist_begin(pslist_second);
    it_first._t_iteratortype = 284923;

    expect_assert_failure(_slist_iterator_equal(it_first, it_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_iterator_equal__second_invalid_container_type(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(double);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init(pslist_first);
    slist_init(pslist_second);

    it_first = slist_begin(pslist_first);
    it_second = slist_begin(pslist_second);
    it_second._t_containertype = 284923;

    expect_assert_failure(_slist_iterator_equal(it_first, it_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_iterator_equal__second_invalid_iterator_type(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(double);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init(pslist_first);
    slist_init(pslist_second);

    it_first = slist_begin(pslist_first);
    it_second = slist_begin(pslist_second);
    it_second._t_iteratortype = 284923;

    expect_assert_failure(_slist_iterator_equal(it_first, it_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_iterator_equal__not_same_container(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init(pslist_first);
    slist_init(pslist_second);

    it_first = slist_begin(pslist_first);
    it_second = slist_begin(pslist_second);

    expect_assert_failure(_slist_iterator_equal(it_first, it_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_iterator_equal__first_not_belong_to_slist(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init(pslist);
    it_first = slist_begin(pslist);
    it_second = slist_begin(pslist);
    it_first._t_pos._pby_corepos = (char*)0x01;

    expect_assert_failure(_slist_iterator_equal(it_first, it_second));

    slist_destroy(pslist);
}

void test__slist_iterator_equal__second_not_belong_to_slist(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init(pslist);
    it_first = slist_begin(pslist);
    it_second = slist_begin(pslist);
    it_second._t_pos._pby_corepos = (char*)0x01;

    expect_assert_failure(_slist_iterator_equal(it_first, it_second));

    slist_destroy(pslist);
}

void test__slist_iterator_equal__two_vector_iterator(void** state)
{
    vector_t* pvector = create_vector(int);
    vector_iterator_t it_first;
    vector_iterator_t it_second;

    vector_init_n(pvector, 10);
    it_first = vector_begin(pvector);
    it_second = vector_begin(pvector);

    expect_assert_failure(_slist_iterator_equal(it_first, it_second));

    vector_destroy(pvector);
}

void test__slist_iterator_equal__equal(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init_n(pslist, 10);
    it_first = slist_begin(pslist);
    it_second = slist_begin(pslist);

    assert_true(_slist_iterator_equal(it_first, it_second));

    slist_destroy(pslist);
}

void test__slist_iterator_equal__not_equal(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init_n(pslist, 10);
    it_first = slist_begin(pslist);
    it_second = slist_end(pslist);

    assert_false(_slist_iterator_equal(it_first, it_second));

    slist_destroy(pslist);
}

/*
 * test _slist_iterator_distance
 */
UT_CASE_DEFINATION(_slist_iterator_distance)
void test__slist_iterator_distance__first_invalid_container_type(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(double);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init(pslist_first);
    slist_init(pslist_second);

    it_first = slist_begin(pslist_first);
    it_second = slist_begin(pslist_second);
    it_first._t_containertype = 284923;

    expect_assert_failure(_slist_iterator_distance(it_first, it_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_iterator_distance__first_invalid_iterator_type(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(double);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init(pslist_first);
    slist_init(pslist_second);

    it_first = slist_begin(pslist_first);
    it_second = slist_begin(pslist_second);
    it_first._t_iteratortype = 284923;

    expect_assert_failure(_slist_iterator_distance(it_first, it_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_iterator_distance__second_invalid_container_type(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(double);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init(pslist_first);
    slist_init(pslist_second);

    it_first = slist_begin(pslist_first);
    it_second = slist_begin(pslist_second);
    it_second._t_containertype = 284923;

    expect_assert_failure(_slist_iterator_distance(it_first, it_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_iterator_distance__second_invalid_iterator_type(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(double);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init(pslist_first);
    slist_init(pslist_second);

    it_first = slist_begin(pslist_first);
    it_second = slist_begin(pslist_second);
    it_second._t_iteratortype = 284923;

    expect_assert_failure(_slist_iterator_distance(it_first, it_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_iterator_distance__not_same_container(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init(pslist_first);
    slist_init(pslist_second);

    it_first = slist_begin(pslist_first);
    it_second = slist_begin(pslist_second);

    expect_assert_failure(_slist_iterator_distance(it_first, it_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_iterator_distance__first_not_belong_to_slist(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init(pslist);
    it_first = slist_begin(pslist);
    it_second = slist_begin(pslist);
    it_first._t_pos._pby_corepos = (char*)0x01;

    expect_assert_failure(_slist_iterator_distance(it_first, it_second));

    slist_destroy(pslist);
}

void test__slist_iterator_distance__second_not_belong_to_slist(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init(pslist);
    it_first = slist_begin(pslist);
    it_second = slist_begin(pslist);
    it_second._t_pos._pby_corepos = (char*)0x01;

    expect_assert_failure(_slist_iterator_distance(it_first, it_second));

    slist_destroy(pslist);
}

void test__slist_iterator_distance__two_vector_iterator(void** state)
{
    vector_t* pvector = create_vector(int);
    vector_iterator_t it_first;
    vector_iterator_t it_second;

    vector_init_n(pvector, 10);
    it_first = vector_begin(pvector);
    it_second = vector_begin(pvector);

    expect_assert_failure(_slist_iterator_distance(it_first, it_second));

    vector_destroy(pvector);
}

void test__slist_iterator_distance__greater_than_0(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init_n(pslist, 10);
    it_first = slist_begin(pslist);
    it_second = slist_end(pslist);

    assert_true(_slist_iterator_distance(it_first, it_second) == 10);

    slist_destroy(pslist);
}

void test__slist_iterator_distance__empty(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init(pslist);
    it_first = slist_begin(pslist);
    it_second = slist_end(pslist);

    assert_true(_slist_iterator_distance(it_first, it_second) == 0);

    slist_destroy(pslist);
}

void test__slist_iterator_distance__non_empty_equal_to_0(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init_n(pslist, 10);
    it_first = iterator_next(slist_begin(pslist));
    it_second = it_first;

    assert_true(_slist_iterator_distance(it_first, it_second) == 0);

    slist_destroy(pslist);
}

void test__slist_iterator_distance__less_than_0(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init_n(pslist, 10);
    it_first = slist_begin(pslist);
    it_second = iterator_next(it_first);

    assert_true(_slist_iterator_distance(it_second, it_first) == -1);

    slist_destroy(pslist);
}

/*
 * test _slist_iterator_before
 */
UT_CASE_DEFINATION(_slist_iterator_before)
void test__slist_iterator_before__first_invalid_container_type(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(double);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init(pslist_first);
    slist_init(pslist_second);

    it_first = slist_begin(pslist_first);
    it_second = slist_begin(pslist_second);
    it_first._t_containertype = 284923;

    expect_assert_failure(_slist_iterator_before(it_first, it_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_iterator_before__first_invalid_iterator_type(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(double);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init(pslist_first);
    slist_init(pslist_second);

    it_first = slist_begin(pslist_first);
    it_second = slist_begin(pslist_second);
    it_first._t_iteratortype = 284923;

    expect_assert_failure(_slist_iterator_before(it_first, it_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_iterator_before__second_invalid_container_type(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(double);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init(pslist_first);
    slist_init(pslist_second);

    it_first = slist_begin(pslist_first);
    it_second = slist_begin(pslist_second);
    it_second._t_containertype = 284923;

    expect_assert_failure(_slist_iterator_before(it_first, it_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_iterator_before__second_invalid_iterator_type(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(double);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init(pslist_first);
    slist_init(pslist_second);

    it_first = slist_begin(pslist_first);
    it_second = slist_begin(pslist_second);
    it_second._t_iteratortype = 284923;

    expect_assert_failure(_slist_iterator_before(it_first, it_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_iterator_before__not_same_container(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init(pslist_first);
    slist_init(pslist_second);

    it_first = slist_begin(pslist_first);
    it_second = slist_begin(pslist_second);

    expect_assert_failure(_slist_iterator_before(it_first, it_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test__slist_iterator_before__first_not_belong_to_slist(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init(pslist);
    it_first = slist_begin(pslist);
    it_second = slist_begin(pslist);
    it_first._t_pos._pby_corepos = (char*)0x01;

    expect_assert_failure(_slist_iterator_before(it_first, it_second));

    slist_destroy(pslist);
}

void test__slist_iterator_before__second_not_belong_to_slist(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init(pslist);
    it_first = slist_begin(pslist);
    it_second = slist_begin(pslist);
    it_second._t_pos._pby_corepos = (char*)0x01;

    expect_assert_failure(_slist_iterator_before(it_first, it_second));

    slist_destroy(pslist);
}

void test__slist_iterator_before__two_vector_iterator(void** state)
{
    vector_t* pvector = create_vector(int);
    vector_iterator_t it_first;
    vector_iterator_t it_second;

    vector_init_n(pvector, 10);
    it_first = vector_begin(pvector);
    it_second = vector_begin(pvector);

    expect_assert_failure(_slist_iterator_before(it_first, it_second));

    vector_destroy(pvector);
}

void test__slist_iterator_before__before(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init_n(pslist, 10);
    it_first = slist_begin(pslist);
    it_second = slist_end(pslist);

    assert_true(_slist_iterator_before(it_first, it_second));

    slist_destroy(pslist);
}

void test__slist_iterator_before__empty(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init(pslist);
    it_first = slist_begin(pslist);
    it_second = slist_end(pslist);

    assert_false(_slist_iterator_before(it_first, it_second));

    slist_destroy(pslist);
}

void test__slist_iterator_before__non_empty_equal(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init_n(pslist, 10);
    it_first = iterator_next(slist_begin(pslist));
    it_second = it_first;

    assert_false(_slist_iterator_before(it_first, it_second));

    slist_destroy(pslist);
}

void test__slist_iterator_before__after(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_first;
    slist_iterator_t it_second;

    slist_init_n(pslist, 10);
    it_first = slist_end(pslist);
    it_second = slist_begin(pslist);

    assert_false(_slist_iterator_before(it_first, it_second));

    slist_destroy(pslist);
}

