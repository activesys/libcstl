#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_iterator.h"
#include "cstl/clist.h"
#include "cstl/cvector.h"
#include "cstl/cstl_basic_string_iterator.h"
#include "cstl/cstl_basic_string_private.h"
#include "cstl/cstl_basic_string.h"
#include "cstl_basic_string_aux.h"

#include "ut_def.h"
#include "ut_cstl_basic_string_private.h"

UT_SUIT_DEFINATION(cstl_basic_string_private, _create_basic_string)

/*
 * test _create_basic_string
 */
UT_CASE_DEFINATION(_create_basic_string)

void test__create_basic_string__null_typename(void** state)
{
    expect_assert_failure(_create_basic_string(NULL));
}

void test__create_basic_string__unregisted_type(void** state)
{
    assert_true(_create_basic_string("unregisted_type_t") == NULL);
}

void test__create_basic_string__c_builtin_type(void** state)
{
    basic_string_t* pt_basic_string = _create_basic_string("unsigned int");
    assert_true(pt_basic_string != NULL);
    basic_string_destroy(pt_basic_string);
}

void test__create_basic_string__libcstl_builtin_type(void** state)
{
    basic_string_t* pt_basic_string = _create_basic_string("list_t<int>");
    assert_true(pt_basic_string != NULL);
    basic_string_destroy(pt_basic_string);
}

void test__create_basic_string__registed_type(void** state)
{
    typedef struct _tag__create_basic_string__registed_type{int n_elem;}_create_basic_string__registed_type_t;
    basic_string_t* pt_basic_string = NULL;
    type_register(_create_basic_string__registed_type_t, NULL, NULL, NULL, NULL);
    pt_basic_string = _create_basic_string("_create_basic_string__registed_type_t");
    assert_true(pt_basic_string != NULL);
    basic_string_destroy(pt_basic_string);
}

/*
 * test _create_basic_string_auxiliary
 */
UT_CASE_DEFINATION(_create_basic_string_auxiliary)
void test__create_basic_string_auxiliary__null_basic_string_container(void** state)
{
    expect_assert_failure(_create_basic_string_auxiliary(NULL, "int"));
}

void test__create_basic_string_auxiliary__null_typename(void** state)
{
    basic_string_t bstr;
    expect_assert_failure(_create_basic_string_auxiliary(&bstr, NULL));
}

void test__create_basic_string_auxiliary__unregisted_type(void** state)
{
    basic_string_t bstr;
    assert_false(_create_basic_string_auxiliary(&bstr, "unregisted_type_t"));
}

void test__create_basic_string_auxiliary__c_builtin_type(void** state)
{
    basic_string_t* pt_basic_string = (basic_string_t*)malloc(sizeof(basic_string_t));
    assert_true(pt_basic_string != NULL);
    assert_true(_create_basic_string_auxiliary(pt_basic_string, "int"));
    assert_true(pt_basic_string->_t_vector._pby_endofstorage == NULL);
    assert_true(pt_basic_string->_t_vector._pby_finish == NULL);
    assert_true(pt_basic_string->_t_vector._pby_start == NULL);
    assert_true(pt_basic_string->_t_vector._t_typeinfo._pt_type != NULL);
    assert_true(pt_basic_string->_t_vector._t_typeinfo._t_style == _TYPE_C_BUILTIN);
    assert_true(strcmp(pt_basic_string->_t_vector._t_typeinfo._sz_typename, _INT_TYPE) == 0);

    basic_string_destroy(pt_basic_string);
}

void test__create_basic_string_auxiliary__libcstl_builtin_type(void** state)
{
    basic_string_t* pt_basic_string = (basic_string_t*)malloc(sizeof(basic_string_t));
    assert_true(pt_basic_string != NULL);
    assert_true(_create_basic_string_auxiliary(pt_basic_string, "list_t< int>    "));
    assert_true(pt_basic_string->_t_vector._pby_endofstorage == NULL);
    assert_true(pt_basic_string->_t_vector._pby_finish == NULL);
    assert_true(pt_basic_string->_t_vector._pby_start == NULL);
    assert_true(pt_basic_string->_t_vector._t_typeinfo._pt_type != NULL);
    assert_true(pt_basic_string->_t_vector._t_typeinfo._t_style == _TYPE_CSTL_BUILTIN);
    assert_true(strcmp(pt_basic_string->_t_vector._t_typeinfo._sz_typename, "list_t<int>") == 0);

    basic_string_destroy(pt_basic_string);
}

