#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/cdeque.h"
#include "cstl/cstring.h"
#include "cstl/clist.h"
#include "cstl/cset.h"
#include "cstl/chash_map.h"
#include "cstl/chash_set.h"
#include "cstl/cslist.h"
#include "cstl_deque_aux.h"
#include "cstl_vector_aux.h"

#include "ut_def.h"
#include "ut_cstl_deque.h"

UT_SUIT_DEFINATION(cstl_deque, deque_init)

/*
 * test deque_init
 */        
UT_CASE_DEFINATION(deque_init)
void test_deque_init__null_deque_container(void** state)
{
    expect_assert_failure(deque_init(NULL));
}

void test_deque_init__non_created_deque_container(void** state)
{
    deque_t deque;
    deque._t_mapsize = 848;
    expect_assert_failure(deque_init(&deque));
}

void test_deque_init__successfully(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_true(_deque_is_inited(pdeq));
    assert_true(deque_size(pdeq) == 0);

    deque_destroy(pdeq);
}

/*
 * test deque_init_n
 */
UT_CASE_DEFINATION(deque_init_n)
void test_deque_init_n__null_deque_container(void** state)
{
    expect_assert_failure(deque_init_n(NULL, 10));
}

void test_deque_init_n__non_created_deque_container(void** state)
{
    deque_t deque;
    deque._t_mapsize = 8494;
    expect_assert_failure(deque_init_n(&deque, 10));
}

void test_deque_init_n__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 0);
    assert_true(_deque_is_inited(pdeq));
    assert_true(deque_size(pdeq) == 0);
    assert_true(pdeq->_t_mapsize == 16);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(pdeq->_t_start) + 1 == _DEQUE_ITERATOR_MAP_POINTER(pdeq->_t_finish));
    assert_true(_DEQUE_ITERATOR_COREPOS(pdeq->_t_start) == _DEQUE_ITERATOR_AFTERLAST_POS(pdeq->_t_start));
    assert_true(_DEQUE_ITERATOR_COREPOS(pdeq->_t_finish) == _DEQUE_ITERATOR_FIRST_POS(pdeq->_t_finish));

    deque_destroy(pdeq);
}

void test_deque_init_n__c_builtin(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    assert_true(_deque_is_inited(pdeq));
    assert_true(deque_size(pdeq) == 10);
    assert_true(pdeq->_t_mapsize == 16);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(pdeq->_t_start) + 1 == _DEQUE_ITERATOR_MAP_POINTER(pdeq->_t_finish));
    assert_true(_DEQUE_ITERATOR_COREPOS(pdeq->_t_start) == _DEQUE_ITERATOR_AFTERLAST_POS(pdeq->_t_start));
    assert_true(_DEQUE_ITERATOR_COREPOS(pdeq->_t_finish) - 10 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_FIRST_POS(pdeq->_t_finish));
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    deque_destroy(pdeq);
}

void test_deque_init_n__cstr(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(char*);

    deque_init_n(pdeq, 10);
    assert_true(_deque_is_inited(pdeq));
    assert_true(deque_size(pdeq) == 10);
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    }

    deque_destroy(pdeq);
}

void test_deque_init_n__libcstl_builtin(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(vector_t<int>);

    deque_init_n(pdeq, 10);
    assert_true(_deque_is_inited(pdeq));
    assert_true(deque_size(pdeq) == 10);
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(_vector_is_inited((vector_t*)iterator_get_pointer(it_iter)));
        assert_true(vector_size((vector_t*)iterator_get_pointer(it_iter)) == 0);
    }

    deque_destroy(pdeq);
}

typedef struct _tag_test_deque_init_n__user_define
{
    int n_elem;
}_test_deque_init_n__user_define_t;
void test_deque_init_n__user_define(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq = NULL;

    type_register(_test_deque_init_n__user_define_t, NULL, NULL, NULL, NULL);
    pdeq = create_deque(_test_deque_init_n__user_define_t);

    deque_init_n(pdeq, 10);
    assert_true(_deque_is_inited(pdeq));
    assert_true(deque_size(pdeq) == 10);
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(((_test_deque_init_n__user_define_t*)iterator_get_pointer(it_iter))->n_elem == 0);
    }

    deque_destroy(pdeq);
}

void test_deque_init_n__one_chunk(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 16);
    assert_true(deque_size(pdeq) == 16);
    assert_true(pdeq->_t_mapsize == 16);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(pdeq->_t_start) + 2 == _DEQUE_ITERATOR_MAP_POINTER(pdeq->_t_finish));
    assert_true(_DEQUE_ITERATOR_COREPOS(pdeq->_t_start) == _DEQUE_ITERATOR_AFTERLAST_POS(pdeq->_t_start));
    assert_true(_DEQUE_ITERATOR_COREPOS(pdeq->_t_finish) == _DEQUE_ITERATOR_FIRST_POS(pdeq->_t_finish));
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    deque_destroy(pdeq);
}

void test_deque_init_n__more_than_one_chunk(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 19);
    assert_true(deque_size(pdeq) == 19);
    assert_true(pdeq->_t_mapsize == 16);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(pdeq->_t_start) + 2 == _DEQUE_ITERATOR_MAP_POINTER(pdeq->_t_finish));
    assert_true(_DEQUE_ITERATOR_COREPOS(pdeq->_t_start) == _DEQUE_ITERATOR_AFTERLAST_POS(pdeq->_t_start));
    assert_true(_DEQUE_ITERATOR_COREPOS(pdeq->_t_finish) - 3 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_FIRST_POS(pdeq->_t_finish));
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    deque_destroy(pdeq);
}

void test_deque_init_n__map_grow(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 260);
    assert_true(deque_size(pdeq) == 260);
    assert_true(pdeq->_t_mapsize == 24);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(pdeq->_t_start) + 17 == _DEQUE_ITERATOR_MAP_POINTER(pdeq->_t_finish));
    assert_true(_DEQUE_ITERATOR_COREPOS(pdeq->_t_start) == _DEQUE_ITERATOR_AFTERLAST_POS(pdeq->_t_start));
    assert_true(_DEQUE_ITERATOR_COREPOS(pdeq->_t_finish) - 4 * pdeq->_t_typeinfo._pt_type->_t_typesize ==
        _DEQUE_ITERATOR_FIRST_POS(pdeq->_t_finish));
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    deque_destroy(pdeq);
}

/*
 * test deque_init_copy
 */
