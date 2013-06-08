#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/cstl_slist_iterator.h"
#include "cstl/cslist.h"
#include "cstl/cdeque.h"
#include "cstl/cvector.h"
#include "cstl_slist_aux.h"
#include "cstl/cstring.h"
#include "cstl/cfunctional.h"
#include "cstl_vector_aux.h"

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
    slist._t_head._pt_next = (_slistnode_t*)0x87734;
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
    pslist_dest->_t_head._pt_next = (_slistnode_t*)0x8888;
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
    pslist_dest->_t_head._pt_next = (_slistnode_t*)0x9999;
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

void test_slist_init_copy_range__other_container_range(void** state)
{
    slist_t* pslist = create_slist(int);
    vector_t* pvec = create_vector(int);
    iterator_t it;

    vector_init_elem(pvec, 10, -33);
    slist_init_copy_range(pslist, vector_begin(pvec), vector_end(pvec));
    assert_true(slist_size(pslist) == 10);
    for(it = slist_begin(pslist); !iterator_equal(it, slist_end(pslist)); it = iterator_next(it))
    {
        assert_true(*(int*)iterator_get_pointer(it) == -33);
    }

    slist_destroy(pslist);
    vector_destroy(pvec);
}

/*
 * test slist_init_copy_array
 */
UT_CASE_DEFINATION(slist_init_copy_array)
void test_slist_init_copy_array__null_slist_container(void** state)
{
    int an_array[10] = {0};
    slist_t* pslist_dest = create_slist(int);

    expect_assert_failure(slist_init_copy_array(NULL, an_array, 10))

    slist_destroy(pslist_dest);
}

void test_slist_init_copy_array__non_created_slist_container(void** state)
{
    int an_array[10] = {0};
    slist_t* pslist_dest = create_slist(int);

    pslist_dest->_t_head._pt_next = (_slistnode_t*)0x9999;
    expect_assert_failure(slist_init_copy_array(pslist_dest, an_array, 10));

    pslist_dest->_t_head._pt_next = NULL;
    slist_destroy(pslist_dest);
}

void test_slist_init_copy_array__invalid_array(void** state)
{
    int an_array[10] = {0};
    slist_t* pslist_dest = create_slist(int);

    expect_assert_failure(slist_init_copy_array(pslist_dest, NULL, 10));

    slist_destroy(pslist_dest);
}

void test_slist_init_copy_array__init_copy_array_empty(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    int an_array[10] = {0};

    slist_init_copy_array(pslist_dest, an_array, 0);
    assert_true(_slist_is_inited(pslist_dest));
    assert_true(slist_size(pslist_dest) == 0);

    slist_destroy(pslist_dest);
}

void test_slist_init_copy_array__c_builtin(void** state)
{
    int an_array[10] = {0};
    size_t i = 0;
    slist_iterator_t it_dest;
    slist_t* pslist_dest = create_slist(int);

    for (i = 0; i < 10; ++i) {
        an_array[i] = i;
    }
    slist_init_copy_array(pslist_dest, an_array, 10);
    assert_true(_slist_is_inited(pslist_dest));
    assert_true(slist_size(pslist_dest) == 10);
    for(it_dest = slist_begin(pslist_dest), i = 0;
        !iterator_equal(it_dest, slist_end(pslist_dest)) && i < 10;
        it_dest = iterator_next(it_dest), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_dest) == an_array[i]);
    }

    slist_destroy(pslist_dest);
}

void test_slist_init_copy_array__cstr(void** state)
{
    const char* as_array[] = {
        "abc", "def", "ssss", "long", "lskdjfas"
    };
    int i = 0;
    slist_iterator_t it_dest;
    slist_t* pslist_dest = create_slist(char*);

    slist_init_copy_array(pslist_dest, as_array, 5);
    assert_true(_slist_is_inited(pslist_dest));
    assert_true(slist_size(pslist_dest) == 5);
    for(it_dest = slist_begin(pslist_dest), i = 0;
        !iterator_equal(it_dest, slist_end(pslist_dest)) && i < 5;
        it_dest = iterator_next(it_dest), ++i)
    {
        assert_true(strcmp((char*)iterator_get_pointer(it_dest), as_array[i]) == 0);
    }

    slist_destroy(pslist_dest);
}

void test_slist_init_copy_array__libcstl_builtin(void** state)
{
    slist_t* apslist_array[10] = {NULL};
    int i = 0;
    slist_iterator_t it_dest;
    slist_t* pslist_dest = create_slist(slist_t<int>);

    for (i = 0; i < 10; ++i) {
        apslist_array[i] = create_slist(int);
        slist_init_elem(apslist_array[i], i, i);
    }
    slist_init_copy_array(pslist_dest, apslist_array, 10);
    assert_true(_slist_is_inited(pslist_dest));
    assert_true(slist_size(pslist_dest) == 10);
    for(it_dest = slist_begin(pslist_dest), i = 0;
        !iterator_equal(it_dest, slist_end(pslist_dest)) && i < 10;
        it_dest = iterator_next(it_dest), ++i)
    {
        assert_true(slist_equal((slist_t*)iterator_get_pointer(it_dest), apslist_array[i]));
    }
    for (i = 0; i < 10; ++i) {
        slist_destroy(apslist_array[i]);
    }

    slist_destroy(pslist_dest);
}

