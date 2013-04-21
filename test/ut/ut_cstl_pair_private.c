#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/citerator.h"
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
    t_pair._bfun_mapkeycompare = NULL;
    t_pair._bfun_mapvaluecompare = NULL;
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
    t_pair._bfun_mapkeycompare = NULL;
    t_pair._bfun_mapvaluecompare = NULL;
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
    t_pair._bfun_mapkeycompare = (binary_function_t)0x7777;
    t_pair._bfun_mapvaluecompare = NULL;
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
    t_pair._bfun_mapkeycompare = NULL;
    t_pair._bfun_mapvaluecompare = (binary_function_t)0x8888;
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
    t_pair._bfun_mapkeycompare = NULL;
    t_pair._bfun_mapvaluecompare = NULL;
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
    t_pair._bfun_mapkeycompare = NULL;
    t_pair._bfun_mapvaluecompare = NULL;
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
    t_pair._bfun_mapkeycompare = NULL;
    t_pair._bfun_mapvaluecompare = NULL;
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
    t_pair._bfun_mapkeycompare = NULL;
    t_pair._bfun_mapvaluecompare = NULL;
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

/*
 * test _pair_is_inited
 */
UT_CASE_DEFINATION(_pair_is_inited)
void test__pair_is_inited__null_pair(void** state)
{
    expect_assert_failure(_pair_is_inited(NULL));
}

void test__pair_is_inited__null_pair_first(void** state)
{
    pair_t* ppair = create_pair(int, double);
    void* ptemp = NULL;

    pair_init(ppair);
    ptemp = ppair->_pv_first;
    ppair->_pv_first = NULL;

    assert_false(_pair_is_inited(ppair));

    ppair->_pv_first = ptemp;
    pair_destroy(ppair);
}

void test__pair_is_inited__null_pair_second(void** state)
{
    pair_t* ppair = create_pair(int, double);
    void* ptemp = NULL;

    pair_init(ppair);
    ptemp = ppair->_pv_second;
    ppair->_pv_second = NULL;

    assert_false(_pair_is_inited(ppair));

    ppair->_pv_second = ptemp;
    pair_destroy(ppair);
}

void test__pair_is_inited__invalid_typeinfofirst_style(void** state)
{
    pair_t* ppair = create_pair(int, double);

    pair_init(ppair);
    ppair->_t_typeinfofirst._t_style = 99999;
    assert_false(_pair_is_inited(ppair));
    ppair->_t_typeinfofirst._t_style = _TYPE_C_BUILTIN;

    pair_destroy(ppair);
}

void test__pair_is_inited__invalid_typeinfofirst_type(void** state)
{
    pair_t* ppair = create_pair(int, double);
    _type_t* ptype = NULL;

    pair_init(ppair);
    ptype = ppair->_t_typeinfofirst._pt_type;
    ppair->_t_typeinfofirst._pt_type = NULL;
    assert_false(_pair_is_inited(ppair));
    ppair->_t_typeinfofirst._pt_type = ptype;

    pair_destroy(ppair);
}

void test__pair_is_inited__invalid_typeinfosecond_style(void** state)
{
    pair_t* ppair = create_pair(int, double);

    pair_init(ppair);
    ppair->_t_typeinfosecond._t_style = 99999;
    assert_false(_pair_is_inited(ppair));
    ppair->_t_typeinfosecond._t_style = _TYPE_C_BUILTIN;

    pair_destroy(ppair);
}

void test__pair_is_inited__invalid_typeinfosecond_type(void** state)
{
    pair_t* ppair = create_pair(int, double);
    _type_t* ptype = NULL;

    pair_init(ppair);
    ptype = ppair->_t_typeinfosecond._pt_type;
    ppair->_t_typeinfosecond._pt_type = NULL;
    assert_false(_pair_is_inited(ppair));
    ppair->_t_typeinfosecond._pt_type = ptype;

    pair_destroy(ppair);
}

/*
 * test _create_pair
 */
UT_CASE_DEFINATION(_create_pair)
void test__create_pair__null_typename(void** state)
{
    expect_assert_failure(_create_pair(NULL));
}

void test__create_pair__c_builtin(void** state)
{
    pair_t* pt_pair = _create_pair("double, unsigned");
    assert_true(pt_pair != NULL);
    assert_true(_pair_is_created(pt_pair));

    pair_destroy(pt_pair);
}

