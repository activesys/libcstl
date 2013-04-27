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
#include "cstl_basic_string_aux.h"

#include "ut_def.h"
#include "ut_cstl_basic_string_aux.h"

UT_SUIT_DEFINATION(cstl_basic_string_aux, _basic_string_is_created)

/*
 * test _basic_string_is_created
 */
UT_CASE_DEFINATION(_basic_string_is_created)
void test__basic_string_is_created__null_basic_string_container(void** state)
{
    expect_assert_failure(_basic_string_is_created(NULL));
}

void test__basic_string_is_created__non_created_invalid_pby_string(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    pbstr->_pby_string = 0xff;
    assert_false(_basic_string_is_created(&pbstr));
    pbstr->_pby_string = NULL;
    basic_string_destroy(pbstr);
}

void test__basic_string_is_created__non_created_invalid_type_style(void** state)
{
    basic_string_t bstr;
    bstr._t_typeinfo._t_style = 100;
    bstr._pby_string = NULL;
    assert_false(_basic_string_is_created(&bstr));
}

void test__basic_string_is_created__created(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);

    assert_true(_basic_string_is_created(pbstr));

    basic_string_destroy(pbstr);
}

/*
 * test _basic_string_is_inited
 */
UT_CASE_DEFINATION(_basic_string_is_inited)
void test__basic_string_is_inited__null_basic_string_container(void** state)
{
    expect_assert_failure(_basic_string_is_inited(NULL));
}

void test__basic_string_is_inited__non_inited_pby_string_null(void** state)
{
    _byte_t* pby_data = NULL;
    basic_string_t* pbstr = create_basic_string(int);
    basic_string_init(pbstr);
    pby_data = pbstr->_pby_string;
    pbstr->_pby_string = NULL;
    assert_false(_basic_string_is_inited(pbstr));
    pbstr->_pby_string = pby_data;
    basic_string_destroy(pbstr);
}

void test__basic_string_is_inited__non_inited_leaked(void** state)
{
    _basic_string_rep_t* prep = NULL;
    basic_string_t* pbstr = create_basic_string(int);
    basic_string_init(pbstr);
    prep = _basic_string_rep_get_representation(pbstr->_pby_string);
    prep->_n_refcount = -1;
    assert_false(_basic_string_is_inited(pbstr));
    prep->_n_refcount = 0;
    basic_string_destroy(pbstr);
}

void test__basic_string_is_inited__non_inited_invalid_type_style(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    basic_string_init(pbstr);
    pbstr->_t_typeinfo._t_style = 100;
    assert_false(_basic_string_is_inited(pbstr));
    pbstr->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    basic_string_destroy(pbstr);
}

void test__basic_string_is_inited__inited_empty(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    basic_string_init(pbstr);

    assert_true(_basic_string_is_inited(pbstr));

    basic_string_destroy(pbstr);
}

void test__basic_string_is_inited__inited_non_empty(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    basic_string_init_elem(pbstr, 10, 100);

    assert_true(_basic_string_is_inited(pbstr));

    basic_string_destroy(pbstr);
}


/*
 * test _basic_string_same_type
 */
UT_CASE_DEFINATION(_basic_string_same_type)
void test__basic_string_same_type__null_first(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);

    expect_assert_failure(_basic_string_same_type(NULL, pt_basic_string));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_same_type__null_second(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);

    expect_assert_failure(_basic_string_same_type(pt_basic_string, NULL));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_same_type__non_created_first(void** state)
{
    basic_string_t bstring;
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);

    bstring._t_typeinfo._t_style = 100;
    expect_assert_failure(_basic_string_same_type(&bstring, pt_basic_string));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_same_type__non_created_second(void** state)
{
    basic_string_t bstring;
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);

    bstring._t_typeinfo._t_style = 100;
    expect_assert_failure(_basic_string_same_type(pt_basic_string, &bstring));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_same_type__not_same_type_name(void** state)
{
    basic_string_t* pt_first = create_basic_string(int);
    basic_string_t* pt_second = create_basic_string(double);
    basic_string_init(pt_first);
    basic_string_init(pt_second);

    assert_false(_basic_string_same_type(pt_first, pt_second));

    basic_string_destroy(pt_first);
    basic_string_destroy(pt_second);
}