UT_CASE_DEFINATION(deque_init_copy)
void test_deque_init_copy__null_dest_deque_container(void** state)
{
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);

    deque_init(pdeq_src);
    expect_assert_failure(deque_init_copy(NULL, pdeq_src));

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_init_copy__null_src_deque_container(void** state)
{
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);

    expect_assert_failure(deque_init_copy(pdeq_dest, NULL));

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_init_copy__non_created_dest_deque_container(void** state)
{
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);

    deque_init(pdeq_src);
    pdeq_dest->_t_mapsize = 99;
    expect_assert_failure(deque_init_copy(pdeq_dest, pdeq_src));

    pdeq_dest->_t_mapsize = 0;
    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_init_copy__non_inited_src_deque_container(void** state)
{
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);

    expect_assert_failure(deque_init_copy(pdeq_dest, pdeq_src));

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_init_copy__not_same_type(void** state)
{
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(double);

    deque_init(pdeq_src);
    expect_assert_failure(deque_init_copy(pdeq_dest, pdeq_src));

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_init_copy__init_copy_empty(void** state)
{
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);

    deque_init(pdeq_src);
    deque_init_copy(pdeq_dest, pdeq_src);
    assert_true(_deque_is_inited(pdeq_dest));
    assert_true(deque_size(pdeq_dest) == deque_size(pdeq_src));

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_init_copy__c_builtin(void** state)
{
    deque_iterator_t it_dest;
    deque_iterator_t it_src;
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);

    deque_init_elem(pdeq_src, 10, 100);
    deque_push_front(pdeq_src, 1943);
    deque_push_back(pdeq_src, 345);
    deque_init_copy(pdeq_dest, pdeq_src);
    assert_true(_deque_is_inited(pdeq_dest));
    assert_true(deque_size(pdeq_dest) == deque_size(pdeq_src));
    for(it_dest = deque_begin(pdeq_dest), it_src = deque_begin(pdeq_src);
        !iterator_equal(it_dest, deque_end(pdeq_dest)) && !iterator_equal(it_src, deque_end(pdeq_src));
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        assert_true(*(int*)iterator_get_pointer(it_dest) == *(int*)iterator_get_pointer(it_src));
    }

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_init_copy__cstr(void** state)
{
    deque_iterator_t it_dest;
    deque_iterator_t it_src;
    deque_t* pdeq_dest = create_deque(char*);
    deque_t* pdeq_src = create_deque(char*);

    deque_init_elem(pdeq_src, 10, "abcdefg");
    deque_push_front(pdeq_src, "222222");
    deque_push_back(pdeq_src, "aldjflakdjf");
    deque_init_copy(pdeq_dest, pdeq_src);
    assert_true(_deque_is_inited(pdeq_dest));
    assert_true(deque_size(pdeq_dest) == deque_size(pdeq_src));
    for(it_dest = deque_begin(pdeq_dest), it_src = deque_begin(pdeq_src);
        !iterator_equal(it_dest, deque_end(pdeq_dest)) && !iterator_equal(it_src, deque_end(pdeq_src));
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        assert_true(strcmp((char*)iterator_get_pointer(it_dest), (char*)iterator_get_pointer(it_src)) == 0);
    }

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_init_copy__libcstl_builtin(void** state)
{
    deque_iterator_t it_dest;
    deque_iterator_t it_src;
    deque_t* pdeq_dest = create_deque(deque_t<int>);
    deque_t* pdeq_src = create_deque(deque_t<signed>);

    deque_init_n(pdeq_src, 10);
    deque_init_copy(pdeq_dest, pdeq_src);
    assert_true(_deque_is_inited(pdeq_dest));
    assert_true(deque_size(pdeq_dest) == deque_size(pdeq_src));
    for(it_dest = deque_begin(pdeq_dest), it_src = deque_begin(pdeq_src);
        !iterator_equal(it_dest, deque_end(pdeq_dest)) && !iterator_equal(it_src, deque_end(pdeq_src));
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        assert_true(deque_equal((deque_t*)iterator_get_pointer(it_dest), (deque_t*)iterator_get_pointer(it_src)));
    }

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

typedef struct _tag_test_deque_init_copy__user_define
{
    int n_elem;
}_test_deque_init_copy__user_define_t;
void test_deque_init_copy__user_define(void** state)
{
    deque_iterator_t it_dest;
    deque_iterator_t it_src;
    deque_t* pdeq_dest = NULL;
    deque_t* pdeq_src = NULL;

    type_register(_test_deque_init_copy__user_define_t, NULL, NULL, NULL, NULL);
    type_duplicate(_test_deque_init_copy__user_define_t, struct _tag_test_deque_init_copy__user_define);
    pdeq_dest = create_deque(_test_deque_init_copy__user_define_t);
    pdeq_src = create_deque(struct _tag_test_deque_init_copy__user_define);

    deque_init_n(pdeq_src, 10);
    deque_init_copy(pdeq_dest, pdeq_src);
    assert_true(_deque_is_inited(pdeq_dest));
    assert_true(deque_size(pdeq_dest) == deque_size(pdeq_src));
    for(it_dest = deque_begin(pdeq_dest), it_src = deque_begin(pdeq_src);
        !iterator_equal(it_dest, deque_end(pdeq_dest)) && !iterator_equal(it_src, deque_end(pdeq_src));
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        assert_true(((_test_deque_init_copy__user_define_t*)iterator_get_pointer(it_dest))->n_elem ==
            ((_test_deque_init_copy__user_define_t*)iterator_get_pointer(it_src))->n_elem);
    }

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

/*
 * test deque_init_copy_range
 */
UT_CASE_DEFINATION(deque_init_copy_range)
void test_deque_init_copy_range__null_deque_container(void** state)
{
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);

    deque_init(pdeq_src);
    expect_assert_failure(deque_init_copy_range(NULL, deque_begin(pdeq_src), deque_end(pdeq_src)));

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_init_copy_range__non_created_deque_container(void** state)
{
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);

    deque_init(pdeq_src);
    pdeq_dest->_t_mapsize = 999;
    expect_assert_failure(deque_init_copy_range(pdeq_dest, deque_begin(pdeq_src), deque_end(pdeq_src)));

    pdeq_dest->_t_mapsize = 0;
    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_init_copy_range__invalid_range(void** state)
{
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);

    deque_init_n(pdeq_src, 10);
    it_begin = deque_begin(pdeq_src);
    it_end = deque_end(pdeq_src);
    expect_assert_failure(deque_init_copy_range(pdeq_dest, it_end, it_begin));

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_init_copy_range__not_same(void** state)
{
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(double);

    deque_init_n(pdeq_src, 10);
    it_begin = deque_begin(pdeq_src);
    it_end = deque_end(pdeq_src);
    expect_assert_failure(deque_init_copy_range(pdeq_dest, it_begin, it_end));

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_init_copy_range__init_copy_range_empty(void** state)
{
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);

    deque_init(pdeq_src);
    deque_init_copy_range(pdeq_dest, deque_begin(pdeq_src), deque_end(pdeq_src));
    assert_true(_deque_is_inited(pdeq_dest));
    assert_true(deque_size(pdeq_dest) == 0);

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_init_copy_range__c_builtin(void** state)
{
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_iterator_t it_dest;
    deque_iterator_t it_src;
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);

    deque_init_elem(pdeq_src, 10, 100);
    deque_push_front(pdeq_src, 1943);
    deque_push_back(pdeq_src, 345);
    it_begin = deque_begin(pdeq_src);
    it_end = iterator_advance(it_begin, 3);
    deque_init_copy_range(pdeq_dest, it_begin, it_end);
    assert_true(_deque_is_inited(pdeq_dest));
    assert_true(deque_size(pdeq_dest) == 3);
    for(it_dest = deque_begin(pdeq_dest), it_src = it_begin;
        !iterator_equal(it_dest, deque_end(pdeq_dest)) && !iterator_equal(it_src, it_end);
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        assert_true(*(int*)iterator_get_pointer(it_dest) == *(int*)iterator_get_pointer(it_src));
    }

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_init_copy_range__cstr(void** state)
{
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_iterator_t it_dest;
    deque_iterator_t it_src;
    deque_t* pdeq_dest = create_deque(char*);
    deque_t* pdeq_src = create_deque(char*);

    deque_init_elem(pdeq_src, 10, "abcdefg");
    deque_push_front(pdeq_src, "222222");
    deque_push_back(pdeq_src, "aldjflakdjf");
    it_begin = iterator_advance(deque_begin(pdeq_src), 3);
    it_end = iterator_advance(it_begin, 3);
    deque_init_copy_range(pdeq_dest, it_begin, it_end);
    assert_true(_deque_is_inited(pdeq_dest));
    assert_true(deque_size(pdeq_dest) == 3);
    for(it_dest = deque_begin(pdeq_dest), it_src = it_begin;
        !iterator_equal(it_dest, deque_end(pdeq_dest)) && !iterator_equal(it_src, it_end);
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        assert_true(strcmp((char*)iterator_get_pointer(it_dest), (char*)iterator_get_pointer(it_src)) == 0);
    }

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_init_copy_range__libcstl_builtin(void** state)
{
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_iterator_t it_dest;
    deque_iterator_t it_src;
    deque_t* pdeq_dest = create_deque(deque_t<int>);
    deque_t* pdeq_src = create_deque(deque_t<signed>);

    deque_init_n(pdeq_src, 10);
    it_begin = iterator_advance(deque_begin(pdeq_src), 3);
    it_end = deque_end(pdeq_src);
    deque_init_copy_range(pdeq_dest, it_begin, it_end);
    assert_true(_deque_is_inited(pdeq_dest));
    assert_true(deque_size(pdeq_dest) == 7);
    for(it_dest = deque_begin(pdeq_dest), it_src = it_begin;
        !iterator_equal(it_dest, deque_end(pdeq_dest)) && !iterator_equal(it_src, it_end);
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        assert_true(deque_equal((deque_t*)iterator_get_pointer(it_dest), (deque_t*)iterator_get_pointer(it_src)));
    }

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

typedef struct _tag_test_deque_init_copy_range__user_define
{
    int n_elem;
}_test_deque_init_copy_range__user_define_t;
void test_deque_init_copy_range__user_define(void** state)
{
    deque_iterator_t it_dest;
    deque_iterator_t it_src;
    deque_t* pdeq_dest = NULL;
    deque_t* pdeq_src = NULL;

    type_register(_test_deque_init_copy_range__user_define_t, NULL, NULL, NULL, NULL);
    type_duplicate(_test_deque_init_copy_range__user_define_t, struct _tag_test_deque_init_copy_range__user_define);
    pdeq_dest = create_deque(_test_deque_init_copy_range__user_define_t);
    pdeq_src = create_deque(struct _tag_test_deque_init_copy_range__user_define);

    deque_init_n(pdeq_src, 10);
    deque_init_copy_range(pdeq_dest, deque_begin(pdeq_src), deque_end(pdeq_src));
    assert_true(_deque_is_inited(pdeq_dest));
    assert_true(deque_size(pdeq_dest) == deque_size(pdeq_src));
    for(it_dest = deque_begin(pdeq_dest), it_src = deque_begin(pdeq_src);
        !iterator_equal(it_dest, deque_end(pdeq_dest)) && !iterator_equal(it_src, deque_end(pdeq_src));
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        assert_true(((_test_deque_init_copy_range__user_define_t*)iterator_get_pointer(it_dest))->n_elem ==
            ((_test_deque_init_copy_range__user_define_t*)iterator_get_pointer(it_src))->n_elem);
    }

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_init_copy_range__other_container_range(void** state)
{
    deque_t* pdeq = create_deque(int);
    list_t* plist = create_list(int);
    iterator_t it_iter;
    int i = 0;

    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    deque_init_copy_range(pdeq, list_begin(plist), list_end(plist));
    assert_true(_deque_is_inited(pdeq));
    for(it_iter = deque_begin(pdeq), i = 0;
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == i);
    }

    deque_destroy(pdeq);
    list_destroy(plist);
}

void test_deque_init_copy_range__other_container_range_1(void** state)
{
    deque_t* pdeq = create_deque(hash_map_t<char*, slist_t<double>>);
    multiset_t* pmset = create_multiset(hash_map_t<char*, slist_t<double>>);
    hash_map_t* phmap = create_hash_map(char*, slist_t<double>);
    pair_t* ppair = create_pair(char*, slist_t<double>);
    slist_t* pslist = create_slist(double);
    iterator_t it_deq, it_mset;

    multiset_init(pmset);
    hash_map_init(phmap);
    pair_init(ppair);
    slist_init(pslist);

    slist_assign_elem((slist_t*)hash_map_at(phmap, "abc"), 4, 2.2);
    multiset_insert(pmset, phmap);
    slist_assign_elem((slist_t*)hash_map_at(phmap, "def"), 2, 3.552);
    multiset_insert(pmset, phmap);
    slist_assign_elem((slist_t*)hash_map_at(phmap, "ghi"), 9, -0.93);
    multiset_insert(pmset, phmap);
    slist_assign_elem((slist_t*)hash_map_at(phmap, "jkl"), 100, 591.03);
    multiset_insert(pmset, phmap);
    slist_assign_elem((slist_t*)hash_map_at(phmap, "mno"), 5, 10.0);
    multiset_insert(pmset, phmap);

    deque_init_copy_range(pdeq, multiset_begin(pmset), multiset_end(pmset));
    assert_true(_deque_is_inited(pdeq));
    for(it_deq = deque_begin(pdeq), it_mset = multiset_begin(pmset);
        !iterator_equal(it_deq, deque_end(pdeq)) && !iterator_equal(it_mset, multiset_end(pmset));
        it_deq = iterator_next(it_deq), it_mset = iterator_next(it_mset))
    {
        assert_true(hash_map_equal((hash_map_t*)iterator_get_pointer(it_deq), (hash_map_t*)iterator_get_pointer(it_mset)));
    }

    deque_destroy(pdeq);
    multiset_destroy(pmset);
    hash_map_destroy(phmap);
    pair_destroy(ppair);
    slist_destroy(pslist);
}

/*
 * test deque_init_copy_array
 */
UT_CASE_DEFINATION(deque_init_copy_array)
void test_deque_init_copy_array__null_deque_container(void** state)
{
    int an_array[10] = {0};
    expect_assert_failure(deque_init_copy_array(NULL, an_array, 10));
}

void test_deque_init_copy_array__non_created_deque_container(void** state)
{
    int an_array[10] = {0};
    deque_t* pdeq_dest = create_deque(int);

    pdeq_dest->_t_mapsize = 999;
    expect_assert_failure(deque_init_copy_array(pdeq_dest, an_array, 10));

    pdeq_dest->_t_mapsize = 0;
    deque_destroy(pdeq_dest);
}

void test_deque_init_copy_array__null_array(void** state)
{
    deque_t* pdeq_dest = create_deque(int);

    expect_assert_failure(deque_init_copy_array(pdeq_dest, NULL, 10));

    deque_destroy(pdeq_dest);
}

void test_deque_init_copy_array__init_copy_array_empty(void** state)
{
    int an_array[10] = {0};
    deque_t* pdeq_dest = create_deque(int);

    deque_init_copy_array(pdeq_dest, an_array, 0);
    assert_true(_deque_is_inited(pdeq_dest));
    assert_true(deque_size(pdeq_dest) == 0);

    deque_destroy(pdeq_dest);
}

void test_deque_init_copy_array__c_builtin(void** state)
{
    int an_array[10];
    int i = 0;
    deque_t* pdeq_dest = create_deque(int);
    deque_iterator_t it_dest;

    for (i = 0; i < 10; ++i) {
        an_array[i] = i;
    }
    deque_init_copy_array(pdeq_dest, an_array, 10);
    assert_true(_deque_is_inited(pdeq_dest));
    assert_true(deque_size(pdeq_dest) == 10);
    for(it_dest = deque_begin(pdeq_dest), i = 0;
        !iterator_equal(it_dest, deque_end(pdeq_dest)) && i < 10;
        it_dest = iterator_next(it_dest), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_dest) == i);
    }

    deque_destroy(pdeq_dest);
}

void test_deque_init_copy_array__cstr(void** state)
{
    char* as_array[] = {
        "Windows",
        "Linux",
        "Mac"
    };
    int i = 0;
    deque_t* pdeq_dest = create_deque(char*);
    deque_iterator_t it_dest;

    deque_init_copy_array(pdeq_dest, as_array, 3);
    assert_true(_deque_is_inited(pdeq_dest));
    assert_true(deque_size(pdeq_dest) == 3);
    for(it_dest = deque_begin(pdeq_dest), i = 0;
        !iterator_equal(it_dest, deque_end(pdeq_dest)) && i < 3;
        it_dest = iterator_next(it_dest), ++i)
    {
        assert_true(strcmp((char*)iterator_get_pointer(it_dest), as_array[i]) == 0);
    }

    deque_destroy(pdeq_dest);
}

void test_deque_init_copy_array__libcstl_builtin(void** state)
{
    int i = 0;
    deque_t* adeq_array[10] = {NULL};
    deque_t* pdeq_dest = create_deque(deque_t<int>);
    deque_iterator_t it_dest;

    for (i = 0; i < 10; ++i) {
        adeq_array[i] = create_deque(int);
        deque_init_elem(adeq_array[i], i, i);
    }
    deque_init_copy_array(pdeq_dest, adeq_array, 10);
    assert_true(_deque_is_inited(pdeq_dest));
    assert_true(deque_size(pdeq_dest) == 10);
    for(it_dest = deque_begin(pdeq_dest), i = 0;
        !iterator_equal(it_dest, deque_end(pdeq_dest)) && i < 10;
        it_dest = iterator_next(it_dest), ++i)
    {
        assert_true(deque_equal((deque_t*)iterator_get_pointer(it_dest), adeq_array[i]));
    }

    deque_destroy(pdeq_dest);
    for (i = 0; i < 10; ++i) {
        deque_destroy(adeq_array[i]);
    }
}

typedef struct _tag_test_deque_init_copy_array__user_define
{
    int n_elem;
}_test_deque_init_copy_array__user_define_t;
void test_deque_init_copy_array__user_define(void** state)
{
    int i = 0;
    _test_deque_init_copy_array__user_define_t* at_array[10] = {NULL};
    deque_t* pdeq_dest = NULL;
    deque_iterator_t it_dest;

    type_register(_test_deque_init_copy_array__user_define_t, NULL, NULL, NULL, NULL);
    type_duplicate(_test_deque_init_copy_array__user_define_t, struct _tag_test_deque_init_copy_array__user_define);
    pdeq_dest = create_deque(_test_deque_init_copy_array__user_define_t);

    for (i = 0; i < 10; ++i) {
        at_array[i] = malloc(sizeof(_test_deque_init_copy_array__user_define_t));
        at_array[i]->n_elem = i;
    }
    deque_init_copy_array(pdeq_dest, at_array, 10);
    assert_true(_deque_is_inited(pdeq_dest));
    assert_true(deque_size(pdeq_dest) == 10);
    for(it_dest = deque_begin(pdeq_dest), i = 0;
        !iterator_equal(it_dest, deque_end(pdeq_dest)) && i < 10;
        it_dest = iterator_next(it_dest), ++i)
    {
        assert_true(((_test_deque_init_copy_array__user_define_t*)iterator_get_pointer(it_dest))->n_elem ==
            at_array[i]->n_elem);
    }

    deque_destroy(pdeq_dest);
    for (i = 0; i < 10; ++i) {
        free(at_array[i]);
    }
}

void test_deque_init_copy_array__other_container_array_1(void** state)
{
    int i = 0;
    hash_map_t* ahmap_array[10] = {NULL};
    deque_t* pdeq = create_deque(hash_map_t<char*, slist_t<double>>);
    deque_iterator_t it_deq;

    for (i = 0; i < 10; ++i) {
        ahmap_array[i] = create_hash_map(char*, slist_t<double>);
        hash_map_init(ahmap_array[i]);
        slist_assign_elem((slist_t*)hash_map_at(ahmap_array[i], "abc"), 4, 2.2);
    }

    deque_init_copy_array(pdeq, ahmap_array, 10);
    assert_true(_deque_is_inited(pdeq));
    for(it_deq = deque_begin(pdeq), i = 0;
        !iterator_equal(it_deq, deque_end(pdeq)) && i < 10;
        it_deq = iterator_next(it_deq), ++i)
    {
        assert_true(hash_map_equal((hash_map_t*)iterator_get_pointer(it_deq), ahmap_array[i]));
    }

    deque_destroy(pdeq);
    for (i = 0; i < 10; ++i) {
        hash_map_destroy(ahmap_array[i]);
    }
}

/*
 * test deque_destroy
 */
UT_CASE_DEFINATION(deque_destroy)
void test_deque_destroy__null_deque_container(void** state)
{
    expect_assert_failure(deque_destroy(NULL));
}

void test_deque_destroy__non_created_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);

    pdeq->_t_mapsize = 993;
    expect_assert_failure(deque_destroy(pdeq));

    pdeq->_t_mapsize = 0;
    deque_destroy(pdeq);
}

void test_deque_destroy__created_non_inited(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_destroy(pdeq);
}

void test_deque_destroy__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    deque_destroy(pdeq);
}

void test_deque_destroy__non_empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    deque_destroy(pdeq);
}

/*
 * test deque_size
 */
UT_CASE_DEFINATION(deque_size)
void test_deque_size__null_deque_container(void** state)
{
    expect_assert_failure(deque_size(NULL));
}

void test_deque_size__non_inited_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);

    expect_assert_failure(deque_size(pdeq));

    deque_destroy(pdeq);
}