typedef struct _tag_test_slist_init_copy_array__user_define
{
    int n_elem;
}_test_slist_init_copy_array__user_define_t;
void test_slist_init_copy_array__user_define(void** state)
{
    _test_slist_init_copy_array__user_define_t* apt_array[10] = {NULL};
    int i = 0;
    slist_iterator_t it_dest;
    slist_t* pslist_dest = NULL;

    for (i = 0; i < 10; ++i) {
        apt_array[i] = malloc(sizeof(_test_slist_init_copy_array__user_define_t));
        apt_array[i]->n_elem = i;
    }
    type_register(_test_slist_init_copy_array__user_define_t, NULL, NULL, NULL, NULL);
    type_duplicate(_test_slist_init_copy_array__user_define_t, struct _tag_test_slist_init_copy_array__user_define);
    pslist_dest = create_slist(_test_slist_init_copy_array__user_define_t);

    slist_init_copy_array(pslist_dest, apt_array, 10);
    assert_true(_slist_is_inited(pslist_dest));
    assert_true(slist_size(pslist_dest) == 10);
    for(it_dest = slist_begin(pslist_dest), i = 0;
        !iterator_equal(it_dest, slist_end(pslist_dest)) && i < 10;
        it_dest = iterator_next(it_dest), ++i)
    {
        assert_true(
            ((_test_slist_init_copy_array__user_define_t*)iterator_get_pointer(it_dest))->n_elem == apt_array[i]->n_elem);
    }

    slist_destroy(pslist_dest);
    for (i = 0; i < 10; ++i) {
        free(apt_array[i]);
    }
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
    expect_assert_failure(slist_equal(pslist_first, pslist_second));

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
    expect_assert_failure(slist_not_equal(pslist_first, pslist_second));

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

void test_slist_assign_range__other_container_range(void** state)
{
    slist_t* pslist = create_slist(int);
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;

    slist_init_elem(pslist, 10, 10);
    vector_init_elem(pvec, 100, 100);
    assert_true(slist_size(pslist) == 10);
    slist_assign_range(pslist, vector_begin(pvec), vector_end(pvec));
    assert_true(slist_size(pslist) == 100);
    for(it_iter = slist_begin(pslist); !iterator_equal(it_iter, slist_end(pslist)); it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    slist_destroy(pslist);
    vector_destroy(pvec);
}

/*
 * test slist_assign_array
 */
UT_CASE_DEFINATION(slist_assign_array)
void test_slist_assign_array__null_slist_container(void** state)
{
    int an_array[10] = {0};

    expect_assert_failure(slist_assign_array(NULL, an_array, 0));
}

void test_slist_assign_array__non_inited(void** state)
{
    int an_array[10] = {0};
    slist_t* pslist_dest = create_slist(int);

    pslist_dest->_t_typeinfo._t_style = 4324;
    expect_assert_failure(slist_assign_array(pslist_dest, an_array, 10));

    pslist_dest->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_dest);
}

void test_slist_assign_array__invalid_array(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_init(pslist_dest);

    expect_assert_failure(slist_assign_array(pslist_dest, NULL, 10));

    slist_destroy(pslist_dest);
}

void test_slist_assign_array__0_assign_array_0(void** state)
{
    int an_array[10] = {0};
    size_t i = 0;
    slist_t* pslist_dest = create_slist(int);
    slist_init(pslist_dest);

    slist_assign_array(pslist_dest, an_array, 0);
    assert_true(slist_size(pslist_dest) == 0);

    slist_destroy(pslist_dest);
}

void test_slist_assign_array__0_assign_array_10(void** state)
{
    int an_array[10] = {0};
    int i = 0;
    slist_iterator_t it_iter;
    slist_t* pslist_dest = create_slist(int);
    slist_init(pslist_dest);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    slist_assign_array(pslist_dest, an_array, 10);
    assert_true(slist_size(pslist_dest) == 10);
    for(it_iter = slist_begin(pslist_dest);
        !iterator_equal(it_iter, slist_end(pslist_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    slist_destroy(pslist_dest);
}

void test_slist_assign_array__10_assign_array_0(void** state)
{
    int an_array[10] = {0};
    slist_iterator_t it_iter;
    slist_t* pslist_dest = create_slist(int);
    slist_init_elem(pslist_dest, 10, 700);

    slist_assign_array(pslist_dest, an_array, 0);
    assert_true(slist_size(pslist_dest) == 0);
    for(it_iter = slist_begin(pslist_dest);
        !iterator_equal(it_iter, slist_end(pslist_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    slist_destroy(pslist_dest);
}

void test_slist_assign_array__10_assign_array_10_same_elem(void** state)
{
    int an_array[10] = {0};
    int i = 0;
    slist_iterator_t it_iter;
    slist_t* pslist_dest = create_slist(int);
    slist_init_elem(pslist_dest, 10, 100);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    slist_assign_array(pslist_dest, an_array, 10);
    assert_true(slist_size(pslist_dest) == 10);
    for(it_iter = slist_begin(pslist_dest);
        !iterator_equal(it_iter, slist_end(pslist_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    slist_destroy(pslist_dest);
}

void test_slist_assign_array__10_assign_array_10_not_same_elem(void** state)
{
    int an_array[10] = {0};
    int i = 0;
    slist_iterator_t it_iter;
    slist_t* pslist_dest = create_slist(int);
    slist_init_elem(pslist_dest, 10, 0);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    slist_assign_array(pslist_dest, an_array, 10);
    assert_true(slist_size(pslist_dest) == 10);
    for(it_iter = slist_begin(pslist_dest);
        !iterator_equal(it_iter, slist_end(pslist_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    slist_destroy(pslist_dest);
}

void test_slist_assign_array__10_assign_array_1000(void** state)
{
    int an_array[1000] = {0};
    int i = 0;
    slist_iterator_t it_iter;
    slist_t* pslist_dest = create_slist(int);
    slist_init_elem(pslist_dest, 10, 0);


    for (i = 0; i < 1000; ++i) {
        an_array[i] = 100;
    }
    slist_assign_array(pslist_dest, an_array, 1000);
    assert_true(slist_size(pslist_dest) == 1000);
    for(it_iter = slist_begin(pslist_dest);
        !iterator_equal(it_iter, slist_end(pslist_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    slist_destroy(pslist_dest);
}

void test_slist_assign_array__cstr(void** state)
{
    const char* as_array[] = {
        "abc", "def", "ghi", "jkl", "mno"
    };
    int i = 0;
    slist_t* pslist = create_slist(char*);
    iterator_t it_iter;

    slist_init_elem(pslist, 10, "xxxx");
    assert_true(slist_size(pslist) == 10);
    slist_assign_array(pslist, as_array, 5);
    assert_true(slist_size(pslist) == 5);
    for (it_iter = slist_begin(pslist), i = 0;
         !iterator_equal(it_iter, slist_end(pslist));
         it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(strcmp((char*)iterator_get_pointer(it_iter), as_array[i]) == 0);
    }

    slist_destroy(pslist);
}

void test_slist_assign__cstl(void** state)
{
    vector_t* apvec_array[10] = {NULL};
    slist_iterator_t it;
    slist_t* pslist = create_slist(vector_t<int>);
    size_t i = 0;

    for (i = 0; i < 10; ++i) {
        apvec_array[i] = create_vector(int);
        vector_init_elem(apvec_array[i], i, i);
    }
    slist_init_n(pslist, 100);
    slist_assign_array(pslist, apvec_array, 10);
    assert_true(slist_size(pslist) == 10);
    for (it = slist_begin(pslist), i = 0;
         !iterator_equal(it, slist_end(pslist));
         it = iterator_next(it), ++i) {
        assert_true(vector_equal(iterator_get_pointer(it), apvec_array[i]));
    }

    slist_destroy(pslist);
    for (i = 0; i < 10; ++i) {
        vector_destroy(apvec_array[i]);
    }
}

typedef struct _test_slist_assign_array {
    int n_elem;
}_test_slist_assign_array_t;
void test_slist_assign_array__user_define(void** state)
{
    _test_slist_assign_array_t* apt_array[10] = {NULL};
    size_t i = 0;
    slist_t* pslist = NULL;
    slist_iterator_t it;

    type_register(_test_slist_assign_array_t, NULL, NULL, NULL, NULL);
    pslist = create_slist(_test_slist_assign_array_t);
    slist_init_n(pslist, 50);
    for (i = 0; i < 10; ++i) {
        apt_array[i] = malloc(sizeof(_test_slist_assign_array_t));
        apt_array[i]->n_elem = i;
    }

    slist_assign_array(pslist, apt_array, 10);
    assert_true(slist_size(pslist) == 10);
    for (it = slist_begin(pslist), i = 0;
         !iterator_equal(it, slist_end(pslist));
         it = iterator_next(it), ++i) {
        assert_true(((_test_slist_assign_array_t*)iterator_get_pointer(it))->n_elem == apt_array[i]->n_elem);
    }

    slist_destroy(pslist);
    for (i = 0; i < 10; ++i) {
        free(apt_array[i]);
    }
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
    assert_true((_slistnode_t*)it_begin._t_pos._pby_corepos == pslist->_t_head._pt_next);
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
    assert_true(it_end._t_pos._pby_corepos == NULL);

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
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    expect_assert_failure(slist_previous(pslist, slist_end(pslist)));

    slist_destroy(pslist);
}

void test_slist_previous__non_empty_begin(void** state)
{
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
    it_pos._t_pos._pby_corepos = (_byte_t*)0x8888;

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

void test_slist_insert_range__other_container_range(void** state)
{
    slist_t* pslist = create_slist(int);
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;
    int i = 0;

    slist_init_n(pslist, 10);
    vector_init_elem(pvec, 10, 10);
    assert_true(slist_size(pslist) == 10);
    slist_insert_range(pslist, slist_begin(pslist), vector_begin(pvec), vector_end(pvec));
    assert_true(slist_size(pslist) == 20);
    for(it_iter = slist_begin(pslist); !iterator_equal(it_iter, slist_end(pslist)); it_iter = iterator_next(it_iter), ++i)
    {
        if(i < 10)
        {
            assert_true(*(int*)iterator_get_pointer(it_iter) == 10);
        }
        else
        {
            assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
        }
    }

    slist_destroy(pslist);
    vector_destroy(pvec);
}

/*
 * test slist_insert_array
 */
UT_CASE_DEFINATION(slist_insert_array)
void test_slist_insert_array__null_slist_container(void** state)
{
    int an_array[10] = {0};
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    expect_assert_failure(slist_insert_array(NULL, slist_begin(pslist), an_array, 10));

    slist_destroy(pslist);
}

void test_slist_insert_array__non_inited(void** state)
{
    int an_array[10] = {0};
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    pslist->_t_typeinfo._t_style = 2323;
    expect_assert_failure(slist_insert_array(pslist, slist_begin(pslist), an_array, 10));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test_slist_insert_array__invalid_position(void** state)
{
    int an_array[10] = {0};
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);
    it_pos = slist_begin(pslist);
    it_pos._t_pos._pby_corepos = (_byte_t*)0x8888;

    expect_assert_failure(slist_insert_array(pslist, it_pos, an_array, 10));

    slist_destroy(pslist);
}

void test_slist_insert_array__invalid_array(void** state)
{
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);
    it_pos = slist_begin(pslist);

    expect_assert_failure(slist_insert_array(pslist, it_pos, NULL, 10));

    slist_destroy(pslist);
}

void test_slist_insert_array__empty_insert_0(void** state)
{
    int an_array[10] = {0};
    slist_iterator_t it_pos;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    assert_true(slist_size(pslist) == 0);
    it_pos = slist_begin(pslist);
    slist_insert_array(pslist, it_pos, an_array, 0);
    assert_true(slist_size(pslist) == 0);

    slist_destroy(pslist);
}

void test_slist_insert_array__empty_insert_10(void** state)
{
    int an_array[10] = {0};
    int i = 0;
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    assert_true(slist_size(pslist) == 0);
    it_pos = slist_begin(pslist);
    slist_insert_array(pslist, it_pos, an_array, 10);
    assert_true(slist_size(pslist) == 10);
    for(it_iter = slist_begin(pslist);
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    slist_destroy(pslist);
}

void test_slist_insert_array__begin_insert_0(void** state)
{
    int an_array[10] = {0};
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 1000);

    assert_true(slist_size(pslist) == 1000);
    it_pos = slist_begin(pslist);
    slist_insert_array(pslist, it_pos, an_array, 0);
    assert_true(slist_size(pslist) == 1000);
    for(it_iter = slist_begin(pslist);
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist);
}

void test_slist_insert_array__begin_insert_10(void** state)
{
    int an_array[10] = {0};
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 1000);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    assert_true(slist_size(pslist) == 1000);
    it_pos = slist_begin(pslist);
    slist_insert_array(pslist, it_pos, an_array, 10);
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
}

void test_slist_insert_array__middle_insert_0(void** state)
{
    int an_array[10] = {0};
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 1000);

    assert_true(slist_size(pslist) == 1000);
    it_pos = iterator_advance(slist_begin(pslist), 300);
    slist_insert_array(pslist, it_pos, an_array, 0);
    assert_true(slist_size(pslist) == 1000);
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist);
}

void test_slist_insert_array__middle_insert_10(void** state)
{
    int an_array[10] = {0};
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 1000);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    assert_true(slist_size(pslist) == 1000);
    it_pos = iterator_advance(slist_begin(pslist), 300);
    slist_insert_array(pslist, it_pos, an_array, 10);
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
}

void test_slist_insert_array__end_insert_0(void** state)
{
    int an_array[10] = {0};
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 1000);

    assert_true(slist_size(pslist) == 1000);
    it_pos = slist_end(pslist);
    slist_insert_array(pslist, it_pos, an_array, 0);
    assert_true(slist_size(pslist) == 1000);
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist);
}

void test_slist_insert_array__end_insert_10(void** state)
{
    int an_array[10] = {0};
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 1000);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    assert_true(slist_size(pslist) == 1000);
    it_pos = slist_end(pslist);
    slist_insert_array(pslist, it_pos, an_array, 10);
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
}

void test_slist_insert_array__cstr(void** state)
{
    const char* as_array[] = {
        "abc", "def", "hij", "klmn", "xyz"
    };
    slist_t* pslist = create_slist(char*);
    slist_iterator_t it;
    int i = 0;

    slist_init_elem(pslist, 10, "xxxx");
    slist_insert_array(pslist, slist_begin(pslist), as_array, 5);
    assert_true(slist_size(pslist) == 15);
    for (it = slist_begin(pslist), i = 0;
         !iterator_equal(it, slist_end(pslist));
         it = iterator_next(it), ++i) {
        if (i < 5) {
            assert_true(strcmp((char*)iterator_get_pointer(it), as_array[i]) == 0);
        } else {
            assert_true(strcmp((char*)iterator_get_pointer(it), "xxxx") == 0);
        }
    }

    slist_destroy(pslist);
}

void test_slist_insert_array__cstl(void** state)
{
    deque_t* apdeq_array[10] = {NULL};
    slist_t* pslist = create_slist(deque_t<int>);
    slist_iterator_t it;
    int i = 0;

    slist_init(pslist);
    for (i = 0; i < 10; ++i) {
        apdeq_array[i] = create_deque(int);
        deque_init_elem(apdeq_array[i], i, i);
    }

    slist_insert_array(pslist, slist_begin(pslist), apdeq_array, 10);
    assert_true(slist_size(pslist) == 10);
    for (it = slist_begin(pslist), i = 0;
         !iterator_equal(it, slist_end(pslist));
         it = iterator_next(it), ++i) {
        assert_true(deque_equal(iterator_get_pointer(it), apdeq_array[i]));
    }

    slist_destroy(pslist);
    for (i = 0; i < 10; ++i) {
        deque_destroy(apdeq_array[i]);
    }
}

typedef struct _test_slist_insert_array {
    int n_elem;
}_test_slist_insert_array_t;
void test_slist_insert_array__user_define(void** state)
{
    _test_slist_insert_array_t* apt_array[10] = {NULL};
    slist_t* pslist = NULL;
    slist_iterator_t it;
    int i = 0;

    type_register(_test_slist_insert_array_t, NULL, NULL, NULL, NULL);
    pslist = create_slist(_test_slist_insert_array_t);
    for (i = 0; i < 10; ++i) {
        apt_array[i] = malloc(sizeof(_test_slist_insert_array_t));
        apt_array[i]->n_elem = i;
    }
    slist_init(pslist);
    slist_insert_array(pslist, slist_begin(pslist), apt_array, 10);
    assert_true(slist_size(pslist) == 10);
    for (it = slist_begin(pslist), i = 0;
         !iterator_equal(it, slist_end(pslist));
         it = iterator_next(it), ++i) {
        assert_true(((_test_slist_insert_array_t*)iterator_get_pointer(it))->n_elem == apt_array[i]->n_elem);
    }

    slist_destroy(pslist);
    for (i = 0; i < 10; ++i) {
        free(apt_array[i]);
    }
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
    it_pos._t_pos._pby_corepos = (_byte_t*)0x8888;

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

void test_slist_insert_after_range__other_container_range(void** state)
{
    slist_t* pslist = create_slist(int);
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;
    int i = 0;

    slist_init_n(pslist, 10);
    vector_init_elem(pvec, 100, 100);
    assert_true(slist_size(pslist) == 10);
    slist_insert_after_range(pslist, slist_begin(pslist), vector_begin(pvec), vector_end(pvec));
    assert_true(slist_size(pslist) == 110);
    for(it_iter = slist_begin(pslist); !iterator_equal(it_iter, slist_end(pslist)); it_iter = iterator_next(it_iter), ++i)
    {
        if(i > 0 && i < 101)
        {
            assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
        }
        else
        {
            assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
        }
    }

    slist_destroy(pslist);
    vector_destroy(pvec);
}

/*
 * test slist_insert_after_array
 */
UT_CASE_DEFINATION(slist_insert_after_array)
void test_slist_insert_after_array__null_slist_container(void** state)
{
    int an_array[10] = {0};
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    expect_assert_failure(slist_insert_after_array(NULL, slist_begin(pslist), an_array, 10));

    slist_destroy(pslist);
}

void test_slist_insert_after_array__non_inited(void** state)
{
    int an_array[10] = {0};
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    pslist->_t_typeinfo._t_style = 2323;
    expect_assert_failure(slist_insert_after_array(pslist, slist_begin(pslist), an_array, 10));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test_slist_insert_after_array__invalid_position(void** state)
{
    int an_array[10] = {0};
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);
    it_pos = slist_begin(pslist);
    it_pos._t_pos._pby_corepos = (_byte_t*)0x8888;

    expect_assert_failure(slist_insert_after_array(pslist, it_pos, an_array, 10));

    slist_destroy(pslist);
}

void test_slist_insert_after_array__invalid_array(void** state)
{
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);
    it_pos = slist_begin(pslist);

    expect_assert_failure(slist_insert_after_array(pslist, it_pos, NULL, 10));

    slist_destroy(pslist);
}

void test_slist_insert_after_array__begin_insert_0(void** state)
{
    int an_array[10] = {0};
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 1000);

    assert_true(slist_size(pslist) == 1000);
    it_pos = slist_begin(pslist);
    slist_insert_after_array(pslist, it_pos, an_array, 0);
    assert_true(slist_size(pslist) == 1000);
    for(it_iter = slist_begin(pslist);
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist);
}

void test_slist_insert_after_array__begin_insert_10(void** state)
{
    int an_array[10] = {0};
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 1000);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    assert_true(slist_size(pslist) == 1000);
    it_pos = slist_begin(pslist);
    slist_insert_after_array(pslist, it_pos, an_array, 10);
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
}

void test_slist_insert_after_array__middle_insert_0(void** state)
{
    int an_array[10] = {0};
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 1000);

    assert_true(slist_size(pslist) == 1000);
    it_pos = iterator_advance(slist_begin(pslist), 300);
    slist_insert_after_array(pslist, it_pos, an_array, 0);
    assert_true(slist_size(pslist) == 1000);
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist);
}

void test_slist_insert_after_array__middle_insert_10(void** state)
{
    int an_array[10] = {0};
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 1000);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    assert_true(slist_size(pslist) == 1000);
    it_pos = iterator_advance(slist_begin(pslist), 300);
    slist_insert_after_array(pslist, it_pos, an_array, 10);
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
}

void test_slist_insert_after_array__end_insert_0(void** state)
{
    int an_array[10] = {0};
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 1000);

    assert_true(slist_size(pslist) == 1000);
    it_pos = slist_previous(pslist, slist_end(pslist));
    slist_insert_after_array(pslist, it_pos, an_array, 0);
    assert_true(slist_size(pslist) == 1000);
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist);
}

void test_slist_insert_after_array__end_insert_10(void** state)
{
    int an_array[10] = {0};
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 1000);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    assert_true(slist_size(pslist) == 1000);
    it_pos = slist_previous(pslist, slist_end(pslist));
    slist_insert_after_array(pslist, it_pos, an_array, 10);
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
}

void test_slist_insert_after_array__cstr(void** state)
{
    const char* as_array[] = {
        "Linux", "abc", "Windows", "aaaaa", "qq", "xxxxx"
    };
    slist_t* pslist = create_slist(char*);
    iterator_t it_iter;
    int i = 0;

    slist_init_n(pslist, 10);
    assert_true(slist_size(pslist) == 10);
    slist_insert_after_array(pslist, slist_begin(pslist), as_array, 6);
    assert_true(slist_size(pslist) == 16);
    for(it_iter = slist_begin(pslist), i = 0; !iterator_equal(it_iter, slist_end(pslist)); it_iter = iterator_next(it_iter), ++i)
    {
        if(i > 0 && i <= 6)
        {
            assert_true(strcmp((char*)iterator_get_pointer(it_iter), as_array[i-1]) == 0);
        }
        else
        {
            assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
        }
    }

    slist_destroy(pslist);
}

void test_slist_insert_after_array__cstl(void** state)
{
    vector_t* apvec_array[10] = {NULL};
    slist_t* pslist = create_slist(vector_t<int>);
    slist_iterator_t it;
    size_t i = 0;

    for (i = 0; i < 10; ++i) {
        apvec_array[i] = create_vector(int);
        vector_init_elem(apvec_array[i], i, i);
    }
    slist_init_n(pslist, 10);
    slist_insert_after_array(pslist, slist_begin(pslist), apvec_array, 10);
    assert_true(slist_size(pslist) == 20);
    for (it = slist_begin(pslist), i = 0;
        !iterator_equal(it, slist_end(pslist));
        it = iterator_next(it), ++i) {
            if (i > 0 && i <= 10) {
                assert_true(vector_equal(iterator_get_pointer(it), apvec_array[i-1]));
            } else {
                assert_true(vector_empty(iterator_get_pointer(it)));
            }
    }

    slist_destroy(pslist);
    for (i = 0; i < 10; ++i) {
        vector_destroy(apvec_array[i]);
    }
}

typedef struct _test_slist_insert_after_array__user_define {
    int n_elem;
}_test_slist_insert_after_array__user_define_t;
void test_slist_insert_after_array__user_define(void** state)
{
    _test_slist_insert_after_array__user_define_t* apt_array[10] = {NULL};
    slist_t* pslist = NULL;
    slist_iterator_t it;
    size_t i = 0;

    type_register(_test_slist_insert_after_array__user_define_t, NULL, NULL, NULL, NULL);
    pslist = create_slist(_test_slist_insert_after_array__user_define_t);
    slist_init_n(pslist, 10);
    for (i = 0; i < 10; ++i) {
        apt_array[i] = malloc(sizeof(_test_slist_insert_after_array__user_define_t));
        apt_array[i]->n_elem = 100;
    }
    slist_insert_after_array(pslist, slist_begin(pslist), apt_array, 10);
    assert_true(slist_size(pslist) == 20);
    for (it = slist_begin(pslist), i = 0;
         !iterator_equal(it, slist_end(pslist));
         it = iterator_next(it), ++i) {
             if (i > 0 && i <= 10) {
                assert_true(((_test_slist_insert_after_array__user_define_t*)iterator_get_pointer(it))->n_elem == apt_array[i-1]->n_elem);
             } else {
                 assert_true(((_test_slist_insert_after_array__user_define_t*)iterator_get_pointer(it))->n_elem == 0);
             }
    }

    for (i = 0; i < 10; ++i) {
        free(apt_array[i]);
    }
    slist_destroy(pslist);
}

/*
 * test slist_pop_front
 */
UT_CASE_DEFINATION(slist_pop_front)
void test_slist_pop_front__null_slist_container(void** state)
{
    expect_assert_failure(slist_pop_front(NULL));
}

void test_slist_pop_front__non_inited_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    pslist->_t_typeinfo._t_style = 4444;
    expect_assert_failure(slist_pop_front(pslist));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test_slist_pop_front__empty(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    expect_assert_failure(slist_pop_front(pslist));

    slist_destroy(pslist);
}

void test_slist_pop_front__successfully(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);
    assert_true(*(int*)slist_front(pslist) == 9);
    slist_pop_front(pslist);
    assert_true(slist_size(pslist) == t_oldsize - 1);
    assert_true(*(int*)slist_front(pslist) == 8);

    slist_destroy(pslist);
}

