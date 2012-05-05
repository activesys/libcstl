#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
#include "cstl/clist.h"
#include "cstl/cvector.h"
#include "cstl/cstl_basic_string_iterator.h"
#include "cstl/cstl_basic_string_private.h"
#include "cstl/cstl_basic_string.h"
#include "cstl/cstl_string_iterator.h"
#include "cstl/cstl_string_private.h"
#include "cstl/cstl_string.h"

#include "ut_def.h"
#include "ut_cstl_string_private.h"

UT_SUIT_DEFINATION(cstl_string_private, _create_string_auxiliary)

/*
 * test _create_string_auxiliary
 */
UT_CASE_DEFINATION(_create_string_auxiliary)
void test__create_string_auxiliary__null_string_container(void** state)
{
    expect_assert_failure(_create_string_auxiliary(NULL));
}

void test__create_string_auxiliary__successfully(void** state)
{
    string_t* pstr = (string_t*)malloc(sizeof(string_t));
    assert_true(pstr != NULL);
    assert_true(_create_string_auxiliary(pstr));
    assert_true(pstr->_vec_base._pby_endofstorage == NULL);
    assert_true(pstr->_vec_base._pby_finish == NULL);
    assert_true(pstr->_vec_base._pby_start == NULL);
    assert_true(pstr->_vec_base._t_typeinfo._pt_type != NULL);
    assert_true(pstr->_vec_base._t_typeinfo._t_style == _TYPE_C_BUILTIN);
    assert_true(strcmp(pstr->_vec_base._t_typeinfo._s_typename, _CHAR_TYPE) == 0);

    string_destroy(pstr);
}

/*
 * test _string_destroy_auxiliary
 */
UT_CASE_DEFINATION(_string_destroy_auxiliary)
void test__string_destroy_auxiliary__null_string_container(void** state)
{
    expect_assert_failure(_string_destroy_auxiliary(NULL));
}

void test__string_destroy_auxiliary__invalid_string_container_finish_less_than_start(void** state)
{
    string_t bstr;
    bstr._vec_base._pby_finish = (_byte_t*)0x00;
    bstr._vec_base._pby_start = (_byte_t*)0x08;

    expect_assert_failure(_string_destroy_auxiliary(&bstr));
}

void test__string_destroy_auxiliary__invalid_string_container_endofstorage_less_than_start(void** state)
{
    string_t bstr;
    bstr._vec_base._pby_endofstorage = (_byte_t*)0x00;
    bstr._vec_base._pby_start = (_byte_t*)0x08;
    bstr._vec_base._pby_finish = (_byte_t*)0x10;

    expect_assert_failure(_string_destroy_auxiliary(&bstr));
}

void test__string_destroy_auxiliary__successfully_non_init_container(void** state)
{
    string_t* pt_string = create_string();

    _string_destroy_auxiliary(pt_string);
    assert_true(pt_string->_vec_base._pby_endofstorage == NULL);
    assert_true(pt_string->_vec_base._pby_finish == NULL);
    assert_true(pt_string->_vec_base._pby_start == NULL);

    free(pt_string);
}

void test__string_destroy_auxiliary__successfully_empty_container(void** state)
{
    string_t* pt_string = create_string();
    string_init(pt_string);

    _string_destroy_auxiliary(pt_string);
    assert_true(pt_string->_vec_base._pby_endofstorage == NULL);
    assert_true(pt_string->_vec_base._pby_finish == NULL);
    assert_true(pt_string->_vec_base._pby_start == NULL);

    free(pt_string);
}

void test__string_destroy_auxiliary__successfully(void** state)
{
    string_t* pt_string = create_string();
    string_init_char(pt_string, 10, 'a');

    _string_destroy_auxiliary(pt_string);
    assert_true(pt_string->_vec_base._pby_endofstorage == NULL);
    assert_true(pt_string->_vec_base._pby_finish == NULL);
    assert_true(pt_string->_vec_base._pby_start == NULL);

    free(pt_string);
}

