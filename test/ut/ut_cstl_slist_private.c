#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/cstl_slist_iterator.h"
#include "cstl/cslist.h"
#include "cstl/cvector.h"
#include "cstl_slist_aux.h"
#include "cstl/cstring.h"

#include "ut_def.h"
#include "ut_cstl_slist_private.h"

UT_SUIT_DEFINATION(cstl_slist_private, _create_slist);

/*
 * test _create_slist
 */
UT_CASE_DEFINATION(_create_slist)
void test__create_slist__null_typename(void** state)
{
    expect_assert_failure(_create_slist(NULL));
}

void test__create_slist__unregisted_type(void** state)
{
    assert_true(_create_slist("_test__create_slist__unregisted_type_t") == NULL);
}

void test__create_slist__c_builtin_type(void** state)
{
    slist_t* pslist = _create_slist("unsigned int");
    assert_true(pslist != NULL);
    assert_true(strcmp(_GET_SLIST_TYPE_NAME(pslist), "unsigned int") == 0);
    assert_true(_slist_is_created(pslist));

    slist_destroy(pslist);
}

void test__create_slist__libcstl_builtin_type(void** state)
{
    slist_t* pslist = _create_slist("vector_t         <      int>     ");
    assert_true(pslist != NULL);
    assert_true(strcmp(_GET_SLIST_TYPE_NAME(pslist), "vector_t<int>") == 0);
    assert_true(_slist_is_created(pslist));

    slist_destroy(pslist);
}

typedef struct _tag_test__create_slist__user_defined_type
{
    int n_elem;
}_test__create_slist__user_defined_type_t;

void test__create_slist__user_defined_type(void** state)
{
    slist_t* pslist = NULL;

    type_register(struct _tag_test__create_slist__user_defined_type, NULL, NULL, NULL, NULL);
    pslist = _create_slist("struct      _tag_test__create_slist__user_defined_type");
    assert_true(pslist != NULL);
    assert_true(strcmp(_GET_SLIST_TYPE_NAME(pslist), "struct _tag_test__create_slist__user_defined_type") == 0);
    assert_true(_slist_is_created(pslist));

    slist_destroy(pslist);
}

void test__create_slist__user_defined_type_dup(void** state)
{
    slist_t* pslist = NULL;

    type_duplicate(struct _tag_test__create_slist__user_defined_type, _test__create_slist__user_defined_type_t);
    pslist = _create_slist("_test__create_slist__user_defined_type_t");
    assert_true(pslist != NULL);
    assert_true(strcmp(_GET_SLIST_TYPE_NAME(pslist), "_test__create_slist__user_defined_type_t") == 0);
    assert_true(_slist_is_created(pslist));

    slist_destroy(pslist);
}

/*
 * test _create_slist_auxiliary
 */
UT_CASE_DEFINATION(_create_slist_auxiliary)
void test__create_slist_auxiliary__null_slist_container(void** state)
{
    expect_assert_failure(_create_slist_auxiliary(NULL, "int"));
}

void test__create_slist_auxiliary__null_typename(void** state)
{
    slist_t* pslist = malloc(sizeof(slist_t));
    expect_assert_failure(_create_slist_auxiliary(pslist, NULL));

    free(pslist);
}

void test__create_slist_auxiliary__unregisted_type(void** state)
{
    slist_t* pslist = malloc(sizeof(slist_t));
    assert_false(_create_slist_auxiliary(pslist, "_test__create_slist_auxiliary__unregisted_type_t"));

    free(pslist);
}

void test__create_slist_auxiliary__c_builtin(void** state)
{
    slist_t* pslist = malloc(sizeof(slist_t));
    assert_true(_create_slist_auxiliary(pslist, "double"));
    assert_true(strcmp(_GET_SLIST_TYPE_NAME(pslist), "double") == 0);
    assert_true(_slist_is_created(pslist));

    slist_destroy(pslist);
}

void test__create_slist_auxiliary__libcstl_builtin(void** state)
{
    slist_t* pslist = malloc(sizeof(slist_t));
    assert_true(_create_slist_auxiliary(pslist, "slist_t<   vector_t     <     string_t>>       "));
    assert_true(strcmp(_GET_SLIST_TYPE_NAME(pslist), "slist_t<vector_t<string_t>>") == 0);
    assert_true(_slist_is_created(pslist));

    slist_destroy(pslist);
}

