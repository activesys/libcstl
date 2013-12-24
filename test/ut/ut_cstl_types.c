#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_alloc.h"
#include "cstl/cstl_types.h"
#include "cstl/cstring.h"
#include "cstl/clist.h"
#include "cstl/cslist.h"
#include "cstl/cdeque.h"
#include "cstl/cstack.h"
#include "cstl/cqueue.h"
#include "cstl/cset.h"
#include "cstl/cmap.h"
#include "cstl/chash_set.h"
#include "cstl/chash_map.h"
#include "cstl_types_builtin.h"
#include "cstl_types_aux.h"

#include "ut_def.h"
#include "ut_cstl_types.h"

UT_SUIT_DEFINATION(cstl_types, all_types)

/*
 * test _type_init_default
 */
UT_CASE_DEFINATION(_type_init_default)
void test__type_init_default__null_input(void** state)
{
    size_t output = 0;
    expect_assert_failure(_type_init_default(NULL, &output));
}

void test__type_init_default__null_output(void** state)
{
    int input = 0;
    expect_assert_failure(_type_init_default(&input, NULL));
}

void test__type_init_default__ok(void** state)
{
    int n_input = 10;
    bool_t b_output = sizeof(int);
    _type_init_default(&n_input, &b_output);
    assert_true(n_input == 0);
    assert_true(b_output == true);
}

/*
 * test _type_copy_default
 */
UT_CASE_DEFINATION(_type_copy_default)
void test__type_copy_defaule__null_first(void** state)
{
    int n_second = 0;
    bool_t b_output = sizeof(int);
    expect_assert_failure(_type_copy_default(NULL, &n_second, &b_output));
}

void test__type_copy_defaule__null_second(void** state)
{
    int n_first = 0;
    bool_t b_output = sizeof(int);
    expect_assert_failure(_type_copy_default(&n_first, NULL, &b_output));
}

void test__type_copy_defaule__null_output(void** state)
{
    int n_first = 10;
    int n_second = 0;
    expect_assert_failure(_type_copy_default(&n_first, &n_second, NULL));
}

void test__type_copy_defaule__ok(void** state)
{
    int n_first = 100;
    int n_second = -9;
    bool_t b_output = sizeof(int);
    _type_copy_default(&n_first, &n_second, &b_output);
    assert_true(n_first == -9);
    assert_true(n_second == -9);
    assert_true(b_output == true);
}

/*
 * test _type_less_default
 */
UT_CASE_DEFINATION(_type_less_default)
void test__type_less_defaule__null_first(void** state)
{
    int n_second = 0;
    bool_t b_output = sizeof(int);
    expect_assert_failure(_type_less_default(NULL, &n_second, &b_output));
}

void test__type_less_defaule__null_second(void** state)
{
    int n_first = 0;
    bool_t b_output = sizeof(int);
    expect_assert_failure(_type_less_default(&n_first, NULL, &b_output));
}

void test__type_less_defaule__null_output(void** state)
{
    int n_first = 10;
    int n_second = 0;
    expect_assert_failure(_type_less_default(&n_first, &n_second, NULL));
}

void test__type_less_defaule__less(void** state)
{
    int n_first = 0;
    int n_second = 9;
    bool_t b_output = sizeof(int);
    _type_less_default(&n_first, &n_second, &b_output);
    assert_true(n_first == 0);
    assert_true(n_second == 9);
    assert_true(b_output == true);
}

void test__type_less_defaule__equal(void** state)
{
    int n_first = 9;
    int n_second = 9;
    bool_t b_output = sizeof(int);
    _type_less_default(&n_first, &n_second, &b_output);
    assert_true(n_first == 9);
    assert_true(n_second == 9);
    assert_true(b_output == false);
}

void test__type_less_defaule__greater(void** state)
{
    int n_first = 9;
    int n_second = 0;
    bool_t b_output = sizeof(int);
    _type_less_default(&n_first, &n_second, &b_output);
    assert_true(n_first == 9);
    assert_true(n_second == 0);
    assert_true(b_output == false);
}

/*
 * test _type_destroy_default
 */
UT_CASE_DEFINATION(_type_destroy_default)
void test__type_destroy_default__null_input(void** state)
{
    size_t output = 0;
    expect_assert_failure(_type_destroy_default(NULL, &output));
}

void test__type_destroy_default__null_output(void** state)
{
    int input = 0;
    expect_assert_failure(_type_destroy_default(&input, NULL));
}

void test__type_destroy_default__ok(void** state)
{
    int n_input = 10;
    bool_t b_output = sizeof(int);
    _type_destroy_default(&n_input, &b_output);
    assert_true(n_input == 10);
    assert_true(b_output == true);
}

/*
 * test _type_get_varg_value
 */
UT_CASE_DEFINATION(_type_get_varg_value)
static void _test__get_type(_typeinfo_t* pt_info, const char* s_typename)
{
    _typenode_t* pt_node = NULL;
    assert_true(pt_info != NULL);
    assert_true(s_typename != NULL);

    strncpy(pt_info->_s_typename, s_typename, _TYPE_NAME_SIZE);
    pt_node = _gt_typeregister._apt_bucket[_type_hash(pt_info->_s_typename)];
    while (pt_node != NULL) {
        if (strncmp(pt_node->_s_typename, pt_info->_s_typename, _TYPE_NAME_SIZE) == 0) {
            pt_info->_pt_type = pt_node->_pt_type;
            return;
        }
        pt_node = pt_node->_pt_next;
    }
    assert_true(false);
}

static void _test__type_get_varg_value__stub(void* pv_output, _typeinfo_t* pt_info, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_info);
    _type_get_varg_value(pt_info, val_elemlist, pv_output);
    va_end(val_elemlist);
}

void test__type_get_varg_value__null_typeinof(void** state)
{
    int n_output = 0;
    va_list val_elemlist;
    expect_assert_failure(_type_get_varg_value(NULL, val_elemlist, &n_output));
}

void test__type_get_varg_value__invalid_typeinfo(void** state)
{
    _typeinfo_t info;
    int n_output = 0;
    va_list val_elemlist;
    info._pt_type = NULL;
    expect_assert_failure(_type_get_varg_value(&info, val_elemlist, &n_output));
}

void test__type_get_varg_value__invalid_typeinfo_style(void** state)
{
    _typeinfo_t t_info;
    int n_output = 0;
    va_list val_elemlist;
    _test__get_type(&t_info, "char");
    t_info._t_style = _TYPE_INVALID;
    expect_assert_failure(_type_get_varg_value(&t_info, val_elemlist, &n_output));
}

void test__type_get_varg_value__invalid_typeinfo_style2(void** state)
{
    _typeinfo_t t_info;
    int n_output = 0;
    va_list val_elemlist;
    _test__get_type(&t_info, "char");
    t_info._t_style = 100;
    expect_assert_failure(_type_get_varg_value(&t_info, val_elemlist, &n_output));
}

void test__type_get_varg_value__null_output(void** state)
{
    _typeinfo_t t_info;
    _test__get_type(&t_info, "char");
    t_info._t_style = _TYPE_C_BUILTIN;
    expect_assert_failure(_test__type_get_varg_value__stub(NULL, &t_info, 'c'));
}

void test__type_get_varg_value__char(void** state)
{
    _typeinfo_t t_info;
    char c_result = '\0';
    _test__get_type(&t_info, "char");
    t_info._t_style = _TYPE_C_BUILTIN;
    _test__type_get_varg_value__stub(&c_result, &t_info, 'c');
    assert_true(c_result == 'c');
}

void test__type_get_varg_value__uchar(void** state)
{
    _typeinfo_t t_info;
    unsigned char uc_result = '\0';
    _test__get_type(&t_info, "unsigned char");
    t_info._t_style = _TYPE_C_BUILTIN;
    _test__type_get_varg_value__stub(&uc_result, &t_info, 0x1a);
    assert_true(uc_result == 0x1a);
}

void test__type_get_varg_value__short(void** state)
{
    _typeinfo_t t_info;
    short h_result = 0;
    _test__get_type(&t_info, "short");
    t_info._t_style = _TYPE_C_BUILTIN;
    _test__type_get_varg_value__stub(&h_result, &t_info, -3333);
    assert_true(h_result == -3333);
}

void test__type_get_varg_value__ushort(void** state)
{
    _typeinfo_t t_info;
    unsigned short uh_result = 0;
    _test__get_type(&t_info, "unsigned short");
    t_info._t_style = _TYPE_C_BUILTIN;
    _test__type_get_varg_value__stub(&uh_result, &t_info, 3333);
    assert_true(uh_result == 3333);
}