void test__create_pair__cstr(void** state)
{
    pair_t* pt_pair = _create_pair("char*, char*");
    assert_true(pt_pair != NULL);
    assert_true(_pair_is_created(pt_pair));

    pair_destroy(pt_pair);
}

void test__create_pair__libcstl_builtin(void** state)
{
    pair_t* pt_pair = _create_pair("vector_t<int>, list_t<double>");
    assert_true(pt_pair != NULL);
    assert_true(_pair_is_created(pt_pair));

    pair_destroy(pt_pair);
}

typedef struct _test_test__create_pair__user_define
{
    int n_elem;
}_test__create_pair__user_define_t;

void test__create_pair__user_define(void** state)
{
    pair_t* pt_pair = NULL;

    type_register(_test__create_pair__user_define_t, NULL, NULL, NULL, NULL);
    type_duplicate(_test__create_pair__user_define_t, struct _test_test__create_pair__user_define);
    pt_pair = _create_pair("_test__create_pair__user_define_t, struct _test_test__create_pair__user_define");
    assert_true(pt_pair != NULL);
    assert_true(_pair_is_created(pt_pair));

    pair_destroy(pt_pair);
}

void test__create_pair__unregister(void** state)
{
    pair_t* pt_pair = _create_pair("test__create_pair__unregister_t, test__create_pair__unregister_other_t");
    assert_true(pt_pair == NULL);
}

void test__create_pair__invalid(void** state)
{
    pair_t* pt_pair = _create_pair("int");
    assert_true(pt_pair == NULL);
}

/*
 * test _create_pair_auxiliary
 */
UT_CASE_DEFINATION(_create_pair_auxiliary)
void test__create_pair_auxiliary__null_pair(void** state)
{
    expect_assert_failure(_create_pair_auxiliary(NULL, "int"));
}

void test__create_pair_auxiliary__null_typename(void** state)
{
    pair_t t_pair;
    expect_assert_failure(_create_pair_auxiliary(&t_pair, NULL));
}

void test__create_pair_auxiliary__unregistered(void** state)
{
    pair_t* pt_pair = malloc(sizeof(pair_t));
    assert_false(_create_pair_auxiliary(pt_pair, "_test__create_pair_auxiliary__unregistered_t"));

    free(pt_pair);
}

void test__create_pair_auxiliary__c_builtin(void** state)
{
    pair_t* pt_pair = malloc(sizeof(pair_t));
    assert_true(_create_pair_auxiliary(pt_pair, "int, int"));
    assert_true(pt_pair != NULL);

    pair_destroy(pt_pair);
}

void test__create_pair_auxiliary__cstr(void** state)
{
    pair_t* pt_pair = malloc(sizeof(pair_t));
    assert_true(_create_pair_auxiliary(pt_pair, "char*, char  *"));
    assert_true(pt_pair != NULL);

    pair_destroy(pt_pair);
}

void test__create_pair_auxiliary__libcstl_builtin(void** state)
{
    pair_t* pt_pair = malloc(sizeof(pair_t));
    assert_true(_create_pair_auxiliary(pt_pair, "vector_t<int>, map_t<int, list_t<double>>"));
    assert_true(pt_pair != NULL);

    pair_destroy(pt_pair);
}

typedef struct _tag_test__create_pair_auxiliary__user_define
{
    int n_elem;
}_test__create_pair_auxiliary__user_define_t;

void test__create_pair_auxiliary__user_define(void** state)
{
    pair_t* pt_pair = NULL;

    type_register(_test__create_pair_auxiliary__user_define_t, NULL, NULL, NULL, NULL);
    type_duplicate(_test__create_pair_auxiliary__user_define_t, struct _tag_test__create_pair_auxiliary__user_define);

    pt_pair = malloc(sizeof(pair_t));
    assert_true(_create_pair_auxiliary(pt_pair, "_test__create_pair_auxiliary__user_define_t, struct _tag_test__create_pair_auxiliary__user_define"));
    assert_true(pt_pair != NULL);

    pair_destroy(pt_pair);
}

/*
 * test _pair_destroy_auxiliary
 */
UT_CASE_DEFINATION(_pair_destroy_auxiliary)
void test__pair_destroy_auxiliary__null_pair(void** state)
{
    expect_assert_failure(_pair_destroy_auxiliary(NULL));
}

