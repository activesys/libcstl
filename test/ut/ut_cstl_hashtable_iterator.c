#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_alloc.h"
#include "cstl/cstl_types.h"
#include "cstl/citerator.h"
#include "cstl/cvector.h"
#include "cstl/cstl_hashtable_iterator.h"
#include "cstl/cstl_hashtable_private.h"
#include "cstl/cstl_hashtable.h"
#include "cstl_hashtable_aux.h"
#include "cstl/cstring.h"

#include "ut_def.h"
#include "ut_cstl_hashtable_iterator.h"

UT_SUIT_DEFINATION(cstl_hashtable_iterator, _create_hashtable_iterator)
/*
 * test _create_hashtable_iterator
 */
UT_CASE_DEFINATION(_create_hashtable_iterator)
void test__create_hashtable_iterator__successfully(void** state)
{
    _hashtable_iterator_t it_iter = _create_hashtable_iterator();
    assert_true(it_iter._t_pos._t_hashpos._pby_corepos == NULL);
    assert_true(it_iter._t_pos._t_hashpos._pby_bucketpos == NULL);
    assert_true(it_iter._t_pos._t_hashpos._pt_hashtable == NULL);
    assert_true(it_iter._pt_container == NULL);
}

/*
 * test _hashtable_iterator_get_value
 */
