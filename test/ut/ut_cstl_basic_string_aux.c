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
#include "cstl_vector_aux.h"
#include "cstl/cstring.h"

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
    string_t elems[10] = {0};
    size_t i = 0;
    basic_string_t* pbstr = create_basic_string(char*);
    basic_string_init_elem(pbstr, 10, "abcdefg");

    for(i = 0; i < basic_string_size(pbstr); ++i)
    {
        assert_true(strcmp((char*)basic_string_at(pbstr, i), "abcdefg") == 0);
    }
    _basic_string_init_elem_range_auxiliary(pbstr, elems, 10);
    for(i = 0; i < 10; ++i)
    {
        assert_true(strcmp(string_c_str(elems+i), "") == 0);
    }

    for (i = 0; i < 10; ++i) {
        _string_destroy_auxiliary(elems+i);
    }
    basic_string_destroy(pbstr);
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
    vector_t a_vec[10];
    basic_string_t* pbstr = create_basic_string(vector_t<int>);
    basic_string_init(pbstr);

    for (i = 0; i < 10; ++i) {
        _create_vector_auxiliary(a_vec + i, "int");
    }
    _basic_string_init_elem_range_auxiliary(pbstr, (_byte_t*)a_vec, 10);
    for(i = 0; i < 10; ++i)
    {
        assert_true(_vector_is_inited(a_vec + i));
    }

    for (i = 0; i < 10; ++i) {
        _vector_destroy_auxiliary(a_vec + i);
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
    basic_string_t* pbstr = create_basic_string(char*);
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
void test__basic_string_clone_representation__cstr_length_not_0(void** state)
{
    int i = 0;
    basic_string_t* pbstr = create_basic_string(char*);
    _basic_string_rep_t* prep = NULL;
    basic_string_init_elem(pbstr, 10, "abc");
    prep = _basic_string_clone_representation(pbstr, 5);
    assert(prep != NULL);
    assert(prep->_n_refcount == -1);
    assert(prep->_t_capacity == 20);
    assert(prep->_t_elemsize == _GET_BASIC_STRING_TYPE_SIZE(pbstr));
    assert(prep->_t_length == 10);
    for (i = 0; i < prep->_t_length; ++i) {
        assert_true(string_compare_cstr((string_t*)(_basic_string_rep_get_data(prep) + i * prep->_t_elemsize), "abc") == 0);
    }
    /*free(prep);*/
    _basic_string_rep_reduce_shared(prep, _GET_BASIC_STRING_TYPE_DESTROY_FUNCTION(pbstr), &pbstr->_t_typeinfo);
    basic_string_destroy(pbstr);
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
    basic_string_destroy(pbstr);
    list_destroy(plist);
    _basic_string_rep_reduce_shared(prep, _GET_BASIC_STRING_TYPE_DESTROY_FUNCTION(pbstr), &pbstr->_t_typeinfo);
    /*free(prep);*/
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

/*
 * test _basic_string_iterator_belong_to_basic_string
 */
UT_CASE_DEFINATION(_basic_string_iterator_belong_to_basic_string)
void test__basic_string_iterator_belong_to_basic_string__null_container_pointer(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pbstr, 10, 100);
    it_iter = basic_string_begin(pbstr);

    expect_assert_failure(_basic_string_iterator_belong_to_basic_string(NULL, it_iter));

    basic_string_destroy(pbstr);
}

void test__basic_string_iterator_belong_to_basic_string__non_inited_basic_string_container(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init(pbstr);
    it_iter = basic_string_begin(pbstr);

    pbstr->_t_typeinfo._t_style = 123455;
    expect_assert_failure(_basic_string_iterator_belong_to_basic_string(pbstr, it_iter));

    pbstr->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    basic_string_destroy(pbstr);
}

void test__basic_string_iterator_belong_to_basic_string__invalid_iterator_container_type(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pbstr, 10, 100);
    it_iter = basic_string_begin(pbstr);
    it_iter._t_containertype = _LIST_CONTAINER;

    expect_assert_failure(_basic_string_iterator_belong_to_basic_string(pbstr, it_iter));

    basic_string_destroy(pbstr);
}

void test__basic_string_iterator_belong_to_basic_string__invalid_iterator_iterator_type(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pbstr, 10, 100);
    it_iter = basic_string_begin(pbstr);
    it_iter._t_iteratortype = _INPUT_ITERATOR;

    expect_assert_failure(_basic_string_iterator_belong_to_basic_string(pbstr, it_iter));

    basic_string_destroy(pbstr);
}

void test__basic_string_iterator_belong_to_basic_string__invalid_iterator_different_container(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pbstr, 10, 100);
    it_iter = basic_string_begin(pbstr);
    it_iter._pt_container = NULL;

    expect_assert_failure(_basic_string_iterator_belong_to_basic_string(pbstr, it_iter));

    basic_string_destroy(pbstr);
}

void test__basic_string_iterator_belong_to_basic_string__less_than_begin(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pbstr, 10, 100);
    it_iter = basic_string_begin(pbstr);
    it_iter._t_pos._pby_corepos = pbstr->_pby_string - 1;

    assert_false(_basic_string_iterator_belong_to_basic_string(pbstr, it_iter));

    basic_string_destroy(pbstr);
}

