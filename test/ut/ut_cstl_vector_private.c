#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/cstl_vector_iterator.h"
#include "cstl/cvector.h"
#include "cstl_vector_aux.h"
#include "cstl/cstring.h"

#include "ut_def.h"
#include "ut_cstl_vector_private.h"

UT_SUIT_DEFINATION(cstl_vector_private, _create_vector)

/*
 * test _create_vector
 */
UT_CASE_DEFINATION(_create_vector)

void test__create_vector__null_typename(void** state)
{
    expect_assert_failure(_create_vector(NULL));
}

void test__create_vector__unregisted_type(void** state)
{
    assert_true(_create_vector("unregisted_type_t") == NULL);
}

void test__create_vector__c_builtin_type(void** state)
{
    vector_t* pvec = _create_vector("unsigned int");
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__create_vector__libcstl_builtin_type(void** state)
{
    vector_t* pvec = _create_vector("list_t<int>");
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__create_vector__registed_type(void** state)
{
    typedef struct _tag__create_vector__registed_type{int n_elem;}_create_vector__registed_type_t;
    vector_t* pvec = NULL;
    type_register(_create_vector__registed_type_t, NULL, NULL, NULL, NULL);
    pvec = _create_vector("_create_vector__registed_type_t");
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

/*
 * test _create_vector_auxiliary
 */
UT_CASE_DEFINATION(_create_vector_auxiliary)
void test__create_vector_auxiliary__null_vector_container(void** state)
{
    expect_assert_failure(_create_vector_auxiliary(NULL, "int"));
}

void test__create_vector_auxiliary__null_typename(void** state)
{
    vector_t vec;
    expect_assert_failure(_create_vector_auxiliary(&vec, NULL));
}

void test__create_vector_auxiliary__unregisted_type(void** state)
{
    vector_t vec;
    assert_false(_create_vector_auxiliary(&vec, "unregisted_type_t"));
}

void test__create_vector_auxiliary__c_builtin_type(void** state)
{
    vector_t* pvec = (vector_t*)malloc(sizeof(vector_t));
    assert_true(pvec != NULL);
    assert_true(_create_vector_auxiliary(pvec, "int"));
    assert_true(pvec->_pby_endofstorage == NULL);
    assert_true(pvec->_pby_finish == NULL);
    assert_true(pvec->_pby_start == NULL);
    assert_true(pvec->_t_typeinfo._pt_type != NULL);
    assert_true(pvec->_t_typeinfo._t_style == _TYPE_C_BUILTIN);
    assert_true(strcmp(pvec->_t_typeinfo._s_typename, _INT_TYPE) == 0);

    vector_destroy(pvec);
}

void test__create_vector_auxiliary__libcstl_builtin_type(void** state)
{
    vector_t* pvec = (vector_t*)malloc(sizeof(vector_t));
    assert_true(pvec != NULL);
    assert_true(_create_vector_auxiliary(pvec, "list_t< int>    "));
    assert_true(pvec->_pby_endofstorage == NULL);
    assert_true(pvec->_pby_finish == NULL);
    assert_true(pvec->_pby_start == NULL);
    assert_true(pvec->_t_typeinfo._pt_type != NULL);
    assert_true(pvec->_t_typeinfo._t_style == _TYPE_CSTL_BUILTIN);
    assert_true(strcmp(pvec->_t_typeinfo._s_typename, "list_t<int>") == 0);

    vector_destroy(pvec);
}

void test__create_vector_auxiliary__registed_type(void** state)
{
    typedef struct _tag_create_vector_auxiliary__registed_type{int n_elem;}_create_vector_auxiliary__registed_type_t;
    vector_t* pvec = (vector_t*)malloc(sizeof(vector_t));
    assert_true(pvec != NULL);
    type_register(_create_vector_auxiliary__registed_type_t, NULL, NULL, NULL, NULL);
    assert_true(_create_vector_auxiliary(pvec, "_create_vector_auxiliary__registed_type_t"));
    assert_true(pvec->_pby_endofstorage == NULL);
    assert_true(pvec->_pby_finish == NULL);
    assert_true(pvec->_pby_start == NULL);
    assert_true(pvec->_t_typeinfo._pt_type != NULL);
    assert_true(pvec->_t_typeinfo._t_style == _TYPE_USER_DEFINE);
    assert_true(strcmp(pvec->_t_typeinfo._s_typename, "_create_vector_auxiliary__registed_type_t") == 0);

    vector_destroy(pvec);
}

/*
 * test _vector_init_elem and _vector_init_elem_varg
 */
UT_CASE_DEFINATION(_vector_init_elem__vector_init_elem_varg)
void test__vector_init_elem__vector_init_elem_varg__null_vector_container(void** state)
{
    expect_assert_failure(_vector_init_elem(NULL, 10, 100));
}

void test__vector_init_elem__vector_init_elem_varg__non_created(void** state)
{
    vector_t vec;
    vec._pby_start = (_byte_t*)0x89;

    expect_assert_failure(_vector_init_elem(&vec, 10, 100));
}

void test__vector_init_elem__vector_init_elem_varg__successfully_0_count(void** state)
{
    vector_t* pvec = create_vector(int);

    _vector_init_elem(pvec, 0, 100);
    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);

    vector_destroy(pvec);
}

void test__vector_init_elem__vector_init_elem_varg__successfully(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);

    _vector_init_elem(pvec, 8, 100);
    assert_true(vector_size(pvec) == 8);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 100);
    }
    assert_true(vector_capacity(pvec) == 24);

    vector_destroy(pvec);
}