void test__basic_string_same_type__not_same_type_pointer(void** state)
{
    basic_string_t* pt_first = create_basic_string(int);
    basic_string_t* pt_second = create_basic_string(double);
    basic_string_init(pt_first);
    basic_string_init(pt_second);

    assert_false(_basic_string_same_type(pt_first, pt_second));

    basic_string_destroy(pt_first);
    basic_string_destroy(pt_second);
}

void test__basic_string_same_type__not_same_type_style(void** state)
{
    basic_string_t* pt_first = create_basic_string(int);
    basic_string_t* pt_second = create_basic_string(list_t<int>);
    basic_string_init(pt_first);
    basic_string_init(pt_second);

    assert_false(_basic_string_same_type(pt_first, pt_second));

    basic_string_destroy(pt_first);
    basic_string_destroy(pt_second);
}

void test__basic_string_same_type__not_same_type_style_ex1(void** state)
{
    basic_string_t* pt_first = create_basic_string(iterator_t);
    basic_string_t* pt_second = create_basic_string(list_t<int>);
    basic_string_init(pt_first);
    basic_string_init(pt_second);

    assert_false(_basic_string_same_type(pt_first, pt_second));

    basic_string_destroy(pt_first);
    basic_string_destroy(pt_second);
}

void test__basic_string_same_type__not_same_type_style_ex2(void** state)
{
    basic_string_t* pt_first = create_basic_string(list_t<double>);
    basic_string_t* pt_second = create_basic_string(list_t<int>);
    basic_string_init(pt_first);
    basic_string_init(pt_second);

    assert_false(_basic_string_same_type(pt_first, pt_second));

    basic_string_destroy(pt_first);
    basic_string_destroy(pt_second);
}


void test__basic_string_same_type__same_type(void** state)
{
    basic_string_t* pt_first = create_basic_string(int);
    basic_string_t* pt_second = create_basic_string(int);
    basic_string_init(pt_first);
    basic_string_init(pt_second);

    assert_true(_basic_string_same_type(pt_first, pt_second));

    basic_string_destroy(pt_first);
    basic_string_destroy(pt_second);
}

void test__basic_string_same_type__same_type_duplicate_name(void** state)
{
    basic_string_t* pt_first = create_basic_string(int);
    basic_string_t* pt_second = create_basic_string(signed);
    basic_string_init(pt_first);
    basic_string_init(pt_second);

    assert_true(_basic_string_same_type(pt_first, pt_second));

    basic_string_destroy(pt_first);
    basic_string_destroy(pt_second);
}

void test__basic_string_same_type__same_container(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);

    assert_true(_basic_string_same_type(pt_basic_string, pt_basic_string));

    basic_string_destroy(pt_basic_string);
}

/*
 * test _basic_string_get_value_string_length
 */
UT_CASE_DEFINATION(_basic_string_get_value_string_length)
void test__basic_string_get_value_string_length__null_basic_string(void** state)
{
    expect_assert_failure(_basic_string_get_value_string_length(NULL, (void*)0xcc));
}

void test__basic_string_get_value_string_length__null_value_string(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);

    basic_string_init(pt_basic_string);
    expect_assert_failure(_basic_string_get_value_string_length(pt_basic_string, NULL));

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_value_string_length__non_create(void** state)
{
    basic_string_t bstr;
    bstr._t_typeinfo._t_style = 1010;
    expect_assert_failure(_basic_string_get_value_string_length(&bstr, 0xcc));
}