/*
 * test slist_erase
 */
UT_CASE_DEFINATION(slist_erase)
void test_slist_erase__null_slist_container(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_pos = slist_begin(pslist);
    expect_assert_failure(slist_erase(NULL, it_pos));

    slist_destroy(pslist);
}

void test_slist_erase__non_inited_slist_container(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    t_oldsize = slist_size(pslist);

    it_pos = slist_begin(pslist);
    pslist->_t_typeinfo._t_style = 5555;
    expect_assert_failure(slist_erase(pslist, it_pos));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test_slist_erase__invalid_pos_end(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_pos = slist_end(pslist);
    expect_assert_failure(slist_erase(pslist, it_pos));

    slist_destroy(pslist);
}

void test_slist_erase__invalid_pos(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_pos = slist_end(pslist);
    it_pos._t_pos._pby_corepos = (_byte_t*)0x999;
    expect_assert_failure(slist_erase(pslist, it_pos));

    slist_destroy(pslist);
}

void test_slist_erase__successfully_begin(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_pos = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 9);
    it_iter = slist_erase(pslist, it_pos);
    assert_true(slist_size(pslist) == t_oldsize - 1);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);

    slist_destroy(pslist);
}

void test_slist_erase__successfully_middle(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_pos = iterator_next(slist_begin(pslist));
    assert_true(*(int*)iterator_get_pointer(it_pos) == 8);
    it_iter = slist_erase(pslist, it_pos);
    assert_true(slist_size(pslist) == t_oldsize - 1);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);

    slist_destroy(pslist);
}

void test_slist_erase__successfully_back(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_pos = slist_previous(pslist, slist_end(pslist));
    assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
    it_iter = slist_erase(pslist, it_pos);
    assert_true(slist_size(pslist) == t_oldsize - 1);
    assert_true(iterator_equal(it_iter, slist_end(pslist)));

    slist_destroy(pslist);
}

/*
 * test slist_erase_range
 */
UT_CASE_DEFINATION(slist_erase_range)
void test_slist_erase_range__null_slist_container(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    slist_iterator_t it_begin = _create_slist_iterator();
    slist_iterator_t it_end = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);
    expect_assert_failure(slist_erase_range(NULL, it_begin, it_end));

    slist_destroy(pslist);
}

void test_slist_erase_range__non_inited_slist_container(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    slist_iterator_t it_begin = _create_slist_iterator();
    slist_iterator_t it_end = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);
    pslist->_t_typeinfo._t_style = 5566;
    expect_assert_failure(slist_erase_range(pslist, it_begin, it_end));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test_slist_erase_range__invalid_range_not_belong_to_slist(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    slist_iterator_t it_begin = _create_slist_iterator();
    slist_iterator_t it_end = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    expect_assert_failure(slist_erase_range(pslist, it_begin, it_end));

    slist_destroy(pslist);
}

void test_slist_erase_range__invalid_range(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    slist_iterator_t it_begin = _create_slist_iterator();
    slist_iterator_t it_end = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);
    expect_assert_failure(slist_erase_range(pslist, it_end, it_begin));

    slist_destroy(pslist);
}

void test_slist_erase_range__successfully_empty(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_erasesize = 0;
    slist_iterator_t it_begin = _create_slist_iterator();
    slist_iterator_t it_end = _create_slist_iterator();
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);
    it_iter = slist_erase_range(pslist, it_begin, it_begin);
    assert_true(slist_size(pslist) == t_oldsize - t_erasesize);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);

    slist_destroy(pslist);
}

void test_slist_erase_range__successfully_begin(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_erasesize = 0;
    slist_iterator_t it_begin = _create_slist_iterator();
    slist_iterator_t it_end = _create_slist_iterator();
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_begin = slist_begin(pslist);
    it_end = iterator_advance(it_begin, 3);
    t_erasesize = iterator_distance(it_begin, it_end);
    it_iter = slist_erase_range(pslist, it_begin, it_end);
    assert_true(slist_size(pslist) == t_oldsize - t_erasesize);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);

    slist_destroy(pslist);
}

void test_slist_erase_range__successfully_middle(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_erasesize = 0;
    slist_iterator_t it_begin = _create_slist_iterator();
    slist_iterator_t it_end = _create_slist_iterator();
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_begin = iterator_advance(slist_begin(pslist), 3);
    it_end = iterator_advance(it_begin, 3);
    t_erasesize = iterator_distance(it_begin, it_end);
    it_iter = slist_erase_range(pslist, it_begin, it_end);
    assert_true(slist_size(pslist) == t_oldsize - t_erasesize);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);

    slist_destroy(pslist);
}

void test_slist_erase_range__successfully_end(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_erasesize = 0;
    slist_iterator_t it_begin = _create_slist_iterator();
    slist_iterator_t it_end = _create_slist_iterator();
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_begin = iterator_advance(slist_begin(pslist), 6);
    it_end = slist_end(pslist);
    t_erasesize = iterator_distance(it_begin, it_end);
    it_iter = slist_erase_range(pslist, it_begin, it_end);
    assert_true(slist_size(pslist) == t_oldsize - t_erasesize);
    assert_true(iterator_equal(it_iter, slist_end(pslist)));

    slist_destroy(pslist);
}

void test_slist_erase_range__successfully_all(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_erasesize = 0;
    slist_iterator_t it_begin = _create_slist_iterator();
    slist_iterator_t it_end = _create_slist_iterator();
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);
    t_erasesize = iterator_distance(it_begin, it_end);
    it_iter = slist_erase_range(pslist, it_begin, it_end);
    assert_true(slist_size(pslist) == t_oldsize - t_erasesize);
    assert_true(slist_empty(pslist));
    assert_true(iterator_equal(it_iter, slist_end(pslist)));

    slist_destroy(pslist);
}

/*
 * test slist_erase_after
 */
UT_CASE_DEFINATION(slist_erase_after)
void test_slist_erase_after__null_slist_container(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_pos = slist_begin(pslist);
    expect_assert_failure(slist_erase_after(NULL, it_pos));

    slist_destroy(pslist);
}

void test_slist_erase_after__non_inited_slist_container(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    t_oldsize = slist_size(pslist);

    it_pos = slist_begin(pslist);
    pslist->_t_typeinfo._t_style = 5555;
    expect_assert_failure(slist_erase_after(pslist, it_pos));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test_slist_erase_after__invalid_pos_end(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_pos = slist_end(pslist);
    expect_assert_failure(slist_erase_after(pslist, it_pos));

    slist_destroy(pslist);
}

void test_slist_erase_after__invalid_pos(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_pos = slist_end(pslist);
    it_pos._t_pos._pby_corepos = (_byte_t*)0x999;
    expect_assert_failure(slist_erase_after(pslist, it_pos));

    slist_destroy(pslist);
}

void test_slist_erase_after__successfully_begin(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_pos = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 9);
    it_iter = slist_erase_after(pslist, it_pos);
    assert_true(slist_size(pslist) == t_oldsize - 1);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);

    slist_destroy(pslist);
}

void test_slist_erase_after__successfully_middle(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_pos = iterator_next(slist_begin(pslist));
    assert_true(*(int*)iterator_get_pointer(it_pos) == 8);
    it_iter = slist_erase_after(pslist, it_pos);
    assert_true(slist_size(pslist) == t_oldsize - 1);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);

    slist_destroy(pslist);
}

void test_slist_erase_after__successfully_back(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_pos = slist_previous(pslist, slist_end(pslist));
    it_pos = slist_previous(pslist, it_pos);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 1);
    it_iter = slist_erase_after(pslist, it_pos);
    assert_true(slist_size(pslist) == t_oldsize - 1);
    assert_true(iterator_equal(it_iter, slist_end(pslist)));

    slist_destroy(pslist);
}

void test_slist_erase_after__successfully_last(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    slist_iterator_t it_pos = _create_slist_iterator();
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_pos = slist_previous(pslist, slist_end(pslist));
    assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
    it_iter = slist_erase_after(pslist, it_pos);
    assert_true(slist_size(pslist) == t_oldsize);
    assert_true(iterator_equal(it_iter, slist_end(pslist)));

    slist_destroy(pslist);
}

/*
 * test slist_erase_after_range
 */
UT_CASE_DEFINATION(slist_erase_after_range)
void test_slist_erase_after_range__null_slist_container(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    slist_iterator_t it_begin = _create_slist_iterator();
    slist_iterator_t it_end = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);
    expect_assert_failure(slist_erase_after_range(NULL, it_begin, it_end));

    slist_destroy(pslist);
}

void test_slist_erase_after_range__non_inited_slist_container(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    slist_iterator_t it_begin = _create_slist_iterator();
    slist_iterator_t it_end = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);
    pslist->_t_typeinfo._t_style = 5566;
    expect_assert_failure(slist_erase_after_range(pslist, it_begin, it_end));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test_slist_erase_after_range__invalid_range_not_belong_to_slist(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    slist_iterator_t it_begin = _create_slist_iterator();
    slist_iterator_t it_end = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    expect_assert_failure(slist_erase_after_range(pslist, it_begin, it_end));

    slist_destroy(pslist);
}

void test_slist_erase_after_range__invalid_range_begin_is_slist_end(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    slist_iterator_t it_begin = _create_slist_iterator();
    slist_iterator_t it_end = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_begin = slist_end(pslist);
    it_end = slist_end(pslist);
    expect_assert_failure(slist_erase_after_range(pslist, it_begin, it_end));

    slist_destroy(pslist);
}

void test_slist_erase_after_range__invalid_range(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    slist_iterator_t it_begin = _create_slist_iterator();
    slist_iterator_t it_end = _create_slist_iterator();
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_begin = slist_begin(pslist);
    it_end = iterator_next(slist_begin(pslist));
    expect_assert_failure(slist_erase_after_range(pslist, it_end, it_begin));

    slist_destroy(pslist);
}

void test_slist_erase_after_range__successfully_empty(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_erasesize = 0;
    slist_iterator_t it_begin = _create_slist_iterator();
    slist_iterator_t it_end = _create_slist_iterator();
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);
    it_iter = slist_erase_after_range(pslist, it_begin, it_begin);
    assert_true(slist_size(pslist) == t_oldsize - t_erasesize);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);

    slist_destroy(pslist);
}

void test_slist_erase_after_range__successfully_empty_next(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_erasesize = 0;
    slist_iterator_t it_begin = _create_slist_iterator();
    slist_iterator_t it_end = _create_slist_iterator();
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_begin = slist_begin(pslist);
    it_end = iterator_next(it_begin);
    it_iter = slist_erase_after_range(pslist, it_begin, it_end);
    assert_true(slist_size(pslist) == t_oldsize - t_erasesize);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);

    slist_destroy(pslist);
}

void test_slist_erase_after_range__successfully_begin(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_erasesize = 0;
    slist_iterator_t it_begin = _create_slist_iterator();
    slist_iterator_t it_end = _create_slist_iterator();
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_begin = slist_begin(pslist);
    it_end = iterator_advance(it_begin, 3);
    t_erasesize = iterator_distance(it_begin, it_end);
    it_iter = slist_erase_after_range(pslist, it_begin, it_end);
    assert_true(slist_size(pslist) == t_oldsize - t_erasesize + 1);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);

    slist_destroy(pslist);
}

void test_slist_erase_after_range__successfully_middle(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_erasesize = 0;
    slist_iterator_t it_begin = _create_slist_iterator();
    slist_iterator_t it_end = _create_slist_iterator();
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_begin = iterator_advance(slist_begin(pslist), 3);
    it_end = iterator_advance(it_begin, 3);
    t_erasesize = iterator_distance(it_begin, it_end);
    it_iter = slist_erase_after_range(pslist, it_begin, it_end);
    assert_true(slist_size(pslist) == t_oldsize - t_erasesize + 1);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);

    slist_destroy(pslist);
}

void test_slist_erase_after_range__successfully_end(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_erasesize = 0;
    slist_iterator_t it_begin = _create_slist_iterator();
    slist_iterator_t it_end = _create_slist_iterator();
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_begin = iterator_advance(slist_begin(pslist), 6);
    it_end = slist_end(pslist);
    t_erasesize = iterator_distance(it_begin, it_end);
    it_iter = slist_erase_after_range(pslist, it_begin, it_end);
    assert_true(slist_size(pslist) == t_oldsize - t_erasesize + 1);
    assert_true(iterator_equal(it_iter, slist_end(pslist)));

    slist_destroy(pslist);
}

void test_slist_erase_after_range__successfully_all(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_erasesize = 0;
    slist_iterator_t it_begin = _create_slist_iterator();
    slist_iterator_t it_end = _create_slist_iterator();
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    t_oldsize = slist_size(pslist);

    it_begin = slist_begin(pslist);
    it_end = slist_end(pslist);
    t_erasesize = iterator_distance(it_begin, it_end);
    it_iter = slist_erase_after_range(pslist, it_begin, it_end);
    assert_true(slist_size(pslist) == 1);
    assert_true(iterator_equal(it_iter, slist_end(pslist)));
    assert_true(*(int*)slist_front(pslist) == 9);

    slist_destroy(pslist);
}

/*
 * test slist_remove_if
 */
UT_CASE_DEFINATION(slist_remove_if)

static void _test_slist_remove_if_ufun_op(const void* cpv_input, void* pv_output)
{
    if(*(int*)cpv_input == 3)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

void test_slist_remove_if__null_slist_container(void** state)
{
    expect_assert_failure(slist_remove_if(NULL, NULL));
}

void test_slist_remove_if__non_inited_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    pslist->_t_typeinfo._t_style = 4355;
    expect_assert_failure(slist_remove_if(pslist, NULL));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test_slist_remove_if__empty(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    slist_remove_if(pslist, _test_slist_remove_if_ufun_op);
    assert_true(slist_size(pslist) == 0);

    slist_destroy(pslist);
}

void test_slist_remove_if__non_empty_no_removed(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    slist_remove_if(pslist, _test_slist_remove_if_ufun_op);
    assert_true(slist_size(pslist) == 10);

    slist_destroy(pslist);
}

void test_slist_remove_if__non_empty_remove(void** state)
{
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 3);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 1);

    t_oldsize = slist_size(pslist);
    slist_remove_if(pslist, _test_slist_remove_if_ufun_op);
    assert_true(slist_size(pslist) == t_oldsize - 1);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    slist_destroy(pslist);
}

void test_slist_remove_if__non_empty_remove_more(void** state)
{
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 2);
    slist_push_front(pslist, 3);
    slist_push_front(pslist, 3);
    slist_push_front(pslist, 1);

    t_oldsize = slist_size(pslist);
    slist_remove_if(pslist, _test_slist_remove_if_ufun_op);
    assert_true(slist_size(pslist) == t_oldsize - 2);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    slist_destroy(pslist);
}

void test_slist_remove_if__non_empty_remove_all(void** state)
{
    size_t t_oldsize = 0;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 3);

    t_oldsize = slist_size(pslist);
    slist_remove_if(pslist, _test_slist_remove_if_ufun_op);
    assert_true(slist_size(pslist) == 0);

    slist_destroy(pslist);
}

void test_slist_remove_if__empty_default_ufun_op(void** state)
{
    size_t t_oldsize = 0;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);

    t_oldsize = slist_size(pslist);
    slist_remove_if(pslist, NULL);
    assert_true(slist_size(pslist) == 0);

    slist_destroy(pslist);
}