void test__vector_init_elem__vector_init_elem_varg__successfully_large_amounts_of_data(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);

    _vector_init_elem(pvec, 800, 100);
    assert_true(vector_size(pvec) == 800);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 100);
    }
    assert_true(vector_capacity(pvec) == 1200);

    vector_destroy(pvec);
}

void test__vector_init_elem__vector_init_elem_varg__successfully_multiple_specificed_element(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);

    _vector_init_elem(pvec, 8, 100, 200, 300, 400);
    assert_true(vector_size(pvec) == 8);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 100);
    }
    assert_true(vector_capacity(pvec) == 24);

    vector_destroy(pvec);
}

/*
 * test _vector_destroy_auxiliary
 */
UT_CASE_DEFINATION(_vector_destroy_auxiliary)
void test__vector_destroy_auxiliary__null_vector_container(void** state)
{
    expect_assert_failure(_vector_destroy_auxiliary(NULL));
}

void test__vector_destroy_auxiliary__invalid_vector_container_finish_less_than_start(void** state)
{
    vector_t vec;
    vec._pby_finish = (_byte_t*)0x00;
    vec._pby_start = (_byte_t*)0x08;

    expect_assert_failure(_vector_destroy_auxiliary(&vec));
}

void test__vector_destroy_auxiliary__invalid_vector_container_endofstorage_less_than_start(void** state)
{
    vector_t vec;
    vec._pby_endofstorage = (_byte_t*)0x00;
    vec._pby_start = (_byte_t*)0x08;
    vec._pby_finish = (_byte_t*)0x10;

    expect_assert_failure(_vector_destroy_auxiliary(&vec));
}

void test__vector_destroy_auxiliary__successfully_non_init_container(void** state)
{
    vector_t* pvec = create_vector(int);

    _vector_destroy_auxiliary(pvec);
    assert_true(pvec->_pby_endofstorage == NULL);
    assert_true(pvec->_pby_finish == NULL);
    assert_true(pvec->_pby_start == NULL);

    free(pvec);
}

void test__vector_destroy_auxiliary__successfully_empty_container(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    _vector_destroy_auxiliary(pvec);
    assert_true(pvec->_pby_endofstorage == NULL);
    assert_true(pvec->_pby_finish == NULL);
    assert_true(pvec->_pby_start == NULL);

    free(pvec);
}

void test__vector_destroy_auxiliary__successfully(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 10);

    _vector_destroy_auxiliary(pvec);
    assert_true(pvec->_pby_endofstorage == NULL);
    assert_true(pvec->_pby_finish == NULL);
    assert_true(pvec->_pby_start == NULL);

    free(pvec);
}

/*
 * test _vector_assign_elem and _vector_assign_elem_varg
 */
UT_CASE_DEFINATION(_vector_assign_elem__vector_assign_elem_varg)
void test__vector_assign_elem__vector_assign_elem_varg__null_vector_container(void** state)
{
    expect_assert_failure(_vector_assign_elem(NULL, 10, 100));
}

void test__vector_assign_elem__vector_assign_elem_varg__non_inited(void** state)
{
    vector_t* pvec = create_vector(int);

    pvec->_pby_start = (_byte_t*)0x89;
    expect_assert_failure(_vector_assign_elem(pvec, 10, 100));

    pvec->_pby_start = NULL;
    vector_destroy(pvec);
}