typedef struct _tag_test__create_slist_auxiliary__user_defined
{
    int n_elem;
}_test__create_slist_auxiliary__user_defined_t;
void test__create_slist_auxiliary__user_defined(void** state)
{
    slist_t* pslist = NULL;
    type_register(struct _tag_test__create_slist_auxiliary__user_defined, NULL, NULL, NULL, NULL);
    pslist = malloc(sizeof(slist_t));
    assert_true(_create_slist_auxiliary(pslist, "struct _tag_test__create_slist_auxiliary__user_defined"));
    assert_true(strcmp(_GET_SLIST_TYPE_NAME(pslist), "struct _tag_test__create_slist_auxiliary__user_defined") == 0);
    assert_true(_slist_is_created(pslist));

    slist_destroy(pslist);
}

void test__create_slist_auxiliary__user_defined_dup(void** state)
{
    slist_t* pslist = NULL;
    type_duplicate(struct _tag_test__create_slist_auxiliary__user_defined, _test__create_slist_auxiliary__user_defined_t);
    pslist = malloc(sizeof(slist_t));
    assert_true(_create_slist_auxiliary(pslist, "_test__create_slist_auxiliary__user_defined_t"));
    assert_true(strcmp(_GET_SLIST_TYPE_NAME(pslist), "_test__create_slist_auxiliary__user_defined_t") == 0);
    assert_true(_slist_is_created(pslist));

    slist_destroy(pslist);
}

/*
 * test _slist_init_elem and _slist_init_elem_varg
 */
UT_CASE_DEFINATION(_slist_init_elem__slist_init_elem_varg)
void test__slist_init_elem__slist_init_elem_varg__null_slist_container(void** state)
{
    expect_assert_failure(_slist_init_elem(NULL, 10, 100));
}

void test__slist_init_elem__slist_init_elem_varg__non_created_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    pslist->_t_head._pt_next = (_slistnode_t*)0x88;
    expect_assert_failure(_slist_init_elem(pslist, 10, 100));

    pslist->_t_head._pt_next = NULL;
    slist_destroy(pslist);
}

void test__slist_init_elem__slist_init_elem_varg__0_count(void** state)
{
    slist_t* pslist = create_slist(int);

    _slist_init_elem(pslist, 0, 100);
    assert_true(slist_size(pslist) == 0);
    assert_true(_slist_is_inited(pslist));

    slist_destroy(pslist);
}