void test_slist_remove_if__non_empty_default_ufun_op(void** state)
{
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 2);
    slist_push_front(pslist, 3);
    slist_push_front(pslist, 3);
    slist_push_front(pslist, 1);

    t_oldsize = slist_size(pslist);
    slist_remove_if(pslist, NULL);
    assert_true(slist_size(pslist) == t_oldsize);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    slist_destroy(pslist);
}

static void _test_slist_remove_if_cstr_ufun_op(const void* cpv_input, void* pv_output)
{
    if(strcmp((char*)cpv_input, "AAAA") == 0)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}
void test_slist_remove_if__cstr_empty(void** state)
{
    slist_t* pslist = create_slist(char*);
    slist_init(pslist);

    slist_remove_if(pslist, _test_slist_remove_if_cstr_ufun_op);
    assert_true(slist_size(pslist) == 0);

    slist_destroy(pslist);
}

void test_slist_remove_if__cstr_non_empty_no_removed(void** state)
{
    slist_t* pslist = create_slist(char*);
    slist_init_n(pslist, 10);

    slist_remove_if(pslist, _test_slist_remove_if_cstr_ufun_op);
    assert_true(slist_size(pslist) == 10);

    slist_destroy(pslist);
}

void test_slist_remove_if__cstr_non_empty_remove(void** state)
{
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    slist_t* pslist = create_slist(char*);

    slist_init(pslist);
    slist_push_front(pslist, "abc");
    slist_push_front(pslist, "AAAA");
    slist_push_front(pslist, "def");
    slist_push_front(pslist, "hij");
    slist_push_front(pslist, "hij");

    t_oldsize = slist_size(pslist);
    slist_remove_if(pslist, _test_slist_remove_if_cstr_ufun_op);
    assert_true(slist_size(pslist) == t_oldsize - 1);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "hij") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "hij") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "def") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "abc") == 0);

    slist_destroy(pslist);
}

void test_slist_remove_if__cstr_non_empty_remove_more(void** state)
{
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    slist_t* pslist = create_slist(char*);

    slist_init(pslist);
    slist_push_front(pslist, "abc");
    slist_push_front(pslist, "AAAA");
    slist_push_front(pslist, "AAAA");
    slist_push_front(pslist, "hij");
    slist_push_front(pslist, "hij");

    t_oldsize = slist_size(pslist);
    slist_remove_if(pslist, _test_slist_remove_if_cstr_ufun_op);
    assert_true(slist_size(pslist) == t_oldsize - 2);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "hij") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "hij") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "abc") == 0);

    slist_destroy(pslist);
}

void test_slist_remove_if__cstr_non_empty_remove_all(void** state)
{
    size_t t_oldsize = 0;
    slist_t* pslist = create_slist(char*);

    slist_init_elem(pslist, 10, "AAAA");

    t_oldsize = slist_size(pslist);
    slist_remove_if(pslist, _test_slist_remove_if_cstr_ufun_op);
    assert_true(slist_size(pslist) == 0);

    slist_destroy(pslist);
}

/*
 * test slist_resize
 */
UT_CASE_DEFINATION(slist_resize)
void test_slist_resize__null_slist_container(void** state)
{
    expect_assert_failure(slist_resize(NULL, 10));
}

void test_slist_resize__non_inited(void** state)
{
    slist_t* pslist = create_slist(int);

    pslist->_t_typeinfo._t_style = 44444;
    expect_assert_failure(slist_resize(pslist, 10));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test_slist_resize__successfully_0_resize_0(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    assert_true(slist_size(pslist) == 0);
    slist_resize(pslist, 0);
    assert_true(slist_size(pslist) == 0);

    slist_destroy(pslist);
}

void test_slist_resize__successfully_0_resize_10(void** state)
{
    size_t i = 0;
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    assert_true(slist_size(pslist) == 0);
    slist_resize(pslist, 10);
    assert_true(slist_size(pslist) == 10);
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist);
}

void test_slist_resize__successfully_10_resize_0(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    assert_true(slist_size(pslist) == 10);
    slist_resize(pslist, 0);
    assert_true(slist_size(pslist) == 0);

    slist_destroy(pslist);
}

void test_slist_resize__successfully_10_resize_10(void** state)
{
    size_t i = 0;
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    assert_true(slist_size(pslist) == 10);
    slist_resize(pslist, 10);
    assert_true(slist_size(pslist) == 10);
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist);
}

void test_slist_resize__successfully_10_resize_1000(void** state)
{
    size_t i = 0;
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init_elem(pslist, 10, 100);

    assert_true(slist_size(pslist) == 10);
    slist_resize(pslist, 1000);
    assert_true(slist_size(pslist) == 1000);
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
}

/*
 * test slist_clear
 */
UT_CASE_DEFINATION(slist_clear)
void test_slist_clear__null_slist_container(void** state)
{
    expect_assert_failure(slist_clear(NULL));
}

void test_slist_clear__non_inited_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    pslist->_t_typeinfo._t_style = 2222;
    expect_assert_failure(slist_clear(pslist));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test_slist_clear__empty_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);

    slist_clear(pslist);
    assert_true(slist_size(pslist) == 0);

    slist_destroy(pslist);
}

void test_slist_clear__non_empty_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 198);

    slist_clear(pslist);
    assert_true(slist_size(pslist) == 0);

    slist_destroy(pslist);
}

/*
 * test slist_unique
 */
UT_CASE_DEFINATION(slist_unique)
void test_slist_unique__null_slist_container(void** state)
{
    expect_assert_failure(slist_unique(NULL));
}

void test_slist_unique__non_inited_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    pslist->_t_typeinfo._t_style = 443;
    expect_assert_failure(slist_unique(pslist));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test_slist_unique__empty(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_unique(pslist);
    assert_true(slist_empty(pslist));

    slist_destroy(pslist);
}

void test_slist_unique__non_empty_no_duplicate(void** state)
{
    size_t i = 0;
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, 9 - i);
    }
    slist_unique(pslist);
    assert_true(slist_size(pslist) == 10);
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == i);
    }

    slist_destroy(pslist);
}

void test_slist_unique__non_empty_adjacent_duplicate(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 2);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 9);
    slist_push_front(pslist, 9);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 3);
    slist_unique(pslist);
    assert_true(slist_size(pslist) == 5);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);

    slist_destroy(pslist);
}

void test_slist_unique__non_empty_not_adjacent_duplicate(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 2);
    slist_push_front(pslist, 9);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 9);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 3);
    slist_unique(pslist);
    assert_true(slist_size(pslist) == 6);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);

    slist_destroy(pslist);
}

void test_slist_unique__non_empty_all_duplicate(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 100);
    slist_unique(pslist);
    assert_true(slist_size(pslist) == 1);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 100);

    slist_destroy(pslist);
}

void test_slist_unique__cstr_non_empty_no_duplicate(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init(pslist);
    slist_push_front(pslist, "f");
    slist_push_front(pslist, "e");
    slist_push_front(pslist, "d");
    slist_push_front(pslist, "c");
    slist_push_front(pslist, "b");
    slist_push_front(pslist, "a");
    slist_unique(pslist);
    assert_true(slist_size(pslist) == 6);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "a") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "b") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "c") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "d") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "e") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "f") == 0);

    slist_destroy(pslist);
}

void test_slist_unique__cstr_non_empty_adjacent_duplicate(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init(pslist);
    slist_push_front(pslist, "f");
    slist_push_front(pslist, "e");
    slist_push_front(pslist, "d");
    slist_push_front(pslist, "b");
    slist_push_front(pslist, "b");
    slist_push_front(pslist, "a");
    slist_unique(pslist);
    assert_true(slist_size(pslist) == 5);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "a") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "b") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "d") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "e") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "f") == 0);

    slist_destroy(pslist);
}

void test_slist_unique__cstr_non_empty_not_adjacent_duplicate(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init(pslist);
    slist_push_front(pslist, "f");
    slist_push_front(pslist, "e");
    slist_push_front(pslist, "b");
    slist_push_front(pslist, "d");
    slist_push_front(pslist, "b");
    slist_push_front(pslist, "a");
    slist_unique(pslist);
    assert_true(slist_size(pslist) == 6);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "a") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "b") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "d") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "b") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "e") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "f") == 0);

    slist_destroy(pslist);
}

void test_slist_unique__cstr_non_empty_all_duplicate(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init_elem(pslist, 10, "a");
    slist_unique(pslist);
    assert_true(slist_size(pslist) == 1);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "a") == 0);

    slist_destroy(pslist);
}

/*
 * test slist_unique_if
 */
UT_CASE_DEFINATION(slist_unique_if)
void test_slist_unique_if__null_slist_container(void** state)
{
    expect_assert_failure(slist_unique_if(NULL, NULL));
}

void test_slist_unique_if__non_inited_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    pslist->_t_typeinfo._t_style = 4444;
    expect_assert_failure(slist_unique_if(pslist, NULL));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test_slist_unique_if__empty(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_unique_if(pslist, fun_equal_int);
    assert_true(slist_empty(pslist));

    slist_destroy(pslist);
}

void test_slist_unique_if__non_empty_non_duplicate(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 3);
    slist_unique_if(pslist, fun_equal_int);
    assert_true(slist_size(pslist) == 5);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    slist_destroy(pslist);
}

void test_slist_unique_if__non_empty_duplicate(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 3);
    slist_unique_if(pslist, fun_equal_int);
    assert_true(slist_size(pslist) == 4);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    slist_destroy(pslist);
}

void test_slist_unique_if__non_empty_more_duplicate(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 3);
    slist_unique_if(pslist, fun_equal_int);
    assert_true(slist_size(pslist) == 3);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);

    slist_destroy(pslist);
}

void test_slist_unique_if__non_empty_duplicate_not_adjacent(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 3);
    slist_unique_if(pslist, fun_equal_int);
    assert_true(slist_size(pslist) == 5);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);

    slist_destroy(pslist);
}

void test_slist_unique_if__non_empty_duplicate_all(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_elem(pslist, 10, 100);
    slist_unique_if(pslist, fun_equal_int);
    assert_true(slist_size(pslist) == 1);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 100);

    slist_destroy(pslist);
}

void test_slist_unique_if__cstr_non_empty_no_duplicate(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init(pslist);
    slist_push_front(pslist, "f");
    slist_push_front(pslist, "e");
    slist_push_front(pslist, "d");
    slist_push_front(pslist, "c");
    slist_push_front(pslist, "b");
    slist_push_front(pslist, "a");
    slist_unique_if(pslist, fun_equal_cstr);
    assert_true(slist_size(pslist) == 6);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "a") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "b") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "c") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "d") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "e") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "f") == 0);

    slist_destroy(pslist);
}

void test_slist_unique_if__cstr_non_empty_adjacent_duplicate(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init(pslist);
    slist_push_front(pslist, "f");
    slist_push_front(pslist, "e");
    slist_push_front(pslist, "d");
    slist_push_front(pslist, "b");
    slist_push_front(pslist, "b");
    slist_push_front(pslist, "a");
    slist_unique_if(pslist, fun_equal_cstr);
    assert_true(slist_size(pslist) == 5);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "a") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "b") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "d") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "e") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "f") == 0);

    slist_destroy(pslist);
}

void test_slist_unique_if__cstr_non_empty_not_adjacent_duplicate(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init(pslist);
    slist_push_front(pslist, "f");
    slist_push_front(pslist, "e");
    slist_push_front(pslist, "b");
    slist_push_front(pslist, "d");
    slist_push_front(pslist, "b");
    slist_push_front(pslist, "a");
    slist_unique_if(pslist, fun_equal_cstr);
    assert_true(slist_size(pslist) == 6);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "a") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "b") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "d") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "b") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "e") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "f") == 0);

    slist_destroy(pslist);
}

void test_slist_unique_if__cstr_non_empty_all_duplicate(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init_elem(pslist, 10, "a");
    slist_unique_if(pslist, fun_equal_cstr);
    assert_true(slist_size(pslist) == 1);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "a") == 0);

    slist_destroy(pslist);
}

void test_slist_unique_if__default_predicate(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init(pslist);
    slist_push_front(pslist, "f");
    slist_push_front(pslist, "e");
    slist_push_front(pslist, "b");
    slist_push_front(pslist, "b");
    slist_push_front(pslist, "b");
    slist_push_front(pslist, "a");
    slist_unique_if(pslist, NULL);
    assert_true(slist_size(pslist) == 6);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "a") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "b") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "b") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "b") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "e") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "f") == 0);

    slist_destroy(pslist);
}

/*
 * test slist_splice
 */
UT_CASE_DEFINATION(slist_splice)
void test_slist_splice__null_target_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    expect_assert_failure(slist_splice(NULL, slist_begin(pslist), pslist));

    slist_destroy(pslist);
}

void test_slist_splice__null_source_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    expect_assert_failure(slist_splice(pslist, slist_begin(pslist), NULL));

    slist_destroy(pslist);
}