void test__basic_string_iterator_belong_to_basic_string__within_basic_string(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pbstr, 10, 100);
    it_iter = basic_string_begin(pbstr);

    assert_true(_basic_string_iterator_belong_to_basic_string(pbstr, it_iter));

    basic_string_destroy(pbstr);
}

void test__basic_string_iterator_belong_to_basic_string__end_iterator(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pbstr, 10, 100);
    it_iter = basic_string_end(pbstr);

    assert_true(_basic_string_iterator_belong_to_basic_string(pbstr, it_iter));

    basic_string_destroy(pbstr);
}

void test__basic_string_iterator_belong_to_basic_string__greater_than_end(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init_elem(pbstr, 10, 100);
    it_iter = basic_string_end(pbstr);
    it_iter._t_pos._pby_corepos += pbstr->_t_typeinfo._pt_type->_t_typesize;

    assert_false(_basic_string_iterator_belong_to_basic_string(pbstr, it_iter));

    basic_string_destroy(pbstr);
}

/*
 * test _basic_string_same_iterator_type
 */
UT_CASE_DEFINATION(_basic_string_same_iterator_type)
void test__basic_string_same_iterator_type__null_basic_string_container(void** state)
{
    basic_string_t* pbasic_string = create_basic_string(int);
    basic_string_init(pbasic_string);

    expect_assert_failure(_basic_string_same_iterator_type(NULL, basic_string_begin(pbasic_string)));

    basic_string_destroy(pbasic_string);
}

void test__basic_string_same_iterator_type__invalid_iterator_null_container(void** state)
{
    basic_string_t* pbasic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init(pbasic_string);
    it_iter = basic_string_begin(pbasic_string);
    it_iter._pt_container = NULL;
    expect_assert_failure(_basic_string_same_iterator_type(pbasic_string, it_iter));

    basic_string_destroy(pbasic_string);
}

void test__basic_string_same_iterator_type__invalid_iterator_container_type(void** state)
{
    basic_string_t* pbasic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init(pbasic_string);
    it_iter = basic_string_begin(pbasic_string);
    it_iter._t_containertype = 2823;
    expect_assert_failure(_basic_string_same_iterator_type(pbasic_string, it_iter));

    basic_string_destroy(pbasic_string);
}

void test__basic_string_same_iterator_type__invalid_iterator_iterator_type(void** state)
{
    basic_string_t* pbasic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init(pbasic_string);
    it_iter = basic_string_begin(pbasic_string);
    it_iter._t_iteratortype = 222;
    expect_assert_failure(_basic_string_same_iterator_type(pbasic_string, it_iter));

    basic_string_destroy(pbasic_string);
}

void test__basic_string_same_iterator_type__same_type_belong_to_basic_string(void** state)
{
    basic_string_t* pbasic_string = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init(pbasic_string);
    it_iter = basic_string_begin(pbasic_string);
    assert_true(_basic_string_same_iterator_type(pbasic_string, it_iter));

    basic_string_destroy(pbasic_string);
}

void test__basic_string_same_iterator_type__same_type_not_belong_to_basic_string(void** state)
{
    basic_string_t* pbasic_string_first = create_basic_string(int);
    basic_string_t* pbasic_string_second = create_basic_string(int);
    basic_string_iterator_t it_iter;

    basic_string_init(pbasic_string_second);
    it_iter = basic_string_begin(pbasic_string_second);
    assert_true(_basic_string_same_iterator_type(pbasic_string_first, it_iter));

    basic_string_destroy(pbasic_string_first);
    basic_string_destroy(pbasic_string_second);
}

void test__basic_string_same_iterator_type__not_same_type(void** state)
{
    basic_string_t* pbasic_string_first = create_basic_string(int);
    basic_string_t* pbasic_string_second = create_basic_string(double);
    basic_string_iterator_t it_iter;

    basic_string_init(pbasic_string_second);
    it_iter = basic_string_begin(pbasic_string_second);
    assert_false(_basic_string_same_iterator_type(pbasic_string_first, it_iter));

    basic_string_destroy(pbasic_string_first);
    basic_string_destroy(pbasic_string_second);
}

void test__basic_string_same_iterator_type__same_type_not_basic_string_iterator(void** state)
{
    basic_string_t* pbasic_string = create_basic_string(int);
    list_t* plist = create_list(int);

    list_init(plist);
    assert_true(_basic_string_same_iterator_type(pbasic_string, list_begin(plist)));

    basic_string_destroy(pbasic_string);
    list_destroy(plist);
}

void test__basic_string_same_iterator_type__not_same_type_not_basic_string_iterator(void** state)
{
    basic_string_t* pbasic_string = create_basic_string(int);
    list_t* plist = create_list(double);

    list_init(plist);
    assert_false(_basic_string_same_iterator_type(pbasic_string, list_begin(plist)));

    basic_string_destroy(pbasic_string);
    list_destroy(plist);
}

/*
 * test _basic_string_copy_substring_auxiliary
 */