UT_CASE_DEFINATION(_hashtable_iterator_get_value)
void test__hashtable_iterator_get_value__null_corepos(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int elem = 0;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    _hashtable_insert_unique(pt_hashtable, &elem);
    it_iter = _hashtable_begin(pt_hashtable);

    it_iter._t_pos._t_hashpos._pby_corepos = (char*)0x9999;
    expect_assert_failure(_hashtable_iterator_get_value(it_iter, &elem));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_get_value__null_hashtable(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int elem = 0;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    it_iter = _hashtable_begin(pt_hashtable);

    it_iter._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hashtable_iterator_get_value(it_iter, &elem));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_get_value__end(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int elem = 0;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    it_iter = _hashtable_end(pt_hashtable);

    expect_assert_failure(_hashtable_iterator_get_value(it_iter, &elem));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_get_value__null_value(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int elem = 0;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    _hashtable_insert_unique(pt_hashtable, &elem);
    it_iter = _hashtable_end(pt_hashtable);

    expect_assert_failure(_hashtable_iterator_get_value(it_iter, NULL));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_get_value__c_builtin(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int elem = 12;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_insert_unique(pt_hashtable, &elem);

    it_iter = _hashtable_begin(pt_hashtable);
    elem = 0;
    _hashtable_iterator_get_value(it_iter, &elem);
    assert_true(elem == 12);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_get_value__cstr(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("char*");
    _hashtable_iterator_t it_iter;
    string_t* pstr = create_string();
    char* p = NULL;
    string_init_cstr(pstr, "abc");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_insert_unique(pt_hashtable, pstr);

    it_iter = _hashtable_begin(pt_hashtable);
    _hashtable_iterator_get_value(it_iter, &p);
    assert_true(strcmp(p, "abc") == 0);

    _hashtable_destroy(pt_hashtable);
    string_destroy(pstr);
}

void test__hashtable_iterator_get_value__libcstl_builtin(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("vector_t<int>");
    _hashtable_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    vector_init_n(pvec, 10);
    _hashtable_insert_unique(pt_hashtable, pvec);

    it_iter = _hashtable_begin(pt_hashtable);
    vector_clear(pvec);
    _hashtable_iterator_get_value(it_iter, pvec);
    assert_true(vector_size(pvec) == 10);

    _hashtable_destroy(pt_hashtable);
    vector_destroy(pvec);
}

typedef struct _tag_test__hashtable_iterator_get_value__user_define
{
    int elem;
}_test__hashtable_iterator_get_value__user_define_t;
void test__hashtable_iterator_get_value__user_define(void** state)
{
    _hashtable_t* pt_hashtable = NULL;
    _hashtable_iterator_t it_iter;
    _test__hashtable_iterator_get_value__user_define_t elem;

    type_register(_test__hashtable_iterator_get_value__user_define_t, NULL, NULL, NULL, NULL);
    pt_hashtable = _create_hashtable("_test__hashtable_iterator_get_value__user_define_t");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    elem.elem = 100;
    _hashtable_insert_unique(pt_hashtable, &elem);

    it_iter = _hashtable_begin(pt_hashtable);
    elem.elem = 0;
    _hashtable_iterator_get_value(it_iter, &elem);
    assert_true(elem.elem == 100);

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_iterator_get_pointer
 */
UT_CASE_DEFINATION(_hashtable_iterator_get_pointer)
void test__hashtable_iterator_get_pointer__null_corepos(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int elem = 9;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    _hashtable_insert_unique(pt_hashtable, &elem);
    it_iter = _hashtable_begin(pt_hashtable);

    it_iter._t_pos._t_hashpos._pby_corepos = (char*)0x3333;
    expect_assert_failure(_hashtable_iterator_get_pointer(it_iter));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_get_pointer__null_hashtable(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    it_iter = _hashtable_begin(pt_hashtable);

    it_iter._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hashtable_iterator_get_pointer(it_iter));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_get_pointer__end(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    it_iter = _hashtable_end(pt_hashtable);

    expect_assert_failure(_hashtable_iterator_get_pointer(it_iter));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_get_pointer__c_builtin(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int elem = 12;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_insert_unique(pt_hashtable, &elem);

    it_iter = _hashtable_begin(pt_hashtable);
    assert_true(*(int*)_hashtable_iterator_get_pointer(it_iter) == 12);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_get_pointer__cstr(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("char*");
    _hashtable_iterator_t it_iter;
    string_t* pstr = create_string();
    string_init_cstr(pstr, "abc");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_insert_unique(pt_hashtable, pstr);

    it_iter = _hashtable_begin(pt_hashtable);
    assert_true(strcmp((char*)_hashtable_iterator_get_pointer(it_iter), "abc") == 0);

    _hashtable_destroy(pt_hashtable);
    string_destroy(pstr);
}

void test__hashtable_iterator_get_pointer__libcstl_builtin(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("vector_t<int>");
    _hashtable_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    vector_init_n(pvec, 10);
    _hashtable_insert_unique(pt_hashtable, pvec);

    it_iter = _hashtable_begin(pt_hashtable);
    assert_true(vector_size((vector_t*)_hashtable_iterator_get_pointer(it_iter)) == 10);

    _hashtable_destroy(pt_hashtable);
    vector_destroy(pvec);
}

typedef struct _tag_test__hashtable_iterator_get_pointer__user_define
{
    int elem;
}_test__hashtable_iterator_get_pointer__user_define_t;
void test__hashtable_iterator_get_pointer__user_define(void** state)
{
    _hashtable_t* pt_hashtable = NULL;
    _hashtable_iterator_t it_iter;
    _test__hashtable_iterator_get_pointer__user_define_t elem;

    type_register(_test__hashtable_iterator_get_pointer__user_define_t, NULL, NULL, NULL, NULL);
    pt_hashtable = _create_hashtable("_test__hashtable_iterator_get_pointer__user_define_t");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    elem.elem = 100;
    _hashtable_insert_unique(pt_hashtable, &elem);

    it_iter = _hashtable_begin(pt_hashtable);
    assert_true(((_test__hashtable_iterator_get_pointer__user_define_t*)_hashtable_iterator_get_pointer(it_iter))->elem == 100);

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_iterator_get_pointer_ignore_cstr
 */
UT_CASE_DEFINATION(_hashtable_iterator_get_pointer_ignore_cstr)
void test__hashtable_iterator_get_pointer_ignore_cstr__null_corepos(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int elem = 9;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    _hashtable_insert_unique(pt_hashtable, &elem);
    it_iter = _hashtable_begin(pt_hashtable);

    it_iter._t_pos._t_hashpos._pby_corepos = (char*)0x3333;
    expect_assert_failure(_hashtable_iterator_get_pointer_ignore_cstr(it_iter));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_get_pointer_ignore_cstr__null_hashtable(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    it_iter = _hashtable_begin(pt_hashtable);

    it_iter._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hashtable_iterator_get_pointer_ignore_cstr(it_iter));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_get_pointer_ignore_cstr__end(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    it_iter = _hashtable_end(pt_hashtable);

    expect_assert_failure(_hashtable_iterator_get_pointer_ignore_cstr(it_iter));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_get_pointer_ignore_cstr__c_builtin(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int elem = 12;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_insert_unique(pt_hashtable, &elem);

    it_iter = _hashtable_begin(pt_hashtable);
    assert_true(*(int*)_hashtable_iterator_get_pointer_ignore_cstr(it_iter) == 12);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_get_pointer_ignore_cstr__cstr(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("char*");
    _hashtable_iterator_t it_iter;
    string_t* pstr = create_string();
    string_init_cstr(pstr, "abc");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_insert_unique(pt_hashtable, pstr);

    it_iter = _hashtable_begin(pt_hashtable);
    assert_true(strcmp(string_c_str(_hashtable_iterator_get_pointer_ignore_cstr(it_iter)), "abc") == 0);

    _hashtable_destroy(pt_hashtable);
    string_destroy(pstr);
}

void test__hashtable_iterator_get_pointer_ignore_cstr__libcstl_builtin(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("vector_t<int>");
    _hashtable_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    vector_init_n(pvec, 10);
    _hashtable_insert_unique(pt_hashtable, pvec);

    it_iter = _hashtable_begin(pt_hashtable);
    assert_true(vector_size((vector_t*)_hashtable_iterator_get_pointer_ignore_cstr(it_iter)) == 10);

    _hashtable_destroy(pt_hashtable);
    vector_destroy(pvec);
}

typedef struct _tag_test__hashtable_iterator_get_pointer_ignore_cstr__user_define
{
    int elem;
}_test__hashtable_iterator_get_pointer_ignore_cstr__user_define_t;
void test__hashtable_iterator_get_pointer_ignore_cstr__user_define(void** state)
{
    _hashtable_t* pt_hashtable = NULL;
    _hashtable_iterator_t it_iter;
    _test__hashtable_iterator_get_pointer_ignore_cstr__user_define_t elem;

    type_register(_test__hashtable_iterator_get_pointer_ignore_cstr__user_define_t, NULL, NULL, NULL, NULL);
    pt_hashtable = _create_hashtable("_test__hashtable_iterator_get_pointer_ignore_cstr__user_define_t");
    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    elem.elem = 100;
    _hashtable_insert_unique(pt_hashtable, &elem);

    it_iter = _hashtable_begin(pt_hashtable);
    assert_true(((_test__hashtable_iterator_get_pointer_ignore_cstr__user_define_t*)_hashtable_iterator_get_pointer_ignore_cstr(it_iter))->elem == 100);

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_iterator_next
 */
UT_CASE_DEFINATION(_hashtable_iterator_next)
void test__hashtable_iterator_next__null_corepos(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int elem = 9;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    _hashtable_insert_unique(pt_hashtable, &elem);
    it_iter = _hashtable_begin(pt_hashtable);

    it_iter._t_pos._t_hashpos._pby_corepos = (char*)0x9999;
    expect_assert_failure(_hashtable_iterator_next(it_iter));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_next__null_hashtable(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    it_iter = _hashtable_begin(pt_hashtable);

    it_iter._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hashtable_iterator_next(it_iter));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_next__end(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    it_iter = _hashtable_end(pt_hashtable);

    expect_assert_failure(_hashtable_iterator_next(it_iter));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_next__last(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int elem = 10;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    _hashtable_insert_unique(pt_hashtable, &elem);
    it_iter = _hashtable_begin(pt_hashtable);

    it_iter = _hashtable_iterator_next(it_iter);
    assert_true(_hashtable_iterator_equal(it_iter, _hashtable_end(pt_hashtable)));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_next__begin(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int elem = 10;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    _hashtable_insert_unique(pt_hashtable, &elem);
    elem = 3;
    _hashtable_insert_unique(pt_hashtable, &elem);
    it_iter = _hashtable_begin(pt_hashtable);
    assert_true(*(int*)_hashtable_iterator_get_pointer(it_iter) == 3);
    it_iter = _hashtable_iterator_next(it_iter);
    assert_true(*(int*)_hashtable_iterator_get_pointer(it_iter) == 10);

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_iterator_prev
 */
UT_CASE_DEFINATION(_hashtable_iterator_prev)
void test__hashtable_iterator_prev__null_corepos(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int elem = 0;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    it_iter = _hashtable_begin(pt_hashtable);

    it_iter._t_pos._t_hashpos._pby_corepos = (char*)0x9999;
    expect_assert_failure(_hashtable_iterator_prev(it_iter));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_prev__null_hashtable(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    it_iter = _hashtable_begin(pt_hashtable);

    it_iter._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hashtable_iterator_prev(it_iter));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_prev__begin(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int elem = 100;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_insert_unique(pt_hashtable, &elem);

    it_iter = _hashtable_begin(pt_hashtable);

    expect_assert_failure(_hashtable_iterator_prev(it_iter));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_prev__empty(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    it_iter = _hashtable_begin(pt_hashtable);

    expect_assert_failure(_hashtable_iterator_prev(it_iter));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_prev__end(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int elem = 10;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    _hashtable_insert_unique(pt_hashtable, &elem);
    it_iter = _hashtable_end(pt_hashtable);

    it_iter = _hashtable_iterator_prev(it_iter);
    assert_true(_hashtable_iterator_equal(it_iter, _hashtable_begin(pt_hashtable)));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_prev__last(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_iter;
    int elem = 10;
    _hashtable_init(pt_hashtable, 0, NULL, NULL);

    _hashtable_insert_unique(pt_hashtable, &elem);
    elem = 3;
    _hashtable_insert_unique(pt_hashtable, &elem);
    it_iter = _hashtable_iterator_prev(_hashtable_end(pt_hashtable));
    assert_true(*(int*)_hashtable_iterator_get_pointer(it_iter) == 10);
    it_iter = _hashtable_iterator_prev(it_iter);
    assert_true(*(int*)_hashtable_iterator_get_pointer(it_iter) == 3);

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_iterator_equal
 */
UT_CASE_DEFINATION(_hashtable_iterator_equal)
void test__hashtable_iterator_equal__invalid_first(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_first;
    _hashtable_iterator_t it_second;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    it_first = _hashtable_begin(pt_hashtable);
    it_second = _hashtable_begin(pt_hashtable);
    it_first._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hashtable_iterator_equal(it_first, it_second));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_equal__invalid_second(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_first;
    _hashtable_iterator_t it_second;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    it_first = _hashtable_begin(pt_hashtable);
    it_second = _hashtable_begin(pt_hashtable);
    it_second._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hashtable_iterator_equal(it_first, it_second));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_equal__not_same_hashtable(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    _hashtable_iterator_t it_first;
    _hashtable_iterator_t it_second;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);
    it_first = _hashtable_begin(pt_first);
    it_second = _hashtable_begin(pt_second);
    expect_assert_failure(_hashtable_iterator_equal(it_first, it_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_iterator_equal__equal(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_first;
    _hashtable_iterator_t it_second;
    int elem = 100;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_insert_unique(pt_hashtable, &elem);
    it_first = _hashtable_begin(pt_hashtable);
    it_second = _hashtable_begin(pt_hashtable);
    assert_true(_hashtable_iterator_equal(it_first, it_second));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_equal__not_equal(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_first;
    _hashtable_iterator_t it_second;
    int elem = 100;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_insert_unique(pt_hashtable, &elem);
    elem = 2;
    _hashtable_insert_unique(pt_hashtable, &elem);
    it_first = _hashtable_begin(pt_hashtable);
    it_second = _hashtable_iterator_next(it_first);
    assert_false(_hashtable_iterator_equal(it_first, it_second));

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_iterator_distance
 */
UT_CASE_DEFINATION(_hashtable_iterator_distance)
void test__hashtable_iterator_distance__invalid_first(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_first;
    _hashtable_iterator_t it_second;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    it_first = _hashtable_begin(pt_hashtable);
    it_second = _hashtable_begin(pt_hashtable);
    it_first._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hashtable_iterator_distance(it_first, it_second));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_distance__invalid_second(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_first;
    _hashtable_iterator_t it_second;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    it_first = _hashtable_begin(pt_hashtable);
    it_second = _hashtable_begin(pt_hashtable);
    it_second._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hashtable_iterator_distance(it_first, it_second));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_distance__not_same_hashtable(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    _hashtable_iterator_t it_first;
    _hashtable_iterator_t it_second;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);
    it_first = _hashtable_begin(pt_first);
    it_second = _hashtable_begin(pt_second);
    expect_assert_failure(_hashtable_iterator_distance(it_first, it_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_iterator_distance__0(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_first;
    _hashtable_iterator_t it_second;
    int elem = 100;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_insert_unique(pt_hashtable, &elem);
    it_first = _hashtable_begin(pt_hashtable);
    it_second = _hashtable_begin(pt_hashtable);
    assert_true(_hashtable_iterator_distance(it_first, it_second) == 0);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_distance__greater_0(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_first;
    _hashtable_iterator_t it_second;
    int elem = 100;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_insert_unique(pt_hashtable, &elem);
    elem = 2;
    _hashtable_insert_unique(pt_hashtable, &elem);
    it_first = _hashtable_begin(pt_hashtable);
    it_second = _hashtable_iterator_next(it_first);
    assert_true(_hashtable_iterator_distance(it_first, it_second) == 1);

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_distance__less_0(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_first;
    _hashtable_iterator_t it_second;
    int elem = 100;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_insert_unique(pt_hashtable, &elem);
    elem = 2;
    _hashtable_insert_unique(pt_hashtable, &elem);
    it_first = _hashtable_end(pt_hashtable);
    it_second = _hashtable_begin(pt_hashtable);
    assert_true(_hashtable_iterator_distance(it_first, it_second) == -2);

    _hashtable_destroy(pt_hashtable);
}

/*
 * test _hashtable_iterator_before
 */
UT_CASE_DEFINATION(_hashtable_iterator_before)
void test__hashtable_iterator_before__invalid_first(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_first;
    _hashtable_iterator_t it_second;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    it_first = _hashtable_begin(pt_hashtable);
    it_second = _hashtable_begin(pt_hashtable);
    it_first._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hashtable_iterator_before(it_first, it_second));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_before__invalid_second(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_first;
    _hashtable_iterator_t it_second;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    it_first = _hashtable_begin(pt_hashtable);
    it_second = _hashtable_begin(pt_hashtable);
    it_second._t_pos._t_hashpos._pt_hashtable = NULL;
    expect_assert_failure(_hashtable_iterator_before(it_first, it_second));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_before__not_same_hashtable(void** state)
{
    _hashtable_t* pt_first = _create_hashtable("int");
    _hashtable_t* pt_second = _create_hashtable("int");
    _hashtable_iterator_t it_first;
    _hashtable_iterator_t it_second;

    _hashtable_init(pt_first, 0, NULL, NULL);
    _hashtable_init(pt_second, 0, NULL, NULL);
    it_first = _hashtable_begin(pt_first);
    it_second = _hashtable_begin(pt_second);
    expect_assert_failure(_hashtable_iterator_before(it_first, it_second));

    _hashtable_destroy(pt_first);
    _hashtable_destroy(pt_second);
}

void test__hashtable_iterator_before__equal(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_first;
    _hashtable_iterator_t it_second;
    int elem = 100;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_insert_unique(pt_hashtable, &elem);
    it_first = _hashtable_begin(pt_hashtable);
    it_second = _hashtable_begin(pt_hashtable);
    assert_false(_hashtable_iterator_before(it_first, it_second));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_before__true(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_first;
    _hashtable_iterator_t it_second;
    int elem = 100;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_insert_unique(pt_hashtable, &elem);
    elem = 2;
    _hashtable_insert_unique(pt_hashtable, &elem);
    it_first = _hashtable_begin(pt_hashtable);
    it_second = _hashtable_iterator_next(it_first);
    assert_true(_hashtable_iterator_before(it_first, it_second));

    _hashtable_destroy(pt_hashtable);
}

void test__hashtable_iterator_before__false(void** state)
{
    _hashtable_t* pt_hashtable = _create_hashtable("int");
    _hashtable_iterator_t it_first;
    _hashtable_iterator_t it_second;
    int elem = 100;

    _hashtable_init(pt_hashtable, 0, NULL, NULL);
    _hashtable_insert_unique(pt_hashtable, &elem);
    elem = 2;
    _hashtable_insert_unique(pt_hashtable, &elem);
    it_first = _hashtable_end(pt_hashtable);
    it_second = _hashtable_begin(pt_hashtable);
    assert_false(_hashtable_iterator_before(it_first, it_second));

    _hashtable_destroy(pt_hashtable);
}