void test__vector_assign_elem__vector_assign_elem_varg__successfully_init_0_assign_0_count(void** state)
{
    vector_t* pvec = create_vector(int);

    vector_init(pvec);
    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0); 
    _vector_assign_elem(pvec, 0, 100);
    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0); 

    vector_destroy(pvec);
}

void test__vector_assign_elem__vector_assign_elem_varg__successfully_init_0_assign_n_count(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);

    vector_init(pvec);
    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0); 
    _vector_assign_elem(pvec, 8, 100);
    assert_true(vector_size(pvec) == 8);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 100);
    }
    assert_true(vector_capacity(pvec) == 24); 

    vector_destroy(pvec);
}

void test__vector_assign_elem__vector_assign_elem_varg__successfully_init_n_assign_0_count(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);

    vector_init_elem(pvec, 9, 45);
    assert_true(vector_size(pvec) == 9);
    assert_true(vector_capacity(pvec) == 25); 
    _vector_assign_elem(pvec, 0, 100);
    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 25); 

    vector_destroy(pvec);
}

void test__vector_assign_elem__vector_assign_elem_varg__successfully_init_n_assign_m_count(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);

    vector_init_elem(pvec, 9, 45);
    assert_true(vector_size(pvec) == 9);
    assert_true(vector_capacity(pvec) == 25); 
    _vector_assign_elem(pvec, 4, 100);
    assert_true(vector_size(pvec) == 4);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 100);
    }
    assert_true(vector_capacity(pvec) == 25); 

    vector_destroy(pvec);
}

void test__vector_assign_elem__vector_assign_elem_varg__successfully_init_n_assign_m_count_n_less_than_m(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);

    vector_init_elem(pvec, 9, 45);
    assert_true(vector_size(pvec) == 9);
    assert_true(vector_capacity(pvec) == 25); 
    _vector_assign_elem(pvec, 44, 100);
    assert_true(vector_size(pvec) == 44);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 100);
    }
    assert_true(vector_capacity(pvec) == 66); 

    vector_destroy(pvec);
}

void test__vector_assign_elem__vector_assign_elem_varg__successfully_multiple_count(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);

    vector_init(pvec);
    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0); 
    _vector_assign_elem(pvec, 4, 100, 200, 300, 400);
    assert_true(vector_size(pvec) == 4);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 100);
    }
    assert_true(vector_capacity(pvec) == 20); 

    vector_destroy(pvec);
}

/*
 * test _vector_push_back and _vector_push_back_varg
 */
UT_CASE_DEFINATION(_vector_push_back__vector_push_back_varg)
void test__vector_push_back__vector_push_back_varg__null_vector_container(void** state)
{
    expect_assert_failure(_vector_push_back(NULL, 90));
}

void test__vector_push_back__vector_push_back_varg__non_inited(void** state)
{
    vector_t* pvec = create_vector(int);
    pvec->_pby_start = (_byte_t*)0x98;

    expect_assert_failure(_vector_push_back(pvec, 90));

    pvec->_pby_start = NULL;
    vector_destroy(pvec);
}

void test__vector_push_back__vector_push_back_varg__successfully_empty(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);

    _vector_push_back(pvec, 90);
    assert_true(vector_size(pvec) == 1);
    assert_true(vector_capacity(pvec) == 17);
    assert_true(*(int*)vector_back(pvec) == 90);

    vector_destroy(pvec);
}

void test__vector_push_back__vector_push_back_varg__successfully_capacity_not_change(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init_elem(pvec, 10, 100);

    assert_true(vector_size(pvec) == 10);
    assert_true(vector_capacity(pvec) == 26);

    _vector_push_back(pvec, 90);
    assert_true(vector_size(pvec) == 11);
    assert_true(vector_capacity(pvec) == 26);
    assert_true(*(int*)vector_back(pvec) == 90);

    vector_destroy(pvec);
}

void test__vector_push_back__vector_push_back_varg__successfully_capacity_change(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init_elem(pvec, 40, 100);
    vector_resize_elem(pvec, 60, 100);

    assert_true(vector_size(pvec) == 60);
    assert_true(vector_capacity(pvec) == 60);

    _vector_push_back(pvec, 90);
    assert_true(vector_size(pvec) == 61);
    assert_true(vector_capacity(pvec) == 91);
    assert_true(*(int*)vector_back(pvec) == 90);

    vector_destroy(pvec);
}

