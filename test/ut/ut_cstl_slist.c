#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_iterator.h"
#include "cstl/cstl_slist_iterator.h"
#include "cstl/cslist.h"
#include "cstl/cvector.h"
#include "cstl_slist_aux.h"
#include "cstl/cstring.h"

#include "ut_def.h"
#include "ut_cstl_slist.h"

UT_SUIT_DEFINATION(cstl_slist, slist_init);

/*
 * test slist_init
 */        
UT_CASE_DEFINATION(slist_init)
void test_slist_init__null_slist_container(void** state)
{
    expect_assert_failure(slist_init(NULL));
}

void test_slist_init__non_created_slist_container(void** state)
{
    slist_t slist;
    slist._t_head._pt_next = 0x87734;
    expect_assert_failure(slist_init(&slist));
}

void test_slist_init__successfully(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    assert_true(_slist_is_inited(pslist));
    assert_true(slist_size(pslist) == 0);

    slist_destroy(pslist);
}

/*
 * test slist_init_n
 */
UT_CASE_DEFINATION(slist_init_n)
void test_slist_init_n__null_slist_container(void** state)
{
    expect_assert_failure(slist_init_n(NULL, 10));
}

void test_slist_init_n__non_created_slist_container(void** state)
{
    slist_t slist;
    slist._t_typeinfo._t_style = 23333;
    expect_assert_failure(slist_init_n(&slist, 10));
}

void test_slist_init_n__empty(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 0);
    assert_true(_slist_is_inited(pslist));
    assert_true(slist_size(pslist) == 0);

    slist_destroy(pslist);
}

void test_slist_init_n__c_builtin(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    assert_true(_slist_is_inited(pslist));
    assert_true(slist_size(pslist) == 10);
    for(it_iter = slist_begin(pslist);
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist);
}

void test_slist_init_n__cstr(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init_n(pslist, 10);
    assert_true(_slist_is_inited(pslist));
    assert_true(slist_size(pslist) == 10);
    for(it_iter = slist_begin(pslist);
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    }

    slist_destroy(pslist);
}

void test_slist_init_n__libcstl_builtin(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(vector_t<int>);

    slist_init_n(pslist, 10);
    assert_true(_slist_is_inited(pslist));
    assert_true(slist_size(pslist) == 10);
    for(it_iter = slist_begin(pslist);
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(_vector_is_inited((vector_t*)iterator_get_pointer(it_iter)));
        assert_true(vector_size((vector_t*)iterator_get_pointer(it_iter)) == 0);
    }

    slist_destroy(pslist);
}

typedef struct _tag_test_slist_init_n__user_define
{
    int n_elem;
}_test_slist_init_n__user_define_t;
void test_slist_init_n__user_define(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = NULL;

    type_register(_test_slist_init_n__user_define_t, NULL, NULL, NULL, NULL);
    pslist = create_slist(_test_slist_init_n__user_define_t);

    slist_init_n(pslist, 10);
    assert_true(_slist_is_inited(pslist));
    assert_true(slist_size(pslist) == 10);
    for(it_iter = slist_begin(pslist);
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(((_test_slist_init_n__user_define_t*)iterator_get_pointer(it_iter))->n_elem == 0);
    }

    slist_destroy(pslist);
}

/*
 * test slist_init_copy
 */