void test__basic_string_get_value_string_length__c_builtin_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    int vstring[10] = {0};

    basic_string_init(pt_basic_string);
    assert_true(_basic_string_get_value_string_length(pt_basic_string, vstring) == 0);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_value_string_length__c_builtin_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    int vstring[10] = {1, 2, 3, 4, 5, 0, 7, 8, 9, -1};

    basic_string_init(pt_basic_string);
    assert_true(_basic_string_get_value_string_length(pt_basic_string, vstring) == 5);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_value_string_length__c_builtin_no_terminal(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    int vstring[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, -1};

    basic_string_init(pt_basic_string);
    /*assert_true(_basic_string_get_value_string_length(pt_basic_string, vstring) >= 10);*/

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_value_string_length__char_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char);

    basic_string_init(pt_basic_string);
    assert_true(_basic_string_get_value_string_length(pt_basic_string, "") == 0);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_value_string_length__char_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char);

    basic_string_init(pt_basic_string);
    assert_true(_basic_string_get_value_string_length(pt_basic_string, "abc0ef") == 6);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_value_string_length__char_no_terminal(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char);
    char elems[] = {'a', 'a', 'a'};

    basic_string_init(pt_basic_string);
    /*assert_true(_basic_string_get_value_string_length(pt_basic_string, elems) == 6);*/

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_value_string_length__cstr_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);
    const char* elems[] = {NULL};

    basic_string_init(pt_basic_string);
    assert_true(_basic_string_get_value_string_length(pt_basic_string, elems) == 0);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_value_string_length__cstr_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);
    const char* elems[] = {"abc", "def", "hij", NULL, "aaaa"};

    basic_string_init(pt_basic_string);
    assert_true(_basic_string_get_value_string_length(pt_basic_string, elems) == 3);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_value_string_length__cstr_no_terminal(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(char*);
    const char* elems[] = {"abc", "def", "hij", "aaaa"};

    basic_string_init(pt_basic_string);
    /*assert_true(_basic_string_get_value_string_length(pt_basic_string, elems) == 3);*/

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_value_string_length__libcstl_builtin_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(list_t<int>);
    list_t* elems[] = {NULL};

    basic_string_init(pt_basic_string);
    assert_true(_basic_string_get_value_string_length(pt_basic_string, elems) == 0);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_value_string_length__libcstl_builtin_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(list_t<int>);
    list_t* plist_1 = create_list(int);
    list_t* plist_2 = create_list(int);
    list_t* plist_3 = create_list(int);
    list_t* plist_4 = create_list(int);
    list_t* elems[5] = {NULL};

    list_init(plist_1);
    list_init(plist_2);
    list_init(plist_3);
    list_init(plist_4);
    basic_string_init(pt_basic_string);
    elems[0] = plist_1;
    elems[1] = plist_2;
    elems[2] = NULL;
    elems[3] = plist_3;
    elems[4] = plist_4;
    assert_true(_basic_string_get_value_string_length(pt_basic_string, elems) == 2);

    basic_string_destroy(pt_basic_string);
    list_destroy(plist_1);
    list_destroy(plist_2);
    list_destroy(plist_3);
    list_destroy(plist_4);
}

void test__basic_string_get_value_string_length__libcstl_builtin_no_terminal(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(list_t<int>);
    list_t* plist_1 = create_list(int);
    list_t* plist_2 = create_list(int);
    list_t* plist_3 = create_list(int);
    list_t* plist_4 = create_list(int);
    list_t* elems[5] = {NULL};

    list_init(plist_1);
    list_init(plist_2);
    list_init(plist_3);
    list_init(plist_4);
    basic_string_init(pt_basic_string);
    elems[0] = plist_1;
    elems[1] = plist_2;
    elems[2] = plist_2;
    elems[3] = plist_3;
    elems[4] = plist_4;
    /*assert_true(_basic_string_get_value_string_length(pt_basic_string, elems) == 2);*/

    basic_string_destroy(pt_basic_string);
    list_destroy(plist_1);
    list_destroy(plist_2);
    list_destroy(plist_3);
    list_destroy(plist_4);
}

