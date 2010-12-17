#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_iterator.h"
#include "cstl/cstl_list_iterator.h"
#include "cstl/clist.h"
#include "cstl_list_aux.h"
#include "cstl/cvector.h"
#include "cstl_vector_aux.h"
#include "cstl/cstring.h"

#include "ut_def.h"
#include "ut_cstl_list.h"

UT_SUIT_DEFINATION(cstl_list, test_list_init__null_list_container)

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
    list._pt_node = 0x9383;
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
    list._pt_node = 0x73734;
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

void test_list_destroy__non_inited_list_container(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    plist->_pt_node->_pt_next = NULL;
    expect_assert_failure(list_destroy(plist));

    plist->_pt_node->_pt_next = plist->_pt_node;
    list_destroy(plist);
}

void test_list_destroy__empty(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    list_destroy(plist);
    assert_true(plist->_pt_node == NULL);
}

void test_list_destroy__non_empty(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    list_destroy(plist);
    assert_true(plist->_pt_node == NULL);
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
    plist_dest->_pt_node = 0x3333;
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
    plist_dest->_pt_node = 0x8383;
    expect_assert_failure(list_init_copy_range(NULL, list_begin(plist_src), list_end(plist_src)));

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
    assert_false(list_equal(plist_first, plist_second));

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
    assert_true(list_not_equal(plist_first, plist_second));

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
    assert_true(it_begin._t_pos._pc_corepos == plist->_pt_node->_pt_next);
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
    assert_true(it_end._t_pos._pc_corepos == plist->_pt_node);

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
    it_pos._t_pos._pc_corepos = NULL;

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
    listnode_t* pt_node = NULL;
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
    it_pos._t_pos._pc_corepos = NULL;
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