UT_CASE_DEFINATION(slist_init_copy)
void test_slist_init_copy__null_dest_slist_container(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_src);
    expect_assert_failure(slist_init_copy(NULL, pslist_src));

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_init_copy__null_src_slist_container(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    expect_assert_failure(slist_init_copy(pslist_dest, NULL));

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_init_copy__non_created_dest_slist_container(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_src);
    pslist_dest->_t_head._pt_next = 0x8888;
    expect_assert_failure(slist_init_copy(pslist_dest, pslist_src));

    pslist_dest->_t_head._pt_next = NULL;
    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_init_copy__non_inited_src_slist_container(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_src);
    pslist_src->_t_typeinfo._t_style = 23234;
    expect_assert_failure(slist_init_copy(pslist_dest, pslist_src));

    pslist_src->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_init_copy__not_same_type(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(double);

    slist_init(pslist_src);
    expect_assert_failure(slist_init_copy(pslist_dest, pslist_src));

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_init_copy__init_copy_empty(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_src);
    slist_init_copy(pslist_dest, pslist_src);
    assert_true(_slist_is_inited(pslist_dest));
    assert_true(slist_size(pslist_dest) == slist_size(pslist_src));

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_init_copy__c_builtin(void** state)
{
    slist_iterator_t it_dest;
    slist_iterator_t it_src;
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_elem(pslist_src, 10, 100);
    slist_push_front(pslist_src, 1943);
    slist_push_front(pslist_src, 345);
    slist_init_copy(pslist_dest, pslist_src);
    assert_true(_slist_is_inited(pslist_dest));
    assert_true(slist_size(pslist_dest) == slist_size(pslist_src));
    for(it_dest = slist_begin(pslist_dest), it_src = slist_begin(pslist_src);
        !iterator_equal(it_dest, slist_end(pslist_dest)) && !iterator_equal(it_src, slist_end(pslist_src));
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        assert_true(*(int*)iterator_get_pointer(it_dest) == *(int*)iterator_get_pointer(it_src));
    }

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_init_copy__cstr(void** state)
{
    slist_iterator_t it_dest;
    slist_iterator_t it_src;
    slist_t* pslist_dest = create_slist(char*);
    slist_t* pslist_src = create_slist(char*);

    slist_init_elem(pslist_src, 10, "abcdefg");
    slist_push_front(pslist_src, "222222");
    slist_push_front(pslist_src, "aldjflakdjf");
    slist_init_copy(pslist_dest, pslist_src);
    assert_true(_slist_is_inited(pslist_dest));
    assert_true(slist_size(pslist_dest) == slist_size(pslist_src));
    for(it_dest = slist_begin(pslist_dest), it_src = slist_begin(pslist_src);
        !iterator_equal(it_dest, slist_end(pslist_dest)) && !iterator_equal(it_src, slist_end(pslist_src));
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        assert_true(strcmp((char*)iterator_get_pointer(it_dest), (char*)iterator_get_pointer(it_src)) == 0);
    }

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_init_copy__libcstl_builtin(void** state)
{
    slist_iterator_t it_dest;
    slist_iterator_t it_src;
    slist_t* pslist_dest = create_slist(slist_t<int>);
    slist_t* pslist_src = create_slist(slist_t<signed>);

    slist_init_n(pslist_src, 10);
    slist_init_copy(pslist_dest, pslist_src);
    assert_true(_slist_is_inited(pslist_dest));
    assert_true(slist_size(pslist_dest) == slist_size(pslist_src));
    for(it_dest = slist_begin(pslist_dest), it_src = slist_begin(pslist_src);
        !iterator_equal(it_dest, slist_end(pslist_dest)) && !iterator_equal(it_src, slist_end(pslist_src));
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        assert_true(slist_equal((slist_t*)iterator_get_pointer(it_dest), (slist_t*)iterator_get_pointer(it_src)));
    }

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

typedef struct _tag_test_slist_init_copy__user_define
{
    int n_elem;
}_test_slist_init_copy__user_define_t;
void test_slist_init_copy__user_define(void** state)
{
    slist_iterator_t it_dest;
    slist_iterator_t it_src;
    slist_t* pslist_dest = NULL;
    slist_t* pslist_src = NULL;

    type_register(_test_slist_init_copy__user_define_t, NULL, NULL, NULL, NULL);
    type_duplicate(_test_slist_init_copy__user_define_t, struct _tag_test_slist_init_copy__user_define);
    pslist_dest = create_slist(_test_slist_init_copy__user_define_t);
    pslist_src = create_slist(struct _tag_test_slist_init_copy__user_define);

    slist_init_n(pslist_src, 10);
    slist_init_copy(pslist_dest, pslist_src);
    assert_true(_slist_is_inited(pslist_dest));
    assert_true(slist_size(pslist_dest) == slist_size(pslist_src));
    for(it_dest = slist_begin(pslist_dest), it_src = slist_begin(pslist_src);
        !iterator_equal(it_dest, slist_end(pslist_dest)) && !iterator_equal(it_src, slist_end(pslist_src));
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        assert_true(((_test_slist_init_copy__user_define_t*)iterator_get_pointer(it_dest))->n_elem ==
            ((_test_slist_init_copy__user_define_t*)iterator_get_pointer(it_src))->n_elem);
    }

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

/*
 * test slist_init_copy_range
 */
UT_CASE_DEFINATION(slist_init_copy_range)
void test_slist_init_copy_range__null_slist_container(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_src);
    expect_assert_failure(slist_init_copy_range(NULL, slist_begin(pslist_src), slist_end(pslist_src)));

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_init_copy_range__non_created_slist_container(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_src);
    pslist_dest->_t_head._pt_next = 0x9999;
    expect_assert_failure(slist_init_copy_range(pslist_dest, slist_begin(pslist_src), slist_end(pslist_src)));

    pslist_dest->_t_head._pt_next = NULL;
    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_init_copy_range__invalid_range(void** state)
{
    slist_iterator_t it_begin;
    slist_iterator_t it_end;
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_src, 10);
    it_begin = slist_begin(pslist_src);
    it_end = slist_end(pslist_src);
    expect_assert_failure(slist_init_copy_range(pslist_dest, it_end, it_begin));

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_init_copy_range__not_same(void** state)
{
    slist_iterator_t it_begin;
    slist_iterator_t it_end;
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(double);

    slist_init_n(pslist_src, 10);
    it_begin = slist_begin(pslist_src);
    it_end = slist_end(pslist_src);
    expect_assert_failure(slist_init_copy_range(pslist_dest, it_begin, it_end));

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_init_copy_range__init_copy_range_empty(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_src);
    slist_init_copy_range(pslist_dest, slist_begin(pslist_src), slist_end(pslist_src));
    assert_true(_slist_is_inited(pslist_dest));
    assert_true(slist_size(pslist_dest) == 0);

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_init_copy_range__c_builtin(void** state)
{
    slist_iterator_t it_begin;
    slist_iterator_t it_end;
    slist_iterator_t it_dest;
    slist_iterator_t it_src;
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_elem(pslist_src, 10, 100);
    slist_push_front(pslist_src, 1943);
    slist_push_front(pslist_src, 345);
    it_begin = slist_begin(pslist_src);
    it_end = iterator_advance(it_begin, 3);
    slist_init_copy_range(pslist_dest, it_begin, it_end);
    assert_true(_slist_is_inited(pslist_dest));
    assert_true(slist_size(pslist_dest) == 3);
    for(it_dest = slist_begin(pslist_dest), it_src = it_begin;
        !iterator_equal(it_dest, slist_end(pslist_dest)) && !iterator_equal(it_src, it_end);
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        assert_true(*(int*)iterator_get_pointer(it_dest) == *(int*)iterator_get_pointer(it_src));
    }

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_init_copy_range__cstr(void** state)
{
    slist_iterator_t it_begin;
    slist_iterator_t it_end;
    slist_iterator_t it_dest;
    slist_iterator_t it_src;
    slist_t* pslist_dest = create_slist(char*);
    slist_t* pslist_src = create_slist(char*);

    slist_init_elem(pslist_src, 10, "abcdefg");
    slist_push_front(pslist_src, "222222");
    slist_push_front(pslist_src, "aldjflakdjf");
    it_begin = iterator_advance(slist_begin(pslist_src), 3);
    it_end = iterator_advance(it_begin, 3);
    slist_init_copy_range(pslist_dest, it_begin, it_end);
    assert_true(_slist_is_inited(pslist_dest));
    assert_true(slist_size(pslist_dest) == 3);
    for(it_dest = slist_begin(pslist_dest), it_src = it_begin;
        !iterator_equal(it_dest, slist_end(pslist_dest)) && !iterator_equal(it_src, it_end);
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        assert_true(strcmp((char*)iterator_get_pointer(it_dest), (char*)iterator_get_pointer(it_src)) == 0);
    }

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_init_copy_range__libcstl_builtin(void** state)
{
    slist_iterator_t it_begin;
    slist_iterator_t it_end;
    slist_iterator_t it_dest;
    slist_iterator_t it_src;
    slist_t* pslist_dest = create_slist(slist_t<int>);
    slist_t* pslist_src = create_slist(slist_t<signed>);

    slist_init_n(pslist_src, 10);
    it_begin = iterator_advance(slist_begin(pslist_src), 3);
    it_end = slist_end(pslist_src);
    slist_init_copy_range(pslist_dest, it_begin, it_end);
    assert_true(_slist_is_inited(pslist_dest));
    assert_true(slist_size(pslist_dest) == 7);
    for(it_dest = slist_begin(pslist_dest), it_src = it_begin;
        !iterator_equal(it_dest, slist_end(pslist_dest)) && !iterator_equal(it_src, it_end);
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        assert_true(slist_equal((slist_t*)iterator_get_pointer(it_dest), (slist_t*)iterator_get_pointer(it_src)));
    }

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

typedef struct _tag_test_slist_init_copy_range__user_define
{
    int n_elem;
}_test_slist_init_copy_range__user_define_t;
void test_slist_init_copy_range__user_define(void** state)
{
    slist_iterator_t it_dest;
    slist_iterator_t it_src;
    slist_t* pslist_dest = NULL;
    slist_t* pslist_src = NULL;

    type_register(_test_slist_init_copy_range__user_define_t, NULL, NULL, NULL, NULL);
    type_duplicate(_test_slist_init_copy_range__user_define_t, struct _tag_test_slist_init_copy_range__user_define);
    pslist_dest = create_slist(_test_slist_init_copy_range__user_define_t);
    pslist_src = create_slist(struct _tag_test_slist_init_copy_range__user_define);

    slist_init_n(pslist_src, 10);
    slist_init_copy_range(pslist_dest, slist_begin(pslist_src), slist_end(pslist_src));
    assert_true(_slist_is_inited(pslist_dest));
    assert_true(slist_size(pslist_dest) == slist_size(pslist_src));
    for(it_dest = slist_begin(pslist_dest), it_src = slist_begin(pslist_src);
        !iterator_equal(it_dest, slist_end(pslist_dest)) && !iterator_equal(it_src, slist_end(pslist_src));
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        assert_true(((_test_slist_init_copy_range__user_define_t*)iterator_get_pointer(it_dest))->n_elem ==
            ((_test_slist_init_copy_range__user_define_t*)iterator_get_pointer(it_src))->n_elem);
    }

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

/*
 * test slist_destroy
 */
UT_CASE_DEFINATION(slist_destroy)
void test_slist_destroy__null_slist_container(void** state)
{
    expect_assert_failure(slist_destroy(NULL));
}

void test_slist_destroy__non_created_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    pslist->_t_typeinfo._t_style = 2334;
    expect_assert_failure(slist_destroy(pslist));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test_slist_destroy__created_non_inited(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_destroy(pslist);
}

void test_slist_destroy__empty(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_destroy(pslist);
}

void test_slist_destroy__non_empty(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    slist_destroy(pslist);
}

/*
 * test slist_size
 */
UT_CASE_DEFINATION(slist_size)
void test_slist_size__null_slist_container(void** state)
{
    expect_assert_failure(slist_size(NULL));
}

void test_slist_size__non_inited_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    pslist->_t_typeinfo._t_style = 434;
    expect_assert_failure(slist_size(pslist));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test_slist_size__empty(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    assert_true(slist_size(pslist) == 0);

    slist_destroy(pslist);
}

void test_slist_size__non_empty(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    assert_true(slist_size(pslist) == 10);

    slist_destroy(pslist);
}

/*
 * test slist_empty
 */
UT_CASE_DEFINATION(slist_empty)
void test_slist_empty__null_slist_container(void** state)
{
    expect_assert_failure(slist_empty(NULL));
}

void test_slist_empty__non_inited_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    pslist->_t_typeinfo._t_style = 24345;
    expect_assert_failure(slist_empty(pslist));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test_slist_empty__empty(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    assert_true(slist_empty(pslist));

    slist_destroy(pslist);
}

void test_slist_empty__non_empty(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    assert_false(slist_empty(pslist));

    slist_destroy(pslist);
}

/*
 * test slist_max_size
 */
UT_CASE_DEFINATION(slist_max_size)
void test_slist_max_size__null_slist_container(void** state)
{
    expect_assert_failure(slist_max_size(NULL));
}

void test_slist_max_size__non_inited_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    pslist->_t_typeinfo._t_style = 3232;
    expect_assert_failure(slist_max_size(pslist));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test_slist_max_size__empty(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    assert_true(slist_max_size(pslist) != 0);

    slist_destroy(pslist);
}

void test_slist_max_size__non_empty(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    assert_true(slist_max_size(pslist) != 0);

    slist_destroy(pslist);
}

/*
 * test slist_equal
 */
UT_CASE_DEFINATION(slist_equal)
void test_slist_equal__null_first(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    expect_assert_failure(slist_equal(NULL, pslist));

    slist_destroy(pslist);
}

void test_slist_equal__null_second(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    expect_assert_failure(slist_equal(pslist, NULL));

    slist_destroy(pslist);
}

void test_slist_equal__non_inited_first(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_second);
    pslist_first->_t_typeinfo._t_style = 9999;
    expect_assert_failure(slist_equal(pslist_first, pslist_second));

    pslist_first->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_equal__non_inited_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_first);
    pslist_second->_t_typeinfo._t_style = 23434;
    expect_assert_failure(slist_equal(pslist_first, pslist_second));

    pslist_second->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_equal__not_same_type(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(double);

    slist_init(pslist_first);
    slist_init(pslist_second);
    assert_false(slist_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_equal__same_slist(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    assert_true(slist_equal(pslist, pslist));

    slist_destroy(pslist);
}

void test_slist_equal__size_first_less_than_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_first);
    slist_init_n(pslist_second, 48);
    assert_false(slist_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_equal__size_first_greater_than_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init_n(pslist_first, 233);
    slist_init_n(pslist_second, 48);
    assert_false(slist_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_equal__size_equal_0(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_first);
    slist_init(pslist_second);
    assert_true(slist_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_equal__size_equal_elem_first_less_than_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init_elem(pslist_first, 10, 100);
    slist_init_elem(pslist_second, 10, 4545);
    assert_false(slist_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_equal__size_equal_elem_first_greater_than_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init_elem(pslist_first, 10, 100);
    slist_init_elem(pslist_second, 10, 45);
    assert_false(slist_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_equal__size_equal_elem_equal(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init_elem(pslist_first, 10, 100);
    slist_init_elem(pslist_second, 10, 100);
    assert_true(slist_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

/*
 * test slist_not_equal
 */
UT_CASE_DEFINATION(slist_not_equal)
void test_slist_not_equal__null_first(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    expect_assert_failure(slist_not_equal(NULL, pslist));

    slist_destroy(pslist);
}

void test_slist_not_equal__null_second(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    expect_assert_failure(slist_not_equal(pslist, NULL));

    slist_destroy(pslist);
}

void test_slist_not_equal__non_inited_first(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_second);
    pslist_first->_t_typeinfo._t_style = 432432;
    expect_assert_failure(slist_not_equal(pslist_first, pslist_second));

    pslist_first->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_not_equal__non_inited_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_first);
    pslist_second->_t_typeinfo._t_style = 2222;
    expect_assert_failure(slist_not_equal(pslist_first, pslist_second));

    pslist_second->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_not_equal__not_same_type(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(double);

    slist_init(pslist_first);
    slist_init(pslist_second);
    assert_true(slist_not_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_not_equal__same_slist(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    assert_false(slist_not_equal(pslist, pslist));

    slist_destroy(pslist);
}

void test_slist_not_equal__size_first_less_than_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_first);
    slist_init_n(pslist_second, 48);
    assert_true(slist_not_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_not_equal__size_first_greater_than_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init_n(pslist_first, 233);
    slist_init_n(pslist_second, 48);
    assert_true(slist_not_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_not_equal__size_equal_0(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_first);
    slist_init(pslist_second);
    assert_false(slist_not_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_not_equal__size_equal_elem_first_less_than_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init_elem(pslist_first, 10, 100);
    slist_init_elem(pslist_second, 10, 4545);
    assert_true(slist_not_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_not_equal__size_equal_elem_first_greater_than_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init_elem(pslist_first, 10, 100);
    slist_init_elem(pslist_second, 10, 45);
    assert_true(slist_not_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_not_equal__size_equal_elem_equal(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init_elem(pslist_first, 10, 100);
    slist_init_elem(pslist_second, 10, 100);
    assert_false(slist_not_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

/*
 * test slist_less
 */
UT_CASE_DEFINATION(slist_less)
void test_slist_less__null_first(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    expect_assert_failure(slist_less(NULL, pslist));

    slist_destroy(pslist);
}

void test_slist_less__null_second(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    expect_assert_failure(slist_less(pslist, NULL));

    slist_destroy(pslist);
}

void test_slist_less__non_inited_first(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_second);
    pslist_first->_t_typeinfo._t_style = 4834;
    expect_assert_failure(slist_less(pslist_first, pslist_second));

    pslist_first->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_less__non_inited_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_first);
    pslist_second->_t_typeinfo._t_style = 22222;
    expect_assert_failure(slist_less(pslist_first, pslist_second));

    pslist_second->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_less__not_same_type(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(double);

    slist_init(pslist_first);
    slist_init(pslist_second);
    expect_assert_failure(slist_less(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_less__same_slist(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    assert_false(slist_less(pslist, pslist));

    slist_destroy(pslist);
}

void test_slist_less__size_first_less_than_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_first);
    slist_init_n(pslist_second, 48);
    assert_true(slist_less(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_less__size_first_greater_than_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init_n(pslist_first, 233);
    slist_init_n(pslist_second, 48);
    assert_false(slist_less(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_less__size_equal_0(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_first);
    slist_init(pslist_second);
    assert_false(slist_less(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_less__size_equal_elem_first_less_than_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init_elem(pslist_first, 10, 100);
    slist_init_elem(pslist_second, 10, 4545);
    assert_true(slist_less(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_less__size_equal_elem_first_greater_than_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init_elem(pslist_first, 10, 100);
    slist_init_elem(pslist_second, 10, 45);
    assert_false(slist_less(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_less__size_equal_elem_equal(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init_elem(pslist_first, 10, 100);
    slist_init_elem(pslist_second, 10, 100);
    assert_false(slist_less(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

/*
 * test slist_less_equal
 */
UT_CASE_DEFINATION(slist_less_equal)
void test_slist_less_equal__null_first(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    expect_assert_failure(slist_less_equal(NULL, pslist));

    slist_destroy(pslist);
}

void test_slist_less_equal__null_second(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    expect_assert_failure(slist_less_equal(pslist, NULL));

    slist_destroy(pslist);
}

void test_slist_less_equal__non_inited_first(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_second);
    pslist_first->_t_typeinfo._t_style = 2233;
    expect_assert_failure(slist_less_equal(pslist_first, pslist_second));

    pslist_first->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_less_equal__non_inited_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_first);
    pslist_second->_t_typeinfo._t_style = 2222;
    expect_assert_failure(slist_less_equal(pslist_first, pslist_second));

    pslist_second->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_less_equal__not_same_type(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(double);

    slist_init(pslist_first);
    slist_init(pslist_second);
    expect_assert_failure(slist_less_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_less_equal__same_slist(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    assert_true(slist_less_equal(pslist, pslist));

    slist_destroy(pslist);
}

void test_slist_less_equal__size_first_less_than_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_first);
    slist_init_n(pslist_second, 48);
    assert_true(slist_less_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_less_equal__size_first_greater_than_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init_n(pslist_first, 233);
    slist_init_n(pslist_second, 48);
    assert_false(slist_less_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_less_equal__size_equal_0(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_first);
    slist_init(pslist_second);
    assert_true(slist_less_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_less_equal__size_equal_elem_first_less_than_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init_elem(pslist_first, 10, 100);
    slist_init_elem(pslist_second, 10, 4545);
    assert_true(slist_less_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_less_equal__size_equal_elem_first_greater_than_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init_elem(pslist_first, 10, 100);
    slist_init_elem(pslist_second, 10, 45);
    assert_false(slist_less_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_less_equal__size_equal_elem_equal(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init_elem(pslist_first, 10, 100);
    slist_init_elem(pslist_second, 10, 100);
    assert_true(slist_less_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

/*
 * test slist_greater
 */
UT_CASE_DEFINATION(slist_greater)
void test_slist_greater__null_first(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    expect_assert_failure(slist_greater(NULL, pslist));

    slist_destroy(pslist);
}

void test_slist_greater__null_second(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    expect_assert_failure(slist_greater(pslist, NULL));

    slist_destroy(pslist);
}

void test_slist_greater__non_inited_first(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_second);
    pslist_first->_t_typeinfo._t_style = 3455;
    expect_assert_failure(slist_greater(pslist_first, pslist_second));

    pslist_first->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_greater__non_inited_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_first);
    pslist_second->_t_typeinfo._t_style = 22222;
    expect_assert_failure(slist_greater(pslist_first, pslist_second));

    pslist_second->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_greater__not_same_type(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(double);

    slist_init(pslist_first);
    slist_init(pslist_second);
    expect_assert_failure(slist_greater(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_greater__same_slist(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    assert_false(slist_greater(pslist, pslist));

    slist_destroy(pslist);
}

void test_slist_greater__size_first_less_than_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_first);
    slist_init_n(pslist_second, 48);
    assert_false(slist_greater(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_greater__size_first_greater_than_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init_n(pslist_first, 233);
    slist_init_n(pslist_second, 48);
    assert_true(slist_greater(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_greater__size_equal_0(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_first);
    slist_init(pslist_second);
    assert_false(slist_greater(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_greater__size_equal_elem_first_less_than_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init_elem(pslist_first, 10, 100);
    slist_init_elem(pslist_second, 10, 4545);
    assert_false(slist_greater(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_greater__size_equal_elem_first_greater_than_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init_elem(pslist_first, 10, 100);
    slist_init_elem(pslist_second, 10, 45);
    assert_true(slist_greater(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_greater__size_equal_elem_equal(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init_elem(pslist_first, 10, 100);
    slist_init_elem(pslist_second, 10, 100);
    assert_false(slist_greater(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

/*
 * test slist_greater_equal
 */
UT_CASE_DEFINATION(slist_greater_equal)
void test_slist_greater_equal__null_first(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    expect_assert_failure(slist_greater_equal(NULL, pslist));

    slist_destroy(pslist);
}

void test_slist_greater_equal__null_second(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    expect_assert_failure(slist_greater_equal(pslist, NULL));

    slist_destroy(pslist);
}

void test_slist_greater_equal__non_inited_first(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_second);
    pslist_first->_t_typeinfo._t_style = 24345;
    expect_assert_failure(slist_greater_equal(pslist_first, pslist_second));

    pslist_first->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_greater_equal__non_inited_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_first);
    pslist_second->_t_typeinfo._t_style = 4444;
    expect_assert_failure(slist_greater_equal(pslist_first, pslist_second));

    pslist_second->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_greater_equal__not_same_type(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(double);

    slist_init(pslist_first);
    slist_init(pslist_second);
    expect_assert_failure(slist_greater_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_greater_equal__same_slist(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    assert_true(slist_greater_equal(pslist, pslist));

    slist_destroy(pslist);
}

void test_slist_greater_equal__size_first_less_than_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_first);
    slist_init_n(pslist_second, 48);
    assert_false(slist_greater_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_greater_equal__size_first_greater_than_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init_n(pslist_first, 233);
    slist_init_n(pslist_second, 48);
    assert_true(slist_greater_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_greater_equal__size_equal_0(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_first);
    slist_init(pslist_second);
    assert_true(slist_greater_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_greater_equal__size_equal_elem_first_less_than_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init_elem(pslist_first, 10, 100);
    slist_init_elem(pslist_second, 10, 4545);
    assert_false(slist_greater_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_greater_equal__size_equal_elem_first_greater_than_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init_elem(pslist_first, 10, 100);
    slist_init_elem(pslist_second, 10, 45);
    assert_true(slist_greater_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_greater_equal__size_equal_elem_equal(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init_elem(pslist_first, 10, 100);
    slist_init_elem(pslist_second, 10, 100);
    assert_true(slist_greater_equal(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

/*
 * test slist_assign
 */
UT_CASE_DEFINATION(slist_assign)
void test_slist_assign__null_dest(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    expect_assert_failure(slist_assign(NULL, pslist));

    slist_destroy(pslist);
}

void test_slist_assign__null_src(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    expect_assert_failure(slist_assign(pslist, NULL));

    slist_destroy(pslist);
}

void test_slist_assign__non_inited_dest(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_src);

    pslist_dest->_t_typeinfo._t_style = 232;
    expect_assert_failure(slist_assign(pslist_dest, pslist_src));

    pslist_dest->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_assign__non_inited_src(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_dest);

    pslist_src->_t_typeinfo._t_style = 32333;
    expect_assert_failure(slist_assign(pslist_dest, pslist_src));

    pslist_src->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_assign__not_same_type(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(double);

    slist_init(pslist_dest);
    slist_init(pslist_src);

    expect_assert_failure(slist_assign(pslist_dest, pslist_src));

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_assign__same_container(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);

    slist_assign(pslist, pslist);
    assert_true(slist_size(pslist) == 0);

    slist_destroy(pslist);
}

void test_slist_assign__0_assign_0(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_dest);
    slist_init(pslist_src);

    slist_assign(pslist_dest, pslist_src);
    assert_true(slist_size(pslist_dest) == 0);
    assert_true(slist_equal(pslist_dest, pslist_src));

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_assign__0_assign_10(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_dest);
    slist_init_n(pslist_src, 10);

    slist_assign(pslist_dest, pslist_src);
    assert_true(slist_size(pslist_dest) == 10);
    assert_true(slist_equal(pslist_dest, pslist_src));

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_assign__10_assign_0(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_dest, 10);
    slist_init(pslist_src);

    slist_assign(pslist_dest, pslist_src);
    assert_true(slist_equal(pslist_dest, pslist_src));
    assert_true(slist_size(pslist_dest) == 0);

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_assign__10_assign_10_slist_equal(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_dest, 10);
    slist_init_n(pslist_src, 10);

    slist_assign(pslist_dest, pslist_src);
    assert_true(slist_equal(pslist_dest, pslist_src));

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_assign__10_assign_10_slist_not_equal(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_elem(pslist_dest, 10, 100);
    slist_init_n(pslist_src, 10);

    slist_assign(pslist_dest, pslist_src);
    assert_true(slist_equal(pslist_dest, pslist_src));
    assert_true(slist_size(pslist_dest) == 10);

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_assign__10_assign_1000(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_elem(pslist_dest, 10, 100);
    slist_init_n(pslist_src, 1000);

    slist_assign(pslist_dest, pslist_src);
    assert_true(slist_equal(pslist_dest, pslist_src));
    assert_true(slist_size(pslist_dest) == 1000);

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

/*
 * test slist_assign_range
 */
UT_CASE_DEFINATION(slist_assign_range)
void test_slist_assign_range__null_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    expect_assert_failure(slist_assign_range(NULL, slist_begin(pslist), slist_end(pslist)));

    slist_destroy(pslist);
}

void test_slist_assign_range__non_inited(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init(pslist_src);

    pslist_dest->_t_typeinfo._t_style = 4324;
    expect_assert_failure(slist_assign_range(pslist_dest, slist_begin(pslist_src), slist_end(pslist_src)));

    pslist_dest->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_assign_range__invalid_it_begin(void** state)
{
    slist_iterator_t it_begin;
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init(pslist_src);
    slist_init(pslist_dest);
    it_begin._t_iteratortype = 284;

    expect_assert_failure(slist_assign_range(pslist_dest, it_begin, slist_end(pslist_src)));

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_assign_range__invalid_it_end(void** state)
{
    slist_iterator_t it_end;
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init(pslist_src);
    slist_init(pslist_dest);
    it_end._t_iteratortype = 284;

    expect_assert_failure(slist_assign_range(pslist_dest, slist_begin(pslist_src), it_end));

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_assign_range__invalid_range(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init_n(pslist_src, 12);
    slist_init(pslist_dest);

    expect_assert_failure(slist_assign_range(pslist_dest, slist_end(pslist_src), slist_begin(pslist_src)));

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_assign_range__invalid_range_not_same_type(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(double);
    slist_init_n(pslist_src, 12);
    slist_init(pslist_dest);

    expect_assert_failure(slist_assign_range(pslist_dest, slist_begin(pslist_src), slist_end(pslist_src)));

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_assign_range__range_belong_to_slist(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_init(pslist_dest);

    slist_assign_range(pslist_dest, slist_begin(pslist_dest), slist_end(pslist_dest));

    slist_destroy(pslist_dest);
}

void test_slist_assign_range__0_assign_range_0(void** state)
{
    size_t i = 0;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init_elem(pslist_src, 1200, 100);
    slist_init(pslist_dest);

    it_begin = slist_begin(pslist_src);
    it_end = slist_begin(pslist_src);
    slist_assign_range(pslist_dest, it_begin, it_end);
    assert_true(slist_size(pslist_dest) == iterator_distance(it_begin, it_end));
    assert_true(slist_size(pslist_dest) == 0);

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_assign_range__0_assign_range_10(void** state)
{
    slist_iterator_t it_iter;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init_elem(pslist_src, 1200, 100);
    slist_init(pslist_dest);

    it_begin = slist_begin(pslist_src);
    it_end = iterator_advance(it_begin, 10);
    slist_assign_range(pslist_dest, it_begin, it_end);
    assert_true(slist_size(pslist_dest) == iterator_distance(it_begin, it_end));
    assert_true(slist_size(pslist_dest) == 10);
    for(it_iter = slist_begin(pslist_dest);
        !iterator_equal(it_iter, slist_end(pslist_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_assign_range__10_assign_range_0(void** state)
{
    slist_iterator_t it_iter;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init_elem(pslist_src, 1200, 100);
    slist_init_elem(pslist_dest, 10, 700);

    it_begin = iterator_advance(slist_begin(pslist_src), 111);
    it_end = it_begin;
    slist_assign_range(pslist_dest, it_begin, it_end);
    assert_true(slist_size(pslist_dest) == iterator_distance(it_begin, it_end));
    assert_true(slist_size(pslist_dest) == 0);
    for(it_iter = slist_begin(pslist_dest);
        !iterator_equal(it_iter, slist_end(pslist_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_assign_range__10_assign_range_10_same_elem(void** state)
{
    slist_iterator_t it_iter;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init_elem(pslist_src, 1200, 100);
    slist_init_elem(pslist_dest, 10, 100);

    it_begin = iterator_advance(slist_begin(pslist_src), 111);
    it_end = iterator_advance(it_begin, 10);
    slist_assign_range(pslist_dest, it_begin, it_end);
    assert_true(slist_size(pslist_dest) == iterator_distance(it_begin, it_end));
    assert_true(slist_size(pslist_dest) == 10);
    for(it_iter = slist_begin(pslist_dest);
        !iterator_equal(it_iter, slist_end(pslist_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_assign_range__10_assign_range_10_not_same_elem(void** state)
{
    slist_iterator_t it_iter;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init_elem(pslist_src, 1200, 100);
    slist_init_elem(pslist_dest, 10, 0);

    it_begin = iterator_advance(slist_begin(pslist_src), 111);
    it_end = iterator_advance(it_begin, 10);
    slist_assign_range(pslist_dest, it_begin, it_end);
    assert_true(slist_size(pslist_dest) == iterator_distance(it_begin, it_end));
    assert_true(slist_size(pslist_dest) == 10);
    for(it_iter = slist_begin(pslist_dest);
        !iterator_equal(it_iter, slist_end(pslist_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_assign_range__10_assign_range_1000(void** state)
{
    slist_iterator_t it_iter;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init_elem(pslist_src, 1200, 100);
    slist_init_elem(pslist_dest, 10, 0);

    it_begin = iterator_advance(slist_begin(pslist_src), 111);
    it_end = iterator_advance(it_begin, 1000);
    slist_assign_range(pslist_dest, it_begin, it_end);
    assert_true(slist_size(pslist_dest) == iterator_distance(it_begin, it_end));
    assert_true(slist_size(pslist_dest) == 1000);
    for(it_iter = slist_begin(pslist_dest);
        !iterator_equal(it_iter, slist_end(pslist_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

/*
 * test slist_swap
 */
UT_CASE_DEFINATION(slist_swap)
void test_slist_swap__null_first(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    expect_assert_failure(slist_swap(NULL, pslist));

    slist_destroy(pslist);
}

void test_slist_swap__null_second(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    expect_assert_failure(slist_swap(pslist, NULL));

    slist_destroy(pslist);
}

void test_slist_swap__non_inited_first(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_second);

    pslist_first->_t_typeinfo._t_style = 4556;
    expect_assert_failure(slist_swap(pslist_first, pslist_second));

    pslist_first->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_swap__non_inited_second(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_first);

    pslist_second->_t_typeinfo._t_style = 4656;
    expect_assert_failure(slist_swap(pslist_first, pslist_second));

    pslist_second->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_swap__not_same_type(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(double);

    slist_init(pslist_first);
    slist_init(pslist_second);

    expect_assert_failure(slist_swap(pslist_first, pslist_second));

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_swap__slist_equal(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);

    slist_init(pslist_first);
    slist_init(pslist_second);

    slist_swap(pslist_first, pslist_second);

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_swap__0_swap_10(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);
    size_t t_firstsize = 0;
    size_t t_secondsize = 0;

    slist_init(pslist_first);
    slist_init_elem(pslist_second, 10, 100);

    t_firstsize = slist_size(pslist_first);
    t_secondsize = slist_size(pslist_second);
    slist_swap(pslist_first, pslist_second);

    assert_true(slist_size(pslist_first) == t_secondsize);
    assert_true(slist_size(pslist_second) == t_firstsize);
    for(it_iter = slist_begin(pslist_first);
        !iterator_equal(it_iter, slist_end(pslist_first));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }
    for(it_iter = slist_begin(pslist_second);
        !iterator_equal(it_iter, slist_end(pslist_second));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_swap__10_swap_0(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);
    size_t t_firstsize = 0;
    size_t t_secondsize = 0;
    slist_iterator_t it_iter;

    slist_init_n(pslist_first, 10);
    slist_init(pslist_second);

    t_firstsize = slist_size(pslist_first);
    t_secondsize = slist_size(pslist_second);
    slist_swap(pslist_first, pslist_second);

    assert_true(slist_size(pslist_first) == t_secondsize);
    assert_true(slist_size(pslist_second) == t_firstsize);
    for(it_iter = slist_begin(pslist_first);
        !iterator_equal(it_iter, slist_end(pslist_first));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }
    for(it_iter = slist_begin(pslist_second);
        !iterator_equal(it_iter, slist_end(pslist_second));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_swap__10_swap_10(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);
    size_t t_firstsize = 0;
    size_t t_secondsize = 0;
    slist_iterator_t it_iter;

    slist_init_n(pslist_first, 10);
    slist_init_elem(pslist_second, 10, 100);

    t_firstsize = slist_size(pslist_first);
    t_secondsize = slist_size(pslist_second);
    slist_swap(pslist_first, pslist_second);

    assert_true(slist_size(pslist_first) == t_secondsize);
    assert_true(slist_size(pslist_second) == t_firstsize);
    for(it_iter = slist_begin(pslist_first);
        !iterator_equal(it_iter, slist_end(pslist_first));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }
    for(it_iter = slist_begin(pslist_second);
        !iterator_equal(it_iter, slist_end(pslist_second));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

void test_slist_swap__10_swap_1000(void** state)
{
    slist_t* pslist_first = create_slist(int);
    slist_t* pslist_second = create_slist(int);
    size_t t_firstsize = 0;
    size_t t_secondsize = 0;
    slist_iterator_t it_iter;

    slist_init_n(pslist_first, 10);
    slist_init_elem(pslist_second, 1000, 100);

    t_firstsize = slist_size(pslist_first);
    t_secondsize = slist_size(pslist_second);
    slist_swap(pslist_first, pslist_second);

    assert_true(slist_size(pslist_first) == t_secondsize);
    assert_true(slist_size(pslist_second) == t_firstsize);
    for(it_iter = slist_begin(pslist_first);
        !iterator_equal(it_iter, slist_end(pslist_first));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }
    for(it_iter = slist_begin(pslist_second);
        !iterator_equal(it_iter, slist_end(pslist_second));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist_first);
    slist_destroy(pslist_second);
}

/*
 * test slist_front
 */
UT_CASE_DEFINATION(slist_front)
void test_slist_front__null_slist_container(void** state)
{
    expect_assert_failure(slist_front(NULL));
}

void test_slist_front__non_inited_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    pslist->_t_typeinfo._t_style = 44444;
    expect_assert_failure(slist_front(pslist));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test_slist_front__empty(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    expect_assert_failure(slist_front(pslist));

    slist_destroy(pslist);
}

void test_slist_front__successfully(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    slist_push_front(pslist, 2);
    slist_push_front(pslist, 345);
    slist_push_front(pslist, 24);
    assert_true(*(int*)slist_front(pslist) == 24);

    slist_destroy(pslist);
}

void test_slist_front__successfully_cstr(void** state)
{
    slist_t* pslist = create_slist(char*);
    slist_init(pslist);

    slist_push_front(pslist, "wodjad");
    slist_push_front(pslist, "345");
    slist_push_front(pslist, "mmmmmm");
    assert_true(strcmp((char*)slist_front(pslist), "mmmmmm") == 0);

    slist_destroy(pslist);
}

/*
 * test slist_begin
 */
UT_CASE_DEFINATION(slist_begin)
void test_slist_begin__null_slist_container(void** state)
{
    expect_assert_failure(slist_begin(NULL));
}

void test_slist_begin__non_inited_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    pslist->_t_typeinfo._t_style = 232332;
    expect_assert_failure(slist_begin(pslist));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test_slist_begin__empty(void** state)
{
    slist_iterator_t it_begin;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    it_begin = slist_begin(pslist);
    assert_true(_slist_iterator_belong_to_slist(pslist, it_begin));
    assert_true(iterator_equal(it_begin, slist_end(pslist)));

    slist_destroy(pslist);
}

void test_slist_begin__non_empty(void** state)
{
    slist_iterator_t it_begin;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    slist_push_front(pslist, 123);
    slist_push_front(pslist, 209);
    slist_push_front(pslist, 3);

    it_begin = slist_begin(pslist);
    assert_true(_slist_iterator_belong_to_slist(pslist, it_begin));
    assert_true(it_begin._t_pos._pc_corepos == pslist->_t_head._pt_next);
    assert_true(*(int*)iterator_get_pointer(it_begin) == 3);

    slist_destroy(pslist);
}

/*
 * test slist_end
 */
UT_CASE_DEFINATION(slist_end)
void test_slist_end__null_slist_container(void** state)
{
    expect_assert_failure(slist_end(NULL));
}

void test_slist_end__non_inited_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    pslist->_t_typeinfo._t_style = 4444;
    expect_assert_failure(slist_end(pslist));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test_slist_end__empty(void** state)
{
    slist_iterator_t it_end;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    it_end = slist_end(pslist);
    assert_true(_slist_iterator_belong_to_slist(pslist, it_end));
    assert_true(iterator_equal(it_end, slist_begin(pslist)));

    slist_destroy(pslist);
}

void test_slist_end__non_empty(void** state)
{
    slist_iterator_t it_end;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    slist_push_front(pslist, 123);
    slist_push_front(pslist, 209);
    slist_push_front(pslist, 3);

    it_end = slist_end(pslist);
    assert_true(_slist_iterator_belong_to_slist(pslist, it_end));
    assert_true(it_end._t_pos._pc_corepos == NULL);

    slist_destroy(pslist);
}

/*
 * test slist_previous
 */
UT_CASE_DEFINATION(slist_previous)
void test_slist_previous__null_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);
    expect_assert_failure(slist_previous(NULL, slist_end(pslist)));

    slist_destroy(pslist);
}

void test_slist_previous__non_inited_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    pslist->_t_typeinfo._t_style = 4444;
    expect_assert_failure(slist_previous(pslist, slist_end(pslist)));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test_slist_previous__empty(void** state)
{
    slist_iterator_t it_end;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    expect_assert_failure(slist_previous(pslist, slist_end(pslist)));

    slist_destroy(pslist);
}

void test_slist_previous__non_empty_begin(void** state)
{
    slist_iterator_t it_end;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    expect_assert_failure(slist_previous(pslist, slist_begin(pslist)));

    slist_destroy(pslist);
}

void test_slist_previous__non_empty_non_begin(void** state)
{
    slist_iterator_t it_end;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    slist_push_front(pslist, 123);
    slist_push_front(pslist, 209);
    slist_push_front(pslist, 3);

    it_end = iterator_next(slist_begin(pslist));
    it_end = slist_previous(pslist, it_end);
    assert_true(_slist_iterator_belong_to_slist(pslist, it_end));
    assert_true(iterator_equal(it_end, slist_begin(pslist)));
    assert_true(*(int*)iterator_get_pointer(it_end) == 3);

    slist_destroy(pslist);
}

void test_slist_previous__non_empty_end(void** state)
{
    slist_iterator_t it_end;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    slist_push_front(pslist, 123);
    slist_push_front(pslist, 209);
    slist_push_front(pslist, 3);

    it_end = slist_previous(pslist, slist_end(pslist));
    assert_true(_slist_iterator_belong_to_slist(pslist, it_end));
    assert_true(*(int*)iterator_get_pointer(it_end) == 123);

    slist_destroy(pslist);
}

/*
 * test slist_insert_range
 */
UT_CASE_DEFINATION(slist_insert_range)
void test_slist_insert_range__null_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init(pslist);
    slist_init(pslist_src);

    expect_assert_failure(slist_insert_range(NULL, slist_begin(pslist), slist_begin(pslist_src), slist_end(pslist_src)));

    slist_destroy(pslist);
    slist_destroy(pslist_src);
}

void test_slist_insert_range__non_inited(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init(pslist_src);
    slist_init(pslist);

    pslist->_t_typeinfo._t_style = 2323;
    expect_assert_failure(slist_insert_range(pslist, slist_begin(pslist), slist_begin(pslist_src), slist_end(pslist_src)));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
    slist_destroy(pslist_src);
}

void test_slist_insert_range__invalid_position(void** state)
{
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init(pslist_src);
    slist_init_n(pslist, 10);
    it_pos = slist_begin(pslist);
    it_pos._t_pos._pc_corepos = 0x8888;

    expect_assert_failure(slist_insert_range(pslist, it_pos, slist_begin(pslist_src), slist_end(pslist_src)));

    slist_destroy(pslist);
    slist_destroy(pslist_src);
}

void test_slist_insert_range__invalid_range(void** state)
{
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_iterator_t it_begin = _create_slist_iterator();
    slist_iterator_t it_end = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init_n(pslist_src, 10);
    slist_init_n(pslist, 10);
    it_pos = slist_begin(pslist);
    it_begin = slist_begin(pslist_src);
    it_end = slist_end(pslist_src);

    expect_assert_failure(slist_insert_range(pslist, it_pos, it_end, it_begin));

    slist_destroy(pslist);
    slist_destroy(pslist_src);
}

void test_slist_insert_range__invalid_range_not_same_type(void** state)
{
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_iterator_t it_begin = _create_slist_iterator();
    slist_iterator_t it_end = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(double);
    slist_init(pslist_src);
    slist_init_n(pslist, 10);
    it_pos = slist_begin(pslist);
    it_begin = slist_begin(pslist_src);
    it_end = slist_end(pslist_src);

    expect_assert_failure(slist_insert_range(pslist, it_pos, it_begin, it_end));

    slist_destroy(pslist);
    slist_destroy(pslist_src);
}

void test_slist_insert_range__invalid_range_belong_to_slist(void** state)
{
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_iterator_t it_begin = _create_slist_iterator();
    slist_iterator_t it_end = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init(pslist_src);
    slist_init_n(pslist, 10);
    it_pos = slist_begin(pslist);
    it_begin = slist_begin(pslist_src);
    it_end = slist_end(pslist_src);

    slist_insert_range(pslist, it_pos, it_pos, it_pos);

    slist_destroy(pslist);
    slist_destroy(pslist_src);
}

void test_slist_insert_range__empty_insert_0(void** state)
{
    slist_iterator_t it_pos;
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init(pslist);
    slist_init(pslist_src);

    assert_true(slist_size(pslist) == 0);
    it_pos = slist_begin(pslist);
    slist_insert_range(pslist, it_pos, slist_begin(pslist_src), slist_end(pslist_src));
    assert_true(slist_size(pslist) == 0);

    slist_destroy(pslist);
    slist_destroy(pslist_src);
}

void test_slist_insert_range__empty_insert_10(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init(pslist);
    slist_init_elem(pslist_src, 10, 100);

    assert_true(slist_size(pslist) == 0);
    it_pos = slist_begin(pslist);
    slist_insert_range(pslist, it_pos, slist_begin(pslist_src), slist_end(pslist_src));
    assert_true(slist_size(pslist) == 10);
    for(it_iter = slist_begin(pslist);
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    slist_destroy(pslist);
    slist_destroy(pslist_src);
}

void test_slist_insert_range__begin_insert_0(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init_n(pslist, 1000);
    slist_init_elem(pslist_src, 0, 100);

    assert_true(slist_size(pslist) == 1000);
    it_pos = slist_begin(pslist);
    slist_insert_range(pslist, it_pos, slist_begin(pslist_src), slist_end(pslist_src));
    assert_true(slist_size(pslist) == 1000);
    for(it_iter = slist_begin(pslist);
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist);
    slist_destroy(pslist_src);
}

void test_slist_insert_range__begin_insert_10(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init_elem(pslist_src, 10, 100);
    slist_init_n(pslist, 1000);

    assert_true(slist_size(pslist) == 1000);
    it_pos = slist_begin(pslist);
    slist_insert_range(pslist, it_pos, slist_begin(pslist_src), slist_end(pslist_src));
    assert_true(slist_size(pslist) == 1010);
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        if(i < 10)
        {
            assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
        }
        else
        {
            assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
        }
    }

    slist_destroy(pslist);
    slist_destroy(pslist_src);
}

void test_slist_insert_range__middle_insert_0(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init_elem(pslist_src, 0, 100);
    slist_init_n(pslist, 1000);

    assert_true(slist_size(pslist) == 1000);
    it_pos = iterator_advance(slist_begin(pslist), 300);
    slist_insert_range(pslist, it_pos, slist_begin(pslist_src), slist_end(pslist_src));
    assert_true(slist_size(pslist) == 1000);
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist);
    slist_destroy(pslist_src);
}

void test_slist_insert_range__middle_insert_10(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init_elem(pslist_src, 10, 100);
    slist_init_n(pslist, 1000);

    assert_true(slist_size(pslist) == 1000);
    it_pos = iterator_advance(slist_begin(pslist), 300);
    slist_insert_range(pslist, it_pos, slist_begin(pslist_src), slist_end(pslist_src));
    assert_true(slist_size(pslist) == 1010);
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        if(i >= 300 && i < 310)
        {
            assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
        }
        else
        {
            assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
        }
    }

    slist_destroy(pslist);
    slist_destroy(pslist_src);
}

void test_slist_insert_range__end_insert_0(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init_elem(pslist_src, 0, 100);
    slist_init_n(pslist, 1000);

    assert_true(slist_size(pslist) == 1000);
    it_pos = slist_end(pslist);
    slist_insert_range(pslist, it_pos, slist_begin(pslist_src), slist_end(pslist_src));
    assert_true(slist_size(pslist) == 1000);
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist);
    slist_destroy(pslist_src);
}

void test_slist_insert_range__end_insert_10(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init_elem(pslist_src, 10, 100);
    slist_init_n(pslist, 1000);

    assert_true(slist_size(pslist) == 1000);
    it_pos = slist_end(pslist);
    slist_insert_range(pslist, it_pos, slist_begin(pslist_src), slist_end(pslist_src));
    assert_true(slist_size(pslist) == 1010);
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        if(i >= 1000)
        {
            assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
        }
        else
        {
            assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
        }
    }

    slist_destroy(pslist);
    slist_destroy(pslist_src);
}

/*
 * test slist_insert_after_range
 */
UT_CASE_DEFINATION(slist_insert_after_range)
void test_slist_insert_after_range__null_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init_n(pslist, 10);
    slist_init(pslist_src);

    expect_assert_failure(slist_insert_after_range(NULL, slist_begin(pslist), slist_begin(pslist_src), slist_end(pslist_src)));

    slist_destroy(pslist);
    slist_destroy(pslist_src);
}

void test_slist_insert_after_range__non_inited(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init_n(pslist, 10);
    slist_init(pslist_src);

    pslist->_t_typeinfo._t_style = 2323;
    expect_assert_failure(slist_insert_after_range(pslist, slist_begin(pslist), slist_begin(pslist_src), slist_end(pslist_src)));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
    slist_destroy(pslist_src);
}

void test_slist_insert_after_range__invalid_position(void** state)
{
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init(pslist_src);
    slist_init_n(pslist, 10);
    it_pos = slist_begin(pslist);
    it_pos._t_pos._pc_corepos = 0x8888;

    expect_assert_failure(slist_insert_after_range(pslist, it_pos, slist_begin(pslist_src), slist_end(pslist_src)));

    slist_destroy(pslist);
    slist_destroy(pslist_src);
}

void test_slist_insert_after_range__invalid_position_end(void** state)
{
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init(pslist_src);
    slist_init_n(pslist, 10);
    it_pos = slist_end(pslist);

    expect_assert_failure(slist_insert_after_range(pslist, it_pos, slist_begin(pslist_src), slist_end(pslist_src)));

    slist_destroy(pslist);
    slist_destroy(pslist_src);
}


void test_slist_insert_after_range__invalid_range(void** state)
{
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_iterator_t it_begin = _create_slist_iterator();
    slist_iterator_t it_end = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init_n(pslist_src, 10);
    slist_init_n(pslist, 10);
    it_pos = slist_begin(pslist);
    it_begin = slist_begin(pslist_src);
    it_end = slist_end(pslist_src);

    expect_assert_failure(slist_insert_after_range(pslist, it_pos, it_end, it_begin));

    slist_destroy(pslist);
    slist_destroy(pslist_src);
}

void test_slist_insert_after_range__invalid_range_not_same_type(void** state)
{
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_iterator_t it_begin = _create_slist_iterator();
    slist_iterator_t it_end = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(double);
    slist_init(pslist_src);
    slist_init_n(pslist, 10);
    it_pos = slist_begin(pslist);
    it_begin = slist_begin(pslist_src);
    it_end = slist_end(pslist_src);

    expect_assert_failure(slist_insert_after_range(pslist, it_pos, it_begin, it_end));

    slist_destroy(pslist);
    slist_destroy(pslist_src);
}

void test_slist_insert_after_range__invalid_range_belong_to_slist(void** state)
{
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_iterator_t it_begin = _create_slist_iterator();
    slist_iterator_t it_end = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init(pslist_src);
    slist_init_n(pslist, 10);
    it_pos = slist_begin(pslist);
    it_begin = slist_begin(pslist_src);
    it_end = slist_end(pslist_src);

    slist_insert_after_range(pslist, it_pos, it_pos, it_pos);

    slist_destroy(pslist);
    slist_destroy(pslist_src);
}

void test_slist_insert_after_range__begin_insert_0(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init_n(pslist, 1000);
    slist_init_elem(pslist_src, 0, 100);

    assert_true(slist_size(pslist) == 1000);
    it_pos = slist_begin(pslist);
    slist_insert_after_range(pslist, it_pos, slist_begin(pslist_src), slist_end(pslist_src));
    assert_true(slist_size(pslist) == 1000);
    for(it_iter = slist_begin(pslist);
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist);
    slist_destroy(pslist_src);
}

void test_slist_insert_after_range__begin_insert_10(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init_elem(pslist_src, 10, 100);
    slist_init_n(pslist, 1000);

    assert_true(slist_size(pslist) == 1000);
    it_pos = slist_begin(pslist);
    slist_insert_after_range(pslist, it_pos, slist_begin(pslist_src), slist_end(pslist_src));
    assert_true(slist_size(pslist) == 1010);
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        if(i > 0 && i < 11)
        {
            assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
        }
        else
        {
            assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
        }
    }

    slist_destroy(pslist);
    slist_destroy(pslist_src);
}

void test_slist_insert_after_range__middle_insert_0(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init_elem(pslist_src, 0, 100);
    slist_init_n(pslist, 1000);

    assert_true(slist_size(pslist) == 1000);
    it_pos = iterator_advance(slist_begin(pslist), 300);
    slist_insert_after_range(pslist, it_pos, slist_begin(pslist_src), slist_end(pslist_src));
    assert_true(slist_size(pslist) == 1000);
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist);
    slist_destroy(pslist_src);
}

void test_slist_insert_after_range__middle_insert_10(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init_elem(pslist_src, 10, 100);
    slist_init_n(pslist, 1000);

    assert_true(slist_size(pslist) == 1000);
    it_pos = iterator_advance(slist_begin(pslist), 300);
    slist_insert_after_range(pslist, it_pos, slist_begin(pslist_src), slist_end(pslist_src));
    assert_true(slist_size(pslist) == 1010);
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        if(i >= 301 && i < 311)
        {
            assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
        }
        else
        {
            assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
        }
    }

    slist_destroy(pslist);
    slist_destroy(pslist_src);
}

void test_slist_insert_after_range__end_insert_0(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init_elem(pslist_src, 0, 100);
    slist_init_n(pslist, 1000);

    assert_true(slist_size(pslist) == 1000);
    it_pos = slist_previous(pslist, slist_end(pslist));
    slist_insert_after_range(pslist, it_pos, slist_begin(pslist_src), slist_end(pslist_src));
    assert_true(slist_size(pslist) == 1000);
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist);
    slist_destroy(pslist_src);
}

void test_slist_insert_after_range__end_insert_10(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_init_elem(pslist_src, 10, 100);
    slist_init_n(pslist, 1000);

    assert_true(slist_size(pslist) == 1000);
    it_pos = slist_previous(pslist, slist_end(pslist));
    slist_insert_after_range(pslist, it_pos, slist_begin(pslist_src), slist_end(pslist_src));
    assert_true(slist_size(pslist) == 1010);
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        if(i >= 1000)
        {
            assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
        }
        else
        {
            assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
        }
    }

    slist_destroy(pslist);
    slist_destroy(pslist_src);
}