typedef struct _tagtest__basic_string_get_value_string_length__user_define
{
    int n_first;
    double d_second;
}_test__basic_string_get_value_string_length__user_define;

void test__basic_string_get_value_string_length__user_define_empty(void** state)
{
    basic_string_t* pt_basic_string = NULL;
    _test__basic_string_get_value_string_length__user_define* elems[] = {NULL};

    type_register(_test__basic_string_get_value_string_length__user_define, NULL, NULL, NULL, NULL);

    pt_basic_string = create_basic_string(_test__basic_string_get_value_string_length__user_define);

    basic_string_init(pt_basic_string);
    assert_true(_basic_string_get_value_string_length(pt_basic_string, elems) == 0);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_value_string_length__user_define_non_empty(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(_test__basic_string_get_value_string_length__user_define);
    _test__basic_string_get_value_string_length__user_define t_user;
    _test__basic_string_get_value_string_length__user_define* elems[5] = {&t_user, &t_user, &t_user, NULL, &t_user};

    basic_string_init(pt_basic_string);
    assert_true(_basic_string_get_value_string_length(pt_basic_string, elems) == 3);

    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_value_string_length__user_define_no_terminal(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(_test__basic_string_get_value_string_length__user_define);
    _test__basic_string_get_value_string_length__user_define t_user;
    _test__basic_string_get_value_string_length__user_define* elems[5] = {&t_user, &t_user, &t_user, &t_user, &t_user};

    basic_string_init(pt_basic_string);
    /*assert_true(_basic_string_get_value_string_length(pt_basic_string, &vstr) >= 5);*/

    basic_string_destroy(pt_basic_string);
}

/*
 * test _basic_string_get_varg_value_auxiliary
 */
UT_CASE_DEFINATION(_basic_string_get_varg_value_auxiliary)

static void _wrapper_basic_string_get_varg_value_auxiliary(basic_string_t* pt_basic_string, void* pv_varg, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pv_varg);
    _basic_string_get_varg_value_auxiliary(pt_basic_string, val_elemlist, pv_varg);
    va_end(val_elemlist);
}

void test__basic_string_get_varg_value_auxiliary__null_basic_string_container(void** state)
{
    int varg = 0;
    expect_assert_failure(_wrapper_basic_string_get_varg_value_auxiliary(NULL, &varg, 100));
}

void test__basic_string_get_varg_value_auxiliary__null_varg(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);
    expect_assert_failure(_wrapper_basic_string_get_varg_value_auxiliary(pt_basic_string, NULL, 100));
    basic_string_destroy(pt_basic_string);
}

void test__basic_string_get_varg_value_auxiliary__non_created(void** state)
{
    int varg = 0;
    basic_string_t bstr;
    bstr._t_typeinfo._t_style = 100;
    expect_assert_failure(_wrapper_basic_string_get_varg_value_auxiliary(&bstr, &varg, 100));
    assert_true(true);
}

void test__basic_string_get_varg_value_auxiliary__successfully(void** state)
{
    int varg = 0;
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);
    _wrapper_basic_string_get_varg_value_auxiliary(pt_basic_string, &varg, 100);
    assert_int_equal(varg, 100);
    basic_string_destroy(pt_basic_string);
}

/*
 * test _basic_string_destroy_varg_value_auxiliary
 */
UT_CASE_DEFINATION(_basic_string_destroy_varg_value_auxiliary)
void test__basic_string_destroy_varg_value_auxiliary__null_basic_string_container(void** state)
{
    int varg = 0;
    expect_assert_failure(_basic_string_destroy_varg_value_auxiliary(NULL, &varg));
}

void test__basic_string_destroy_varg_value_auxiliary__null_varg(void** state)
{
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);
    expect_assert_failure(_basic_string_destroy_varg_value_auxiliary(pt_basic_string, NULL));
    basic_string_destroy(pt_basic_string);
}

