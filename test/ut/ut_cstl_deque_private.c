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
#include "ut_cstl_deque_private.h"

UT_SUIT_DEFINATION(cstl_deque_private, _create_deque)

/*
 * test _create_deque
 */
UT_CASE_DEFINATION(_create_deque)
void test__create_deque__null_typename(void** state)
{
    expect_assert_failure(_create_deque(NULL));
}

void test__create_deque__unregisted_type(void** state)
{
    assert_true(_create_deque("_test__create_deque__unregisted_type_t") == NULL);
}

void test__create_deque__c_builtin_type(void** state)
{
    deque_t* pdeq = _create_deque("unsigned int");
    assert_true(pdeq != NULL);
    assert_true(strcmp(_GET_DEQUE_TYPE_NAME(pdeq), "unsigned int") == 0);
    assert_true(_deque_is_created(pdeq));

    deque_destroy(pdeq);
}

void test__create_deque__libcstl_builtin_type(void** state)
{
    deque_t* pdeq = _create_deque("vector_t         <      int>     ");
    assert_true(pdeq != NULL);
    assert_true(strcmp(_GET_DEQUE_TYPE_NAME(pdeq), "vector_t<int>") == 0);
    assert_true(_deque_is_created(pdeq));

    deque_destroy(pdeq);
}

typedef struct _tag_test__create_deque__user_defined_type
{
    int n_elem;
}_test__create_deque__user_defined_type_t;

void test__create_deque__user_defined_type(void** state)
{
    deque_t* pdeq = NULL;

    type_register(struct _tag_test__create_deque__user_defined_type, NULL, NULL, NULL, NULL);
    pdeq = _create_deque("struct      _tag_test__create_deque__user_defined_type");
    assert_true(pdeq != NULL);
    assert_true(strcmp(_GET_DEQUE_TYPE_NAME(pdeq), "struct _tag_test__create_deque__user_defined_type") == 0);
    assert_true(_deque_is_created(pdeq));

    deque_destroy(pdeq);
}

void test__create_deque__user_defined_type_dup(void** state)
{
    deque_t* pdeq = NULL;

    type_duplicate(struct _tag_test__create_deque__user_defined_type, _test__create_deque__user_defined_type_t);
    pdeq = _create_deque("_test__create_deque__user_defined_type_t");
    assert_true(pdeq != NULL);
    assert_true(strcmp(_GET_DEQUE_TYPE_NAME(pdeq), "_test__create_deque__user_defined_type_t") == 0);
    assert_true(_deque_is_created(pdeq));

    deque_destroy(pdeq);
}

/*
 * test _create_deque_auxiliary
 */
UT_CASE_DEFINATION(_create_deque_auxiliary)
void test__create_deque_auxiliary__null_deque_container(void** state)
{
    expect_assert_failure(_create_deque_auxiliary(NULL, "int"));
}

void test__create_deque_auxiliary__null_typename(void** state)
{
    deque_t* pdeq = malloc(sizeof(deque_t));
    expect_assert_failure(_create_deque_auxiliary(pdeq, NULL));

    free(pdeq);
}

void test__create_deque_auxiliary__unregisted_type(void** state)
{
    deque_t* pdeq = malloc(sizeof(deque_t));
    assert_false(_create_deque_auxiliary(pdeq, "_test__create_deque_auxiliary__unregisted_type_t"));

    free(pdeq);
}

void test__create_deque_auxiliary__c_builtin(void** state)
{
    deque_t* pdeq = malloc(sizeof(deque_t));
    assert_true(_create_deque_auxiliary(pdeq, "double"));
    assert_true(strcmp(_GET_DEQUE_TYPE_NAME(pdeq), "double") == 0);
    assert_true(_alloc_is_inited(&pdeq->_t_allocator));
    assert_true(_deque_is_created(pdeq));

    deque_destroy(pdeq);
}