UT_CASE_DEFINATION(_basic_string_copy_substring_auxiliary)
void test__basic_string_copy_substring_auxiliary__null_bstr(void** state)
{
    _byte_t by_dest[10];
    _byte_t by_src[10];
    expect_assert_failure(_basic_string_copy_substring_auxiliary(NULL, by_dest, by_src, 10));
}
void test__basic_string_copy_substring_auxiliary__non_created(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    _byte_t aby_dest[10];
    _byte_t aby_src[10];

    pbstr->_t_typeinfo._t_style = 9999;
    expect_assert_failure(_basic_string_copy_substring_auxiliary(pbstr, aby_dest, aby_src, 10));
    pbstr->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    basic_string_destroy(pbstr);
}
void test__basic_string_copy_substring_auxiliary__null_dest(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    _byte_t aby_src[10];

    expect_assert_failure(_basic_string_copy_substring_auxiliary(pbstr, NULL, aby_src, 10));
    basic_string_destroy(pbstr);
}
void test__basic_string_copy_substring_auxiliary__null_src(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    _byte_t aby_dest[10];

    expect_assert_failure(_basic_string_copy_substring_auxiliary(pbstr, aby_dest, NULL, 10));
    basic_string_destroy(pbstr);
}
void test__basic_string_copy_substring_auxiliary__invalid_len(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    _byte_t aby_dest[10];
    _byte_t aby_src[10];
    expect_assert_failure(_basic_string_copy_substring_auxiliary(pbstr, aby_dest, aby_src, NPOS));
    basic_string_destroy(pbstr);
}
void test__basic_string_copy_substring_auxiliary__empty(void** state)
{
    basic_string_t* pbstr1 = create_basic_string(int);
    basic_string_t* pbstr2 = create_basic_string(int);

    basic_string_init_elem(pbstr1, 10, 111);
    basic_string_init_elem(pbstr2, 10, 0);
    _basic_string_copy_substring_auxiliary(pbstr1, pbstr1->_pby_string, pbstr2->_pby_string, 0);
    assert_true(*(int*)basic_string_at(pbstr1, 0) == 111);

    basic_string_destroy(pbstr1);
    basic_string_destroy(pbstr2);
}
void test__basic_string_copy_substring_auxiliary__non_empty(void** state)
{
    int i = 0;
    basic_string_t* pbstr1 = create_basic_string(int);
    basic_string_t* pbstr2 = create_basic_string(int);

    basic_string_init_elem(pbstr1, 10, 111);
    basic_string_init(pbstr2);
    for (i = 0; i < 10; ++i) {
        basic_string_push_back(pbstr2, i);
    }
    _basic_string_copy_substring_auxiliary(pbstr1, pbstr1->_pby_string, pbstr2->_pby_string, 5);
    for (i = 0; i < 10; ++i) {
        if (i < 5) {
            assert_true(*(int*)basic_string_at(pbstr1, i) == i);
        } else {
            assert_true(*(int*)basic_string_at(pbstr1, i) == 111);
        }
    }

    basic_string_destroy(pbstr1);
    basic_string_destroy(pbstr2);
}
void test__basic_string_copy_substring_auxiliary__cstr(void** state)
{
    int i = 0;
    basic_string_t* pbstr1 = create_basic_string(char*);
    basic_string_t* pbstr2 = create_basic_string(char*);

    basic_string_init_elem(pbstr1, 10, "abc");
    basic_string_init(pbstr2);
    for (i = 0; i < 10; ++i) {
        basic_string_push_back(pbstr2, "xyz");
    }
    _basic_string_copy_substring_auxiliary(pbstr1, pbstr1->_pby_string, pbstr2->_pby_string, 5);
    for (i = 0; i < 10; ++i) {
        if (i < 5) {
            assert_true(strcmp((char*)basic_string_at(pbstr1, i), "xyz") == 0);
        } else {
            assert_true(strcmp((char*)basic_string_at(pbstr1, i), "abc") == 0);
        }
    }

    basic_string_destroy(pbstr1);
    basic_string_destroy(pbstr2);
}
void test__basic_string_copy_substring_auxiliary__libcstl(void** state)
{
    basic_string_t* pbstr1 = create_basic_string(list_t<int>);
    basic_string_t* pbstr2 = create_basic_string(list_t<int>);
    list_t* plist = create_list(int);
    int i = 0;

    list_init(plist);
    basic_string_init_elem(pbstr1, 10, plist);
    basic_string_init(pbstr2);
    for (i = 0; i < 10; ++i) {
        list_resize(plist, i);
        basic_string_push_back(pbstr2, plist);
    }
    _basic_string_copy_substring_auxiliary(pbstr1, pbstr1->_pby_string, pbstr2->_pby_string, 5);
    for (i = 0; i < 10; ++i) {
        if (i < 5) {
            assert_true(list_size(basic_string_at(pbstr1, i)) == i);
        } else {
            assert_true(list_size(basic_string_at(pbstr1, i)) == 0);
        }
    }

    basic_string_destroy(pbstr1);
    basic_string_destroy(pbstr2);
    list_destroy(plist);
}
typedef struct _tag_test__basic_string_copy_auxiliary__user_define {
    int a;
} _test__basic_string_copy_auxiliary__t;
void test__basic_string_copy_substring_auxiliary__user_define(void** state)
{
    basic_string_t* pbstr1 = NULL;
    basic_string_t* pbstr2 = NULL;
    _test__basic_string_copy_auxiliary__t t_elem;
    int i = 0;

    type_register(_test__basic_string_copy_auxiliary__t, NULL, NULL, NULL, NULL);
    pbstr1 = create_basic_string(_test__basic_string_copy_auxiliary__t);
    pbstr2 = create_basic_string(_test__basic_string_copy_auxiliary__t);
    t_elem.a = 100;
    basic_string_init_elem(pbstr1, 10, &t_elem);
    basic_string_init(pbstr2);
    for (i = 0; i < 10; ++i) {
        t_elem.a = i;
        basic_string_push_back(pbstr2, &t_elem);
    }
    _basic_string_copy_substring_auxiliary(pbstr1, pbstr1->_pby_string, pbstr2->_pby_string, 5);
    for (i = 0; i < 10; ++i) {
        if (i < 5) {
            assert_true(((_test__basic_string_copy_auxiliary__t*)basic_string_at(pbstr1, i))->a == i);
        } else {
            assert_true(((_test__basic_string_copy_auxiliary__t*)basic_string_at(pbstr1, i))->a == 100);
        }
    }

    basic_string_destroy(pbstr1);
    basic_string_destroy(pbstr2);
}