void test__slist_init_elem__slist_init_elem_varg__count(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    _slist_init_elem(pslist, 10, 100);
    assert_true(slist_size(pslist) == 10);
    assert_true(_slist_is_inited(pslist));
    for(it_iter = slist_begin(pslist);
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    slist_destroy(pslist);
}

void test__slist_init_elem__slist_init_elem_varg__multiple_elem(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    _slist_init_elem(pslist, 10, 100, 3940, 23342, -284);
    assert_true(slist_size(pslist) == 10);
    assert_true(_slist_is_inited(pslist));
    for(it_iter = slist_begin(pslist);
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    slist_destroy(pslist);
}

/*
 * test _slist_destroy_auxiliary
 */
UT_CASE_DEFINATION(_slist_destroy_auxiliary)
void test__slist_destroy_auxiliary__null_slist_container(void** state)
{
    expect_assert_failure(_slist_destroy_auxiliary(NULL));
}

void test__slist_destroy_auxiliary__non_created_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    pslist->_t_typeinfo._t_style = 9484;
    expect_assert_failure(_slist_destroy_auxiliary(pslist));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test__slist_destroy_auxiliary__non_inited(void** state)
{
    slist_t* pslist = create_slist(int);
    _slist_destroy_auxiliary(pslist);
    assert_true(pslist->_t_head._pt_next == NULL);

    free(pslist);
}

void test__slist_destroy_auxiliary__empty(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    _slist_destroy_auxiliary(pslist);
    assert_true(pslist->_t_head._pt_next == NULL);

    free(pslist);
}

void test__slist_destroy_auxiliary__non_empty(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    assert_true(slist_size(pslist) == 10);
    _slist_destroy_auxiliary(pslist);
    assert_true(pslist->_t_head._pt_next == NULL);

    free(pslist);
}

/*
 * test _slist_assign_elem and _slist_assign_elem_varg
 */
UT_CASE_DEFINATION(_slist_assign_elem__slist_assign_elem_varg)
void test__slist_assign_elem__slist_assign_elem_varg__null_slist_container(void** state)
{
    expect_assert_failure(_slist_assign_elem(NULL, 10, 100));
}

void test__slist_assign_elem__slist_assign_elem_varg__non_inited_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    pslist->_t_typeinfo._t_style = 4556;
    expect_assert_failure(_slist_assign_elem(pslist, 10, 100));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test__slist_assign_elem__slist_assign_elem_varg__0_assign_0(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    assert_true(slist_size(pslist) == 0);
    _slist_assign_elem(pslist, 0, 100);
    assert_true(slist_size(pslist) == 0);

    slist_destroy(pslist);
}

void test__slist_assign_elem__slist_assign_elem_varg__0_assign_n(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    assert_true(slist_size(pslist) == 0);
    _slist_assign_elem(pslist, 10, 100);
    assert_true(slist_size(pslist) == 10);
    for(it_iter = slist_begin(pslist);
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    slist_destroy(pslist);
}

void test__slist_assign_elem__slist_assign_elem_varg__n_assign_0(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    assert_true(slist_size(pslist) == 10);
    for(it_iter = slist_begin(pslist);
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }
    _slist_assign_elem(pslist, 0, 100);
    assert_true(slist_size(pslist) == 0);

    slist_destroy(pslist);
}

void test__slist_assign_elem__slist_assign_elem_varg__n_assign_m_n_greater_than_m(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    assert_true(slist_size(pslist) == 10);
    for(it_iter = slist_begin(pslist);
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }
    _slist_assign_elem(pslist, 4, 100);
    assert_true(slist_size(pslist) == 4);
    for(it_iter = slist_begin(pslist);
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    slist_destroy(pslist);
}

void test__slist_assign_elem__slist_assign_elem_varg__n_assign_m_n_equal_to_m(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    assert_true(slist_size(pslist) == 10);
    for(it_iter = slist_begin(pslist);
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }
    _slist_assign_elem(pslist, 10, 100);
    assert_true(slist_size(pslist) == 10);
    for(it_iter = slist_begin(pslist);
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    slist_destroy(pslist);
}

void test__slist_assign_elem__slist_assign_elem_varg__n_assign_m_n_less_than_m(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    assert_true(slist_size(pslist) == 10);
    for(it_iter = slist_begin(pslist);
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }
    _slist_assign_elem(pslist, 18, 100);
    assert_true(slist_size(pslist) == 18);
    for(it_iter = slist_begin(pslist);
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    slist_destroy(pslist);
}

void test__slist_assign_elem__slist_assign_elem_varg__n_assign_m_n_less_than_m_multiple(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    assert_true(slist_size(pslist) == 10);
    for(it_iter = slist_begin(pslist);
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }
    _slist_assign_elem(pslist, 18, 100, 2983, 2445, 2222);
    assert_true(slist_size(pslist) == 18);
    for(it_iter = slist_begin(pslist);
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    slist_destroy(pslist);
}

/*
 * test _slist_push_front and _slist_push_front_varg
 */
UT_CASE_DEFINATION(_slist_push_front__slist_push_front_varg)
void test__slist_push_front__slist_push_front_varg__null_slist_container(void** state)
{
    expect_assert_failure(_slist_push_front(NULL, 100));
}

void test__slist_push_front__slist_push_front_varg__non_inited_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    pslist->_t_typeinfo._t_style = 4444;
    expect_assert_failure(_slist_push_front(pslist, 100));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test__slist_push_front__slist_push_front_varg__empty(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    _slist_push_front(pslist, 100);
    assert_true(slist_size(pslist) == 1);
    assert_true(*(int*)slist_front(pslist) == 100);

    slist_destroy(pslist);
}

void test__slist_push_front__slist_push_front_varg__non_empty(void** state)
{
    slist_t* pslist = create_slist(int);
    size_t t_oldsize = 0;

    slist_init_n(pslist, 10);
    t_oldsize = slist_size(pslist);
    _slist_push_front(pslist, 100);
    assert_true(slist_size(pslist) == t_oldsize + 1);
    assert_true(*(int*)slist_front(pslist) == 100);

    slist_destroy(pslist);
}

void test__slist_push_front__slist_push_front_varg__non_empty_multiple(void** state)
{
    slist_t* pslist = create_slist(int);
    size_t t_oldsize = 0;

    slist_init_n(pslist, 10);
    t_oldsize = slist_size(pslist);
    _slist_push_front(pslist, 100, 98, 23523, 2222);
    assert_true(slist_size(pslist) == t_oldsize + 1);
    assert_true(*(int*)slist_front(pslist) == 100);

    slist_destroy(pslist);
}

/*
 * test _slist_resize_elem and _slist_resize_elem_varg
 */
UT_CASE_DEFINATION(_slist_resize_elem__slist_resize_elem_varg)
void test__slist_resize_elem__slist_resize_elem_varg__null_slist_container(void** state)
{
    expect_assert_failure(_slist_resize_elem(NULL, 10, 100));
}

void test__slist_resize_elem__slist_resize_elem_varg__non_inited_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    pslist->_t_typeinfo._t_style = 33243;
    expect_assert_failure(_slist_resize_elem(pslist, 10, 100));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test__slist_resize_elem__slist_resize_elem_varg__0_resize_0(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    _slist_resize_elem(pslist, 0, 100);
    assert_true(slist_size(pslist) == 0);

    slist_destroy(pslist);
}

void test__slist_resize_elem__slist_resize_elem_varg__0_resize_n(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    _slist_resize_elem(pslist, 10, 100);
    assert_true(slist_size(pslist) == 10);
    for(it_iter = slist_begin(pslist);
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    slist_destroy(pslist);
}

void test__slist_resize_elem__slist_resize_elem_varg__n_resize_0(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    _slist_resize_elem(pslist, 0, 100);
    assert_true(slist_size(pslist) == 0);

    slist_destroy(pslist);
}

void test__slist_resize_elem__slist_resize_elem_varg__n_resize_m_n_greater_than_m(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    _slist_resize_elem(pslist, 4, 100);
    assert_true(slist_size(pslist) == 4);
    for(it_iter = slist_begin(pslist);
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist);
}

void test__slist_resize_elem__slist_resize_elem_varg__n_resize_m_n_equal_to_m(void** state)
{
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    _slist_resize_elem(pslist, 10, 100);
    assert_true(slist_size(pslist) == 10);
    for(it_iter = slist_begin(pslist);
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist);
}

void test__slist_resize_elem__slist_resize_elem_varg__n_resize_m_n_less_than_m(void** state)
{
    size_t i = 0;
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    _slist_resize_elem(pslist, 16, 100);
    assert_true(slist_size(pslist) == 16);
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
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

    slist_destroy(pslist);
}

void test__slist_resize_elem__slist_resize_elem_varg__n_resize_m_n_less_than_m_multiple(void** state)
{
    size_t i = 0;
    slist_iterator_t it_iter;
    slist_t* pslist = create_slist(int);

    slist_init_n(pslist, 10);
    _slist_resize_elem(pslist, 16, 100, 0, 28348, 274984);
    assert_true(slist_size(pslist) == 16);
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
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

    slist_destroy(pslist);
}

/*
 * test _slist_remove and _slist_remove_varg
 */
UT_CASE_DEFINATION(_slist_remove__slist_remove_varg)
void test__slist_remove__slist_remove_varg__null_slist_container(void** state)
{
    expect_assert_failure(_slist_remove(NULL, 99));
}

void test__slist_remove__slist_remove_varg__non_inited_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    pslist->_t_typeinfo._t_style = 434234;
    expect_assert_failure(_slist_remove(pslist, 99));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test__slist_remove__slist_remove_varg__empty(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    _slist_remove(pslist, 100);
    assert_true(slist_size(pslist) == 0);

    slist_destroy(pslist);
}

void test__slist_remove__slist_remove_varg__non_empty_no_removed(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    _slist_remove(pslist, 100);
    assert_true(slist_size(pslist) == 10);

    slist_destroy(pslist);
}

void test__slist_remove__slist_remove_varg__non_empty_remove(void** state)
{
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 2);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 1);

    t_oldsize = slist_size(pslist);
    _slist_remove(pslist, 2);
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

void test__slist_remove__slist_remove_varg__non_empty_remove_more(void** state)
{
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 2);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 1);

    t_oldsize = slist_size(pslist);
    _slist_remove(pslist, 4);
    assert_true(slist_size(pslist) == t_oldsize - 2);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    slist_destroy(pslist);
}

void test__slist_remove__slist_remove_varg__non_empty_remove_more_multiple(void** state)
{
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    slist_push_front(pslist, 0);
    slist_push_front(pslist, 2);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 4);
    slist_push_front(pslist, 1);

    t_oldsize = slist_size(pslist);
    _slist_remove(pslist, 4, 0, 1, 2);
    assert_true(slist_size(pslist) == t_oldsize - 2);
    it_iter = slist_begin(pslist);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 1);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 2);
    it_iter = iterator_next(it_iter);
    assert_true(*(int*)iterator_get_pointer(it_iter) == 0);

    slist_destroy(pslist);
}

/*
 * test _slist_init_elem_auxiliary
 */
UT_CASE_DEFINATION(_slist_init_elem_auxiliary)
void test__slist_init_elem_auxiliary__null_slist_container(void** state)
{
    int elem = 0;
    expect_assert_failure(_slist_init_elem_auxiliary(NULL, &elem));
}

void test__slist_init_elem_auxiliary__null_elem(void** state)
{
    slist_t* pslist = create_slist(int);

    expect_assert_failure(_slist_init_elem_auxiliary(pslist, NULL));

    slist_destroy(pslist);
}

void test__slist_init_elem_auxiliary__non_inited_slist(void** state)
{
    int elem = 0;
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    pslist->_t_typeinfo._t_style = 234213;
    expect_assert_failure(_slist_init_elem_auxiliary(pslist, &elem));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
}

void test__slist_init_elem_auxiliary__successfully_int(void** state)
{
    int elem = 100;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    _slist_init_elem_auxiliary(pslist, &elem);
    assert_true(elem == 0);

    slist_destroy(pslist);
}

void test__slist_init_elem_auxiliary__successfully_cstr(void** state)
{
    string_t elem;
    slist_t* pslist = create_slist(char*);
    slist_init_elem(pslist, 10, "abcdefg");

    _slist_init_elem_auxiliary(pslist, &elem);
    assert_true(strcmp(string_c_str(&elem), "") == 0);

    _string_destroy_auxiliary(&elem);
    slist_destroy(pslist);
}

void test__slist_init_elem_auxiliary__successfully_iterator(void** state)
{
    iterator_t it_iter = _create_slist_iterator();
    slist_t* pslist = create_slist(iterator_t);
    slist_init_elem(pslist, 10, &it_iter);

    _slist_init_elem_auxiliary(pslist, pslist->_t_head._pt_next->_pby_data);
    memset(&it_iter, 0x00, sizeof(iterator_t));
    assert_true(memcmp((iterator_t*)slist_front(pslist), &it_iter, sizeof(iterator_t)) == 0);

    slist_destroy(pslist);
}

void test__slist_init_elem_auxiliary__successfully_container(void** state)
{
    slist_t slist;
    slist_t* pslist = create_slist(slist_t<int>);

    _slist_init_elem_auxiliary(pslist, &slist);
    assert_true(_slist_is_inited(&slist));

    slist_destroy(pslist);
}

typedef struct _tag_test__slist_init_elem_auxiliary__successfully_user_defined
{
    int n_elem;
}_test__slist_init_elem_auxiliary__successfully_user_defined_t;

void test__slist_init_elem_auxiliary__successfully_user_defined(void** stat)
{
    _test__slist_init_elem_auxiliary__successfully_user_defined_t t_user;
    slist_t* pslist = NULL;

    type_register(_test__slist_init_elem_auxiliary__successfully_user_defined_t, NULL, NULL, NULL, NULL);
    pslist = create_slist(_test__slist_init_elem_auxiliary__successfully_user_defined_t);
    t_user.n_elem = 100;
    _slist_init_elem_auxiliary(pslist, &t_user);
    assert_true(t_user.n_elem == 0);

    slist_destroy(pslist);
}

/*
 * test _slist_insert
 */
UT_CASE_DEFINATION(_slist_insert)
void test__slist_insert__null_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    expect_assert_failure(_slist_insert(NULL, slist_begin(pslist), 100));

    slist_destroy(pslist);
}

void test__slist_insert__non_inited_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_t* pslist_slist = create_slist(int);

    slist_init(pslist_slist);
    pslist->_t_typeinfo._t_style = 2222;
    expect_assert_failure(_slist_insert(pslist, slist_begin(pslist_slist), 10));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
    slist_destroy(pslist_slist);
}