void test__basic_string_destroy_varg_value_auxiliary__non_created(void** state)
{
    int varg = 0;
    basic_string_t bstr;
    bstr._t_typeinfo._t_style = 100;
    expect_assert_failure(_basic_string_destroy_varg_value_auxiliary(&bstr, &varg));
}

void test__basic_string_destroy_varg_value_auxiliary__successfully(void** state)
{
    int varg = 100;
    basic_string_t* pt_basic_string = create_basic_string(int);
    basic_string_init(pt_basic_string);
    _basic_string_destroy_varg_value_auxiliary(pt_basic_string, &varg);
    basic_string_destroy(pt_basic_string);
}

/*
 * test _basic_string_init_elem_range_auxiliary
 */
UT_CASE_DEFINATION(_basic_string_init_elem_range_auxiliary)
void test__basic_string_init_elem_range_auxiliary__null_basic_string_containter(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    basic_string_init_elem(pbstr, 10, 100);

    expect_assert_failure(_basic_string_init_elem_range_auxiliary(NULL, pbstr->_pby_string, 10));

    basic_string_destroy(pbstr);
}

void test__basic_string_init_elem_range_auxiliary__null_pby_string(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    basic_string_init_elem(pbstr, 10, 100);

    expect_assert_failure(_basic_string_init_elem_range_auxiliary(pbstr, NULL, 10));

    basic_string_destroy(pbstr);
}

void test__basic_string_init_elem_range_auxiliary__non_created(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    basic_string_init_elem(pbstr, 10, 100);
    pbstr->_t_typeinfo._t_style = 100;

    expect_assert_failure(_basic_string_init_elem_range_auxiliary(pbstr, pbstr->_pby_string, 10));

    pbstr->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    basic_string_destroy(pbstr);
}

void test__basic_string_init_elem_range_auxiliary__successfully_int(void** state)
{
    size_t i = 0;
    basic_string_t* pbstr = create_basic_string(int);
    basic_string_init_elem(pbstr, 10, 100);

    for(i = 0; i < basic_string_size(pbstr); ++i)
    {
        assert_int_equal(*(int*)basic_string_at(pbstr, i), 100);
    }
    _basic_string_init_elem_range_auxiliary(pbstr, pbstr->_pby_string, 10);
    for(i = 0; i < basic_string_size(pbstr); ++i)
    {
        assert_int_equal(*(int*)basic_string_at(pbstr, i), 0);
    }

    basic_string_destroy(pbstr);
}

void test__basic_string_init_elem_range_auxiliary__successfully_cstr(void** state)
{
    /*
    size_t i = 0;
    basic_string_t* pbstr = create_basic_string(char*);
    basic_string_init_elem(pbstr, 10, "abcdefg");

    for(i = 0; i < basic_string_size(pbstr); ++i)
    {
        assert_true(strcmp((char*)basic_string_at(pbstr, i), "abcdefg") == 0);
    }
    _basic_string_init_elem_range_auxiliary(pbstr, pbstr->_pby_string, 10);
    for(i = 0; i < basic_string_size(pbstr); ++i)
    {
        assert_true(strcmp((char*)basic_string_at(pbstr, i), "") == 0);
    }

    basic_string_destroy(pbstr);
    */
    assert_true(false);
}

void test__basic_string_init_elem_range_auxiliary__successfully_iterator(void** state)
{
    size_t i = 0;
    basic_string_t* pbstr = create_basic_string(iterator_t);
    basic_string_iterator_t it_iter = _create_basic_string_iterator();
    basic_string_init_elem(pbstr, 10, &it_iter);

    for(i = 0; i < basic_string_size(pbstr); ++i)
    {
        assert_true(memcmp((iterator_t*)basic_string_at(pbstr, i), &it_iter, sizeof(iterator_t)) == 0);
    }
    _basic_string_init_elem_range_auxiliary(pbstr, pbstr->_pby_string, 10);
    memset(&it_iter, 0x00, sizeof(iterator_t));
    for(i = 0; i < basic_string_size(pbstr); ++i)
    {
        assert_true(memcmp((iterator_t*)basic_string_at(pbstr, i), &it_iter, sizeof(iterator_t)) == 0);
    }

    basic_string_destroy(pbstr);
}