void test__type_get_varg_value__int(void** state)
{
    _typeinfo_t t_info;
    int n_result = 0;
    _test__get_type(&t_info, "int");
    t_info._t_style = _TYPE_C_BUILTIN;
    _test__type_get_varg_value__stub(&n_result, &t_info, -3333);
    assert_true(n_result == -3333);
}

void test__type_get_varg_value__uint(void** state)
{
    _typeinfo_t t_info;
    unsigned int un_result = 0;
    _test__get_type(&t_info, "unsigned int");
    t_info._t_style = _TYPE_C_BUILTIN;
    _test__type_get_varg_value__stub(&un_result, &t_info, 3333);
    assert_true(un_result == 3333);
}

void test__type_get_varg_value__long(void** state)
{
    _typeinfo_t t_info;
    long l_result = 0;
    _test__get_type(&t_info, "long");
    t_info._t_style = _TYPE_C_BUILTIN;
    _test__type_get_varg_value__stub(&l_result, &t_info, -3333l);
    assert_true(l_result == -3333);
}

void test__type_get_varg_value__ulong(void** state)
{
    _typeinfo_t t_info;
    unsigned long ul_result = 0;
    _test__get_type(&t_info, "unsigned long");
    t_info._t_style = _TYPE_C_BUILTIN;
    _test__type_get_varg_value__stub(&ul_result, &t_info, 3333);
    assert_true(ul_result == 3333);
}

void test__type_get_varg_value__float(void** state)
{
    _typeinfo_t t_info;
    float f_result = 0;
    _test__get_type(&t_info, "float");
    t_info._t_style = _TYPE_C_BUILTIN;
    _test__type_get_varg_value__stub(&f_result, &t_info, -45.09f);
    assert_true(f_result - (-45.09f) >= -FLT_EPSILON && f_result - (-45.09f) <= FLT_EPSILON);
}

void test__type_get_varg_value__double(void** state)
{
    _typeinfo_t t_info;
    double d_result = 0;
    _test__get_type(&t_info, "double");
    t_info._t_style = _TYPE_C_BUILTIN;
    _test__type_get_varg_value__stub(&d_result, &t_info, -3333.3333);
    assert_true(d_result - (-3333.3333) >= -DBL_EPSILON && d_result - (-3333.3333) <= DBL_EPSILON);
}

void test__type_get_varg_value__ldouble(void** state)
{
    _typeinfo_t t_info;
    long double ld_result = 0;
    _test__get_type(&t_info, "long double");
    t_info._t_style = _TYPE_C_BUILTIN;
    _test__type_get_varg_value__stub(&ld_result, &t_info, 3333.3333);
    assert_true(ld_result - 3333.3333 >= -LDBL_EPSILON && ld_result - 3333.3333 <= LDBL_EPSILON);
}

void test__type_get_varg_value__bool(void** state)
{
    _typeinfo_t t_info;
    bool_t b_result = false;
    _test__get_type(&t_info, "bool_t");
    t_info._t_style = _TYPE_C_BUILTIN;
    _test__type_get_varg_value__stub(&b_result, &t_info, true);
    assert_true(b_result == true);
}

void test__type_get_varg_value__cstr(void** state)
{
    _typeinfo_t t_info;
    string_t* pstr_result = create_string();
    _test__get_type(&t_info, "char*");
    t_info._t_style = _TYPE_C_BUILTIN;
    string_init(pstr_result);
    _test__type_get_varg_value__stub(pstr_result, &t_info, "linux");
    assert_true(strcmp(string_c_str(pstr_result), "linux") == 0);
    string_destroy(pstr_result);
}

typedef struct _test__type_get_varg_value{
    int n_a;
    int n_b;
    int n_c;
}_test__type_get_varg_value_t;
void test__type_get_varg_value__invalid_c_builtin(void** state)
{
    _typeinfo_t t_info;
    _test__type_get_varg_value_t t_result;
    _test__type_get_varg_value_t t_input;
    type_register(_test__type_get_varg_value_t, NULL, NULL, NULL, NULL);
    _test__get_type(&t_info, "_test__type_get_varg_value_t");
    t_info._t_style = _TYPE_C_BUILTIN;
    expect_assert_failure(_test__type_get_varg_value__stub(&t_result, &t_info, &t_input));
}

void test__type_get_varg_value__user_define(void** state)
{
    _typeinfo_t t_info;
    _test__type_get_varg_value_t t_result = {0, 0, 0};
    _test__type_get_varg_value_t t_input = {10, 20, 30};
    _test__get_type(&t_info, "_test__type_get_varg_value_t");
    t_info._t_style = _TYPE_USER_DEFINE;
    _test__type_get_varg_value__stub(&t_result, &t_info, &t_input);
    assert_true(t_result.n_a == 10 && t_result.n_b == 20 && t_result.n_c == 30);
}

void test__type_get_varg_value__cstl_builtin(void** state)
{
    _typeinfo_t t_info;
    size_t i = 0;
    vector_t* pvec_result = create_vector(int);
    vector_t* pvec_input = create_vector(int);
    _test__get_type(&t_info, "vector_t");
    t_info._t_style = _TYPE_CSTL_BUILTIN;
    vector_init(pvec_result);
    vector_init_elem(pvec_input, 10, 100);
    _test__type_get_varg_value__stub(pvec_result, &t_info, pvec_input);
    assert_true(vector_size(pvec_result) == 10);
    for (i = 0; i < 10; ++i) {
        assert_true(*(int*)vector_at(pvec_result, i) == 100);
    }
    vector_destroy(pvec_result);
    vector_destroy(pvec_input);
}

/*
 * test _type_get_elem_typename
 */
UT_CASE_DEFINATION(_type_get_elem_typename)
void test__type_get_elem_typename__null_typename(void** state)
{
    char s_elemtypename[_TYPE_NAME_SIZE + 1] = {'\0'};
    expect_assert_failure(_type_get_elem_typename(NULL, s_elemtypename));
}

void test__type_get_elem_typename__null_elemtypename(void** state)
{
    expect_assert_failure(_type_get_elem_typename("iterator_t", NULL));
}