void test_slist_splice__non_inited_target_slist_container(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_src);
    pslist_slist->_t_typeinfo._t_style = 1990;
    expect_assert_failure(slist_splice(pslist_slist, slist_begin(pslist_src), pslist_src));

    pslist_slist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice__non_inited_source_slist_container(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_slist);
    pslist_src->_t_typeinfo._t_style = 4455;
    expect_assert_failure(slist_splice(pslist_slist, slist_begin(pslist_slist), pslist_src));

    pslist_src->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice__not_same_type(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(double);

    slist_init(pslist_slist);
    slist_init(pslist_src);
    expect_assert_failure(slist_splice(pslist_slist, slist_begin(pslist_slist), pslist_src));

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice__invalid_target_position(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_slist);
    slist_init(pslist_src);
    it_iter._t_iteratortype = 232323;
    expect_assert_failure(slist_splice(pslist_slist, it_iter, pslist_src));

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice__same_slist(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    slist_splice(pslist, slist_begin(pslist), pslist);
    assert_true(slist_size(pslist) == 10);

    slist_destroy(pslist);
}

void test_slist_splice__target_empty_source_empty(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_slist);
    slist_init(pslist_src);
    slist_splice(pslist_slist, slist_begin(pslist_slist), pslist_src);
    assert_true(slist_empty(pslist_slist));
    assert_true(slist_empty(pslist_src));

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice__target_empty_source_non_empty(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_slist);
    slist_init_n(pslist_src, 10);
    slist_splice(pslist_slist, slist_begin(pslist_slist), pslist_src);
    assert_true(slist_size(pslist_slist) == 10);
    assert_true(slist_empty(pslist_src));
    for(it_iter  = slist_begin(pslist_slist);
        !iterator_equal(it_iter, slist_end(pslist_slist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice__target_begin_source_empty(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_slist, 10);
    slist_init(pslist_src);
    slist_splice(pslist_slist, slist_begin(pslist_slist), pslist_src);
    assert_true(slist_size(pslist_slist) == 10);
    assert_true(slist_empty(pslist_src));
    for(it_iter  = slist_begin(pslist_slist);
        !iterator_equal(it_iter, slist_end(pslist_slist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice__target_begin_source_non_empty(void** state)
{
    slist_iterator_t it_iter;
    size_t i = 0;
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_slist, 10);
    slist_init_elem(pslist_src, 10, 100);
    slist_splice(pslist_slist, slist_begin(pslist_slist), pslist_src);
    assert_true(slist_size(pslist_slist) == 20);
    assert_true(slist_empty(pslist_src));
    for(it_iter  = slist_begin(pslist_slist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist_slist));
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

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice__target_middle_source_non_empty(void** state)
{
    slist_iterator_t it_iter;
    size_t i = 0;
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_slist, 10);
    slist_init_elem(pslist_src, 10, 100);
    it_iter = iterator_advance(slist_begin(pslist_slist), 3);
    slist_splice(pslist_slist, it_iter, pslist_src);
    assert_true(slist_size(pslist_slist) == 20);
    assert_true(slist_empty(pslist_src));
    for(it_iter  = slist_begin(pslist_slist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist_slist));
        it_iter = iterator_next(it_iter), ++i)
    {
        if(i < 13 && i > 2)
        {
            assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
        }
        else
        {
            assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
        }
    }

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice__target_end_source_non_empty(void** state)
{
    slist_iterator_t it_iter;
    size_t i = 0;
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_slist, 10);
    slist_init_elem(pslist_src, 10, 100);
    slist_splice(pslist_slist, slist_end(pslist_slist), pslist_src);
    assert_true(slist_size(pslist_slist) == 20);
    assert_true(slist_empty(pslist_src));
    for(it_iter  = slist_begin(pslist_slist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist_slist));
        it_iter = iterator_next(it_iter), ++i)
    {
        if(i < 10)
        {
            assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
        }
        else
        {
            assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
        }
    }

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

/*
 * test slist_splice_pos
 */
UT_CASE_DEFINATION(slist_splice_pos)
void test_slist_splice_pos__null_target_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    expect_assert_failure(slist_splice_pos(NULL, slist_begin(pslist), pslist, slist_begin(pslist)));

    slist_destroy(pslist);
}

void test_slist_splice_pos__null_source_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    expect_assert_failure(slist_splice_pos(pslist, slist_begin(pslist), NULL, slist_begin(pslist)));

    slist_destroy(pslist);
}

void test_slist_splice_pos__non_inited_target_slist_container(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_src, 10);
    pslist_slist->_t_typeinfo._t_style = 54566;
    expect_assert_failure(slist_splice_pos(pslist_slist, slist_begin(pslist_slist), pslist_src, slist_begin(pslist_src)));

    pslist_slist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_pos__non_inited_source_slist_container(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_slist);
    pslist_src->_t_typeinfo._t_style = 5688;
    expect_assert_failure(slist_splice_pos(pslist_slist, slist_begin(pslist_slist), pslist_src, slist_begin(pslist_slist)));

    pslist_src->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_pos__not_same(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(double);

    slist_init(pslist_slist);
    slist_init_n(pslist_src, 10);
    expect_assert_failure(slist_splice_pos(pslist_slist, slist_begin(pslist_slist), pslist_src, slist_begin(pslist_src)));

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_pos__invalid_tearget_position(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_slist);
    slist_init_n(pslist_src, 10);
    it_iter._t_iteratortype = 9999;
    expect_assert_failure(slist_splice_pos(pslist_slist, it_iter, pslist_src, slist_begin(pslist_src)));

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_pos__invalid_source_position(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_slist);
    slist_init_n(pslist_src, 10);
    it_iter._t_pos._pby_corepos = (_byte_t*)0x8734;
    expect_assert_failure(slist_splice_pos(pslist_slist, slist_begin(pslist_slist), pslist_src, it_iter));

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_pos__invalid_source_position_end(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_slist);
    slist_init_n(pslist_src, 10);
    it_iter = slist_end(pslist_src);
    expect_assert_failure(slist_splice_pos(pslist_slist, slist_begin(pslist_slist), pslist_src, it_iter));

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_pos__same_slist_container_same_position(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 7);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 2);
    slist_splice_pos(pslist, slist_begin(pslist), pslist, slist_begin(pslist));
    assert_true(slist_size(pslist) == 5);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);

    slist_destroy(pslist);
}

void test_slist_splice_pos__same_slist_container_next_position(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 7);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 2);
    slist_splice_pos(pslist, iterator_next(slist_begin(pslist)), pslist, slist_begin(pslist));
    assert_true(slist_size(pslist) == 5);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);

    slist_destroy(pslist);
}

void test_slist_splice_pos__same_slist_container_not_same_not_next_position(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 7);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 2);
    slist_splice_pos(pslist, slist_end(pslist), pslist, slist_begin(pslist));
    assert_true(slist_size(pslist) == 5);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);

    slist_destroy(pslist);
}

void test_slist_splice_pos__target_empty(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_slist);
    slist_init_elem(pslist_src, 10, 100);
    slist_splice_pos(pslist_slist, slist_begin(pslist_slist), pslist_src, slist_begin(pslist_src));
    assert_true(slist_size(pslist_slist) == 1);
    assert_true(slist_size(pslist_src) == 9);
    assert_true(*(int*)iterator_get_pointer(slist_begin(pslist_slist)) == 100);

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_pos__target_begin_source_begin(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_slist, 10);
    slist_init_elem(pslist_src, 10, 100);
    slist_splice_pos(pslist_slist, slist_begin(pslist_slist), pslist_src, slist_begin(pslist_src));
    assert_true(slist_size(pslist_slist) == 11);
    assert_true(slist_size(pslist_src) == 9);
    assert_true(*(int*)iterator_get_pointer(slist_begin(pslist_slist)) == 100);

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_pos__target_middle_source_middle(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_slist, 10);
    slist_init_elem(pslist_src, 10, 100);
    slist_splice_pos(pslist_slist, iterator_next(slist_begin(pslist_slist)), pslist_src, iterator_next(slist_begin(pslist_src)));
    assert_true(slist_size(pslist_slist) == 11);
    assert_true(slist_size(pslist_src) == 9);
    assert_true(*(int*)iterator_get_pointer(iterator_next(slist_begin(pslist_slist))) == 100);

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_pos__target_end_source_begin(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_slist, 10);
    slist_init_elem(pslist_src, 10, 100);
    slist_splice_pos(pslist_slist, slist_end(pslist_slist), pslist_src, slist_begin(pslist_src));
    assert_true(slist_size(pslist_slist) == 11);
    assert_true(slist_size(pslist_src) == 9);
    assert_true(*(int*)iterator_get_pointer(slist_previous(pslist_slist, slist_end(pslist_slist))) == 100);

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

/*
 * test slist_splice_range
 */
UT_CASE_DEFINATION(slist_splice_range)
void test_slist_splice_range__null_target_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    expect_assert_failure(slist_splice_range(NULL, slist_begin(pslist), pslist, slist_begin(pslist), slist_end(pslist)));

    slist_destroy(pslist);
}

void test_slist_splice_range__null_source_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    expect_assert_failure(slist_splice_range(pslist, slist_begin(pslist), NULL, slist_begin(pslist), slist_end(pslist)));

    slist_destroy(pslist);
}

void test_slist_splice_range__non_inited_target_slist_container(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_src, 10);
    pslist_slist->_t_typeinfo._t_style = 9999;
    expect_assert_failure(slist_splice_range(
        pslist_slist, slist_begin(pslist_slist), pslist_src, slist_begin(pslist_src), slist_end(pslist_src)));

    pslist_slist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_range__non_inited_source_slist_container(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_slist);
    pslist_src->_t_typeinfo._t_style = 33333;
    expect_assert_failure(slist_splice_range(
        pslist_slist, slist_begin(pslist_slist), pslist_src, slist_begin(pslist_slist), slist_end(pslist_slist)));

    pslist_src->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_range__not_same(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(double);

    slist_init(pslist_slist);
    slist_init_n(pslist_src, 10);
    expect_assert_failure(slist_splice_range
        (pslist_slist, slist_begin(pslist_slist), pslist_src, slist_begin(pslist_src), slist_end(pslist_src)));

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_range__invalid_tearget_position(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_slist);
    slist_init_n(pslist_src, 10);
    it_iter._t_pos._pby_corepos = (_byte_t*)0x99;
    expect_assert_failure(slist_splice_range(
        pslist_slist, it_iter, pslist_src, slist_begin(pslist_src), slist_end(pslist_src)));

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_range__invalid_source_range(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_slist);
    slist_init_n(pslist_src, 10);
    expect_assert_failure(slist_splice_range(
        pslist_slist, slist_begin(pslist_slist), pslist_src, slist_end(pslist_src), slist_begin(pslist_src)));

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_range__invalid_target_position_in_range(void** state)
{
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_src, 10);
    expect_assert_failure(slist_splice_range(
        pslist_src, iterator_next(slist_begin(pslist_src)), pslist_src, slist_begin(pslist_src), slist_end(pslist_src)));

    slist_destroy(pslist_src);
}

void test_slist_splice_range__same_slist_container_pos_equal_begin(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 7);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 2);
    slist_splice_range(pslist, slist_begin(pslist), pslist, slist_begin(pslist), slist_end(pslist));
    assert_true(slist_size(pslist) == 5);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);

    slist_destroy(pslist);
}

void test_slist_splice_range__same_slist_container_pos_equal_end(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 7);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 2);
    slist_splice_range(pslist, slist_end(pslist), pslist, slist_begin(pslist), slist_end(pslist));
    assert_true(slist_size(pslist) == 5);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);

    slist_destroy(pslist);
}

void test_slist_splice_range__same_slist_container_pos_not_in_range(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 7);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 2);
    slist_splice_range(pslist, slist_begin(pslist), pslist, iterator_advance(slist_begin(pslist), 2), slist_end(pslist));
    assert_true(slist_size(pslist) == 5);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);

    slist_destroy(pslist);
}

void test_slist_splice_range__target_empty_range_empty(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_slist);
    slist_init_elem(pslist_src, 10, 100);
    slist_splice_range(pslist_slist, slist_begin(pslist_slist), pslist_src, slist_begin(pslist_src), slist_begin(pslist_src));
    assert_true(slist_size(pslist_slist) == 0);
    assert_true(slist_size(pslist_src) == 10);

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_range__target_empty_range_not_empty(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_slist);
    slist_init_elem(pslist_src, 10, 100);
    slist_splice_range(pslist_slist, slist_begin(pslist_slist), pslist_src, slist_begin(pslist_src), slist_end(pslist_src));
    assert_true(slist_size(pslist_slist) == 10);
    assert_true(slist_size(pslist_src) == 0);

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_range__target_begin_source_begin(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_slist, 10);
    slist_init_elem(pslist_src, 10, 100);
    slist_splice_range(pslist_slist, slist_begin(pslist_slist),
        pslist_src, slist_begin(pslist_src), iterator_advance(slist_begin(pslist_src), 2));
    assert_true(slist_size(pslist_slist) == 12);
    assert_true(slist_size(pslist_src) == 8);
    assert_true(*(int*)iterator_get_pointer(slist_begin(pslist_slist)) == 100);
    assert_true(*(int*)iterator_get_pointer(iterator_next(slist_begin(pslist_slist))) == 100);

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_range__target_middle_source_middle(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_slist, 10);
    slist_init_elem(pslist_src, 10, 100);
    slist_splice_range(pslist_slist, iterator_next(slist_begin(pslist_slist)),
        pslist_src, iterator_next(slist_begin(pslist_src)), iterator_advance(slist_begin(pslist_src), 3));
    assert_true(slist_size(pslist_slist) == 12);
    assert_true(slist_size(pslist_src) == 8);
    assert_true(*(int*)iterator_get_pointer(iterator_next(slist_begin(pslist_slist))) == 100);
    assert_true(*(int*)iterator_get_pointer(iterator_advance(slist_begin(pslist_slist), 2)) == 100);

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_range__target_end_source_all(void** state)
{
    slist_iterator_t it_iter;
    size_t i = 0;
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_slist, 10);
    slist_init_elem(pslist_src, 10, 100);
    slist_splice_range(pslist_slist, slist_end(pslist_slist), pslist_src, slist_begin(pslist_src), slist_end(pslist_src));
    assert_true(slist_size(pslist_slist) == 20);
    assert_true(slist_size(pslist_src) == 0);
    for(it_iter = slist_begin(pslist_slist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist_slist));
        it_iter = iterator_next(it_iter), ++i)
    {
        if(i < 10)
        {
            assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
        }
        else
        {
            assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
        }
    }

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

/*
 * test slist_splice_after_pos
 */
UT_CASE_DEFINATION(slist_splice_after_pos)
void test_slist_splice_after_pos__null_target_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    expect_assert_failure(slist_splice_after_pos(NULL, slist_begin(pslist), pslist, slist_begin(pslist)));

    slist_destroy(pslist);
}

void test_slist_splice_after_pos__null_source_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    expect_assert_failure(slist_splice_after_pos(pslist, slist_begin(pslist), NULL, slist_begin(pslist)));

    slist_destroy(pslist);
}

void test_slist_splice_after_pos__non_inited_target_slist_container(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_src, 10);
    pslist_slist->_t_typeinfo._t_style = 54566;
    expect_assert_failure(slist_splice_after_pos(pslist_slist, slist_begin(pslist_slist), pslist_src, slist_begin(pslist_src)));

    pslist_slist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_after_pos__non_inited_source_slist_container(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_slist, 10);
    pslist_src->_t_typeinfo._t_style = 5688;
    expect_assert_failure(slist_splice_after_pos(pslist_slist, slist_begin(pslist_slist), pslist_src, slist_begin(pslist_slist)));

    pslist_src->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_after_pos__not_same(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(double);

    slist_init_n(pslist_slist, 10);
    slist_init_n(pslist_src, 10);
    expect_assert_failure(slist_splice_after_pos(pslist_slist, slist_begin(pslist_slist), pslist_src, slist_begin(pslist_src)));

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_after_pos__invalid_tearget_position(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_slist, 10);
    slist_init_n(pslist_src, 10);
    it_iter._t_iteratortype = 9999;
    expect_assert_failure(slist_splice_after_pos(pslist_slist, it_iter, pslist_src, slist_begin(pslist_src)));

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_after_pos__invalid_source_position(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_slist, 10);
    slist_init_n(pslist_src, 10);
    it_iter._t_pos._pby_corepos = (_byte_t*)0x8734;
    expect_assert_failure(slist_splice_after_pos(pslist_slist, slist_begin(pslist_slist), pslist_src, it_iter));

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_after_pos__invalid_target_position_end(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_slist, 10);
    slist_init_n(pslist_src, 10);
    it_iter = slist_begin(pslist_src);
    expect_assert_failure(slist_splice_after_pos(pslist_slist, slist_end(pslist_slist), pslist_src, it_iter));

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_after_pos__invalid_source_position_end(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_slist, 10);
    slist_init_n(pslist_src, 10);
    it_iter = slist_end(pslist_src);
    expect_assert_failure(slist_splice_after_pos(pslist_slist, slist_begin(pslist_slist), pslist_src, it_iter));

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_after_pos__same_slist_container_same_position(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 7);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 2);
    slist_splice_after_pos(pslist, slist_begin(pslist), pslist, slist_begin(pslist));
    assert_true(slist_size(pslist) == 5);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);

    slist_destroy(pslist);
}