void test__basic_string_init_elem_range_auxiliary__successfully_container(void** state)
{
    size_t i = 0;
    basic_string_t a_vec[10];
    basic_string_t* pbstr = create_basic_string(basic_string_t<int>);
    basic_string_init(pbstr);

    _basic_string_init_elem_range_auxiliary(pbstr, (_byte_t*)a_vec, 10);
    for(i = 0; i < 10; ++i)
    {
        assert_true(a_vec[i]._t_typeinfo._t_style == _TYPE_C_BUILTIN);
        assert_true(strcmp(a_vec[i]._t_typeinfo._s_typename, _INT_TYPE) == 0);
        assert_true(a_vec[i]._t_typeinfo._pt_type != NULL);
        assert_true(a_vec[i]._pby_string != NULL);
        assert_true(_basic_string_rep_get_representation(a_vec[i]._pby_string)->_t_length == 0);
        assert_true(_basic_string_rep_get_representation(a_vec[i]._pby_string)->_t_capacity == 0);
        assert_true(_basic_string_rep_get_representation(a_vec[i]._pby_string)->_n_refcount == 0);
        assert_true(_basic_string_rep_get_representation(a_vec[i]._pby_string)->_t_elemsize == sizeof(int));
    }

    basic_string_destroy(pbstr);
}

/*
 * test _basic_string_detach
 */
UT_CASE_DEFINATION(_basic_string_detach)
void test__basic_string_detach__null(void** state)
{
    expect_assert_failure(_basic_string_detach(NULL));
}

void test__basic_string_detach__non_init(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    expect_assert_failure(_basic_string_detach(pbstr));
    basic_string_destroy(pbstr);
}

void test__basic_string_detach__non_sharable(void** state)
{
    size_t t_length = 0;
    size_t t_size = 0;
    size_t t_capacity = 0;
    int n_refcount = 0;
    _byte_t* pby_string = NULL;

    basic_string_t* pbstr = create_basic_string(int);
    basic_string_init_elem(pbstr, 10, 111);
    
    t_length = _basic_string_rep_get_representation(pbstr->_pby_string)->_t_length;
    t_capacity = _basic_string_rep_get_representation(pbstr->_pby_string)->_t_capacity;
    t_size = _basic_string_rep_get_representation(pbstr->_pby_string)->_t_elemsize;
    n_refcount = _basic_string_rep_get_representation(pbstr->_pby_string)->_n_refcount;
    pby_string = pbstr->_pby_string;
    _basic_string_detach(pbstr);
    assert(_basic_string_rep_get_representation(pbstr->_pby_string)->_t_length == t_length);
    assert(_basic_string_rep_get_representation(pbstr->_pby_string)->_t_capacity == t_capacity);
    assert(_basic_string_rep_get_representation(pbstr->_pby_string)->_t_elemsize == t_size);
    assert(_basic_string_rep_get_representation(pbstr->_pby_string)->_n_refcount == n_refcount);
    assert(pbstr->_pby_string == pby_string);

    basic_string_destroy(pbstr);
}