void test__create_deque_auxiliary__libcstl_builtin(void** state)
{
    deque_t* pdeq = malloc(sizeof(deque_t));
    assert_true(_create_deque_auxiliary(pdeq, "deque_t<   vector_t     <     string_t>>       "));
    assert_true(strcmp(_GET_DEQUE_TYPE_NAME(pdeq), "deque_t<vector_t<string_t>>") == 0);
    assert_true(_alloc_is_inited(&pdeq->_t_allocator));
    assert_true(_deque_is_created(pdeq));

    deque_destroy(pdeq);
}

typedef struct _tag_test__create_deque_auxiliary__user_defined
{
    int n_elem;
}_test__create_deque_auxiliary__user_defined_t;
void test__create_deque_auxiliary__user_defined(void** state)
{
    deque_t* pdeq = NULL;
    type_register(struct _tag_test__create_deque_auxiliary__user_defined, NULL, NULL, NULL, NULL);
    pdeq = malloc(sizeof(deque_t));
    assert_true(_create_deque_auxiliary(pdeq, "struct _tag_test__create_deque_auxiliary__user_defined"));
    assert_true(strcmp(_GET_DEQUE_TYPE_NAME(pdeq), "struct _tag_test__create_deque_auxiliary__user_defined") == 0);
    assert_true(_alloc_is_inited(&pdeq->_t_allocator));
    assert_true(_deque_is_created(pdeq));

    deque_destroy(pdeq);
}

void test__create_deque_auxiliary__user_defined_dup(void** state)
{
    deque_t* pdeq = NULL;
    type_duplicate(struct _tag_test__create_deque_auxiliary__user_defined, _test__create_deque_auxiliary__user_defined_t);
    pdeq = malloc(sizeof(deque_t));
    assert_true(_create_deque_auxiliary(pdeq, "_test__create_deque_auxiliary__user_defined_t"));
    assert_true(strcmp(_GET_DEQUE_TYPE_NAME(pdeq), "_test__create_deque_auxiliary__user_defined_t") == 0);
    assert_true(_alloc_is_inited(&pdeq->_t_allocator));
    assert_true(_deque_is_created(pdeq));

    deque_destroy(pdeq);
}

/*
 * test _deque_init_elem and _deque_init_elem_varg
 */
UT_CASE_DEFINATION(_deque_init_elem__deque_init_elem_varg)
void test__deque_init_elem__deque_init_elem_varg__null_deque_container(void** state)
{
    expect_assert_failure(_deque_init_elem(NULL, 10, 100));
}

void test__deque_init_elem__deque_init_elem_varg__non_created_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);

    pdeq->_t_mapsize = 9009;
    expect_assert_failure(_deque_init_elem(pdeq, 10, 100));

    pdeq->_t_mapsize = 0;
    deque_destroy(pdeq);
}

void test__deque_init_elem__deque_init_elem_varg__0_count(void** state)
{
    deque_t* pdeq = create_deque(int);

    _deque_init_elem(pdeq, 0, 100);
    assert_true(deque_size(pdeq) == 0);
    assert_true(pdeq->_t_mapsize == 16);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(pdeq->_t_start) + 1 == _DEQUE_ITERATOR_MAP_POINTER(pdeq->_t_finish));
    assert_true(_DEQUE_ITERATOR_COREPOS(pdeq->_t_start) == _DEQUE_ITERATOR_AFTERLAST_POS(pdeq->_t_start));
    assert_true(_DEQUE_ITERATOR_COREPOS(pdeq->_t_finish) == _DEQUE_ITERATOR_FIRST_POS(pdeq->_t_finish));

    deque_destroy(pdeq);
}

void test__deque_init_elem__deque_init_elem_varg__count(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);

    _deque_init_elem(pdeq, 10, 100);
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
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    deque_destroy(pdeq);
}

void test__deque_init_elem__deque_init_elem_varg__multiple_elem(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);

    _deque_init_elem(pdeq, 10, 100, 3940, 23342, -284);
    assert_true(deque_size(pdeq) == 10);
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    deque_destroy(pdeq);
}

