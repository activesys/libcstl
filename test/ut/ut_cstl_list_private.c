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
#include "cstl/cstring.h"

#include "ut_def.h"
#include "ut_cstl_list_private.h"

UT_SUIT_DEFINATION(cstl_list_private, _create_list)

/*
 * test _create_list
 */
UT_CASE_DEFINATION(_create_list)
void test__create_list__null_typename(void** state)
{
    expect_assert_failure(_create_list(NULL));
}

void test__create_list__unregisted_type(void** state)
{
    assert_true(_create_list("_test__create_list__unregisted_type_t") == NULL);
}

void test__create_list__c_builtin_type(void** state)
{
    list_t* plist = _create_list("unsigned int");
    assert_true(plist != NULL);
    assert_true(strcmp(_GET_LIST_TYPE_NAME(plist), "unsigned int") == 0);

    list_destroy(plist);
}

void test__create_list__libcstl_builtin_type(void** state)
{
    list_t* plist = _create_list("vector_t         <      int>     ");
    assert_true(plist != NULL);
    assert_true(strcmp(_GET_LIST_TYPE_NAME(plist), "vector_t<int>") == 0);

    list_destroy(plist);
}

typedef struct _tag_test__create_list__user_defined_type
{
    int n_elem;
}_test__create_list__user_defined_type_t;

void test__create_list__user_defined_type(void** state)
{
    list_t* plist = NULL;

    type_register(struct _tag_test__create_list__user_defined_type, NULL, NULL, NULL, NULL);
    plist = _create_list("struct      _tag_test__create_list__user_defined_type");
    assert_true(plist != NULL);
    assert_true(strcmp(_GET_LIST_TYPE_NAME(plist), "struct _tag_test__create_list__user_defined_type") == 0);

    list_destroy(plist);
}

void test__create_list__user_defined_type_dup(void** state)
{
    list_t* plist = NULL;

    type_duplicate(struct _tag_test__create_list__user_defined_type, _test__create_list__user_defined_type_t);
    plist = _create_list("_test__create_list__user_defined_type_t");
    assert_true(plist != NULL);
    assert_true(strcmp(_GET_LIST_TYPE_NAME(plist), "_test__create_list__user_defined_type_t") == 0);

    list_destroy(plist);
}

/*
 * test _create_list_auxiliary
 */
UT_CASE_DEFINATION(_create_list_auxiliary)
void test__create_list_auxiliary__null_list_container(void** state)
{
    expect_assert_failure(_create_list_auxiliary(NULL, "int"));
}

void test__create_list_auxiliary__null_typename(void** state)
{
    list_t* plist = malloc(sizeof(list_t));
    expect_assert_failure(_create_list_auxiliary(plist, NULL));

    free(plist);
}

void test__create_list_auxiliary__unregisted_type(void** state)
{
    list_t* plist = malloc(sizeof(list_t));
    assert_false(_create_list_auxiliary(plist, "_test__create_list_auxiliary__unregisted_type_t"));

    free(plist);
}

void test__create_list_auxiliary__c_builtin(void** state)
{
    list_t* plist = malloc(sizeof(list_t));
    assert_true(_create_list_auxiliary(plist, "double"));
    assert_true(strcmp(_GET_LIST_TYPE_NAME(plist), "double") == 0);
    assert_true(_alloc_is_inited(&plist->_t_allocator));

    list_destroy(plist);
}

void test__create_list_auxiliary__libcstl_builtin(void** state)
{
    list_t* plist = malloc(sizeof(list_t));
    assert_true(_create_list_auxiliary(plist, "list_t<   vector_t     <     string_t>>       "));
    assert_true(strcmp(_GET_LIST_TYPE_NAME(plist), "list_t<vector_t<string_t>>") == 0);
    assert_true(_alloc_is_inited(&plist->_t_allocator));

    list_destroy(plist);
}