void test__slist_insert__invalid_pos(void** state)
{
    slist_iterator_t it_pos;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    it_pos = slist_begin(pslist);
    it_pos._t_pos._pby_corepos = (_byte_t*)0x3849;
    expect_assert_failure(_slist_insert(pslist, it_pos, 100));

    slist_destroy(pslist);
}

void test__slist_insert__empty_insert(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    it_pos = slist_begin(pslist);
    t_oldsize = slist_size(pslist);
    it_iter = _slist_insert(pslist, it_pos, 100);
    assert_true(slist_size(pslist) == t_oldsize + 1);
    assert_true(iterator_equal(it_iter, slist_begin(pslist)));
    assert_true(iterator_equal(it_pos, slist_end(pslist)));
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    slist_destroy(pslist);
}

void test__slist_insert__n_insert_begin(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    it_pos = slist_begin(pslist);
    t_oldsize = slist_size(pslist);
    it_iter = _slist_insert(pslist, it_pos, 100);
    assert_true(slist_size(pslist) == t_oldsize + 1);
    assert_true(iterator_equal(it_iter, slist_begin(pslist)));
    assert_true(iterator_equal(it_pos, iterator_advance(slist_begin(pslist), 1)));
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        if(i < 1)
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

void test__slist_insert__n_insert_middle(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    it_pos = iterator_advance(slist_begin(pslist), 3);
    t_oldsize = slist_size(pslist);
    it_iter = _slist_insert(pslist, it_pos, 100);
    assert_true(slist_size(pslist) == t_oldsize + 1);
    assert_true(iterator_equal(it_iter, iterator_advance(slist_begin(pslist), 3)));
    assert_true(iterator_equal(it_pos, iterator_advance(slist_begin(pslist), 4)));
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        if(i > 2 && i < 4)
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

void test__slist_insert__n_insert_end(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    it_pos = slist_end(pslist);
    t_oldsize = slist_size(pslist);
    it_iter = _slist_insert(pslist, it_pos, 100);
    assert_true(slist_size(pslist) == t_oldsize + 1);
    assert_true(iterator_equal(it_iter, slist_previous(pslist, slist_end(pslist))));
    assert_true(iterator_equal(it_pos, slist_end(pslist)));
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
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

    slist_destroy(pslist);
}

void test__slist_insert__n_insert_end_multiple(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    it_pos = slist_end(pslist);
    t_oldsize = slist_size(pslist);
    it_iter = _slist_insert(pslist, it_pos, 100, 9888, 8374, 23523);
    assert_true(slist_size(pslist) == t_oldsize + 1);
    assert_true(iterator_equal(it_iter, slist_previous(pslist, slist_end(pslist))));
    assert_true(iterator_equal(it_pos, slist_end(pslist)));
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
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

    slist_destroy(pslist);
}

/*
 * test _slist_insert_n
 */
UT_CASE_DEFINATION(_slist_insert_n)
void test__slist_insert_n__null_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    expect_assert_failure(_slist_insert_n(NULL, slist_begin(pslist), 10, 100));

    slist_destroy(pslist);
}

void test__slist_insert_n__non_inited_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_t* pslist_slist = create_slist(int);

    slist_init(pslist_slist);
    pslist->_t_typeinfo._t_style = 9877;
    expect_assert_failure(_slist_insert_n(pslist, slist_begin(pslist_slist), 10, 100));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
    slist_destroy(pslist_slist);
}