void test__basic_string_detach__sharable(void** state)
{
    _basic_string_rep_t* prep1 = NULL;
    _basic_string_rep_t* prep2 = NULL;
    _basic_string_rep_t* prep3 = NULL;
    basic_string_t* pbstr1 = create_basic_string(int);
    basic_string_t* pbstr2 = create_basic_string(int);
    basic_string_t* pbstr3 = create_basic_string(int);
    basic_string_init_elem(pbstr1, 10, 111);
    basic_string_init_copy(pbstr2, pbstr1);
    basic_string_init_copy(pbstr3, pbstr2);
    
    assert(pbstr1->_pby_string == pbstr2->_pby_string);
    assert(pbstr1->_pby_string == pbstr3->_pby_string);
    _basic_string_detach(pbstr2);
    prep1 = _basic_string_rep_get_representation(pbstr1->_pby_string);
    prep2 = _basic_string_rep_get_representation(pbstr2->_pby_string);
    prep3 = _basic_string_rep_get_representation(pbstr3->_pby_string);
    assert(prep1 == prep3);
    assert(prep1 != prep2);
    assert(prep1->_n_refcount == 1);
    assert(prep2->_n_refcount == 0);
    assert(prep1->_t_capacity == prep2->_t_capacity);
    assert(prep1->_t_elemsize == prep2->_t_elemsize);
    assert(prep1->_t_length == prep2->_t_length);
    assert(pbstr1->_pby_string != pbstr2->_pby_string);
    assert(memcmp(pbstr1->_pby_string, pbstr2->_pby_string, prep1->_t_length * prep1->_t_elemsize) == 0);

    basic_string_destroy(pbstr1);
    basic_string_destroy(pbstr2);
    basic_string_destroy(pbstr3);
}

/*
 * test _basic_string_is_shared
 */
UT_CASE_DEFINATION(_basic_string_is_shared)
void test__basic_string_is_shared__null(void** state)
{
    expect_assert_failure(_basic_string_is_shared(NULL));
}
void test__basic_string_is_shared__non_inited(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    expect_assert_failure(_basic_string_is_shared(pbstr));
    basic_string_destroy(pbstr);
}
void test__basic_string_is_shared__shared(void** state)
{
    basic_string_t* pbstr1 = create_basic_string(int);
    basic_string_t* pbstr2 = create_basic_string(int);
    basic_string_init(pbstr1);
    basic_string_init_copy(pbstr2, pbstr1);
    assert_true(_basic_string_is_shared(pbstr1));
    assert_true(_basic_string_is_shared(pbstr2));
    basic_string_destroy(pbstr1);
    basic_string_destroy(pbstr2); 
}
void test__basic_string_is_shared__not_shared(void** state)
{
    basic_string_t* pbstr1 = create_basic_string(int);
    basic_string_t* pbstr2 = create_basic_string(int);
    basic_string_init(pbstr1);
    basic_string_init(pbstr2);
    assert_false(_basic_string_is_shared(pbstr1));
    assert_false(_basic_string_is_shared(pbstr2));
    basic_string_destroy(pbstr1);
    basic_string_destroy(pbstr2);
}

/*
 * test _basic_string_clone_representation
 */
