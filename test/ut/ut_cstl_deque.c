#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/cdeque.h"
#include "cstl/cstring.h"
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
    assert_false(deque_equal(pdeq_first, pdeq_second));

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
    assert_true(deque_not_equal(pdeq_first, pdeq_second));

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