void test_slist_splice_after_pos__same_slist_container_next_position(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 7);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 2);
    slist_splice_after_pos(pslist, iterator_next(slist_begin(pslist)), pslist, slist_begin(pslist));
    assert_true(slist_size(pslist) == 5);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);

    slist_destroy(pslist);
}

void test_slist_splice_after_pos__same_slist_container_last_source_position(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 7);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 2);
    slist_splice_after_pos(pslist, iterator_next(slist_begin(pslist)), pslist, slist_previous(pslist, slist_end(pslist)));
    assert_true(slist_size(pslist) == 5);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);

    slist_destroy(pslist);
}

void test_slist_splice_after_pos__same_slist_container_not_same_not_next_position(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 2);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 7);
    slist_splice_after_pos(pslist, slist_previous(pslist, slist_end(pslist)), pslist, slist_begin(pslist));
    assert_true(slist_size(pslist) == 5);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);

    slist_destroy(pslist);
}

void test_slist_splice_after_pos__target_begin_source_begin(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_slist, 10);
    slist_init_elem(pslist_src, 10, 100);
    slist_splice_after_pos(pslist_slist, slist_begin(pslist_slist), pslist_src, slist_begin(pslist_src));
    assert_true(slist_size(pslist_slist) == 11);
    assert_true(slist_size(pslist_src) == 9);
    assert_true(*(int*)iterator_get_pointer(slist_begin(pslist_slist)) == 0);
    assert_true(*(int*)iterator_get_pointer(iterator_next(slist_begin(pslist_slist))) == 100);

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_after_pos__target_middle_source_middle(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_slist, 10);
    slist_init_elem(pslist_src, 10, 100);
    slist_splice_after_pos(
        pslist_slist, iterator_next(slist_begin(pslist_slist)), pslist_src, iterator_next(slist_begin(pslist_src)));
    assert_true(slist_size(pslist_slist) == 11);
    assert_true(slist_size(pslist_src) == 9);
    assert_true(*(int*)iterator_get_pointer(iterator_next(slist_begin(pslist_slist))) == 0);
    assert_true(*(int*)iterator_get_pointer(iterator_advance(slist_begin(pslist_slist), 2)) == 100);

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_after_pos__target_last_source_begin(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_slist, 10);
    slist_init_elem(pslist_src, 10, 100);
    slist_splice_after_pos(
        pslist_slist, slist_previous(pslist_slist, slist_end(pslist_slist)), pslist_src, slist_begin(pslist_src));
    assert_true(slist_size(pslist_slist) == 11);
    assert_true(slist_size(pslist_src) == 9);
    assert_true(*(int*)iterator_get_pointer(slist_previous(pslist_slist, slist_end(pslist_slist))) == 100);

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_after_pos__target_last_source_last(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_slist, 10);
    slist_init_elem(pslist_src, 10, 100);
    slist_splice_after_pos(
        pslist_slist, slist_previous(pslist_slist, slist_end(pslist_slist)),
        pslist_src, slist_previous(pslist_src, slist_end(pslist_src)));
    assert_true(slist_size(pslist_slist) == 10);
    assert_true(slist_size(pslist_src) == 10);
    assert_true(*(int*)iterator_get_pointer(slist_previous(pslist_slist, slist_end(pslist_slist))) == 0);

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

/*
 * test slist_splice_after_range
 */
UT_CASE_DEFINATION(slist_splice_after_range)
void test_slist_splice_after_range__null_target_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    expect_assert_failure(slist_splice_after_range(
        NULL, slist_begin(pslist), pslist, slist_begin(pslist), iterator_next(slist_begin(pslist))));

    slist_destroy(pslist);
}

void test_slist_splice_after_range__null_source_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    expect_assert_failure(slist_splice_after_range(
        pslist, slist_begin(pslist), NULL, slist_begin(pslist), iterator_next(slist_begin(pslist))));

    slist_destroy(pslist);
}

void test_slist_splice_after_range__non_inited_target_slist_container(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_src, 10);
    pslist_slist->_t_typeinfo._t_style = 9999;
    expect_assert_failure(slist_splice_after_range(
        pslist_slist, slist_begin(pslist_slist), pslist_src, slist_begin(pslist_src), iterator_next(slist_begin(pslist_src))));

    pslist_slist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_after_range__non_inited_source_slist_container(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_slist, 10);
    pslist_src->_t_typeinfo._t_style = 33333;
    expect_assert_failure(slist_splice_after_range(
        pslist_slist, slist_begin(pslist_slist), pslist_src, slist_begin(pslist_slist), iterator_next(slist_begin(pslist_slist))));

    pslist_src->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_after_range__not_same(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(double);

    slist_init_n(pslist_slist, 10);
    slist_init_n(pslist_src, 10);
    expect_assert_failure(slist_splice_after_range
        (pslist_slist, slist_begin(pslist_slist), pslist_src, slist_begin(pslist_src), slist_begin(pslist_src)));

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_after_range__invalid_tearget_position(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_slist, 10);
    slist_init_n(pslist_src, 10);
    it_iter._t_pos._pby_corepos = (_byte_t*)0x99;
    expect_assert_failure(slist_splice_after_range(
        pslist_slist, it_iter, pslist_src, slist_begin(pslist_src), slist_begin(pslist_src)));

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_after_range__invalid_source_range(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_slist, 10);
    slist_init_n(pslist_src, 10);
    expect_assert_failure(slist_splice_after_range(
        pslist_slist, slist_begin(pslist_slist), pslist_src, iterator_next(slist_begin(pslist_src)), slist_begin(pslist_src)));

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_after_range__invalid_target_position_end(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_slist, 10);
    slist_init_n(pslist_src, 10);
    expect_assert_failure(slist_splice_after_range(
        pslist_slist, slist_end(pslist_slist),
        pslist_src, iterator_next(slist_begin(pslist_src)), slist_previous(pslist_src, slist_end(pslist_src))));

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}


void test_slist_splice_after_range__invalid_source_range_end(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_slist, 10);
    slist_init_n(pslist_src, 10);
    expect_assert_failure(slist_splice_after_range(
        pslist_slist, slist_begin(pslist_slist), pslist_src, iterator_next(slist_begin(pslist_src)), slist_end(pslist_src)));

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_after_range__invalid_target_position_in_range(void** state)
{
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_src, 10);
    expect_assert_failure(slist_splice_after_range(
        pslist_src, iterator_advance(slist_begin(pslist_src), 3),
        pslist_src, slist_begin(pslist_src), slist_previous(pslist_src, slist_end(pslist_src))));

    slist_destroy(pslist_src);
}

void test_slist_splice_after_range__same_slist_container_pos_equal_begin(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 7);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 2);
    slist_splice_after_range(pslist, slist_begin(pslist), pslist, slist_begin(pslist), slist_previous(pslist, slist_end(pslist)));
    assert_true(slist_size(pslist) == 5);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);

    slist_destroy(pslist);
}

void test_slist_splice_after_range__same_slist_container_pos_equal_end(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 7);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 2);
    slist_splice_after_range(
        pslist, slist_previous(pslist, slist_end(pslist)),
        pslist, slist_begin(pslist), slist_previous(pslist, slist_end(pslist)));
    assert_true(slist_size(pslist) == 5);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);

    slist_destroy(pslist);
}

void test_slist_splice_after_range__same_slist_container_pos_not_in_range(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 7);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 2);
    slist_splice_after_range(pslist, slist_begin(pslist),
        pslist, iterator_advance(slist_begin(pslist), 2), slist_previous(pslist, slist_end(pslist)));
    assert_true(slist_size(pslist) == 5);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    slist_destroy(pslist);
}

void test_slist_splice_after_range__target_begin_source_begin(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_iterator_t it_iter;

    slist_init_n(pslist_slist, 10);
    slist_init(pslist_src);
    slist_push_front(pslist_src, 7);
    slist_push_front(pslist_src, 4);
    slist_push_front(pslist_src, 3);
    slist_push_front(pslist_src, 5);
    slist_push_front(pslist_src, 2);
    slist_splice_after_range(pslist_slist, slist_begin(pslist_slist),
        pslist_src, slist_begin(pslist_src), iterator_advance(slist_begin(pslist_src), 2));
    assert_true(slist_size(pslist_slist) == 12);
    assert_true(slist_size(pslist_src) == 3);
    it_iter = slist_begin(pslist_slist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    it_iter = slist_begin(pslist_src);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_after_range__target_middle_source_middle(void** state)
{
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);
    slist_iterator_t it_iter;

    slist_init_n(pslist_slist, 10);
    slist_init(pslist_src);
    slist_push_front(pslist_src, 7);
    slist_push_front(pslist_src, 4);
    slist_push_front(pslist_src, 3);
    slist_push_front(pslist_src, 5);
    slist_push_front(pslist_src, 2);
    slist_splice_after_range(pslist_slist, iterator_next(slist_begin(pslist_slist)),
        pslist_src, iterator_next(slist_begin(pslist_src)), iterator_advance(slist_begin(pslist_src), 3));
    assert_true(slist_size(pslist_slist) == 12);
    assert_true(slist_size(pslist_src) == 3);
    it_iter = slist_begin(pslist_slist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    it_iter = slist_begin(pslist_src);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_after_range__target_last_source_all(void** state)
{
    slist_iterator_t it_iter;
    size_t i = 0;
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_slist, 3);
    slist_init(pslist_src);
    slist_push_front(pslist_src, 7);
    slist_push_front(pslist_src, 4);
    slist_push_front(pslist_src, 3);
    slist_push_front(pslist_src, 5);
    slist_push_front(pslist_src, 2);
    slist_splice_after_range(
        pslist_slist, slist_previous(pslist_slist, slist_end(pslist_slist)),
        pslist_src, slist_begin(pslist_src), slist_previous(pslist_src, slist_end(pslist_src)));
    assert_true(slist_size(pslist_slist) == 7);
    assert_true(slist_size(pslist_src) == 1);

    it_iter = slist_begin(pslist_slist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);

    it_iter = slist_begin(pslist_src);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

void test_slist_splice_after_range__target_last_source_empty(void** state)
{
    slist_iterator_t it_iter;
    size_t i = 0;
    slist_t* pslist_slist = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_slist, 3);
    slist_init(pslist_src);
    slist_push_front(pslist_src, 7);
    slist_push_front(pslist_src, 4);
    slist_push_front(pslist_src, 3);
    slist_push_front(pslist_src, 5);
    slist_push_front(pslist_src, 2);
    slist_splice_after_range(
        pslist_slist, slist_previous(pslist_slist, slist_end(pslist_slist)),
        pslist_src, slist_begin(pslist_src), slist_begin(pslist_src));
    assert_true(slist_size(pslist_slist) == 3);
    assert_true(slist_size(pslist_src) == 5);

    it_iter = slist_begin(pslist_slist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    it_iter = slist_begin(pslist_src);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);

    slist_destroy(pslist_slist);
    slist_destroy(pslist_src);
}

/*
 * test slist_sort
 */
UT_CASE_DEFINATION(slist_sort)
void test_slist_sort__null_slist_container(void** state)
{
    expect_assert_failure(slist_sort(NULL));
}

void test_slist_sort__non_inited_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    pslist->_t_typeinfo._t_style = 4444;
    expect_assert_failure(slist_sort(pslist));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test_slist_sort__empty_less(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    assert_true(slist_size(pslist) == 0);
    slist_sort(pslist);
    assert_true(slist_size(pslist) == 0);

    slist_destroy(pslist);
}

void test_slist_sort__1_less(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 1);
    assert_true(slist_size(pslist) == 1);
    slist_sort(pslist);
    assert_true(slist_size(pslist) == 1);
    assert_true(*(int*)iterator_get_pointer(slist_begin(pslist)) == 0);

    slist_destroy(pslist);
}

void test_slist_sort__2_equal_less(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 2);
    assert_true(slist_size(pslist) == 2);
    slist_sort(pslist);
    assert_true(slist_size(pslist) == 2);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    slist_destroy(pslist);
}

void test_slist_sort__2_less_less(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 1);
    assert_true(slist_size(pslist) == 2);
    slist_sort(pslist);
    assert_true(slist_size(pslist) == 2);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    slist_destroy(pslist);
}

void test_slist_sort__2_greater_less(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 0);
    assert_true(slist_size(pslist) == 2);
    slist_sort(pslist);
    assert_true(slist_size(pslist) == 2);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    slist_destroy(pslist);
}

void test_slist_sort__random_equal_less(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    assert_true(slist_size(pslist) == 10);
    slist_sort(pslist);
    assert_true(slist_size(pslist) == 10);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    slist_destroy(pslist);
}

void test_slist_sort__random_less_less(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 9);
    slist_push_front(pslist, 8);
    slist_push_front(pslist, 7);
    slist_push_front(pslist, 6);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 3);
    slist_push_front(pslist, 2);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 0);
    assert_true(slist_size(pslist) == 10);
    slist_sort(pslist);
    assert_true(slist_size(pslist) == 10);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);

    slist_destroy(pslist);
}

void test_slist_sort__random_greater_less(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 2);
    slist_push_front(pslist, 3);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 6);
    slist_push_front(pslist, 7);
    slist_push_front(pslist, 8);
    slist_push_front(pslist, 9);
    assert_true(slist_size(pslist) == 10);
    slist_sort(pslist);
    assert_true(slist_size(pslist) == 10);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);

    slist_destroy(pslist);
}

void test_slist_sort__random_random_less(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 6);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 2);
    slist_push_front(pslist, 9);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 3);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 7);
    slist_push_front(pslist, 8);
    slist_push_front(pslist, 4);
    assert_true(slist_size(pslist) == 10);
    slist_sort(pslist);
    assert_true(slist_size(pslist) == 10);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);

    slist_destroy(pslist);
}

void test_slist_sort__random_random_dup_less(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 8);
    slist_push_front(pslist, 7);
    slist_push_front(pslist, 8);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 3);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 6);
    slist_push_front(pslist, 9);
    slist_push_front(pslist, 2);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 6);
    slist_push_front(pslist, 4);
    assert_true(slist_size(pslist) == 15);
    slist_sort(pslist);
    assert_true(slist_size(pslist) == 15);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);

    slist_destroy(pslist);
}

/*
 * test slist_sort_if
 */
UT_CASE_DEFINATION(slist_sort_if)
void test_slist_sort_if__null_slist_container(void** state)
{
    expect_assert_failure(slist_sort_if(NULL, NULL));
}