typedef struct _tag_test__create_list_auxiliary__user_defined
{
    int n_elem;
}_test__create_list_auxiliary__user_defined_t;
void test__create_list_auxiliary__user_defined(void** state)
{
    list_t* plist = NULL;
    type_register(struct _tag_test__create_list_auxiliary__user_defined, NULL, NULL, NULL, NULL);
    plist = malloc(sizeof(list_t));
    assert_true(_create_list_auxiliary(plist, "struct _tag_test__create_list_auxiliary__user_defined"));
    assert_true(strcmp(_GET_LIST_TYPE_NAME(plist), "struct _tag_test__create_list_auxiliary__user_defined") == 0);
    assert_true(_alloc_is_inited(&plist->_t_allocator));

    list_destroy(plist);
}

void test__create_list_auxiliary__user_defined_dup(void** state)
{
    list_t* plist = NULL;
    type_duplicate(struct _tag_test__create_list_auxiliary__user_defined, _test__create_list_auxiliary__user_defined_t);
    plist = malloc(sizeof(list_t));
    assert_true(_create_list_auxiliary(plist, "_test__create_list_auxiliary__user_defined_t"));
    assert_true(strcmp(_GET_LIST_TYPE_NAME(plist), "_test__create_list_auxiliary__user_defined_t") == 0);
    assert_true(_alloc_is_inited(&plist->_t_allocator));

    list_destroy(plist);
}

/*
 * test _list_init_elem and _list_init_elem_varg
 */
UT_CASE_DEFINATION(_list_init_elem__list_init_elem_varg)
void test__list_init_elem__list_init_elem_varg__null_list_container(void** state)
{
    expect_assert_failure(_list_init_elem(NULL, 10, 100));
}

void test__list_init_elem__list_init_elem_varg__non_created_list_container(void** state)
{
    list_t* plist = create_list(int);

    plist->_pt_node = (_listnode_t*)0x8834;
    expect_assert_failure(_list_init_elem(plist, 10, 100));

    plist->_pt_node = NULL;
    list_destroy(plist);
}