void test__slist_insert_n__invalid_pos(void** state)
{
    slist_iterator_t it_pos;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    it_pos = slist_begin(pslist);
    it_pos._t_pos._pby_corepos = (_byte_t*)0x3849;
    expect_assert_failure(_slist_insert_n(pslist, it_pos, 10, 100));

    slist_destroy(pslist);
}

void test__slist_insert_n__0_insert_0(void** state)
{
    slist_iterator_t it_pos;
    size_t t_oldsize = 0;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    it_pos = slist_begin(pslist);
    t_oldsize = slist_size(pslist);
    _slist_insert_n(pslist, it_pos, 0, 100);
    assert_true(slist_size(pslist) == t_oldsize);

    slist_destroy(pslist);
}

void test__slist_insert_n__0_insert_n(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    it_pos = slist_begin(pslist);
    t_oldsize = slist_size(pslist);
    _slist_insert_n(pslist, it_pos, 10, 100);
    assert_true(slist_size(pslist) == t_oldsize + 10);
    assert_true(iterator_equal(it_pos, slist_end(pslist)));
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    slist_destroy(pslist);
}

void test__slist_insert_n__n_insert_0(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    it_pos = slist_begin(pslist);
    t_oldsize = slist_size(pslist);
    _slist_insert_n(pslist, it_pos, 0, 100);
    assert_true(slist_size(pslist) == t_oldsize);
    assert_true(iterator_equal(it_pos, slist_begin(pslist)));
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist);
}