void test__deque_init_elem__deque_init_elem_varg__one_chunk(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);

    _deque_init_elem(pdeq, 16, 100);
    assert_true(deque_size(pdeq) == 16);
    assert_true(pdeq->_t_mapsize == 16);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(pdeq->_t_start) + 2 == _DEQUE_ITERATOR_MAP_POINTER(pdeq->_t_finish));
    assert_true(_DEQUE_ITERATOR_COREPOS(pdeq->_t_start) == _DEQUE_ITERATOR_AFTERLAST_POS(pdeq->_t_start));
    assert_true(_DEQUE_ITERATOR_COREPOS(pdeq->_t_finish) == _DEQUE_ITERATOR_FIRST_POS(pdeq->_t_finish));
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    deque_destroy(pdeq);
}

void test__deque_init_elem__deque_init_elem_varg__more_than_one_chunk(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);

    _deque_init_elem(pdeq, 19, 100);
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
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    deque_destroy(pdeq);
}

void test__deque_init_elem__deque_init_elem_varg__map_grow(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);

    _deque_init_elem(pdeq, 260, 100);
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
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    deque_destroy(pdeq);
}

/*
 * test _deque_destroy_auxiliary
 */
UT_CASE_DEFINATION(_deque_destroy_auxiliary)
void test__deque_destroy_auxiliary__null_deque_container(void** state)
{
    expect_assert_failure(_deque_destroy_auxiliary(NULL));
}

void test__deque_destroy_auxiliary__non_created_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);

    pdeq->_t_mapsize = 99000;
    expect_assert_failure(_deque_destroy_auxiliary(pdeq));

    pdeq->_t_mapsize = 0;
    deque_destroy(pdeq);
}

void test__deque_destroy_auxiliary__non_inited(void** state)
{
    deque_t* pdeq = create_deque(int);
    _deque_destroy_auxiliary(pdeq);
    assert_true(pdeq->_t_mapsize == 0);
    assert_true(pdeq->_ppby_map == NULL);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(pdeq->_t_start) == NULL);
    assert_true(_DEQUE_ITERATOR_FIRST_POS(pdeq->_t_start) == NULL);
    assert_true(_DEQUE_ITERATOR_AFTERLAST_POS(pdeq->_t_start) == NULL);
    assert_true(_DEQUE_ITERATOR_COREPOS(pdeq->_t_start) == NULL);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(pdeq->_t_finish) == NULL);
    assert_true(_DEQUE_ITERATOR_FIRST_POS(pdeq->_t_finish) == NULL);
    assert_true(_DEQUE_ITERATOR_AFTERLAST_POS(pdeq->_t_finish) == NULL);
    assert_true(_DEQUE_ITERATOR_COREPOS(pdeq->_t_finish) == NULL);

    free(pdeq);
}

void test__deque_destroy_auxiliary__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _deque_destroy_auxiliary(pdeq);
    assert_true(pdeq->_t_mapsize == 0);
    assert_true(pdeq->_ppby_map == NULL);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(pdeq->_t_start) == NULL);
    assert_true(_DEQUE_ITERATOR_FIRST_POS(pdeq->_t_start) == NULL);
    assert_true(_DEQUE_ITERATOR_AFTERLAST_POS(pdeq->_t_start) == NULL);
    assert_true(_DEQUE_ITERATOR_COREPOS(pdeq->_t_start) == NULL);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(pdeq->_t_finish) == NULL);
    assert_true(_DEQUE_ITERATOR_FIRST_POS(pdeq->_t_finish) == NULL);
    assert_true(_DEQUE_ITERATOR_AFTERLAST_POS(pdeq->_t_finish) == NULL);
    assert_true(_DEQUE_ITERATOR_COREPOS(pdeq->_t_finish) == NULL);

    free(pdeq);
}