void test_deque_size__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_true(deque_size(pdeq) == 0);

    deque_destroy(pdeq);
}

void test_deque_size__non_empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    assert_true(deque_size(pdeq) == 10);

    deque_destroy(pdeq);
}

/*
 * test deque_empty
 */
UT_CASE_DEFINATION(deque_empty)
void test_deque_empty__null_deque_container(void** state)
{
    expect_assert_failure(deque_empty(NULL));
}

void test_deque_empty__non_inited_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);

    expect_assert_failure(deque_empty(pdeq));

    deque_destroy(pdeq);
}

void test_deque_empty__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_true(deque_empty(pdeq));

    deque_destroy(pdeq);
}

void test_deque_empty__non_empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    assert_false(deque_empty(pdeq));

    deque_destroy(pdeq);
}

/*
 * test deque_max_size
 */
UT_CASE_DEFINATION(deque_max_size)
void test_deque_max_size__null_deque_container(void** state)
{
    expect_assert_failure(deque_max_size(NULL));
}

void test_deque_max_size__non_inited_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);

    expect_assert_failure(deque_max_size(pdeq));

    deque_destroy(pdeq);
}

void test_deque_max_size__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    assert_true(deque_max_size(pdeq) != 0);

    deque_destroy(pdeq);
}

void test_deque_max_size__non_empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    assert_true(deque_max_size(pdeq) != 0);

    deque_destroy(pdeq);
}

/*
 * test deque_begin
 */
UT_CASE_DEFINATION(deque_begin)
void test_deque_begin__null_deque_container(void** state)
{
    expect_assert_failure(deque_begin(NULL));
}

void test_deque_begin__non_inited_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);

    expect_assert_failure(deque_begin(pdeq));

    deque_destroy(pdeq);
}

void test_deque_begin__empty(void** state)
{
    deque_iterator_t it_begin;
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    it_begin = deque_begin(pdeq);
    assert_true(_deque_iterator_belong_to_deque(pdeq, it_begin));
    assert_true(iterator_equal(it_begin, pdeq->_t_start));
    assert_true(iterator_equal(it_begin, deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test_deque_begin__non_empty(void** state)
{
    deque_iterator_t it_begin;
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);
    deque_push_back(pdeq, 123);
    deque_push_back(pdeq, 209);
    deque_push_back(pdeq, 3);

    it_begin = deque_begin(pdeq);
    assert_true(_deque_iterator_belong_to_deque(pdeq, it_begin));
    assert_true(iterator_equal(it_begin, pdeq->_t_start));
    assert_true(*(int*)iterator_get_pointer(it_begin) == 123);

    deque_destroy(pdeq);
}

/*
 * test deque_end
 */
UT_CASE_DEFINATION(deque_end)
void test_deque_end__null_deque_container(void** state)
{
    expect_assert_failure(deque_end(NULL));
}

void test_deque_end__non_inited_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);

    expect_assert_failure(deque_end(pdeq));

    deque_destroy(pdeq);
}

void test_deque_end__empty(void** state)
{
    deque_iterator_t it_end;
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    it_end = deque_end(pdeq);
    assert_true(_deque_iterator_belong_to_deque(pdeq, it_end));
    assert_true(iterator_equal(it_end, pdeq->_t_finish));
    assert_true(iterator_equal(it_end, deque_begin(pdeq)));

    deque_destroy(pdeq);
}

void test_deque_end__non_empty(void** state)
{
    deque_iterator_t it_end;
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);
    deque_push_back(pdeq, 123);
    deque_push_back(pdeq, 209);
    deque_push_back(pdeq, 3);

    it_end = deque_end(pdeq);
    assert_true(_deque_iterator_belong_to_deque(pdeq, it_end));
    assert_true(iterator_equal(it_end, pdeq->_t_finish));

    deque_destroy(pdeq);
}

/*
 * test deque_assign
 */
UT_CASE_DEFINATION(deque_assign)
void test_deque_assign__null_dest(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    expect_assert_failure(deque_assign(NULL, pdeq));

    deque_destroy(pdeq);
}

void test_deque_assign__null_src(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    expect_assert_failure(deque_assign(pdeq, NULL));

    deque_destroy(pdeq);
}

void test_deque_assign__non_inited_dest(void** state)
{
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);

    deque_init(pdeq_src);

    expect_assert_failure(deque_assign(pdeq_dest, pdeq_src));

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_assign__non_inited_src(void** state)
{
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);

    deque_init(pdeq_dest);

    expect_assert_failure(deque_assign(pdeq_dest, pdeq_src));

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_assign__not_same_type(void** state)
{
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(double);

    deque_init(pdeq_dest);
    deque_init(pdeq_src);

    expect_assert_failure(deque_assign(pdeq_dest, pdeq_src));

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_assign__same_container(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);

    deque_assign(pdeq, pdeq);
    assert_true(deque_size(pdeq) == 0);

    deque_destroy(pdeq);
}

void test_deque_assign__0_assign_0(void** state)
{
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);

    deque_init(pdeq_dest);
    deque_init(pdeq_src);

    deque_assign(pdeq_dest, pdeq_src);
    assert_true(deque_size(pdeq_dest) == 0);
    assert_true(deque_equal(pdeq_dest, pdeq_src));

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_assign__0_assign_10(void** state)
{
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);

    deque_init(pdeq_dest);
    deque_init_n(pdeq_src, 10);

    deque_assign(pdeq_dest, pdeq_src);
    assert_true(deque_size(pdeq_dest) == 10);
    assert_true(deque_equal(pdeq_dest, pdeq_src));

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_assign__10_assign_0(void** state)
{
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);

    deque_init_n(pdeq_dest, 10);
    deque_init(pdeq_src);

    deque_assign(pdeq_dest, pdeq_src);
    assert_true(deque_equal(pdeq_dest, pdeq_src));
    assert_true(deque_size(pdeq_dest) == 0);

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_assign__10_assign_10_deque_equal(void** state)
{
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);

    deque_init_n(pdeq_dest, 10);
    deque_init_n(pdeq_src, 10);

    deque_assign(pdeq_dest, pdeq_src);
    assert_true(deque_equal(pdeq_dest, pdeq_src));

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_assign__10_assign_10_deque_not_equal(void** state)
{
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);

    deque_init_elem(pdeq_dest, 10, 100);
    deque_init_n(pdeq_src, 10);

    deque_assign(pdeq_dest, pdeq_src);
    assert_true(deque_equal(pdeq_dest, pdeq_src));
    assert_true(deque_size(pdeq_dest) == 10);

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_assign__10_assign_1000(void** state)
{
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);

    deque_init_elem(pdeq_dest, 10, 100);
    deque_init_n(pdeq_src, 1000);

    deque_assign(pdeq_dest, pdeq_src);
    assert_true(deque_equal(pdeq_dest, pdeq_src));
    assert_true(deque_size(pdeq_dest) == 1000);

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

/*
 * test deque_assign_range
 */
