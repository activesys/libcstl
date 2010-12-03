#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_iterator.h"
#include "cstl/cstl_vector_iterator.h"
#include "cstl/cvector.h"
#include "cstl_vector_aux.h"

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
    assert_true(pvec->_pc_endofstorage == NULL);
    assert_true(pvec->_pc_finish == NULL);
    assert_true(pvec->_pc_start == NULL);
    assert_true(pvec->_t_typeinfo._pt_type != NULL);
    assert_true(pvec->_t_typeinfo._t_style == _TYPE_C_BUILTIN);
    assert_true(strcmp(pvec->_t_typeinfo._sz_typename, _INT_TYPE) == 0);

    vector_destroy(pvec);
}

void test__create_vector_auxiliary__libcstl_builtin_type(void** state)
{
    vector_t* pvec = (vector_t*)malloc(sizeof(vector_t));
    assert_true(pvec != NULL);
    assert_true(_create_vector_auxiliary(pvec, "list_t< int>    "));
    assert_true(pvec->_pc_endofstorage == NULL);
    assert_true(pvec->_pc_finish == NULL);
    assert_true(pvec->_pc_start == NULL);
    assert_true(pvec->_t_typeinfo._pt_type != NULL);
    assert_true(pvec->_t_typeinfo._t_style == _TYPE_CSTL_BUILTIN);
    assert_true(strcmp(pvec->_t_typeinfo._sz_typename, "list_t<int>") == 0);

    vector_destroy(pvec);
}

void test__create_vector_auxiliary__registed_type(void** state)
{
    typedef struct _tag_create_vector_auxiliary__registed_type{int n_elem}_create_vector_auxiliary__registed_type_t;
    vector_t* pvec = (vector_t*)malloc(sizeof(vector_t));
    assert_true(pvec != NULL);
    type_register(_create_vector_auxiliary__registed_type_t, NULL, NULL, NULL, NULL);
    assert_true(_create_vector_auxiliary(pvec, "_create_vector_auxiliary__registed_type_t"));
    assert_true(pvec->_pc_endofstorage == NULL);
    assert_true(pvec->_pc_finish == NULL);
    assert_true(pvec->_pc_start == NULL);
    assert_true(pvec->_t_typeinfo._pt_type != NULL);
    assert_true(pvec->_t_typeinfo._t_style == _TYPE_USER_DEFINE);
    assert_true(strcmp(pvec->_t_typeinfo._sz_typename, "_create_vector_auxiliary__registed_type_t") == 0);

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

void test__vector_init_elem__vector_init_elem_varg__successfully_0_count(void** state)
{
    vector_t* pvec = create_vector(int);

    _vector_init_elem(pvec, 0, 100);
    assert_true(vector_size(pvec) == 0);

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
    vec._pc_finish = (char*)0x00;
    vec._pc_start = (char*)0x08;

    expect_assert_failure(_vector_destroy_auxiliary(&vec));
}

void test__vector_destroy_auxiliary__invalid_vector_container_endofstorage_less_than_start(void** state)
{
    vector_t vec;
    vec._pc_endofstorage = (char*)0x00;
    vec._pc_start = (char*)0x08;
    vec._pc_finish = (char*)0x10;

    expect_assert_failure(_vector_destroy_auxiliary(&vec));
}

void test__vector_destroy_auxiliary__successfully_non_init_container(void** state)
{
    vector_t* pvec = create_vector(int);

    _vector_destroy_auxiliary(pvec);
    assert_true(pvec->_pc_endofstorage == NULL);
    assert_true(pvec->_pc_finish == NULL);
    assert_true(pvec->_pc_start == NULL);

    free(pvec);
}

void test__vector_destroy_auxiliary__successfully_empty_container(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init(pvec);

    _vector_destroy_auxiliary(pvec);
    assert_true(pvec->_pc_endofstorage == NULL);
    assert_true(pvec->_pc_finish == NULL);
    assert_true(pvec->_pc_start == NULL);

    free(pvec);
}

void test__vector_destroy_auxiliary__successfully(void** state)
{
    vector_t* pvec = create_vector(int);
    vector_init_n(pvec, 10);

    _vector_destroy_auxiliary(pvec);
    assert_true(pvec->_pc_endofstorage == NULL);
    assert_true(pvec->_pc_finish == NULL);
    assert_true(pvec->_pc_start == NULL);

    free(pvec);
}