void test_slist_sort_if__non_inited_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    pslist->_t_typeinfo._t_style = 43454;
    expect_assert_failure(slist_sort_if(pslist, NULL));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test_slist_sort_if__empty_less(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    assert_true(slist_size(pslist) == 0);
    slist_sort_if(pslist, NULL);
    assert_true(slist_size(pslist) == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__empty_greater(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    assert_true(slist_size(pslist) == 0);
    slist_sort_if(pslist, fun_greater_int);
    assert_true(slist_size(pslist) == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__1_less(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 1);
    assert_true(slist_size(pslist) == 1);
    slist_sort_if(pslist, NULL);
    assert_true(slist_size(pslist) == 1);
    assert_true(*(int*)iterator_get_pointer(slist_begin(pslist)) == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__1_greater(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 1);
    assert_true(slist_size(pslist) == 1);
    slist_sort_if(pslist, fun_greater_int);
    assert_true(slist_size(pslist) == 1);
    assert_true(*(int*)iterator_get_pointer(slist_begin(pslist)) == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__2_equal_less(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 2);
    assert_true(slist_size(pslist) == 2);
    slist_sort_if(pslist, NULL);
    assert_true(slist_size(pslist) == 2);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__2_equal_greater(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 2);
    assert_true(slist_size(pslist) == 2);
    slist_sort_if(pslist, fun_greater_int);
    assert_true(slist_size(pslist) == 2);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__2_less_less(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 0);
    assert_true(slist_size(pslist) == 2);
    slist_sort_if(pslist, NULL);
    assert_true(slist_size(pslist) == 2);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    slist_destroy(pslist);
}

void test_slist_sort_if__2_less_greater(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 0);
    assert_true(slist_size(pslist) == 2);
    slist_sort_if(pslist, fun_greater_int);
    assert_true(slist_size(pslist) == 2);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__2_greater_less(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 1);
    assert_true(slist_size(pslist) == 2);
    slist_sort_if(pslist, NULL);
    assert_true(slist_size(pslist) == 2);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    slist_destroy(pslist);
}

void test_slist_sort_if__2_greater_greater(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 1);
    assert_true(slist_size(pslist) == 2);
    slist_sort_if(pslist, fun_greater_int);
    assert_true(slist_size(pslist) == 2);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__random_equal_less(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    assert_true(slist_size(pslist) == 10);
    slist_sort_if(pslist, NULL);
    assert_true(slist_size(pslist) == 10);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__random_equal_greater(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    assert_true(slist_size(pslist) == 10);
    slist_sort_if(pslist, fun_greater_int);
    assert_true(slist_size(pslist) == 10);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__random_less_less(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 9);
    slist_push_front(pslist, 8);
    slist_push_front(pslist, 7);
    slist_push_front(pslist, 6);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 3);
    slist_push_front(pslist, 2);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 0);
    assert_true(slist_size(pslist) == 10);
    slist_sort_if(pslist, NULL);
    assert_true(slist_size(pslist) == 10);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);

    slist_destroy(pslist);
}

void test_slist_sort_if__random_less_greater(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 9);
    slist_push_front(pslist, 8);
    slist_push_front(pslist, 7);
    slist_push_front(pslist, 6);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 3);
    slist_push_front(pslist, 2);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 0);
    assert_true(slist_size(pslist) == 10);
    slist_sort_if(pslist, fun_greater_int);
    assert_true(slist_size(pslist) == 10);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__random_greater_less(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 2);
    slist_push_front(pslist, 3);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 6);
    slist_push_front(pslist, 7);
    slist_push_front(pslist, 8);
    slist_push_front(pslist, 9);
    assert_true(slist_size(pslist) == 10);
    slist_sort_if(pslist, NULL);
    assert_true(slist_size(pslist) == 10);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);

    slist_destroy(pslist);
}

void test_slist_sort_if__random_greater_greater(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 2);
    slist_push_front(pslist, 3);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 6);
    slist_push_front(pslist, 7);
    slist_push_front(pslist, 8);
    slist_push_front(pslist, 9);
    assert_true(slist_size(pslist) == 10);
    slist_sort_if(pslist, fun_greater_int);
    assert_true(slist_size(pslist) == 10);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__random_random_less(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 8);
    slist_push_front(pslist, 7);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 3);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 9);
    slist_push_front(pslist, 2);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 6);
    assert_true(slist_size(pslist) == 10);
    slist_sort_if(pslist, NULL);
    assert_true(slist_size(pslist) == 10);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);

    slist_destroy(pslist);
}

void test_slist_sort_if__random_random_greater(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 8);
    slist_push_front(pslist, 3);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 2);
    slist_push_front(pslist, 6);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 9);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 7);
    assert_true(slist_size(pslist) == 10);
    slist_sort_if(pslist, fun_greater_int);
    assert_true(slist_size(pslist) == 10);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__random_random_dup_less(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 8);
    slist_push_front(pslist, 7);
    slist_push_front(pslist, 8);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 3);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 6);
    slist_push_front(pslist, 9);
    slist_push_front(pslist, 2);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 6);
    slist_push_front(pslist, 4);
    assert_true(slist_size(pslist) == 15);
    slist_sort_if(pslist, NULL);
    assert_true(slist_size(pslist) == 15);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);

    slist_destroy(pslist);
}

void test_slist_sort_if__random_random_dup_greater(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 1);
    slist_push_front(pslist, 8);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 8);
    slist_push_front(pslist, 3);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 2);
    slist_push_front(pslist, 6);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 9);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 7);
    slist_push_front(pslist, 5);
    slist_push_front(pslist, 7);
    assert_true(slist_size(pslist) == 15);
    slist_sort_if(pslist, fun_greater_int);
    assert_true(slist_size(pslist) == 15);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__cstr_1_less(void** state)
{
    slist_t* pslist = create_slist(char*);

    slist_init_n(pslist, 1);
    assert_true(slist_size(pslist) == 1);
    slist_sort_if(pslist, NULL);
    assert_true(slist_size(pslist) == 1);
    assert_true(strcmp((char*)iterator_get_pointer(slist_begin(pslist)), "") == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__cstr_1_greater(void** state)
{
    slist_t* pslist = create_slist(char*);

    slist_init_n(pslist, 1);
    assert_true(slist_size(pslist) == 1);
    slist_sort_if(pslist, fun_greater_cstr);
    assert_true(slist_size(pslist) == 1);
    assert_true(strcmp((char*)iterator_get_pointer(slist_begin(pslist)), "") == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__cstr_2_equal_less(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init_n(pslist, 2);
    assert_true(slist_size(pslist) == 2);
    slist_sort_if(pslist, NULL);
    assert_true(slist_size(pslist) == 2);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__cstr_2_equal_greater(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init_n(pslist, 2);
    assert_true(slist_size(pslist) == 2);
    slist_sort_if(pslist, fun_greater_cstr);
    assert_true(slist_size(pslist) == 2);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__cstr_2_less_less(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init(pslist);
    slist_push_front(pslist, "1");
    slist_push_front(pslist, "0");
    assert_true(slist_size(pslist) == 2);
    slist_sort_if(pslist, NULL);
    assert_true(slist_size(pslist) == 2);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__cstr_2_less_greater(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init(pslist);
    slist_push_front(pslist, "1");
    slist_push_front(pslist, "0");
    assert_true(slist_size(pslist) == 2);
    slist_sort_if(pslist, fun_greater_cstr);
    assert_true(slist_size(pslist) == 2);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__cstr_2_greater_less(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init(pslist);
    slist_push_front(pslist, "0");
    slist_push_front(pslist, "1");
    assert_true(slist_size(pslist) == 2);
    slist_sort_if(pslist, NULL);
    assert_true(slist_size(pslist) == 2);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__cstr_2_greater_greater(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init(pslist);
    slist_push_front(pslist, "0");
    slist_push_front(pslist, "1");
    assert_true(slist_size(pslist) == 2);
    slist_sort_if(pslist, fun_greater_cstr);
    assert_true(slist_size(pslist) == 2);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__cstr_random_equal_less(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init_n(pslist, 10);
    assert_true(slist_size(pslist) == 10);
    slist_sort_if(pslist, NULL);
    assert_true(slist_size(pslist) == 10);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__cstr_random_equal_greater(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init_n(pslist, 10);
    assert_true(slist_size(pslist) == 10);
    slist_sort_if(pslist, fun_greater_cstr);
    assert_true(slist_size(pslist) == 10);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__cstr_random_less_less(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init(pslist);
    slist_push_front(pslist, "9");
    slist_push_front(pslist, "8");
    slist_push_front(pslist, "7");
    slist_push_front(pslist, "6");
    slist_push_front(pslist, "5");
    slist_push_front(pslist, "4");
    slist_push_front(pslist, "3");
    slist_push_front(pslist, "2");
    slist_push_front(pslist, "1");
    slist_push_front(pslist, "0");
    assert_true(slist_size(pslist) == 10);
    slist_sort_if(pslist, NULL);
    assert_true(slist_size(pslist) == 10);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "2") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "4") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "6") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "9") == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__cstr_random_less_greater(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init(pslist);
    slist_push_front(pslist, "9");
    slist_push_front(pslist, "8");
    slist_push_front(pslist, "7");
    slist_push_front(pslist, "6");
    slist_push_front(pslist, "5");
    slist_push_front(pslist, "4");
    slist_push_front(pslist, "3");
    slist_push_front(pslist, "2");
    slist_push_front(pslist, "1");
    slist_push_front(pslist, "0");
    assert_true(slist_size(pslist) == 10);
    slist_sort_if(pslist, fun_greater_cstr);
    assert_true(slist_size(pslist) == 10);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "9") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "6") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "4") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "2") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__cstr_random_greater_less(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init(pslist);
    slist_push_front(pslist, "0");
    slist_push_front(pslist, "1");
    slist_push_front(pslist, "2");
    slist_push_front(pslist, "3");
    slist_push_front(pslist, "4");
    slist_push_front(pslist, "5");
    slist_push_front(pslist, "6");
    slist_push_front(pslist, "7");
    slist_push_front(pslist, "8");
    slist_push_front(pslist, "9");
    assert_true(slist_size(pslist) == 10);
    slist_sort_if(pslist, NULL);
    assert_true(slist_size(pslist) == 10);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "2") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "4") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "6") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "9") == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__cstr_random_greater_greater(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init(pslist);
    slist_push_front(pslist, "0");
    slist_push_front(pslist, "1");
    slist_push_front(pslist, "2");
    slist_push_front(pslist, "3");
    slist_push_front(pslist, "4");
    slist_push_front(pslist, "5");
    slist_push_front(pslist, "6");
    slist_push_front(pslist, "7");
    slist_push_front(pslist, "8");
    slist_push_front(pslist, "9");
    assert_true(slist_size(pslist) == 10);
    slist_sort_if(pslist, fun_greater_cstr);
    assert_true(slist_size(pslist) == 10);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "9") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "6") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "4") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "2") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__cstr_random_random_less(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init(pslist);
    slist_push_front(pslist, "4");
    slist_push_front(pslist, "8");
    slist_push_front(pslist, "7");
    slist_push_front(pslist, "0");
    slist_push_front(pslist, "3");
    slist_push_front(pslist, "5");
    slist_push_front(pslist, "9");
    slist_push_front(pslist, "2");
    slist_push_front(pslist, "1");
    slist_push_front(pslist, "6");
    assert_true(slist_size(pslist) == 10);
    slist_sort_if(pslist, NULL);
    assert_true(slist_size(pslist) == 10);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "2") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "4") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "6") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "9") == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__cstr_random_random_greater(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init(pslist);
    slist_push_front(pslist, "1");
    slist_push_front(pslist, "8");
    slist_push_front(pslist, "3");
    slist_push_front(pslist, "0");
    slist_push_front(pslist, "2");
    slist_push_front(pslist, "6");
    slist_push_front(pslist, "4");
    slist_push_front(pslist, "9");
    slist_push_front(pslist, "5");
    slist_push_front(pslist, "7");
    assert_true(slist_size(pslist) == 10);
    slist_sort_if(pslist, fun_greater_cstr);
    assert_true(slist_size(pslist) == 10);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "9") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "6") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "4") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "2") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__cstr_random_random_dup_less(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init(pslist);
    slist_push_front(pslist, "4");
    slist_push_front(pslist, "8");
    slist_push_front(pslist, "7");
    slist_push_front(pslist, "8");
    slist_push_front(pslist, "0");
    slist_push_front(pslist, "3");
    slist_push_front(pslist, "5");
    slist_push_front(pslist, "1");
    slist_push_front(pslist, "6");
    slist_push_front(pslist, "9");
    slist_push_front(pslist, "2");
    slist_push_front(pslist, "1");
    slist_push_front(pslist, "1");
    slist_push_front(pslist, "6");
    slist_push_front(pslist, "4");
    assert_true(slist_size(pslist) == 15);
    slist_sort_if(pslist, NULL);
    assert_true(slist_size(pslist) == 15);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "2") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "4") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "4") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "6") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "6") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "9") == 0);

    slist_destroy(pslist);
}

void test_slist_sort_if__cstr_random_random_dup_greater(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(char*);

    slist_init(pslist);
    slist_push_front(pslist, "1");
    slist_push_front(pslist, "8");
    slist_push_front(pslist, "0");
    slist_push_front(pslist, "8");
    slist_push_front(pslist, "3");
    slist_push_front(pslist, "0");
    slist_push_front(pslist, "0");
    slist_push_front(pslist, "2");
    slist_push_front(pslist, "6");
    slist_push_front(pslist, "4");
    slist_push_front(pslist, "9");
    slist_push_front(pslist, "5");
    slist_push_front(pslist, "7");
    slist_push_front(pslist, "5");
    slist_push_front(pslist, "7");
    assert_true(slist_size(pslist) == 15);
    slist_sort_if(pslist, fun_greater_cstr);
    assert_true(slist_size(pslist) == 15);
    it_iter = slist_begin(pslist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "9") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "6") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "4") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "2") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);

    slist_destroy(pslist);
}

/*
 * test slist_merge
 */
UT_CASE_DEFINATION(slist_merge)
void test_slist_merge__null_dest_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    expect_assert_failure(slist_merge(NULL, pslist));

    slist_destroy(pslist);
}

void test_slist_merge__null_src_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    expect_assert_failure(slist_merge(pslist, NULL));

    slist_destroy(pslist);
}

void test_slist_merge__non_inited_dest_slist_container(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_src);
    pslist_dest->_t_typeinfo._t_style = 23423;
    expect_assert_failure(slist_merge(pslist_dest, pslist_src));

    pslist_dest->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_merge__non_inited_src_slist_container(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_dest);
    pslist_src->_t_typeinfo._t_style = 23434;
    expect_assert_failure(slist_merge(pslist_dest, pslist_src));

    pslist_src->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_merge__not_same(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(double);

    slist_init(pslist_dest);
    slist_init(pslist_src);
    expect_assert_failure(slist_merge(pslist_dest, pslist_src));

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_merge__same_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_merge(pslist, pslist);
    assert_true(slist_empty(pslist));

    slist_destroy(pslist);
}