UT_CASE_DEFINATION(_basic_string_clone_representation)
void test__basic_string_clone_representation__null(void** state)
{
    expect_assert_failure(_basic_string_clone_representation(NULL, 0));
}
void test__basic_string_clone_representation__non_inited(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    expect_assert_failure(_basic_string_clone_representation(pbstr, 0));
    basic_string_destroy(pbstr);
}
void test__basic_string_clone_representation__c_builtin_length_0(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    _basic_string_rep_t* prep = NULL;
    basic_string_init(pbstr);
    prep = _basic_string_clone_representation(pbstr, 0);
    assert(prep != NULL);
    assert(prep->_n_refcount == -1);
    assert(prep->_t_capacity == 0);
    assert(prep->_t_elemsize == _GET_BASIC_STRING_TYPE_SIZE(pbstr));
    assert(prep->_t_length == 0);
    free(prep);
    basic_string_destroy(pbstr);
}
void test__basic_string_clone_representation__c_builtin_length_not_0(void** state)
{
    int i = 0;
    basic_string_t* pbstr = create_basic_string(int);
    _basic_string_rep_t* prep = NULL;
    basic_string_init_elem(pbstr, 10, 111);
    prep = _basic_string_clone_representation(pbstr, 5);
    assert(prep != NULL);
    assert(prep->_n_refcount == -1);
    assert(prep->_t_capacity == 20);
    assert(prep->_t_elemsize == _GET_BASIC_STRING_TYPE_SIZE(pbstr));
    assert(prep->_t_length == 10);
    for (i = 0; i < prep->_t_length; ++i) {
        assert_true(*(int*)(_basic_string_rep_get_data(prep) + i * prep->_t_elemsize) == 111);
    }
    free(prep);
    basic_string_destroy(pbstr);
}
void test__basic_string_clone_representation__cstr_length_0(void** state)
{
    assert_true(false);
}
void test__basic_string_clone_representation__cstr_length_not_0(void** state)
{
    assert_true(false);
}
void test__basic_string_clone_representation__cstl_builtin_length_0(void** state)
{
    basic_string_t* pbstr = create_basic_string(list_t<int>);
    _basic_string_rep_t* prep = NULL;
    basic_string_init(pbstr);
    prep = _basic_string_clone_representation(pbstr, 0);
    assert(prep != NULL);
    assert(prep->_n_refcount == -1);
    assert(prep->_t_capacity == 0);
    assert(prep->_t_elemsize == _GET_BASIC_STRING_TYPE_SIZE(pbstr));
    assert(prep->_t_length == 0);
    free(prep);
    basic_string_destroy(pbstr);
}
void test__basic_string_clone_representation__cstl_builtin_length_not_0(void** state)
{
    int i = 0;
    list_t* plist = create_list(int);
    basic_string_t* pbstr = create_basic_string(list_t<int>);
    _basic_string_rep_t* prep = NULL;
    list_init(plist);
    list_push_back(plist, 111);
    basic_string_init_elem(pbstr, 10, plist);
    prep = _basic_string_clone_representation(pbstr, 100);
    assert(prep != NULL);
    assert(prep->_n_refcount == -1);
    assert(prep->_t_capacity == 110);
    assert(prep->_t_elemsize == _GET_BASIC_STRING_TYPE_SIZE(pbstr));
    assert(prep->_t_length == 10);
    for (i = 0; i < prep->_t_length; ++i) {
        assert_true(*(int*)list_front((list_t*)(_basic_string_rep_get_data(prep) + i * prep->_t_elemsize)) == 111);
    }
    free(prep);
    basic_string_destroy(pbstr);
    list_destroy(plist);
}
typedef struct _tag_basic_string_clone_representation
{
    int a;
} _basic_string_clone_representation_t;
void test__basic_string_clone_representation__user_define_length_0(void** state)
{
    basic_string_t* pbstr = NULL;
    _basic_string_rep_t* prep = NULL;

    type_register(_basic_string_clone_representation_t, NULL, NULL, NULL, NULL);

    pbstr = create_basic_string(_basic_string_clone_representation_t);
    basic_string_init(pbstr);
    prep = _basic_string_clone_representation(pbstr, 10);
    assert(prep != NULL);
    assert(prep->_n_refcount == -1);
    assert(prep->_t_capacity == 10);
    assert(prep->_t_elemsize == _GET_BASIC_STRING_TYPE_SIZE(pbstr));
    assert(prep->_t_length == 0);
    free(prep);
    basic_string_destroy(pbstr);
}
void test__basic_string_clone_representation__user_define_length_not_0(void** state)
{
    int i = 0;
    _basic_string_clone_representation_t t_elem;
    basic_string_t* pbstr = create_basic_string(_basic_string_clone_representation_t);
    _basic_string_rep_t* prep = NULL;
    t_elem.a = 111;
    basic_string_init_elem(pbstr, 10, &t_elem);
    prep = _basic_string_clone_representation(pbstr, 100);
    assert(prep != NULL);
    assert(prep->_n_refcount == -1);
    assert(prep->_t_capacity == 110);
    assert(prep->_t_elemsize == _GET_BASIC_STRING_TYPE_SIZE(pbstr));
    assert(prep->_t_length == 10);
    for (i = 0; i < prep->_t_length; ++i) {
        assert_true(((_basic_string_clone_representation_t*)(_basic_string_rep_get_data(prep) + i * prep->_t_elemsize))->a == 111);
    }
    free(prep);
    basic_string_destroy(pbstr);
}