void test__slist_insert_n__n_insert_begin(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    it_pos = slist_begin(pslist);
    t_oldsize = slist_size(pslist);
    _slist_insert_n(pslist, it_pos, 10, 100);
    assert_true(slist_size(pslist) == t_oldsize + 10);
    assert_true(iterator_equal(it_pos, iterator_advance(slist_begin(pslist), 10)));
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

void test__slist_insert_n__n_insert_middle(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    it_pos = iterator_advance(slist_begin(pslist), 3);
    t_oldsize = slist_size(pslist);
    _slist_insert_n(pslist, it_pos, 10, 100);
    assert_true(slist_size(pslist) == t_oldsize + 10);
    assert_true(iterator_equal(it_pos, iterator_advance(slist_begin(pslist), 13)));
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
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

    slist_destroy(pslist);
}

void test__slist_insert_n__n_insert_end(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    it_pos = slist_end(pslist);
    t_oldsize = slist_size(pslist);
    _slist_insert_n(pslist, it_pos, 10, 100);
    assert_true(slist_size(pslist) == t_oldsize + 10);
    assert_true(iterator_equal(it_pos, slist_end(pslist)));
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
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

    slist_destroy(pslist);
}

void test__slist_insert_n__n_insert_end_multiple(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    it_pos = slist_end(pslist);
    t_oldsize = slist_size(pslist);
    _slist_insert_n(pslist, it_pos, 10, 100, 9888, 8374, 23523);
    assert_true(slist_size(pslist) == t_oldsize + 10);
    assert_true(iterator_equal(it_pos, slist_end(pslist)));
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
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

    slist_destroy(pslist);
}

/*
 * test _slist_insert_after
 */
UT_CASE_DEFINATION(_slist_insert_after)
void test__slist_insert_after__null_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    expect_assert_failure(_slist_insert_after(NULL, slist_begin(pslist), 100));

    slist_destroy(pslist);
}