void test__deque_destroy_auxiliary__non_empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    assert_true(deque_size(pdeq) == 10);
    _deque_destroy_auxiliary(pdeq);
    assert_true(pdeq->_t_mapsize == 0);
    assert_true(pdeq->_ppby_map == NULL);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(pdeq->_t_start) == NULL);
    assert_true(_DEQUE_ITERATOR_FIRST_POS(pdeq->_t_start) == NULL);
    assert_true(_DEQUE_ITERATOR_AFTERLAST_POS(pdeq->_t_start) == NULL);
    assert_true(_DEQUE_ITERATOR_COREPOS(pdeq->_t_start) == NULL);
    assert_true(_DEQUE_ITERATOR_MAP_POINTER(pdeq->_t_finish) == NULL);
    assert_true(_DEQUE_ITERATOR_FIRST_POS(pdeq->_t_finish) == NULL);
    assert_true(_DEQUE_ITERATOR_AFTERLAST_POS(pdeq->_t_finish) == NULL);
    assert_true(_DEQUE_ITERATOR_COREPOS(pdeq->_t_finish) == NULL);

    free(pdeq);
}

/*
 * test _deque_assign_elem and _deque_assign_elem_varg
 */
UT_CASE_DEFINATION(_deque_assign_elem__deque_assign_elem_varg)
void test__deque_assign_elem__deque_assign_elem_varg__null_deque_container(void** state)
{
    expect_assert_failure(_deque_assign_elem(NULL, 10, 100));
}

void test__deque_assign_elem__deque_assign_elem_varg__non_inited_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);

    expect_assert_failure(_deque_assign_elem(pdeq, 10, 100));

    deque_destroy(pdeq);
}

void test__deque_assign_elem__deque_assign_elem_varg__0_assign_0(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    assert_true(deque_size(pdeq) == 0);
    _deque_assign_elem(pdeq, 0, 100);
    assert_true(deque_size(pdeq) == 0);

    deque_destroy(pdeq);
}

void test__deque_assign_elem__deque_assign_elem_varg__0_assign_n(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    assert_true(deque_size(pdeq) == 0);
    _deque_assign_elem(pdeq, 10, 100);
    assert_true(deque_size(pdeq) == 10);
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    deque_destroy(pdeq);
}

void test__deque_assign_elem__deque_assign_elem_varg__n_assign_0(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);
    deque_init_n(pdeq, 10);

    assert_true(deque_size(pdeq) == 10);
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }
    _deque_assign_elem(pdeq, 0, 100);
    assert_true(deque_size(pdeq) == 0);

    deque_destroy(pdeq);
}

void test__deque_assign_elem__deque_assign_elem_varg__n_assign_m_n_greater_than_m(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);
    deque_init_n(pdeq, 10);

    assert_true(deque_size(pdeq) == 10);
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }
    _deque_assign_elem(pdeq, 4, 100);
    assert_true(deque_size(pdeq) == 4);
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    deque_destroy(pdeq);
}

void test__deque_assign_elem__deque_assign_elem_varg__n_assign_m_n_equal_to_m(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);
    deque_init_n(pdeq, 10);

    assert_true(deque_size(pdeq) == 10);
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }
    _deque_assign_elem(pdeq, 10, 100);
    assert_true(deque_size(pdeq) == 10);
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    deque_destroy(pdeq);
}

void test__deque_assign_elem__deque_assign_elem_varg__n_assign_m_n_less_than_m(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);
    deque_init_n(pdeq, 10);

    assert_true(deque_size(pdeq) == 10);
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }
    _deque_assign_elem(pdeq, 18, 100);
    assert_true(deque_size(pdeq) == 18);
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    deque_destroy(pdeq);
}

void test__deque_assign_elem__deque_assign_elem_varg__n_assign_m_n_less_than_m_multiple(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);
    deque_init_n(pdeq, 10);

    assert_true(deque_size(pdeq) == 10);
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }
    _deque_assign_elem(pdeq, 18, 100, 2983, 2445, 2222);
    assert_true(deque_size(pdeq) == 18);
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    deque_destroy(pdeq);
}