void test__vector_push_back__vector_push_back_varg__successfully_multiple_element(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);

    _vector_push_back(pvec, 90, 100, 110, 111);
    assert_true(vector_size(pvec) == 1);
    assert_true(vector_capacity(pvec) == 17);
    assert_true(*(int*)vector_back(pvec) == 90);

    vector_destroy(pvec);
}

/*
 * test _vector_resize_elem and _vector_resize_elem_varg
 */
UT_CASE_DEFINATION(_vector_resize_elem__vector_resize_elem_varg)
void test__vector_resize_elem__vector_resize_elem_varg__null_vector_container(void** state)
{
    expect_assert_failure(_vector_resize_elem(NULL, 10, 100));
}

void test__vector_resize_elem__vector_resize_elem_varg__non_inited(void** state)
{
    vector_t* pvec = create_vector(int);
    pvec->_pby_start = (_byte_t*)0x987;

    expect_assert_failure(_vector_resize_elem(pvec, 10, 100));

    pvec->_pby_start = NULL;
    vector_destroy(pvec);
}

void test__vector_resize_elem__vector_resize_elem_varg__successfully_0_resize_0(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);
    _vector_resize_elem(pvec, 0, 100);
    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);

    vector_destroy(pvec);
}

void test__vector_resize_elem__vector_resize_elem_varg__successfully_0_resize_10(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);
    _vector_resize_elem(pvec, 10, 100);
    assert_true(vector_size(pvec) == 10);
    assert_true(vector_capacity(pvec) == 26);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 100);
    }

    vector_destroy(pvec);
}

void test__vector_resize_elem__vector_resize_elem_varg__successfully_0_resize_1000(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);
    _vector_resize_elem(pvec, 1000, 100);
    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 100);
    }

    vector_destroy(pvec);
}

void test__vector_resize_elem__vector_resize_elem_varg__successfully_10_resize_0(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 10);

    assert_true(vector_size(pvec) == 10);
    assert_true(vector_capacity(pvec) == 26);
    _vector_resize_elem(pvec, 0, 100);
    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 26);

    vector_destroy(pvec);
}

void test__vector_resize_elem__vector_resize_elem_varg__successfully_10_resize_10(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 10);

    assert_true(vector_size(pvec) == 10);
    assert_true(vector_capacity(pvec) == 26);
    _vector_resize_elem(pvec, 10, 100);
    assert_true(vector_size(pvec) == 10);
    assert_true(vector_capacity(pvec) == 26);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 0);
    }

    vector_destroy(pvec);
}

void test__vector_resize_elem__vector_resize_elem_varg__successfully_10_resize_1000(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 10);

    assert_true(vector_size(pvec) == 10);
    assert_true(vector_capacity(pvec) == 26);
    _vector_resize_elem(pvec, 1000, 100);
    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        if(i < 10)
        {
            assert_true(*(int*)vector_at(pvec, i) == 0);
        }
        else
        {
            assert_true(*(int*)vector_at(pvec, i) == 100);
        }
    }

    vector_destroy(pvec);
}

void test__vector_resize_elem__vector_resize_elem_varg__successfully_1000_resize_0(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    _vector_resize_elem(pvec, 0, 100);
    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 1500);

    vector_destroy(pvec);
}

void test__vector_resize_elem__vector_resize_elem_varg__successfully_1000_resize_10(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    _vector_resize_elem(pvec, 10, 100);
    assert_true(vector_size(pvec) == 10);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 0);
    }

    vector_destroy(pvec);
}

void test__vector_resize_elem__vector_resize_elem_varg__successfully_1000_resize_1000(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    _vector_resize_elem(pvec, 1000, 100);
    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 0);
    }

    vector_destroy(pvec);
}

void test__vector_resize_elem__vector_resize_elem_varg__successfully_1000_resize_1200(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    _vector_resize_elem(pvec, 1200, 100);
    assert_true(vector_size(pvec) == 1200);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        if(i < 1000)
        {
            assert_true(*(int*)vector_at(pvec, i) == 0);
        }
        else
        {
            assert_true(*(int*)vector_at(pvec, i) == 100);
        }
    }

    vector_destroy(pvec);
}

