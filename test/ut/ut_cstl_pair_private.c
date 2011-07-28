#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_iterator.h"
#include "cstl/cmap.h"
#include "cstl/cstring.h"
#include "cstl/cvector.h"
#include "cstl/cstl_pair_private.h"
#include "cstl/cstl_pair.h"

#include "ut_def.h"
#include "ut_cstl_pair_private.h"

UT_SUIT_DEFINATION(cstl_pair_private, _pair_is_created)
/*
 * test _pair_is_created
 */
UT_CASE_DEFINATION(_pair_is_created)
void test__pair_is_created__null_pair(void** state)
{
    expect_assert_failure(_pair_is_created(NULL));
}

void test__pair_is_created__invalid_first(void** state)
{
    pair_t t_pair;

    t_pair._pv_first = (void*)0x99999;
    t_pair._pv_second = NULL;
    t_pair._t_mapkeycompare = NULL;
    t_pair._t_mapvaluecompare = NULL;
    t_pair._t_typeinfofirst._t_style = _TYPE_C_BUILTIN;
    t_pair._t_typeinfofirst._pt_type = (_type_t*)0x9999; 
    t_pair._t_typeinfosecond._t_style = _TYPE_USER_DEFINE;
    t_pair._t_typeinfosecond._pt_type = (_type_t*)0x8888;
    assert_false(_pair_is_created(&t_pair));
}

void test__pair_is_created__invalid_second(void** state)
{
    pair_t t_pair;

    t_pair._pv_first = NULL;
    t_pair._pv_second = (void*)0x8888;
    t_pair._t_mapkeycompare = NULL;
    t_pair._t_mapvaluecompare = NULL;
    t_pair._t_typeinfofirst._t_style = _TYPE_C_BUILTIN;
    t_pair._t_typeinfofirst._pt_type = (_type_t*)0x9999; 
    t_pair._t_typeinfosecond._t_style = _TYPE_USER_DEFINE;
    t_pair._t_typeinfosecond._pt_type = (_type_t*)0x8888;
    assert_false(_pair_is_created(&t_pair));
}

void test__pair_is_created__invalid_mapkeycompare(void** state)
{
    pair_t t_pair;

    t_pair._pv_first = NULL;
    t_pair._pv_second = NULL;
    t_pair._t_mapkeycompare = (binary_function_t)0x7777;
    t_pair._t_mapvaluecompare = NULL;
    t_pair._t_typeinfofirst._t_style = _TYPE_C_BUILTIN;
    t_pair._t_typeinfofirst._pt_type = (_type_t*)0x9999; 
    t_pair._t_typeinfosecond._t_style = _TYPE_USER_DEFINE;
    t_pair._t_typeinfosecond._pt_type = (_type_t*)0x8888;
    assert_false(_pair_is_created(&t_pair));
}

void test__pair_is_created__invalid_mapvaluecompare(void** state)
{
    pair_t t_pair;

    t_pair._pv_first = NULL;
    t_pair._pv_second = NULL;
    t_pair._t_mapkeycompare = NULL;
    t_pair._t_mapvaluecompare = (binary_function_t)0x8888;
    t_pair._t_typeinfofirst._t_style = _TYPE_C_BUILTIN;
    t_pair._t_typeinfofirst._pt_type = (_type_t*)0x9999; 
    t_pair._t_typeinfosecond._t_style = _TYPE_USER_DEFINE;
    t_pair._t_typeinfosecond._pt_type = (_type_t*)0x8888;
    assert_false(_pair_is_created(&t_pair));
}

void test__pair_is_created__invalid_typeinfofirst_style(void** state)
{
    pair_t t_pair;

    t_pair._pv_first = NULL;
    t_pair._pv_second = NULL;
    t_pair._t_mapkeycompare = NULL;
    t_pair._t_mapvaluecompare = NULL;
    t_pair._t_typeinfofirst._t_style = 837383;
    t_pair._t_typeinfofirst._pt_type = (_type_t*)0x9999; 
    t_pair._t_typeinfosecond._t_style = _TYPE_USER_DEFINE;
    t_pair._t_typeinfosecond._pt_type = (_type_t*)0x8888;
    assert_false(_pair_is_created(&t_pair));
}

void test__pair_is_created__invalid_typeinfofirst_type(void** state)
{
    pair_t t_pair;

    t_pair._pv_first = NULL;
    t_pair._pv_second = NULL;
    t_pair._t_mapkeycompare = NULL;
    t_pair._t_mapvaluecompare = NULL;
    t_pair._t_typeinfofirst._t_style = _TYPE_CSTL_BUILTIN;
    t_pair._t_typeinfofirst._pt_type = NULL;
    t_pair._t_typeinfosecond._t_style = _TYPE_USER_DEFINE;
    t_pair._t_typeinfosecond._pt_type = (_type_t*)0x8888;
    assert_false(_pair_is_created(&t_pair));
}

void test__pair_is_created__invalid_typeinfosecond_style(void** state)
{
    pair_t t_pair;

    t_pair._pv_first = NULL;
    t_pair._pv_second = NULL;
    t_pair._t_mapkeycompare = NULL;
    t_pair._t_mapvaluecompare = NULL;
    t_pair._t_typeinfofirst._t_style = _TYPE_CSTL_BUILTIN;
    t_pair._t_typeinfofirst._pt_type = (_type_t*)0x3333;
    t_pair._t_typeinfosecond._t_style = 9999;
    t_pair._t_typeinfosecond._pt_type = (_type_t*)0x8888;
    assert_false(_pair_is_created(&t_pair));
}

void test__pair_is_created__invalid_typeinfosecond_type(void** state)
{
    pair_t t_pair;

    t_pair._pv_first = NULL;
    t_pair._pv_second = NULL;
    t_pair._t_mapkeycompare = NULL;
    t_pair._t_mapvaluecompare = NULL;
    t_pair._t_typeinfofirst._t_style = _TYPE_CSTL_BUILTIN;
    t_pair._t_typeinfofirst._pt_type = (_type_t*)0x3333;
    t_pair._t_typeinfosecond._t_style = _TYPE_C_BUILTIN;
    t_pair._t_typeinfosecond._pt_type = NULL;
    assert_false(_pair_is_created(&t_pair));
}

void test__pair_is_created__created(void** state)
{
    pair_t* pt_pair = create_pair(int, double);

    assert_true(_pair_is_created(pt_pair));

    pair_destroy(pt_pair);
}


