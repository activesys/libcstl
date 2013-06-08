#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/cstl_list_iterator.h"
#include "cstl/clist.h"
#include "cstl_list_aux.h"
#include "cstl/cvector.h"
#include "cstl/cdeque.h"
#include "cstl_vector_aux.h"
#include "cstl/cstring.h"
#include "cstl/cfunctional.h"
#include "cstl/cslist.h"

#include "ut_def.h"
#include "ut_cstl_list.h"

UT_SUIT_DEFINATION(cstl_list, list_init)

/*
 * test list_init
 */        
UT_CASE_DEFINATION(list_init)
void test_list_init__null_list_container(void** state)
{
    expect_assert_failure(list_init(NULL));
}

void test_list_init__non_created_list_container(void** state)
{
    list_t list;
    list._pt_node = (_listnode_t*)0x9383;
    expect_assert_failure(list_init(&list));
}

void test_list_init__successfully(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    assert_true(_list_is_inited(plist));
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

/*
 * test list_init_n
 */
UT_CASE_DEFINATION(list_init_n)
void test_list_init_n__null_list_container(void** state)
{
    expect_assert_failure(list_init_n(NULL, 10));
}

void test_list_init_n__non_created_list_container(void** state)
{
    list_t list;
    list._pt_node = (_listnode_t*)0x73734;
    expect_assert_failure(list_init_n(&list, 10));
}

void test_list_init_n__empty(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 0);
    assert_true(_list_is_inited(plist));
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

void test_list_init_n__c_builtin(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    assert_true(_list_is_inited(plist));
    assert_true(list_size(plist) == 10);
    for(it_iter = list_begin(plist);
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    list_destroy(plist);
}

void test_list_init_n__cstr(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init_n(plist, 10);
    assert_true(_list_is_inited(plist));
    assert_true(list_size(plist) == 10);
    for(it_iter = list_begin(plist);
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    }

    list_destroy(plist);
}

void test_list_init_n__libcstl_builtin(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(vector_t<int>);

    list_init_n(plist, 10);
    assert_true(_list_is_inited(plist));
    assert_true(list_size(plist) == 10);
    for(it_iter = list_begin(plist);
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(_vector_is_inited((vector_t*)iterator_get_pointer(it_iter)));
        assert_true(vector_size((vector_t*)iterator_get_pointer(it_iter)) == 0);
    }

    list_destroy(plist);
}

typedef struct _tag_test_list_init_n__user_define
{
    int n_elem;
}_test_list_init_n__user_define_t;
void test_list_init_n__user_define(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = NULL;

    type_register(_test_list_init_n__user_define_t, NULL, NULL, NULL, NULL);
    plist = create_list(_test_list_init_n__user_define_t);

    list_init_n(plist, 10);
    assert_true(_list_is_inited(plist));
    assert_true(list_size(plist) == 10);
    for(it_iter = list_begin(plist);
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(((_test_list_init_n__user_define_t*)iterator_get_pointer(it_iter))->n_elem == 0);
    }

    list_destroy(plist);
}

/*
 * test list_destroy
 */
UT_CASE_DEFINATION(list_destroy)
void test_list_destroy__null_list_container(void** state)
{
    expect_assert_failure(list_destroy(NULL));
}

void test_list_destroy__non_created_list_container(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    plist->_pt_node->_pt_next = NULL;
    expect_assert_failure(list_destroy(plist));

    plist->_pt_node->_pt_next = plist->_pt_node;
    list_destroy(plist);
}

void test_list_destroy__created_non_inited(void** state)
{
    list_t* plist = create_list(int);

    list_destroy(plist);
}

void test_list_destroy__empty(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    list_destroy(plist);
}

void test_list_destroy__non_empty(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    list_destroy(plist);
}

/*
 * test list_init_copy
 */
UT_CASE_DEFINATION(list_init_copy)
void test_list_init_copy__null_dest_list_container(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_src);
    expect_assert_failure(list_init_copy(NULL, plist_src));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_init_copy__null_src_list_container(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    expect_assert_failure(list_init_copy(plist_dest, NULL));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_init_copy__non_created_dest_list_container(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_src);
    plist_dest->_pt_node = (_listnode_t*)0x3333;
    expect_assert_failure(list_init_copy(plist_dest, plist_src));

    plist_dest->_pt_node = NULL;
    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_init_copy__non_inited_src_list_container(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_src);
    plist_src->_pt_node->_pt_next = NULL;
    expect_assert_failure(list_init_copy(plist_dest, plist_src));

    plist_src->_pt_node->_pt_next = plist_src->_pt_node;
    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_init_copy__not_same_type(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(double);

    list_init(plist_src);
    expect_assert_failure(list_init_copy(plist_dest, plist_src));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_init_copy__init_copy_empty(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_src);
    list_init_copy(plist_dest, plist_src);
    assert_true(_list_is_inited(plist_dest));
    assert_true(list_size(plist_dest) == list_size(plist_src));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_init_copy__c_builtin(void** state)
{
    list_iterator_t it_dest;
    list_iterator_t it_src;
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init_elem(plist_src, 10, 100);
    list_push_front(plist_src, 1943);
    list_push_back(plist_src, 345);
    list_init_copy(plist_dest, plist_src);
    assert_true(_list_is_inited(plist_dest));
    assert_true(list_size(plist_dest) == list_size(plist_src));
    for(it_dest = list_begin(plist_dest), it_src = list_begin(plist_src);
        !iterator_equal(it_dest, list_end(plist_dest)) && !iterator_equal(it_src, list_end(plist_src));
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        assert_true(*(int*)iterator_get_pointer(it_dest) == *(int*)iterator_get_pointer(it_src));
    }

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_init_copy__cstr(void** state)
{
    list_iterator_t it_dest;
    list_iterator_t it_src;
    list_t* plist_dest = create_list(char*);
    list_t* plist_src = create_list(char*);

    list_init_elem(plist_src, 10, "abcdefg");
    list_push_front(plist_src, "222222");
    list_push_back(plist_src, "aldjflakdjf");
    list_init_copy(plist_dest, plist_src);
    assert_true(_list_is_inited(plist_dest));
    assert_true(list_size(plist_dest) == list_size(plist_src));
    for(it_dest = list_begin(plist_dest), it_src = list_begin(plist_src);
        !iterator_equal(it_dest, list_end(plist_dest)) && !iterator_equal(it_src, list_end(plist_src));
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        assert_true(strcmp((char*)iterator_get_pointer(it_dest), (char*)iterator_get_pointer(it_src)) == 0);
    }

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_init_copy__libcstl_builtin(void** state)
{
    list_iterator_t it_dest;
    list_iterator_t it_src;
    list_t* plist_dest = create_list(list_t<int>);
    list_t* plist_src = create_list(list_t<signed>);

    list_init_n(plist_src, 10);
    list_init_copy(plist_dest, plist_src);
    assert_true(_list_is_inited(plist_dest));
    assert_true(list_size(plist_dest) == list_size(plist_src));
    for(it_dest = list_begin(plist_dest), it_src = list_begin(plist_src);
        !iterator_equal(it_dest, list_end(plist_dest)) && !iterator_equal(it_src, list_end(plist_src));
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        assert_true(list_equal((list_t*)iterator_get_pointer(it_dest), (list_t*)iterator_get_pointer(it_src)));
    }

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

typedef struct _tag_test_list_init_copy__user_define
{
    int n_elem;
}_test_list_init_copy__user_define_t;
void test_list_init_copy__user_define(void** state)
{
    list_iterator_t it_dest;
    list_iterator_t it_src;
    list_t* plist_dest = NULL;
    list_t* plist_src = NULL;

    type_register(_test_list_init_copy__user_define_t, NULL, NULL, NULL, NULL);
    type_duplicate(_test_list_init_copy__user_define_t, struct _tag_test_list_init_copy__user_define);
    plist_dest = create_list(_test_list_init_copy__user_define_t);
    plist_src = create_list(struct _tag_test_list_init_copy__user_define);

    list_init_n(plist_src, 10);
    list_init_copy(plist_dest, plist_src);
    assert_true(_list_is_inited(plist_dest));
    assert_true(list_size(plist_dest) == list_size(plist_src));
    for(it_dest = list_begin(plist_dest), it_src = list_begin(plist_src);
        !iterator_equal(it_dest, list_end(plist_dest)) && !iterator_equal(it_src, list_end(plist_src));
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        assert_true(((_test_list_init_copy__user_define_t*)iterator_get_pointer(it_dest))->n_elem ==
            ((_test_list_init_copy__user_define_t*)iterator_get_pointer(it_src))->n_elem);
    }

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

/*
 * test list_init_copy_range
 */
UT_CASE_DEFINATION(list_init_copy_range)
void test_list_init_copy_range__null_list_container(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_src);
    expect_assert_failure(list_init_copy_range(NULL, list_begin(plist_src), list_end(plist_src)));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_init_copy_range__non_created_list_container(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_src);
    plist_dest->_pt_node = (_listnode_t*)0x8383;
    expect_assert_failure(list_init_copy_range(plist_dest, list_begin(plist_src), list_end(plist_src)));

    plist_dest->_pt_node = NULL;
    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_init_copy_range__invalid_range(void** state)
{
    list_iterator_t it_begin;
    list_iterator_t it_end;
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init_n(plist_src, 10);
    it_begin = list_begin(plist_src);
    it_end = list_end(plist_src);
    expect_assert_failure(list_init_copy_range(plist_dest, it_end, it_begin));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_init_copy_range__not_same(void** state)
{
    list_iterator_t it_begin;
    list_iterator_t it_end;
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(double);

    list_init_n(plist_src, 10);
    it_begin = list_begin(plist_src);
    it_end = list_end(plist_src);
    expect_assert_failure(list_init_copy_range(plist_dest, it_begin, it_end));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_init_copy_range__init_copy_range_empty(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_src);
    list_init_copy_range(plist_dest, list_begin(plist_src), list_end(plist_src));
    assert_true(_list_is_inited(plist_dest));
    assert_true(list_size(plist_dest) == 0);

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_init_copy_range__c_builtin(void** state)
{
    list_iterator_t it_begin;
    list_iterator_t it_end;
    list_iterator_t it_dest;
    list_iterator_t it_src;
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init_elem(plist_src, 10, 100);
    list_push_front(plist_src, 1943);
    list_push_back(plist_src, 345);
    it_begin = list_begin(plist_src);
    it_end = iterator_advance(it_begin, 3);
    list_init_copy_range(plist_dest, it_begin, it_end);
    assert_true(_list_is_inited(plist_dest));
    assert_true(list_size(plist_dest) == 3);
    for(it_dest = list_begin(plist_dest), it_src = it_begin;
        !iterator_equal(it_dest, list_end(plist_dest)) && !iterator_equal(it_src, it_end);
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        assert_true(*(int*)iterator_get_pointer(it_dest) == *(int*)iterator_get_pointer(it_src));
    }

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_init_copy_range__cstr(void** state)
{
    list_iterator_t it_begin;
    list_iterator_t it_end;
    list_iterator_t it_dest;
    list_iterator_t it_src;
    list_t* plist_dest = create_list(char*);
    list_t* plist_src = create_list(char*);

    list_init_elem(plist_src, 10, "abcdefg");
    list_push_front(plist_src, "222222");
    list_push_back(plist_src, "aldjflakdjf");
    it_begin = iterator_advance(list_begin(plist_src), 3);
    it_end = iterator_advance(it_begin, 3);
    list_init_copy_range(plist_dest, it_begin, it_end);
    assert_true(_list_is_inited(plist_dest));
    assert_true(list_size(plist_dest) == 3);
    for(it_dest = list_begin(plist_dest), it_src = it_begin;
        !iterator_equal(it_dest, list_end(plist_dest)) && !iterator_equal(it_src, it_end);
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        assert_true(strcmp((char*)iterator_get_pointer(it_dest), (char*)iterator_get_pointer(it_src)) == 0);
    }

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_init_copy_range__libcstl_builtin(void** state)
{
    list_iterator_t it_begin;
    list_iterator_t it_end;
    list_iterator_t it_dest;
    list_iterator_t it_src;
    list_t* plist_dest = create_list(list_t<int>);
    list_t* plist_src = create_list(list_t<signed>);

    list_init_n(plist_src, 10);
    it_begin = iterator_advance(list_begin(plist_src), 3);
    it_end = list_end(plist_src);
    list_init_copy_range(plist_dest, it_begin, it_end);
    assert_true(_list_is_inited(plist_dest));
    assert_true(list_size(plist_dest) == 7);
    for(it_dest = list_begin(plist_dest), it_src = it_begin;
        !iterator_equal(it_dest, list_end(plist_dest)) && !iterator_equal(it_src, it_end);
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        assert_true(list_equal((list_t*)iterator_get_pointer(it_dest), (list_t*)iterator_get_pointer(it_src)));
    }

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

typedef struct _tag_test_list_init_copy_range__user_define
{
    int n_elem;
}_test_list_init_copy_range__user_define_t;
void test_list_init_copy_range__user_define(void** state)
{
    list_iterator_t it_dest;
    list_iterator_t it_src;
    list_t* plist_dest = NULL;
    list_t* plist_src = NULL;

    type_register(_test_list_init_copy_range__user_define_t, NULL, NULL, NULL, NULL);
    type_duplicate(_test_list_init_copy_range__user_define_t, struct _tag_test_list_init_copy_range__user_define);
    plist_dest = create_list(_test_list_init_copy_range__user_define_t);
    plist_src = create_list(struct _tag_test_list_init_copy_range__user_define);

    list_init_n(plist_src, 10);
    list_init_copy_range(plist_dest, list_begin(plist_src), list_end(plist_src));
    assert_true(_list_is_inited(plist_dest));
    assert_true(list_size(plist_dest) == list_size(plist_src));
    for(it_dest = list_begin(plist_dest), it_src = list_begin(plist_src);
        !iterator_equal(it_dest, list_end(plist_dest)) && !iterator_equal(it_src, list_end(plist_src));
        it_dest = iterator_next(it_dest), it_src = iterator_next(it_src))
    {
        assert_true(((_test_list_init_copy_range__user_define_t*)iterator_get_pointer(it_dest))->n_elem ==
            ((_test_list_init_copy_range__user_define_t*)iterator_get_pointer(it_src))->n_elem);
    }

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_init_copy_range__other_container_range(void** state)
{
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;

    vector_init_elem(pvec, 10, 100);
    list_init_copy_range(plist, vector_begin(pvec), vector_end(pvec));

    assert_true(list_size(plist) == 10);
    for(it_iter = list_begin(plist); !iterator_equal(it_iter, list_end(plist)); it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    list_destroy(plist);
    vector_destroy(pvec);
}

void test_list_init_copy_range__other_container_range1(void** state)
{
    list_t* plist = create_list(vector_t<int>);
    slist_t* pslist = create_slist(vector_t<int>);
    vector_t* pvec = create_vector(int);
    list_iterator_t it_iter;

    vector_init_n(pvec, 84);
    slist_init_elem(pslist, 10, pvec);
    list_init_copy_range(plist, slist_begin(pslist), slist_end(pslist));
    assert_true(list_size(plist) == 10);
    for(it_iter = list_begin(plist); !iterator_equal(it_iter, list_end(plist)); it_iter = iterator_next(it_iter))
    {
        assert_true(vector_size((vector_t*)iterator_get_pointer(it_iter)) == 84);
    }

    vector_destroy(pvec);
    list_destroy(plist);
    slist_destroy(pslist);
}

/*
 * test list_init_copy_array
 */
UT_CASE_DEFINATION(list_init_copy_array)
void test_list_init_copy_array__null_list_container(void** state)
{
    int an_array[10] = {0};

    expect_assert_failure(list_init_copy_array(NULL, an_array, 10));
}

void test_list_init_copy_array__non_created_list_container(void** state)
{
    list_t* plist_dest = create_list(int);
    int an_array[10] = {0};

    plist_dest->_pt_node = (_listnode_t*)0x8383;
    expect_assert_failure(list_init_copy_array(plist_dest, an_array, 10));

    plist_dest->_pt_node = NULL;
    list_destroy(plist_dest);
}

void test_list_init_copy_array__invalid_array(void** state)
{
    list_t* plist_dest = create_list(int);

    expect_assert_failure(list_init_copy_array(plist_dest, NULL, 5));

    list_destroy(plist_dest);
}

void test_list_init_copy_array__init_copy_array_empty(void** state)
{
    list_t* plist_dest = create_list(int);
    int an_array[10] = {0};

    list_init_copy_array(plist_dest, an_array, 0);
    assert_true(_list_is_inited(plist_dest));
    assert_true(list_size(plist_dest) == 0);

    list_destroy(plist_dest);
}

void test_list_init_copy_array__c_builtin(void** state)
{
    int an_array[10] = {0};
    int i = 0;
    list_t* plist_dest = create_list(int);
    list_iterator_t it_dest;


    for (i = 0; i < 10; ++i) {
        an_array[i] = i * 100;
    }
    list_init_copy_array(plist_dest, an_array, 10);
    assert_true(_list_is_inited(plist_dest));
    assert_true(list_size(plist_dest) == 10);
    for(it_dest = list_begin(plist_dest), i = 0;
        !iterator_equal(it_dest, list_end(plist_dest)) && i < 10;
        it_dest = iterator_next(it_dest), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_dest) == an_array[i]);
    }

    list_destroy(plist_dest);
}

void test_list_init_copy_array__cstr(void** state)
{
    list_iterator_t it_dest;
    list_t* plist_dest = create_list(char*);
    int i = 0;
    const char* as_array[] = {
        "abc", "nba", "nbc", "bbc", "ddd"
    };

    list_init_copy_array(plist_dest, as_array, 5);
    assert_true(_list_is_inited(plist_dest));
    assert_true(list_size(plist_dest) == 5);
    for(it_dest = list_begin(plist_dest), i = 0;
        !iterator_equal(it_dest, list_end(plist_dest)) && i < 5;
        it_dest = iterator_next(it_dest), ++i)
    {
        assert_true(strcmp((char*)iterator_get_pointer(it_dest), as_array[i]) == 0);
    }

    list_destroy(plist_dest);
}

void test_list_init_copy_array__libcstl_builtin(void** state)
{
    list_iterator_t it_dest;
    list_t* plist_dest = create_list(list_t<int>);
    list_t* aplist_array[10] = {NULL};
    int i = 0;

    for (i = 0; i < 10; ++i) {
        aplist_array[i] = create_list(int);
        list_init_elem(aplist_array[i], i, i);
    }
    list_init_copy_array(plist_dest, aplist_array, 10);
    assert_true(_list_is_inited(plist_dest));
    assert_true(list_size(plist_dest) == 10);
    for(it_dest = list_begin(plist_dest), i = 0;
        !iterator_equal(it_dest, list_end(plist_dest)) && i < 10;
        it_dest = iterator_next(it_dest), ++i)
    {
        assert_true(list_equal((list_t*)iterator_get_pointer(it_dest), aplist_array[i]));
    }

    list_destroy(plist_dest);
    for (i = 0; i < 10; ++i) {
        list_destroy(aplist_array[i]);
    }
}

typedef struct _tag_test_list_init_copy_array__user_define
{
    int n_elem;
}_test_list_init_copy_array__user_define_t;
void test_list_init_copy_array__user_define(void** state)
{
    list_iterator_t it_dest;
    list_t* plist_dest = NULL;
    _test_list_init_copy_array__user_define_t* apt_array[10] = {NULL};
    int i = 0;

    type_register(_test_list_init_copy_array__user_define_t, NULL, NULL, NULL, NULL);
    type_duplicate(_test_list_init_copy_array__user_define_t, struct _tag_test_list_init_copy_array__user_define);
    plist_dest = create_list(_test_list_init_copy_array__user_define_t);

    for (i = 0; i < 10; ++i) {
        apt_array[i] = malloc(sizeof(_test_list_init_copy_array__user_define_t));
        apt_array[i]->n_elem = i;
    }
    list_init_copy_array(plist_dest, apt_array, 10);
    assert_true(_list_is_inited(plist_dest));
    assert_true(list_size(plist_dest) == 10);
    for(it_dest = list_begin(plist_dest), i = 0;
        !iterator_equal(it_dest, list_end(plist_dest)) && i < 10;
        it_dest = iterator_next(it_dest), ++i)
    {
        assert_true(((_test_list_init_copy_array__user_define_t*)iterator_get_pointer(it_dest))->n_elem ==
            apt_array[i]->n_elem);
    }

    list_destroy(plist_dest);
    for (i = 0; i < 10; ++i) {
        free(apt_array[i]);
    }
}

/*
 * test list_size
 */
UT_CASE_DEFINATION(list_size)
void test_list_size__null_list_container(void** state)
{
    expect_assert_failure(list_size(NULL));
}

void test_list_size__non_inited_list_container(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(list_size(plist));

    list_destroy(plist);
}

void test_list_size__empty(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

void test_list_size__non_empty(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    assert_true(list_size(plist) == 10);

    list_destroy(plist);
}

/*
 * test list_empty
 */
UT_CASE_DEFINATION(list_empty)
void test_list_empty__null_list_container(void** state)
{
    expect_assert_failure(list_empty(NULL));
}

void test_list_empty__non_inited_list_container(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(list_empty(plist));

    list_destroy(plist);
}

void test_list_empty__empty(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    assert_true(list_empty(plist));

    list_destroy(plist);
}

void test_list_empty__non_empty(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    assert_false(list_empty(plist));

    list_destroy(plist);
}

/*
 * test list_max_size
 */
UT_CASE_DEFINATION(list_max_size)
void test_list_max_size__null_list_container(void** state)
{
    expect_assert_failure(list_max_size(NULL));
}

void test_list_max_size__non_inited_list_container(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(list_max_size(plist));

    list_destroy(plist);
}

void test_list_max_size__empty(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    assert_true(list_max_size(plist) != 0);

    list_destroy(plist);
}

void test_list_max_size__non_empty(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    assert_true(list_max_size(plist) != 0);

    list_destroy(plist);
}

/*
 * test list_equal
 */
UT_CASE_DEFINATION(list_equal)
void test_list_equal__null_first(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    expect_assert_failure(list_equal(NULL, plist));

    list_destroy(plist);
}

void test_list_equal__null_second(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    expect_assert_failure(list_equal(plist, NULL));

    list_destroy(plist);
}

void test_list_equal__non_inited_first(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_second);
    expect_assert_failure(list_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_equal__non_inited_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_first);
    expect_assert_failure(list_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_equal__not_same_type(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(double);

    list_init(plist_first);
    list_init(plist_second);
    expect_assert_failure(list_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_equal__same_list(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    assert_true(list_equal(plist, plist));

    list_destroy(plist);
}

void test_list_equal__size_first_less_than_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_first);
    list_init_n(plist_second, 48);
    assert_false(list_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_equal__size_first_greater_than_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init_n(plist_first, 233);
    list_init_n(plist_second, 48);
    assert_false(list_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_equal__size_equal_0(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_first);
    list_init(plist_second);
    assert_true(list_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_equal__size_equal_elem_first_less_than_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init_elem(plist_first, 10, 100);
    list_init_elem(plist_second, 10, 4545);
    assert_false(list_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_equal__size_equal_elem_first_greater_than_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init_elem(plist_first, 10, 100);
    list_init_elem(plist_second, 10, 45);
    assert_false(list_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_equal__size_equal_elem_equal(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init_elem(plist_first, 10, 100);
    list_init_elem(plist_second, 10, 100);
    assert_true(list_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

/*
 * test list_not_equal
 */
UT_CASE_DEFINATION(list_not_equal)
void test_list_not_equal__null_first(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    expect_assert_failure(list_not_equal(NULL, plist));

    list_destroy(plist);
}

void test_list_not_equal__null_second(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    expect_assert_failure(list_not_equal(plist, NULL));

    list_destroy(plist);
}

void test_list_not_equal__non_inited_first(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_second);
    expect_assert_failure(list_not_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_not_equal__non_inited_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_first);
    expect_assert_failure(list_not_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_not_equal__not_same_type(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(double);

    list_init(plist_first);
    list_init(plist_second);
    expect_assert_failure(list_not_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_not_equal__same_list(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    assert_false(list_not_equal(plist, plist));

    list_destroy(plist);
}

void test_list_not_equal__size_first_less_than_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_first);
    list_init_n(plist_second, 48);
    assert_true(list_not_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_not_equal__size_first_greater_than_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init_n(plist_first, 233);
    list_init_n(plist_second, 48);
    assert_true(list_not_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_not_equal__size_equal_0(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_first);
    list_init(plist_second);
    assert_false(list_not_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_not_equal__size_equal_elem_first_less_than_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init_elem(plist_first, 10, 100);
    list_init_elem(plist_second, 10, 4545);
    assert_true(list_not_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_not_equal__size_equal_elem_first_greater_than_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init_elem(plist_first, 10, 100);
    list_init_elem(plist_second, 10, 45);
    assert_true(list_not_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_not_equal__size_equal_elem_equal(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init_elem(plist_first, 10, 100);
    list_init_elem(plist_second, 10, 100);
    assert_false(list_not_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

/*
 * test list_less
 */
UT_CASE_DEFINATION(list_less)
void test_list_less__null_first(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    expect_assert_failure(list_less(NULL, plist));

    list_destroy(plist);
}

void test_list_less__null_second(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    expect_assert_failure(list_less(plist, NULL));

    list_destroy(plist);
}

void test_list_less__non_inited_first(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_second);
    expect_assert_failure(list_less(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_less__non_inited_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_first);
    expect_assert_failure(list_less(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_less__not_same_type(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(double);

    list_init(plist_first);
    list_init(plist_second);
    expect_assert_failure(list_less(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_less__same_list(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    assert_false(list_less(plist, plist));

    list_destroy(plist);
}

void test_list_less__size_first_less_than_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_first);
    list_init_n(plist_second, 48);
    assert_true(list_less(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_less__size_first_greater_than_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init_n(plist_first, 233);
    list_init_n(plist_second, 48);
    assert_false(list_less(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_less__size_equal_0(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_first);
    list_init(plist_second);
    assert_false(list_less(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_less__size_equal_elem_first_less_than_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init_elem(plist_first, 10, 100);
    list_init_elem(plist_second, 10, 4545);
    assert_true(list_less(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_less__size_equal_elem_first_greater_than_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init_elem(plist_first, 10, 100);
    list_init_elem(plist_second, 10, 45);
    assert_false(list_less(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_less__size_equal_elem_equal(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init_elem(plist_first, 10, 100);
    list_init_elem(plist_second, 10, 100);
    assert_false(list_less(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

/*
 * test list_less_equal
 */
UT_CASE_DEFINATION(list_less_equal)
void test_list_less_equal__null_first(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    expect_assert_failure(list_less_equal(NULL, plist));

    list_destroy(plist);
}

void test_list_less_equal__null_second(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    expect_assert_failure(list_less_equal(plist, NULL));

    list_destroy(plist);
}

void test_list_less_equal__non_inited_first(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_second);
    expect_assert_failure(list_less_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_less_equal__non_inited_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_first);
    expect_assert_failure(list_less_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_less_equal__not_same_type(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(double);

    list_init(plist_first);
    list_init(plist_second);
    expect_assert_failure(list_less_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_less_equal__same_list(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    assert_true(list_less_equal(plist, plist));

    list_destroy(plist);
}

void test_list_less_equal__size_first_less_than_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_first);
    list_init_n(plist_second, 48);
    assert_true(list_less_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_less_equal__size_first_greater_than_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init_n(plist_first, 233);
    list_init_n(plist_second, 48);
    assert_false(list_less_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_less_equal__size_equal_0(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_first);
    list_init(plist_second);
    assert_true(list_less_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_less_equal__size_equal_elem_first_less_than_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init_elem(plist_first, 10, 100);
    list_init_elem(plist_second, 10, 4545);
    assert_true(list_less_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_less_equal__size_equal_elem_first_greater_than_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init_elem(plist_first, 10, 100);
    list_init_elem(plist_second, 10, 45);
    assert_false(list_less_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_less_equal__size_equal_elem_equal(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init_elem(plist_first, 10, 100);
    list_init_elem(plist_second, 10, 100);
    assert_true(list_less_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

/*
 * test list_greater
 */
UT_CASE_DEFINATION(list_greater)
void test_list_greater__null_first(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    expect_assert_failure(list_greater(NULL, plist));

    list_destroy(plist);
}

void test_list_greater__null_second(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    expect_assert_failure(list_greater(plist, NULL));

    list_destroy(plist);
}

void test_list_greater__non_inited_first(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_second);
    expect_assert_failure(list_greater(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_greater__non_inited_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_first);
    expect_assert_failure(list_greater(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_greater__not_same_type(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(double);

    list_init(plist_first);
    list_init(plist_second);
    expect_assert_failure(list_greater(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_greater__same_list(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    assert_false(list_greater(plist, plist));

    list_destroy(plist);
}

void test_list_greater__size_first_less_than_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_first);
    list_init_n(plist_second, 48);
    assert_false(list_greater(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_greater__size_first_greater_than_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init_n(plist_first, 233);
    list_init_n(plist_second, 48);
    assert_true(list_greater(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_greater__size_equal_0(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_first);
    list_init(plist_second);
    assert_false(list_greater(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_greater__size_equal_elem_first_less_than_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init_elem(plist_first, 10, 100);
    list_init_elem(plist_second, 10, 4545);
    assert_false(list_greater(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_greater__size_equal_elem_first_greater_than_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init_elem(plist_first, 10, 100);
    list_init_elem(plist_second, 10, 45);
    assert_true(list_greater(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_greater__size_equal_elem_equal(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init_elem(plist_first, 10, 100);
    list_init_elem(plist_second, 10, 100);
    assert_false(list_greater(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

/*
 * test list_greater_equal
 */
UT_CASE_DEFINATION(list_greater_equal)
void test_list_greater_equal__null_first(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    expect_assert_failure(list_greater_equal(NULL, plist));

    list_destroy(plist);
}

void test_list_greater_equal__null_second(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    expect_assert_failure(list_greater_equal(plist, NULL));

    list_destroy(plist);
}

void test_list_greater_equal__non_inited_first(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_second);
    expect_assert_failure(list_greater_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_greater_equal__non_inited_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_first);
    expect_assert_failure(list_greater_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_greater_equal__not_same_type(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(double);

    list_init(plist_first);
    list_init(plist_second);
    expect_assert_failure(list_greater_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_greater_equal__same_list(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    assert_true(list_greater_equal(plist, plist));

    list_destroy(plist);
}

void test_list_greater_equal__size_first_less_than_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_first);
    list_init_n(plist_second, 48);
    assert_false(list_greater_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_greater_equal__size_first_greater_than_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init_n(plist_first, 233);
    list_init_n(plist_second, 48);
    assert_true(list_greater_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_greater_equal__size_equal_0(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_first);
    list_init(plist_second);
    assert_true(list_greater_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_greater_equal__size_equal_elem_first_less_than_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init_elem(plist_first, 10, 100);
    list_init_elem(plist_second, 10, 4545);
    assert_false(list_greater_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_greater_equal__size_equal_elem_first_greater_than_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init_elem(plist_first, 10, 100);
    list_init_elem(plist_second, 10, 45);
    assert_true(list_greater_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_greater_equal__size_equal_elem_equal(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init_elem(plist_first, 10, 100);
    list_init_elem(plist_second, 10, 100);
    assert_true(list_greater_equal(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

/*
 * test list_assign
 */
UT_CASE_DEFINATION(list_assign)
void test_list_assign__null_dest(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    expect_assert_failure(list_assign(NULL, plist));

    list_destroy(plist);
}

void test_list_assign__null_src(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    expect_assert_failure(list_assign(plist, NULL));

    list_destroy(plist);
}

void test_list_assign__non_inited_dest(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_src);

    expect_assert_failure(list_assign(plist_dest, plist_src));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_assign__non_inited_src(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_dest);

    expect_assert_failure(list_assign(plist_dest, plist_src));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_assign__not_same_type(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(double);

    list_init(plist_dest);
    list_init(plist_src);

    expect_assert_failure(list_assign(plist_dest, plist_src));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_assign__same_container(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);

    list_assign(plist, plist);
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

void test_list_assign__0_assign_0(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_dest);
    list_init(plist_src);

    list_assign(plist_dest, plist_src);
    assert_true(list_size(plist_dest) == 0);
    assert_true(list_equal(plist_dest, plist_src));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_assign__0_assign_10(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_dest);
    list_init_n(plist_src, 10);

    list_assign(plist_dest, plist_src);
    assert_true(list_size(plist_dest) == 10);
    assert_true(list_equal(plist_dest, plist_src));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_assign__10_assign_0(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init_n(plist_dest, 10);
    list_init(plist_src);

    list_assign(plist_dest, plist_src);
    assert_true(list_equal(plist_dest, plist_src));
    assert_true(list_size(plist_dest) == 0);

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_assign__10_assign_10_list_equal(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init_n(plist_dest, 10);
    list_init_n(plist_src, 10);

    list_assign(plist_dest, plist_src);
    assert_true(list_equal(plist_dest, plist_src));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_assign__10_assign_10_list_not_equal(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init_elem(plist_dest, 10, 100);
    list_init_n(plist_src, 10);

    list_assign(plist_dest, plist_src);
    assert_true(list_equal(plist_dest, plist_src));
    assert_true(list_size(plist_dest) == 10);

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_assign__10_assign_1000(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init_elem(plist_dest, 10, 100);
    list_init_n(plist_src, 1000);

    list_assign(plist_dest, plist_src);
    assert_true(list_equal(plist_dest, plist_src));
    assert_true(list_size(plist_dest) == 1000);

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

/*
 * test list_assign_range
 */
UT_CASE_DEFINATION(list_assign_range)
void test_list_assign_range__null_list_container(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    expect_assert_failure(list_assign_range(NULL, list_begin(plist), list_end(plist)));

    list_destroy(plist);
}

void test_list_assign_range__non_inited(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);
    list_init(plist_src);

    expect_assert_failure(list_assign_range(plist_dest, list_begin(plist_src), list_end(plist_src)));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_assign_range__invalid_it_begin(void** state)
{
    list_iterator_t it_begin;
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);
    list_init(plist_src);
    list_init(plist_dest);
    it_begin._t_iteratortype = 284;

    expect_assert_failure(list_assign_range(plist_dest, it_begin, list_end(plist_src)));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_assign_range__invalid_it_end(void** state)
{
    list_iterator_t it_end;
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);
    list_init(plist_src);
    list_init(plist_dest);
    it_end._t_iteratortype = 284;

    expect_assert_failure(list_assign_range(plist_dest, list_begin(plist_src), it_end));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_assign_range__invalid_range(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);
    list_init_n(plist_src, 12);
    list_init(plist_dest);

    expect_assert_failure(list_assign_range(plist_dest, list_end(plist_src), list_begin(plist_src)));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_assign_range__invalid_range_not_same_type(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(double);
    list_init_n(plist_src, 12);
    list_init(plist_dest);

    expect_assert_failure(list_assign_range(plist_dest, list_begin(plist_src), list_end(plist_src)));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_assign_range__range_belong_to_list(void** state)
{
    list_t* plist_dest = create_list(int);
    list_init(plist_dest);

    list_assign_range(plist_dest, list_begin(plist_dest), list_end(plist_dest));

    list_destroy(plist_dest);
}

void test_list_assign_range__0_assign_range_0(void** state)
{
    size_t i = 0;
    list_iterator_t it_begin;
    list_iterator_t it_end;
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);
    list_init_elem(plist_src, 1200, 100);
    list_init(plist_dest);

    it_begin = list_begin(plist_src);
    it_end = list_begin(plist_src);
    list_assign_range(plist_dest, it_begin, it_end);
    assert_true(list_size(plist_dest) == iterator_distance(it_begin, it_end));
    assert_true(list_size(plist_dest) == 0);

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_assign_range__0_assign_range_10(void** state)
{
    list_iterator_t it_iter;
    list_iterator_t it_begin;
    list_iterator_t it_end;
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);
    list_init_elem(plist_src, 1200, 100);
    list_init(plist_dest);

    it_begin = list_begin(plist_src);
    it_end = iterator_advance(it_begin, 10);
    list_assign_range(plist_dest, it_begin, it_end);
    assert_true(list_size(plist_dest) == iterator_distance(it_begin, it_end));
    assert_true(list_size(plist_dest) == 10);
    for(it_iter = list_begin(plist_dest);
        !iterator_equal(it_iter, list_end(plist_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_assign_range__10_assign_range_0(void** state)
{
    list_iterator_t it_iter;
    list_iterator_t it_begin;
    list_iterator_t it_end;
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);
    list_init_elem(plist_src, 1200, 100);
    list_init_elem(plist_dest, 10, 700);

    it_begin = iterator_advance(list_begin(plist_src), 111);
    it_end = it_begin;
    list_assign_range(plist_dest, it_begin, it_end);
    assert_true(list_size(plist_dest) == iterator_distance(it_begin, it_end));
    assert_true(list_size(plist_dest) == 0);
    for(it_iter = list_begin(plist_dest);
        !iterator_equal(it_iter, list_end(plist_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_assign_range__10_assign_range_10_same_elem(void** state)
{
    list_iterator_t it_iter;
    list_iterator_t it_begin;
    list_iterator_t it_end;
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);
    list_init_elem(plist_src, 1200, 100);
    list_init_elem(plist_dest, 10, 100);

    it_begin = iterator_advance(list_begin(plist_src), 111);
    it_end = iterator_advance(it_begin, 10);
    list_assign_range(plist_dest, it_begin, it_end);
    assert_true(list_size(plist_dest) == iterator_distance(it_begin, it_end));
    assert_true(list_size(plist_dest) == 10);
    for(it_iter = list_begin(plist_dest);
        !iterator_equal(it_iter, list_end(plist_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_assign_range__10_assign_range_10_not_same_elem(void** state)
{
    list_iterator_t it_iter;
    list_iterator_t it_begin;
    list_iterator_t it_end;
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);
    list_init_elem(plist_src, 1200, 100);
    list_init_elem(plist_dest, 10, 0);

    it_begin = iterator_advance(list_begin(plist_src), 111);
    it_end = iterator_advance(it_begin, 10);
    list_assign_range(plist_dest, it_begin, it_end);
    assert_true(list_size(plist_dest) == iterator_distance(it_begin, it_end));
    assert_true(list_size(plist_dest) == 10);
    for(it_iter = list_begin(plist_dest);
        !iterator_equal(it_iter, list_end(plist_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_assign_range__10_assign_range_1000(void** state)
{
    list_iterator_t it_iter;
    list_iterator_t it_begin;
    list_iterator_t it_end;
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);
    list_init_elem(plist_src, 1200, 100);
    list_init_elem(plist_dest, 10, 0);

    it_begin = iterator_advance(list_begin(plist_src), 111);
    it_end = iterator_advance(it_begin, 1000);
    list_assign_range(plist_dest, it_begin, it_end);
    assert_true(list_size(plist_dest) == iterator_distance(it_begin, it_end));
    assert_true(list_size(plist_dest) == 1000);
    for(it_iter = list_begin(plist_dest);
        !iterator_equal(it_iter, list_end(plist_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_assign_range__other_container_range(void** state)
{
    list_t* plist = create_list(int);
    deque_t* pdeq = create_deque(int);

    list_init_n(plist, 100);
    deque_init_n(pdeq, 3);

    assert_true(list_size(plist) == 100);
    list_assign_range(plist, deque_begin(pdeq), deque_end(pdeq));
    assert_true(list_size(plist) == 3);

    list_destroy(plist);
    deque_destroy(pdeq);
}

/*
 * test list_assign_array
 */
UT_CASE_DEFINATION(list_assign_array)
void test_list_assign_array__null_list_container(void** state)
{
    int an_array[10] = {0};

    expect_assert_failure(list_assign_array(NULL, an_array, 10));
}

void test_list_assign_array__non_inited(void** state)
{
    int an_array[10] = {0};
    list_t* plist_dest = create_list(int);

    expect_assert_failure(list_assign_array(plist_dest, an_array, 10));

    list_destroy(plist_dest);
}

void test_list_assign_array__invalid_array(void** state)
{
    list_t* plist_dest = create_list(int);
    list_init(plist_dest);

    expect_assert_failure(list_assign_array(plist_dest, NULL, 10));

    list_destroy(plist_dest);
}

void test_list_assign_array__0_assign_array_0(void** state)
{
    int an_array[10] = {0};
    list_t* plist_dest = create_list(int);
    list_init(plist_dest);

    list_assign_array(plist_dest, an_array, 0);
    assert_true(list_size(plist_dest) == 0);

    list_destroy(plist_dest);
}

void test_list_assign_array__0_assign_array_10(void** state)
{
    int an_array[10];
    int i = 0;
    list_iterator_t it_iter;
    list_t* plist_dest = create_list(int);
    list_init(plist_dest);

    for (i = 0; i < 10; ++i) {
        an_array[i] = i;
    }
    list_assign_array(plist_dest, an_array, 10);
    assert_true(list_size(plist_dest) == 10);
    for(it_iter = list_begin(plist_dest), i = 0;
        !iterator_equal(it_iter, list_end(plist_dest)) && i < 10;
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == an_array[i]);
    }

    list_destroy(plist_dest);
}

void test_list_assign_array__10_assign_array_0(void** state)
{
    int an_array[10] = {0};
    list_t* plist_dest = create_list(int);
    list_init_elem(plist_dest, 10, 700);

    list_assign_array(plist_dest, an_array, 0);
    assert_true(list_size(plist_dest) == 0);

    list_destroy(plist_dest);
}

void test_list_assign_array__10_assign_array_10_same_elem(void** state)
{
    int an_array[10] = {0};
    int i = 0;
    list_iterator_t it_iter;
    list_t* plist_dest = create_list(int);
    list_init_elem(plist_dest, 10, 100);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    list_assign_array(plist_dest, an_array, 10);
    assert_true(list_size(plist_dest) == 10);
    for(it_iter = list_begin(plist_dest);
        !iterator_equal(it_iter, list_end(plist_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    list_destroy(plist_dest);
}

void test_list_assign_array__10_assign_array_10_not_same_elem(void** state)
{
    int an_array[10] = {0};
    int i = 0;
    list_iterator_t it_iter;
    list_t* plist_dest = create_list(int);
    list_init_elem(plist_dest, 10, 0);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    list_assign_array(plist_dest, an_array, 10);
    assert_true(list_size(plist_dest) == 10);
    for(it_iter = list_begin(plist_dest);
        !iterator_equal(it_iter, list_end(plist_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    list_destroy(plist_dest);
}

void test_list_assign_array__10_assign_array_1000(void** state)
{
    int an_array[1000] = {0};
    int i = 0;
    list_iterator_t it_iter;
    list_t* plist_dest = create_list(int);
    list_init_elem(plist_dest, 10, 0);

    for (i = 0; i < 1000; ++i) {
        an_array[i] = 100;
    }
    list_assign_array(plist_dest, an_array, 1000);
    assert_true(list_size(plist_dest) == 1000);
    for(it_iter = list_begin(plist_dest);
        !iterator_equal(it_iter, list_end(plist_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    list_destroy(plist_dest);
}

void test_list_assign_array__cstr(void** state)
{
    const char* as_array[] = {
        "abc", "def", "ghi", "jkl", "mno"
    };
    list_t* plist = create_list(char*);
    list_iterator_t it_iter;
    int i = 0;

    list_init_n(plist, 100);

    assert_true(list_size(plist) == 100);
    list_assign_array(plist, as_array, 5);
    assert_true(list_size(plist) == 5);
    for (it_iter = list_begin(plist), i = 0;
         !iterator_equal(it_iter, list_end(plist)) && i < 5;
         it_iter = iterator_next(it_iter), ++i) {
        assert_true(strcmp((char*)iterator_get_pointer(it_iter), as_array[i]) == 0);
    }

    list_destroy(plist);
}

typedef struct _test_list_assign_array__user_define {
    int n_elem;
}_test_list_assign_array__user_define_t;
void test_list_assign_array__user_define(void** state)
{
    _test_list_assign_array__user_define_t* apt_array[10] = {NULL};
    list_t* plist = NULL;
    list_iterator_t it;
    int i = 0;

    type_register(_test_list_assign_array__user_define_t, NULL, NULL, NULL, NULL);
    plist = create_list(_test_list_assign_array__user_define_t);
    list_init(plist);

    for (i = 0; i < 10; ++i) {
        apt_array[i] = malloc(sizeof(_test_list_assign_array__user_define_t));
        apt_array[i]->n_elem = i;
    }
    list_assign_array(plist, apt_array, 10);
    assert_true(list_size(plist) == 10);
    for (it = list_begin(plist), i = 0;
         !iterator_equal(it, list_end(plist)) && i < 10;
         it = iterator_next(it), ++i) {
        assert_true(((_test_list_assign_array__user_define_t*)iterator_get_pointer(it))->n_elem ==
            apt_array[i]->n_elem);
    }

    list_destroy(plist);
    for (i = 0; i < 10; ++i) {
        free(apt_array[i]);
    }
}

void test_list_assign_array__cstl_builtin(void** state)
{
    deque_t* apdeq[10] = {NULL};
    int i = 0;
    list_t* plist = create_list(deque_t<int>);
    list_iterator_t it;

    for (i = 0; i < 10; ++i) {
        apdeq[i] = create_deque(int);
        deque_init_elem(apdeq[i], i, i);
    }
    list_init(plist);
    list_assign_array(plist, apdeq, 10);
    assert_true(list_size(plist) == 10);
    for (it = list_begin(plist), i = 0;
         !iterator_equal(it, list_end(plist)) && i < 10;
         it = iterator_next(it), ++i) {
        assert_true(deque_equal((deque_t*)iterator_get_pointer(it), apdeq[i]));
    }

    list_destroy(plist);
    for (i = 0; i < 10; ++i) {
        deque_destroy(apdeq[i]);
    }
}

/*
 * test list_swap
 */
UT_CASE_DEFINATION(list_swap)
void test_list_swap__null_first(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    expect_assert_failure(list_swap(NULL, plist));

    list_destroy(plist);
}

void test_list_swap__null_second(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    expect_assert_failure(list_swap(plist, NULL));

    list_destroy(plist);
}

void test_list_swap__non_inited_first(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_second);

    expect_assert_failure(list_swap(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_swap__non_inited_second(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_first);

    expect_assert_failure(list_swap(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_swap__not_same_type(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(double);

    list_init(plist_first);
    list_init(plist_second);

    expect_assert_failure(list_swap(plist_first, plist_second));

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_swap__list_equal(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);

    list_init(plist_first);
    list_init(plist_second);

    list_swap(plist_first, plist_second);

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_swap__0_swap_10(void** state)
{
    list_iterator_t it_iter;
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);
    size_t t_firstsize = 0;
    size_t t_secondsize = 0;

    list_init(plist_first);
    list_init_elem(plist_second, 10, 100);

    t_firstsize = list_size(plist_first);
    t_secondsize = list_size(plist_second);
    list_swap(plist_first, plist_second);

    assert_true(list_size(plist_first) == t_secondsize);
    assert_true(list_size(plist_second) == t_firstsize);
    for(it_iter = list_begin(plist_first);
        !iterator_equal(it_iter, list_end(plist_first));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }
    for(it_iter = list_begin(plist_second);
        !iterator_equal(it_iter, list_end(plist_second));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_swap__10_swap_0(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);
    size_t t_firstsize = 0;
    size_t t_secondsize = 0;
    list_iterator_t it_iter;

    list_init_n(plist_first, 10);
    list_init(plist_second);

    t_firstsize = list_size(plist_first);
    t_secondsize = list_size(plist_second);
    list_swap(plist_first, plist_second);

    assert_true(list_size(plist_first) == t_secondsize);
    assert_true(list_size(plist_second) == t_firstsize);
    for(it_iter = list_begin(plist_first);
        !iterator_equal(it_iter, list_end(plist_first));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }
    for(it_iter = list_begin(plist_second);
        !iterator_equal(it_iter, list_end(plist_second));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_swap__10_swap_10(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);
    size_t t_firstsize = 0;
    size_t t_secondsize = 0;
    list_iterator_t it_iter;

    list_init_n(plist_first, 10);
    list_init_elem(plist_second, 10, 100);

    t_firstsize = list_size(plist_first);
    t_secondsize = list_size(plist_second);
    list_swap(plist_first, plist_second);

    assert_true(list_size(plist_first) == t_secondsize);
    assert_true(list_size(plist_second) == t_firstsize);
    for(it_iter = list_begin(plist_first);
        !iterator_equal(it_iter, list_end(plist_first));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }
    for(it_iter = list_begin(plist_second);
        !iterator_equal(it_iter, list_end(plist_second));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    list_destroy(plist_first);
    list_destroy(plist_second);
}

void test_list_swap__10_swap_1000(void** state)
{
    list_t* plist_first = create_list(int);
    list_t* plist_second = create_list(int);
    size_t t_firstsize = 0;
    size_t t_secondsize = 0;
    list_iterator_t it_iter;

    list_init_n(plist_first, 10);
    list_init_elem(plist_second, 1000, 100);

    t_firstsize = list_size(plist_first);
    t_secondsize = list_size(plist_second);
    list_swap(plist_first, plist_second);

    assert_true(list_size(plist_first) == t_secondsize);
    assert_true(list_size(plist_second) == t_firstsize);
    for(it_iter = list_begin(plist_first);
        !iterator_equal(it_iter, list_end(plist_first));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }
    for(it_iter = list_begin(plist_second);
        !iterator_equal(it_iter, list_end(plist_second));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    list_destroy(plist_first);
    list_destroy(plist_second);
}

/*
 * test list_front
 */
UT_CASE_DEFINATION(list_front)
void test_list_front__null_list_container(void** state)
{
    expect_assert_failure(list_front(NULL));
}

void test_list_front__non_inited_list_container(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(list_front(plist));

    list_destroy(plist);
}

void test_list_front__empty(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    expect_assert_failure(list_front(plist));

    list_destroy(plist);
}

void test_list_front__successfully(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    list_push_back(plist, 2);
    list_push_back(plist, 345);
    list_push_back(plist, 24);
    assert_true(*(int*)list_front(plist) == 2);

    list_destroy(plist);
}

void test_list_front__successfully_cstr(void** state)
{
    list_t* plist = create_list(char*);
    list_init(plist);

    list_push_back(plist, "wodjad");
    list_push_back(plist, "345");
    list_push_back(plist, "mmmmmm");
    assert_true(strcmp((char*)list_front(plist), "wodjad") == 0);

    list_destroy(plist);
}

/*
 * test list_back
 */
UT_CASE_DEFINATION(list_back)
void test_list_back__null_list_container(void** state)
{
    expect_assert_failure(list_back(NULL));
}

void test_list_back__non_inited_list_container(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(list_back(plist));

    list_destroy(plist);
}

void test_list_back__empty(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    expect_assert_failure(list_back(plist));

    list_destroy(plist);
}

void test_list_back__successfully(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    list_push_back(plist, 2);
    list_push_back(plist, 345);
    list_push_back(plist, 24);
    assert_true(*(int*)list_back(plist) == 24);

    list_destroy(plist);
}

void test_list_back__successfully_cstr(void** state)
{
    list_t* plist = create_list(char*);
    list_init(plist);

    list_push_back(plist, "wodjad");
    list_push_back(plist, "345");
    list_push_back(plist, "mmmmmm");
    assert_true(strcmp((char*)list_back(plist), "mmmmmm") == 0);

    list_destroy(plist);
}

/*
 * test list_begin
 */
UT_CASE_DEFINATION(list_begin)
void test_list_begin__null_list_container(void** state)
{
    expect_assert_failure(list_begin(NULL));
}

void test_list_begin__non_inited_list_container(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(list_begin(plist));

    list_destroy(plist);
}

void test_list_begin__empty(void** state)
{
    list_iterator_t it_begin;
    list_t* plist = create_list(int);
    list_init(plist);

    it_begin = list_begin(plist);
    assert_true(_list_iterator_belong_to_list(plist, it_begin));
    assert_true(iterator_equal(it_begin, list_end(plist)));

    list_destroy(plist);
}

void test_list_begin__non_empty(void** state)
{
    list_iterator_t it_begin;
    list_t* plist = create_list(int);
    list_init(plist);
    list_push_back(plist, 123);
    list_push_back(plist, 209);
    list_push_back(plist, 3);

    it_begin = list_begin(plist);
    assert_true(_list_iterator_belong_to_list(plist, it_begin));
    assert_true((_listnode_t*)it_begin._t_pos._pby_corepos == plist->_pt_node->_pt_next);
    assert_true(*(int*)iterator_get_pointer(it_begin) == 123);

    list_destroy(plist);
}

/*
 * test list_end
 */
UT_CASE_DEFINATION(list_end)
void test_list_end__null_list_container(void** state)
{
    expect_assert_failure(list_end(NULL));
}

void test_list_end__non_inited_list_container(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(list_end(plist));

    list_destroy(plist);
}

void test_list_end__empty(void** state)
{
    list_iterator_t it_end;
    list_t* plist = create_list(int);
    list_init(plist);

    it_end = list_end(plist);
    assert_true(_list_iterator_belong_to_list(plist, it_end));
    assert_true(iterator_equal(it_end, list_begin(plist)));

    list_destroy(plist);
}

void test_list_end__non_empty(void** state)
{
    list_iterator_t it_end;
    list_t* plist = create_list(int);
    list_init(plist);
    list_push_back(plist, 123);
    list_push_back(plist, 209);
    list_push_back(plist, 3);

    it_end = list_end(plist);
    assert_true(_list_iterator_belong_to_list(plist, it_end));
    assert_true((_listnode_t*)it_end._t_pos._pby_corepos == plist->_pt_node);

    list_destroy(plist);
}

/*
 * test list_insert_range
 */
UT_CASE_DEFINATION(list_insert_range)
void test_list_insert_range__null_list_container(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_src = create_list(int);
    list_init(plist);
    list_init(plist_src);

    expect_assert_failure(list_insert_range(NULL, list_begin(plist), list_begin(plist_src), list_end(plist_src)));

    list_destroy(plist);
    list_destroy(plist_src);
}

void test_list_insert_range__non_inited(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_src = create_list(int);
    list_init(plist_src);

    expect_assert_failure(list_insert_range(plist, list_begin(plist), list_begin(plist_src), list_end(plist_src)));

    list_destroy(plist);
    list_destroy(plist_src);
}

void test_list_insert_range__invalid_position(void** state)
{
    list_iterator_t it_pos = _create_list_iterator();
    list_t* plist = create_list(int);
    list_t* plist_src = create_list(int);
    list_init(plist_src);
    list_init_n(plist, 10);
    it_pos = list_begin(plist);
    it_pos._t_pos._pby_corepos = NULL;

    expect_assert_failure(list_insert_range(plist, it_pos, list_begin(plist_src), list_end(plist_src)));

    list_destroy(plist);
    list_destroy(plist_src);
}

void test_list_insert_range__invalid_range(void** state)
{
    list_iterator_t it_pos = _create_list_iterator();
    list_iterator_t it_begin = _create_list_iterator();
    list_iterator_t it_end = _create_list_iterator();
    list_t* plist = create_list(int);
    list_t* plist_src = create_list(int);
    list_init_n(plist_src, 10);
    list_init_n(plist, 10);
    it_pos = list_begin(plist);
    it_begin = list_begin(plist_src);
    it_end = list_end(plist_src);

    expect_assert_failure(list_insert_range(plist, it_pos, it_end, it_begin));

    list_destroy(plist);
    list_destroy(plist_src);
}

void test_list_insert_range__invalid_range_not_same_type(void** state)
{
    list_iterator_t it_pos = _create_list_iterator();
    list_iterator_t it_begin = _create_list_iterator();
    list_iterator_t it_end = _create_list_iterator();
    list_t* plist = create_list(int);
    list_t* plist_src = create_list(double);
    list_init(plist_src);
    list_init_n(plist, 10);
    it_pos = list_begin(plist);
    it_begin = list_begin(plist_src);
    it_end = list_end(plist_src);

    expect_assert_failure(list_insert_range(plist, it_pos, it_begin, it_end));

    list_destroy(plist);
    list_destroy(plist_src);
}

void test_list_insert_range__invalid_range_belong_to_list(void** state)
{
    list_iterator_t it_pos = _create_list_iterator();
    list_iterator_t it_begin = _create_list_iterator();
    list_iterator_t it_end = _create_list_iterator();
    list_t* plist = create_list(int);
    list_t* plist_src = create_list(int);
    list_init(plist_src);
    list_init_n(plist, 10);
    it_pos = list_begin(plist);
    it_begin = list_begin(plist_src);
    it_end = list_end(plist_src);

    list_insert_range(plist, it_pos, it_pos, it_pos);

    list_destroy(plist);
    list_destroy(plist_src);
}

void test_list_insert_range__empty_insert_0(void** state)
{
    list_iterator_t it_pos;
    list_t* plist = create_list(int);
    list_t* plist_src = create_list(int);
    list_init(plist);
    list_init(plist_src);

    assert_true(list_size(plist) == 0);
    it_pos = list_begin(plist);
    list_insert_range(plist, it_pos, list_begin(plist_src), list_end(plist_src));
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
    list_destroy(plist_src);
}

void test_list_insert_range__empty_insert_10(void** state)
{
    list_iterator_t it_pos;
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_t* plist_src = create_list(int);
    list_init(plist);
    list_init_elem(plist_src, 10, 100);

    assert_true(list_size(plist) == 0);
    it_pos = list_begin(plist);
    list_insert_range(plist, it_pos, list_begin(plist_src), list_end(plist_src));
    assert_true(list_size(plist) == 10);
    for(it_iter = list_begin(plist);
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    list_destroy(plist);
    list_destroy(plist_src);
}

void test_list_insert_range__begin_insert_0(void** state)
{
    list_iterator_t it_pos;
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_t* plist_src = create_list(int);
    list_init_n(plist, 1000);
    list_init_elem(plist_src, 0, 100);

    assert_true(list_size(plist) == 1000);
    it_pos = list_begin(plist);
    list_insert_range(plist, it_pos, list_begin(plist_src), list_end(plist_src));
    assert_true(list_size(plist) == 1000);
    for(it_iter = list_begin(plist);
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    list_destroy(plist);
    list_destroy(plist_src);
}

void test_list_insert_range__begin_insert_10(void** state)
{
    list_iterator_t it_pos;
    list_iterator_t it_iter;
    size_t i = 0;
    list_t* plist = create_list(int);
    list_t* plist_src = create_list(int);
    list_init_elem(plist_src, 10, 100);
    list_init_n(plist, 1000);

    assert_true(list_size(plist) == 1000);
    it_pos = list_begin(plist);
    list_insert_range(plist, it_pos, list_begin(plist_src), list_end(plist_src));
    assert_true(list_size(plist) == 1010);
    for(it_iter = list_begin(plist), i = 0;
        !iterator_equal(it_iter, list_end(plist));
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

    list_destroy(plist);
    list_destroy(plist_src);
}

void test_list_insert_range__middle_insert_0(void** state)
{
    list_iterator_t it_pos;
    list_iterator_t it_iter;
    size_t i = 0;
    list_t* plist = create_list(int);
    list_t* plist_src = create_list(int);
    list_init_elem(plist_src, 0, 100);
    list_init_n(plist, 1000);

    assert_true(list_size(plist) == 1000);
    it_pos = iterator_advance(list_begin(plist), 300);
    list_insert_range(plist, it_pos, list_begin(plist_src), list_end(plist_src));
    assert_true(list_size(plist) == 1000);
    for(it_iter = list_begin(plist), i = 0;
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    list_destroy(plist);
    list_destroy(plist_src);
}

void test_list_insert_range__middle_insert_10(void** state)
{
    list_iterator_t it_pos;
    list_iterator_t it_iter;
    size_t i = 0;
    list_t* plist = create_list(int);
    list_t* plist_src = create_list(int);
    list_init_elem(plist_src, 10, 100);
    list_init_n(plist, 1000);

    assert_true(list_size(plist) == 1000);
    it_pos = iterator_advance(list_begin(plist), 300);
    list_insert_range(plist, it_pos, list_begin(plist_src), list_end(plist_src));
    assert_true(list_size(plist) == 1010);
    for(it_iter = list_begin(plist), i = 0;
        !iterator_equal(it_iter, list_end(plist));
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

    list_destroy(plist);
    list_destroy(plist_src);
}

void test_list_insert_range__end_insert_0(void** state)
{
    list_iterator_t it_pos;
    list_iterator_t it_iter;
    size_t i = 0;
    list_t* plist = create_list(int);
    list_t* plist_src = create_list(int);
    list_init_elem(plist_src, 0, 100);
    list_init_n(plist, 1000);

    assert_true(list_size(plist) == 1000);
    it_pos = list_end(plist);
    list_insert_range(plist, it_pos, list_begin(plist_src), list_end(plist_src));
    assert_true(list_size(plist) == 1000);
    for(it_iter = list_begin(plist), i = 0;
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    list_destroy(plist);
    list_destroy(plist_src);
}

void test_list_insert_range__end_insert_10(void** state)
{
    list_iterator_t it_pos;
    list_iterator_t it_iter;
    size_t i = 0;
    list_t* plist = create_list(int);
    list_t* plist_src = create_list(int);
    list_init_elem(plist_src, 10, 100);
    list_init_n(plist, 1000);

    assert_true(list_size(plist) == 1000);
    it_pos = list_end(plist);
    list_insert_range(plist, it_pos, list_begin(plist_src), list_end(plist_src));
    assert_true(list_size(plist) == 1010);
    for(it_iter = list_begin(plist), i = 0;
        !iterator_equal(it_iter, list_end(plist));
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

    list_destroy(plist);
    list_destroy(plist_src);
}

void test_list_insert_range__other_container_range(void** state)
{
    list_t* plist = create_list(int);
    vector_t* pvec = create_vector(int);
    iterator_t it_iter;
    int i = 0;

    list_init_elem(plist, 10, 9);
    vector_init_elem(pvec, 10, 100);
    assert_true(list_size(plist) == 10);
    list_insert_range(plist, list_begin(plist), vector_begin(pvec), vector_end(pvec));
    for(it_iter = list_begin(plist), i = 0; !iterator_equal(it_iter, list_end(plist)); it_iter = iterator_next(it_iter), ++i)
    {
        if(i < 10)
        {
            assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
        }
        else
        {
            assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
        }
    }

    list_destroy(plist);
    vector_destroy(pvec);
}

/*
 * test list_insert_array
 */
UT_CASE_DEFINATION(list_insert_array)
void test_list_insert_array__null_list_container(void** state)
{
    int an_array[10] = {0};
    list_t* plist = create_list(int);
    list_init(plist);

    expect_assert_failure(list_insert_array(NULL, list_begin(plist), an_array, 10));

    list_destroy(plist);
}

void test_list_insert_array__non_inited(void** state)
{
    int an_array[10] = {0};
    list_t* plist = create_list(int);

    expect_assert_failure(list_insert_array(plist, list_begin(plist), an_array, 10));

    list_destroy(plist);
}

void test_list_insert_array__invalid_position(void** state)
{
    int an_array[10] = {0};
    list_iterator_t it_pos = _create_list_iterator();
    list_t* plist = create_list(int);
    list_init_n(plist, 10);
    it_pos = list_begin(plist);
    it_pos._t_pos._pby_corepos = NULL;

    expect_assert_failure(list_insert_array(plist, it_pos, an_array, 10));

    list_destroy(plist);
}

void test_list_insert_array__invalid_array(void** state)
{
    list_iterator_t it_pos = _create_list_iterator();
    list_t* plist = create_list(int);
    list_init_n(plist, 10);
    it_pos = list_begin(plist);

    expect_assert_failure(list_insert_array(plist, it_pos, NULL, 10));

    list_destroy(plist);
}

void test_list_insert_array__empty_insert_0(void** state)
{
    int an_array[10] = {0};
    list_iterator_t it_pos;
    list_t* plist = create_list(int);
    list_init(plist);

    assert_true(list_size(plist) == 0);
    it_pos = list_begin(plist);
    list_insert_array(plist, it_pos, an_array, 0);
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

void test_list_insert_array__empty_insert_10(void** state)
{
    int an_array[10];
    int i = 0;
    list_iterator_t it_pos;
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init(plist);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    assert_true(list_size(plist) == 0);
    it_pos = list_begin(plist);
    list_insert_array(plist, it_pos, an_array, 10);
    assert_true(list_size(plist) == 10);
    for(it_iter = list_begin(plist);
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    list_destroy(plist);
}

void test_list_insert_array__begin_insert_0(void** state)
{
    int an_array[10] = {0};
    list_iterator_t it_pos;
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init_n(plist, 1000);

    assert_true(list_size(plist) == 1000);
    it_pos = list_begin(plist);
    list_insert_array(plist, it_pos, an_array, 0);
    assert_true(list_size(plist) == 1000);
    for(it_iter = list_begin(plist);
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    list_destroy(plist);
}

void test_list_insert_array__begin_insert_10(void** state)
{
    int an_array[10] = {0};
    list_iterator_t it_pos;
    list_iterator_t it_iter;
    size_t i = 0;
    list_t* plist = create_list(int);
    list_init_n(plist, 1000);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    assert_true(list_size(plist) == 1000);
    it_pos = list_begin(plist);
    list_insert_array(plist, it_pos, an_array, 10);
    assert_true(list_size(plist) == 1010);
    for(it_iter = list_begin(plist), i = 0;
        !iterator_equal(it_iter, list_end(plist));
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

    list_destroy(plist);
}

void test_list_insert_array__middle_insert_0(void** state)
{
    int an_array[10] = {0};
    list_iterator_t it_pos;
    list_iterator_t it_iter;
    size_t i = 0;
    list_t* plist = create_list(int);
    list_init_n(plist, 1000);

    assert_true(list_size(plist) == 1000);
    it_pos = iterator_advance(list_begin(plist), 300);
    list_insert_array(plist, it_pos, an_array, 0);
    assert_true(list_size(plist) == 1000);
    for(it_iter = list_begin(plist), i = 0;
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    list_destroy(plist);
}

void test_list_insert_array__middle_insert_10(void** state)
{
    int an_array[10] = {0};
    list_iterator_t it_pos;
    list_iterator_t it_iter;
    size_t i = 0;
    list_t* plist = create_list(int);
    list_init_n(plist, 1000);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    assert_true(list_size(plist) == 1000);
    it_pos = iterator_advance(list_begin(plist), 300);
    list_insert_array(plist, it_pos, an_array, 10);
    assert_true(list_size(plist) == 1010);
    for(it_iter = list_begin(plist), i = 0;
        !iterator_equal(it_iter, list_end(plist));
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

    list_destroy(plist);
}

void test_list_insert_array__end_insert_0(void** state)
{
    int an_array[10] = {0};
    list_iterator_t it_pos;
    list_iterator_t it_iter;
    size_t i = 0;
    list_t* plist = create_list(int);
    list_init_n(plist, 1000);

    assert_true(list_size(plist) == 1000);
    it_pos = list_end(plist);
    list_insert_array(plist, it_pos, an_array, 0);
    assert_true(list_size(plist) == 1000);
    for(it_iter = list_begin(plist), i = 0;
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    list_destroy(plist);
}

void test_list_insert_array__end_insert_10(void** state)
{
    int an_array[10] = {0};
    list_iterator_t it_pos;
    list_iterator_t it_iter;
    size_t i = 0;
    list_t* plist = create_list(int);
    list_init_n(plist, 1000);

    for (i = 0; i < 10; ++i) {
        an_array[i] = 100;
    }
    assert_true(list_size(plist) == 1000);
    it_pos = list_end(plist);
    list_insert_array(plist, it_pos, an_array, 10);
    assert_true(list_size(plist) == 1010);
    for(it_iter = list_begin(plist), i = 0;
        !iterator_equal(it_iter, list_end(plist));
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

    list_destroy(plist);
}

void test_list_insert_array__cstr(void** state)
{
    const char* as_array[] = {
        "linux", "windows", "mac", "unix", "solaris", "freebsd"
    };
    size_t i = 0;
    list_t* plist = create_list(char*);
    list_iterator_t it;
    list_init_elem(plist, 10, "xxxx");

    list_insert_array(plist, list_begin(plist), as_array, 6);
    assert_true(list_size(plist) == 16);
    for (it = list_begin(plist), i = 0;
         !iterator_equal(it, list_end(plist));
         it = iterator_next(it), ++i) {
        if (i < 6) {
            assert_true(strcmp((char*)iterator_get_pointer(it), as_array[i]) == 0);
        } else {
            assert_true(strcmp((char*)iterator_get_pointer(it), "xxxx") == 0);
        }
    }

    list_destroy(plist);
}

void test_list_insert_array__cstl(void** state)
{
    list_iterator_t it;
    list_t* plist = create_list(deque_t<int>);
    deque_t* apdeq_array[10] = {NULL};
    size_t i = 0;

    for (i = 0; i < 10; ++i) {
        apdeq_array[i] = create_deque(int);
        deque_init_elem(apdeq_array[i], i, i);
    }
    list_init_n(plist, 10);
    list_insert_array(plist, list_end(plist), apdeq_array, 10);
    assert_true(list_size(plist) == 20);
    for (it = list_begin(plist), i = 0;
         !iterator_equal(it, list_end(plist));
         it = iterator_next(it), ++i) {
        if (i < 10) {
            assert_true(deque_empty(iterator_get_pointer(it)));
        } else {
            assert_true(deque_equal(iterator_get_pointer(it), apdeq_array[i - 10]));
        }
    }
    list_destroy(plist);
    for (i = 0; i < 10; ++i) {
        deque_destroy(apdeq_array[i]);
    }
}

typedef struct _test_list_insert_array {
    int n_elem;
}_test_list_insert_array_t;
void test_list_insert_array__user_define(void** state)
{
    _test_list_insert_array_t* apt_array[10] = {NULL};
    size_t i = 0;
    list_t* plist = NULL;
    list_iterator_t it;

    type_register(_test_list_insert_array_t, NULL, NULL, NULL, NULL);
    plist = create_list(_test_list_insert_array_t);
    list_init(plist);
    for (i = 0; i < 10; ++i) {
        apt_array[i] = malloc(sizeof(_test_list_insert_array_t));
        apt_array[i]->n_elem = 100;
    }

    list_insert_array(plist, list_begin(plist), apt_array, 10);
    assert_true(list_size(plist) == 10);
    for (it = list_begin(plist), i = 0;
         !iterator_equal(it, list_end(plist));
         it = iterator_next(it), ++i) {
        assert_true(((_test_list_insert_array_t*)iterator_get_pointer(it))->n_elem == apt_array[i]->n_elem);
    }

    list_destroy(plist);
    for (i = 0; i < 10; ++i) {
        free(apt_array[i]);
    }
}

/*
 * test list_pop_back
 */
UT_CASE_DEFINATION(list_pop_back)
void test_list_pop_back__null_list_container(void** state)
{
    expect_assert_failure(list_pop_back(NULL));
}

void test_list_pop_back__non_inited_list_container(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(list_pop_back(plist));

    list_destroy(plist);
}

void test_list_pop_back__empty(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    expect_assert_failure(list_pop_back(plist));

    list_destroy(plist);
}

void test_list_pop_back__successfully(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    list_t* plist = create_list(int);
    list_init(plist);

    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    t_oldsize = list_size(plist);
    assert_true(*(int*)list_back(plist) == 9);
    list_pop_back(plist);
    assert_true(list_size(plist) == t_oldsize - 1);
    assert_true(*(int*)list_back(plist) == 8);

    list_destroy(plist);
}

/*
 * test list_pop_front
 */
UT_CASE_DEFINATION(list_pop_front)
void test_list_pop_front__null_list_container(void** state)
{
    expect_assert_failure(list_pop_front(NULL));
}

void test_list_pop_front__non_inited_list_container(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(list_pop_front(plist));

    list_destroy(plist);
}

void test_list_pop_front__empty(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    expect_assert_failure(list_pop_front(plist));

    list_destroy(plist);
}

void test_list_pop_front__successfully(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    list_t* plist = create_list(int);
    list_init(plist);

    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    t_oldsize = list_size(plist);
    assert_true(*(int*)list_front(plist) == 0);
    list_pop_front(plist);
    assert_true(list_size(plist) == t_oldsize - 1);
    assert_true(*(int*)list_front(plist) == 1);

    list_destroy(plist);
}

/*
 * test list_erase
 */
UT_CASE_DEFINATION(list_erase)
void test_list_erase__null_list_container(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    list_iterator_t it_pos = _create_list_iterator();
    list_t* plist = create_list(int);
    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    t_oldsize = list_size(plist);

    it_pos = list_begin(plist);
    expect_assert_failure(list_erase(NULL, it_pos));

    list_destroy(plist);
}

void test_list_erase__non_inited_list_container(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    _listnode_t* pt_node = NULL;
    list_iterator_t it_pos = _create_list_iterator();
    list_t* plist = create_list(int);
    list_init(plist);
    t_oldsize = list_size(plist);

    it_pos = list_begin(plist);
    pt_node = plist->_pt_node;
    plist->_pt_node = NULL;
    expect_assert_failure(list_erase(plist, it_pos));

    plist->_pt_node = pt_node;
    list_destroy(plist);
}

void test_list_erase__invalid_pos_end(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    list_iterator_t it_pos = _create_list_iterator();
    list_t* plist = create_list(int);
    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    t_oldsize = list_size(plist);

    it_pos = list_end(plist);
    expect_assert_failure(list_erase(plist, it_pos));

    list_destroy(plist);
}

void test_list_erase__invalid_pos(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    list_iterator_t it_pos = _create_list_iterator();
    list_t* plist = create_list(int);
    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    t_oldsize = list_size(plist);

    it_pos = list_end(plist);
    it_pos._t_pos._pby_corepos = NULL;
    expect_assert_failure(list_erase(plist, it_pos));

    list_destroy(plist);
}

void test_list_erase__successfully_begin(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    list_iterator_t it_pos = _create_list_iterator();
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    t_oldsize = list_size(plist);

    it_pos = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_pos) == 0);
    it_iter = list_erase(plist, it_pos);
    assert_true(list_size(plist) == t_oldsize - 1);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    list_destroy(plist);
}

void test_list_erase__successfully_middle(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    list_iterator_t it_pos = _create_list_iterator();
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    t_oldsize = list_size(plist);

    it_pos = iterator_next(list_begin(plist));
    assert_true(*(int*)iterator_get_pointer(it_pos) == 1);
    it_iter = list_erase(plist, it_pos);
    assert_true(list_size(plist) == t_oldsize - 1);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);

    list_destroy(plist);
}

void test_list_erase__successfully_back(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    list_iterator_t it_pos = _create_list_iterator();
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    t_oldsize = list_size(plist);

    it_pos = iterator_prev(list_end(plist));
    assert_true(*(int*)iterator_get_pointer(it_pos) == 9);
    it_iter = list_erase(plist, it_pos);
    assert_true(list_size(plist) == t_oldsize - 1);
    assert_true(*(int*)list_back(plist) == 8);
    assert_true(iterator_equal(it_iter, list_end(plist)));

    list_destroy(plist);
}

/*
 * test list_erase_range
 */
UT_CASE_DEFINATION(list_erase_range)
void test_list_erase_range__null_list_container(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    list_iterator_t it_begin = _create_list_iterator();
    list_iterator_t it_end = _create_list_iterator();
    list_t* plist = create_list(int);
    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    t_oldsize = list_size(plist);

    it_begin = list_begin(plist);
    it_end = list_end(plist);
    expect_assert_failure(list_erase_range(NULL, it_begin, it_end));

    list_destroy(plist);
}

void test_list_erase_range__non_inited_list_container(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    _listnode_t* pt_node = NULL;
    list_iterator_t it_begin = _create_list_iterator();
    list_iterator_t it_end = _create_list_iterator();
    list_t* plist = create_list(int);
    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    t_oldsize = list_size(plist);

    it_begin = list_begin(plist);
    it_end = list_end(plist);
    pt_node = plist->_pt_node;
    plist->_pt_node = NULL;
    expect_assert_failure(list_erase_range(plist, it_begin, it_end));

    plist->_pt_node = pt_node;
    list_destroy(plist);
}

void test_list_erase_range__invalid_range_not_belong_to_list(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    list_iterator_t it_begin = _create_list_iterator();
    list_iterator_t it_end = _create_list_iterator();
    list_t* plist = create_list(int);
    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    t_oldsize = list_size(plist);

    expect_assert_failure(list_erase_range(plist, it_begin, it_end));

    list_destroy(plist);
}

void test_list_erase_range__invalid_range(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    list_iterator_t it_begin = _create_list_iterator();
    list_iterator_t it_end = _create_list_iterator();
    list_t* plist = create_list(int);
    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    t_oldsize = list_size(plist);

    it_begin = list_begin(plist);
    it_end = list_end(plist);
    expect_assert_failure(list_erase_range(plist, it_end, it_begin));

    list_destroy(plist);
}

void test_list_erase_range__successfully_empty(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_erasesize = 0;
    list_iterator_t it_begin = _create_list_iterator();
    list_iterator_t it_end = _create_list_iterator();
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    t_oldsize = list_size(plist);

    it_begin = list_begin(plist);
    it_end = list_end(plist);
    it_iter = list_erase_range(plist, it_begin, it_begin);
    assert_true(list_size(plist) == t_oldsize - t_erasesize);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    list_destroy(plist);
}

void test_list_erase_range__successfully_begin(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_erasesize = 0;
    list_iterator_t it_begin = _create_list_iterator();
    list_iterator_t it_end = _create_list_iterator();
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    t_oldsize = list_size(plist);

    it_begin = list_begin(plist);
    it_end = iterator_advance(it_begin, 3);
    t_erasesize = iterator_distance(it_begin, it_end);
    it_iter = list_erase_range(plist, it_begin, it_end);
    assert_true(list_size(plist) == t_oldsize - t_erasesize);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);

    list_destroy(plist);
}

void test_list_erase_range__successfully_middle(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_erasesize = 0;
    list_iterator_t it_begin = _create_list_iterator();
    list_iterator_t it_end = _create_list_iterator();
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    t_oldsize = list_size(plist);

    it_begin = iterator_advance(list_begin(plist), 3);
    it_end = iterator_advance(it_begin, 3);
    t_erasesize = iterator_distance(it_begin, it_end);
    it_iter = list_erase_range(plist, it_begin, it_end);
    assert_true(list_size(plist) == t_oldsize - t_erasesize);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 6);

    list_destroy(plist);
}

void test_list_erase_range__successfully_end(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_erasesize = 0;
    list_iterator_t it_begin = _create_list_iterator();
    list_iterator_t it_end = _create_list_iterator();
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    t_oldsize = list_size(plist);

    it_begin = iterator_advance(list_begin(plist), 6);
    it_end = list_end(plist);
    t_erasesize = iterator_distance(it_begin, it_end);
    it_iter = list_erase_range(plist, it_begin, it_end);
    assert_true(list_size(plist) == t_oldsize - t_erasesize);
    assert_true(*(int*)list_back(plist) == 5);
    assert_true(iterator_equal(it_iter, list_end(plist)));

    list_destroy(plist);
}

void test_list_erase_range__successfully_all(void** state)
{
    size_t i = 0;
    size_t t_oldsize = 0;
    size_t t_erasesize = 0;
    list_iterator_t it_begin = _create_list_iterator();
    list_iterator_t it_end = _create_list_iterator();
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    t_oldsize = list_size(plist);

    it_begin = list_begin(plist);
    it_end = list_end(plist);
    t_erasesize = iterator_distance(it_begin, it_end);
    it_iter = list_erase_range(plist, it_begin, it_end);
    assert_true(list_size(plist) == t_oldsize - t_erasesize);
    assert_true(list_empty(plist));
    assert_true(iterator_equal(it_iter, list_end(plist)));

    list_destroy(plist);
}

/*
 * test list_remove_if
 */
UT_CASE_DEFINATION(list_remove_if)

static void _test_list_remove_if_ufun_op(const void* cpv_input, void* pv_output)
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

void test_list_remove_if__null_list_container(void** state)
{
    expect_assert_failure(list_remove_if(NULL, NULL));
}

void test_list_remove_if__non_inited_list_container(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(list_remove_if(plist, NULL));

    list_destroy(plist);
}

void test_list_remove_if__empty(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    list_remove_if(plist, _test_list_remove_if_ufun_op);
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

void test_list_remove_if__non_empty_no_removed(void** state)
{
    list_t* plist = create_list(int);
    list_init_n(plist, 10);

    list_remove_if(plist, _test_list_remove_if_ufun_op);
    assert_true(list_size(plist) == 10);

    list_destroy(plist);
}

void test_list_remove_if__non_empty_remove(void** state)
{
    list_iterator_t it_iter;
    size_t t_oldsize = 0;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 0);
    list_push_back(plist, 3);
    list_push_back(plist, 4);
    list_push_back(plist, 4);
    list_push_back(plist, 1);

    t_oldsize = list_size(plist);
    list_remove_if(plist, _test_list_remove_if_ufun_op);
    assert_true(list_size(plist) == t_oldsize - 1);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    list_destroy(plist);
}

void test_list_remove_if__non_empty_remove_more(void** state)
{
    list_iterator_t it_iter;
    size_t t_oldsize = 0;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 0);
    list_push_back(plist, 2);
    list_push_back(plist, 3);
    list_push_back(plist, 3);
    list_push_back(plist, 1);

    t_oldsize = list_size(plist);
    list_remove_if(plist, _test_list_remove_if_ufun_op);
    assert_true(list_size(plist) == t_oldsize - 2);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    list_destroy(plist);
}

void test_list_remove_if__non_empty_remove_all(void** state)
{
    size_t t_oldsize = 0;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 3);

    t_oldsize = list_size(plist);
    list_remove_if(plist, _test_list_remove_if_ufun_op);
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

void test_list_remove_if__empty_default_ufun_op(void** state)
{
    size_t t_oldsize = 0;
    list_t* plist = create_list(int);

    list_init(plist);

    t_oldsize = list_size(plist);
    list_remove_if(plist, NULL);
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

void test_list_remove_if__non_empty_default_ufun_op(void** state)
{
    list_iterator_t it_iter;
    size_t t_oldsize = 0;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 0);
    list_push_back(plist, 2);
    list_push_back(plist, 3);
    list_push_back(plist, 3);
    list_push_back(plist, 1);

    t_oldsize = list_size(plist);
    list_remove_if(plist, NULL);
    assert_true(list_size(plist) == t_oldsize);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    list_destroy(plist);
}

static void _test_list_remove_if_cstr_ufun_op(const void* cpv_input, void* pv_output)
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
void test_list_remove_if__cstr_empty(void** state)
{
    list_t* plist = create_list(char*);
    list_init(plist);

    list_remove_if(plist, _test_list_remove_if_cstr_ufun_op);
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

void test_list_remove_if__cstr_non_empty_no_removed(void** state)
{
    list_t* plist = create_list(char*);
    list_init_n(plist, 10);

    list_remove_if(plist, _test_list_remove_if_cstr_ufun_op);
    assert_true(list_size(plist) == 10);

    list_destroy(plist);
}

void test_list_remove_if__cstr_non_empty_remove(void** state)
{
    list_iterator_t it_iter;
    size_t t_oldsize = 0;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_back(plist, "abc");
    list_push_back(plist, "AAAA");
    list_push_back(plist, "def");
    list_push_back(plist, "hij");
    list_push_back(plist, "hij");

    t_oldsize = list_size(plist);
    list_remove_if(plist, _test_list_remove_if_cstr_ufun_op);
    assert_true(list_size(plist) == t_oldsize - 1);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "abc") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "def") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "hij") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "hij") == 0);

    list_destroy(plist);
}

void test_list_remove_if__cstr_non_empty_remove_more(void** state)
{
    list_iterator_t it_iter;
    size_t t_oldsize = 0;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_back(plist, "abc");
    list_push_back(plist, "AAAA");
    list_push_back(plist, "AAAA");
    list_push_back(plist, "hij");
    list_push_back(plist, "hij");

    t_oldsize = list_size(plist);
    list_remove_if(plist, _test_list_remove_if_cstr_ufun_op);
    assert_true(list_size(plist) == t_oldsize - 2);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "abc") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "hij") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "hij") == 0);

    list_destroy(plist);
}

void test_list_remove_if__cstr_non_empty_remove_all(void** state)
{
    size_t t_oldsize = 0;
    list_t* plist = create_list(char*);

    list_init_elem(plist, 10, "AAAA");

    t_oldsize = list_size(plist);
    list_remove_if(plist, _test_list_remove_if_cstr_ufun_op);
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

/*
 * test list_resize
 */
UT_CASE_DEFINATION(list_resize)
void test_list_resize__null_list_container(void** state)
{
    expect_assert_failure(list_resize(NULL, 10));
}

void test_list_resize__non_inited(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(list_resize(plist, 10));

    list_destroy(plist);
}

void test_list_resize__successfully_0_resize_0(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    assert_true(list_size(plist) == 0);
    list_resize(plist, 0);
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

void test_list_resize__successfully_0_resize_10(void** state)
{
    size_t i = 0;
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init(plist);

    assert_true(list_size(plist) == 0);
    list_resize(plist, 10);
    assert_true(list_size(plist) == 10);
    for(it_iter = list_begin(plist), i = 0;
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    list_destroy(plist);
}

void test_list_resize__successfully_10_resize_0(void** state)
{
    list_t* plist = create_list(int);
    list_init_n(plist, 10);

    assert_true(list_size(plist) == 10);
    list_resize(plist, 0);
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

void test_list_resize__successfully_10_resize_10(void** state)
{
    size_t i = 0;
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init_n(plist, 10);

    assert_true(list_size(plist) == 10);
    list_resize(plist, 10);
    assert_true(list_size(plist) == 10);
    for(it_iter = list_begin(plist), i = 0;
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    list_destroy(plist);
}

void test_list_resize__successfully_10_resize_1000(void** state)
{
    size_t i = 0;
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init_elem(plist, 10, 100);

    assert_true(list_size(plist) == 10);
    list_resize(plist, 1000);
    assert_true(list_size(plist) == 1000);
    for(it_iter = list_begin(plist), i = 0;
        !iterator_equal(it_iter, list_end(plist));
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

    list_destroy(plist);
}

/*
 * test list_clear
 */
UT_CASE_DEFINATION(list_clear)
void test_list_clear__null_list_container(void** state)
{
    expect_assert_failure(list_clear(NULL));
}

void test_list_clear__non_inited_list_container(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(list_clear(plist));

    list_destroy(plist);
}

void test_list_clear__empty_list_container(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);

    list_clear(plist);
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

void test_list_clear__non_empty_list_container(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 198);

    list_clear(plist);
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

/*
 * test list_unique
 */
UT_CASE_DEFINATION(list_unique)
void test_list_unique__null_list_container(void** state)
{
    expect_assert_failure(list_unique(NULL));
}

void test_list_unique__non_inited_list_container(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(list_unique(plist));

    list_destroy(plist);
}

void test_list_unique__empty(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    list_unique(plist);
    assert_true(list_empty(plist));

    list_destroy(plist);
}

void test_list_unique__non_empty_no_duplicate(void** state)
{
    size_t i = 0;
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    list_unique(plist);
    assert_true(list_size(plist) == 10);
    for(it_iter = list_begin(plist), i = 0;
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == i);
    }

    list_destroy(plist);
}

void test_list_unique__non_empty_adjacent_duplicate(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 3);
    list_push_back(plist, 5);
    list_push_back(plist, 9);
    list_push_back(plist, 9);
    list_push_back(plist, 0);
    list_push_back(plist, 2);
    list_unique(plist);
    assert_true(list_size(plist) == 5);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 9);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);

    list_destroy(plist);
}

void test_list_unique__non_empty_not_adjacent_duplicate(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 3);
    list_push_back(plist, 5);
    list_push_back(plist, 9);
    list_push_back(plist, 0);
    list_push_back(plist, 9);
    list_push_back(plist, 2);
    list_unique(plist);
    assert_true(list_size(plist) == 6);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_unique__non_empty_all_duplicate(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    list_unique(plist);
    assert_true(list_size(plist) == 1);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 100);

    list_destroy(plist);
}

void test_list_unique__cstr_non_empty_no_duplicate(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_back(plist, "a");
    list_push_back(plist, "b");
    list_push_back(plist, "c");
    list_push_back(plist, "d");
    list_push_back(plist, "e");
    list_push_back(plist, "f");
    list_unique(plist);
    assert_true(list_size(plist) == 6);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_unique__cstr_non_empty_adjacent_duplicate(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_back(plist, "a");
    list_push_back(plist, "b");
    list_push_back(plist, "b");
    list_push_back(plist, "d");
    list_push_back(plist, "e");
    list_push_back(plist, "f");
    list_unique(plist);
    assert_true(list_size(plist) == 5);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "a") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "b") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "d") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "e") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "f") == 0);

    list_destroy(plist);
}

void test_list_unique__cstr_non_empty_not_adjacent_duplicate(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_back(plist, "a");
    list_push_back(plist, "b");
    list_push_back(plist, "d");
    list_push_back(plist, "b");
    list_push_back(plist, "e");
    list_push_back(plist, "f");
    list_unique(plist);
    assert_true(list_size(plist) == 6);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_unique__cstr_non_empty_all_duplicate(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init_elem(plist, 10, "a");
    list_unique(plist);
    assert_true(list_size(plist) == 1);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "a") == 0);

    list_destroy(plist);
}

/*
 * test list_unique_if
 */
UT_CASE_DEFINATION(list_unique_if)
void test_list_unique_if__null_list_container(void** state)
{
    expect_assert_failure(list_unique_if(NULL, NULL));
}

void test_list_unique_if__non_inited_list_container(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(list_unique_if(plist, NULL));

    list_destroy(plist);
}

void test_list_unique_if__empty(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    list_unique_if(plist, fun_equal_int);
    assert_true(list_empty(plist));

    list_destroy(plist);
}

void test_list_unique_if__non_empty_non_duplicate(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 3);
    list_push_back(plist, 4);
    list_push_back(plist, 5);
    list_push_back(plist, 0);
    list_push_back(plist, 1);
    list_unique_if(plist, fun_equal_int);
    assert_true(list_size(plist) == 5);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    list_destroy(plist);
}

void test_list_unique_if__non_empty_duplicate(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 3);
    list_push_back(plist, 4);
    list_push_back(plist, 5);
    list_push_back(plist, 5);
    list_push_back(plist, 1);
    list_unique_if(plist, fun_equal_int);
    assert_true(list_size(plist) == 4);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    list_destroy(plist);
}

void test_list_unique_if__non_empty_more_duplicate(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 3);
    list_push_back(plist, 4);
    list_push_back(plist, 5);
    list_push_back(plist, 5);
    list_push_back(plist, 5);
    list_unique_if(plist, fun_equal_int);
    assert_true(list_size(plist) == 3);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);

    list_destroy(plist);
}

void test_list_unique_if__non_empty_duplicate_not_adjacent(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 3);
    list_push_back(plist, 4);
    list_push_back(plist, 5);
    list_push_back(plist, 0);
    list_push_back(plist, 5);
    list_unique_if(plist, fun_equal_int);
    assert_true(list_size(plist) == 5);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 3);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);

    list_destroy(plist);
}

void test_list_unique_if__non_empty_duplicate_all(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_elem(plist, 10, 100);
    list_unique_if(plist, fun_equal_int);
    assert_true(list_size(plist) == 1);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 100);

    list_destroy(plist);
}

void test_list_unique_if__cstr_non_empty_no_duplicate(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_back(plist, "a");
    list_push_back(plist, "b");
    list_push_back(plist, "c");
    list_push_back(plist, "d");
    list_push_back(plist, "e");
    list_push_back(plist, "f");
    list_unique_if(plist, fun_equal_cstr);
    assert_true(list_size(plist) == 6);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_unique_if__cstr_non_empty_adjacent_duplicate(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_back(plist, "a");
    list_push_back(plist, "b");
    list_push_back(plist, "b");
    list_push_back(plist, "d");
    list_push_back(plist, "e");
    list_push_back(plist, "f");
    list_unique_if(plist, fun_equal_cstr);
    assert_true(list_size(plist) == 5);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "a") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "b") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "d") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "e") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "f") == 0);

    list_destroy(plist);
}

void test_list_unique_if__cstr_non_empty_not_adjacent_duplicate(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_back(plist, "a");
    list_push_back(plist, "b");
    list_push_back(plist, "d");
    list_push_back(plist, "b");
    list_push_back(plist, "e");
    list_push_back(plist, "f");
    list_unique_if(plist, fun_equal_cstr);
    assert_true(list_size(plist) == 6);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_unique_if__cstr_non_empty_all_duplicate(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init_elem(plist, 10, "a");
    list_unique_if(plist, fun_equal_cstr);
    assert_true(list_size(plist) == 1);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "a") == 0);

    list_destroy(plist);
}

void test_list_unique_if__default_predicate(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_back(plist, "a");
    list_push_back(plist, "b");
    list_push_back(plist, "b");
    list_push_back(plist, "b");
    list_push_back(plist, "e");
    list_push_back(plist, "f");
    list_unique_if(plist, NULL);
    assert_true(list_size(plist) == 6);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

/*
 * test list_splice
 */
UT_CASE_DEFINATION(list_splice)
void test_list_splice__null_target_list_container(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    expect_assert_failure(list_splice(NULL, list_begin(plist), plist));

    list_destroy(plist);
}

void test_list_splice__null_source_list_container(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    expect_assert_failure(list_splice(plist, list_begin(plist), NULL));

    list_destroy(plist);
}

void test_list_splice__non_inited_target_list_container(void** state)
{
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_src);
    expect_assert_failure(list_splice(plist_list, list_begin(plist_src), plist_src));

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice__non_inited_source_list_container(void** state)
{
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_list);
    expect_assert_failure(list_splice(plist_list, list_begin(plist_list), plist_src));

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice__not_same_type(void** state)
{
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(double);

    list_init(plist_list);
    list_init(plist_src);
    expect_assert_failure(list_splice(plist_list, list_begin(plist_list), plist_src));

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice__invalid_target_position(void** state)
{
    list_iterator_t it_iter;
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_list);
    list_init(plist_src);
    expect_assert_failure(list_splice(plist_list, it_iter, plist_src));

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice__same_list(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    list_splice(plist, list_begin(plist), plist);
    assert_true(list_size(plist) == 10);

    list_destroy(plist);
}

void test_list_splice__target_empty_source_empty(void** state)
{
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_list);
    list_init(plist_src);
    list_splice(plist_list, list_begin(plist_list), plist_src);
    assert_true(list_empty(plist_list));
    assert_true(list_empty(plist_src));

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice__target_empty_source_non_empty(void** state)
{
    list_iterator_t it_iter;
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_list);
    list_init_n(plist_src, 10);
    list_splice(plist_list, list_begin(plist_list), plist_src);
    assert_true(list_size(plist_list) == 10);
    assert_true(list_empty(plist_src));
    for(it_iter  = list_begin(plist_list);
        !iterator_equal(it_iter, list_end(plist_list));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice__target_begin_source_empty(void** state)
{
    list_iterator_t it_iter;
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init_n(plist_list, 10);
    list_init(plist_src);
    list_splice(plist_list, list_begin(plist_list), plist_src);
    assert_true(list_size(plist_list) == 10);
    assert_true(list_empty(plist_src));
    for(it_iter  = list_begin(plist_list);
        !iterator_equal(it_iter, list_end(plist_list));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice__target_begin_source_non_empty(void** state)
{
    list_iterator_t it_iter;
    size_t i = 0;
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init_n(plist_list, 10);
    list_init_elem(plist_src, 10, 100);
    list_splice(plist_list, list_begin(plist_list), plist_src);
    assert_true(list_size(plist_list) == 20);
    assert_true(list_empty(plist_src));
    for(it_iter  = list_begin(plist_list), i = 0;
        !iterator_equal(it_iter, list_end(plist_list));
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

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice__target_middle_source_non_empty(void** state)
{
    list_iterator_t it_iter;
    size_t i = 0;
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init_n(plist_list, 10);
    list_init_elem(plist_src, 10, 100);
    it_iter = iterator_advance(list_begin(plist_list), 3);
    list_splice(plist_list, it_iter, plist_src);
    assert_true(list_size(plist_list) == 20);
    assert_true(list_empty(plist_src));
    for(it_iter  = list_begin(plist_list), i = 0;
        !iterator_equal(it_iter, list_end(plist_list));
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

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice__target_end_source_non_empty(void** state)
{
    list_iterator_t it_iter;
    size_t i = 0;
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init_n(plist_list, 10);
    list_init_elem(plist_src, 10, 100);
    list_splice(plist_list, list_end(plist_list), plist_src);
    assert_true(list_size(plist_list) == 20);
    assert_true(list_empty(plist_src));
    for(it_iter  = list_begin(plist_list), i = 0;
        !iterator_equal(it_iter, list_end(plist_list));
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

    list_destroy(plist_list);
    list_destroy(plist_src);
}

/*
 * test list_splice_pos
 */
UT_CASE_DEFINATION(list_splice_pos)
void test_list_splice_pos__null_target_list_container(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(list_splice_pos(NULL, list_begin(plist), plist, list_begin(plist)));

    list_destroy(plist);
}

void test_list_splice_pos__null_source_list_container(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    expect_assert_failure(list_splice_pos(plist, list_begin(plist), NULL, list_begin(plist)));

    list_destroy(plist);
}

void test_list_splice_pos__non_inited_target_list_container(void** state)
{
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init_n(plist_src, 10);
    expect_assert_failure(list_splice_pos(plist_list, list_begin(plist_list), plist_src, list_begin(plist_src)));

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice_pos__non_inited_source_list_container(void** state)
{
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_list);
    expect_assert_failure(list_splice_pos(plist_list, list_begin(plist_list), plist_src, list_begin(plist_list)));

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice_pos__not_same(void** state)
{
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(double);

    list_init(plist_list);
    list_init_n(plist_src, 10);
    expect_assert_failure(list_splice_pos(plist_list, list_begin(plist_list), plist_src, list_begin(plist_src)));

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice_pos__invalid_tearget_position(void** state)
{
    list_iterator_t it_iter;
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_list);
    list_init_n(plist_src, 10);
    expect_assert_failure(list_splice_pos(plist_list, it_iter, plist_src, list_begin(plist_src)));

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice_pos__invalid_source_position(void** state)
{
    list_iterator_t it_iter;
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_list);
    list_init_n(plist_src, 10);
    expect_assert_failure(list_splice_pos(plist_list, list_begin(plist_list), plist_src, it_iter));

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice_pos__invalid_source_position_end(void** state)
{
    list_iterator_t it_iter;
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_list);
    list_init_n(plist_src, 10);
    it_iter = list_end(plist_src);
    expect_assert_failure(list_splice_pos(plist_list, list_begin(plist_list), plist_src, it_iter));

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice_pos__same_list_container_same_position(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 2);
    list_push_back(plist, 5);
    list_push_back(plist, 0);
    list_push_back(plist, 4);
    list_push_back(plist, 7);
    list_splice_pos(plist, list_begin(plist), plist, list_begin(plist));
    assert_true(list_size(plist) == 5);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);

    list_destroy(plist);
}

void test_list_splice_pos__same_list_container_next_position(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 2);
    list_push_back(plist, 5);
    list_push_back(plist, 0);
    list_push_back(plist, 4);
    list_push_back(plist, 7);
    list_splice_pos(plist, iterator_next(list_begin(plist)), plist, list_begin(plist));
    assert_true(list_size(plist) == 5);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);

    list_destroy(plist);
}

void test_list_splice_pos__same_list_container_not_same_not_next_position(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 2);
    list_push_back(plist, 5);
    list_push_back(plist, 0);
    list_push_back(plist, 4);
    list_push_back(plist, 7);
    list_splice_pos(plist, list_end(plist), plist, list_begin(plist));
    assert_true(list_size(plist) == 5);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);

    list_destroy(plist);
}

void test_list_splice_pos__target_empty(void** state)
{
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_list);
    list_init_elem(plist_src, 10, 100);
    list_splice_pos(plist_list, list_begin(plist_list), plist_src, list_begin(plist_src));
    assert_true(list_size(plist_list) == 1);
    assert_true(list_size(plist_src) == 9);
    assert_true(*(int*)iterator_get_pointer(list_begin(plist_list)) == 100);

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice_pos__target_begin_source_begin(void** state)
{
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init_n(plist_list, 10);
    list_init_elem(plist_src, 10, 100);
    list_splice_pos(plist_list, list_begin(plist_list), plist_src, list_begin(plist_src));
    assert_true(list_size(plist_list) == 11);
    assert_true(list_size(plist_src) == 9);
    assert_true(*(int*)iterator_get_pointer(list_begin(plist_list)) == 100);

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice_pos__target_middle_source_middle(void** state)
{
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init_n(plist_list, 10);
    list_init_elem(plist_src, 10, 100);
    list_splice_pos(plist_list, iterator_next(list_begin(plist_list)), plist_src, iterator_next(list_begin(plist_src)));
    assert_true(list_size(plist_list) == 11);
    assert_true(list_size(plist_src) == 9);
    assert_true(*(int*)iterator_get_pointer(iterator_next(list_begin(plist_list))) == 100);

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice_pos__target_end_source_begin(void** state)
{
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init_n(plist_list, 10);
    list_init_elem(plist_src, 10, 100);
    list_splice_pos(plist_list, list_end(plist_list), plist_src, list_begin(plist_src));
    assert_true(list_size(plist_list) == 11);
    assert_true(list_size(plist_src) == 9);
    assert_true(*(int*)iterator_get_pointer(iterator_prev(list_end(plist_list))) == 100);

    list_destroy(plist_list);
    list_destroy(plist_src);
}

/*
 * test list_splice_range
 */
UT_CASE_DEFINATION(list_splice_range)
void test_list_splice_range__null_target_list_container(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(list_splice_range(NULL, list_begin(plist), plist, list_begin(plist), list_end(plist)));

    list_destroy(plist);
}

void test_list_splice_range__null_source_list_container(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    expect_assert_failure(list_splice_range(plist, list_begin(plist), NULL, list_begin(plist), list_end(plist)));

    list_destroy(plist);
}

void test_list_splice_range__non_inited_target_list_container(void** state)
{
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init_n(plist_src, 10);
    expect_assert_failure(list_splice_range(
        plist_list, list_begin(plist_list), plist_src, list_begin(plist_src), list_end(plist_src)));

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice_range__non_inited_source_list_container(void** state)
{
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_list);
    expect_assert_failure(list_splice_range(
        plist_list, list_begin(plist_list), plist_src, list_begin(plist_list), list_end(plist_list)));

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice_range__not_same(void** state)
{
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(double);

    list_init(plist_list);
    list_init_n(plist_src, 10);
    expect_assert_failure(list_splice_range
        (plist_list, list_begin(plist_list), plist_src, list_begin(plist_src), list_end(plist_src)));

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice_range__invalid_tearget_position(void** state)
{
    list_iterator_t it_iter;
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_list);
    list_init_n(plist_src, 10);
    expect_assert_failure(list_splice_range(
        plist_list, it_iter, plist_src, list_begin(plist_src), list_end(plist_src)));

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice_range__invalid_source_range(void** state)
{
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_list);
    list_init_n(plist_src, 10);
    expect_assert_failure(list_splice_range(
        plist_list, list_begin(plist_list), plist_src, list_end(plist_src), list_begin(plist_src)));

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice_range__invalid_target_position_in_range(void** state)
{
    list_t* plist_src = create_list(int);

    list_init_n(plist_src, 10);
    expect_assert_failure(list_splice_range(
        plist_src, iterator_next(list_begin(plist_src)), plist_src, list_begin(plist_src), list_end(plist_src)));

    list_destroy(plist_src);
}

void test_list_splice_range__same_list_container_pos_equal_begin(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 2);
    list_push_back(plist, 5);
    list_push_back(plist, 0);
    list_push_back(plist, 4);
    list_push_back(plist, 7);
    list_splice_range(plist, list_begin(plist), plist, list_begin(plist), list_end(plist));
    assert_true(list_size(plist) == 5);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);

    list_destroy(plist);
}

void test_list_splice_range__same_list_container_pos_equal_end(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 2);
    list_push_back(plist, 5);
    list_push_back(plist, 0);
    list_push_back(plist, 4);
    list_push_back(plist, 7);
    list_splice_range(plist, list_end(plist), plist, list_begin(plist), list_end(plist));
    assert_true(list_size(plist) == 5);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);

    list_destroy(plist);
}

void test_list_splice_range__same_list_container_pos_not_in_range(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 2);
    list_push_back(plist, 5);
    list_push_back(plist, 0);
    list_push_back(plist, 4);
    list_push_back(plist, 7);
    list_splice_range(plist, list_begin(plist), plist, iterator_advance(list_begin(plist), 2), list_end(plist));
    assert_true(list_size(plist) == 5);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 4);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 7);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 5);

    list_destroy(plist);
}

void test_list_splice_range__target_empty_range_empty(void** state)
{
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_list);
    list_init_elem(plist_src, 10, 100);
    list_splice_range(plist_list, list_begin(plist_list), plist_src, list_begin(plist_src), list_begin(plist_src));
    assert_true(list_size(plist_list) == 0);
    assert_true(list_size(plist_src) == 10);

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice_range__target_empty_range_not_empty(void** state)
{
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_list);
    list_init_elem(plist_src, 10, 100);
    list_splice_range(plist_list, list_begin(plist_list), plist_src, list_begin(plist_src), list_end(plist_src));
    assert_true(list_size(plist_list) == 10);
    assert_true(list_size(plist_src) == 0);

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice_range__target_begin_source_begin(void** state)
{
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init_n(plist_list, 10);
    list_init_elem(plist_src, 10, 100);
    list_splice_range(plist_list, list_begin(plist_list),
        plist_src, list_begin(plist_src), iterator_advance(list_begin(plist_src), 2));
    assert_true(list_size(plist_list) == 12);
    assert_true(list_size(plist_src) == 8);
    assert_true(*(int*)iterator_get_pointer(list_begin(plist_list)) == 100);
    assert_true(*(int*)iterator_get_pointer(iterator_next(list_begin(plist_list))) == 100);

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice_range__target_middle_source_middle(void** state)
{
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init_n(plist_list, 10);
    list_init_elem(plist_src, 10, 100);
    list_splice_range(plist_list, iterator_next(list_begin(plist_list)),
        plist_src, iterator_next(list_begin(plist_src)), iterator_advance(list_begin(plist_src), 3));
    assert_true(list_size(plist_list) == 12);
    assert_true(list_size(plist_src) == 8);
    assert_true(*(int*)iterator_get_pointer(iterator_next(list_begin(plist_list))) == 100);
    assert_true(*(int*)iterator_get_pointer(iterator_advance(list_begin(plist_list), 2)) == 100);

    list_destroy(plist_list);
    list_destroy(plist_src);
}

void test_list_splice_range__target_end_source_all(void** state)
{
    list_iterator_t it_iter;
    size_t i = 0;
    list_t* plist_list = create_list(int);
    list_t* plist_src = create_list(int);

    list_init_n(plist_list, 10);
    list_init_elem(plist_src, 10, 100);
    list_splice_range(plist_list, list_end(plist_list), plist_src, list_begin(plist_src), list_end(plist_src));
    assert_true(list_size(plist_list) == 20);
    assert_true(list_size(plist_src) == 0);
    for(it_iter = list_begin(plist_list), i = 0;
        !iterator_equal(it_iter, list_end(plist_list));
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

    list_destroy(plist_list);
    list_destroy(plist_src);
}

/*
 * test list_sort
 */
UT_CASE_DEFINATION(list_sort)
void test_list_sort__null_list_container(void** state)
{
    expect_assert_failure(list_sort(NULL));
}

void test_list_sort__non_inited_list_container(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(list_sort(plist));

    list_destroy(plist);
}


void test_list_sort__empty_less(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    assert_true(list_size(plist) == 0);
    list_sort(plist);
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

void test_list_sort__1_less(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 1);
    assert_true(list_size(plist) == 1);
    list_sort(plist);
    assert_true(list_size(plist) == 1);
    assert_true(*(int*)iterator_get_pointer(list_begin(plist)) == 0);

    list_destroy(plist);
}

void test_list_sort__2_equal_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_n(plist, 2);
    assert_true(list_size(plist) == 2);
    list_sort(plist);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    list_destroy(plist);
}

void test_list_sort__2_less_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 0);
    list_push_back(plist, 1);
    assert_true(list_size(plist) == 2);
    list_sort(plist);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    list_destroy(plist);
}

void test_list_sort__2_greater_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 1);
    list_push_back(plist, 0);
    assert_true(list_size(plist) == 2);
    list_sort(plist);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    list_destroy(plist);
}

void test_list_sort__random_equal_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    assert_true(list_size(plist) == 10);
    list_sort(plist);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_sort__random_less_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 0);
    list_push_back(plist, 1);
    list_push_back(plist, 2);
    list_push_back(plist, 3);
    list_push_back(plist, 4);
    list_push_back(plist, 5);
    list_push_back(plist, 6);
    list_push_back(plist, 7);
    list_push_back(plist, 8);
    list_push_back(plist, 9);
    assert_true(list_size(plist) == 10);
    list_sort(plist);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_sort__random_greater_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 9);
    list_push_back(plist, 8);
    list_push_back(plist, 7);
    list_push_back(plist, 6);
    list_push_back(plist, 5);
    list_push_back(plist, 4);
    list_push_back(plist, 3);
    list_push_back(plist, 2);
    list_push_back(plist, 1);
    list_push_back(plist, 0);
    assert_true(list_size(plist) == 10);
    list_sort(plist);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_sort__random_random_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 4);
    list_push_back(plist, 8);
    list_push_back(plist, 7);
    list_push_back(plist, 0);
    list_push_back(plist, 3);
    list_push_back(plist, 5);
    list_push_back(plist, 9);
    list_push_back(plist, 2);
    list_push_back(plist, 1);
    list_push_back(plist, 6);
    assert_true(list_size(plist) == 10);
    list_sort(plist);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_sort__random_random_dup_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 4);
    list_push_back(plist, 8);
    list_push_back(plist, 7);
    list_push_back(plist, 8);
    list_push_back(plist, 0);
    list_push_back(plist, 3);
    list_push_back(plist, 5);
    list_push_back(plist, 1);
    list_push_back(plist, 6);
    list_push_back(plist, 9);
    list_push_back(plist, 2);
    list_push_back(plist, 1);
    list_push_back(plist, 1);
    list_push_back(plist, 6);
    list_push_back(plist, 4);
    assert_true(list_size(plist) == 15);
    list_sort(plist);
    assert_true(list_size(plist) == 15);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

/*
 * test list_sort_if
 */
UT_CASE_DEFINATION(list_sort_if)
void test_list_sort_if__null_list_container(void** state)
{
    expect_assert_failure(list_sort_if(NULL, NULL));
}

void test_list_sort_if__non_inited_list_container(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(list_sort_if(plist, NULL));

    list_destroy(plist);
}

void test_list_sort_if__empty_less(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    assert_true(list_size(plist) == 0);
    list_sort_if(plist, NULL);
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

void test_list_sort_if__empty_greater(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    assert_true(list_size(plist) == 0);
    list_sort_if(plist, fun_greater_int);
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

void test_list_sort_if__1_less(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 1);
    assert_true(list_size(plist) == 1);
    list_sort_if(plist, NULL);
    assert_true(list_size(plist) == 1);
    assert_true(*(int*)iterator_get_pointer(list_begin(plist)) == 0);

    list_destroy(plist);
}

void test_list_sort_if__1_greater(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 1);
    assert_true(list_size(plist) == 1);
    list_sort_if(plist, fun_greater_int);
    assert_true(list_size(plist) == 1);
    assert_true(*(int*)iterator_get_pointer(list_begin(plist)) == 0);

    list_destroy(plist);
}

void test_list_sort_if__2_equal_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_n(plist, 2);
    assert_true(list_size(plist) == 2);
    list_sort_if(plist, NULL);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    list_destroy(plist);
}

void test_list_sort_if__2_equal_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_n(plist, 2);
    assert_true(list_size(plist) == 2);
    list_sort_if(plist, fun_greater_int);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    list_destroy(plist);
}

void test_list_sort_if__2_less_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 0);
    list_push_back(plist, 1);
    assert_true(list_size(plist) == 2);
    list_sort_if(plist, NULL);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    list_destroy(plist);
}

void test_list_sort_if__2_less_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 0);
    list_push_back(plist, 1);
    assert_true(list_size(plist) == 2);
    list_sort_if(plist, fun_greater_int);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    list_destroy(plist);
}

void test_list_sort_if__2_greater_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 1);
    list_push_back(plist, 0);
    assert_true(list_size(plist) == 2);
    list_sort_if(plist, NULL);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    list_destroy(plist);
}

void test_list_sort_if__2_greater_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 1);
    list_push_back(plist, 0);
    assert_true(list_size(plist) == 2);
    list_sort_if(plist, fun_greater_int);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    list_destroy(plist);
}

void test_list_sort_if__random_equal_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    assert_true(list_size(plist) == 10);
    list_sort_if(plist, NULL);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_sort_if__random_equal_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    assert_true(list_size(plist) == 10);
    list_sort_if(plist, fun_greater_int);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_sort_if__random_less_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 0);
    list_push_back(plist, 1);
    list_push_back(plist, 2);
    list_push_back(plist, 3);
    list_push_back(plist, 4);
    list_push_back(plist, 5);
    list_push_back(plist, 6);
    list_push_back(plist, 7);
    list_push_back(plist, 8);
    list_push_back(plist, 9);
    assert_true(list_size(plist) == 10);
    list_sort_if(plist, NULL);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_sort_if__random_less_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 0);
    list_push_back(plist, 1);
    list_push_back(plist, 2);
    list_push_back(plist, 3);
    list_push_back(plist, 4);
    list_push_back(plist, 5);
    list_push_back(plist, 6);
    list_push_back(plist, 7);
    list_push_back(plist, 8);
    list_push_back(plist, 9);
    assert_true(list_size(plist) == 10);
    list_sort_if(plist, fun_greater_int);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_sort_if__random_greater_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 9);
    list_push_back(plist, 8);
    list_push_back(plist, 7);
    list_push_back(plist, 6);
    list_push_back(plist, 5);
    list_push_back(plist, 4);
    list_push_back(plist, 3);
    list_push_back(plist, 2);
    list_push_back(plist, 1);
    list_push_back(plist, 0);
    assert_true(list_size(plist) == 10);
    list_sort_if(plist, NULL);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_sort_if__random_greater_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 9);
    list_push_back(plist, 8);
    list_push_back(plist, 7);
    list_push_back(plist, 6);
    list_push_back(plist, 5);
    list_push_back(plist, 4);
    list_push_back(plist, 3);
    list_push_back(plist, 2);
    list_push_back(plist, 1);
    list_push_back(plist, 0);
    assert_true(list_size(plist) == 10);
    list_sort_if(plist, fun_greater_int);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_sort_if__random_random_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 4);
    list_push_back(plist, 8);
    list_push_back(plist, 7);
    list_push_back(plist, 0);
    list_push_back(plist, 3);
    list_push_back(plist, 5);
    list_push_back(plist, 9);
    list_push_back(plist, 2);
    list_push_back(plist, 1);
    list_push_back(plist, 6);
    assert_true(list_size(plist) == 10);
    list_sort_if(plist, NULL);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_sort_if__random_random_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 1);
    list_push_back(plist, 8);
    list_push_back(plist, 3);
    list_push_back(plist, 0);
    list_push_back(plist, 2);
    list_push_back(plist, 6);
    list_push_back(plist, 4);
    list_push_back(plist, 9);
    list_push_back(plist, 5);
    list_push_back(plist, 7);
    assert_true(list_size(plist) == 10);
    list_sort_if(plist, fun_greater_int);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_sort_if__random_random_dup_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 4);
    list_push_back(plist, 8);
    list_push_back(plist, 7);
    list_push_back(plist, 8);
    list_push_back(plist, 0);
    list_push_back(plist, 3);
    list_push_back(plist, 5);
    list_push_back(plist, 1);
    list_push_back(plist, 6);
    list_push_back(plist, 9);
    list_push_back(plist, 2);
    list_push_back(plist, 1);
    list_push_back(plist, 1);
    list_push_back(plist, 6);
    list_push_back(plist, 4);
    assert_true(list_size(plist) == 15);
    list_sort_if(plist, NULL);
    assert_true(list_size(plist) == 15);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_sort_if__random_random_dup_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 1);
    list_push_back(plist, 8);
    list_push_back(plist, 0);
    list_push_back(plist, 8);
    list_push_back(plist, 3);
    list_push_back(plist, 0);
    list_push_back(plist, 0);
    list_push_back(plist, 2);
    list_push_back(plist, 6);
    list_push_back(plist, 4);
    list_push_back(plist, 9);
    list_push_back(plist, 5);
    list_push_back(plist, 7);
    list_push_back(plist, 5);
    list_push_back(plist, 7);
    assert_true(list_size(plist) == 15);
    list_sort_if(plist, fun_greater_int);
    assert_true(list_size(plist) == 15);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_sort_if__cstr_1_less(void** state)
{
    list_t* plist = create_list(char*);

    list_init_n(plist, 1);
    assert_true(list_size(plist) == 1);
    list_sort_if(plist, NULL);
    assert_true(list_size(plist) == 1);
    assert_true(strcmp((char*)iterator_get_pointer(list_begin(plist)), "") == 0);

    list_destroy(plist);
}

void test_list_sort_if__cstr_1_greater(void** state)
{
    list_t* plist = create_list(char*);

    list_init_n(plist, 1);
    assert_true(list_size(plist) == 1);
    list_sort_if(plist, fun_greater_cstr);
    assert_true(list_size(plist) == 1);
    assert_true(strcmp((char*)iterator_get_pointer(list_begin(plist)), "") == 0);

    list_destroy(plist);
}

void test_list_sort_if__cstr_2_equal_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init_n(plist, 2);
    assert_true(list_size(plist) == 2);
    list_sort_if(plist, NULL);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);

    list_destroy(plist);
}

void test_list_sort_if__cstr_2_equal_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init_n(plist, 2);
    assert_true(list_size(plist) == 2);
    list_sort_if(plist, fun_greater_cstr);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "") == 0);

    list_destroy(plist);
}

void test_list_sort_if__cstr_2_less_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_front(plist, "1");
    list_push_front(plist, "0");
    assert_true(list_size(plist) == 2);
    list_sort_if(plist, NULL);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);

    list_destroy(plist);
}

void test_list_sort_if__cstr_2_less_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_front(plist, "1");
    list_push_front(plist, "0");
    assert_true(list_size(plist) == 2);
    list_sort_if(plist, fun_greater_cstr);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);

    list_destroy(plist);
}

void test_list_sort_if__cstr_2_greater_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_front(plist, "0");
    list_push_front(plist, "1");
    assert_true(list_size(plist) == 2);
    list_sort_if(plist, NULL);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);

    list_destroy(plist);
}

void test_list_sort_if__cstr_2_greater_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_front(plist, "0");
    list_push_front(plist, "1");
    assert_true(list_size(plist) == 2);
    list_sort_if(plist, fun_greater_cstr);
    assert_true(list_size(plist) == 2);
    it_iter = list_begin(plist);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "1") == 0);
    it_iter = iterator_next(it_iter);
    assert_true(strcmp((char*)iterator_get_pointer(it_iter), "0") == 0);

    list_destroy(plist);
}

void test_list_sort_if__cstr_random_equal_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init_n(plist, 10);
    assert_true(list_size(plist) == 10);
    list_sort_if(plist, NULL);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_sort_if__cstr_random_equal_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init_n(plist, 10);
    assert_true(list_size(plist) == 10);
    list_sort_if(plist, fun_greater_cstr);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_sort_if__cstr_random_less_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_front(plist, "9");
    list_push_front(plist, "8");
    list_push_front(plist, "7");
    list_push_front(plist, "6");
    list_push_front(plist, "5");
    list_push_front(plist, "4");
    list_push_front(plist, "3");
    list_push_front(plist, "2");
    list_push_front(plist, "1");
    list_push_front(plist, "0");
    assert_true(list_size(plist) == 10);
    list_sort_if(plist, NULL);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_sort_if__cstr_random_less_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_front(plist, "9");
    list_push_front(plist, "8");
    list_push_front(plist, "7");
    list_push_front(plist, "6");
    list_push_front(plist, "5");
    list_push_front(plist, "4");
    list_push_front(plist, "3");
    list_push_front(plist, "2");
    list_push_front(plist, "1");
    list_push_front(plist, "0");
    assert_true(list_size(plist) == 10);
    list_sort_if(plist, fun_greater_cstr);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_sort_if__cstr_random_greater_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_front(plist, "0");
    list_push_front(plist, "1");
    list_push_front(plist, "2");
    list_push_front(plist, "3");
    list_push_front(plist, "4");
    list_push_front(plist, "5");
    list_push_front(plist, "6");
    list_push_front(plist, "7");
    list_push_front(plist, "8");
    list_push_front(plist, "9");
    assert_true(list_size(plist) == 10);
    list_sort_if(plist, NULL);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_sort_if__cstr_random_greater_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_front(plist, "0");
    list_push_front(plist, "1");
    list_push_front(plist, "2");
    list_push_front(plist, "3");
    list_push_front(plist, "4");
    list_push_front(plist, "5");
    list_push_front(plist, "6");
    list_push_front(plist, "7");
    list_push_front(plist, "8");
    list_push_front(plist, "9");
    assert_true(list_size(plist) == 10);
    list_sort_if(plist, fun_greater_cstr);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_sort_if__cstr_random_random_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_front(plist, "4");
    list_push_front(plist, "8");
    list_push_front(plist, "7");
    list_push_front(plist, "0");
    list_push_front(plist, "3");
    list_push_front(plist, "5");
    list_push_front(plist, "9");
    list_push_front(plist, "2");
    list_push_front(plist, "1");
    list_push_front(plist, "6");
    assert_true(list_size(plist) == 10);
    list_sort_if(plist, NULL);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_sort_if__cstr_random_random_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_front(plist, "1");
    list_push_front(plist, "8");
    list_push_front(plist, "3");
    list_push_front(plist, "0");
    list_push_front(plist, "2");
    list_push_front(plist, "6");
    list_push_front(plist, "4");
    list_push_front(plist, "9");
    list_push_front(plist, "5");
    list_push_front(plist, "7");
    assert_true(list_size(plist) == 10);
    list_sort_if(plist, fun_greater_cstr);
    assert_true(list_size(plist) == 10);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_sort_if__cstr_random_random_dup_less(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_front(plist, "4");
    list_push_front(plist, "8");
    list_push_front(plist, "7");
    list_push_front(plist, "8");
    list_push_front(plist, "0");
    list_push_front(plist, "3");
    list_push_front(plist, "5");
    list_push_front(plist, "1");
    list_push_front(plist, "6");
    list_push_front(plist, "9");
    list_push_front(plist, "2");
    list_push_front(plist, "1");
    list_push_front(plist, "1");
    list_push_front(plist, "6");
    list_push_front(plist, "4");
    assert_true(list_size(plist) == 15);
    list_sort_if(plist, NULL);
    assert_true(list_size(plist) == 15);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

void test_list_sort_if__cstr_random_random_dup_greater(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(char*);

    list_init(plist);
    list_push_front(plist, "1");
    list_push_front(plist, "8");
    list_push_front(plist, "0");
    list_push_front(plist, "8");
    list_push_front(plist, "3");
    list_push_front(plist, "0");
    list_push_front(plist, "0");
    list_push_front(plist, "2");
    list_push_front(plist, "6");
    list_push_front(plist, "4");
    list_push_front(plist, "9");
    list_push_front(plist, "5");
    list_push_front(plist, "7");
    list_push_front(plist, "5");
    list_push_front(plist, "7");
    assert_true(list_size(plist) == 15);
    list_sort_if(plist, fun_greater_cstr);
    assert_true(list_size(plist) == 15);
    it_iter = list_begin(plist);
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

    list_destroy(plist);
}

/*
 * test list_merge
 */
UT_CASE_DEFINATION(list_merge)
void test_list_merge__null_dest_list_container(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    expect_assert_failure(list_merge(NULL, plist));

    list_destroy(plist);
}

void test_list_merge__null_src_list_container(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    expect_assert_failure(list_merge(plist, NULL));

    list_destroy(plist);
}

void test_list_merge__non_inited_dest_list_container(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_src);
    expect_assert_failure(list_merge(plist_dest, plist_src));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_merge__non_inited_src_list_container(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_dest);
    expect_assert_failure(list_merge(plist_dest, plist_src));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_merge__not_same(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(double);

    list_init(plist_dest);
    list_init(plist_src);
    expect_assert_failure(list_merge(plist_dest, plist_src));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_merge__same_list_container(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    list_merge(plist, plist);
    assert_true(list_empty(plist));

    list_destroy(plist);
}

void test_list_merge__dest_empty_src_empty(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_dest);
    list_init(plist_src);
    list_merge(plist_dest, plist_src);
    assert_true(list_empty(plist_dest));
    assert_true(list_empty(plist_src));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_merge__dest_non_empty_src_empty(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init_n(plist_dest, 10);
    list_init(plist_src);
    list_merge(plist_dest, plist_src);
    assert_true(list_size(plist_dest) == 10);
    assert_true(list_empty(plist_src));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_merge__dest_empty_src_non_empty(void** state)
{
    list_iterator_t it_iter;
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_dest);
    list_init_n(plist_src, 10);
    list_merge(plist_dest, plist_src);
    assert_true(list_size(plist_dest) == 10);
    assert_true(list_empty(plist_src));
    for(it_iter = list_begin(plist_dest);
        !iterator_equal(it_iter, list_end(plist_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_merge__dest_tailing(void** state)
{
    list_iterator_t it_iter;
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_dest);
    list_push_back(plist_dest, 4);
    list_push_back(plist_dest, 5);
    list_push_back(plist_dest, 8);
    list_push_back(plist_dest, 9);
    list_init(plist_src);
    list_push_back(plist_src, 2);
    list_push_back(plist_src, 3);
    list_push_back(plist_src, 7);
    list_merge(plist_dest, plist_src);
    assert_true(list_size(plist_dest) == 7);
    assert_true(list_empty(plist_src));
    it_iter = list_begin(plist_dest);
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

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_merge__src_tailing(void** state)
{
    list_iterator_t it_iter;
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_dest);
    list_push_back(plist_dest, 3);
    list_push_back(plist_dest, 5);
    list_push_back(plist_dest, 5);
    list_push_back(plist_dest, 7);
    list_init(plist_src);
    list_push_back(plist_src, 2);
    list_push_back(plist_src, 3);
    list_push_back(plist_src, 7);
    list_push_back(plist_src, 8);
    list_push_back(plist_src, 9);
    list_merge(plist_dest, plist_src);
    assert_true(list_size(plist_dest) == 9);
    assert_true(list_empty(plist_src));
    it_iter = list_begin(plist_dest);
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

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_merge__random(void** state)
{
    list_iterator_t it_iter;
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_dest);
    list_push_back(plist_dest, 3);
    list_push_back(plist_dest, 8);
    list_push_back(plist_dest, 5);
    list_push_back(plist_dest, 3);
    list_init(plist_src);
    list_push_back(plist_src, 3);
    list_push_back(plist_src, 9);
    list_push_back(plist_src, 7);
    list_push_back(plist_src, 8);
    list_push_back(plist_src, 2);
    list_merge(plist_dest, plist_src);
    assert_true(list_size(plist_dest) == 9);
    assert_true(list_empty(plist_src));
    it_iter = list_begin(plist_dest);
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

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_merge__cstr_dest_tailing(void** state)
{
    list_iterator_t it_iter;
    list_t* plist_dest = create_list(char*);
    list_t* plist_src = create_list(char*);

    list_init(plist_dest);
    list_push_back(plist_dest, "4");
    list_push_back(plist_dest, "5");
    list_push_back(plist_dest, "8");
    list_push_back(plist_dest, "9");
    list_init(plist_src);
    list_push_back(plist_src, "2");
    list_push_back(plist_src, "3");
    list_push_back(plist_src, "7");
    list_merge(plist_dest, plist_src);
    assert_true(list_size(plist_dest) == 7);
    assert_true(list_empty(plist_src));
    it_iter = list_begin(plist_dest);
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

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_merge__cstr_src_tailing(void** state)
{
    list_iterator_t it_iter;
    list_t* plist_dest = create_list(char*);
    list_t* plist_src = create_list(char*);

    list_init(plist_dest);
    list_push_back(plist_dest, "3");
    list_push_back(plist_dest, "5");
    list_push_back(plist_dest, "5");
    list_push_back(plist_dest, "7");
    list_init(plist_src);
    list_push_back(plist_src, "2");
    list_push_back(plist_src, "3");
    list_push_back(plist_src, "7");
    list_push_back(plist_src, "8");
    list_push_back(plist_src, "9");
    list_merge(plist_dest, plist_src);
    assert_true(list_size(plist_dest) == 9);
    assert_true(list_empty(plist_src));
    it_iter = list_begin(plist_dest);
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

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_merge__cstr_random(void** state)
{
    list_iterator_t it_iter;
    list_t* plist_dest = create_list(char*);
    list_t* plist_src = create_list(char*);

    list_init(plist_dest);
    list_push_back(plist_dest, "3");
    list_push_back(plist_dest, "8");
    list_push_back(plist_dest, "5");
    list_push_back(plist_dest, "3");
    list_init(plist_src);
    list_push_back(plist_src, "3");
    list_push_back(plist_src, "9");
    list_push_back(plist_src, "7");
    list_push_back(plist_src, "8");
    list_push_back(plist_src, "2");
    list_merge(plist_dest, plist_src);
    assert_true(list_size(plist_dest) == 9);
    assert_true(list_empty(plist_src));
    it_iter = list_begin(plist_dest);
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

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

/*
 * test list_merge_if
 */
UT_CASE_DEFINATION(list_merge_if)
void test_list_merge_if__null_dest_list_container(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    expect_assert_failure(list_merge_if(NULL, plist, NULL));

    list_destroy(plist);
}

void test_list_merge_if__null_src_list_container(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    expect_assert_failure(list_merge_if(plist, NULL, NULL));

    list_destroy(plist);
}

void test_list_merge_if__non_inited_dest_list_container(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_src);
    expect_assert_failure(list_merge_if(plist_dest, plist_src, NULL));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_merge_if__non_inited_src_list_container(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_dest);
    expect_assert_failure(list_merge_if(plist_dest, plist_src, NULL));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_merge_if__not_same(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(double);

    list_init(plist_dest);
    list_init(plist_src);
    expect_assert_failure(list_merge_if(plist_dest, plist_src, NULL));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_merge_if__same_list_container(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    list_merge_if(plist, plist, NULL);
    assert_true(list_empty(plist));

    list_destroy(plist);
}

void test_list_merge_if__dest_empty_src_empty(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_dest);
    list_init(plist_src);
    list_merge_if(plist_dest, plist_src, NULL);
    assert_true(list_empty(plist_dest));
    assert_true(list_empty(plist_src));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_merge_if__dest_non_empty_src_empty(void** state)
{
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init_n(plist_dest, 10);
    list_init(plist_src);
    list_merge_if(plist_dest, plist_src, NULL);
    assert_true(list_size(plist_dest) == 10);
    assert_true(list_empty(plist_src));

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_merge_if__dest_empty_src_non_empty(void** state)
{
    list_iterator_t it_iter;
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_dest);
    list_init_n(plist_src, 10);
    list_merge_if(plist_dest, plist_src, NULL);
    assert_true(list_size(plist_dest) == 10);
    assert_true(list_empty(plist_src));
    for(it_iter = list_begin(plist_dest);
        !iterator_equal(it_iter, list_end(plist_dest));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_merge_if__ascending_dest_tailing(void** state)
{
    list_iterator_t it_iter;
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_dest);
    list_push_back(plist_dest, 4);
    list_push_back(plist_dest, 5);
    list_push_back(plist_dest, 8);
    list_push_back(plist_dest, 9);
    list_init(plist_src);
    list_push_back(plist_src, 2);
    list_push_back(plist_src, 3);
    list_push_back(plist_src, 7);
    list_merge_if(plist_dest, plist_src, NULL);
    assert_true(list_size(plist_dest) == 7);
    assert_true(list_empty(plist_src));
    it_iter = list_begin(plist_dest);
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

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_merge_if__ascending_src_tailing(void** state)
{
    list_iterator_t it_iter;
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_dest);
    list_push_back(plist_dest, 3);
    list_push_back(plist_dest, 5);
    list_push_back(plist_dest, 5);
    list_push_back(plist_dest, 7);
    list_init(plist_src);
    list_push_back(plist_src, 2);
    list_push_back(plist_src, 3);
    list_push_back(plist_src, 7);
    list_push_back(plist_src, 8);
    list_push_back(plist_src, 9);
    list_merge_if(plist_dest, plist_src, NULL);
    assert_true(list_size(plist_dest) == 9);
    assert_true(list_empty(plist_src));
    it_iter = list_begin(plist_dest);
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

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_merge_if__descending_dest_tailing(void** state)
{
    list_iterator_t it_iter;
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_dest);
    list_push_back(plist_dest, 8);
    list_push_back(plist_dest, 5);
    list_push_back(plist_dest, 3);
    list_push_back(plist_dest, 3);
    list_push_back(plist_dest, 2);
    list_init(plist_src);
    list_push_back(plist_src, 9);
    list_push_back(plist_src, 8);
    list_push_back(plist_src, 7);
    list_push_back(plist_src, 3);
    list_merge_if(plist_dest, plist_src, fun_greater_int);
    assert_true(list_size(plist_dest) == 9);
    assert_true(list_empty(plist_src));
    it_iter = list_begin(plist_dest);
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

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_merge_if__descending_src_tailing(void** state)
{
    list_iterator_t it_iter;
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_dest);
    list_push_back(plist_dest, 8);
    list_push_back(plist_dest, 5);
    list_push_back(plist_dest, 3);
    list_push_back(plist_dest, 3);
    list_init(plist_src);
    list_push_back(plist_src, 9);
    list_push_back(plist_src, 8);
    list_push_back(plist_src, 7);
    list_push_back(plist_src, 3);
    list_push_back(plist_src, 2);
    list_merge_if(plist_dest, plist_src, fun_greater_int);
    assert_true(list_size(plist_dest) == 9);
    assert_true(list_empty(plist_src));
    it_iter = list_begin(plist_dest);
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

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_merge_if__random(void** state)
{
    list_iterator_t it_iter;
    list_t* plist_dest = create_list(int);
    list_t* plist_src = create_list(int);

    list_init(plist_dest);
    list_push_back(plist_dest, 3);
    list_push_back(plist_dest, 8);
    list_push_back(plist_dest, 5);
    list_push_back(plist_dest, 3);
    list_init(plist_src);
    list_push_back(plist_src, 3);
    list_push_back(plist_src, 9);
    list_push_back(plist_src, 7);
    list_push_back(plist_src, 8);
    list_push_back(plist_src, 2);
    list_merge_if(plist_dest, plist_src, NULL);
    assert_true(list_size(plist_dest) == 9);
    assert_true(list_empty(plist_src));
    it_iter = list_begin(plist_dest);
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

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_merge_if__cstr_ascending_dest_tailing(void** state)
{
    list_iterator_t it_iter;
    list_t* plist_dest = create_list(char*);
    list_t* plist_src = create_list(char*);

    list_init(plist_dest);
    list_push_back(plist_dest, "4");
    list_push_back(plist_dest, "5");
    list_push_back(plist_dest, "8");
    list_push_back(plist_dest, "9");
    list_init(plist_src);
    list_push_back(plist_src, "2");
    list_push_back(plist_src, "3");
    list_push_back(plist_src, "7");
    list_merge_if(plist_dest, plist_src, NULL);
    assert_true(list_size(plist_dest) == 7);
    assert_true(list_empty(plist_src));
    it_iter = list_begin(plist_dest);
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

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_merge_if__cstr_ascending_src_tailing(void** state)
{
    list_iterator_t it_iter;
    list_t* plist_dest = create_list(char*);
    list_t* plist_src = create_list(char*);

    list_init(plist_dest);
    list_push_back(plist_dest, "3");
    list_push_back(plist_dest, "5");
    list_push_back(plist_dest, "5");
    list_push_back(plist_dest, "7");
    list_init(plist_src);
    list_push_back(plist_src, "2");
    list_push_back(plist_src, "3");
    list_push_back(plist_src, "7");
    list_push_back(plist_src, "8");
    list_push_back(plist_src, "9");
    list_merge_if(plist_dest, plist_src, NULL);
    assert_true(list_size(plist_dest) == 9);
    assert_true(list_empty(plist_src));
    it_iter = list_begin(plist_dest);
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

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_merge_if__cstr_descending_dest_tailing(void** state)
{
    list_iterator_t it_iter;
    list_t* plist_dest = create_list(char*);
    list_t* plist_src = create_list(char*);

    list_init(plist_dest);
    list_push_back(plist_dest, "9");
    list_push_back(plist_dest, "8");
    list_push_back(plist_dest, "5");
    list_push_back(plist_dest, "4");
    list_push_back(plist_dest, "2");
    list_init(plist_src);
    list_push_back(plist_src, "7");
    list_push_back(plist_src, "3");
    list_merge_if(plist_dest, plist_src, fun_greater_cstr);
    assert_true(list_size(plist_dest) == 7);
    assert_true(list_empty(plist_src));
    it_iter = list_begin(plist_dest);
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

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_merge_if__cstr_descending_src_tailing(void** state)
{
    list_iterator_t it_iter;
    list_t* plist_dest = create_list(char*);
    list_t* plist_src = create_list(char*);

    list_init(plist_dest);
    list_push_back(plist_dest, "7");
    list_push_back(plist_dest, "5");
    list_push_back(plist_dest, "5");
    list_push_back(plist_dest, "3");
    list_init(plist_src);
    list_push_back(plist_src, "9");
    list_push_back(plist_src, "8");
    list_push_back(plist_src, "7");
    list_push_back(plist_src, "3");
    list_push_back(plist_src, "2");
    list_merge_if(plist_dest, plist_src, fun_greater_cstr);
    assert_true(list_size(plist_dest) == 9);
    assert_true(list_empty(plist_src));
    it_iter = list_begin(plist_dest);
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

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

void test_list_merge_if__cstr_random(void** state)
{
    list_iterator_t it_iter;
    list_t* plist_dest = create_list(char*);
    list_t* plist_src = create_list(char*);

    list_init(plist_dest);
    list_push_back(plist_dest, "3");
    list_push_back(plist_dest, "8");
    list_push_back(plist_dest, "5");
    list_push_back(plist_dest, "3");
    list_init(plist_src);
    list_push_back(plist_src, "3");
    list_push_back(plist_src, "9");
    list_push_back(plist_src, "7");
    list_push_back(plist_src, "8");
    list_push_back(plist_src, "2");
    list_merge_if(plist_dest, plist_src, NULL);
    assert_true(list_size(plist_dest) == 9);
    assert_true(list_empty(plist_src));
    it_iter = list_begin(plist_dest);
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

    list_destroy(plist_dest);
    list_destroy(plist_src);
}

/*
 * test list_reverse
 */
UT_CASE_DEFINATION(list_reverse)
void test_list_reverse__null_list_container(void** state)
{
    expect_assert_failure(list_reverse(NULL));
}

void test_list_reverse__non_inited_list_container(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(list_reverse(plist));

    list_destroy(plist);
}

void test_list_reverse__empty(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    list_reverse(plist);
    assert_true(list_empty(plist));

    list_destroy(plist);
}

void test_list_reverse__same(void** state)
{
    list_t* plist = create_list(int);
    list_iterator_t it_iter;

    list_init_elem(plist, 10, 100);
    list_reverse(plist);
    assert_true(list_size(plist) == 10);
    for(it_iter = list_begin(plist);
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    list_destroy(plist);
}

void test_list_reverse__not_same(void** state)
{
    list_t* plist = create_list(int);
    size_t i = 0;
    list_iterator_t it_iter;

    list_init(plist);
    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist, i);
    }
    list_reverse(plist);
    assert_true(list_size(plist) == 10);
    for(it_iter = list_begin(plist), i = 0;
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 9 - i);
    }

    list_destroy(plist);
}