void test__create_basic_string_auxiliary__registed_type(void** state)
{
    typedef struct _tag_create_basic_string_auxiliary__registed_type{int n_elem;}_create_basic_string_auxiliary__registed_type_t;
    basic_string_t* pt_basic_string = (basic_string_t*)malloc(sizeof(basic_string_t));
    assert_true(pt_basic_string != NULL);
    type_register(_create_basic_string_auxiliary__registed_type_t, NULL, NULL, NULL, NULL);
    assert_true(_create_basic_string_auxiliary(pt_basic_string, "_create_basic_string_auxiliary__registed_type_t"));
    assert_true(pt_basic_string->_t_vector._pby_endofstorage == NULL);
    assert_true(pt_basic_string->_t_vector._pby_finish == NULL);
    assert_true(pt_basic_string->_t_vector._pby_start == NULL);
    assert_true(pt_basic_string->_t_vector._t_typeinfo._pt_type != NULL);
    assert_true(pt_basic_string->_t_vector._t_typeinfo._t_style == _TYPE_USER_DEFINE);
    assert_true(strcmp(pt_basic_string->_t_vector._t_typeinfo._sz_typename,
        "_create_basic_string_auxiliary__registed_type_t") == 0);

    basic_string_destroy(pt_basic_string);
}

/*
 * test _basic_string_init_elem and _basic_string_init_elem_varg
 */
UT_CASE_DEFINATION(_basic_string_init_elem__basic_string_init_elem_varg)
void test__basic_string_init_elem__basic_string_init_elem_varg__null_basic_string_container(void** state)
{
    expect_assert_failure(_basic_string_init_elem(NULL, 10, 100));
}

void test__basic_string_init_elem__basic_string_init_elem_varg__non_created(void** state)
{
    basic_string_t bstr;
    bstr._t_vector._pby_start = (_byte_t*)0x89;

    expect_assert_failure(_basic_string_init_elem(&bstr, 10, 100));
}

void test__basic_string_init_elem__basic_string_init_elem_varg__successfully_0_count(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);

    _basic_string_init_elem(pt_basic_string, 0, 100);
    assert_true(basic_string_size(pt_basic_string) == 0);
    assert_true(basic_string_capacity(pt_basic_string) == 0);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_init_elem__basic_string_init_elem_varg__successfully(void** state)
{
    size_t i = 0;
    basic_string_t* pt_basic_string = create_basic_string(int);

    _basic_string_init_elem(pt_basic_string, 8, 100);
    assert_true(basic_string_size(pt_basic_string) == 8);
    for(i = 0; i < basic_string_size(pt_basic_string); ++i)
    {
        assert_true(*(int*)basic_string_at(pt_basic_string, i) == 100);
    }
    assert_true(basic_string_capacity(pt_basic_string) == 24);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_init_elem__basic_string_init_elem_varg__successfully_large_amounts_of_data(void** state)
{
    size_t i = 0;
    basic_string_t* pt_basic_string = create_basic_string(int);

    _basic_string_init_elem(pt_basic_string, 800, 100);
    assert_true(basic_string_size(pt_basic_string) == 800);
    for(i = 0; i < basic_string_size(pt_basic_string); ++i)
    {
        assert_true(*(int*)basic_string_at(pt_basic_string, i) == 100);
    }
    assert_true(basic_string_capacity(pt_basic_string) == 1200);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_init_elem__basic_string_init_elem_varg__successfully_multiple_specificed_element(void** state)
{
    size_t i = 0;
    basic_string_t* pt_basic_string = create_basic_string(int);

    _basic_string_init_elem(pt_basic_string, 8, 100, 200, 300, 400);
    assert_true(basic_string_size(pt_basic_string) == 8);
    for(i = 0; i < basic_string_size(pt_basic_string); ++i)
    {
        assert_true(*(int*)basic_string_at(pt_basic_string, i) == 100);
    }
    assert_true(basic_string_capacity(pt_basic_string) == 24);

    basic_string_destroy(pt_basic_string);
}

/*
 * test _basic_string_destroy_auxiliary
 */
UT_CASE_DEFINATION(_basic_string_destroy_auxiliary)
void test__basic_string_destroy_auxiliary__null_basic_string_container(void** state)
{
    expect_assert_failure(_basic_string_destroy_auxiliary(NULL));
}

void test__basic_string_destroy_auxiliary__invalid_basic_string_container_finish_less_than_start(void** state)
{
    basic_string_t bstr;
    bstr._t_vector._pby_finish = (_byte_t*)0x00;
    bstr._t_vector._pby_start = (_byte_t*)0x08;

    expect_assert_failure(_basic_string_destroy_auxiliary(&bstr));
}

void test__basic_string_destroy_auxiliary__invalid_basic_string_container_endofstorage_less_than_start(void** state)
{
    basic_string_t bstr;
    bstr._t_vector._pby_endofstorage = (_byte_t*)0x00;
    bstr._t_vector._pby_start = (_byte_t*)0x08;
    bstr._t_vector._pby_finish = (_byte_t*)0x10;

    expect_assert_failure(_basic_string_destroy_auxiliary(&bstr));
}

void test__basic_string_destroy_auxiliary__successfully_non_init_container(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);

    _basic_string_destroy_auxiliary(pt_basic_string);
    assert_true(pt_basic_string->_t_vector._pby_endofstorage == NULL);
    assert_true(pt_basic_string->_t_vector._pby_finish == NULL);
    assert_true(pt_basic_string->_t_vector._pby_start == NULL);

    free(pt_basic_string);
}

void test__basic_string_destroy_auxiliary__successfully_empty_container(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);

    _basic_string_destroy_auxiliary(pt_basic_string);
    assert_true(pt_basic_string->_t_vector._pby_endofstorage == NULL);
    assert_true(pt_basic_string->_t_vector._pby_finish == NULL);
    assert_true(pt_basic_string->_t_vector._pby_start == NULL);

    free(pt_basic_string);
}