void test__type_get_elem_typename__iterator(void** state)
{
    char s_elemtypename[_TYPE_NAME_SIZE + 1] = {'\0'};
    _type_get_elem_typename("vector_iterator_t", s_elemtypename);
    assert_true(strncmp(s_elemtypename, "vector_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_elem_typename__string(void** state)
{
    char s_elemtypename[_TYPE_NAME_SIZE + 1] = {'\0'};
    _type_get_elem_typename("string_t", s_elemtypename);
    assert_true(strncmp(s_elemtypename, "string_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_elem_typename__invliad_typename(void** state)
{
    char s_elemtypename[_TYPE_NAME_SIZE + 1] = {'\0'};
    expect_assert_failure(_type_get_elem_typename("abc_t", s_elemtypename));
}

void test__type_get_elem_typename__container(void** state)
{
    char s_elemtypename[_TYPE_NAME_SIZE + 1] = {'\0'};
    _type_get_elem_typename("hash_set_t<vector_t<abc_t>>", s_elemtypename);
    assert_true(strncmp(s_elemtypename, "vector_t<abc_t>", _TYPE_NAME_SIZE) == 0);
}

/*
 * test _type_is_same
 */
UT_CASE_DEFINATION(_type_is_same)
void test__type_is_same__null_typename1(void** state)
{
    expect_assert_failure(_type_is_same(NULL, "int"));
}

void test__type_is_same__null_typename2(void** state)
{
    expect_assert_failure(_type_is_same("int", NULL));
}

void test__type_is_same__c_c_same(void** state)
{
    assert_true(_type_is_same("int", "int") == true);
}

void test__type_is_same__c_c_duplicate(void** state)
{
    assert_true(_type_is_same("int", "signed") == true);
}

void test__type_is_same__c_c_not_same(void** state)
{
    assert_true(_type_is_same("int", "long") == false);
}

typedef struct _test__type_is_same {
    int n_elem;
}_test__type_is_same_t;
void test__type_is_same__c_user_not_same(void** state)
{
    type_register(struct _test__type_is_same, NULL, NULL, NULL, NULL);
    assert_true(_type_is_same("int", "struct _test__type_is_same") == false);
}

void test__type_is_same__c_string_not_same(void** state)
{
    assert_true(_type_is_same("int", "string_t") == false);
}

void test__type_is_same__c_iterator_not_same(void** state)
{
    assert_true(_type_is_same("int", "iterator_t") == false);
}

void test__type_is_same__c_cstl_not_same(void** state)
{
    assert_true(_type_is_same("int", "vector_t<int>") == false);
}

void test__type_is_same__user_user_same(void** state)
{
    assert_true(_type_is_same("struct _test__type_is_same", "struct _test__type_is_same") == true);
}

void test__type_is_same__user_user_not_same(void** state)
{
    assert_true(_type_is_same("struct _test__type_is_same", "_test__type_is_same_t") == false);
}

void test__type_is_same__user_user_duplicate(void** state)
{
    type_duplicate(struct _test__type_is_same, _test__type_is_same_t);
    assert_true(_type_is_same("_test__type_is_same_t", "struct _test__type_is_same") == true);
}

void test__type_is_same__user_cstl_not_same(void** state)
{
    assert_true(_type_is_same("_test__type_is_same_t", "list_t<int>") == false);
}

void test__type_is_same__string_iterator_not_same(void** state)
{
    assert_true(_type_is_same("string_t", "vector_iterator_t") == false);
}

void test__type_is_same__cstl_cstl_same(void** state)
{
    assert_true(_type_is_same("deque_t<int>", "deque_t<signed>") == true);
}

void test__type_is_same__cstl_cstl_elem_not_same(void** state)
{
    assert_true(_type_is_same("slist_t<long>", "slist_t<double>") == false);
}

void test__type_is_same__cstl_cstl_container_not_same(void** state)
{
    assert_true(_type_is_same("set_t<int>", "stack_t<int>") == false);
}

void test__type_is_same__cstl_cstl_seq_rel_not_same(void** state)
{
    assert_true(_type_is_same("set_t<int>", "map_t<int,int>") == false);
}

void test__type_is_same__cstl_cstl_first_not_same(void** state)
{
    assert_true(_type_is_same("map_t<int,double>", "map_t<long,double>") == false);
}

void test__type_is_same__cstl_cstl_second_not_same(void** state)
{
    assert_true(_type_is_same("map_t<int,double>", "map_t<int,short>") == false);
}

void test__type_is_same__cstl_cstl_rel_not_same(void** state)
{
    assert_true(_type_is_same("map_t<int,double>", "hash_map_t<int,double>") == false);
}

void test__type_is_same__cstl_cstl_same_complex(void** state)
{
    assert_true(_type_is_same("hash_set_t<pair_t<vector_t<_test__type_is_same_t>,list_t<queue_t<int>>>>",
                "hash_set_t<pair_t<vector_t<struct _test__type_is_same>,list_t<queue_t<signed int>>>>") == true);
}

void test__type_is_same__cstl_cstl_invalid(void** state)
{
    assert_true(_type_is_same("pair_t<int<abcdefg,abc>>>>>>,long<pair_t,vector_t<int>,double>", "pair_t<int<dddd>abcdefg") == false);
}

/*
 * test _type_is_same_ex
 */
UT_CASE_DEFINATION(_type_is_same_ex)
void test__type_is_same_ex__null_first(void** state)
{
    _typeinfo_t t_second;
    expect_assert_failure(_type_is_same_ex(NULL, &t_second));
}

void test__type_is_same_ex__null_second(void** state)
{
    _typeinfo_t t_first;
    expect_assert_failure(_type_is_same_ex(&t_first, NULL));
}

void test__type_is_same_ex__same_typeinfo(void** state)
{
    _typeinfo_t t_info;
    _test__get_type(&t_info, "int");
    assert_true(_type_is_same_ex(&t_info, &t_info) == true);
}

void test__type_is_same_ex__not_same_type(void** state)
{
    _typeinfo_t t_first;
    _typeinfo_t t_second;
    _test__get_type(&t_first, "int");
    t_first._t_style = _TYPE_C_BUILTIN;
    _test__get_type(&t_second, "long");
    t_second._t_style = _TYPE_C_BUILTIN;
    assert_true(_type_is_same_ex(&t_first, &t_second) == false);
}

void test__type_is_same_ex__not_same_style(void** state)
{
    _typeinfo_t t_first;
    _typeinfo_t t_second;
    _test__get_type(&t_first, "int");
    t_first._t_style = _TYPE_C_BUILTIN;
    _test__get_type(&t_second, "int");
    t_second._t_style = _TYPE_USER_DEFINE;
    assert_true(_type_is_same_ex(&t_first, &t_second) == false);
}

void test__type_is_same_ex__same(void** state)
{
    _typeinfo_t t_first;
    _typeinfo_t t_second;
    _test__get_type(&t_first, "int");
    t_first._t_style = _TYPE_C_BUILTIN;
    _test__get_type(&t_second, "signed");
    t_second._t_style = _TYPE_C_BUILTIN;
    assert_true(_type_is_same_ex(&t_first, &t_second) == true);
}

/*
 * test _type_get_type
 */
UT_CASE_DEFINATION(_type_get_type)
void test__type_get_type__null_typeinfo(void** state)
{
    expect_assert_failure(_type_get_type(NULL, "int"));
}

void test__type_get_type__null_typename(void** state)
{
    _typeinfo_t t_info;
    expect_assert_failure(_type_get_type(&t_info, NULL));
}

void test__type_get_type__invalid(void** state)
{
    _typeinfo_t t_info;
    _type_get_type(&t_info, "abcdefg_t");
    assert_true(t_info._t_style == _TYPE_INVALID);
    assert_true(t_info._pt_type == NULL);
}

void test__type_get_type__c_builtin(void** state)
{
    _typeinfo_t t_info;
    _type_get_type(&t_info, "unsigned    int");
    assert_true(t_info._t_style == _TYPE_C_BUILTIN);
    assert_true(strncmp(t_info._s_typename, "unsigned int", _TYPE_NAME_SIZE) == 0);
    assert_true(t_info._pt_type != NULL);
    assert_true(t_info._pt_type->_t_typesize == sizeof(unsigned int));
    assert_true(strncmp(t_info._pt_type->_s_typename, "unsigned int", _TYPE_NAME_SIZE) == 0);
    assert_true(t_info._pt_type->_t_typeinit == _type_init_uint);
    assert_true(t_info._pt_type->_t_typeless == _type_less_uint);
    assert_true(t_info._pt_type->_t_typecopy == _type_copy_uint);
    assert_true(t_info._pt_type->_t_typedestroy == _type_destroy_uint);
}

typedef struct _test__type_get_type
{
    int n_elem;
}_test__type_get_type_t;
void test__type_get_type__user_define(void** state)
{
    _typeinfo_t t_info;
    type_register(struct _test__type_get_type, NULL, NULL, NULL, NULL);
    type_duplicate(struct _test__type_get_type, _test__type_get_type_t);
    _type_get_type(&t_info, "_test__type_get_type_t");
    assert_true(t_info._t_style == _TYPE_USER_DEFINE);
    assert_true(strncmp(t_info._s_typename, "_test__type_get_type_t", _TYPE_NAME_SIZE) == 0);
    assert_true(t_info._pt_type != NULL);
    assert_true(t_info._pt_type->_t_typesize == sizeof(_test__type_get_type_t));
    assert_true(strncmp(t_info._pt_type->_s_typename, "struct _test__type_get_type", _TYPE_NAME_SIZE) == 0);
    assert_true(t_info._pt_type->_t_typeinit == _type_init_default);
    assert_true(t_info._pt_type->_t_typeless == _type_less_default);
    assert_true(t_info._pt_type->_t_typecopy == _type_copy_default);
    assert_true(t_info._pt_type->_t_typedestroy == _type_destroy_default);
}

void test__type_get_type__cstl_iterator(void** state)
{
    _typeinfo_t t_info;
    _type_get_type(&t_info, "vector_iterator_t");
    assert_true(t_info._t_style == _TYPE_CSTL_BUILTIN);
    assert_true(strncmp(t_info._s_typename, "vector_iterator_t", _TYPE_NAME_SIZE) == 0);
    assert_true(t_info._pt_type != NULL);
    assert_true(t_info._pt_type->_t_typesize == sizeof(iterator_t));
    assert_true(strncmp(t_info._pt_type->_s_typename, "iterator_t", _TYPE_NAME_SIZE) == 0);
    assert_true(t_info._pt_type->_t_typeinit == _type_init_iterator);
    assert_true(t_info._pt_type->_t_typeless == _type_less_iterator);
    assert_true(t_info._pt_type->_t_typecopy == _type_copy_iterator);
    assert_true(t_info._pt_type->_t_typedestroy == _type_destroy_iterator);
}

void test__type_get_type__cstl_container(void** state)
{
    _typeinfo_t t_info;
    _type_get_type(&t_info, "deque_t<int>");
    assert_true(t_info._t_style == _TYPE_CSTL_BUILTIN);
    assert_true(strncmp(t_info._s_typename, "deque_t<int>", _TYPE_NAME_SIZE) == 0);
    assert_true(t_info._pt_type != NULL);
    assert_true(t_info._pt_type->_t_typesize == sizeof(deque_t));
    assert_true(strncmp(t_info._pt_type->_s_typename, "deque_t", _TYPE_NAME_SIZE) == 0);
    assert_true(t_info._pt_type->_t_typeinit == _type_init_deque);
    assert_true(t_info._pt_type->_t_typeless == _type_less_deque);
    assert_true(t_info._pt_type->_t_typecopy == _type_copy_deque);
    assert_true(t_info._pt_type->_t_typedestroy == _type_destroy_deque);
}

/*
 * test _type_get_type_pair
 */
UT_CASE_DEFINATION(_type_get_type_pair)
void test__type_get_type_pair__null_first(void** state)
{
    _typeinfo_t t_info;
    expect_assert_failure(_type_get_type_pair(NULL, &t_info, "int,int"));
}

void test__type_get_type_pair__null_second(void** state)
{
    _typeinfo_t t_info;
    expect_assert_failure(_type_get_type_pair(&t_info, NULL, "int,int"));
}

void test__type_get_type_pair__null_typename(void** state)
{
    _typeinfo_t t_first;
    _typeinfo_t t_second;
    expect_assert_failure(_type_get_type_pair(&t_first, &t_second, NULL));
}

void test__type_get_type_pair__c_c(void** state)
{
    _typeinfo_t t_first;
    _typeinfo_t t_second;
    _type_get_type_pair(&t_first, &t_second, "int,double");
    assert_true(t_first._t_style == _TYPE_C_BUILTIN);
    assert_true(strncmp(t_first._s_typename, "int", _TYPE_NAME_SIZE) == 0);
    assert_true(t_first._pt_type != NULL);
    assert_true(t_second._t_style == _TYPE_C_BUILTIN);
    assert_true(strncmp(t_second._s_typename, "double", _TYPE_NAME_SIZE) == 0);
    assert_true(t_second._pt_type != NULL);
}

void test__type_get_type_pair__c_user(void** state)
{
    _typeinfo_t t_first;
    _typeinfo_t t_second;
    _type_get_type_pair(&t_first, &t_second, "int,_test__type_get_type_t");
    assert_true(t_first._t_style == _TYPE_C_BUILTIN);
    assert_true(strncmp(t_first._s_typename, "int", _TYPE_NAME_SIZE) == 0);
    assert_true(t_first._pt_type != NULL);
    assert_true(t_second._t_style == _TYPE_USER_DEFINE);
    assert_true(strncmp(t_second._s_typename, "_test__type_get_type_t", _TYPE_NAME_SIZE) == 0);
    assert_true(t_second._pt_type != NULL);
}

void test__type_get_type_pair__c_iterator(void** state)
{
    _typeinfo_t t_first;
    _typeinfo_t t_second;
    _type_get_type_pair(&t_first, &t_second, "bool_t,deque_iterator_t");
    assert_true(t_first._t_style == _TYPE_C_BUILTIN);
    assert_true(strncmp(t_first._s_typename, "bool_t", _TYPE_NAME_SIZE) == 0);
    assert_true(t_first._pt_type != NULL);
    assert_true(t_second._t_style == _TYPE_CSTL_BUILTIN);
    assert_true(strncmp(t_second._s_typename, "deque_iterator_t", _TYPE_NAME_SIZE) == 0);
    assert_true(t_second._pt_type != NULL);
}

void test__type_get_type_pair__c_seq(void** state)
{
    _typeinfo_t t_first;
    _typeinfo_t t_second;
    _type_get_type_pair(&t_first, &t_second, "bool_t,list_t<int>");
    assert_true(t_first._t_style == _TYPE_C_BUILTIN);
    assert_true(strncmp(t_first._s_typename, "bool_t", _TYPE_NAME_SIZE) == 0);
    assert_true(t_first._pt_type != NULL);
    assert_true(t_second._t_style == _TYPE_CSTL_BUILTIN);
    assert_true(strncmp(t_second._s_typename, "list_t<int>", _TYPE_NAME_SIZE) == 0);
    assert_true(t_second._pt_type != NULL);
}

void test__type_get_type_pair__c_rel(void** state)
{
    _typeinfo_t t_first;
    _typeinfo_t t_second;
    _type_get_type_pair(&t_first, &t_second, "bool_t,map_t<int,double>");
    assert_true(t_first._t_style == _TYPE_C_BUILTIN);
    assert_true(strncmp(t_first._s_typename, "bool_t", _TYPE_NAME_SIZE) == 0);
    assert_true(t_first._pt_type != NULL);
    assert_true(t_second._t_style == _TYPE_CSTL_BUILTIN);
    assert_true(strncmp(t_second._s_typename, "map_t<int,double>", _TYPE_NAME_SIZE) == 0);
    assert_true(t_second._pt_type != NULL);
}

void test__type_get_type_pair__usr_usr(void** state)
{
    _typeinfo_t t_first;
    _typeinfo_t t_second;
    _type_get_type_pair(&t_first, &t_second, "_test__type_get_type_t,struct _test__type_get_type");
    assert_true(t_first._t_style == _TYPE_USER_DEFINE);
    assert_true(strncmp(t_first._s_typename, "_test__type_get_type_t", _TYPE_NAME_SIZE) == 0);
    assert_true(t_first._pt_type != NULL);
    assert_true(t_second._t_style == _TYPE_USER_DEFINE);
    assert_true(strncmp(t_second._s_typename, "struct _test__type_get_type", _TYPE_NAME_SIZE) == 0);
    assert_true(t_second._pt_type != NULL);
}

void test__type_get_type_pair__usr_string(void** state)
{
    _typeinfo_t t_first;
    _typeinfo_t t_second;
    _type_get_type_pair(&t_first, &t_second, "_test__type_get_type_t,string_t");
    assert_true(t_first._t_style == _TYPE_USER_DEFINE);
    assert_true(strncmp(t_first._s_typename, "_test__type_get_type_t", _TYPE_NAME_SIZE) == 0);
    assert_true(t_first._pt_type != NULL);
    assert_true(t_second._t_style == _TYPE_CSTL_BUILTIN);
    assert_true(strncmp(t_second._s_typename, "string_t", _TYPE_NAME_SIZE) == 0);
    assert_true(t_second._pt_type != NULL);
}

void test__type_get_type_pair__seq_seq(void** state)
{
    _typeinfo_t t_first;
    _typeinfo_t t_second;
    _type_get_type_pair(&t_first, &t_second, "vector_t<int>,slist_t<int>");
    assert_true(t_first._t_style == _TYPE_CSTL_BUILTIN);
    assert_true(strncmp(t_first._s_typename, "vector_t<int>", _TYPE_NAME_SIZE) == 0);
    assert_true(t_first._pt_type != NULL);
    assert_true(t_second._t_style == _TYPE_CSTL_BUILTIN);
    assert_true(strncmp(t_second._s_typename, "slist_t<int>", _TYPE_NAME_SIZE) == 0);
    assert_true(t_second._pt_type != NULL);
}

void test__type_get_type_pair__seq_rel(void** state)
{
    _typeinfo_t t_first;
    _typeinfo_t t_second;
    _type_get_type_pair(&t_first, &t_second, "vector_t<int>,pair_t<int,int>");
    assert_true(t_first._t_style == _TYPE_CSTL_BUILTIN);
    assert_true(strncmp(t_first._s_typename, "vector_t<int>", _TYPE_NAME_SIZE) == 0);
    assert_true(t_first._pt_type != NULL);
    assert_true(t_second._t_style == _TYPE_CSTL_BUILTIN);
    assert_true(strncmp(t_second._s_typename, "pair_t<int,int>", _TYPE_NAME_SIZE) == 0);
    assert_true(t_second._pt_type != NULL);
}

void test__type_get_type_pair__rel_rel(void** state)
{
    _typeinfo_t t_first;
    _typeinfo_t t_second;
    _type_get_type_pair(&t_first, &t_second, "hash_map_t<double,int>,pair_t<int,int>");
    assert_true(t_first._t_style == _TYPE_CSTL_BUILTIN);
    assert_true(strncmp(t_first._s_typename, "hash_map_t<double,int>", _TYPE_NAME_SIZE) == 0);
    assert_true(t_first._pt_type != NULL);
    assert_true(t_second._t_style == _TYPE_CSTL_BUILTIN);
    assert_true(strncmp(t_second._s_typename, "pair_t<int,int>", _TYPE_NAME_SIZE) == 0);
    assert_true(t_second._pt_type != NULL);
}

void test__type_get_type_pair__complex(void** state)
{
    _typeinfo_t t_first;
    _typeinfo_t t_second;
    _type_get_type_pair(&t_first, &t_second, "hash_map_t<double,slist_t<pair_t<int,_test__type_get_type_t>>>,pair_t<int,vector_t<stack_t<deque_t<int>>>>");
    assert_true(t_first._t_style == _TYPE_CSTL_BUILTIN);
    assert_true(strncmp(t_first._s_typename, "hash_map_t<double,slist_t<pair_t<int,_test__type_get_type_t>>>", _TYPE_NAME_SIZE) == 0);
    assert_true(t_first._pt_type != NULL);
    assert_true(t_second._t_style == _TYPE_CSTL_BUILTIN);
    assert_true(strncmp(t_second._s_typename, "pair_t<int,vector_t<stack_t<deque_t<int>>>>", _TYPE_NAME_SIZE) == 0);
    assert_true(t_second._pt_type != NULL);
}

void test__type_get_type_pair__invalid(void** state)
{
    _typeinfo_t t_first;
    _typeinfo_t t_second;
    _type_get_type_pair(&t_first, &t_second, "hash_map_t<double,slist_t<pair_t<int,_test__type_get_type_t>>>pair_t<int,vector_t<stack_t<deque_t<int>>>>");
    assert_true(t_first._t_style == _TYPE_INVALID);
    assert_true(t_first._pt_type == NULL);
    assert_true(t_second._t_style == _TYPE_INVALID);
    assert_true(t_second._pt_type == NULL);
}

/*
 * test _type_duplicate
 */
UT_CASE_DEFINATION(_type_duplicate)
void test__type_duplicate__null_typename1(void** state)
{
    expect_assert_failure(_type_duplicate(sizeof(int), NULL, sizeof(long), "long"));
}

void test__type_duplicate__null_typename2(void** state)
{
    expect_assert_failure(_type_duplicate(sizeof(int), "int", sizeof(long), NULL));
}

typedef struct _test__type_duplicate1 {
    int n_a;
    int n_b;
}_test__type_duplicate1_t;
typedef struct _test__type_duplicate2 {
    int n_a;
    int n_b;
}_test__type_duplicate2_t;
void test__type_duplicate__size_not_equal(void** state)
{
    assert_true(_type_duplicate(sizeof(_test__type_duplicate2_t), "_test__type_duplicate2_t", sizeof(int), "int") == false);
}

void test__type_duplicate__all_not_registered(void** state)
{
    assert_true(_type_duplicate(sizeof(_test__type_duplicate1_t), "_test__type_duplicate1_t", 
                sizeof(_test__type_duplicate2_t), "_test__type_duplicate2_t") == false);
}

void test__type_duplicate__all_registered(void** state)
{
    type_register(_test__type_duplicate1_t, NULL, NULL, NULL, NULL);
    type_register(_test__type_duplicate2_t, NULL, NULL, NULL, NULL);
    assert_true(_type_duplicate(sizeof(_test__type_duplicate1_t), "_test__type_duplicate1_t",
                sizeof(_test__type_duplicate2_t), "_test__type_duplicate2_t") == false);
}

void test__type_duplicate__all_registered_same(void** state)
{
    assert_true(_type_duplicate(sizeof(_test__type_duplicate1_t), "_test__type_duplicate1_t",
                sizeof(_test__type_duplicate1_t), "_test__type_duplicate1_t") == true);
}

void test__type_duplicate__duplicate_first(void** state)
{
    assert_true(_type_duplicate(sizeof(_test__type_duplicate1_t), "_test__type_duplicate1_t",
                sizeof(struct _test__type_duplicate1), "struct _test__type_duplicate1") == true);
    assert_true(_type_is_registered("struct _test__type_duplicate1") != NULL);
}

void test__type_duplicate__duplicate_second(void** state)
{
    assert_true(_type_duplicate(sizeof(struct _test__type_duplicate2), "struct _test__type_duplicate2",
                sizeof(_test__type_duplicate2_t), "_test__type_duplicate2_t") == true);
    assert_true(_type_is_registered("struct _test__type_duplicate2") != NULL);
}

/*
 * test _type_register
 */
UT_CASE_DEFINATION(_type_register)
typedef struct _test__type_register1 {
    int n_elem;
}_test__type_register1_t;
typedef struct _test__type_register2 {
    int n_elem;
}_test__type_register2_t;
static void _test__type_register2_init(const void* cpv_input, void* pv_output)
{
}
static void _test__type_register2_copy(const void* cpv_first, const void* cpv_second, void* pv_output)
{
}
static void _test__type_register2_less(const void* cpv_first, const void* cpv_second, void* pv_output)
{
}
static void _test__type_register2_destroy(const void* cpv_input, void* pv_output)
{
}

void test__type_register__null_typename(void** state)
{
    expect_assert_failure(_type_register(sizeof(int), NULL, NULL, NULL, NULL, NULL));
}

void test__type_register__registered(void** state)
{
    assert_true(_type_register(sizeof(_test__type_duplicate2_t), "_test__type_duplicate2_t", NULL, NULL, NULL, NULL) == false);
}

void test__type_register__register_default(void** state)
{
    _type_t* pt_type = NULL;
    assert_true(_type_register(sizeof(_test__type_register1_t), "_test__type_register1_t", NULL, NULL, NULL, NULL) == true);
    pt_type = _type_is_registered("_test__type_register1_t");
    assert_true(pt_type != NULL);
    assert_true(pt_type->_t_typesize == sizeof(_test__type_register1_t));
    assert_true(strncmp(pt_type->_s_typename, "_test__type_register1_t", _TYPE_NAME_SIZE) == 0);
    assert_true(pt_type->_t_style == _TYPE_USER_DEFINE);
    assert_true(pt_type->_t_typeinit == _type_init_default);
    assert_true(pt_type->_t_typeless == _type_less_default);
    assert_true(pt_type->_t_typecopy == _type_copy_default);
    assert_true(pt_type->_t_typedestroy == _type_destroy_default);
}

void test__type_register__register(void** state)
{
    _type_t* pt_type = NULL;
    assert_true(_type_register(sizeof(_test__type_register2_t), "_test__type_register2_t",
                _test__type_register2_init, _test__type_register2_copy, _test__type_register2_less, _test__type_register2_destroy) == true);
    pt_type = _type_is_registered("_test__type_register2_t");
    assert_true(pt_type != NULL);
    assert_true(pt_type->_t_typesize == sizeof(_test__type_register2_t));
    assert_true(strncmp(pt_type->_s_typename, "_test__type_register2_t", _TYPE_NAME_SIZE) == 0);
    assert_true(pt_type->_t_style == _TYPE_USER_DEFINE);
    assert_true(pt_type->_t_typeinit == _test__type_register2_init);
    assert_true(pt_type->_t_typeless == _test__type_register2_less);
    assert_true(pt_type->_t_typecopy == _test__type_register2_copy);
    assert_true(pt_type->_t_typedestroy == _test__type_register2_destroy);
}

/*
 * test all_types
 */
UT_CASE_DEFINATION(all_types)
void test__all_types__char(void** state)
{
    vector_t* pvec = create_vector(char);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__signed_char(void** state)
{
    vector_t* pvec = create_vector(signed char);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__unsigned_char(void** state)
{
    vector_t* pvec = create_vector(unsigned char);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__short(void** state)
{
    vector_t* pvec = create_vector(short);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__signed_short(void** state)
{
    vector_t* pvec = create_vector(signed short);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__short_int(void** state)
{
    vector_t* pvec = create_vector(short int);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__signed_short_int(void** state)
{
    vector_t* pvec = create_vector(signed short int);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__unsigned_short(void** state)
{
    vector_t* pvec = create_vector(unsigned short);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__unsigned_short_int(void** state)
{
    vector_t* pvec = create_vector(unsigned short int);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__int(void** state)
{
    vector_t* pvec = create_vector(int);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__signed(void** state)
{
    vector_t* pvec = create_vector(signed );
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__signed_int(void** state)
{
    vector_t* pvec = create_vector(signed int);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__unsigned(void** state)
{
    vector_t* pvec = create_vector(unsigned);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__unsigned_int(void** state)
{
    vector_t* pvec = create_vector(unsigned int);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__long(void** state)
{
    vector_t* pvec = create_vector(long);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__signed_long(void** state)
{
    vector_t* pvec = create_vector(signed long);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__long_int(void** state)
{
    vector_t* pvec = create_vector(long int);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__signed_long_int(void** state)
{
    vector_t* pvec = create_vector(signed long int);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__unsigned_long(void** state)
{
    vector_t* pvec = create_vector( unsigned  long );
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__unsigned_long_int(void** state)
{
    vector_t* pvec = create_vector(unsigned long int);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__float(void** state)
{
    vector_t* pvec = create_vector(float);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__double(void** state)
{
    vector_t* pvec = create_vector(double);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__long_double(void** state)
{
    vector_t* pvec = create_vector(long double);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__cstr(void** state)
{
    vector_t* pvec = create_vector(char *);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__pointer(void** state)
{
    vector_t* pvec = create_vector(void*);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

struct abc {
    int a;
    int b;
};
void test__all_types__struct(void** state)
{
    vector_t* pvec = NULL;
    type_register(struct abc, NULL, NULL, NULL, NULL);
    pvec = create_vector(struct abc);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

enum def {
    AAA, BBB
};
void test__all_types__enum(void** state)
{
    vector_t* pvec = NULL;
    type_register(enum def, NULL, NULL, NULL, NULL);
    pvec = create_vector(enum def);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

union hij {
    int a;
    struct xyz {
        short b;
        short c;
    } xxx;
};
void test__all_types__union(void** state)
{
    vector_t* pvec = NULL;
    type_register(union hij, NULL, NULL, NULL, NULL);
    pvec = create_vector(union hij);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

typedef struct ooo {
    int a;
    int b;
} ooo_t;
void test__all_types__id(void** state)
{
    vector_t* pvec = NULL;
    type_register(ooo_t, NULL, NULL, NULL, NULL);
    pvec = create_vector(ooo_t);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__vector(void** state)
{
    vector_t* pvec = create_vector(vector_t<int>);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__list(void** state)
{
    vector_t* pvec = create_vector(list_t<int>);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__slist(void** state)
{
    vector_t* pvec = create_vector(slist_t<int>);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__deque(void** state)
{
    vector_t* pvec = create_vector(deque_t<int>);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__queue(void** state)
{
    vector_t* pvec = create_vector(queue_t<int>);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__stack(void** state)
{
    vector_t* pvec = create_vector(stack_t<int>);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__priority_queue(void** state)
{
    vector_t* pvec = create_vector(priority_queue_t<int>);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__set(void** state)
{
    vector_t* pvec = create_vector(set_t<int>);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__multiset(void** state)
{
    vector_t* pvec = create_vector(multiset_t<int>);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__hash_set(void** state)
{
    vector_t* pvec = create_vector(hash_set_t<int>);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__hash_multiset(void** state)
{
    vector_t* pvec = create_vector(hash_multiset_t<int>);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__map(void** state)
{
    vector_t* pvec = create_vector(map_t<int, int>);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__multimap(void** state)
{
    vector_t* pvec = create_vector(multimap_t<int, int>);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__hash_map(void** state)
{
    vector_t* pvec = create_vector(hash_map_t<int, int>);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__hash_multimap(void** state)
{
    vector_t* pvec = create_vector(hash_multimap_t<int, int>);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__pair(void** state)
{
    vector_t* pvec = create_vector(pair_t<int, int>);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__string(void** state)
{
    vector_t* pvec = create_vector(string_t);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__cstl_bool(void** state)
{
    vector_t* pvec = create_vector(bool_t);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__range(void** state)
{
    vector_t* pvec = create_vector(range_t);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__iterator(void** state)
{
    vector_t* pvec = create_vector(iterator_t);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__vector_iterator(void** state)
{
    vector_t* pvec = create_vector(vector_iterator_t);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__list_iterator(void** state)
{
    vector_t* pvec = create_vector(list_iterator_t);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__slist_iterator(void** state)
{
    vector_t* pvec = create_vector(slist_iterator_t);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__deque_iterator(void** state)
{
    vector_t* pvec = create_vector(deque_iterator_t);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__set_iterator(void** state)
{
    vector_t* pvec = create_vector(set_iterator_t);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__map_iterator(void** state)
{
    vector_t* pvec = create_vector(map_iterator_t);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__multiset_iterator(void** state)
{
    vector_t* pvec = create_vector(multiset_iterator_t);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__multimap_iterator(void** state)
{
    vector_t* pvec = create_vector(multimap_iterator_t);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__hash_set_iterator(void** state)
{
    vector_t* pvec = create_vector(hash_set_iterator_t);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__hash_map_iterator(void** state)
{
    vector_t* pvec = create_vector(hash_map_iterator_t);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__hash_multiset_iterator(void** state)
{
    vector_t* pvec = create_vector(hash_multiset_iterator_t);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__hash_multimap_iterator(void** state)
{
    vector_t* pvec = create_vector(hash_multimap_iterator_t);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__string_iterator(void** state)
{
    vector_t* pvec = create_vector(string_iterator_t);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__input_iterator(void** state)
{
    vector_t* pvec = create_vector(input_iterator_t);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__output_iterator(void** state)
{
    vector_t* pvec = create_vector(output_iterator_t);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__forward_iterator(void** state)
{
    vector_t* pvec = create_vector(forward_iterator_t);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__bidirectional_iterator(void** state)
{
    vector_t* pvec = create_vector(bidirectional_iterator_t);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__random_access_iterator(void** state)
{
    vector_t* pvec = create_vector(random_access_iterator_t);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__basic_string(void** state)
{
    vector_t* pvec = create_vector(basic_string_t<basic_string_t<int>>);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__basic_string_iterator(void** state)
{
    vector_t* pvec = create_vector(basic_string_iterator_t);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

#ifndef _MSC_VER
void test__all_types__bool(void** state)
{
    vector_t* pvec = create_vector(_Bool);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__long_long(void** state)
{
    vector_t* pvec = create_vector(long long);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__long_long_int(void** state)
{
    vector_t* pvec = create_vector(long long int);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__signed_long_long(void** state)
{
    vector_t* pvec = create_vector(signed long long);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__signed_long_long_int(void** state)
{
    vector_t* pvec = create_vector(signed long long int);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__unsigned_long_long(void** state)
{
    vector_t* pvec = create_vector(unsigned long long);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__all_types__unsigned_long_long_int(void** state)
{
    vector_t* pvec = create_vector(unsigned long long int);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}
#endif

/*
 * test void* usage
 */
UT_CASE_DEFINATION(pointer_usage)
void test__pointer_usage__create(void** state)
{
    vector_t* pvec = create_vector(void*);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__pointer_usage__init_n(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(void *);
    vector_init_n(pvec, 10);
    for (i = 0; i < vector_size(pvec); ++i) {
        assert_true(*(void**)vector_at(pvec, i) == NULL);
    }
    vector_destroy(pvec);
}

void test__pointer_usage__init_elem(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(void*);
    vector_init_elem(pvec, 10, 0xffff);
    for (i = 0; i < vector_size(pvec); ++i) {
        assert_true(*(void**)vector_at(pvec, i) == 0xffff);
    }
    vector_destroy(pvec);
}

void test__pointer_usage__at(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(void*);
    vector_init_elem(pvec, 10, 0x1111);
    for (i = 0; i < vector_size(pvec); ++i) {
        assert_true(*(void**)vector_at(pvec, i) == 0x1111);
        *(void**)vector_at(pvec, i) = 0xffff;
    }
    for (i = 0; i < vector_size(pvec); ++i) {
        assert_true(*(void**)vector_at(pvec, i) == 0xffff);
    }
    vector_destroy(pvec);
}

void test__pointer_usage__iterator(void** state)
{
    iterator_t it;
    vector_t* pvec = create_vector(void*);
    vector_init_elem(pvec, 10, 0xffff);
    for (it = vector_begin(pvec);
         !iterator_equal(it, vector_end(pvec));
         it = iterator_next(it)) {
        void* p = NULL;
        assert_true(*(void**)iterator_get_pointer(it) == 0xffff);
        iterator_get_value(it, &p);
        assert_true(p == 0xffff);
    }
    vector_destroy(pvec);
}

void test__pointer_usage__copy(void** state)
{
    size_t i = 0;
    vector_t* pvec1 = create_vector(void*);
    vector_t* pvec2 = create_vector(void*);
    vector_init_elem(pvec1, 10, 0xffff);
    vector_init_copy_range(pvec2, vector_begin(pvec1), vector_end(pvec1));

    for (i = 0; i < vector_size(pvec1); ++i) {
        assert_true(*(void**)vector_at(pvec1, i) == *(void**)vector_at(pvec2, i));
    }

    vector_destroy(pvec1);
    vector_destroy(pvec2);
}

void test__pointer_usage__less(void** state)
{
    vector_t* pvec1 = create_vector(void*);
    vector_t* pvec2 = create_vector(void*);
    vector_init_elem(pvec1, 10, 0x1111);
    vector_init_elem(pvec2, 10, 0xffff);
    assert_true(vector_less(pvec1, pvec2));
    vector_destroy(pvec1);
    vector_destroy(pvec2);
}

typedef void* pointer;
void test__pointer_usage__duplicate(void** state)
{
    vector_t* pvec = NULL;

    type_duplicate(pointer, void*);
    pvec = create_vector(pointer);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

/*
 * test range_t usage
 */
UT_CASE_DEFINATION(range_usage)
void test__range_usage__create(void** state)
{
    vector_t* pvec = create_vector(range_t);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__range_usage__init_n(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(range_t);
    range_t r;
    memset(&r, 0x00, sizeof(range_t));
    vector_init_n(pvec, 10);
    for (i = 0; i < vector_size(pvec); ++i) {
        assert_true(memcmp((range_t*)vector_at(pvec, i), &r, sizeof(range_t)) == 0);
    }
    vector_destroy(pvec);
}

void test__range_usage__init_elem(void** state)
{
    size_t i = 0;
    range_t r;
    vector_t* pvec = create_vector(range_t);
    memset(&r, 0xcc, sizeof(range_t));
    vector_init_elem(pvec, 10, &r);
    for (i = 0; i < vector_size(pvec); ++i) {
        assert_true(memcmp((range_t*)vector_at(pvec, i), &r, sizeof(range_t)) == 0);
    }
    vector_destroy(pvec);
}

void test__range_usage__at(void** state)
{
    size_t i = 0;
    range_t r1;
    range_t r2;
    vector_t* pvec = create_vector(range_t);
    memset(&r1, 0x00, sizeof(range_t));
    memset(&r2, 0xcc, sizeof(range_t));
    vector_init_elem(pvec, 10, &r1);
    for (i = 0; i < vector_size(pvec); ++i) {
        assert_true(memcmp((range_t*)vector_at(pvec, i), &r1, sizeof(range_t)) == 0);
        memcpy((range_t*)vector_at(pvec, i), &r2, sizeof(range_t));
    }
    for (i = 0; i < vector_size(pvec); ++i) {
        assert_true(memcmp((range_t*)vector_at(pvec, i), &r2, sizeof(range_t)) == 0);
    }
    vector_destroy(pvec);
}

void test__range_usage__iterator(void** state)
{
    iterator_t it;
    range_t r;
    vector_t* pvec = create_vector(range_t);
    memset(&r, 0x11, sizeof(range_t));
    vector_init_elem(pvec, 10, &r);
    for (it = vector_begin(pvec);
         !iterator_equal(it, vector_end(pvec));
         it = iterator_next(it)) {
        range_t rr;
        assert_true(memcmp((range_t*)iterator_get_pointer(it), &r, sizeof(range_t)) == 0);
        iterator_get_value(it, &rr);
        assert_true(memcmp(&r, &rr, sizeof(range_t)) == 0);
    }
    vector_destroy(pvec);
}

void test__range_usage__copy(void** state)
{
    size_t i = 0;
    range_t r;
    vector_t* pvec1 = create_vector(range_t);
    vector_t* pvec2 = create_vector(range_t);
    vector_init_elem(pvec1, 10, &r);
    vector_init_copy_range(pvec2, vector_begin(pvec1), vector_end(pvec1));

    for (i = 0; i < vector_size(pvec1); ++i) {
        assert_true(memcmp((range_t*)vector_at(pvec1, i), (range_t*)vector_at(pvec2, i), sizeof(range_t)) == 0);
    }

    vector_destroy(pvec1);
    vector_destroy(pvec2);
}

void test__range_usage__less(void** state)
{
    vector_t* pvec1 = create_vector(range_t);
    vector_t* pvec2 = create_vector(range_t);
    range_t r1;
    range_t r2;
    memset(&r1, 0x11, sizeof(range_t));
    memset(&r2, 0x22, sizeof(range_t));
    vector_init_elem(pvec1, 10, &r1);
    vector_init_elem(pvec2, 10, &r2);
    assert_true(vector_less(pvec1, pvec2));
    vector_destroy(pvec1);
    vector_destroy(pvec2);
}

typedef range_t my_range;
void test__range_usage__duplicate(void** state)
{
    vector_t* pvec = NULL;

    type_duplicate(my_range, range_t);
    pvec = create_vector(my_range);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

/*
 * test basic_string_t usage
 */
UT_CASE_DEFINATION(basic_string_usage)
void test__basic_string_usage__create(void** state)
{
    vector_t* pvec = create_vector(basic_string_t<int>);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__basic_string_usage__init_n(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(basic_string_t<int>);
    vector_init_n(pvec, 10);
    for (i = 0; i < vector_size(pvec); ++i) {
        assert_true(basic_string_empty((basic_string_t*)vector_at(pvec, i)));
    }
    vector_destroy(pvec);
}

void test__basic_string_usage__init_elem(void** state)
{
    size_t i = 0;
    basic_string_t* pbstr = create_basic_string(int);
    vector_t* pvec = create_vector(basic_string_t<int>);
    basic_string_init_elem(pbstr, 10, 0);
    vector_init_elem(pvec, 10, pbstr);
    for (i = 0; i < vector_size(pvec); ++i) {
        assert_true(basic_string_size((basic_string_t*)vector_at(pvec, i)) == 10);
    }
    vector_destroy(pvec);
    basic_string_destroy(pbstr);
}

void test__basic_string_usage__at(void** state)
{
    size_t i = 0;
    basic_string_t* pbstr1 = create_basic_string(int);
    basic_string_t* pbstr2 = create_basic_string(int);
    vector_t* pvec = create_vector(basic_string_t<int>);
    basic_string_init_elem(pbstr1, 10, 0);
    basic_string_init_elem(pbstr2, 3, 0);
    vector_init_elem(pvec, 10, pbstr1);
    for (i = 0; i < vector_size(pvec); ++i) {
        assert_true(basic_string_size((basic_string_t*)vector_at(pvec, i)) == 10);
        basic_string_assign((basic_string_t*)vector_at(pvec, i), pbstr2);
    }
    for (i = 0; i < vector_size(pvec); ++i) {
        assert_true(basic_string_size((basic_string_t*)vector_at(pvec, i)) == 3);
    }
    vector_destroy(pvec);
    basic_string_destroy(pbstr1);
    basic_string_destroy(pbstr2);
}

void test__basic_string_usage__iterator(void** state)
{
    iterator_t it;
    basic_string_t* pbstr = create_basic_string(int);
    vector_t* pvec = create_vector(basic_string_t<int>);
    basic_string_init_elem(pbstr, 10, 0);
    vector_init_elem(pvec, 10, pbstr);
    for (it = vector_begin(pvec);
         !iterator_equal(it, vector_end(pvec));
         it = iterator_next(it)) {
        basic_string_t* pbstr1 = create_basic_string(int);
        basic_string_init(pbstr1);
        assert_true(basic_string_size((basic_string_t*)iterator_get_pointer(it)) == 10);
        iterator_get_value(it, pbstr1);
        assert_true(basic_string_size(pbstr1) == 10);
        basic_string_destroy(pbstr1);
    }
    vector_destroy(pvec);
    basic_string_destroy(pbstr);
}

void test__basic_string_usage__copy(void** state)
{
    size_t i = 0;
    basic_string_t* pbstr = create_basic_string(int);
    vector_t* pvec1 = create_vector(basic_string_t<int>);
    vector_t* pvec2 = create_vector(basic_string_t<int>);
    basic_string_init_elem(pbstr, 10, 10);
    vector_init_elem(pvec1, 10, pbstr);
    vector_init_copy_range(pvec2, vector_begin(pvec1), vector_end(pvec1));

    assert_true(vector_equal(pvec1, pvec2));

    vector_destroy(pvec1);
    vector_destroy(pvec2);
    basic_string_destroy(pbstr);
}

void test__basic_string_usage__less(void** state)
{
    vector_t* pvec1 = create_vector(basic_string_t<int>);
    vector_t* pvec2 = create_vector(basic_string_t<int>);
    basic_string_t* pbstr1 = create_basic_string(int);
    basic_string_t* pbstr2 = create_basic_string(int);
    basic_string_init_elem(pbstr1, 10, 10);
    basic_string_init_elem(pbstr2, 10, 20);
    vector_init_elem(pvec1, 10, pbstr1);
    vector_init_elem(pvec2, 10, pbstr2);
    assert_true(vector_less(pvec1, pvec2));
    vector_destroy(pvec1);
    vector_destroy(pvec2);
    basic_string_destroy(pbstr1);
    basic_string_destroy(pbstr2);
}

typedef basic_string_t my_basic_string;
void test__basic_string_usage__duplicate(void** state)
{
    vector_t* pvec = NULL;

    type_duplicate(my_basic_string, basic_string_t);
    pvec = create_vector(my_basic_string);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

#ifndef _MSC_VER
/*
 * test _Bool usage
 */
UT_CASE_DEFINATION(bool_usage)
void test__bool_usage__create(void** state)
{
    vector_t* pvec = create_vector(_Bool);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__bool_usage__init_n(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(_Bool);
    vector_init_n(pvec, 10);
    for (i = 0; i < vector_size(pvec); ++i) {
        assert_true(*(_Bool*)vector_at(pvec, i) == false);
    }
    vector_destroy(pvec);
}

void test__bool_usage__init_elem(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(_Bool);
    vector_init_elem(pvec, 10, true);
    for (i = 0; i < vector_size(pvec); ++i) {
        assert_true(*(_Bool*)vector_at(pvec, i) == true);
    }
    vector_destroy(pvec);
}

void test__bool_usage__at(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(_Bool);
    vector_init_elem(pvec, 10, true);
    for (i = 0; i < vector_size(pvec); ++i) {
        assert_true(*(_Bool*)vector_at(pvec, i) == true);
        *(_Bool*)vector_at(pvec, i) = false;
    }
    for (i = 0; i < vector_size(pvec); ++i) {
        assert_true(*(_Bool*)vector_at(pvec, i) == false);
    }
    vector_destroy(pvec);
}

void test__bool_usage__iterator(void** state)
{
    iterator_t it;
    vector_t* pvec = create_vector(_Bool);
    vector_init_elem(pvec, 10, true);
    for (it = vector_begin(pvec);
         !iterator_equal(it, vector_end(pvec));
         it = iterator_next(it)) {
        _Bool b = false;
        assert_true(*(_Bool*)iterator_get_pointer(it) == true);
        iterator_get_value(it, &b);
        assert_true(b);
    }
    vector_destroy(pvec);
}

void test__bool_usage__copy(void** state)
{
    size_t i = 0;
    vector_t* pvec1 = create_vector(_Bool);
    vector_t* pvec2 = create_vector(_Bool);
    vector_init_elem(pvec1, 10, true);
    vector_init_copy_range(pvec2, vector_begin(pvec1), vector_end(pvec1));

    for (i = 0; i < vector_size(pvec1); ++i) {
        assert_true(*(_Bool*)vector_at(pvec1, i) == *(_Bool*)vector_at(pvec2, i));
    }

    vector_destroy(pvec1);
    vector_destroy(pvec2);
}

void test__bool_usage__less(void** state)
{
    vector_t* pvec1 = create_vector(_Bool);
    vector_t* pvec2 = create_vector(_Bool);
    vector_init_elem(pvec1, 10, false);
    vector_init_elem(pvec2, 10, true);
    assert_true(vector_less(pvec1, pvec2));
    vector_destroy(pvec1);
    vector_destroy(pvec2);
}

typedef _Bool my_bool;
void test__bool_usage__duplicate(void** state)
{
    vector_t* pvec = NULL;

    type_duplicate(my_bool, _Bool);
    pvec = create_vector(my_bool);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

/*
 * test long long usage
 */
UT_CASE_DEFINATION(long_long_usage)
void test__long_long_usage__create(void** state)
{
    vector_t* pvec = create_vector(long long);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__long_long_usage__init_n(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(long long int);
    vector_init_n(pvec, 10);
    for (i = 0; i < vector_size(pvec); ++i) {
        assert_true(*(long long*)vector_at(pvec, i) == 0ll);
    }
    vector_destroy(pvec);
}

void test__long_long_usage__init_elem(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(signed long long);
    vector_init_elem(pvec, 10, 100ll);
    for (i = 0; i < vector_size(pvec); ++i) {
        assert_true(*(long long*)vector_at(pvec, i) == 100ll);
    }
    vector_destroy(pvec);
}

void test__long_long_usage__at(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(signed long long int);
    vector_init_elem(pvec, 10, 100ll);
    for (i = 0; i < vector_size(pvec); ++i) {
        assert_true(*(long long*)vector_at(pvec, i) == 100ll);
        *(long long*)vector_at(pvec, i) = 200ll;
    }
    for (i = 0; i < vector_size(pvec); ++i) {
        assert_true(*(long long*)vector_at(pvec, i) == 200ll);
    }
    vector_destroy(pvec);
}

void test__long_long_usage__iterator(void** state)
{
    iterator_t it;
    vector_t* pvec = create_vector(long long);
    vector_init_elem(pvec, 10, 100ll);
    for (it = vector_begin(pvec);
         !iterator_equal(it, vector_end(pvec));
         it = iterator_next(it)) {
        long long b = 0ll;
        assert_true(*(long long*)iterator_get_pointer(it) == 100ll);
        iterator_get_value(it, &b);
        assert_true(b == 100ll);
    }
    vector_destroy(pvec);
}

void test__long_long_usage__copy(void** state)
{
    size_t i = 0;
    vector_t* pvec1 = create_vector(long long);
    vector_t* pvec2 = create_vector(long long);
    vector_init_elem(pvec1, 10, 88ll);
    vector_init_copy_range(pvec2, vector_begin(pvec1), vector_end(pvec1));

    for (i = 0; i < vector_size(pvec1); ++i) {
        assert_true(*(long long*)vector_at(pvec1, i) == *(long long*)vector_at(pvec2, i));
    }

    vector_destroy(pvec1);
    vector_destroy(pvec2);
}

void test__long_long_usage__less(void** state)
{
    vector_t* pvec1 = create_vector(long long);
    vector_t* pvec2 = create_vector(long long);
    vector_init_elem(pvec1, 10, 1234ll);
    vector_init_elem(pvec2, 10, 9939393ll);
    assert_true(vector_less(pvec1, pvec2));
    vector_destroy(pvec1);
    vector_destroy(pvec2);
}

typedef long long my_ll;
void test__long_long_usage__duplicate(void** state)
{
    vector_t* pvec = NULL;

    type_duplicate(my_ll, long long);
    pvec = create_vector(my_ll);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

/*
 * test unsigned long long usage
 */
UT_CASE_DEFINATION(ulong_long_usage)
void test__ulong_long_usage__create(void** state)
{
    vector_t* pvec = create_vector(unsigned long long);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}

void test__ulong_long_usage__init_n(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector(unsigned long long int);
    vector_init_n(pvec, 10);
    for (i = 0; i < vector_size(pvec); ++i) {
        assert_true(*(unsigned long long*)vector_at(pvec, i) == 0ll);
    }
    vector_destroy(pvec);
}

void test__ulong_long_usage__init_elem(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector( unsigned long long);
    vector_init_elem(pvec, 10, 100ll);
    for (i = 0; i < vector_size(pvec); ++i) {
        assert_true(*(unsigned long long*)vector_at(pvec, i) == 100ll);
    }
    vector_destroy(pvec);
}

void test__ulong_long_usage__at(void** state)
{
    size_t i = 0;
    vector_t* pvec = create_vector( unsigned long long int);
    vector_init_elem(pvec, 10, 100ll);
    for (i = 0; i < vector_size(pvec); ++i) {
        assert_true(*(unsigned long long*)vector_at(pvec, i) == 100ll);
        *(unsigned long long*)vector_at(pvec, i) = 200ll;
    }
    for (i = 0; i < vector_size(pvec); ++i) {
        assert_true(*(unsigned long long*)vector_at(pvec, i) == 200ll);
    }
    vector_destroy(pvec);
}

void test__ulong_long_usage__iterator(void** state)
{
    iterator_t it;
    vector_t* pvec = create_vector(unsigned long long);
    vector_init_elem(pvec, 10, 100ll);
    for (it = vector_begin(pvec);
         !iterator_equal(it, vector_end(pvec));
         it = iterator_next(it)) {
        unsigned long long b = false;
        assert_true(*(unsigned long long*)iterator_get_pointer(it) == 100ll);
        iterator_get_value(it, &b);
        assert_true(b == 100ll);
    }
    vector_destroy(pvec);
}

void test__ulong_long_usage__copy(void** state)
{
    size_t i = 0;
    vector_t* pvec1 = create_vector(unsigned long long);
    vector_t* pvec2 = create_vector(unsigned long long);
    vector_init_elem(pvec1, 10, 88ll);
    vector_init_copy_range(pvec2, vector_begin(pvec1), vector_end(pvec1));

    for (i = 0; i < vector_size(pvec1); ++i) {
        assert_true(*(unsigned long long*)vector_at(pvec1, i) == *(unsigned long long*)vector_at(pvec2, i));
    }

    vector_destroy(pvec1);
    vector_destroy(pvec2);
}

void test__ulong_long_usage__less(void** state)
{
    vector_t* pvec1 = create_vector(unsigned long long);
    vector_t* pvec2 = create_vector(unsigned long long);
    vector_init_elem(pvec1, 10, 1234ll);
    vector_init_elem(pvec2, 10, 9939393ll);
    assert_true(vector_less(pvec1, pvec2));
    vector_destroy(pvec1);
    vector_destroy(pvec2);
}

typedef unsigned long long my_ull;
void test__ulong_long_usage__duplicate(void** state)
{
    vector_t* pvec = NULL;

    type_duplicate(my_ull, unsigned long long);
    pvec = create_vector(my_ull);
    assert_true(pvec != NULL);
    vector_destroy(pvec);
}
#endif