void test__list_init_elem__list_init_elem_varg__0_count(void** state)
{
    list_t* plist = create_list(int);

    _list_init_elem(plist, 0, 100);
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

void test__list_init_elem__list_init_elem_varg__count(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    _list_init_elem(plist, 10, 100);
    assert_true(list_size(plist) == 10);
    for(it_iter = list_begin(plist);
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    list_destroy(plist);
}

void test__list_init_elem__list_init_elem_varg__multiple_elem(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    _list_init_elem(plist, 10, 100, 3940, 23342, -284);
    assert_true(list_size(plist) == 10);
    for(it_iter = list_begin(plist);
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    list_destroy(plist);
}

/*
 * test _list_destroy_auxiliary
 */
UT_CASE_DEFINATION(_list_destroy_auxiliary)
void test__list_destroy_auxiliary__null_list_container(void** state)
{
    expect_assert_failure(_list_destroy_auxiliary(NULL));
}

void test__list_destroy_auxiliary__non_created_list_container(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    plist->_pt_node->_pt_next = NULL;
    expect_assert_failure(_list_destroy_auxiliary(plist));

    plist->_pt_node->_pt_next = plist->_pt_node;
    list_destroy(plist);
}

void test__list_destroy_auxiliary__non_inited(void** state)
{
    list_t* plist = create_list(int);
    _list_destroy_auxiliary(plist);
    assert_true(plist->_pt_node == NULL);

    free(plist);
}

void test__list_destroy_auxiliary__empty(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    _list_destroy_auxiliary(plist);
    assert_true(plist->_pt_node == NULL);

    free(plist);
}

void test__list_destroy_auxiliary__non_empty(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    assert_true(list_size(plist) == 10);
    _list_destroy_auxiliary(plist);
    assert_true(plist->_pt_node == NULL);

    free(plist);
}

/*
 * test _list_assign_elem and _list_assign_elem_varg
 */
UT_CASE_DEFINATION(_list_assign_elem__list_assign_elem_varg)
void test__list_assign_elem__list_assign_elem_varg__null_list_container(void** state)
{
    expect_assert_failure(_list_assign_elem(NULL, 10, 100));
}

void test__list_assign_elem__list_assign_elem_varg__non_inited_list_container(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(_list_assign_elem(plist, 10, 100));

    list_destroy(plist);
}

void test__list_assign_elem__list_assign_elem_varg__0_assign_0(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    assert_true(list_size(plist) == 0);
    _list_assign_elem(plist, 0, 100);
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

void test__list_assign_elem__list_assign_elem_varg__0_assign_n(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init(plist);

    assert_true(list_size(plist) == 0);
    _list_assign_elem(plist, 10, 100);
    assert_true(list_size(plist) == 10);
    for(it_iter = list_begin(plist);
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    list_destroy(plist);
}

void test__list_assign_elem__list_assign_elem_varg__n_assign_0(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init_n(plist, 10);

    assert_true(list_size(plist) == 10);
    for(it_iter = list_begin(plist);
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }
    _list_assign_elem(plist, 0, 100);
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

void test__list_assign_elem__list_assign_elem_varg__n_assign_m_n_greater_than_m(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init_n(plist, 10);

    assert_true(list_size(plist) == 10);
    for(it_iter = list_begin(plist);
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }
    _list_assign_elem(plist, 4, 100);
    assert_true(list_size(plist) == 4);
    for(it_iter = list_begin(plist);
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    list_destroy(plist);
}

void test__list_assign_elem__list_assign_elem_varg__n_assign_m_n_equal_to_m(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init_n(plist, 10);

    assert_true(list_size(plist) == 10);
    for(it_iter = list_begin(plist);
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }
    _list_assign_elem(plist, 10, 100);
    assert_true(list_size(plist) == 10);
    for(it_iter = list_begin(plist);
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    list_destroy(plist);
}

void test__list_assign_elem__list_assign_elem_varg__n_assign_m_n_less_than_m(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init_n(plist, 10);

    assert_true(list_size(plist) == 10);
    for(it_iter = list_begin(plist);
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }
    _list_assign_elem(plist, 18, 100);
    assert_true(list_size(plist) == 18);
    for(it_iter = list_begin(plist);
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    list_destroy(plist);
}

void test__list_assign_elem__list_assign_elem_varg__n_assign_m_n_less_than_m_multiple(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);
    list_init_n(plist, 10);

    assert_true(list_size(plist) == 10);
    for(it_iter = list_begin(plist);
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }
    _list_assign_elem(plist, 18, 100, 2983, 2445, 2222);
    assert_true(list_size(plist) == 18);
    for(it_iter = list_begin(plist);
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    list_destroy(plist);
}

/*
 * test _list_push_back and _list_push_back_varg
 */
UT_CASE_DEFINATION(_list_push_back__list_push_back_varg)
void test__list_push_back__list_push_back_varg__null_list_container(void** state)
{
    expect_assert_failure(_list_push_back(NULL, 100));
}

void test__list_push_back__list_push_back_varg__non_inited_list_container(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(_list_push_back(plist, 100));

    list_destroy(plist);
}

void test__list_push_back__list_push_back_varg__empty(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    _list_push_back(plist, 100);
    assert_true(list_size(plist) == 1);
    assert_true(*(int*)list_back(plist) == 100);

    list_destroy(plist);
}

void test__list_push_back__list_push_back_varg__non_empty(void** state)
{
    list_t* plist = create_list(int);
    size_t t_oldsize = 0;

    list_init_n(plist, 10);
    t_oldsize = list_size(plist);
    _list_push_back(plist, 100);
    assert_true(list_size(plist) == t_oldsize + 1);
    assert_true(*(int*)list_back(plist) == 100);

    list_destroy(plist);
}

void test__list_push_back__list_push_back_varg__non_empty_multiple(void** state)
{
    list_t* plist = create_list(int);
    size_t t_oldsize = 0;

    list_init_n(plist, 10);
    t_oldsize = list_size(plist);
    _list_push_back(plist, 100, 927, 0, 7284394);
    assert_true(list_size(plist) == t_oldsize + 1);
    assert_true(*(int*)list_back(plist) == 100);

    list_destroy(plist);
}

/*
 * test _list_push_front and _list_push_front_varg
 */
UT_CASE_DEFINATION(_list_push_front__list_push_front_varg)
void test__list_push_front__list_push_front_varg__null_list_container(void** state)
{
    expect_assert_failure(_list_push_front(NULL, 100));
}

void test__list_push_front__list_push_front_varg__non_inited_list_container(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(_list_push_front(plist, 100));

    list_destroy(plist);
}

void test__list_push_front__list_push_front_varg__empty(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    _list_push_front(plist, 100);
    assert_true(list_size(plist) == 1);
    assert_true(*(int*)list_front(plist) == 100);

    list_destroy(plist);
}

void test__list_push_front__list_push_front_varg__non_empty(void** state)
{
    list_t* plist = create_list(int);
    size_t t_oldsize = 0;

    list_init_n(plist, 10);
    t_oldsize = list_size(plist);
    _list_push_front(plist, 100);
    assert_true(list_size(plist) == t_oldsize + 1);
    assert_true(*(int*)list_front(plist) == 100);

    list_destroy(plist);
}

void test__list_push_front__list_push_front_varg__non_empty_multiple(void** state)
{
    list_t* plist = create_list(int);
    size_t t_oldsize = 0;

    list_init_n(plist, 10);
    t_oldsize = list_size(plist);
    _list_push_front(plist, 100, 98, 23523, 2222);
    assert_true(list_size(plist) == t_oldsize + 1);
    assert_true(*(int*)list_front(plist) == 100);

    list_destroy(plist);
}

/*
 * test _list_resize_elem and _list_resize_elem_varg
 */
UT_CASE_DEFINATION(_list_resize_elem__list_resize_elem_varg)
void test__list_resize_elem__list_resize_elem_varg__null_list_container(void** state)
{
    expect_assert_failure(_list_resize_elem(NULL, 10, 100));
}

void test__list_resize_elem__list_resize_elem_varg__non_inited_list_container(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(_list_resize_elem(plist, 10, 100));

    list_destroy(plist);
}

void test__list_resize_elem__list_resize_elem_varg__0_resize_0(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    _list_resize_elem(plist, 0, 100);
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

void test__list_resize_elem__list_resize_elem_varg__0_resize_n(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init(plist);
    _list_resize_elem(plist, 10, 100);
    assert_true(list_size(plist) == 10);
    for(it_iter = list_begin(plist);
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    list_destroy(plist);
}

void test__list_resize_elem__list_resize_elem_varg__n_resize_0(void** state)
{
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    _list_resize_elem(plist, 0, 100);
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

void test__list_resize_elem__list_resize_elem_varg__n_resize_m_n_greater_than_m(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    _list_resize_elem(plist, 4, 100);
    assert_true(list_size(plist) == 4);
    for(it_iter = list_begin(plist);
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    list_destroy(plist);
}

void test__list_resize_elem__list_resize_elem_varg__n_resize_m_n_equal_to_m(void** state)
{
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    _list_resize_elem(plist, 10, 100);
    assert_true(list_size(plist) == 10);
    for(it_iter = list_begin(plist);
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    list_destroy(plist);
}

void test__list_resize_elem__list_resize_elem_varg__n_resize_m_n_less_than_m(void** state)
{
    size_t i = 0;
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    _list_resize_elem(plist, 16, 100);
    assert_true(list_size(plist) == 16);
    for(it_iter = list_begin(plist), i = 0;
        !iterator_equal(it_iter, list_end(plist));
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

    list_destroy(plist);
}

void test__list_resize_elem__list_resize_elem_varg__n_resize_m_n_less_than_m_multiple(void** state)
{
    size_t i = 0;
    list_iterator_t it_iter;
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    _list_resize_elem(plist, 16, 100, 0, 28348, 274984);
    assert_true(list_size(plist) == 16);
    for(it_iter = list_begin(plist), i = 0;
        !iterator_equal(it_iter, list_end(plist));
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

    list_destroy(plist);
}

/*
 * test _list_remove and _list_remove_varg
 */
UT_CASE_DEFINATION(_list_remove__list_remove_varg)
void test__list_remove__list_remove_varg__null_list_container(void** state)
{
    expect_assert_failure(_list_remove(NULL, 99));
}

void test__list_remove__list_remove_varg__non_inited_list_container(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(_list_remove(plist, 99));

    list_destroy(plist);
}

void test__list_remove__list_remove_varg__empty(void** state)
{
    list_t* plist = create_list(int);
    list_init(plist);

    _list_remove(plist, 100);
    assert_true(list_size(plist) == 0);

    list_destroy(plist);
}

void test__list_remove__list_remove_varg__non_empty_no_removed(void** state)
{
    list_t* plist = create_list(int);
    list_init_n(plist, 10);

    _list_remove(plist, 100);
    assert_true(list_size(plist) == 10);

    list_destroy(plist);
}

void test__list_remove__list_remove_varg__non_empty_remove(void** state)
{
    list_iterator_t it_iter;
    size_t t_oldsize = 0;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 0);
    list_push_back(plist, 2);
    list_push_back(plist, 4);
    list_push_back(plist, 4);
    list_push_back(plist, 1);

    t_oldsize = list_size(plist);
    _list_remove(plist, 2);
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

void test__list_remove__list_remove_varg__non_empty_remove_more(void** state)
{
    list_iterator_t it_iter;
    size_t t_oldsize = 0;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 0);
    list_push_back(plist, 2);
    list_push_back(plist, 4);
    list_push_back(plist, 4);
    list_push_back(plist, 1);

    t_oldsize = list_size(plist);
    _list_remove(plist, 4);
    assert_true(list_size(plist) == t_oldsize - 2);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    list_destroy(plist);
}

void test__list_remove__list_remove_varg__non_empty_remove_more_multiple(void** state)
{
    list_iterator_t it_iter;
    size_t t_oldsize = 0;
    list_t* plist = create_list(int);

    list_init(plist);
    list_push_back(plist, 0);
    list_push_back(plist, 2);
    list_push_back(plist, 4);
    list_push_back(plist, 4);
    list_push_back(plist, 1);

    t_oldsize = list_size(plist);
    _list_remove(plist, 4, 0, 1, 2);
    assert_true(list_size(plist) == t_oldsize - 2);
    it_iter = list_begin(plist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);

    list_destroy(plist);
}

/*
 * test _list_insert_n and _list_insert_n_varg
 */
UT_CASE_DEFINATION(_list_insert_n__list_insert_n_varg)
void test__list_insert_n__list_insert_n_varg__null_list_container(void** state)
{
    list_t* plist = create_list(int);

    list_init(plist);
    expect_assert_failure(_list_insert_n(NULL, list_begin(plist), 10, 100));

    list_destroy(plist);
}

void test__list_insert_n__list_insert_n_varg__non_inited_list_container(void** state)
{
    list_t* plist = create_list(int);
    list_t* plist_list = create_list(int);

    list_init(plist_list);
    expect_assert_failure(_list_insert_n(plist, list_begin(plist_list), 10, 100));

    list_destroy(plist);
    list_destroy(plist_list);
}

void test__list_insert_n__list_insert_n_varg__invalid_pos(void** state)
{
    list_iterator_t it_pos;
    list_t* plist = create_list(int);
    list_init(plist);

    it_pos = list_begin(plist);
    it_pos._t_pos._pby_corepos = (_byte_t*)0x3849;
    expect_assert_failure(_list_insert_n(plist, it_pos, 10, 100));

    list_destroy(plist);
}

void test__list_insert_n__list_insert_n_varg__0_insert_0(void** state)
{
    list_iterator_t it_pos;
    list_iterator_t it_iter;
    size_t t_oldsize = 0;
    list_t* plist = create_list(int);
    list_init(plist);

    it_pos = list_begin(plist);
    t_oldsize = list_size(plist);
    it_iter = _list_insert_n(plist, it_pos, 0, 100);
    assert_true(list_size(plist) == t_oldsize);
    assert_true(iterator_equal(it_iter, it_pos));

    list_destroy(plist);
}

void test__list_insert_n__list_insert_n_varg__0_insert_n(void** state)
{
    list_iterator_t it_pos;
    list_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    list_t* plist = create_list(int);
    list_init(plist);

    it_pos = list_begin(plist);
    t_oldsize = list_size(plist);
    it_iter = _list_insert_n(plist, it_pos, 10, 100);
    assert_true(list_size(plist) == t_oldsize + 10);
    assert_true(iterator_equal(it_iter, list_begin(plist)));
    assert_true(iterator_equal(it_pos, list_end(plist)));
    for(it_iter = list_begin(plist), i = 0;
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    list_destroy(plist);
}

void test__list_insert_n__list_insert_n_varg__n_insert_0(void** state)
{
    list_iterator_t it_pos;
    list_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    list_t* plist = create_list(int);
    list_init_n(plist, 10);

    it_pos = list_begin(plist);
    t_oldsize = list_size(plist);
    it_iter = _list_insert_n(plist, it_pos, 0, 100);
    assert_true(list_size(plist) == t_oldsize);
    assert_true(iterator_equal(it_iter, list_begin(plist)));
    assert_true(iterator_equal(it_pos, list_begin(plist)));
    for(it_iter = list_begin(plist), i = 0;
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    list_destroy(plist);
}

void test__list_insert_n__list_insert_n_varg__n_insert_begin(void** state)
{
    list_iterator_t it_pos;
    list_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    list_t* plist = create_list(int);
    list_init_n(plist, 10);

    it_pos = list_begin(plist);
    t_oldsize = list_size(plist);
    it_iter = _list_insert_n(plist, it_pos, 10, 100);
    assert_true(list_size(plist) == t_oldsize + 10);
    assert_true(iterator_equal(it_iter, list_begin(plist)));
    assert_true(iterator_equal(it_pos, iterator_advance(list_begin(plist), 10)));
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

void test__list_insert_n__list_insert_n_varg__n_insert_middle(void** state)
{
    list_iterator_t it_pos;
    list_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    list_t* plist = create_list(int);
    list_init_n(plist, 10);

    it_pos = iterator_advance(list_begin(plist), 3);
    t_oldsize = list_size(plist);
    it_iter = _list_insert_n(plist, it_pos, 10, 100);
    assert_true(list_size(plist) == t_oldsize + 10);
    assert_true(iterator_equal(it_iter, iterator_advance(list_begin(plist), 3)));
    assert_true(iterator_equal(it_pos, iterator_advance(list_begin(plist), 13)));
    for(it_iter = list_begin(plist), i = 0;
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter), ++i)
    {
        if(i > 2 && i < 13)
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

void test__list_insert_n__list_insert_n_varg__n_insert_end(void** state)
{
    list_iterator_t it_pos;
    list_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    list_t* plist = create_list(int);
    list_init_n(plist, 10);

    it_pos = list_end(plist);
    t_oldsize = list_size(plist);
    it_iter = _list_insert_n(plist, it_pos, 10, 100);
    assert_true(list_size(plist) == t_oldsize + 10);
    assert_true(iterator_equal(it_iter, iterator_advance(list_end(plist), -10)));
    assert_true(iterator_equal(it_pos, list_end(plist)));
    for(it_iter = list_begin(plist), i = 0;
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter), ++i)
    {
        if(i > 9)
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

void test__list_insert_n__list_insert_n_varg__n_insert_end_multiple(void** state)
{
    list_iterator_t it_pos;
    list_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    list_t* plist = create_list(int);
    list_init_n(plist, 10);

    it_pos = list_end(plist);
    t_oldsize = list_size(plist);
    it_iter = _list_insert_n(plist, it_pos, 10, 100, 9888, 8374, 23523);
    assert_true(list_size(plist) == t_oldsize + 10);
    assert_true(iterator_equal(it_iter, iterator_advance(list_end(plist), -10)));
    assert_true(iterator_equal(it_pos, list_end(plist)));
    for(it_iter = list_begin(plist), i = 0;
        !iterator_equal(it_iter, list_end(plist));
        it_iter = iterator_next(it_iter), ++i)
    {
        if(i > 9)
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
 * test _list_init_elem_auxiliary
 */
UT_CASE_DEFINATION(_list_init_elem_auxiliary)
void test__list_init_elem_auxiliary__null_list_container(void** state)
{
    int elem = 0;
    expect_assert_failure(_list_init_elem_auxiliary(NULL, &elem));
}

void test__list_init_elem_auxiliary__null_elem(void** state)
{
    list_t* plist = create_list(int);

    expect_assert_failure(_list_init_elem_auxiliary(plist, NULL));

    list_destroy(plist);
}

void test__list_init_elem_auxiliary__non_inited_list(void** state)
{
    int elem = 0;
    list_t* plist = create_list(int);

    list_init(plist);
    plist->_pt_node->_pt_next = NULL;
    expect_assert_failure(_list_init_elem_auxiliary(plist, &elem));

    plist->_pt_node->_pt_next = plist->_pt_node;
    list_destroy(plist);
}

void test__list_init_elem_auxiliary__successfully_int(void** state)
{
    int elem = 100;
    list_t* plist = create_list(int);
    list_init(plist);

    _list_init_elem_auxiliary(plist, &elem);
    assert_true(elem == 0);

    list_destroy(plist);
}

void test__list_init_elem_auxiliary__successfully_cstr(void** state)
{
    string_t elem;
    list_t* plist = create_list(char*);
    list_init_elem(plist, 10, "abcdefg");

    _list_init_elem_auxiliary(plist, &elem);
    assert_true(strcmp(string_c_str(&elem), "") == 0);

    _string_destroy_auxiliary(&elem);
    list_destroy(plist);
}

void test__list_init_elem_auxiliary__successfully_iterator(void** state)
{
    iterator_t it_iter = _create_list_iterator();
    list_t* plist = create_list(iterator_t);
    list_init_elem(plist, 10, &it_iter);

    _list_init_elem_auxiliary(plist, plist->_pt_node->_pt_next->_pby_data);
    memset(&it_iter, 0x00, sizeof(iterator_t));
    assert_true(memcmp((iterator_t*)list_front(plist), &it_iter, sizeof(iterator_t)) == 0);

    list_destroy(plist);
}

void test__list_init_elem_auxiliary__successfully_container(void** state)
{
    list_t list;
    list_t* plist = create_list(list_t<int>);

    _list_init_elem_auxiliary(plist, &list);
    assert_true(_list_is_inited(&list));

    list_destroy(plist);
    _list_destroy_auxiliary(&list);
}

typedef struct _tag_test__list_init_elem_auxiliary__successfully_user_defined
{
    int n_elem;
}_test__list_init_elem_auxiliary__successfully_user_defined_t;

void test__list_init_elem_auxiliary__successfully_user_defined(void** stat)
{
    _test__list_init_elem_auxiliary__successfully_user_defined_t t_user;
    list_t* plist = NULL;

    type_register(_test__list_init_elem_auxiliary__successfully_user_defined_t, NULL, NULL, NULL, NULL);
    plist = create_list(_test__list_init_elem_auxiliary__successfully_user_defined_t);
    t_user.n_elem = 100;
    _list_init_elem_auxiliary(plist, &t_user);
    assert_true(t_user.n_elem == 0);

    list_destroy(plist);
}