void test__slist_insert_after__non_inited_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_t* pslist_slist = create_slist(int);

    slist_init(pslist_slist);
    pslist->_t_typeinfo._t_style = 24355;
    expect_assert_failure(_slist_insert_after(pslist, slist_begin(pslist_slist), 10));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
    slist_destroy(pslist_slist);
}

void test__slist_insert_after__invalid_pos(void** state)
{
    slist_iterator_t it_pos;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    it_pos = slist_begin(pslist);
    it_pos._t_pos._pby_corepos = (_byte_t*)0x3849;
    expect_assert_failure(_slist_insert_after(pslist, it_pos, 100));

    slist_destroy(pslist);
}

void test__slist_insert_after__invalid_pos_end(void** state)
{
    slist_iterator_t it_pos;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    it_pos = slist_end(pslist);
    expect_assert_failure(_slist_insert_after(pslist, it_pos, 100));

    slist_destroy(pslist);
}

void test__slist_insert_after__empty_insert(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 1);

    it_pos = slist_begin(pslist);
    t_oldsize = slist_size(pslist);
    it_iter = _slist_insert_after(pslist, it_pos, 100);
    assert_true(slist_size(pslist) == t_oldsize + 1);
    assert_true(iterator_equal(it_iter, iterator_next(slist_begin(pslist))));
    assert_true(iterator_equal(it_pos, slist_begin(pslist)));
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        if(i > 0)
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

void test__slist_insert_after__n_insert_begin(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    it_pos = slist_begin(pslist);
    t_oldsize = slist_size(pslist);
    it_iter = _slist_insert_after(pslist, it_pos, 100);
    assert_true(slist_size(pslist) == t_oldsize + 1);
    assert_true(iterator_equal(it_iter, iterator_next(slist_begin(pslist))));
    assert_true(iterator_equal(it_pos, slist_begin(pslist)));
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        if(i == 1)
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

void test__slist_insert_after__n_insert_middle(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    it_pos = iterator_advance(slist_begin(pslist), 3);
    t_oldsize = slist_size(pslist);
    it_iter = _slist_insert_after(pslist, it_pos, 100);
    assert_true(slist_size(pslist) == t_oldsize + 1);
    assert_true(iterator_equal(it_iter, iterator_advance(slist_begin(pslist), 4)));
    assert_true(iterator_equal(it_pos, iterator_advance(slist_begin(pslist), 3)));
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        if(i == 4)
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

void test__slist_insert_after__n_insert_end(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    it_pos = slist_previous(pslist, slist_end(pslist));
    t_oldsize = slist_size(pslist);
    it_iter = _slist_insert_after(pslist, it_pos, 100);
    assert_true(slist_size(pslist) == t_oldsize + 1);
    assert_true(iterator_equal(it_iter, slist_previous(pslist, slist_end(pslist))));
    assert_true(iterator_equal(it_pos, iterator_advance(slist_begin(pslist), 9)));
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
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

    slist_destroy(pslist);
}

void test__slist_insert_after__n_insert_end_multiple(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    it_pos = slist_previous(pslist, slist_end(pslist));
    t_oldsize = slist_size(pslist);
    it_iter = _slist_insert_after(pslist, it_pos, 100, 9888, 8374, 23523);
    assert_true(slist_size(pslist) == t_oldsize + 1);
    assert_true(iterator_equal(it_iter, slist_previous(pslist, slist_end(pslist))));
    assert_true(iterator_equal(it_pos, iterator_advance(slist_begin(pslist), 9)));
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
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

    slist_destroy(pslist);
}

/*
 * test _slist_insert_after_n and _slist_insert_after_n_varg
 */
UT_CASE_DEFINATION(_slist_insert_after_n__slist_insert_after_n_varg)
void test__slist_insert_after_n__slist_insert_after_n_varg__null_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);

    slist_init(pslist);
    expect_assert_failure(_slist_insert_after_n(NULL, slist_begin(pslist), 10, 100));

    slist_destroy(pslist);
}