/*
 * test _deque_push_back and _deque_push_back_varg
 */
UT_CASE_DEFINATION(_deque_push_back__deque_push_back_varg)
void test__deque_push_back__deque_push_back_varg__null_deque_container(void** state)
{
    expect_assert_failure(_deque_push_back(NULL, 100));
}

void test__deque_push_back__deque_push_back_varg__non_inited_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);

    expect_assert_failure(_deque_push_back(pdeq, 100));

    deque_destroy(pdeq);
}

void test__deque_push_back__deque_push_back_varg__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _deque_push_back(pdeq, 100);
    assert_true(deque_size(pdeq) == 1);
    assert_true(*(int*)deque_back(pdeq) == 100);

    deque_destroy(pdeq);
}

void test__deque_push_back__deque_push_back_varg__non_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    size_t t_oldsize = 0;

    deque_init_n(pdeq, 10);
    t_oldsize = deque_size(pdeq);
    _deque_push_back(pdeq, 100);
    assert_true(deque_size(pdeq) == t_oldsize + 1);
    assert_true(*(int*)deque_back(pdeq) == 100);

    deque_destroy(pdeq);
}

void test__deque_push_back__deque_push_back_varg__non_empty_multiple(void** state)
{
    deque_t* pdeq = create_deque(int);
    size_t t_oldsize = 0;

    deque_init_n(pdeq, 10);
    t_oldsize = deque_size(pdeq);
    _deque_push_back(pdeq, 100, 927, 0, 7284394);
    assert_true(deque_size(pdeq) == t_oldsize + 1);
    assert_true(*(int*)deque_back(pdeq) == 100);

    deque_destroy(pdeq);
}

/*
 * test _deque_push_front and _deque_push_front_varg
 */
UT_CASE_DEFINATION(_deque_push_front__deque_push_front_varg)
void test__deque_push_front__deque_push_front_varg__null_deque_container(void** state)
{
    expect_assert_failure(_deque_push_front(NULL, 100));
}

void test__deque_push_front__deque_push_front_varg__non_inited_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);

    expect_assert_failure(_deque_push_front(pdeq, 100));

    deque_destroy(pdeq);
}

void test__deque_push_front__deque_push_front_varg__empty(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _deque_push_front(pdeq, 100);
    assert_true(deque_size(pdeq) == 1);
    assert_true(*(int*)deque_front(pdeq) == 100);

    deque_destroy(pdeq);
}

void test__deque_push_front__deque_push_front_varg__non_empty(void** state)
{
    deque_t* pdeq = create_deque(int);
    size_t t_oldsize = 0;

    deque_init_n(pdeq, 10);
    t_oldsize = deque_size(pdeq);
    _deque_push_front(pdeq, 100);
    assert_true(deque_size(pdeq) == t_oldsize + 1);
    assert_true(*(int*)deque_front(pdeq) == 100);

    deque_destroy(pdeq);
}

void test__deque_push_front__deque_push_front_varg__non_empty_multiple(void** state)
{
    deque_t* pdeq = create_deque(int);
    size_t t_oldsize = 0;

    deque_init_n(pdeq, 10);
    t_oldsize = deque_size(pdeq);
    _deque_push_front(pdeq, 100, 98, 23523, 2222);
    assert_true(deque_size(pdeq) == t_oldsize + 1);
    assert_true(*(int*)deque_front(pdeq) == 100);

    deque_destroy(pdeq);
}

/*
 * test _deque_resize_elem and _deque_resize_elem_varg
 */
UT_CASE_DEFINATION(_deque_resize_elem__deque_resize_elem_varg)
void test__deque_resize_elem__deque_resize_elem_varg__null_deque_container(void** state)
{
    expect_assert_failure(_deque_resize_elem(NULL, 10, 100));
}

void test__deque_resize_elem__deque_resize_elem_varg__non_inited_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);

    expect_assert_failure(_deque_resize_elem(pdeq, 10, 100));

    deque_destroy(pdeq);
}