void test__pair_destroy_auxiliary__non_created(void** state)
{
    pair_t* pt_pair = _create_pair("int, double");

    pt_pair->_t_typeinfofirst._t_style = 999;
    expect_assert_failure(_pair_destroy_auxiliary(pt_pair));
    pt_pair->_t_typeinfofirst._t_style = _TYPE_C_BUILTIN;

    pair_destroy(pt_pair);
}

void test__pair_destroy_auxiliary__non_inited(void** state)
{
    pair_t* pt_pair = _create_pair("int, int");
    pair_init(pt_pair);

    pt_pair->_t_typeinfosecond._t_style = 2222;
    expect_assert_failure(_pair_destroy_auxiliary(pt_pair));
    pt_pair->_t_typeinfosecond._t_style = _TYPE_C_BUILTIN;

    pair_destroy(pt_pair);
}

void test__pair_destroy_auxiliary__empty(void** state)
{
    pair_t* pt_pair = _create_pair("int, double");
    pair_init(pt_pair);

    _pair_destroy_auxiliary(pt_pair);
    assert_true(pt_pair->_pv_first == NULL);
    assert_true(pt_pair->_pv_second == NULL);
    assert_true(pt_pair->_bfun_mapkeycompare == NULL);
    assert_true(pt_pair->_bfun_mapvaluecompare == NULL);
    free(pt_pair);
}

void test__pair_destroy_auxiliary__non_empty(void** state)
{
    pair_t* pt_pair = _create_pair("int, int");
    pair_init_elem(pt_pair, 9, 22);

    _pair_destroy_auxiliary(pt_pair);
    assert_true(pt_pair->_pv_first == NULL);
    assert_true(pt_pair->_pv_second == NULL);
    assert_true(pt_pair->_bfun_mapkeycompare == NULL);
    assert_true(pt_pair->_bfun_mapvaluecompare == NULL);
    free(pt_pair);
}

void test__pair_destroy_auxiliary__created_not_inited(void** state)
{
    pair_t* pt_pair = create_pair(int, int);

    _pair_destroy_auxiliary(pt_pair);
    assert_true(pt_pair->_pv_first == NULL);
    assert_true(pt_pair->_pv_second == NULL);
    assert_true(pt_pair->_bfun_mapkeycompare == NULL);
    assert_true(pt_pair->_bfun_mapvaluecompare == NULL);
    free(pt_pair);
}

/*
 * test _pair_make_first
 */
UT_CASE_DEFINATION(_pair_make_first)
void test__pair_make_first__null_pair(void** state)
{
    expect_assert_failure(_pair_make_first(NULL));
}

void test__pair_make_first__non_inited(void** state)
{
    pair_t* ppair = create_pair(int, int);

    expect_assert_failure(_pair_make_first(ppair));

    pair_destroy(ppair);
}

void test__pair_make_first__c_builtin(void** state)
{
    pair_t* ppair = create_pair(int, int);
    pair_init(ppair);

    assert_true(*(int*)pair_first(ppair) == 0);
    assert_true(*(int*)pair_second(ppair) == 0);
    _pair_make_first(ppair, 9);
    assert_true(*(int*)pair_first(ppair) == 9);
    assert_true(*(int*)pair_second(ppair) == 0);

    pair_destroy(ppair);
}

void test__pair_make_first__str(void** state)
{
    pair_t* ppair = create_pair(char*, int);
    pair_init(ppair);

    assert_true(strcmp((char*)pair_first(ppair), "") == 0);
    assert_true(*(int*)pair_second(ppair) == 0);
    _pair_make_first(ppair, "abcdefg");
    assert_true(strcmp((char*)pair_first(ppair), "abcdefg") == 0);
    assert_true(*(int*)pair_second(ppair) == 0);

    pair_destroy(ppair);
}

void test__pair_make_first__libcstl_builtin(void** state)
{
    pair_t* ppair = create_pair(vector_t<int>, int);
    vector_t* pvec = create_vector(int);
    pair_init(ppair);
    vector_init(pvec);

    assert_true(vector_empty((vector_t*)pair_first(ppair)));
    assert_true(*(int*)pair_second(ppair) == 0);

    vector_push_back(pvec, 100);
    _pair_make_first(ppair, pvec);
    assert_true(vector_size((vector_t*)pair_first(ppair)) == 1);
    assert_true(*(int*)vector_front((vector_t*)pair_first(ppair)) == 100);
    assert_true(*(int*)pair_second(ppair) == 0);

    pair_destroy(ppair);
    vector_destroy(pvec);
}