void test_slist_merge__dest_empty_src_empty(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_dest);
    slist_init(pslist_src);
    slist_merge(pslist_dest, pslist_src);
    assert_true(slist_empty(pslist_dest));
    assert_true(slist_empty(pslist_src));

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_merge__dest_non_empty_src_empty(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_dest, 10);
    slist_init(pslist_src);
    slist_merge(pslist_dest, pslist_src);
    assert_true(slist_size(pslist_dest) == 10);
    assert_true(slist_empty(pslist_src));

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_merge__dest_empty_src_non_empty(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_dest);
    slist_init_n(pslist_src, 10);
    slist_merge(pslist_dest, pslist_src);
    assert_true(slist_size(pslist_dest) == 10);
    assert_true(slist_empty(pslist_src));
    for(it_iter = slist_begin(pslist_dest);
        !iterator_equal(it_iter, slist_end(pslist_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_merge__dest_tailing(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_dest);
    slist_push_front(pslist_dest, 9);
    slist_push_front(pslist_dest, 8);
    slist_push_front(pslist_dest, 5);
    slist_push_front(pslist_dest, 4);
    slist_init(pslist_src);
    slist_push_front(pslist_src, 7);
    slist_push_front(pslist_src, 3);
    slist_push_front(pslist_src, 2);
    slist_merge(pslist_dest, pslist_src);
    assert_true(slist_size(pslist_dest) == 7);
    assert_true(slist_empty(pslist_src));
    it_iter = slist_begin(pslist_dest);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_merge__src_tailing(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_dest);
    slist_push_front(pslist_dest, 7);
    slist_push_front(pslist_dest, 5);
    slist_push_front(pslist_dest, 5);
    slist_push_front(pslist_dest, 3);
    slist_init(pslist_src);
    slist_push_front(pslist_src, 9);
    slist_push_front(pslist_src, 8);
    slist_push_front(pslist_src, 7);
    slist_push_front(pslist_src, 3);
    slist_push_front(pslist_src, 2);
    slist_merge(pslist_dest, pslist_src);
    assert_true(slist_size(pslist_dest) == 9);
    assert_true(slist_empty(pslist_src));
    it_iter = slist_begin(pslist_dest);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_merge__random(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_dest);
    slist_push_front(pslist_dest, 3);
    slist_push_front(pslist_dest, 5);
    slist_push_front(pslist_dest, 8);
    slist_push_front(pslist_dest, 3);
    slist_init(pslist_src);
    slist_push_front(pslist_src, 2);
    slist_push_front(pslist_src, 8);
    slist_push_front(pslist_src, 7);
    slist_push_front(pslist_src, 9);
    slist_push_front(pslist_src, 3);
    slist_merge(pslist_dest, pslist_src);
    assert_true(slist_size(pslist_dest) == 9);
    assert_true(slist_empty(pslist_src));
    it_iter = slist_begin(pslist_dest);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_merge__cstr_dest_tailing(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_dest = create_slist(char*);
    slist_t* pslist_src = create_slist(char*);

    slist_init(pslist_dest);
    slist_push_front(pslist_dest, "9");
    slist_push_front(pslist_dest, "8");
    slist_push_front(pslist_dest, "5");
    slist_push_front(pslist_dest, "4");
    slist_init(pslist_src);
    slist_push_front(pslist_src, "7");
    slist_push_front(pslist_src, "3");
    slist_push_front(pslist_src, "2");
    slist_merge(pslist_dest, pslist_src);
    assert_true(slist_size(pslist_dest) == 7);
    assert_true(slist_empty(pslist_src));
    it_iter = slist_begin(pslist_dest);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "2") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "4") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "9") == 0);

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_merge__cstr_src_tailing(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_dest = create_slist(char*);
    slist_t* pslist_src = create_slist(char*);

    slist_init(pslist_dest);
    slist_push_front(pslist_dest, "7");
    slist_push_front(pslist_dest, "5");
    slist_push_front(pslist_dest, "5");
    slist_push_front(pslist_dest, "3");
    slist_init(pslist_src);
    slist_push_front(pslist_src, "9");
    slist_push_front(pslist_src, "8");
    slist_push_front(pslist_src, "7");
    slist_push_front(pslist_src, "3");
    slist_push_front(pslist_src, "2");
    slist_merge(pslist_dest, pslist_src);
    assert_true(slist_size(pslist_dest) == 9);
    assert_true(slist_empty(pslist_src));
    it_iter = slist_begin(pslist_dest);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "2") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "9") == 0);

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_merge__cstr_random(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_dest = create_slist(char*);
    slist_t* pslist_src = create_slist(char*);

    slist_init(pslist_dest);
    slist_push_front(pslist_dest, "3");
    slist_push_front(pslist_dest, "5");
    slist_push_front(pslist_dest, "8");
    slist_push_front(pslist_dest, "3");
    slist_init(pslist_src);
    slist_push_front(pslist_src, "2");
    slist_push_front(pslist_src, "8");
    slist_push_front(pslist_src, "7");
    slist_push_front(pslist_src, "9");
    slist_push_front(pslist_src, "3");
    slist_merge(pslist_dest, pslist_src);
    assert_true(slist_size(pslist_dest) == 9);
    assert_true(slist_empty(pslist_src));
    it_iter = slist_begin(pslist_dest);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "9") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "2") == 0);

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

/*
 * test slist_merge_if
 */
UT_CASE_DEFINATION(slist_merge_if)
void test_slist_merge_if__null_dest_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    expect_assert_failure(slist_merge_if(NULL, pslist, NULL));

    slist_destroy(pslist);
}

void test_slist_merge_if__null_src_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    expect_assert_failure(slist_merge_if(pslist, NULL, NULL));

    slist_destroy(pslist);
}

void test_slist_merge_if__non_inited_dest_slist_container(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_src);
    pslist_dest->_t_typeinfo._t_style = 44444;
    expect_assert_failure(slist_merge_if(pslist_dest, pslist_src, NULL));

    pslist_dest->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_merge_if__non_inited_src_slist_container(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_dest);
    pslist_src->_t_typeinfo._t_style = 4455;
    expect_assert_failure(slist_merge_if(pslist_dest, pslist_src, NULL));

    pslist_src->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_merge_if__not_same(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(double);

    slist_init(pslist_dest);
    slist_init(pslist_src);
    expect_assert_failure(slist_merge_if(pslist_dest, pslist_src, NULL));

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_merge_if__same_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_merge_if(pslist, pslist, NULL);
    assert_true(slist_empty(pslist));

    slist_destroy(pslist);
}

void test_slist_merge_if__dest_empty_src_empty(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_dest);
    slist_init(pslist_src);
    slist_merge_if(pslist_dest, pslist_src, NULL);
    assert_true(slist_empty(pslist_dest));
    assert_true(slist_empty(pslist_src));

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_merge_if__dest_non_empty_src_empty(void** state)
{
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init_n(pslist_dest, 10);
    slist_init(pslist_src);
    slist_merge_if(pslist_dest, pslist_src, NULL);
    assert_true(slist_size(pslist_dest) == 10);
    assert_true(slist_empty(pslist_src));

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_merge_if__dest_empty_src_non_empty(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_dest);
    slist_init_n(pslist_src, 10);
    slist_merge_if(pslist_dest, pslist_src, NULL);
    assert_true(slist_size(pslist_dest) == 10);
    assert_true(slist_empty(pslist_src));
    for(it_iter = slist_begin(pslist_dest);
        !iterator_equal(it_iter, slist_end(pslist_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_merge_if__ascending_dest_tailing(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_dest);
    slist_push_front(pslist_dest, 9);
    slist_push_front(pslist_dest, 8);
    slist_push_front(pslist_dest, 5);
    slist_push_front(pslist_dest, 4);
    slist_init(pslist_src);
    slist_push_front(pslist_src, 7);
    slist_push_front(pslist_src, 3);
    slist_push_front(pslist_src, 2);
    slist_merge_if(pslist_dest, pslist_src, NULL);
    assert_true(slist_size(pslist_dest) == 7);
    assert_true(slist_empty(pslist_src));
    it_iter = slist_begin(pslist_dest);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_merge_if__ascending_src_tailing(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_dest);
    slist_push_front(pslist_dest, 7);
    slist_push_front(pslist_dest, 5);
    slist_push_front(pslist_dest, 5);
    slist_push_front(pslist_dest, 3);
    slist_init(pslist_src);
    slist_push_front(pslist_src, 9);
    slist_push_front(pslist_src, 8);
    slist_push_front(pslist_src, 7);
    slist_push_front(pslist_src, 3);
    slist_push_front(pslist_src, 2);
    slist_merge_if(pslist_dest, pslist_src, NULL);
    assert_true(slist_size(pslist_dest) == 9);
    assert_true(slist_empty(pslist_src));
    it_iter = slist_begin(pslist_dest);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_merge_if__descending_dest_tailing(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_dest);
    slist_push_front(pslist_dest, 2);
    slist_push_front(pslist_dest, 3);
    slist_push_front(pslist_dest, 3);
    slist_push_front(pslist_dest, 5);
    slist_push_front(pslist_dest, 8);
    slist_init(pslist_src);
    slist_push_front(pslist_src, 3);
    slist_push_front(pslist_src, 7);
    slist_push_front(pslist_src, 8);
    slist_push_front(pslist_src, 9);
    slist_merge_if(pslist_dest, pslist_src, fun_greater_int);
    assert_true(slist_size(pslist_dest) == 9);
    assert_true(slist_empty(pslist_src));
    it_iter = slist_begin(pslist_dest);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_merge_if__descending_src_tailing(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_dest);
    slist_push_front(pslist_dest, 3);
    slist_push_front(pslist_dest, 3);
    slist_push_front(pslist_dest, 5);
    slist_push_front(pslist_dest, 8);
    slist_init(pslist_src);
    slist_push_front(pslist_src, 2);
    slist_push_front(pslist_src, 3);
    slist_push_front(pslist_src, 7);
    slist_push_front(pslist_src, 8);
    slist_push_front(pslist_src, 9);
    slist_merge_if(pslist_dest, pslist_src, fun_greater_int);
    assert_true(slist_size(pslist_dest) == 9);
    assert_true(slist_empty(pslist_src));
    it_iter = slist_begin(pslist_dest);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_merge_if__random(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_dest = create_slist(int);
    slist_t* pslist_src = create_slist(int);

    slist_init(pslist_dest);
    slist_push_front(pslist_dest, 3);
    slist_push_front(pslist_dest, 5);
    slist_push_front(pslist_dest, 8);
    slist_push_front(pslist_dest, 3);
    slist_init(pslist_src);
    slist_push_front(pslist_src, 2);
    slist_push_front(pslist_src, 8);
    slist_push_front(pslist_src, 7);
    slist_push_front(pslist_src, 9);
    slist_push_front(pslist_src, 3);
    slist_merge_if(pslist_dest, pslist_src, NULL);
    assert_true(slist_size(pslist_dest) == 9);
    assert_true(slist_empty(pslist_src));
    it_iter = slist_begin(pslist_dest);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 8);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_merge_if__cstr_ascending_dest_tailing(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_dest = create_slist(char*);
    slist_t* pslist_src = create_slist(char*);

    slist_init(pslist_dest);
    slist_push_front(pslist_dest, "9");
    slist_push_front(pslist_dest, "8");
    slist_push_front(pslist_dest, "5");
    slist_push_front(pslist_dest, "4");
    slist_init(pslist_src);
    slist_push_front(pslist_src, "7");
    slist_push_front(pslist_src, "3");
    slist_push_front(pslist_src, "2");
    slist_merge_if(pslist_dest, pslist_src, NULL);
    assert_true(slist_size(pslist_dest) == 7);
    assert_true(slist_empty(pslist_src));
    it_iter = slist_begin(pslist_dest);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "2") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "4") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "9") == 0);

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_merge_if__cstr_ascending_src_tailing(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_dest = create_slist(char*);
    slist_t* pslist_src = create_slist(char*);

    slist_init(pslist_dest);
    slist_push_front(pslist_dest, "7");
    slist_push_front(pslist_dest, "5");
    slist_push_front(pslist_dest, "5");
    slist_push_front(pslist_dest, "3");
    slist_init(pslist_src);
    slist_push_front(pslist_src, "9");
    slist_push_front(pslist_src, "8");
    slist_push_front(pslist_src, "7");
    slist_push_front(pslist_src, "3");
    slist_push_front(pslist_src, "2");
    slist_merge_if(pslist_dest, pslist_src, NULL);
    assert_true(slist_size(pslist_dest) == 9);
    assert_true(slist_empty(pslist_src));
    it_iter = slist_begin(pslist_dest);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "2") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "9") == 0);

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_merge_if__cstr_descending_dest_tailing(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_dest = create_slist(char*);
    slist_t* pslist_src = create_slist(char*);

    slist_init(pslist_dest);
    slist_push_front(pslist_dest, "2");
    slist_push_front(pslist_dest, "4");
    slist_push_front(pslist_dest, "5");
    slist_push_front(pslist_dest, "8");
    slist_push_front(pslist_dest, "9");
    slist_init(pslist_src);
    slist_push_front(pslist_src, "3");
    slist_push_front(pslist_src, "7");
    slist_merge_if(pslist_dest, pslist_src, fun_greater_cstr);
    assert_true(slist_size(pslist_dest) == 7);
    assert_true(slist_empty(pslist_src));
    it_iter = slist_begin(pslist_dest);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "9") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "4") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "2") == 0);

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_merge_if__cstr_descending_src_tailing(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_dest = create_slist(char*);
    slist_t* pslist_src = create_slist(char*);

    slist_init(pslist_dest);
    slist_push_front(pslist_dest, "3");
    slist_push_front(pslist_dest, "5");
    slist_push_front(pslist_dest, "5");
    slist_push_front(pslist_dest, "7");
    slist_init(pslist_src);
    slist_push_front(pslist_src, "2");
    slist_push_front(pslist_src, "3");
    slist_push_front(pslist_src, "7");
    slist_push_front(pslist_src, "8");
    slist_push_front(pslist_src, "9");
    slist_merge_if(pslist_dest, pslist_src, fun_greater_cstr);
    assert_true(slist_size(pslist_dest) == 9);
    assert_true(slist_empty(pslist_src));
    it_iter = slist_begin(pslist_dest);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "9") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "2") == 0);

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

void test_slist_merge_if__cstr_random(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist_dest = create_slist(char*);
    slist_t* pslist_src = create_slist(char*);

    slist_init(pslist_dest);
    slist_push_front(pslist_dest, "3");
    slist_push_front(pslist_dest, "5");
    slist_push_front(pslist_dest, "8");
    slist_push_front(pslist_dest, "3");
    slist_init(pslist_src);
    slist_push_front(pslist_src, "2");
    slist_push_front(pslist_src, "8");
    slist_push_front(pslist_src, "7");
    slist_push_front(pslist_src, "9");
    slist_push_front(pslist_src, "3");
    slist_merge_if(pslist_dest, pslist_src, NULL);
    assert_true(slist_size(pslist_dest) == 9);
    assert_true(slist_empty(pslist_src));
    it_iter = slist_begin(pslist_dest);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "5") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "3") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "9") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "7") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "8") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "2") == 0);

    slist_destroy(pslist_dest);
    slist_destroy(pslist_src);
}

/*
 * test slist_reverse
 */
UT_CASE_DEFINATION(slist_reverse)
void test_slist_reverse__null_slist_container(void** state)
{
    expect_assert_failure(slist_reverse(NULL));
}

void test_slist_reverse__non_inited_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    pslist->_t_typeinfo._t_style = 34545;
    expect_assert_failure(slist_reverse(pslist));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test_slist_reverse__empty(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_reverse(pslist);
    assert_true(slist_empty(pslist));

    slist_destroy(pslist);
}

void test_slist_reverse__same(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_iterator_t it_iter;

    slist_init_elem(pslist, 10, 100);
    slist_reverse(pslist);
    assert_true(slist_size(pslist) == 10);
    for(it_iter = slist_begin(pslist);
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    slist_destroy(pslist);
}

void test_slist_reverse__not_same(void** state)
{
    slist_t* pslist = create_slist(int);
    size_t i = 0;
    slist_iterator_t it_iter;

    slist_init(pslist);
    for(i = 0; i < 10; ++i)
    {
        slist_push_front(pslist, i);
    }
    slist_reverse(pslist);
    assert_true(slist_size(pslist) == 10);
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == i);
    }

    slist_destroy(pslist);
}