UT_CASE_DEFINATION(deque_assign_range)
void test_deque_assign_range__null_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    expect_assert_failure(deque_assign_range(NULL, deque_begin(pdeq), deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test_deque_assign_range__non_inited(void** state)
{
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);
    deque_init(pdeq_src);

    expect_assert_failure(deque_assign_range(pdeq_dest, deque_begin(pdeq_src), deque_end(pdeq_src)));

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_assign_range__invalid_it_begin(void** state)
{
    deque_iterator_t it_begin;
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);
    deque_init(pdeq_src);
    deque_init(pdeq_dest);
    it_begin._t_iteratortype = 284;

    expect_assert_failure(deque_assign_range(pdeq_dest, it_begin, deque_end(pdeq_src)));

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_assign_range__invalid_it_end(void** state)
{
    deque_iterator_t it_end;
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);
    deque_init(pdeq_src);
    deque_init(pdeq_dest);
    it_end._t_iteratortype = 284;

    expect_assert_failure(deque_assign_range(pdeq_dest, deque_begin(pdeq_src), it_end));

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_assign_range__invalid_range(void** state)
{
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);
    deque_init_n(pdeq_src, 12);
    deque_init(pdeq_dest);

    expect_assert_failure(deque_assign_range(pdeq_dest, deque_end(pdeq_src), deque_begin(pdeq_src)));

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_assign_range__invalid_range_not_same_type(void** state)
{
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(double);
    deque_init_n(pdeq_src, 12);
    deque_init(pdeq_dest);

    expect_assert_failure(deque_assign_range(pdeq_dest, deque_begin(pdeq_src), deque_end(pdeq_src)));

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_assign_range__range_belong_to_deque(void** state)
{
    deque_t* pdeq_dest = create_deque(int);
    deque_init(pdeq_dest);

    deque_assign_range(pdeq_dest, deque_begin(pdeq_dest), deque_end(pdeq_dest));

    deque_destroy(pdeq_dest);
}

void test_deque_assign_range__0_assign_range_0(void** state)
{
    size_t i = 0;
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);
    deque_init_elem(pdeq_src, 1200, 100);
    deque_init(pdeq_dest);

    it_begin = deque_begin(pdeq_src);
    it_end = deque_begin(pdeq_src);
    deque_assign_range(pdeq_dest, it_begin, it_end);
    assert_true(deque_size(pdeq_dest) == iterator_distance(it_begin, it_end));
    assert_true(deque_size(pdeq_dest) == 0);

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_assign_range__0_assign_range_10(void** state)
{
    deque_iterator_t it_iter;
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);
    deque_init_elem(pdeq_src, 1200, 100);
    deque_init(pdeq_dest);

    it_begin = deque_begin(pdeq_src);
    it_end = iterator_advance(it_begin, 10);
    deque_assign_range(pdeq_dest, it_begin, it_end);
    assert_true(deque_size(pdeq_dest) == iterator_distance(it_begin, it_end));
    assert_true(deque_size(pdeq_dest) == 10);
    for(it_iter = deque_begin(pdeq_dest);
        !iterator_equal(it_iter, deque_end(pdeq_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_assign_range__10_assign_range_0(void** state)
{
    deque_iterator_t it_iter;
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);
    deque_init_elem(pdeq_src, 1200, 100);
    deque_init_elem(pdeq_dest, 10, 700);

    it_begin = iterator_advance(deque_begin(pdeq_src), 111);
    it_end = it_begin;
    deque_assign_range(pdeq_dest, it_begin, it_end);
    assert_true(deque_size(pdeq_dest) == iterator_distance(it_begin, it_end));
    assert_true(deque_size(pdeq_dest) == 0);
    for(it_iter = deque_begin(pdeq_dest);
        !iterator_equal(it_iter, deque_end(pdeq_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_assign_range__10_assign_range_10_same_elem(void** state)
{
    deque_iterator_t it_iter;
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);
    deque_init_elem(pdeq_src, 1200, 100);
    deque_init_elem(pdeq_dest, 10, 100);

    it_begin = iterator_advance(deque_begin(pdeq_src), 111);
    it_end = iterator_advance(it_begin, 10);
    deque_assign_range(pdeq_dest, it_begin, it_end);
    assert_true(deque_size(pdeq_dest) == iterator_distance(it_begin, it_end));
    assert_true(deque_size(pdeq_dest) == 10);
    for(it_iter = deque_begin(pdeq_dest);
        !iterator_equal(it_iter, deque_end(pdeq_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_assign_range__10_assign_range_10_not_same_elem(void** state)
{
    deque_iterator_t it_iter;
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);
    deque_init_elem(pdeq_src, 1200, 100);
    deque_init_elem(pdeq_dest, 10, 0);

    it_begin = iterator_advance(deque_begin(pdeq_src), 111);
    it_end = iterator_advance(it_begin, 10);
    deque_assign_range(pdeq_dest, it_begin, it_end);
    assert_true(deque_size(pdeq_dest) == iterator_distance(it_begin, it_end));
    assert_true(deque_size(pdeq_dest) == 10);
    for(it_iter = deque_begin(pdeq_dest);
        !iterator_equal(it_iter, deque_end(pdeq_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_assign_range__10_assign_range_1000(void** state)
{
    deque_iterator_t it_iter;
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);
    deque_init_elem(pdeq_src, 1200, 100);
    deque_init_elem(pdeq_dest, 10, 0);

    it_begin = iterator_advance(deque_begin(pdeq_src), 111);
    it_end = iterator_advance(it_begin, 1000);
    deque_assign_range(pdeq_dest, it_begin, it_end);
    assert_true(deque_size(pdeq_dest) == iterator_distance(it_begin, it_end));
    assert_true(deque_size(pdeq_dest) == 1000);
    for(it_iter = deque_begin(pdeq_dest);
        !iterator_equal(it_iter, deque_end(pdeq_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_assign_range__other_container_range(void** state)
{
    deque_t* pdeq = create_deque(list_t<int>);
    hash_set_t* phset = create_hash_set(list_t<int>);
    list_t* plist = create_list(int);
    int i = 0;

    deque_init(pdeq);
    hash_set_init(phset);
    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, plist);
    }

    list_clear(plist);
    for(i = 0; i < 100; ++i)
    {
        list_push_front(plist, i);
        hash_set_insert(phset, plist);
    }

    assert_true(deque_size(pdeq) == 10);
    assert_true(hash_set_size(phset) == 100);
    deque_assign_range(pdeq, hash_set_begin(phset), hash_set_end(phset));
    assert_true(deque_size(pdeq) == 100);

    deque_destroy(pdeq);
    hash_set_destroy(phset);
    list_destroy(plist);
}

void test_deque_assign_range__other_container_range1(void** state)
{
    deque_t* pdeq = create_deque(float);
    vector_t* pvec = create_vector(float);
    size_t i = 0;
    
    deque_init_elem(pdeq, 45, 9.04f);
    vector_init_elem(pvec, 10, -145.4f);

    assert_true(deque_size(pdeq) == 45);
    assert_true(vector_size(pvec) == 10);
    deque_assign_range(pdeq, vector_begin(pvec), vector_end(pvec));
    assert_true(deque_size(pdeq) == 10);
    for(i = 0; i < deque_size(pdeq); ++i)
    {
        assert_true(*(float*)deque_at(pdeq, i) == -145.4f);
    }

    deque_destroy(pdeq);
    vector_destroy(pvec);
}

/*
 * test deque_assign_array
 */
UT_CASE_DEFINATION(deque_assign_array)
void test_deque_assign_array__null_deque_container(void** state)
{
    int an_array[10] = {0};
    expect_assert_failure(deque_assign_array(NULL, an_array, 10));
}

void test_deque_assign_array__non_inited(void** state)
{
    deque_t* pdeq_dest = create_deque(int);
    int an_array[10] = {0};

    expect_assert_failure(deque_assign_array(pdeq_dest, an_array, 10));

    deque_destroy(pdeq_dest);
}

void test_deque_assign_array__null_array(void** state)
{
    deque_t* pdeq_dest = create_deque(int);
    deque_init(pdeq_dest);

    expect_assert_failure(deque_assign_array(pdeq_dest, NULL, 10));

    deque_destroy(pdeq_dest);
}

void test_deque_assign_array__0_assign_array_0(void** state)
{
    int an_array[10] = {0};
    deque_t* pdeq_dest = create_deque(int);
    deque_init(pdeq_dest);

    deque_assign_array(pdeq_dest, an_array, 0);
    assert_true(deque_size(pdeq_dest) == 0);

    deque_destroy(pdeq_dest);
}

void test_deque_assign_array__0_assign_array_10(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq_dest = create_deque(int);
    int an_array[10] = {0};
    int i = 0;
    deque_init(pdeq_dest);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    deque_assign_array(pdeq_dest, an_array, 10);
    assert_true(deque_size(pdeq_dest) == 10);
    for(it_iter = deque_begin(pdeq_dest);
        !iterator_equal(it_iter, deque_end(pdeq_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    deque_destroy(pdeq_dest);
}

void test_deque_assign_array__10_assign_array_0(void** state)
{
    int an_array[10] = {0};
    int i = 0;
    deque_iterator_t it_iter;
    deque_t* pdeq_dest = create_deque(int);
    deque_init_elem(pdeq_dest, 10, 700);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    deque_assign_array(pdeq_dest, an_array, 0);
    assert_true(deque_size(pdeq_dest) == 0);
    for(it_iter = deque_begin(pdeq_dest);
        !iterator_equal(it_iter, deque_end(pdeq_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    deque_destroy(pdeq_dest);
}

void test_deque_assign_array__10_assign_array_10_same_elem(void** state)
{
    int an_array[100] = {0};
    int i = 0;
    deque_iterator_t it_iter;
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);
    deque_init_elem(pdeq_dest, 10, 100);

    for (i = 0; i < 100; ++i) {
        an_array[i] = 100;
    }
    deque_assign_array(pdeq_dest, an_array, 10);
    assert_true(deque_size(pdeq_dest) == 10);
    for(it_iter = deque_begin(pdeq_dest);
        !iterator_equal(it_iter, deque_end(pdeq_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_assign_array__10_assign_array_10_not_same_elem(void** state)
{
    int an_array[100] = {0};
    int i = 0;
    deque_iterator_t it_iter;
    deque_t* pdeq_dest = create_deque(int);
    deque_t* pdeq_src = create_deque(int);
    deque_init_elem(pdeq_dest, 10, 0);

    for (i = 0; i < 100; ++i) {
        an_array[i] = 100;
    }
    deque_assign_array(pdeq_dest, an_array, 10);
    assert_true(deque_size(pdeq_dest) == 10);
    for(it_iter = deque_begin(pdeq_dest);
        !iterator_equal(it_iter, deque_end(pdeq_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    deque_destroy(pdeq_dest);
    deque_destroy(pdeq_src);
}

void test_deque_assign_array__10_assign_array_1000(void** state)
{
    int an_array[1024] = {0};
    int i = 0;
    deque_iterator_t it_iter;
    deque_t* pdeq_dest = create_deque(int);
    deque_init_elem(pdeq_dest, 10, 0);

    for (i = 0; i < 1024; ++i) {
        an_array[i] = 100;
    }
    deque_assign_array(pdeq_dest, an_array, 1000);
    assert_true(deque_size(pdeq_dest) == 1000);
    for(it_iter = deque_begin(pdeq_dest);
        !iterator_equal(it_iter, deque_end(pdeq_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    deque_destroy(pdeq_dest);
}

void test_deque_assign_array__other_container_array(void** state)
{
    list_t* aplist_array[100] = {NULL};
    deque_t* pdeq = create_deque(list_t<int>);
    list_t* plist = create_list(int);
    deque_iterator_t it_iter;
    int i = 0;

    deque_init(pdeq);
    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, plist);
    }

    for (i = 0; i < 100; ++i) {
        aplist_array[i] = create_list(int);
        list_init_elem(aplist_array[i], i, i);
    }

    assert_true(deque_size(pdeq) == 10);
    deque_assign_array(pdeq, aplist_array, 100);
    assert_true(deque_size(pdeq) == 100);
    for (it_iter = deque_begin(pdeq), i = 0;
         !iterator_equal(it_iter, deque_end(pdeq)) && i < 100;
         it_iter = iterator_next(it_iter), ++i) {
        assert_true(list_equal((list_t*)iterator_get_pointer(it_iter), aplist_array[i]));
    }

    for (i = 0; i < 100; ++i) {
        list_destroy(aplist_array[i]);
    }

    deque_destroy(pdeq);
    list_destroy(plist);
}

typedef struct _test_deque_assign_array {
    int n_elem;
}_test_deque_assign_array_t;
void test_deque_assign_array__user_define(void** state)
{
    _test_deque_assign_array_t* apt_array[10] = {NULL};
    _test_deque_assign_array_t t_elem;
    deque_t* pdeq = NULL;
    size_t i = 0;

    type_register(_test_deque_assign_array_t, NULL, NULL, NULL, NULL);
    t_elem.n_elem = 100;
    pdeq = create_deque(_test_deque_assign_array_t);
    deque_init_elem(pdeq, 45, &t_elem);

    for (i = 0; i < 10; ++i) {
        apt_array[i] = malloc(sizeof(_test_deque_assign_array_t));
        apt_array[i]->n_elem = -8;
    }
    assert_true(deque_size(pdeq) == 45);
    deque_assign_array(pdeq, apt_array, 10);
    assert_true(deque_size(pdeq) == 10);
    for(i = 0; i < deque_size(pdeq); ++i)
    {
        assert_true(((_test_deque_assign_array_t*)deque_at(pdeq, i))->n_elem == -8);
    }

    deque_destroy(pdeq);
    for (i = 0; i < 10; ++i) {
        free(apt_array[i]);
    }
}

void test_deque_assign_array__cstr(void** state)
{
    const char* acs_array[5] = {
        "abcdefgh",
        "ABCDEFGH",
        "IIIIIIII",
        "NG",
        "MMMM"
    };
    int i = 0;
    deque_iterator_t it_iter;
    deque_t* pdeq_dest = create_deque(char*);
    deque_init_elem(pdeq_dest, 10, "XXX");

    deque_assign_array(pdeq_dest, acs_array, 5);
    assert_true(deque_size(pdeq_dest) == 5);
    for(it_iter = deque_begin(pdeq_dest), i = 0;
        !iterator_equal(it_iter, deque_end(pdeq_dest)) && i < 5;
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(strcmp((char*)iterator_get_pointer(it_iter), acs_array[i]) == 0);
    }

    deque_destroy(pdeq_dest);
}

/*
 * test deque_equal
 */
UT_CASE_DEFINATION(deque_equal)
void test_deque_equal__null_first(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    expect_assert_failure(deque_equal(NULL, pdeq));

    deque_destroy(pdeq);
}

void test_deque_equal__null_second(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    expect_assert_failure(deque_equal(pdeq, NULL));

    deque_destroy(pdeq);
}

void test_deque_equal__non_inited_first(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_second);
    expect_assert_failure(deque_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_equal__non_inited_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_first);
    expect_assert_failure(deque_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_equal__not_same_type(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(double);

    deque_init(pdeq_first);
    deque_init(pdeq_second);
    expect_assert_failure(deque_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_equal__same_deque(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    assert_true(deque_equal(pdeq, pdeq));

    deque_destroy(pdeq);
}

void test_deque_equal__size_first_less_than_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_first);
    deque_init_n(pdeq_second, 48);
    assert_false(deque_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_equal__size_first_greater_than_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init_n(pdeq_first, 233);
    deque_init_n(pdeq_second, 48);
    assert_false(deque_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_equal__size_equal_0(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_first);
    deque_init(pdeq_second);
    assert_true(deque_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_equal__size_equal_elem_first_less_than_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init_elem(pdeq_first, 10, 100);
    deque_init_elem(pdeq_second, 10, 4545);
    assert_false(deque_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_equal__size_equal_elem_first_greater_than_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init_elem(pdeq_first, 10, 100);
    deque_init_elem(pdeq_second, 10, 45);
    assert_false(deque_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_equal__size_equal_elem_equal(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init_elem(pdeq_first, 10, 100);
    deque_init_elem(pdeq_second, 10, 100);
    assert_true(deque_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

/*
 * test deque_not_equal
 */
UT_CASE_DEFINATION(deque_not_equal)
void test_deque_not_equal__null_first(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    expect_assert_failure(deque_not_equal(NULL, pdeq));

    deque_destroy(pdeq);
}

void test_deque_not_equal__null_second(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    expect_assert_failure(deque_not_equal(pdeq, NULL));

    deque_destroy(pdeq);
}

void test_deque_not_equal__non_inited_first(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_second);
    expect_assert_failure(deque_not_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_not_equal__non_inited_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_first);
    expect_assert_failure(deque_not_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_not_equal__not_same_type(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(double);

    deque_init(pdeq_first);
    deque_init(pdeq_second);
    expect_assert_failure(deque_not_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_not_equal__same_deque(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    assert_false(deque_not_equal(pdeq, pdeq));

    deque_destroy(pdeq);
}

void test_deque_not_equal__size_first_less_than_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_first);
    deque_init_n(pdeq_second, 48);
    assert_true(deque_not_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_not_equal__size_first_greater_than_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init_n(pdeq_first, 233);
    deque_init_n(pdeq_second, 48);
    assert_true(deque_not_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_not_equal__size_equal_0(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_first);
    deque_init(pdeq_second);
    assert_false(deque_not_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_not_equal__size_equal_elem_first_less_than_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init_elem(pdeq_first, 10, 100);
    deque_init_elem(pdeq_second, 10, 4545);
    assert_true(deque_not_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_not_equal__size_equal_elem_first_greater_than_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init_elem(pdeq_first, 10, 100);
    deque_init_elem(pdeq_second, 10, 45);
    assert_true(deque_not_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_not_equal__size_equal_elem_equal(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init_elem(pdeq_first, 10, 100);
    deque_init_elem(pdeq_second, 10, 100);
    assert_false(deque_not_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

/*
 * test deque_less
 */
UT_CASE_DEFINATION(deque_less)
void test_deque_less__null_first(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    expect_assert_failure(deque_less(NULL, pdeq));

    deque_destroy(pdeq);
}

void test_deque_less__null_second(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    expect_assert_failure(deque_less(pdeq, NULL));

    deque_destroy(pdeq);
}

void test_deque_less__non_inited_first(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_second);
    expect_assert_failure(deque_less(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_less__non_inited_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_first);
    expect_assert_failure(deque_less(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_less__not_same_type(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(double);

    deque_init(pdeq_first);
    deque_init(pdeq_second);
    expect_assert_failure(deque_less(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_less__same_deque(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    assert_false(deque_less(pdeq, pdeq));

    deque_destroy(pdeq);
}

void test_deque_less__size_first_less_than_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_first);
    deque_init_n(pdeq_second, 48);
    assert_true(deque_less(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_less__size_first_greater_than_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init_n(pdeq_first, 233);
    deque_init_n(pdeq_second, 48);
    assert_false(deque_less(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_less__size_equal_0(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_first);
    deque_init(pdeq_second);
    assert_false(deque_less(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_less__size_equal_elem_first_less_than_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init_elem(pdeq_first, 10, 100);
    deque_init_elem(pdeq_second, 10, 4545);
    assert_true(deque_less(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_less__size_equal_elem_first_greater_than_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init_elem(pdeq_first, 10, 100);
    deque_init_elem(pdeq_second, 10, 45);
    assert_false(deque_less(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_less__size_equal_elem_equal(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init_elem(pdeq_first, 10, 100);
    deque_init_elem(pdeq_second, 10, 100);
    assert_false(deque_less(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

/*
 * test deque_less_equal
 */
UT_CASE_DEFINATION(deque_less_equal)
void test_deque_less_equal__null_first(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    expect_assert_failure(deque_less_equal(NULL, pdeq));

    deque_destroy(pdeq);
}

void test_deque_less_equal__null_second(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    expect_assert_failure(deque_less_equal(pdeq, NULL));

    deque_destroy(pdeq);
}

void test_deque_less_equal__non_inited_first(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_second);
    expect_assert_failure(deque_less_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_less_equal__non_inited_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_first);
    expect_assert_failure(deque_less_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_less_equal__not_same_type(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(double);

    deque_init(pdeq_first);
    deque_init(pdeq_second);
    expect_assert_failure(deque_less_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_less_equal__same_deque(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    assert_true(deque_less_equal(pdeq, pdeq));

    deque_destroy(pdeq);
}

void test_deque_less_equal__size_first_less_than_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_first);
    deque_init_n(pdeq_second, 48);
    assert_true(deque_less_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_less_equal__size_first_greater_than_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init_n(pdeq_first, 233);
    deque_init_n(pdeq_second, 48);
    assert_false(deque_less_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_less_equal__size_equal_0(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_first);
    deque_init(pdeq_second);
    assert_true(deque_less_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_less_equal__size_equal_elem_first_less_than_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init_elem(pdeq_first, 10, 100);
    deque_init_elem(pdeq_second, 10, 4545);
    assert_true(deque_less_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_less_equal__size_equal_elem_first_greater_than_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init_elem(pdeq_first, 10, 100);
    deque_init_elem(pdeq_second, 10, 45);
    assert_false(deque_less_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_less_equal__size_equal_elem_equal(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init_elem(pdeq_first, 10, 100);
    deque_init_elem(pdeq_second, 10, 100);
    assert_true(deque_less_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

/*
 * test deque_greater
 */
UT_CASE_DEFINATION(deque_greater)
void test_deque_greater__null_first(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    expect_assert_failure(deque_greater(NULL, pdeq));

    deque_destroy(pdeq);
}

void test_deque_greater__null_second(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    expect_assert_failure(deque_greater(pdeq, NULL));

    deque_destroy(pdeq);
}

void test_deque_greater__non_inited_first(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_second);
    expect_assert_failure(deque_greater(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_greater__non_inited_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_first);
    expect_assert_failure(deque_greater(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_greater__not_same_type(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(double);

    deque_init(pdeq_first);
    deque_init(pdeq_second);
    expect_assert_failure(deque_greater(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_greater__same_deque(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    assert_false(deque_greater(pdeq, pdeq));

    deque_destroy(pdeq);
}

void test_deque_greater__size_first_less_than_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_first);
    deque_init_n(pdeq_second, 48);
    assert_false(deque_greater(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_greater__size_first_greater_than_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init_n(pdeq_first, 233);
    deque_init_n(pdeq_second, 48);
    assert_true(deque_greater(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_greater__size_equal_0(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_first);
    deque_init(pdeq_second);
    assert_false(deque_greater(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_greater__size_equal_elem_first_less_than_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init_elem(pdeq_first, 10, 100);
    deque_init_elem(pdeq_second, 10, 4545);
    assert_false(deque_greater(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_greater__size_equal_elem_first_greater_than_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init_elem(pdeq_first, 10, 100);
    deque_init_elem(pdeq_second, 10, 45);
    assert_true(deque_greater(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_greater__size_equal_elem_equal(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init_elem(pdeq_first, 10, 100);
    deque_init_elem(pdeq_second, 10, 100);
    assert_false(deque_greater(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

/*
 * test deque_greater_equal
 */
UT_CASE_DEFINATION(deque_greater_equal)
void test_deque_greater_equal__null_first(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    expect_assert_failure(deque_greater_equal(NULL, pdeq));

    deque_destroy(pdeq);
}

void test_deque_greater_equal__null_second(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    expect_assert_failure(deque_greater_equal(pdeq, NULL));

    deque_destroy(pdeq);
}

void test_deque_greater_equal__non_inited_first(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_second);
    expect_assert_failure(deque_greater_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_greater_equal__non_inited_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_first);
    expect_assert_failure(deque_greater_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_greater_equal__not_same_type(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(double);

    deque_init(pdeq_first);
    deque_init(pdeq_second);
    expect_assert_failure(deque_greater_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_greater_equal__same_deque(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    assert_true(deque_greater_equal(pdeq, pdeq));

    deque_destroy(pdeq);
}

void test_deque_greater_equal__size_first_less_than_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_first);
    deque_init_n(pdeq_second, 48);
    assert_false(deque_greater_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_greater_equal__size_first_greater_than_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init_n(pdeq_first, 233);
    deque_init_n(pdeq_second, 48);
    assert_true(deque_greater_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_greater_equal__size_equal_0(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_first);
    deque_init(pdeq_second);
    assert_true(deque_greater_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_greater_equal__size_equal_elem_first_less_than_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init_elem(pdeq_first, 10, 100);
    deque_init_elem(pdeq_second, 10, 4545);
    assert_false(deque_greater_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_greater_equal__size_equal_elem_first_greater_than_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init_elem(pdeq_first, 10, 100);
    deque_init_elem(pdeq_second, 10, 45);
    assert_true(deque_greater_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_greater_equal__size_equal_elem_equal(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init_elem(pdeq_first, 10, 100);
    deque_init_elem(pdeq_second, 10, 100);
    assert_true(deque_greater_equal(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

/*
 * test deque_at
 */
UT_CASE_DEFINATION(deque_at)
void test_deque_at__null_deque_container(void** state)
{
    expect_assert_failure(deque_at(NULL, 0));
}

void test_deque_at__non_inited_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);

    expect_assert_failure(deque_at(pdeq, 0));

    deque_destroy(pdeq);
}

void test_deque_at__invalid_subscript_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    expect_assert_failure(deque_at(pdeq, 0));

    deque_destroy(pdeq);
}

void test_deque_at__invalid_subscript_end(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init_n(pdeq, 10);

    expect_assert_failure(deque_at(pdeq, deque_size(pdeq)));

    deque_destroy(pdeq);
}

void test_deque_at__invalid_subscript(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init_n(pdeq, 10);

    expect_assert_failure(deque_at(pdeq, 132));

    deque_destroy(pdeq);
}

void test_deque_at__successfully(void** state)
{
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }

    for(i = 0; i < deque_size(pdeq); ++i)
    {
        assert_true(*(int*)deque_at(pdeq, i) == i);
    }

    deque_destroy(pdeq);
}

void test_deque_at__successfully_cstr(void** state)
{
    deque_t* pdeq = create_deque(char*);
    deque_init(pdeq);

    deque_push_back(pdeq, "abc");
    deque_push_back(pdeq, "def");
    deque_push_back(pdeq, "hij");

    assert_true(strcmp((char*)deque_at(pdeq, 0), "abc") == 0);
    assert_true(strcmp((char*)deque_at(pdeq, 1), "def") == 0);
    assert_true(strcmp((char*)deque_at(pdeq, 2), "hij") == 0);

    deque_destroy(pdeq);
}

/*
 * test deque_front
 */
UT_CASE_DEFINATION(deque_front)
void test_deque_front__null_deque_container(void** state)
{
    expect_assert_failure(deque_front(NULL));
}

void test_deque_front__non_inited_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);

    expect_assert_failure(deque_front(pdeq));

    deque_destroy(pdeq);
}

void test_deque_front__empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    expect_assert_failure(deque_front(pdeq));

    deque_destroy(pdeq);
}

void test_deque_front__successfully(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    deque_push_back(pdeq, 2);
    deque_push_back(pdeq, 345);
    deque_push_back(pdeq, 24);
    assert_true(*(int*)deque_front(pdeq) == 2);

    deque_destroy(pdeq);
}

void test_deque_front__successfully_cstr(void** state)
{
    deque_t* pdeq = create_deque(char*);
    deque_init(pdeq);

    deque_push_back(pdeq, "wodjad");
    deque_push_back(pdeq, "345");
    deque_push_back(pdeq, "mmmmmm");
    assert_true(strcmp((char*)deque_front(pdeq), "wodjad") == 0);

    deque_destroy(pdeq);
}

/*
 * test deque_back
 */
UT_CASE_DEFINATION(deque_back)
void test_deque_back__null_deque_container(void** state)
{
    expect_assert_failure(deque_back(NULL));
}

void test_deque_back__non_inited_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);

    expect_assert_failure(deque_back(pdeq));

    deque_destroy(pdeq);
}

void test_deque_back__empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    expect_assert_failure(deque_back(pdeq));

    deque_destroy(pdeq);
}

void test_deque_back__successfully(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    deque_push_back(pdeq, 2);
    deque_push_back(pdeq, 345);
    deque_push_back(pdeq, 24);
    assert_true(*(int*)deque_back(pdeq) == 24);

    deque_destroy(pdeq);
}

void test_deque_back__successfully_cstr(void** state)
{
    deque_t* pdeq = create_deque(char*);
    deque_init(pdeq);

    deque_push_back(pdeq, "wodjad");
    deque_push_back(pdeq, "345");
    deque_push_back(pdeq, "mmmmmm");
    assert_true(strcmp((char*)deque_back(pdeq), "mmmmmm") == 0);

    deque_destroy(pdeq);
}

/*
 * test deque_swap
 */
UT_CASE_DEFINATION(deque_swap)
void test_deque_swap__null_first(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    expect_assert_failure(deque_swap(NULL, pdeq));

    deque_destroy(pdeq);
}

void test_deque_swap__null_second(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    expect_assert_failure(deque_swap(pdeq, NULL));

    deque_destroy(pdeq);
}

void test_deque_swap__non_inited_first(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_second);

    expect_assert_failure(deque_swap(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_swap__non_inited_second(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_first);

    expect_assert_failure(deque_swap(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_swap__not_same_type(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(double);

    deque_init(pdeq_first);
    deque_init(pdeq_second);

    expect_assert_failure(deque_swap(pdeq_first, pdeq_second));

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_swap__deque_equal(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);

    deque_init(pdeq_first);
    deque_init(pdeq_second);

    deque_swap(pdeq_first, pdeq_second);

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_swap__0_swap_10(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);
    size_t t_firstsize = 0;
    size_t t_secondsize = 0;

    deque_init(pdeq_first);
    deque_init_elem(pdeq_second, 10, 100);

    t_firstsize = deque_size(pdeq_first);
    t_secondsize = deque_size(pdeq_second);
    deque_swap(pdeq_first, pdeq_second);

    assert_true(deque_size(pdeq_first) == t_secondsize);
    assert_true(deque_size(pdeq_second) == t_firstsize);
    for(it_iter = deque_begin(pdeq_first);
        !iterator_equal(it_iter, deque_end(pdeq_first));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }
    for(it_iter = deque_begin(pdeq_second);
        !iterator_equal(it_iter, deque_end(pdeq_second));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_swap__10_swap_0(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);
    size_t t_firstsize = 0;
    size_t t_secondsize = 0;
    deque_iterator_t it_iter;

    deque_init_n(pdeq_first, 10);
    deque_init(pdeq_second);

    t_firstsize = deque_size(pdeq_first);
    t_secondsize = deque_size(pdeq_second);
    deque_swap(pdeq_first, pdeq_second);

    assert_true(deque_size(pdeq_first) == t_secondsize);
    assert_true(deque_size(pdeq_second) == t_firstsize);
    for(it_iter = deque_begin(pdeq_first);
        !iterator_equal(it_iter, deque_end(pdeq_first));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }
    for(it_iter = deque_begin(pdeq_second);
        !iterator_equal(it_iter, deque_end(pdeq_second));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_swap__10_swap_10(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);
    size_t t_firstsize = 0;
    size_t t_secondsize = 0;
    deque_iterator_t it_iter;

    deque_init_n(pdeq_first, 10);
    deque_init_elem(pdeq_second, 10, 100);

    t_firstsize = deque_size(pdeq_first);
    t_secondsize = deque_size(pdeq_second);
    deque_swap(pdeq_first, pdeq_second);

    assert_true(deque_size(pdeq_first) == t_secondsize);
    assert_true(deque_size(pdeq_second) == t_firstsize);
    for(it_iter = deque_begin(pdeq_first);
        !iterator_equal(it_iter, deque_end(pdeq_first));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }
    for(it_iter = deque_begin(pdeq_second);
        !iterator_equal(it_iter, deque_end(pdeq_second));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

void test_deque_swap__10_swap_1000(void** state)
{
    deque_t* pdeq_first = create_deque(int);
    deque_t* pdeq_second = create_deque(int);
    size_t t_firstsize = 0;
    size_t t_secondsize = 0;
    deque_iterator_t it_iter;

    deque_init_n(pdeq_first, 10);
    deque_init_elem(pdeq_second, 1000, 100);

    t_firstsize = deque_size(pdeq_first);
    t_secondsize = deque_size(pdeq_second);
    deque_swap(pdeq_first, pdeq_second);

    assert_true(deque_size(pdeq_first) == t_secondsize);
    assert_true(deque_size(pdeq_second) == t_firstsize);
    for(it_iter = deque_begin(pdeq_first);
        !iterator_equal(it_iter, deque_end(pdeq_first));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }
    for(it_iter = deque_begin(pdeq_second);
        !iterator_equal(it_iter, deque_end(pdeq_second));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    deque_destroy(pdeq_first);
    deque_destroy(pdeq_second);
}

/*
 * test deque_pop_back
 */
UT_CASE_DEFINATION(deque_pop_back)
void test_deque_pop_back__null_deque_container(void** state)
{
    expect_assert_failure(deque_pop_back(NULL));
}

void test_deque_pop_back__non_inited_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);

    expect_assert_failure(deque_pop_back(pdeq));

    deque_destroy(pdeq);
}

void test_deque_pop_back__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    expect_assert_failure(deque_pop_back(pdeq));

    deque_destroy(pdeq);
}

void test_deque_pop_back__successfully(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }
    t_oldsize = deque_size(pdeq);
    assert_true(*(int*)deque_back(pdeq) == 9);
    deque_pop_back(pdeq);
    assert_true(deque_size(pdeq) == t_oldsize - 1);
    assert_true(*(int*)deque_back(pdeq) == 8);

    deque_destroy(pdeq);
}

/*
 * test deque_pop_front
 */
UT_CASE_DEFINATION(deque_pop_front)
void test_deque_pop_front__null_deque_container(void** state)
{
    expect_assert_failure(deque_pop_front(NULL));
}

void test_deque_pop_front__non_inited_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);

    expect_assert_failure(deque_pop_front(pdeq));

    deque_destroy(pdeq);
}

void test_deque_pop_front__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    expect_assert_failure(deque_pop_front(pdeq));

    deque_destroy(pdeq);
}

void test_deque_pop_front__successfully(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }
    t_oldsize = deque_size(pdeq);
    assert_true(*(int*)deque_front(pdeq) == 0);
    deque_pop_front(pdeq);
    assert_true(deque_size(pdeq) == t_oldsize - 1);
    assert_true(*(int*)deque_front(pdeq) == 1);

    deque_destroy(pdeq);
}

/*
 * test deque_insert_range
 */
UT_CASE_DEFINATION(deque_insert_range)
void test_deque_insert_range__null_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_src = create_deque(int);
    deque_init(pdeq);
    deque_init(pdeq_src);

    expect_assert_failure(deque_insert_range(NULL, deque_begin(pdeq), deque_begin(pdeq_src), deque_end(pdeq_src)));

    deque_destroy(pdeq);
    deque_destroy(pdeq_src);
}

void test_deque_insert_range__non_inited(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_src = create_deque(int);
    deque_init(pdeq_src);

    expect_assert_failure(deque_insert_range(pdeq, deque_begin(pdeq), deque_begin(pdeq_src), deque_end(pdeq_src)));

    deque_destroy(pdeq);
    deque_destroy(pdeq_src);
}

void test_deque_insert_range__invalid_position(void** state)
{
    deque_iterator_t it_pos = _create_deque_iterator();
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_src = create_deque(int);
    deque_init(pdeq_src);
    deque_init_n(pdeq, 10);
    it_pos = deque_begin(pdeq);
    it_pos._t_pos._t_dequepos._pby_corepos = NULL;

    expect_assert_failure(deque_insert_range(pdeq, it_pos, deque_begin(pdeq_src), deque_end(pdeq_src)));

    deque_destroy(pdeq);
    deque_destroy(pdeq_src);
}

void test_deque_insert_range__invalid_range(void** state)
{
    deque_iterator_t it_pos = _create_deque_iterator();
    deque_iterator_t it_begin = _create_deque_iterator();
    deque_iterator_t it_end = _create_deque_iterator();
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_src = create_deque(int);
    deque_init_n(pdeq_src, 10);
    deque_init_n(pdeq, 10);
    it_pos = deque_begin(pdeq);
    it_begin = deque_begin(pdeq_src);
    it_end = deque_end(pdeq_src);

    expect_assert_failure(deque_insert_range(pdeq, it_pos, it_end, it_begin));

    deque_destroy(pdeq);
    deque_destroy(pdeq_src);
}

void test_deque_insert_range__invalid_range_not_same_type(void** state)
{
    deque_iterator_t it_pos = _create_deque_iterator();
    deque_iterator_t it_begin = _create_deque_iterator();
    deque_iterator_t it_end = _create_deque_iterator();
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_src = create_deque(double);
    deque_init(pdeq_src);
    deque_init_n(pdeq, 10);
    it_pos = deque_begin(pdeq);
    it_begin = deque_begin(pdeq_src);
    it_end = deque_end(pdeq_src);

    expect_assert_failure(deque_insert_range(pdeq, it_pos, it_begin, it_end));

    deque_destroy(pdeq);
    deque_destroy(pdeq_src);
}

void test_deque_insert_range__invalid_range_belong_to_deque(void** state)
{
    deque_iterator_t it_pos = _create_deque_iterator();
    deque_iterator_t it_begin = _create_deque_iterator();
    deque_iterator_t it_end = _create_deque_iterator();
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_src = create_deque(int);
    deque_init(pdeq_src);
    deque_init_n(pdeq, 10);
    it_pos = deque_begin(pdeq);
    it_begin = deque_begin(pdeq_src);
    it_end = deque_end(pdeq_src);

    deque_insert_range(pdeq, it_pos, it_pos, it_pos);

    deque_destroy(pdeq);
    deque_destroy(pdeq_src);
}

void test_deque_insert_range__empty_insert_0(void** state)
{
    deque_iterator_t it_pos;
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_src = create_deque(int);
    deque_init(pdeq);
    deque_init(pdeq_src);

    assert_true(deque_size(pdeq) == 0);
    it_pos = deque_begin(pdeq);
    deque_insert_range(pdeq, it_pos, deque_begin(pdeq_src), deque_end(pdeq_src));
    assert_true(deque_size(pdeq) == 0);

    deque_destroy(pdeq);
    deque_destroy(pdeq_src);
}

void test_deque_insert_range__empty_insert_10(void** state)
{
    deque_iterator_t it_pos;
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_src = create_deque(int);
    deque_init(pdeq);
    deque_init_elem(pdeq_src, 10, 100);

    assert_true(deque_size(pdeq) == 0);
    it_pos = deque_begin(pdeq);
    deque_insert_range(pdeq, it_pos, deque_begin(pdeq_src), deque_end(pdeq_src));
    assert_true(deque_size(pdeq) == 10);
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    deque_destroy(pdeq);
    deque_destroy(pdeq_src);
}

void test_deque_insert_range__begin_insert_0(void** state)
{
    deque_iterator_t it_pos;
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_src = create_deque(int);
    deque_init_n(pdeq, 1000);
    deque_init_elem(pdeq_src, 0, 100);

    assert_true(deque_size(pdeq) == 1000);
    it_pos = deque_begin(pdeq);
    deque_insert_range(pdeq, it_pos, deque_begin(pdeq_src), deque_end(pdeq_src));
    assert_true(deque_size(pdeq) == 1000);
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    deque_destroy(pdeq);
    deque_destroy(pdeq_src);
}

void test_deque_insert_range__begin_insert_10(void** state)
{
    deque_iterator_t it_pos;
    deque_iterator_t it_iter;
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_src = create_deque(int);
    deque_init_elem(pdeq_src, 10, 100);
    deque_init_n(pdeq, 1000);

    assert_true(deque_size(pdeq) == 1000);
    it_pos = deque_begin(pdeq);
    deque_insert_range(pdeq, it_pos, deque_begin(pdeq_src), deque_end(pdeq_src));
    assert_true(deque_size(pdeq) == 1010);
    for(it_iter = deque_begin(pdeq), i = 0;
        !iterator_equal(it_iter, deque_end(pdeq));
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

    deque_destroy(pdeq);
    deque_destroy(pdeq_src);
}

void test_deque_insert_range__middle_insert_0(void** state)
{
    deque_iterator_t it_pos;
    deque_iterator_t it_iter;
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_src = create_deque(int);
    deque_init_elem(pdeq_src, 0, 100);
    deque_init_n(pdeq, 1000);

    assert_true(deque_size(pdeq) == 1000);
    it_pos = iterator_advance(deque_begin(pdeq), 300);
    deque_insert_range(pdeq, it_pos, deque_begin(pdeq_src), deque_end(pdeq_src));
    assert_true(deque_size(pdeq) == 1000);
    for(it_iter = deque_begin(pdeq), i = 0;
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    deque_destroy(pdeq);
    deque_destroy(pdeq_src);
}

void test_deque_insert_range__middle_insert_10(void** state)
{
    deque_iterator_t it_pos;
    deque_iterator_t it_iter;
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_src = create_deque(int);
    deque_init_elem(pdeq_src, 10, 100);
    deque_init_n(pdeq, 1000);

    assert_true(deque_size(pdeq) == 1000);
    it_pos = iterator_advance(deque_begin(pdeq), 300);
    deque_insert_range(pdeq, it_pos, deque_begin(pdeq_src), deque_end(pdeq_src));
    assert_true(deque_size(pdeq) == 1010);
    for(it_iter = deque_begin(pdeq), i = 0;
        !iterator_equal(it_iter, deque_end(pdeq));
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

    deque_destroy(pdeq);
    deque_destroy(pdeq_src);
}

void test_deque_insert_range__end_insert_0(void** state)
{
    deque_iterator_t it_pos;
    deque_iterator_t it_iter;
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_src = create_deque(int);
    deque_init_elem(pdeq_src, 0, 100);
    deque_init_n(pdeq, 1000);

    assert_true(deque_size(pdeq) == 1000);
    it_pos = deque_end(pdeq);
    deque_insert_range(pdeq, it_pos, deque_begin(pdeq_src), deque_end(pdeq_src));
    assert_true(deque_size(pdeq) == 1000);
    for(it_iter = deque_begin(pdeq), i = 0;
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    deque_destroy(pdeq);
    deque_destroy(pdeq_src);
}

void test_deque_insert_range__end_insert_10(void** state)
{
    deque_iterator_t it_pos;
    deque_iterator_t it_iter;
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_src = create_deque(int);
    deque_init_elem(pdeq_src, 10, 100);
    deque_init_n(pdeq, 1000);

    assert_true(deque_size(pdeq) == 1000);
    it_pos = deque_end(pdeq);
    deque_insert_range(pdeq, it_pos, deque_begin(pdeq_src), deque_end(pdeq_src));
    assert_true(deque_size(pdeq) == 1010);
    for(it_iter = deque_begin(pdeq), i = 0;
        !iterator_equal(it_iter, deque_end(pdeq));
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

    deque_destroy(pdeq);
    deque_destroy(pdeq_src);
}

void test_deque_insert_range__other_container_range(void** state)
{
    deque_t* pdeq = create_deque(char);
    string_t* pstr = create_string();
    size_t i = 0;

    deque_init_elem(pdeq, 10, 'a');
    string_init_char(pstr, 100, 'x');
    deque_insert_range(pdeq, deque_begin(pdeq), string_begin(pstr), string_end(pstr));
    assert_true(deque_size(pdeq) == 110);
    for(i = 0; i < deque_size(pdeq); ++i)
    {
        if(i < 100)
        {
            assert_true(*(char*)deque_at(pdeq, i) == 'x');
        }
        else
        {
            assert_true(*(char*)deque_at(pdeq, i) == 'a');
        }
    }

    deque_destroy(pdeq);
    string_destroy(pstr);
}

void test_deque_insert_range__other_container_range1(void** state)
{
    deque_t* pdeq = create_deque(deque_t<char*>);
    slist_t* pslist = create_slist(deque_t<char*>);
    deque_t* pdeq_str = create_deque(char*);
    size_t i = 0;

    deque_init_n(pdeq_str, 10);
    deque_init_elem(pdeq, 10, pdeq_str);
    deque_resize(pdeq_str, 100);
    slist_init_elem(pslist, 100, pdeq_str);
    deque_insert_range(pdeq, deque_end(pdeq), slist_begin(pslist), slist_end(pslist));
    assert_true(deque_size(pdeq) == 110);
    for(i = 0; i < deque_size(pdeq); ++i)
    {
        if(i >= 10)
        {
            assert_true(deque_size((deque_t*)deque_at(pdeq, i)) == 100);
        }
        else
        {
            assert_true(deque_size((deque_t*)deque_at(pdeq, i)) == 10);
        }
    }

    deque_destroy(pdeq);
    deque_destroy(pdeq_str);
    slist_destroy(pslist);
}

/*
 * test deque_insert_array
 */
UT_CASE_DEFINATION(deque_insert_array)
void test_deque_insert_array__null_deque_container(void** state)
{
    int an_array[10] = {0};
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    expect_assert_failure(deque_insert_array(NULL, deque_begin(pdeq), an_array, 10));

    deque_destroy(pdeq);
}

void test_deque_insert_array__non_inited(void** state)
{
    int an_array[10] = {0};
    deque_t* pdeq = create_deque(int);

    expect_assert_failure(deque_insert_array(pdeq, deque_begin(pdeq), an_array, 10));

    deque_destroy(pdeq);
}

void test_deque_insert_array__invalid_position(void** state)
{
    int an_array[10] = {0};
    deque_iterator_t it_pos = _create_deque_iterator();
    deque_t* pdeq = create_deque(int);
    deque_init_n(pdeq, 10);
    it_pos = deque_begin(pdeq);
    it_pos._t_pos._t_dequepos._pby_corepos = NULL;

    expect_assert_failure(deque_insert_array(pdeq, it_pos, an_array, 10));

    deque_destroy(pdeq);
}

void test_deque_insert_array__invalid_array(void** state)
{
    deque_iterator_t it_pos = _create_deque_iterator();
    deque_t* pdeq = create_deque(int);
    deque_init_n(pdeq, 10);
    it_pos = deque_begin(pdeq);

    expect_assert_failure(deque_insert_array(pdeq, it_pos, NULL, 10));

    deque_destroy(pdeq);
}

void test_deque_insert_array__empty_insert_0(void** state)
{
    int an_array[10] = {0};
    deque_iterator_t it_pos;
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    assert_true(deque_size(pdeq) == 0);
    it_pos = deque_begin(pdeq);
    deque_insert_array(pdeq, it_pos, an_array, 0);
    assert_true(deque_size(pdeq) == 0);

    deque_destroy(pdeq);
}

void test_deque_insert_array__empty_insert_10(void** state)
{
    int i = 0;
    int an_array[10] = {0};
    deque_iterator_t it_pos;
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    assert_true(deque_size(pdeq) == 0);
    it_pos = deque_begin(pdeq);
    deque_insert_array(pdeq, it_pos, an_array, 10);
    assert_true(deque_size(pdeq) == 10);
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    deque_destroy(pdeq);
}

void test_deque_insert_array__begin_insert_0(void** state)
{
    int i = 0;
    int an_array[10] = {0};
    deque_iterator_t it_pos;
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);
    deque_init_n(pdeq, 1000);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    assert_true(deque_size(pdeq) == 1000);
    it_pos = deque_begin(pdeq);
    deque_insert_array(pdeq, it_pos, an_array, 0);
    assert_true(deque_size(pdeq) == 1000);
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    deque_destroy(pdeq);
}

void test_deque_insert_array__begin_insert_10(void** state)
{
    deque_iterator_t it_pos;
    deque_iterator_t it_iter;
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    int an_array[10] = {0};
    deque_init_n(pdeq, 1000);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    assert_true(deque_size(pdeq) == 1000);
    it_pos = deque_begin(pdeq);
    deque_insert_array(pdeq, it_pos, an_array, 10);
    assert_true(deque_size(pdeq) == 1010);
    for(it_iter = deque_begin(pdeq), i = 0;
        !iterator_equal(it_iter, deque_end(pdeq));
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

    deque_destroy(pdeq);
}

void test_deque_insert_array__middle_insert_0(void** state)
{
    deque_iterator_t it_pos;
    deque_iterator_t it_iter;
    size_t i = 0;
    int an_array[10] = {0};
    deque_t* pdeq = create_deque(int);
    deque_init_n(pdeq, 1000);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    assert_true(deque_size(pdeq) == 1000);
    it_pos = iterator_advance(deque_begin(pdeq), 300);
    deque_insert_array(pdeq, it_pos, an_array, 0);
    assert_true(deque_size(pdeq) == 1000);
    for(it_iter = deque_begin(pdeq), i = 0;
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    deque_destroy(pdeq);
}

void test_deque_insert_array__middle_insert_10(void** state)
{
    deque_iterator_t it_pos;
    deque_iterator_t it_iter;
    size_t i = 0;
    int an_array[10] = {0};
    deque_t* pdeq = create_deque(int);
    deque_init_n(pdeq, 1000);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    assert_true(deque_size(pdeq) == 1000);
    it_pos = iterator_advance(deque_begin(pdeq), 300);
    deque_insert_array(pdeq, it_pos, an_array, 10);
    assert_true(deque_size(pdeq) == 1010);
    for(it_iter = deque_begin(pdeq), i = 0;
        !iterator_equal(it_iter, deque_end(pdeq));
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

    deque_destroy(pdeq);
}

void test_deque_insert_array__end_insert_0(void** state)
{
    deque_iterator_t it_pos;
    deque_iterator_t it_iter;
    int an_array[10] = {0};
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_init_n(pdeq, 1000);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    assert_true(deque_size(pdeq) == 1000);
    it_pos = deque_end(pdeq);
    deque_insert_array(pdeq, it_pos, an_array, 0);
    assert_true(deque_size(pdeq) == 1000);
    for(it_iter = deque_begin(pdeq), i = 0;
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    deque_destroy(pdeq);
}

void test_deque_insert_array__end_insert_10(void** state)
{
    deque_iterator_t it_pos;
    deque_iterator_t it_iter;
    size_t i = 0;
    int an_array[10] = {0};
    deque_t* pdeq = create_deque(int);
    deque_init_n(pdeq, 1000);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    assert_true(deque_size(pdeq) == 1000);
    it_pos = deque_end(pdeq);
    deque_insert_array(pdeq, it_pos, an_array, 10);
    assert_true(deque_size(pdeq) == 1010);
    for(it_iter = deque_begin(pdeq), i = 0;
        !iterator_equal(it_iter, deque_end(pdeq));
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

    deque_destroy(pdeq);
}

void test_deque_insert_array__other_container_array(void** state)
{
    deque_t* pdeq = create_deque(char);
    string_t* pstr = create_string();
    size_t i = 0;

    deque_init_elem(pdeq, 10, 'a');
    string_init_char(pstr, 100, 'x');
    deque_insert_array(pdeq, deque_begin(pdeq), string_c_str(pstr), string_size(pstr));
    assert_true(deque_size(pdeq) == 110);
    for(i = 0; i < deque_size(pdeq); ++i)
    {
        if(i < 100)
        {
            assert_true(*(char*)deque_at(pdeq, i) == 'x');
        }
        else
        {
            assert_true(*(char*)deque_at(pdeq, i) == 'a');
        }
    }

    deque_destroy(pdeq);
    string_destroy(pstr);
}

void test_deque_insert_array__other_container_array1(void** state)
{
    deque_t* apdeq_array[100] = {NULL};
    deque_t* pdeq = create_deque(deque_t<char*>);
    deque_t* pdeq_str = create_deque(char*);
    size_t i = 0;

    deque_init_n(pdeq_str, 10);
    deque_init_elem(pdeq, 10, pdeq_str);
    for (i = 0; i < 100; ++i) {
        apdeq_array[i] = create_deque(char*);
        deque_init_n(apdeq_array[i], 100);
    }
    deque_insert_array(pdeq, deque_end(pdeq), apdeq_array, 100);
    assert_true(deque_size(pdeq) == 110);
    for(i = 0; i < deque_size(pdeq); ++i)
    {
        if(i >= 10)
        {
            assert_true(deque_size((deque_t*)deque_at(pdeq, i)) == 100);
        }
        else
        {
            assert_true(deque_size((deque_t*)deque_at(pdeq, i)) == 10);
        }
    }
    for (i = 0; i < 100; ++i) {
        deque_destroy(apdeq_array[i]);
    }

    deque_destroy(pdeq);
    deque_destroy(pdeq_str);
}

void test_deque_insert_array__cstr(void** state)
{
    const char* as_array[10] = {
        "Linux","FreeBSD","Fedora","Redhat","IBM","MS","MacOSX","Apple","Windows","UNIX"
    };
    int i = 0;
    deque_t* pdeq = create_deque(char*);
    deque_iterator_t it_iter;
    deque_init(pdeq);

    deque_insert_array(pdeq, deque_begin(pdeq), as_array, 10);
    assert_true(deque_size(pdeq) == 10);
    for (it_iter = deque_begin(pdeq), i = 0;
         !iterator_equal(it_iter, deque_end(pdeq)) && i < 10;
         it_iter = iterator_next(it_iter), ++i) {
        assert_true(strcmp((char*)iterator_get_pointer(it_iter), as_array[i]) == 0);
    }

    deque_destroy(pdeq);
}

typedef struct _test_deque_insert_array{
    int n_elem;
}_test_deque_insert_array_t;
void test_deque_insert_array__user_define(void** state)
{
    _test_deque_insert_array_t* apt_array[10] = {NULL};
    int i = 0;
    deque_t* pdeq = NULL;
    deque_iterator_t it_iter;

    type_register(_test_deque_insert_array_t, NULL, NULL, NULL, NULL);
    pdeq = create_deque(_test_deque_insert_array_t);
    deque_init(pdeq);
    for (i = 0; i < 10; ++i) {
        apt_array[i] = malloc(sizeof(_test_deque_insert_array_t));
        apt_array[i]->n_elem = 100;
    }
    deque_insert_array(pdeq, deque_begin(pdeq), apt_array, 10);
    for (it_iter = deque_begin(pdeq);
         !iterator_equal(it_iter, deque_end(pdeq));
         it_iter = iterator_next(it_iter)) {
        assert_true(((_test_deque_insert_array_t*)iterator_get_pointer(it_iter))->n_elem == 100);
    }

    deque_destroy(pdeq);
    for (i = 0; i < 10; ++i) {
        free(apt_array[i]);
    }
}

/*
 * test deque_erase
 */
UT_CASE_DEFINATION(deque_erase)
void test_deque_erase__null_deque_container(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    deque_iterator_t it_pos = _create_deque_iterator();
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }
    t_oldsize = deque_size(pdeq);

    it_pos = deque_begin(pdeq);
    expect_assert_failure(deque_erase(NULL, it_pos));

    deque_destroy(pdeq);
}

void test_deque_erase__non_inited_deque_container(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    deque_iterator_t it_pos = _create_deque_iterator();
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);
    t_oldsize = deque_size(pdeq);

    it_pos = deque_begin(pdeq);
    pdeq->_t_mapsize = 0;
    expect_assert_failure(deque_erase(pdeq, it_pos));

    pdeq->_t_mapsize = 16;
    deque_destroy(pdeq);
}

void test_deque_erase__invalid_pos_end(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    deque_iterator_t it_pos = _create_deque_iterator();
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }
    t_oldsize = deque_size(pdeq);

    it_pos = deque_end(pdeq);
    expect_assert_failure(deque_erase(pdeq, it_pos));

    deque_destroy(pdeq);
}

void test_deque_erase__invalid_pos(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    deque_iterator_t it_pos = _create_deque_iterator();
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }
    t_oldsize = deque_size(pdeq);

    it_pos = deque_end(pdeq);
    it_pos._t_pos._t_dequepos._pby_corepos = NULL;
    expect_assert_failure(deque_erase(pdeq, it_pos));

    deque_destroy(pdeq);
}

void test_deque_erase__successfully_begin(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    deque_iterator_t it_pos = _create_deque_iterator();
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }
    t_oldsize = deque_size(pdeq);

    it_pos = deque_begin(pdeq);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
    it_iter = deque_erase(pdeq, it_pos);
    assert_true(deque_size(pdeq) == t_oldsize - 1);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    deque_destroy(pdeq);
}

void test_deque_erase__successfully_middle(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    deque_iterator_t it_pos = _create_deque_iterator();
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }
    t_oldsize = deque_size(pdeq);

    it_pos = iterator_next(deque_begin(pdeq));
    assert_true(*(int*)iterator_get_pointer(it_pos) == 1);
    it_iter = deque_erase(pdeq, it_pos);
    assert_true(deque_size(pdeq) == t_oldsize - 1);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);

    deque_destroy(pdeq);
}

void test_deque_erase__successfully_back(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    deque_iterator_t it_pos = _create_deque_iterator();
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }
    t_oldsize = deque_size(pdeq);

    it_pos = iterator_prev(deque_end(pdeq));
    assert_true(*(int*)iterator_get_pointer(it_pos) == 9);
    it_iter = deque_erase(pdeq, it_pos);
    assert_true(deque_size(pdeq) == t_oldsize - 1);
    assert_true(*(int*)deque_back(pdeq) == 8);
    assert_true(iterator_equal(it_iter, deque_end(pdeq)));

    deque_destroy(pdeq);
}

/*
 * test deque_erase_range
 */
UT_CASE_DEFINATION(deque_erase_range)
void test_deque_erase_range__null_deque_container(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    deque_iterator_t it_begin = _create_deque_iterator();
    deque_iterator_t it_end = _create_deque_iterator();
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }
    t_oldsize = deque_size(pdeq);

    it_begin = deque_begin(pdeq);
    it_end = deque_end(pdeq);
    expect_assert_failure(deque_erase_range(NULL, it_begin, it_end));

    deque_destroy(pdeq);
}

void test_deque_erase_range__non_inited_deque_container(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    deque_iterator_t it_begin = _create_deque_iterator();
    deque_iterator_t it_end = _create_deque_iterator();
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }
    t_oldsize = deque_size(pdeq);

    it_begin = deque_begin(pdeq);
    it_end = deque_end(pdeq);
    pdeq->_t_mapsize = 0;
    expect_assert_failure(deque_erase_range(pdeq, it_begin, it_end));

    pdeq->_t_mapsize = 16;
    deque_destroy(pdeq);
}

void test_deque_erase_range__invalid_range_not_belong_to_deque(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    deque_iterator_t it_begin = _create_deque_iterator();
    deque_iterator_t it_end = _create_deque_iterator();
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }
    t_oldsize = deque_size(pdeq);

    expect_assert_failure(deque_erase_range(pdeq, it_begin, it_end));

    deque_destroy(pdeq);
}

void test_deque_erase_range__invalid_range(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    deque_iterator_t it_begin = _create_deque_iterator();
    deque_iterator_t it_end = _create_deque_iterator();
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }
    t_oldsize = deque_size(pdeq);

    it_begin = deque_begin(pdeq);
    it_end = deque_end(pdeq);
    expect_assert_failure(deque_erase_range(pdeq, it_end, it_begin));

    deque_destroy(pdeq);
}

void test_deque_erase_range__successfully_empty(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_erasesize = 0;
    deque_iterator_t it_begin = _create_deque_iterator();
    deque_iterator_t it_end = _create_deque_iterator();
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }
    t_oldsize = deque_size(pdeq);

    it_begin = deque_begin(pdeq);
    it_end = deque_end(pdeq);
    it_iter = deque_erase_range(pdeq, it_begin, it_begin);
    assert_true(deque_size(pdeq) == t_oldsize - t_erasesize);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    deque_destroy(pdeq);
}

void test_deque_erase_range__successfully_begin(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_erasesize = 0;
    deque_iterator_t it_begin = _create_deque_iterator();
    deque_iterator_t it_end = _create_deque_iterator();
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }
    t_oldsize = deque_size(pdeq);

    it_begin = deque_begin(pdeq);
    it_end = iterator_advance(it_begin, 3);
    t_erasesize = iterator_distance(it_begin, it_end);
    it_iter = deque_erase_range(pdeq, it_begin, it_end);
    assert_true(deque_size(pdeq) == t_oldsize - t_erasesize);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);

    deque_destroy(pdeq);
}

void test_deque_erase_range__successfully_middle(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_erasesize = 0;
    deque_iterator_t it_begin = _create_deque_iterator();
    deque_iterator_t it_end = _create_deque_iterator();
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }
    t_oldsize = deque_size(pdeq);

    it_begin = iterator_advance(deque_begin(pdeq), 3);
    it_end = iterator_advance(it_begin, 3);
    t_erasesize = iterator_distance(it_begin, it_end);
    it_iter = deque_erase_range(pdeq, it_begin, it_end);
    assert_true(deque_size(pdeq) == t_oldsize - t_erasesize);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);

    deque_destroy(pdeq);
}

void test_deque_erase_range__successfully_end(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_erasesize = 0;
    deque_iterator_t it_begin = _create_deque_iterator();
    deque_iterator_t it_end = _create_deque_iterator();
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }
    t_oldsize = deque_size(pdeq);

    it_begin = iterator_advance(deque_begin(pdeq), 6);
    it_end = deque_end(pdeq);
    t_erasesize = iterator_distance(it_begin, it_end);
    it_iter = deque_erase_range(pdeq, it_begin, it_end);
    assert_true(deque_size(pdeq) == t_oldsize - t_erasesize);
    assert_true(*(int*)deque_back(pdeq) == 5);
    assert_true(iterator_equal(it_iter, deque_end(pdeq)));

    deque_destroy(pdeq);
}

void test_deque_erase_range__successfully_all(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_erasesize = 0;
    deque_iterator_t it_begin = _create_deque_iterator();
    deque_iterator_t it_end = _create_deque_iterator();
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);
    for(i = 0; i < 10; ++i)
    {
        deque_push_back(pdeq, i);
    }
    t_oldsize = deque_size(pdeq);

    it_begin = deque_begin(pdeq);
    it_end = deque_end(pdeq);
    t_erasesize = iterator_distance(it_begin, it_end);
    it_iter = deque_erase_range(pdeq, it_begin, it_end);
    assert_true(deque_size(pdeq) == t_oldsize - t_erasesize);
    assert_true(deque_empty(pdeq));
    assert_true(iterator_equal(it_iter, deque_end(pdeq)));

    deque_destroy(pdeq);
}

/*
 * test deque_clear
 */
UT_CASE_DEFINATION(deque_clear)
void test_deque_clear__null_deque_container(void** state)
{
    expect_assert_failure(deque_clear(NULL));
}

void test_deque_clear__non_inited_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);

    expect_assert_failure(deque_clear(pdeq));

    deque_destroy(pdeq);
}

void test_deque_clear__empty_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);

    deque_clear(pdeq);
    assert_true(deque_size(pdeq) == 0);

    deque_destroy(pdeq);
}

void test_deque_clear__non_empty_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 198);

    deque_clear(pdeq);
    assert_true(deque_size(pdeq) == 0);

    deque_destroy(pdeq);
}

/*
 * test deque_resize
 */
UT_CASE_DEFINATION(deque_resize)
void test_deque_resize__null_deque_container(void** state)
{
    expect_assert_failure(deque_resize(NULL, 10));
}

void test_deque_resize__non_inited(void** state)
{
    deque_t* pdeq = create_deque(int);

    expect_assert_failure(deque_resize(pdeq, 10));

    deque_destroy(pdeq);
}

void test_deque_resize__successfully_0_resize_0(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    assert_true(deque_size(pdeq) == 0);
    deque_resize(pdeq, 0);
    assert_true(deque_size(pdeq) == 0);

    deque_destroy(pdeq);
}

void test_deque_resize__successfully_0_resize_10(void** state)
{
    size_t i = 0;
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    assert_true(deque_size(pdeq) == 0);
    deque_resize(pdeq, 10);
    assert_true(deque_size(pdeq) == 10);
    for(it_iter = deque_begin(pdeq), i = 0;
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    deque_destroy(pdeq);
}

void test_deque_resize__successfully_10_resize_0(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init_n(pdeq, 10);

    assert_true(deque_size(pdeq) == 10);
    deque_resize(pdeq, 0);
    assert_true(deque_size(pdeq) == 0);

    deque_destroy(pdeq);
}

void test_deque_resize__successfully_10_resize_10(void** state)
{
    size_t i = 0;
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);
    deque_init_n(pdeq, 10);

    assert_true(deque_size(pdeq) == 10);
    deque_resize(pdeq, 10);
    assert_true(deque_size(pdeq) == 10);
    for(it_iter = deque_begin(pdeq), i = 0;
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    deque_destroy(pdeq);
}

void test_deque_resize__successfully_10_resize_1000(void** state)
{
    size_t i = 0;
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);
    deque_init_elem(pdeq, 10, 100);

    assert_true(deque_size(pdeq) == 10);
    deque_resize(pdeq, 1000);
    assert_true(deque_size(pdeq) == 1000);
    for(it_iter = deque_begin(pdeq), i = 0;
        !iterator_equal(it_iter, deque_end(pdeq));
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

    deque_destroy(pdeq);
}