/*
 * test _basic_string_copy_substring_backward_auxiliary
 */
UT_CASE_DEFINATION(_basic_string_copy_substring_backward_auxiliary)
void test__basic_string_copy_substring_backward_auxiliary__null_bstr(void** state)
{
    _byte_t by_dest[10];
    _byte_t by_src[10];
    expect_assert_failure(_basic_string_copy_substring_backward_auxiliary(NULL, by_dest, by_src, 10));
}
void test__basic_string_copy_substring_backward_auxiliary__non_created(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    _byte_t aby_dest[10];
    _byte_t aby_src[10];

    pbstr->_t_typeinfo._t_style = 9999;
    expect_assert_failure(_basic_string_copy_substring_backward_auxiliary(pbstr, aby_dest, aby_src, 10));
    pbstr->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    basic_string_destroy(pbstr);
}
void test__basic_string_copy_substring_backward_auxiliary__null_dest(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    _byte_t aby_src[10];

    expect_assert_failure(_basic_string_copy_substring_backward_auxiliary(pbstr, NULL, aby_src, 10));
    basic_string_destroy(pbstr);
}
void test__basic_string_copy_substring_backward_auxiliary__null_src(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    _byte_t aby_dest[10];

    expect_assert_failure(_basic_string_copy_substring_backward_auxiliary(pbstr, aby_dest, NULL, 10));
    basic_string_destroy(pbstr);
}
void test__basic_string_copy_substring_backward_auxiliary__invalid_len(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    _byte_t aby_dest[10];
    _byte_t aby_src[10];
    expect_assert_failure(_basic_string_copy_substring_backward_auxiliary(pbstr, aby_dest, aby_src, NPOS));
    basic_string_destroy(pbstr);
}
void test__basic_string_copy_substring_backward_auxiliary__empty(void** state)
{
    basic_string_t* pbstr1 = create_basic_string(int);

    basic_string_init_elem(pbstr1, 10, 111);
    _basic_string_copy_substring_backward_auxiliary(pbstr1, pbstr1->_pby_string + sizeof(int), pbstr1->_pby_string, 0);
    assert_true(*(int*)basic_string_at(pbstr1, 0) == 111);

    basic_string_destroy(pbstr1);
}
void test__basic_string_copy_substring_backward_auxiliary__non_empty(void** state)
{
    int i = 0;
    basic_string_t* pbstr2 = create_basic_string(int);

    basic_string_init(pbstr2);
    for (i = 0; i < 10; ++i) {
        basic_string_push_back(pbstr2, i);
    }
    _basic_string_copy_substring_backward_auxiliary(pbstr2, pbstr2->_pby_string + sizeof(int), pbstr2->_pby_string, 9);
    for (i = 0; i < 10; ++i) {
        if (i == 0) {
            assert_true(*(int*)basic_string_at(pbstr2, i) == 0);
        } else {
            assert_true(*(int*)basic_string_at(pbstr2, i) == i - 1);
        }
    }

    basic_string_destroy(pbstr2);
}
void test__basic_string_copy_substring_backward_auxiliary__cstr(void** state)
{
    int i = 0;
    basic_string_t* pbstr2 = create_basic_string(char*);
    char elems[] = {'0', '1', '2', '3', '4', '\0'};

    basic_string_init(pbstr2);
    for (i = 0; i < 10; ++i) {
        elems[0] = '0' + i;
        basic_string_push_back(pbstr2, elems);
    }
    _basic_string_copy_substring_backward_auxiliary(pbstr2, pbstr2->_pby_string + _GET_BASIC_STRING_TYPE_SIZE(pbstr2), pbstr2->_pby_string, 9);
    for (i = 0; i < 10; ++i) {
        if (i == 0) {
            assert_true(((char*)basic_string_at(pbstr2, i))[0] == '0');
        } else {
            assert_true(((char*)basic_string_at(pbstr2, i))[0] + 1 - i == '0');
        }
    }

    basic_string_destroy(pbstr2);
}
void test__basic_string_copy_substring_backward_auxiliary__libcstl(void** state)
{
    basic_string_t* pbstr1 = create_basic_string(list_t<int>);
    basic_string_t* pbstr2 = create_basic_string(list_t<int>);
    list_t* plist = create_list(int);
    int i = 0;

    list_init(plist);
    basic_string_init_elem(pbstr1, 10, plist);
    basic_string_init(pbstr2);
    for (i = 0; i < 10; ++i) {
        list_resize(plist, i);
        basic_string_push_back(pbstr2, plist);
    }
    _basic_string_copy_substring_backward_auxiliary(pbstr1, pbstr1->_pby_string, pbstr2->_pby_string, 5);
    for (i = 0; i < 10; ++i) {
        if (i < 5) {
            assert_true(list_size(basic_string_at(pbstr1, i)) == i);
        } else {
            assert_true(list_size(basic_string_at(pbstr1, i)) == 0);
        }
    }

    basic_string_destroy(pbstr1);
    basic_string_destroy(pbstr2);
    list_destroy(plist);
}
void test__basic_string_copy_substring_backward_auxiliary__user_define(void** state)
{
    basic_string_t* pbstr1 = NULL;
    basic_string_t* pbstr2 = NULL;
    _test__basic_string_copy_auxiliary__t t_elem;
    int i = 0;

    pbstr1 = create_basic_string(_test__basic_string_copy_auxiliary__t);
    pbstr2 = create_basic_string(_test__basic_string_copy_auxiliary__t);
    t_elem.a = 100;
    basic_string_init_elem(pbstr1, 10, &t_elem);
    basic_string_init(pbstr2);
    for (i = 0; i < 10; ++i) {
        t_elem.a = i;
        basic_string_push_back(pbstr2, &t_elem);
    }
    _basic_string_copy_substring_backward_auxiliary(pbstr1, pbstr1->_pby_string, pbstr2->_pby_string, 5);
    for (i = 0; i < 10; ++i) {
        if (i < 5) {
            assert_true(((_test__basic_string_copy_auxiliary__t*)basic_string_at(pbstr1, i))->a == i);
        } else {
            assert_true(((_test__basic_string_copy_auxiliary__t*)basic_string_at(pbstr1, i))->a == 100);
        }
    }

    basic_string_destroy(pbstr1);
    basic_string_destroy(pbstr2);
}