void test__deque_resize_elem__deque_resize_elem_varg__0_resize_0(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _deque_resize_elem(pdeq, 0, 100);
    assert_true(deque_size(pdeq) == 0);

    deque_destroy(pdeq);
}

void test__deque_resize_elem__deque_resize_elem_varg__0_resize_n(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    _deque_resize_elem(pdeq, 10, 100);
    assert_true(deque_size(pdeq) == 10);
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    deque_destroy(pdeq);
}

void test__deque_resize_elem__deque_resize_elem_varg__n_resize_0(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    _deque_resize_elem(pdeq, 0, 100);
    assert_true(deque_size(pdeq) == 0);

    deque_destroy(pdeq);
}

void test__deque_resize_elem__deque_resize_elem_varg__n_resize_m_n_greater_than_m(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    _deque_resize_elem(pdeq, 4, 100);
    assert_true(deque_size(pdeq) == 4);
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    deque_destroy(pdeq);
}

void test__deque_resize_elem__deque_resize_elem_varg__n_resize_m_n_equal_to_m(void** state)
{
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    _deque_resize_elem(pdeq, 10, 100);
    assert_true(deque_size(pdeq) == 10);
    for(it_iter = deque_begin(pdeq);
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter))
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    deque_destroy(pdeq);
}

void test__deque_resize_elem__deque_resize_elem_varg__n_resize_m_n_less_than_m(void** state)
{
    size_t i = 0;
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    _deque_resize_elem(pdeq, 16, 100);
    assert_true(deque_size(pdeq) == 16);
    for(it_iter = deque_begin(pdeq), i = 0;
        !iterator_equal(it_iter, deque_end(pdeq));
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

    deque_destroy(pdeq);
}

void test__deque_resize_elem__deque_resize_elem_varg__n_resize_m_n_less_than_m_multiple(void** state)
{
    size_t i = 0;
    deque_iterator_t it_iter;
    deque_t* pdeq = create_deque(int);

    deque_init_n(pdeq, 10);
    _deque_resize_elem(pdeq, 16, 100, 0, 28348, 274984);
    assert_true(deque_size(pdeq) == 16);
    for(it_iter = deque_begin(pdeq), i = 0;
        !iterator_equal(it_iter, deque_end(pdeq));
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

    deque_destroy(pdeq);
}

/*
 * test _deque_insert_n and _deque_insert_n_varg
 */
UT_CASE_DEFINATION(_deque_insert_n__deque_insert_n_varg)
void test__deque_insert_n__deque_insert_n_varg__null_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    expect_assert_failure(_deque_insert_n(NULL, deque_begin(pdeq), 10, 100));

    deque_destroy(pdeq);
}

void test__deque_insert_n__deque_insert_n_varg__non_inited_deque_container(void** state)
{
    deque_t* pdeq = create_deque(int);
    deque_t* pdeq_deque = create_deque(int);

    deque_init(pdeq_deque);
    expect_assert_failure(_deque_insert_n(pdeq, deque_begin(pdeq_deque), 10, 100));

    deque_destroy(pdeq);
    deque_destroy(pdeq_deque);
}

void test__deque_insert_n__deque_insert_n_varg__invalid_pos(void** state)
{
    deque_iterator_t it_pos;
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    it_pos = deque_begin(pdeq);
    it_pos._t_pos._t_dequepos._pby_corepos = (_byte_t*)0x99;
    expect_assert_failure(_deque_insert_n(pdeq, it_pos, 10, 100));

    deque_destroy(pdeq);
}

void test__deque_insert_n__deque_insert_n_varg__0_insert_0(void** state)
{
    deque_iterator_t it_pos;
    deque_iterator_t it_iter;
    size_t t_oldsize = 0;
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    it_pos = deque_begin(pdeq);
    t_oldsize = deque_size(pdeq);
    it_iter = _deque_insert_n(pdeq, it_pos, 0, 100);
    assert_true(deque_size(pdeq) == t_oldsize);
    assert_true(iterator_equal(it_iter, it_pos));

    deque_destroy(pdeq);
}

void test__deque_insert_n__deque_insert_n_varg__0_insert_n(void** state)
{
    deque_iterator_t it_pos;
    deque_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    it_pos = deque_begin(pdeq);
    t_oldsize = deque_size(pdeq);
    it_iter = _deque_insert_n(pdeq, it_pos, 10, 100);
    assert_true(deque_size(pdeq) == t_oldsize + 10);
    assert_true(iterator_equal(it_iter, deque_begin(pdeq)));
    for(it_iter = deque_begin(pdeq), i = 0;
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 100);
    }

    deque_destroy(pdeq);
}