void test__vector_resize_elem__vector_resize_elem_varg__successfully_1000_resize_2000(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    _vector_resize_elem(pvec, 2000, 100);
    assert_true(vector_size(pvec) == 2000);
    assert_true(vector_capacity(pvec) == 3000);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        if(i < 1000)
        {
            assert_true(*(int*)vector_at(pvec, i) == 0);
        }
        else
        {
            assert_true(*(int*)vector_at(pvec, i) == 100);
        }
    }

    vector_destroy(pvec);
}

void test__vector_resize_elem__vector_resize_elem_varg__successfully_1000_resize_2000_multiple(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    _vector_resize_elem(pvec, 2000, 100, 110, 120, 130, 140, 150);
    assert_true(vector_size(pvec) == 2000);
    assert_true(vector_capacity(pvec) == 3000);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        if(i < 1000)
        {
            assert_true(*(int*)vector_at(pvec, i) == 0);
        }
        else
        {
            assert_true(*(int*)vector_at(pvec, i) == 100);
        }
    }

    vector_destroy(pvec);
}

/*
 * test _vector_insert_n and _vector_insert_n_varg
 */
UT_CASE_DEFINATION(_vector_insert_n__vector_insert_n_varg)
void test__vector_insert_n__vector_insert_n_varg__null_vector_container(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    expect_assert_failure(_vector_insert_n(NULL, vector_begin(pvec), 10, 100));

    vector_destroy(pvec);
}

void test__vector_insert_n__vector_insert_n_varg__non_inited(void** state)
{
    vector_t* pvec = create_vector(int);
    pvec->_pby_start = (_byte_t*)0x78;

    expect_assert_failure(_vector_insert_n(pvec, vector_begin(pvec), 10, 100));

    pvec->_pby_start = NULL;
    vector_destroy(pvec);
}

void test__vector_insert_n__vector_insert_n_varg__invalid_position(void** state)
{
    vector_iterator_t it_pos = _create_vector_iterator();
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 10);
    it_pos = vector_begin(pvec);
    it_pos._t_pos._pby_corepos = NULL;

    expect_assert_failure(_vector_insert_n(pvec, it_pos, 10, 100));

    vector_destroy(pvec);
}

void test__vector_insert_n__vector_insert_n_varg__empty_insert_0(void** state)
{
    vector_iterator_t it_pos;
    vector_iterator_t it_iter;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);
    it_pos = vector_begin(pvec);
    it_iter = _vector_insert_n(pvec, it_pos, 0, 100);
    assert_true(iterator_equal(it_iter, it_pos));
    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);

    vector_destroy(pvec);
}

void test__vector_insert_n__vector_insert_n_varg__empty_insert_10(void** state)
{
    vector_iterator_t it_pos;
    vector_iterator_t it_iter;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);
    it_pos = vector_begin(pvec);
    it_iter = _vector_insert_n(pvec, it_pos, 10, 100);
    assert_true(iterator_equal(it_iter, vector_begin(pvec)));
    assert_true(vector_size(pvec) == 10);
    assert_true(vector_capacity(pvec) == 26);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 100);
    }

    vector_destroy(pvec);
}

void test__vector_insert_n__vector_insert_n_varg__empty_insert_1000(void** state)
{
    vector_iterator_t it_pos;
    vector_iterator_t it_iter;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    assert_true(vector_size(pvec) == 0);
    assert_true(vector_capacity(pvec) == 0);
    it_pos = vector_begin(pvec);
    it_iter = _vector_insert_n(pvec, it_pos, 1000, 100);
    assert_true(iterator_equal(it_iter, vector_begin(pvec)));
    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 100);
    }

    vector_destroy(pvec);
}

void test__vector_insert_n__vector_insert_n_varg__begin_insert_0(void** state)
{
    vector_iterator_t it_pos;
    vector_iterator_t it_iter;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = vector_begin(pvec);
    it_iter = _vector_insert_n(pvec, it_pos, 0, 100);
    assert_true(iterator_equal(it_iter, vector_begin(pvec)));
    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 0);
    }

    vector_destroy(pvec);
}

void test__vector_insert_n__vector_insert_n_varg__begin_insert_10(void** state)
{
    vector_iterator_t it_pos;
    vector_iterator_t it_iter;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = vector_begin(pvec);
    it_iter = _vector_insert_n(pvec, it_pos, 10, 100);
    assert_true(iterator_equal(it_iter, vector_begin(pvec)));
    assert_true(vector_size(pvec) == 1010);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        if(i < 10)
        {
            assert_true(*(int*)vector_at(pvec, i) == 100);
        }
        else
        {
            assert_true(*(int*)vector_at(pvec, i) == 0);
        }
    }

    vector_destroy(pvec);
}