typedef struct _tag_test__pair_make_first__user_define
{
    int n_elem;
}_test__pair_make_first__user_define_t;

void test__pair_make_first__user_define(void** state)
{
    pair_t* ppair = NULL;
    _test__pair_make_first__user_define_t t_elem;

    type_register(_test__pair_make_first__user_define_t, NULL, NULL, NULL, NULL);
    ppair = create_pair(_test__pair_make_first__user_define_t, int);
    pair_init(ppair);

    assert_true(((_test__pair_make_first__user_define_t*)pair_first(ppair))->n_elem == 0);
    assert_true(*(int*)pair_second(ppair) == 0);
    t_elem.n_elem = 100;
    _pair_make_first(ppair, &t_elem);
    assert_true(((_test__pair_make_first__user_define_t*)pair_first(ppair))->n_elem == 100);
    assert_true(*(int*)pair_second(ppair) == 0);

    pair_destroy(ppair);
}

/*
 * test _pair_make_second
 */
UT_CASE_DEFINATION(_pair_make_second)
void test__pair_make_second__null_pair(void** state)
{
    expect_assert_failure(_pair_make_second(NULL));
}

void test__pair_make_second__non_inited(void** state)
{
    pair_t* ppair = create_pair(int, int);

    expect_assert_failure(_pair_make_second(ppair));

    pair_destroy(ppair);
}

void test__pair_make_second__c_builtin(void** state)
{
    pair_t* ppair = create_pair(int, int);
    pair_init(ppair);

    assert_true(*(int*)pair_first(ppair) == 0);
    assert_true(*(int*)pair_second(ppair) == 0);
    _pair_make_second(ppair, 9);
    assert_true(*(int*)pair_first(ppair) == 0);
    assert_true(*(int*)pair_second(ppair) == 9);

    pair_destroy(ppair);
}

void test__pair_make_second__str(void** state)
{
    pair_t* ppair = create_pair(int, char*);
    pair_init(ppair);

    assert_true(*(int*)pair_first(ppair) == 0);
    assert_true(strcmp((char*)pair_second(ppair), "") == 0);
    _pair_make_second(ppair, "abcdefg");
    assert_true(*(int*)pair_first(ppair) == 0);
    assert_true(strcmp((char*)pair_second(ppair), "abcdefg") == 0);

    pair_destroy(ppair);
}

void test__pair_make_second__libcstl_builtin(void** state)
{
    pair_t* ppair = create_pair(int, vector_t<int>);
    vector_t* pvec = create_vector(int);
    pair_init(ppair);
    vector_init(pvec);

    assert_true(*(int*)pair_first(ppair) == 0);
    assert_true(vector_empty((vector_t*)pair_second(ppair)));

    vector_push_back(pvec, 100);
    _pair_make_second(ppair, pvec);
    assert_true(vector_size((vector_t*)pair_second(ppair)) == 1);
    assert_true(*(int*)vector_front((vector_t*)pair_second(ppair)) == 100);
    assert_true(*(int*)pair_first(ppair) == 0);

    pair_destroy(ppair);
    vector_destroy(pvec);
}

typedef struct _tag_test__pair_make_second__user_define
{
    int n_elem;
}_test__pair_make_second__user_define_t;

void test__pair_make_second__user_define(void** state)
{
    pair_t* ppair = NULL;
    _test__pair_make_second__user_define_t t_elem;

    type_register(_test__pair_make_second__user_define_t, NULL, NULL, NULL, NULL);
    ppair = create_pair(int, _test__pair_make_second__user_define_t);
    pair_init(ppair);

    assert_true(((_test__pair_make_second__user_define_t*)pair_second(ppair))->n_elem == 0);
    assert_true(*(int*)pair_first(ppair) == 0);
    t_elem.n_elem = 100;
    _pair_make_second(ppair, &t_elem);
    assert_true(((_test__pair_make_second__user_define_t*)pair_second(ppair))->n_elem == 100);
    assert_true(*(int*)pair_first(ppair) == 0);

    pair_destroy(ppair);
}