void test__deque_insert_n__deque_insert_n_varg__n_insert_0(void** state)
{
    deque_iterator_t it_pos;
    deque_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_init_n(pdeq, 10);

    it_pos = deque_begin(pdeq);
    t_oldsize = deque_size(pdeq);
    it_iter = _deque_insert_n(pdeq, it_pos, 0, 100);
    assert_true(deque_size(pdeq) == t_oldsize);
    assert_true(iterator_equal(it_iter, deque_begin(pdeq)));
    for(it_iter = deque_begin(pdeq), i = 0;
        !iterator_equal(it_iter, deque_end(pdeq));
        it_iter = iterator_next(it_iter), ++i)
    {
        assert_true(*(int*)iterator_get_pointer(it_iter) == 0);
    }

    deque_destroy(pdeq);
}

void test__deque_insert_n__deque_insert_n_varg__n_insert_begin(void** state)
{
    deque_iterator_t it_pos;
    deque_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_init_n(pdeq, 10);

    it_pos = deque_begin(pdeq);
    t_oldsize = deque_size(pdeq);
    it_iter = _deque_insert_n(pdeq, it_pos, 10, 100);
    assert_true(deque_size(pdeq) == t_oldsize + 10);
    assert_true(iterator_equal(it_iter, deque_begin(pdeq)));
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

void test__deque_insert_n__deque_insert_n_varg__n_insert_middle(void** state)
{
    deque_iterator_t it_pos;
    deque_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_init_n(pdeq, 10);

    it_pos = iterator_advance(deque_begin(pdeq), 3);
    t_oldsize = deque_size(pdeq);
    it_iter = _deque_insert_n(pdeq, it_pos, 10, 100);
    assert_true(deque_size(pdeq) == t_oldsize + 10);
    assert_true(iterator_equal(it_iter, iterator_advance(deque_begin(pdeq), 3)));
    for(it_iter = deque_begin(pdeq), i = 0;
        !iterator_equal(it_iter, deque_end(pdeq));
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

    deque_destroy(pdeq);
}

void test__deque_insert_n__deque_insert_n_varg__n_insert_end(void** state)
{
    deque_iterator_t it_pos;
    deque_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_init_n(pdeq, 10);

    it_pos = deque_end(pdeq);
    t_oldsize = deque_size(pdeq);
    it_iter = _deque_insert_n(pdeq, it_pos, 10, 100);
    assert_true(deque_size(pdeq) == t_oldsize + 10);
    assert_true(iterator_equal(it_iter, iterator_advance(deque_end(pdeq), -10)));
    for(it_iter = deque_begin(pdeq), i = 0;
        !iterator_equal(it_iter, deque_end(pdeq));
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

    deque_destroy(pdeq);
}

void test__deque_insert_n__deque_insert_n_varg__n_insert_end_multiple(void** state)
{
    deque_iterator_t it_pos;
    deque_iterator_t it_iter;
    size_t t_oldsize = 0;
    size_t i = 0;
    deque_t* pdeq = create_deque(int);
    deque_init_n(pdeq, 10);

    it_pos = deque_end(pdeq);
    t_oldsize = deque_size(pdeq);
    it_iter = _deque_insert_n(pdeq, it_pos, 10, 100, 9888, 8374, 23523);
    assert_true(deque_size(pdeq) == t_oldsize + 10);
    assert_true(iterator_equal(it_iter, iterator_advance(deque_end(pdeq), -10)));
    for(it_iter = deque_begin(pdeq), i = 0;
        !iterator_equal(it_iter, deque_end(pdeq));
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

    deque_destroy(pdeq);
}

/*
 * test _deque_init_elem_auxiliary
 */
UT_CASE_DEFINATION(_deque_init_elem_auxiliary)
void test__deque_init_elem_auxiliary__null_deque_container(void** state)
{
    int elem = 0;
    expect_assert_failure(_deque_init_elem_auxiliary(NULL, &elem));
}

void test__deque_init_elem_auxiliary__null_elem(void** state)
{
    deque_t* pdeq = create_deque(int);

    expect_assert_failure(_deque_init_elem_auxiliary(pdeq, NULL));

    deque_destroy(pdeq);
}

void test__deque_init_elem_auxiliary__non_inited_deque(void** state)
{
    int elem = 0;
    deque_t* pdeq = create_deque(int);

    deque_init(pdeq);
    pdeq->_t_mapsize = 0;
    expect_assert_failure(_deque_init_elem_auxiliary(pdeq, &elem));

    pdeq->_t_mapsize = 16;
    deque_destroy(pdeq);
}

void test__deque_init_elem_auxiliary__successfully_int(void** state)
{
    int elem = 100;
    deque_t* pdeq = create_deque(int);
    deque_init(pdeq);

    _deque_init_elem_auxiliary(pdeq, &elem);
    assert_true(elem == 0);

    deque_destroy(pdeq);
}

void test__deque_init_elem_auxiliary__successfully_cstr(void** state)
{
    string_t elem;
    deque_t* pdeq = create_deque(char*);
    deque_init_elem(pdeq, 10, "abcdefg");

    _deque_init_elem_auxiliary(pdeq, &elem);
    assert_true(strcmp(string_c_str(&elem), "") == 0);

    _string_destroy_auxiliary(&elem);
    deque_destroy(pdeq);
}

void test__deque_init_elem_auxiliary__successfully_iterator(void** state)
{
    iterator_t it_iter = _create_deque_iterator();
    deque_t* pdeq = create_deque(iterator_t);
    deque_init_elem(pdeq, 10, &it_iter);

    _deque_init_elem_auxiliary(pdeq, _deque_iterator_get_pointer_auxiliary(deque_begin(pdeq)));
    memset(&it_iter, 0x00, sizeof(iterator_t));
    assert_true(memcmp((iterator_t*)deque_front(pdeq), &it_iter, sizeof(iterator_t)) == 0);

    deque_destroy(pdeq);
}

void test__deque_init_elem_auxiliary__successfully_container(void** state)
{
    deque_t deque;
    deque_t* pdeq = create_deque(deque_t<int>);

    _deque_init_elem_auxiliary(pdeq, &deque);
    assert_true(_deque_is_inited(&deque));

    _deque_destroy_auxiliary(&deque);
    deque_destroy(pdeq);
}

typedef struct _tag_test__deque_init_elem_auxiliary__successfully_user_defined
{
    int n_elem;
}_test__deque_init_elem_auxiliary__successfully_user_defined_t;

void test__deque_init_elem_auxiliary__successfully_user_defined(void** stat)
{
    _test__deque_init_elem_auxiliary__successfully_user_defined_t t_user;
    deque_t* pdeq = NULL;

    type_register(_test__deque_init_elem_auxiliary__successfully_user_defined_t, NULL, NULL, NULL, NULL);
    pdeq = create_deque(_test__deque_init_elem_auxiliary__successfully_user_defined_t);
    t_user.n_elem = 100;
    _deque_init_elem_auxiliary(pdeq, &t_user);
    assert_true(t_user.n_elem == 0);

    deque_destroy(pdeq);
}