void test__vector_insert_n__vector_insert_n_varg__begin_insert_1000(void** state)
{
    vector_iterator_t it_pos;
    vector_iterator_t it_iter;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = vector_begin(pvec);
    it_iter = _vector_insert_n(pvec, it_pos, 1000, 100);
    assert_true(iterator_equal(it_iter, vector_begin(pvec)));
    assert_true(vector_size(pvec) == 2000);
    assert_true(vector_capacity(pvec) == 3000);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        if(i < 1000)
        {
            assert_true(*(int*)vector_at(pvec, i) == 100);
        }
        else
        {
            assert_true(*(int*)vector_at(pvec, i) == 0);
        }
    }

    vector_destroy(pvec);
}

void test__vector_insert_n__vector_insert_n_varg__middle_insert_0(void** state)
{
    vector_iterator_t it_pos;
    vector_iterator_t it_iter;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = iterator_next_n(vector_begin(pvec), 300);
    it_iter = _vector_insert_n(pvec, it_pos, 0, 100);
    assert_true(iterator_equal(it_iter, iterator_next_n(vector_begin(pvec), 300)));
    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 0);
    }

    vector_destroy(pvec);
}

void test__vector_insert_n__vector_insert_n_varg__middle_insert_10(void** state)
{
    vector_iterator_t it_pos;
    vector_iterator_t it_iter;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = iterator_next_n(vector_begin(pvec), 300);
    it_iter = _vector_insert_n(pvec, it_pos, 10, 100);
    assert_true(iterator_equal(it_iter, iterator_next_n(vector_begin(pvec), 300)));
    assert_true(vector_size(pvec) == 1010);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        if(i >= 300 && i < 310)
        {
            assert_true(*(int*)vector_at(pvec, i) == 100);
        }
        else
        {
            assert_true(*(int*)vector_at(pvec, i) == 0);
        }
    }

    vector_destroy(pvec);
}

void test__vector_insert_n__vector_insert_n_varg__middle_insert_1000(void** state)
{
    vector_iterator_t it_pos;
    vector_iterator_t it_iter;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = iterator_next_n(vector_begin(pvec), 300);
    it_iter = _vector_insert_n(pvec, it_pos, 1000, 100);
    assert_true(iterator_equal(it_iter, iterator_next_n(vector_begin(pvec), 300)));
    assert_true(vector_size(pvec) == 2000);
    assert_true(vector_capacity(pvec) == 3000);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        if(i >= 300 && i < 1300)
        {
            assert_true(*(int*)vector_at(pvec, i) == 100);
        }
        else
        {
            assert_true(*(int*)vector_at(pvec, i) == 0);
        }
    }

    vector_destroy(pvec);
}

void test__vector_insert_n__vector_insert_n_varg__end_insert_0(void** state)
{
    vector_iterator_t it_pos;
    vector_iterator_t it_iter;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = vector_end(pvec);
    it_iter = _vector_insert_n(pvec, it_pos, 0, 100);
    assert_true(iterator_equal(it_iter, vector_end(pvec)));
    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        assert_true(*(int*)vector_at(pvec, i) == 0);
    }

    vector_destroy(pvec);
}

void test__vector_insert_n__vector_insert_n_varg__end_insert_10(void** state)
{
    vector_iterator_t it_pos;
    vector_iterator_t it_iter;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = vector_end(pvec);
    it_iter = _vector_insert_n(pvec, it_pos, 10, 100);
    assert_true(iterator_equal(it_iter, iterator_next_n(vector_begin(pvec), 1000)));
    assert_true(vector_size(pvec) == 1010);
    assert_true(vector_capacity(pvec) == 1500);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        if(i >= 1000)
        {
            assert_true(*(int*)vector_at(pvec, i) == 100);
        }
        else
        {
            assert_true(*(int*)vector_at(pvec, i) == 0);
        }
    }

    vector_destroy(pvec);
}