void test__slist_insert_after_n__slist_insert_after_n_varg__non_inited_slist_container(void** state)
{
    slist_t* pslist = create_slist(int);
    slist_t* pslist_slist = create_slist(int);

    slist_init(pslist_slist);
    pslist->_t_typeinfo._t_style = 9877;
    expect_assert_failure(_slist_insert_after_n(pslist, slist_begin(pslist_slist), 10, 100));

    pslist->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    slist_destroy(pslist);
    slist_destroy(pslist_slist);
}

void test__slist_insert_after_n__slist_insert_after_n_varg__invalid_pos(void** state)
{
    slist_iterator_t it_pos;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    it_pos = slist_begin(pslist);
    it_pos._t_pos._pby_corepos = (_byte_t*)0x3849;
    expect_assert_failure(_slist_insert_after_n(pslist, it_pos, 10, 100));

    slist_destroy(pslist);
}

void test__slist_insert_after_n__slist_insert_after_n_varg__invalid_pos_end(void** state)
{
    slist_iterator_t it_pos;
    slist_t* pslist = create_slist(int);
    slist_init(pslist);

    it_pos = slist_end(pslist);
    expect_assert_failure(_slist_insert_after_n(pslist, it_pos, 10, 100));

    slist_destroy(pslist);
}

void test__slist_insert_after_n__slist_insert_after_n_varg__n_insert_0(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    it_pos = slist_begin(pslist);
    t_oldsize = slist_size(pslist);
    _slist_insert_after_n(pslist, it_pos, 0, 100);
    assert_true(slist_size(pslist) == t_oldsize);
    assert_true(iterator_equal(it_pos, slist_begin(pslist)));
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    slist_destroy(pslist);
}

void test__slist_insert_after_n__slist_insert_after_n_varg__n_insert_begin(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    it_pos = slist_begin(pslist);
    t_oldsize = slist_size(pslist);
    _slist_insert_after_n(pslist, it_pos, 10, 100);
    assert_true(slist_size(pslist) == t_oldsize + 10);
    assert_true(iterator_equal(it_pos, slist_begin(pslist)));
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

void test__slist_insert_after_n__slist_insert_after_n_varg__n_insert_middle(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    it_pos = iterator_advance(slist_begin(pslist), 3);
    t_oldsize = slist_size(pslist);
    _slist_insert_after_n(pslist, it_pos, 10, 100);
    assert_true(slist_size(pslist) == t_oldsize + 10);
    assert_true(iterator_equal(it_pos, iterator_advance(slist_begin(pslist), 3)));
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
        it_iter = iterator_next(it_iter), ++i)
    {
        if(i > 3 && i < 14)
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

void test__slist_insert_after_n__slist_insert_after_n_varg__n_insert_end(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    it_pos = slist_previous(pslist, slist_end(pslist));
    t_oldsize = slist_size(pslist);
    _slist_insert_after_n(pslist, it_pos, 10, 100);
    assert_true(slist_size(pslist) == t_oldsize + 10);
    assert_true(iterator_equal(it_pos, iterator_advance(slist_begin(pslist), 9)));
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
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

    slist_destroy(pslist);
}

void test__slist_insert_after_n__slist_insert_after_n_varg__n_insert_end_multiple(void** state)
{
    slist_iterator_t it_pos;
    slist_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    slist_t* pslist = create_slist(int);
    slist_init_n(pslist, 10);

    it_pos = slist_previous(pslist, slist_end(pslist));
    t_oldsize = slist_size(pslist);
    _slist_insert_after_n(pslist, it_pos, 10, 100, 9888, 8374, 23523);
    assert_true(slist_size(pslist) == t_oldsize + 10);
    assert_true(iterator_equal(it_pos, iterator_advance(slist_begin(pslist), 9)));
    for(it_iter = slist_begin(pslist), i = 0;
        !iterator_equal(it_iter, slist_end(pslist));
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

    slist_destroy(pslist);
}