void test__basic_string_destroy_auxiliary__successfully(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init_elem(pt_basic_string, 10, 100);

    _basic_string_destroy_auxiliary(pt_basic_string);
    assert_true(pt_basic_string->_t_vector._pby_endofstorage == NULL);
    assert_true(pt_basic_string->_t_vector._pby_finish == NULL);
    assert_true(pt_basic_string->_t_vector._pby_start == NULL);

    free(pt_basic_string);
}

/*
 * test _basic_string_find_elem and _basic_string_find_elem_varg
 */
UT_CASE_DEFINATION(_basic_string_find_elem__basic_string_find_elem_varg)

void test__basic_string_find_elem__basic_string_find_elem_varg__null_basic_string_container(void** state)
{
    expect_assert_failure(_basic_string_find_elem(NULL, 0, 2323));
}

void test__basic_string_find_elem__basic_string_find_elem_varg__non_init_basic_string_container(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);

    pt_basic_string->_t_vector._t_typeinfo._t_style = 23423;
    expect_assert_failure(_basic_string_find_elem(pt_basic_string, 0, 111));

    pt_basic_string->_t_vector._t_typeinfo._t_style = _TYPE_C_BUILTIN;
    basic_string_destroy(pt_basic_string);
}

void test__basic_string_find_elem__basic_string_find_elem_varg__invalid_position(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);

    basic_string_init_elem(pt_basic_string, 10, 100);
    assert_true(_basic_string_find_elem(pt_basic_string, 34456, 100) == NPOS);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_find_elem__basic_string_find_elem_varg__invalid_position_end(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);

    basic_string_init_elem(pt_basic_string, 10, 100);
    assert_true(_basic_string_find_elem(pt_basic_string, basic_string_size(pt_basic_string), 100) == NPOS);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_find_elem__basic_string_find_elem_varg__invalid_position_NPOS(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);

    basic_string_init_elem(pt_basic_string, 10, 100);
    assert_true(_basic_string_find_elem(pt_basic_string, NPOS, 100) == NPOS);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_find_elem__basic_string_find_elem_varg__find_failure(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);

    basic_string_init_elem(pt_basic_string, 10, 100);
    assert_true(_basic_string_find_elem(pt_basic_string, 0, 9999) == NPOS);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_find_elem__basic_string_find_elem_varg__find_failure_middle_pos(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);

    basic_string_init_elem(pt_basic_string, 1, 9999);
    basic_string_push_back(pt_basic_string, 100);
    basic_string_push_back(pt_basic_string, 100);
    basic_string_push_back(pt_basic_string, 100);
    basic_string_push_back(pt_basic_string, 100);
    basic_string_push_back(pt_basic_string, 100);
    basic_string_push_back(pt_basic_string, 100);
    assert_true(_basic_string_find_elem(pt_basic_string, 3, 9999) == NPOS);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_find_elem__basic_string_find_elem_varg__find_successful(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);

    basic_string_init(pt_basic_string);
    basic_string_push_back(pt_basic_string, 97);
    basic_string_push_back(pt_basic_string, 400);
    basic_string_push_back(pt_basic_string, 97);
    basic_string_push_back(pt_basic_string, -3);
    basic_string_push_back(pt_basic_string, 97);
    basic_string_push_back(pt_basic_string, 700);
    assert_true(_basic_string_find_elem(pt_basic_string, 0, 97) == 0);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_find_elem__basic_string_find_elem_varg__find_successful_middle(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);

    basic_string_init(pt_basic_string);
    basic_string_push_back(pt_basic_string, 47);
    basic_string_push_back(pt_basic_string, 400);
    basic_string_push_back(pt_basic_string, 97);
    basic_string_push_back(pt_basic_string, -3);
    basic_string_push_back(pt_basic_string, 97);
    basic_string_push_back(pt_basic_string, 700);
    assert_true(_basic_string_find_elem(pt_basic_string, 0, 97) == 2);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_find_elem__basic_string_find_elem_varg__find_successful_back(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);

    basic_string_init(pt_basic_string);
    basic_string_push_back(pt_basic_string, 47);
    basic_string_push_back(pt_basic_string, 400);
    basic_string_push_back(pt_basic_string, 7);
    basic_string_push_back(pt_basic_string, -3);
    basic_string_push_back(pt_basic_string, 97);
    assert_true(_basic_string_find_elem(pt_basic_string, 0, 97) == 4);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_find_elem__basic_string_find_elem_varg__find_successful_middle_pos(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);

    basic_string_init(pt_basic_string);
    basic_string_push_back(pt_basic_string, 47);
    basic_string_push_back(pt_basic_string, 400);
    basic_string_push_back(pt_basic_string, 97);
    basic_string_push_back(pt_basic_string, -3);
    basic_string_push_back(pt_basic_string, 97);
    basic_string_push_back(pt_basic_string, 700);
    assert_true(_basic_string_find_elem(pt_basic_string, 3, 97) == 4);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_find_elem__basic_string_find_elem_varg__cstr_find_failure(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);

    basic_string_init_elem(pt_basic_string, 10, "100");
    assert_true(_basic_string_find_elem(pt_basic_string, 0, "9999") == NPOS);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_find_elem__basic_string_find_elem_varg__cstr_find_failure_middle_pos(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);

    basic_string_init_elem(pt_basic_string, 1, "9999");
    basic_string_push_back(pt_basic_string, "100");
    basic_string_push_back(pt_basic_string, "100");
    basic_string_push_back(pt_basic_string, "100");
    basic_string_push_back(pt_basic_string, "100");
    basic_string_push_back(pt_basic_string, "100");
    basic_string_push_back(pt_basic_string, "100");
    assert_true(_basic_string_find_elem(pt_basic_string, 3, "9999") == NPOS);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_find_elem__basic_string_find_elem_varg__cstr_find_successful(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);

    basic_string_init(pt_basic_string);
    basic_string_push_back(pt_basic_string, "97");
    basic_string_push_back(pt_basic_string, "400");
    basic_string_push_back(pt_basic_string, "97");
    basic_string_push_back(pt_basic_string, "-3");
    basic_string_push_back(pt_basic_string, "97");
    basic_string_push_back(pt_basic_string, "700");
    assert_true(_basic_string_find_elem(pt_basic_string, 0, "97") == 0);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_find_elem__basic_string_find_elem_varg__cstr_find_successful_middle(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);

    basic_string_init(pt_basic_string);
    basic_string_push_back(pt_basic_string, "47");
    basic_string_push_back(pt_basic_string, "400");
    basic_string_push_back(pt_basic_string, "97");
    basic_string_push_back(pt_basic_string, "-3");
    basic_string_push_back(pt_basic_string, "97");
    basic_string_push_back(pt_basic_string, "700");
    assert_true(_basic_string_find_elem(pt_basic_string, 0, "97") == 2);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_find_elem__basic_string_find_elem_varg__cstr_find_successful_back(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);

    basic_string_init(pt_basic_string);
    basic_string_push_back(pt_basic_string, "47");
    basic_string_push_back(pt_basic_string, "400");
    basic_string_push_back(pt_basic_string, "7");
    basic_string_push_back(pt_basic_string, "-3");
    basic_string_push_back(pt_basic_string, "97");
    assert_true(_basic_string_find_elem(pt_basic_string, 0, "97") == 4);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_find_elem__basic_string_find_elem_varg__cstr_find_successful_middle_pos(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);

    basic_string_init(pt_basic_string);
    basic_string_push_back(pt_basic_string, "47");
    basic_string_push_back(pt_basic_string, "400");
    basic_string_push_back(pt_basic_string, "97");
    basic_string_push_back(pt_basic_string, "-3");
    basic_string_push_back(pt_basic_string, "97");
    basic_string_push_back(pt_basic_string, "700");
    assert_true(_basic_string_find_elem(pt_basic_string, 3, "97") == 4);

    basic_string_destroy(pt_basic_string);
}