void test__vector_insert_n__vector_insert_n_varg__end_insert_1000(void** state)
{
    vector_iterator_t it_pos;
    vector_iterator_t it_iter;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = vector_end(pvec);
    it_iter = _vector_insert_n(pvec, it_pos, 1000, 100);
    assert_true(iterator_equal(it_iter, iterator_next_n(vector_begin(pvec), 1000)));
    assert_true(vector_size(pvec) == 2000);
    assert_true(vector_capacity(pvec) == 3000);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        if(i >= 1000)
        {
            assert_true(*(int*)vector_at(pvec, i) == 100);
        }
        else
        {
            assert_true(*(int*)vector_at(pvec, i) == 0);
        }
    }

    vector_destroy(pvec);
}

void test__vector_insert_n__vector_insert_n_varg__end_insert_1000_multiple(void** state)
{
    vector_iterator_t it_pos;
    vector_iterator_t it_iter;
    size_t i = 0;
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 1000);

    assert_true(vector_size(pvec) == 1000);
    assert_true(vector_capacity(pvec) == 1500);
    it_pos = vector_end(pvec);
    it_iter = _vector_insert_n(pvec, it_pos, 1000, 100, 200, 300, 400, 500);
    assert_true(iterator_equal(it_iter, iterator_next_n(vector_begin(pvec), 1000)));
    assert_true(vector_size(pvec) == 2000);
    assert_true(vector_capacity(pvec) == 3000);
    for(i = 0; i < vector_size(pvec); ++i)
    {
        if(i >= 1000)
        {
            assert_true(*(int*)vector_at(pvec, i) == 100);
        }
        else
        {
            assert_true(*(int*)vector_at(pvec, i) == 0);
        }
    }

    vector_destroy(pvec);
}

/*
 * test _vector_init_elem_auxiliary
 */
UT_CASE_DEFINATION(_vector_init_elem_auxiliary)
void test__vector_init_elem_auxiliary__null_vector_container(void** state)
{
    int elem = 0;
    expect_assert_failure(_vector_init_elem_auxiliary(NULL, &elem));
}

void test__vector_init_elem_auxiliary__null_elem(void** state)
{
    vector_t* pvec = create_vector(int);

    expect_assert_failure(_vector_init_elem_auxiliary(pvec, NULL));

    vector_destroy(pvec);
}

void test__vector_init_elem_auxiliary__non_created_vector(void** state)
{
    int elem = 0;
    vector_t vec;
    vec._pby_start = (_byte_t*)0x78;

    expect_assert_failure(_vector_init_elem_auxiliary(&vec, &elem));
}

void test__vector_init_elem_auxiliary__successfully_int(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init_elem(pvec, 10, 100);

    _vector_init_elem_auxiliary(pvec, pvec->_pby_start);
    assert_true(*(int*)vector_front(pvec) == 0);

    vector_destroy(pvec);
}

void test__vector_init_elem_auxiliary__successfully_cstr(void** state)
{
    string_t elem;
    vector_t* pvec = create_vector(char*);
    vector_init_elem(pvec, 10, "abcdefg");

    _vector_init_elem_auxiliary(pvec, &elem);
    assert_true(strcmp(string_c_str(&elem), "") == 0);

    _string_destroy_auxiliary(&elem);
    vector_destroy(pvec);
}

void test__vector_init_elem_auxiliary__successfully_iterator(void** state)
{
    iterator_t it_iter = _create_vector_iterator();
    vector_t* pvec = create_vector(iterator_t);
    vector_init_elem(pvec, 10, &it_iter);

    _vector_init_elem_auxiliary(pvec, pvec->_pby_start);
    memset(&it_iter, 0x00, sizeof(iterator_t));
    assert_true(memcmp((iterator_t*)vector_front(pvec), &it_iter, sizeof(iterator_t)) == 0);

    vector_destroy(pvec);
}

void test__vector_init_elem_auxiliary__successfully_container(void** state)
{
    vector_t vec;
    vector_t* pvec = create_vector(vector_t<int>);

    _vector_init_elem_auxiliary(pvec, &vec);
    assert_true(vec._pby_start == NULL);
    assert_true(vec._pby_finish == NULL);
    assert_true(vec._pby_endofstorage == NULL);
    assert_true(vec._t_typeinfo._t_style == _TYPE_C_BUILTIN);
    assert_true(vec._t_typeinfo._pt_type != NULL);
    assert_true(strcmp(vec._t_typeinfo._s_typename, _INT_TYPE) == 0);
    assert_true(_alloc_is_inited(&vec._t_allocator));

    vector_destroy(pvec);
}