/*
 * test _basic_string_copy_subcstr_auxiliary
 */
UT_CASE_DEFINATION(_basic_string_copy_subcstr_auxiliary)
void test__basic_string_copy_subcstr_auxiliary__null_bstr(void** state)
{
    _byte_t by_dest[10];
    int an_src[10];
    expect_assert_failure(_basic_string_copy_subcstr_auxiliary(NULL, by_dest, an_src, 10));
}
void test__basic_string_copy_subcstr_auxiliary__non_created(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    _byte_t aby_dest[10];
    int aby_src[10];

    pbstr->_t_typeinfo._t_style = 9999;
    expect_assert_failure(_basic_string_copy_subcstr_auxiliary(pbstr, aby_dest, aby_src, 10));
    pbstr->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    basic_string_destroy(pbstr);
}
void test__basic_string_copy_subcstr_auxiliary__null_dest(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    int aby_src[10];

    expect_assert_failure(_basic_string_copy_subcstr_auxiliary(pbstr, NULL, aby_src, 10));
    basic_string_destroy(pbstr);
}
void test__basic_string_copy_subcstr_auxiliary__null_src(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    _byte_t aby_dest[10];

    expect_assert_failure(_basic_string_copy_subcstr_auxiliary(pbstr, aby_dest, NULL, 10));
    basic_string_destroy(pbstr);
}
void test__basic_string_copy_subcstr_auxiliary__invalid_len(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    _byte_t aby_dest[10];
    int aby_src[10];
    expect_assert_failure(_basic_string_copy_subcstr_auxiliary(pbstr, aby_dest, aby_src, NPOS));
    basic_string_destroy(pbstr);
}
void test__basic_string_copy_subcstr_auxiliary__empty(void** state)
{
    basic_string_t* pbstr1 = create_basic_string(int);
    int an_src[10] = {0};

    basic_string_init_elem(pbstr1, 10, 111);
    _basic_string_copy_subcstr_auxiliary(pbstr1, pbstr1->_pby_string, an_src, 0);
    assert_true(*(int*)basic_string_at(pbstr1, 0) == 111);

    basic_string_destroy(pbstr1);
}
void test__basic_string_copy_subcstr_auxiliary__non_empty(void** state)
{
    int i = 0;
    basic_string_t* pbstr1 = create_basic_string(int);
    int an_src[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    basic_string_init_elem(pbstr1, 10, 111);
    _basic_string_copy_subcstr_auxiliary(pbstr1, pbstr1->_pby_string, an_src, 5);
    for (i = 0; i < 10; ++i) {
        if (i < 5) {
            assert_true(*(int*)basic_string_at(pbstr1, i) == i);
        } else {
            assert_true(*(int*)basic_string_at(pbstr1, i) == 111);
        }
    }

    basic_string_destroy(pbstr1);
}
void test__basic_string_copy_subcstr_auxiliary__cstr(void** state)
{
    int i = 0;
    basic_string_t* pbstr = create_basic_string(char*);
    const char* elems[] = {"abc", "abc", NULL, NULL};
    const char* inits[] = {"xyz", NULL, NULL, "xyz", "xyz", "xyz", "xyz", "xyz", "xyz", "xyz"};
    string_t terminator;

    basic_string_init_subcstr(pbstr, inits, 10);
    _basic_string_copy_subcstr_auxiliary(pbstr, pbstr->_pby_string, elems, 4);
    for (i = 0; i < 10; ++i) {
        if (i < 4) {
            if (i == 2 || i == 3) {
                assert_true(basic_string_at(pbstr, i) == NULL);
            } else {
                assert_true(strcmp((char*)basic_string_at(pbstr, i), "abc") == 0);
            }
        } else {
            assert_true(strcmp((char*)basic_string_at(pbstr, i), "xyz") == 0);
        }
    }
    basic_string_destroy(pbstr);
}
void test__basic_string_copy_subcstr_auxiliary__libcstl(void** state)
{
    int i = 0;
    basic_string_t* pbstr1 = create_basic_string(list_t<int>);
    list_t* plist = create_list(int);
    list_t* ap_src[] = {plist, plist, plist, plist, plist, plist, plist};

    list_init(plist);
    basic_string_init_elem(pbstr1, 10, plist);
    list_resize(plist, 5);
    _basic_string_copy_subcstr_auxiliary(pbstr1, pbstr1->_pby_string, ap_src, 5);
    for (i = 0; i < 10; ++i) {
        if (i < 5) {
            assert_true(list_size(basic_string_at(pbstr1, i)) == 5);
        } else {
            assert_true(list_size(basic_string_at(pbstr1, i)) == 0);
        }
    }

    basic_string_destroy(pbstr1);
    list_destroy(plist);
}
void test__basic_string_copy_subcstr_auxiliary__user_define(void** state)
{
    _test__basic_string_copy_auxiliary__t t_elem;
    _test__basic_string_copy_auxiliary__t* apt_src[] = {&t_elem, &t_elem, &t_elem, &t_elem, &t_elem};
    basic_string_t* pbstr1 = create_basic_string(_test__basic_string_copy_auxiliary__t);
    int i = 0;

    t_elem.a = 100;
    basic_string_init_elem(pbstr1, 10, &t_elem);
    t_elem.a = 0;
    _basic_string_copy_subcstr_auxiliary(pbstr1, pbstr1->_pby_string, apt_src, 5);
    for (i = 0; i < 10; ++i) {
        if (i < 5) {
            assert_true(((_test__basic_string_copy_auxiliary__t*)basic_string_at(pbstr1, i))->a == 0);
        } else {
            assert_true(((_test__basic_string_copy_auxiliary__t*)basic_string_at(pbstr1, i))->a == 100);
        }
    }

    basic_string_destroy(pbstr1);
}
void test__basic_string_copy_subcstr_auxiliary__include_terminator(void** state)
{
    int i = 0;
    basic_string_t* pbstr1 = create_basic_string(list_t<int>);
    list_t* plist = create_list(int);
    list_t* ap_src[] = {plist, plist, NULL, plist, plist, plist, plist};
    list_t terminator;

    list_init(plist);
    basic_string_init_elem(pbstr1, 10, plist);
    list_resize(plist, 5);
    _basic_string_copy_subcstr_auxiliary(pbstr1, pbstr1->_pby_string, ap_src, 5);
    for (i = 0; i < 10; ++i) {
        if (i < 5) {
            if (i == 2) {
                memset(&terminator, 0x00, sizeof(list_t));
                assert_true(memcmp(&terminator, basic_string_at(pbstr1, i), sizeof(list_t)) == 0);
            } else {
                assert_true(list_size(basic_string_at(pbstr1, i)) == 5);
            }
        } else {
            assert_true(list_size(basic_string_at(pbstr1, i)) == 0);
        }
    }

    basic_string_destroy(pbstr1);
    list_destroy(plist);
}

/*
 * test _basic_string_copy_range_auxiliary
 */
UT_CASE_DEFINATION(_basic_string_copy_range_auxiliary)
void test__basic_string_copy_range_auxiliary__null_bstr(void** state)
{
    list_t* plist = create_list(int);
    _byte_t by_dest[10];
    list_init(plist);
    expect_assert_failure(_basic_string_copy_range_auxiliary(NULL, by_dest, list_begin(plist), list_end(plist)));
    list_destroy(plist);
}
void test__basic_string_copy_range_auxiliary__non_created(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    list_t* plist = create_list(int);
    _byte_t aby_dest[10];

    list_init(plist);
    pbstr->_t_typeinfo._t_style = 9999;
    expect_assert_failure(_basic_string_copy_range_auxiliary(pbstr, aby_dest, list_begin(plist), list_end(plist)));
    pbstr->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    basic_string_destroy(pbstr);
    list_destroy(plist);
}
void test__basic_string_copy_range_auxiliary__null_dest(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    list_t* plist = create_list(int);
    list_init(plist);

    expect_assert_failure(_basic_string_copy_range_auxiliary(pbstr, NULL, list_begin(plist), list_end(plist)));
    basic_string_destroy(pbstr);
    list_destroy(plist);
}
void test__basic_string_copy_range_auxiliary__invalid_range(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    _byte_t aby_dest[10];
    list_t* plist = create_list(int);

    list_init_n(plist, 10);
    expect_assert_failure(_basic_string_copy_range_auxiliary(pbstr, aby_dest, list_end(plist), list_begin(plist)));
    basic_string_destroy(pbstr);
    list_destroy(plist);
}
void test__basic_string_copy_range_auxiliary__empty(void** state)
{
    basic_string_t* pbstr1 = create_basic_string(int);
    basic_string_t* pbstr2 = create_basic_string(int);

    basic_string_init_elem(pbstr1, 10, 111);
    basic_string_init_elem(pbstr2, 10, 0);
    _basic_string_copy_range_auxiliary(pbstr1, pbstr1->_pby_string, basic_string_begin(pbstr2), basic_string_begin(pbstr2));
    assert_true(*(int*)basic_string_at(pbstr1, 0) == 111);

    basic_string_destroy(pbstr1);
    basic_string_destroy(pbstr2);
}
void test__basic_string_copy_range_auxiliary__non_empty(void** state)
{
    int i = 0;
    basic_string_t* pbstr1 = create_basic_string(int);
    basic_string_t* pbstr2 = create_basic_string(int);

    basic_string_init_elem(pbstr1, 10, 111);
    basic_string_init(pbstr2);
    for (i = 0; i < 10; ++i) {
        basic_string_push_back(pbstr2, i);
    }
    _basic_string_copy_range_auxiliary(pbstr1, pbstr1->_pby_string, basic_string_begin(pbstr2), iterator_next_n(basic_string_begin(pbstr2), 5));
    for (i = 0; i < 10; ++i) {
        if (i < 5) {
            assert_true(*(int*)basic_string_at(pbstr1, i) == i);
        } else {
            assert_true(*(int*)basic_string_at(pbstr1, i) == 111);
        }
    }

    basic_string_destroy(pbstr1);
    basic_string_destroy(pbstr2);
}
void test__basic_string_copy_range_auxiliary__cstr(void** state)
{
    basic_string_t* pbstr1 = create_basic_string(char*);
    basic_string_t* pbstr2 = create_basic_string(char*);

    basic_string_init(pbstr1);
    basic_string_init(pbstr2);
    basic_string_push_back(pbstr1, "abc");
    basic_string_push_back(pbstr1, NULL);
    basic_string_push_back(pbstr1, NULL);
    basic_string_push_back(pbstr1, "abc");
    basic_string_push_back(pbstr2, "xyz");
    basic_string_push_back(pbstr2, "xyz");
    basic_string_push_back(pbstr2, NULL);
    basic_string_push_back(pbstr2, NULL);

    _basic_string_copy_range_auxiliary(pbstr1, pbstr1->_pby_string, basic_string_begin(pbstr2), basic_string_end(pbstr2));
    assert_true(strcmp((char*)basic_string_at(pbstr1, 0), "xyz") == 0);
    assert_true(strcmp((char*)basic_string_at(pbstr1, 1), "xyz") == 0);
    assert_true(basic_string_at(pbstr1, 2) == NULL);
    assert_true(basic_string_at(pbstr1, 3) == NULL);

    basic_string_destroy(pbstr1);
    basic_string_destroy(pbstr2);
}
void test__basic_string_copy_range_auxiliary__libcstl(void** state)
{
    basic_string_t* pbstr1 = create_basic_string(list_t<int>);
    basic_string_t* pbstr2 = create_basic_string(list_t<int>);
    list_t* plist = create_list(int);
    int i = 0;

    list_init(plist);
    basic_string_init_elem(pbstr1, 10, plist);
    basic_string_init(pbstr2);
    for (i = 0; i < 10; ++i) {
        list_resize(plist, i);
        basic_string_push_back(pbstr2, plist);
    }
    _basic_string_copy_range_auxiliary(pbstr1, pbstr1->_pby_string, basic_string_begin(pbstr2), iterator_next_n(basic_string_begin(pbstr2), 5));
    for (i = 0; i < 10; ++i) {
        if (i < 5) {
            assert_true(list_size(basic_string_at(pbstr1, i)) == i);
        } else {
            assert_true(list_size(basic_string_at(pbstr1, i)) == 0);
        }
    }

    basic_string_destroy(pbstr1);
    basic_string_destroy(pbstr2);
    list_destroy(plist);
}
void test__basic_string_copy_range_auxiliary__user_define(void** state)
{
    basic_string_t* pbstr1 = NULL;
    list_t* pbstr2 = NULL;
    _test__basic_string_copy_auxiliary__t t_elem;
    int i = 0;

    pbstr1 = create_basic_string(_test__basic_string_copy_auxiliary__t);
    pbstr2 = create_list(_test__basic_string_copy_auxiliary__t);
    t_elem.a = 100;
    basic_string_init_elem(pbstr1, 10, &t_elem);
    list_init(pbstr2);
    for (i = 0; i < 10; ++i) {
        t_elem.a = i;
        list_push_back(pbstr2, &t_elem);
    }
    _basic_string_copy_range_auxiliary(pbstr1, pbstr1->_pby_string, list_begin(pbstr2), iterator_advance(list_begin(pbstr2), 5));
    for (i = 0; i < 10; ++i) {
        if (i < 5) {
            assert_true(((_test__basic_string_copy_auxiliary__t*)basic_string_at(pbstr1, i))->a == i);
        } else {
            assert_true(((_test__basic_string_copy_auxiliary__t*)basic_string_at(pbstr1, i))->a == 100);
        }
    }

    basic_string_destroy(pbstr1);
    list_destroy(pbstr2);
}

/*
 * test _basic_string_copy_elem_auxiliary
 */
UT_CASE_DEFINATION(_basic_string_copy_elem_auxiliary)
static void _basic_string_copy_elem_auxiliary__wrapper(const basic_string_t* pbstr, _byte_t* pby_dest, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _basic_string_copy_elem_auxiliary(pbstr, pby_dest, t_count, val_elemlist);
    va_end(val_elemlist);
}
void test__basic_string_copy_elem_auxiliary__null_bstr(void** state)
{
    _byte_t by_dest[10];
    expect_assert_failure(_basic_string_copy_elem_auxiliary__wrapper(NULL, by_dest, 10, 10));
}
void test__basic_string_copy_elem_auxiliary__non_created(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    _byte_t aby_dest[10];

    pbstr->_t_typeinfo._t_style = 9999;
    expect_assert_failure(_basic_string_copy_elem_auxiliary__wrapper(pbstr, aby_dest, 10, 10));
    pbstr->_t_typeinfo._t_style = _TYPE_C_BUILTIN;
    basic_string_destroy(pbstr);
}
void test__basic_string_copy_elem_auxiliary__null_dest(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);

    expect_assert_failure(_basic_string_copy_elem_auxiliary__wrapper(pbstr, NULL, 10, 10));
    basic_string_destroy(pbstr);
}
void test__basic_string_copy_elem_auxiliary__invalid_len(void** state)
{
    basic_string_t* pbstr = create_basic_string(int);
    _byte_t aby_dest[10];
    expect_assert_failure(_basic_string_copy_elem_auxiliary__wrapper(pbstr, aby_dest, NPOS, 100));
    basic_string_destroy(pbstr);
}
void test__basic_string_copy_elem_auxiliary__empty(void** state)
{
    basic_string_t* pbstr1 = create_basic_string(int);

    basic_string_init_elem(pbstr1, 10, 111);
    _basic_string_copy_elem_auxiliary__wrapper(pbstr1, pbstr1->_pby_string, 0, 100);
    assert_true(*(int*)basic_string_at(pbstr1, 0) == 111);

    basic_string_destroy(pbstr1);
}
void test__basic_string_copy_elem_auxiliary__non_empty(void** state)
{
    basic_string_t* pbstr1 = create_basic_string(int);
    int i = 0;

    basic_string_init_elem(pbstr1, 10, 111);
    _basic_string_copy_elem_auxiliary__wrapper(pbstr1, pbstr1->_pby_string, 5, 0);
    for (i = 0; i < 10; ++i) {
        if (i < 5) {
            assert_true(*(int*)basic_string_at(pbstr1, i) == 0);
        } else {
            assert_true(*(int*)basic_string_at(pbstr1, i) == 111);
        }
    }

    basic_string_destroy(pbstr1);
}
void test__basic_string_copy_elem_auxiliary__cstr(void** state)
{
    int i = 0;
    basic_string_t* pbstr = create_basic_string(char*);
    basic_string_init_elem(pbstr, 10, "abc");

    _basic_string_copy_elem_auxiliary__wrapper(pbstr, pbstr->_pby_string, 5, NULL);
    for (i = 0; i < 10; ++i) {
        if (i < 5) {
            assert_true(basic_string_at(pbstr, i) == NULL);
        } else {
            assert_true(strcmp((char*)basic_string_at(pbstr, i), "abc") == 0);
        }
    }

    basic_string_destroy(pbstr);
}
void test__basic_string_copy_elem_auxiliary__libcstl(void** state)
{
    basic_string_t* pbstr1 = create_basic_string(list_t<int>);
    list_t* plist = create_list(int);
    int i = 0;

    list_init(plist);
    basic_string_init_elem(pbstr1, 10, plist);
    list_resize(plist, 10);
    _basic_string_copy_elem_auxiliary__wrapper(pbstr1, pbstr1->_pby_string, 5, plist);
    for (i = 0; i < 10; ++i) {
        if (i < 5) {
            assert_true(list_size(basic_string_at(pbstr1, i)) == 10);
        } else {
            assert_true(list_size(basic_string_at(pbstr1, i)) == 0);
        }
    }

    basic_string_destroy(pbstr1);
    list_destroy(plist);
}
void test__basic_string_copy_elem_auxiliary__user_define(void** state)
{
    basic_string_t* pbstr1 = NULL;
    _test__basic_string_copy_auxiliary__t t_elem;
    int i = 0;

    pbstr1 = create_basic_string(_test__basic_string_copy_auxiliary__t);
    t_elem.a = 100;
    basic_string_init_elem(pbstr1, 10, &t_elem);
    t_elem.a = 999;
    _basic_string_copy_elem_auxiliary__wrapper(pbstr1, pbstr1->_pby_string, 5, &t_elem);
    for (i = 0; i < 10; ++i) {
        if (i < 5) {
            assert_true(((_test__basic_string_copy_auxiliary__t*)basic_string_at(pbstr1, i))->a == 999);
        } else {
            assert_true(((_test__basic_string_copy_auxiliary__t*)basic_string_at(pbstr1, i))->a == 100);
        }
    }

    basic_string_destroy(pbstr1);
}

