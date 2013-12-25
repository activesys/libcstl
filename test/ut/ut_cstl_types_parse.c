#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <google/cmockery.h>

#include "cstl/cstl_def.h"
#include "cstl/cstl_alloc.h"
#include "cstl/cstl_types.h"
#include "cstl_types_parse.h"

#include "ut_def.h"
#include "ut_cstl_types_parse.h"

UT_SUIT_DEFINATION(cstl_types_parse, _type_get_token)
typedef struct abc {
    int n_abc;
}type_abc_t;

static void test_parse_setup(const char* typename)
{
    _gt_typeanalysis._t_token = _TOKEN_INVALID;
    _gt_typeanalysis._t_index = 0;
    memset(_gt_typeanalysis._s_tokentext, '\0', _TYPE_NAME_SIZE + 1);
    memset(_gt_typeanalysis._s_typename, '\0', _TYPE_NAME_SIZE + 1);
    strncpy(_gt_typeanalysis._s_typename, typename, _TYPE_NAME_SIZE);
}

static void test_parse_setup_ex(const char* typename, _typetoken_t token, size_t index, const char* s_tokentext)
{
    test_parse_setup(typename);
    _gt_typeanalysis._t_token = token;
    _gt_typeanalysis._t_index = index;
    strncpy(_gt_typeanalysis._s_tokentext, s_tokentext, _TYPE_NAME_SIZE);
}

/*
 * test _type_get_token
 */
UT_CASE_DEFINATION(_type_get_token)
void test__type_get_token__sign_left_bracket(void** state)
{
    type_register(type_abc_t, NULL, NULL, NULL, NULL);
    test_parse_setup("<");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_SIGN_LEFT_BRACKET);
    assert_true(_gt_typeanalysis._t_index == 1);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "<", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__sign_right_bracket(void** state)
{
    test_parse_setup(">");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_SIGN_RIGHT_BRACKET);
    assert_true(_gt_typeanalysis._t_index == 1);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, ">", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__sign_comma(void** state)
{
    test_parse_setup(",");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_SIGN_COMMA);
    assert_true(_gt_typeanalysis._t_index == 1);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, ",", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__sign_pointer(void** state)
{
    test_parse_setup("*");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_SIGN_POINTER);
    assert_true(_gt_typeanalysis._t_index == 1);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "*", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__sign_space_and_eoi(void** state)
{
    test_parse_setup(" \t\v\f\r\n");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_END_OF_INPUT);
    assert_true(_gt_typeanalysis._t_index == 6);
    assert_true(strlen(_gt_typeanalysis._s_tokentext) == 0);
}

void test__type_get_token__sign_invalid(void** state)
{
    test_parse_setup("@#$");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_INVALID);
    assert_true(_gt_typeanalysis._t_index == 0);
    assert_true(strlen(_gt_typeanalysis._s_tokentext) == 0);
}

void test__type_get_token__identifier(void** state)
{
    test_parse_setup("abc");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_IDENTIFIER);
    assert_true(_gt_typeanalysis._t_index == 3);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "abc", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__identifier_with_underline(void** state)
{
    test_parse_setup("_abc_xyz_");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_IDENTIFIER);
    assert_true(_gt_typeanalysis._t_index == 9);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "_abc_xyz_", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_void(void** state)
{
    test_parse_setup("void");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_VOID);
    assert_true(_gt_typeanalysis._t_index == 4);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "void", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_char(void** state)
{
    test_parse_setup("char");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_CHAR);
    assert_true(_gt_typeanalysis._t_index == 4);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "char", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_short(void** state)
{
    test_parse_setup("short");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_SHORT);
    assert_true(_gt_typeanalysis._t_index == 5);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "short", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_int(void** state)
{
    test_parse_setup("int");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_INT);
    assert_true(_gt_typeanalysis._t_index == 3);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "int", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_long(void** state)
{
    test_parse_setup("long");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_LONG);
    assert_true(_gt_typeanalysis._t_index == 4);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "long", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_double(void** state)
{
    test_parse_setup("double");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_DOUBLE);
    assert_true(_gt_typeanalysis._t_index == 6);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "double", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_float(void** state)
{
    test_parse_setup("float");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_FLOAT);
    assert_true(_gt_typeanalysis._t_index == 5);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "float", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_signed(void** state)
{
    test_parse_setup("signed");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_SIGNED);
    assert_true(_gt_typeanalysis._t_index == 6);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "signed", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_unsigned(void** state)
{
    test_parse_setup("unsigned");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_UNSIGNED);
    assert_true(_gt_typeanalysis._t_index == 8);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "unsigned", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_cstl_bool(void** state)
{
    test_parse_setup("bool_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_CSTL_BOOL);
    assert_true(_gt_typeanalysis._t_index == 6);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "bool_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_struct(void** state)
{
    test_parse_setup("struct");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_STRUCT);
    assert_true(_gt_typeanalysis._t_index == 6);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "struct", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_enum(void** state)
{
    test_parse_setup("enum");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_ENUM);
    assert_true(_gt_typeanalysis._t_index == 4);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "enum", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_union(void** state)
{
    test_parse_setup("union");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_UNION);
    assert_true(_gt_typeanalysis._t_index == 5);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "union", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_vector(void** state)
{
    test_parse_setup("vector_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_VECTOR);
    assert_true(_gt_typeanalysis._t_index == 8);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "vector_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_list(void** state)
{
    test_parse_setup("list_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_LIST);
    assert_true(_gt_typeanalysis._t_index == 6);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "list_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_slist(void** state)
{
    test_parse_setup("slist_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_SLIST);
    assert_true(_gt_typeanalysis._t_index == 7);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "slist_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_deque(void** state)
{
    test_parse_setup("deque_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_DEQUE);
    assert_true(_gt_typeanalysis._t_index == 7);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "deque_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_stack(void** state)
{
    test_parse_setup("stack_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_STACK);
    assert_true(_gt_typeanalysis._t_index == 7);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "stack_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_queue(void** state)
{
    test_parse_setup("queue_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_QUEUE);
    assert_true(_gt_typeanalysis._t_index == 7);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "queue_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_priority_queue(void** state)
{
    test_parse_setup("priority_queue_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_PRIORITY_QUEUE);
    assert_true(_gt_typeanalysis._t_index == 16);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "priority_queue_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_set(void** state)
{
    test_parse_setup("set_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_SET);
    assert_true(_gt_typeanalysis._t_index == 5);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "set_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_map(void** state)
{
    test_parse_setup("map_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_MAP);
    assert_true(_gt_typeanalysis._t_index == 5);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "map_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_multiset(void** state)
{
    test_parse_setup("multiset_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_MULTISET);
    assert_true(_gt_typeanalysis._t_index == 10);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "multiset_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_multimap(void** state)
{
    test_parse_setup("multimap_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_MULTIMAP);
    assert_true(_gt_typeanalysis._t_index == 10);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "multimap_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_hash_set(void** state)
{
    test_parse_setup("hash_set_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_HASH_SET);
    assert_true(_gt_typeanalysis._t_index == 10);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "hash_set_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_hash_map(void** state)
{
    test_parse_setup("hash_map_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_HASH_MAP);
    assert_true(_gt_typeanalysis._t_index == 10);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "hash_map_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_hash_multiset(void** state)
{
    test_parse_setup("hash_multiset_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_HASH_MULTISET);
    assert_true(_gt_typeanalysis._t_index == 15);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "hash_multiset_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_hash_multimap(void** state)
{
    test_parse_setup("hash_multimap_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_HASH_MULTIMAP);
    assert_true(_gt_typeanalysis._t_index == 15);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "hash_multimap_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_pair(void** state)
{
    test_parse_setup("pair_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_PAIR);
    assert_true(_gt_typeanalysis._t_index == 6);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "pair_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_string(void** state)
{
    test_parse_setup("string_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_STRING);
    assert_true(_gt_typeanalysis._t_index == 8);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "string_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_iterator(void** state)
{
    test_parse_setup("iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 10);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_vector_iterator(void** state)
{
    test_parse_setup("vector_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_VECTOR_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 17);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "vector_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_list_iterator(void** state)
{
    test_parse_setup("list_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_LIST_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 15);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "list_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_slist_iterator(void** state)
{
    test_parse_setup("slist_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_SLIST_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 16);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "slist_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_deque_iterator(void** state)
{
    test_parse_setup("deque_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_DEQUE_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 16);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "deque_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_set_iterator(void** state)
{
    test_parse_setup("set_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_SET_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 14);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "set_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_map_iterator(void** state)
{
    test_parse_setup("map_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_MAP_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 14);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "map_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_multiset_iterator(void** state)
{
    test_parse_setup("multiset_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_MULTISET_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 19);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "multiset_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_multimap_iterator(void** state)
{
    test_parse_setup("multimap_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_MULTIMAP_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 19);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "multimap_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_hash_set_iterator(void** state)
{
    test_parse_setup("hash_set_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_HASH_SET_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 19);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "hash_set_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_hash_map_iterator(void** state)
{
    test_parse_setup("hash_map_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_HASH_MAP_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 19);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "hash_map_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_hash_multiset_iterator(void** state)
{
    test_parse_setup("hash_multiset_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_HASH_MULTISET_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 24);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "hash_multiset_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_hash_multimap_iterator(void** state)
{
    test_parse_setup("hash_multimap_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_HASH_MULTIMAP_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 24);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "hash_multimap_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_string_iterator(void** state)
{
    test_parse_setup("string_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_STRING_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 17);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "string_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_input_iterator(void** state)
{
    test_parse_setup("input_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_INPUT_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 16);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "input_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_output_iterator(void** state)
{
    test_parse_setup("output_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_OUTPUT_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 17);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "output_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_forward_iterator(void** state)
{
    test_parse_setup("forward_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_FORWARD_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 18);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "forward_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_bidirectional_iterator(void** state)
{
    test_parse_setup("bidirectional_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_BIDIRECTIONAL_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 24);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "bidirectional_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_random_access_iterator(void** state)
{
    test_parse_setup("random_access_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_RANDOM_ACCESS_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 24);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "random_access_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_range(void** state)
{
    test_parse_setup("range_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_RANGE);
    assert_true(_gt_typeanalysis._t_index == 7);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "range_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_basic_string(void** state)
{
    test_parse_setup("basic_string_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_BASIC_STRING);
    assert_true(_gt_typeanalysis._t_index == 14);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "basic_string_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_basic_string_iterator(void** state)
{
    test_parse_setup("basic_string_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_BASIC_STRING_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 23);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "basic_string_iterator_t", _TYPE_NAME_SIZE) == 0);
}

#ifndef _MSC_VER
void test__type_get_token__key_bool(void** state)
{
    test_parse_setup("_Bool");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_BOOL);
    assert_true(_gt_typeanalysis._t_index == 5);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "_Bool", _TYPE_NAME_SIZE) == 0);
}
#endif

/*
 * test _type_token_rollback
 */
UT_CASE_DEFINATION(_type_token_rollback)
void test__type_token_rollback__invalid_token(void** state)
{
    test_parse_setup("abc");
    expect_assert_failure(_type_token_rollback());
}

void test__type_token_rollback__invalid_index(void** state)
{
    test_parse_setup("abc");
    _gt_typeanalysis._t_token = _TOKEN_SIGN_COMMA;
    expect_assert_failure(_type_token_rollback());
}

void test__type_token_rollback__invalid_tokentext(void** state)
{
    test_parse_setup(",abc");
    _gt_typeanalysis._t_token = _TOKEN_SIGN_COMMA;
    _gt_typeanalysis._t_index++;
    strncpy(_gt_typeanalysis._s_tokentext, "abc", _TYPE_NAME_SIZE);
    expect_assert_failure(_type_token_rollback());
}

void test__type_token_rollback__eoi(void** state)
{
    test_parse_setup("pair_t<int, int>");
    _gt_typeanalysis._t_token = _TOKEN_SIGN_COMMA;
    _gt_typeanalysis._t_index = 11;
    strncpy(_gt_typeanalysis._s_tokentext, ",", _TYPE_NAME_SIZE);
    _type_token_rollback();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_ROLLBACK);
    assert_true(_gt_typeanalysis._t_index = 10);
}

void test__type_token_rollback__comma(void** state)
{
    test_parse_setup("pair_t<int,");
    _gt_typeanalysis._t_token = _TOKEN_SIGN_COMMA;
    _gt_typeanalysis._t_index = 11;
    strncpy(_gt_typeanalysis._s_tokentext, ",", _TYPE_NAME_SIZE);
    _type_token_rollback();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_ROLLBACK);
    assert_true(_gt_typeanalysis._t_index = 10);
}

void test__type_token_rollback__right_bracket(void** state)
{
    test_parse_setup("list_t<int>");
    _gt_typeanalysis._t_token = _TOKEN_SIGN_RIGHT_BRACKET;
    _gt_typeanalysis._t_index = 11;
    strncpy(_gt_typeanalysis._s_tokentext, ">", _TYPE_NAME_SIZE);
    _type_token_rollback();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_ROLLBACK);
    assert_true(_gt_typeanalysis._t_index = 10);
}

void test__type_token_rollback__not_rollback(void** state)
{
    test_parse_setup("list_t<int> ");
    _gt_typeanalysis._t_token = _TOKEN_SIGN_RIGHT_BRACKET;
    _gt_typeanalysis._t_index = 11;
    strncpy(_gt_typeanalysis._s_tokentext, ">", _TYPE_NAME_SIZE);
    _type_token_rollback();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_ROLLBACK);
    assert_true(_gt_typeanalysis._t_index = 11);
}

/*
 * test _type_parse_iterator
 */
UT_CASE_DEFINATION(_type_parse_iterator)
void test__type_parse_iterator__null(void** state)
{
    expect_assert_failure(_type_parse_iterator(NULL));
}

void test__type_parse_iterator__iterator(void** state)
{
    const char* str = "iterator_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_ITERATOR, strlen(str), str);

    assert_true(_type_parse_iterator(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_iterator__vector_iterator(void** state)
{
    const char* str = "vector_iterator_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_VECTOR_ITERATOR, strlen(str), str);

    assert_true(_type_parse_iterator(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_iterator__list_iterator(void** state)
{
    const char* str = "list_iterator_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_LIST_ITERATOR, strlen(str), str);

    assert_true(_type_parse_iterator(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_iterator__slist_iterator(void** state)
{
    const char* str = "slist_iterator_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_SLIST_ITERATOR, strlen(str), str);

    assert_true(_type_parse_iterator(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_iterator__deque_iterator(void** state)
{
    const char* str = "deque_iterator_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_DEQUE_ITERATOR, strlen(str), str);

    assert_true(_type_parse_iterator(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_iterator__set_iterator(void** state)
{
    const char* str = "set_iterator_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_SET_ITERATOR, strlen(str), str);

    assert_true(_type_parse_iterator(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_iterator__map_iterator(void** state)
{
    const char* str = "map_iterator_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_MAP_ITERATOR, strlen(str), str);

    assert_true(_type_parse_iterator(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_iterator__multiset_iterator(void** state)
{
    const char* str = "multiset_iterator_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_MULTISET_ITERATOR, strlen(str), str);

    assert_true(_type_parse_iterator(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_iterator__multimap_iterator(void** state)
{
    const char* str = "multimap_iterator_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_MULTIMAP_ITERATOR, strlen(str), str);

    assert_true(_type_parse_iterator(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_iterator__hash_set_iterator(void** state)
{
    const char* str = "hash_set_iterator_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_HASH_SET_ITERATOR, strlen(str), str);

    assert_true(_type_parse_iterator(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_iterator__hash_map_iterator(void** state)
{
    const char* str = "hash_map_iterator_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_HASH_MAP_ITERATOR, strlen(str), str);

    assert_true(_type_parse_iterator(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_iterator__hash_multiset_iterator(void** state)
{
    const char* str = "hash_multiset_iterator_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_HASH_MULTISET_ITERATOR, strlen(str), str);

    assert_true(_type_parse_iterator(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_iterator__hash_multimap_iterator(void** state)
{
    const char* str = "hash_multimap_iterator_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_HASH_MULTIMAP_ITERATOR, strlen(str), str);

    assert_true(_type_parse_iterator(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_iterator__string_iterator(void** state)
{
    const char* str = "string_iterator_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_STRING_ITERATOR, strlen(str), str);

    assert_true(_type_parse_iterator(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_iterator__input_iterator(void** state)
{
    const char* str = "input_iterator_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_INPUT_ITERATOR, strlen(str), str);

    assert_true(_type_parse_iterator(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_iterator__output_iterator(void** state)
{
    const char* str = "output_iterator_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_OUTPUT_ITERATOR, strlen(str), str);

    assert_true(_type_parse_iterator(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_iterator__forward_iterator(void** state)
{
    const char* str = "forward_iterator_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_FORWARD_ITERATOR, strlen(str), str);

    assert_true(_type_parse_iterator(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_iterator__bidirectional_iterator(void** state)
{
    const char* str = "bidirectional_iterator_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_BIDIRECTIONAL_ITERATOR, strlen(str), str);

    assert_true(_type_parse_iterator(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_iterator__random_access_iterator(void** state)
{
    const char* str = "random_access_iterator_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_RANDOM_ACCESS_ITERATOR, strlen(str), str);

    assert_true(_type_parse_iterator(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_iterator__invalid_iterator(void** state)
{
    const char* str = "random_access_iterator_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_ITERATOR, strlen(str), str);

    expect_assert_failure(_type_parse_iterator(s_formalname));
}

void test__type_parse_iterator__invalid_token(void** state)
{
    const char* str = "random_access_iterator_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_INVALID, strlen(str), str);

    assert_false(_type_parse_iterator(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_iterator__basic_string_iterator(void** state)
{
    const char* str = "basic_string_iterator_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_BASIC_STRING_ITERATOR, strlen(str), str);

    assert_true(_type_parse_iterator(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

/*
 * test _type_parse_relation_name
 */
UT_CASE_DEFINATION(_type_parse_relation_name)
void test__type_parse_relation_name__null(void** state)
{
    expect_assert_failure(_type_parse_relation_name(NULL));
}

void test__type_parse_relation_name__map(void** state)
{
    const char* str = "map_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_MAP, strlen(str), str);

    assert_true(_type_parse_relation_name(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_relation_name__multimap(void** state)
{
    const char* str = "multimap_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_MULTIMAP, strlen(str), str);

    assert_true(_type_parse_relation_name(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_relation_name__hash_map(void** state)
{
    const char* str = "hash_map_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_HASH_MAP, strlen(str), str);

    assert_true(_type_parse_relation_name(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_relation_name__hash_multimap(void** state)
{
    const char* str = "hash_multimap_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_HASH_MULTIMAP, strlen(str), str);

    assert_true(_type_parse_relation_name(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_relation_name__pair(void** state)
{
    const char* str = "pair_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_PAIR, strlen(str), str);

    assert_true(_type_parse_relation_name(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_relation_name__invalid_tokentext(void** state)
{
    const char* str = "pair";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_PAIR, strlen(str), str);

    expect_assert_failure(_type_parse_relation_name(s_formalname));
}

void test__type_parse_relation_name__invalid_token(void** state)
{
    const char* str = "pair_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_INVALID, strlen(str), str);

    assert_false(_type_parse_relation_name(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
}

/*
 * test _type_parse_sequence_name
 */
UT_CASE_DEFINATION(_type_parse_sequence_name)
void test__type_parse_sequence_name__null(void** state)
{
    expect_assert_failure(_type_parse_sequence_name(NULL));
}

void test__type_parse_sequence_name__vector(void** state)
{
    const char* str = "vector_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_VECTOR, strlen(str), str);

    assert_true(_type_parse_sequence_name(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_sequence_name__list(void** state)
{
    const char* str = "list_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_LIST, strlen(str), str);

    assert_true(_type_parse_sequence_name(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_sequence_name__slist(void** state)
{
    const char* str = "slist_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_SLIST, strlen(str), str);

    assert_true(_type_parse_sequence_name(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_sequence_name__deque(void** state)
{
    const char* str = "deque_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_DEQUE, strlen(str), str);

    assert_true(_type_parse_sequence_name(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_sequence_name__queue(void** state)
{
    const char* str = "queue_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_QUEUE, strlen(str), str);

    assert_true(_type_parse_sequence_name(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_sequence_name__stack(void** state)
{
    const char* str = "stack_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_STACK, strlen(str), str);

    assert_true(_type_parse_sequence_name(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_sequence_name__priority_queue(void** state)
{
    const char* str = "priority_queue_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_PRIORITY_QUEUE, strlen(str), str);

    assert_true(_type_parse_sequence_name(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_sequence_name__set(void** state)
{
    const char* str = "set_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_SET, strlen(str), str);

    assert_true(_type_parse_sequence_name(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_sequence_name__multiset(void** state)
{
    const char* str = "multiset_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_MULTISET, strlen(str), str);

    assert_true(_type_parse_sequence_name(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_sequence_name__hash_set(void** state)
{
    const char* str = "hash_set_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_HASH_SET, strlen(str), str);

    assert_true(_type_parse_sequence_name(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_sequence_name__hash_multiset(void** state)
{
    const char* str = "hash_multiset_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_HASH_MULTISET, strlen(str), str);

    assert_true(_type_parse_sequence_name(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_sequence_name__invalid_tokentext(void** state)
{
    const char* str = "hash_multiset";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_HASH_MULTISET, strlen(str), str);

    expect_assert_failure(_type_parse_sequence_name(s_formalname));
}

void test__type_parse_sequence_name__invalid_token(void** state)
{
    const char* str = "hash_multiset_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_INVALID, strlen(str), str);

    assert_false(_type_parse_sequence_name(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_sequence_name__basic_string(void** state)
{
    const char* str = "basic_string_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_BASIC_STRING, strlen(str), str);

    assert_true(_type_parse_sequence_name(s_formalname));
    assert_true(strncmp(s_formalname, "basic_string_t", _TYPE_NAME_SIZE) == 0);
}

/*
 * test _type_parse_user_define_type
 */
UT_CASE_DEFINATION(_type_parse_user_define_type)
void test__type_parse_user_define_type__null(void** state)
{
    expect_assert_failure(_type_parse_user_define_type(NULL));
}

void test__type_parse_user_define_type__struct(void** state)
{
    const char* str = "struct";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_STRUCT, strlen(str), str);

    assert_true(_type_parse_user_define_type(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_user_define_type__enum(void** state)
{
    const char* str = "enum";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_ENUM, strlen(str), str);

    assert_true(_type_parse_user_define_type(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_user_define_type__union(void** state)
{
    const char* str = "union";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_UNION, strlen(str), str);

    assert_true(_type_parse_user_define_type(s_formalname));
    assert_true(strncmp(s_formalname, str, _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_user_define_type__invalid_tokentext(void** state)
{
    const char* str = "union_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_UNION, strlen(str), str);

    expect_assert_failure(_type_parse_user_define_type(s_formalname));
}

void test__type_parse_user_define_type__invalid_token(void** state)
{
    const char* str = "union";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_INVALID, strlen(str), str);

    assert_false(_type_parse_user_define_type(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
}

/*
 * test _type_parse_user_define
 */
UT_CASE_DEFINATION(_type_parse_user_define)
void test__type_parse_user_define__null(void** state)
{
    expect_assert_failure(_type_parse_user_define(NULL));
}

void test__type_parse_user_define__struct_invalid_tokentype(void** state)
{
    const char* str = "struct type_abc_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_ENUM, strlen("struct"), "struct");

    expect_assert_failure(_type_parse_user_define(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_user_define__struct_invalid_identifier(void** state)
{
    const char* str = "struct long";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_STRUCT, strlen("struct"), "struct");

    assert_false(_type_parse_user_define(s_formalname));
    assert_true(strncmp(s_formalname, "struct ", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_user_define__struct(void** state)
{
    const char* str = "struct        type_abc_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_STRUCT, strlen("struct"), "struct");

    assert_true(_type_parse_user_define(s_formalname));
    assert_true(strncmp(s_formalname, "struct type_abc_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_user_define__identifier(void** state)
{
    const char* str = "type_abc_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_IDENTIFIER, strlen(str), str);

    assert_true(_type_parse_user_define(s_formalname));
    assert_true(strncmp(s_formalname, "type_abc_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_user_define__invalid_token(void** state)
{
    const char* str = "type_abc_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_INT, strlen(str), str);

    assert_false(_type_parse_user_define(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
}
/*
 * test _type_parse_pointer_builtin
 */
UT_CASE_DEFINATION(_type_parse_pointer_builtin)
void test__type_parse_pointer_builtin__null(void** state)
{
    expect_assert_failure(_type_parse_pointer_builtin(NULL));
}

void test__type_parse_pointer_builtin__pointer(void** state)
{
    const char* str = "void*";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_VOID, strlen("void"), "void");

    assert_true(_type_parse_pointer_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "void*", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_pointer_builtin__invalid_token(void** state)
{
    const char* str = "int";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_INT, strlen(str), str);

    assert_false(_type_parse_pointer_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
}

/*
 * test _type_parse_pointer_suffix
 */
UT_CASE_DEFINATION(_type_parse_pointer_suffix)
void test__type_parse_pointer_suffix__null(void** state)
{
    expect_assert_failure(_type_parse_pointer_suffix(NULL));
}

void test__type_parse_pointer_suffix__pointer(void** state)
{
    const char* str = "*";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_SIGN_POINTER, strlen(str), str);

    assert_true(_type_parse_pointer_suffix(s_formalname));
    assert_true(strncmp(s_formalname, "*", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_pointer_suffix__eof(void** state)
{
    const char* str = " ";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_END_OF_INPUT, strlen(str), "");

    assert_true(_type_parse_pointer_suffix(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
    assert_true(_gt_typeanalysis._t_index == 1);
    assert_true(_gt_typeanalysis._t_token == _TOKEN_ROLLBACK);
}

void test__type_parse_pointer_suffix__comma(void** state)
{
    const char* str = ",";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_SIGN_COMMA, strlen(str), str);

    assert_true(_type_parse_pointer_suffix(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
    assert_true(_gt_typeanalysis._t_index == 0);
    assert_true(_gt_typeanalysis._t_token == _TOKEN_ROLLBACK);
}

void test__type_parse_pointer_suffix__right_bracket(void** state)
{
    const char* str = ">";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_SIGN_RIGHT_BRACKET, strlen(str), str);

    assert_true(_type_parse_pointer_suffix(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
    assert_true(_gt_typeanalysis._t_index == 0);
    assert_true(_gt_typeanalysis._t_token == _TOKEN_ROLLBACK);
}

void test__type_parse_pointer_suffix__invalid_token(void** state)
{
    const char* str = "int";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_INT, strlen(str), str);

    assert_false(_type_parse_pointer_suffix(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
}

/*
 * test _type_parse_common_suffix
 */
UT_CASE_DEFINATION(_type_parse_common_suffix)
void test__type_parse_common_suffix__null(void** state)
{
    expect_assert_failure(_type_parse_common_suffix(NULL));
}

void test__type_parse_common_suffix__int(void** state)
{
    const char* str = "int";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_INT, strlen(str), str);

    assert_true(_type_parse_common_suffix(s_formalname));
    assert_true(strncmp(s_formalname, " int", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_common_suffix__eof(void** state)
{
    const char* str = " ";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_END_OF_INPUT, strlen(str), "");

    assert_true(_type_parse_common_suffix(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
    assert_true(_gt_typeanalysis._t_index == 1);
    assert_true(_gt_typeanalysis._t_token == _TOKEN_ROLLBACK);
}

void test__type_parse_common_suffix__comma(void** state)
{
    const char* str = ",";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_SIGN_COMMA, strlen(str), str);

    assert_true(_type_parse_common_suffix(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
    assert_true(_gt_typeanalysis._t_index == 0);
    assert_true(_gt_typeanalysis._t_token == _TOKEN_ROLLBACK);
}

void test__type_parse_common_suffix__right_bracket(void** state)
{
    const char* str = ">";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_SIGN_RIGHT_BRACKET, strlen(str), str);

    assert_true(_type_parse_common_suffix(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
    assert_true(_gt_typeanalysis._t_index == 0);
    assert_true(_gt_typeanalysis._t_token == _TOKEN_ROLLBACK);
}

void test__type_parse_common_suffix__invalid_token(void** state)
{
    const char* str = "abc";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_IDENTIFIER, strlen(str), str);

    assert_false(_type_parse_common_suffix(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
}

/*
 * test _type_parse_complex_suffix
 */
UT_CASE_DEFINATION(_type_parse_complex_suffix)
void test__type_parse_complex_suffix__null(void** state)
{
    expect_assert_failure(_type_parse_complex_suffix(NULL));
}

void test__type_parse_complex_suffix__char(void** state)
{
    const char* str = "char";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_CHAR, strlen(str), str);

    assert_true(_type_parse_complex_suffix(s_formalname));
    assert_true(strncmp(s_formalname, " char", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_complex_suffix__short(void** state)
{
    const char* str = "short";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_SHORT, strlen(str), str);

    assert_true(_type_parse_complex_suffix(s_formalname));
    assert_true(strncmp(s_formalname, " short", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_complex_suffix__short_int(void** state)
{
    const char* str = "short int";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_SHORT, strlen("short"), "short");

    assert_true(_type_parse_complex_suffix(s_formalname));
    assert_true(strncmp(s_formalname, " short int", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_complex_suffix__int(void** state)
{
    const char* str = "int";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_INT, strlen(str), str);

    assert_true(_type_parse_complex_suffix(s_formalname));
    assert_true(strncmp(s_formalname, " int", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_complex_suffix__long(void** state)
{
    const char* str = "long";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_LONG, strlen(str), str);

    assert_true(_type_parse_complex_suffix(s_formalname));
    assert_true(strncmp(s_formalname, " long", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_complex_suffix__long_int(void** state)
{
    const char* str = "long int";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_LONG, strlen("long"), "long");

    assert_true(_type_parse_complex_suffix(s_formalname));
    assert_true(strncmp(s_formalname, " long int", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_complex_suffix__eof(void** state)
{
    const char* str = " ";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_END_OF_INPUT, strlen(str), "");

    assert_true(_type_parse_complex_suffix(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
    assert_true(_gt_typeanalysis._t_index == 1);
    assert_true(_gt_typeanalysis._t_token == _TOKEN_ROLLBACK);
}

void test__type_parse_complex_suffix__comma(void** state)
{
    const char* str = ",";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_SIGN_COMMA, strlen(str), str);

    assert_true(_type_parse_complex_suffix(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
    assert_true(_gt_typeanalysis._t_index == 0);
    assert_true(_gt_typeanalysis._t_token == _TOKEN_ROLLBACK);
}

void test__type_parse_complex_suffix__right_bracket(void** state)
{
    const char* str = ">";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_SIGN_RIGHT_BRACKET, strlen(str), str);

    assert_true(_type_parse_complex_suffix(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
    assert_true(_gt_typeanalysis._t_index == 0);
    assert_true(_gt_typeanalysis._t_token == _TOKEN_ROLLBACK);
}

void test__type_parse_complex_suffix__invalid_token(void** state)
{
    const char* str = "struct";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_STRUCT, strlen(str), str);

    assert_false(_type_parse_complex_suffix(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
}

#ifndef _MSC_VER
void test__type_parse_complex_suffix__long_long(void** state)
{
    const char* str = "long long";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_LONG, strlen("long"), "long");

    assert_true(_type_parse_complex_suffix(s_formalname));
    assert_true(strncmp(s_formalname, " long long", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_complex_suffix__long_long_int(void** state)
{
    const char* str = "long long int";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_LONG, strlen("long"), "long");

    assert_true(_type_parse_complex_suffix(s_formalname));
    assert_true(strncmp(s_formalname, " long long int", _TYPE_NAME_SIZE) == 0);
}
#endif

/*
 * test _type_parse_signed_builtin
 */
UT_CASE_DEFINATION(_type_parse_signed_builtin)
void test__type_parse_signed_builtin__null(void** state)
{
    expect_assert_failure(_type_parse_signed_builtin(NULL));
}

void test__type_parse_signed_builtin__valid(void** state)
{
    const char* str = "signed char";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_SIGNED, strlen("signed"), "signed");

    assert_true(_type_parse_signed_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "signed char", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_signed_builtin__invalid(void** state)
{
    const char* str = "unsigned char";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_UNSIGNED, strlen("unsigned"), "unsigned");

    assert_false(_type_parse_signed_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
}

/*
 * test _type_parse_unsigned_builtin
 */
UT_CASE_DEFINATION(_type_parse_unsigned_builtin)
void test__type_parse_unsigned_builtin__null(void** state)
{
    expect_assert_failure(_type_parse_unsigned_builtin(NULL));
}

void test__type_parse_unsigned_builtin__valid(void** state)
{
    const char* str = "unsigned char";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_UNSIGNED, strlen("unsigned"), "unsigned");

    assert_true(_type_parse_unsigned_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "unsigned char", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_unsigned_builtin__invalid(void** state)
{
    const char* str = "signed char";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_SIGNED, strlen("signed"), "signed");

    assert_false(_type_parse_unsigned_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
}

/*
 * test _type_parse_simple_long_suffix
 */
UT_CASE_DEFINATION(_type_parse_simple_long_suffix)
void test__type_parse_simple_long_suffix__null(void** state)
{
    expect_assert_failure(_type_parse_simple_long_suffix(NULL));
}

void test__type_parse_simple_long_suffix__double(void** state)
{
    const char* str = "double";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_DOUBLE, strlen(str), str);

    assert_true(_type_parse_simple_long_suffix(s_formalname));
    assert_true(strncmp(s_formalname, " double", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_simple_long_suffix__common_suffix(void** state)
{
    const char* str = "int";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_INT, strlen(str), str);

    assert_true(_type_parse_simple_long_suffix(s_formalname));
    assert_true(strncmp(s_formalname, " int", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_simple_long_suffix__common_suffix_comma(void** state)
{
    const char* str = ",";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_SIGN_COMMA, strlen(str), str);

    assert_true(_type_parse_simple_long_suffix(s_formalname));
    assert_true(_gt_typeanalysis._t_index == 0);
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_simple_long_suffix__invalid_token(void** state)
{
    const char* str = "struct";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_STRUCT, strlen(str), str);

    assert_false(_type_parse_simple_long_suffix(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
}

#ifndef _MSC_VER
void test__type_parse_simple_long_suffix__complex_long_suffix(void** state)
{
    const char* str = "long int";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_LONG, strlen("long"), "long");

    assert_true(_type_parse_simple_long_suffix(s_formalname));
    assert_true(strncmp(s_formalname, " long int", _TYPE_NAME_SIZE) == 0);
}
#endif

/*
 * test _type_parse_simple_builtin
 */
UT_CASE_DEFINATION(_type_parse_simple_builtin)
void test__type_parse_simple_builtin__null(void** state)
{
    expect_assert_failure(_type_parse_simple_builtin(NULL));
}

void test__type_parse_simple_builtin__char(void** state)
{
    const char* str = "char";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_CHAR, strlen(str), str);

    assert_true(_type_parse_simple_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "char", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_simple_builtin__short(void** state)
{
    const char* str = "short";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_SHORT, strlen(str), str);

    assert_true(_type_parse_simple_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "short", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_simple_builtin__short_int(void** state)
{
    const char* str = "short int";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_SHORT, strlen("short"), "short");

    assert_true(_type_parse_simple_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "short int", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_simple_builtin__int(void** state)
{
    const char* str = "int";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_INT, strlen(str), str);

    assert_true(_type_parse_simple_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "int", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_simple_builtin__long(void** state)
{
    const char* str = "long";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_LONG, strlen(str), str);

    assert_true(_type_parse_simple_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "long", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_simple_builtin__long_int(void** state)
{
    const char* str = "long int";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_LONG, strlen("long"), "long");

    assert_true(_type_parse_simple_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "long int", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_simple_builtin__long_double(void** state)
{
    const char* str = "long double";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_LONG, strlen("long"), "long");

    assert_true(_type_parse_simple_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "long double", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_simple_builtin__float(void** state)
{
    const char* str = "float";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_FLOAT, strlen(str), str);

    assert_true(_type_parse_simple_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "float", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_simple_builtin__double(void** state)
{
    const char* str = "double";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_DOUBLE, strlen(str), str);

    assert_true(_type_parse_simple_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "double", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_simple_builtin__char_pointer(void** state)
{
    const char* str = "char*";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_CHAR, strlen("char"), "char");

    assert_true(_type_parse_simple_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "char*", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_simple_builtin__cstl_bool(void** state)
{
    const char* str = "bool_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_CSTL_BOOL, strlen(str), str);

    assert_true(_type_parse_simple_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "bool_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_simple_builtin__invalid_token(void** state)
{
    const char* str = "type_abc_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_STRUCT, strlen(str), str);

    assert_false(_type_parse_simple_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
}

#ifndef _MSC_VER
void test__type_parse_simple_builtin__bool(void** state)
{
    const char* str = "_Bool";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_BOOL, strlen(str), str);

    assert_true(_type_parse_simple_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "_Bool", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_simple_builtin__long_long_int(void** state)
{
    const char* str = "long long int";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_LONG, strlen("long"), "long");

    assert_true(_type_parse_simple_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "long long int", _TYPE_NAME_SIZE) == 0);
}
#endif

/*
 * test _type_parse_c_builtin
 */
UT_CASE_DEFINATION(_type_parse_c_builtin)
void test__type_parse_c_builtin__null(void** state)
{
    expect_assert_failure(_type_parse_c_builtin(NULL));
}

void test__type_parse_c_builtin__simple_builtin(void** state)
{
    const char* str = "bool_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_CSTL_BOOL, strlen(str), str);

    assert_true(_type_parse_c_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "bool_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_c_builtin__signed(void** state)
{
    const char* str = "signed int";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_SIGNED, strlen("signed"), "signed");

    assert_true(_type_parse_c_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "signed int", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_c_builtin__unsigned(void** state)
{
    const char* str = "unsigned int";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_UNSIGNED, strlen("unsigned"), "unsigned");

    assert_true(_type_parse_c_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "unsigned int", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_c_builtin__pointer(void** state)
{
    const char* str = "void *";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_VOID, strlen("void"), "void");

    assert_true(_type_parse_c_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "void*", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_c_builtin__invalid_token(void** state)
{
    const char* str = "unsigned int";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_INVALID, strlen("unsigned"), "unsigned");

    assert_false(_type_parse_c_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
}

/*
 * test _type_parse_relation
 */
UT_CASE_DEFINATION(_type_parse_relation)
void test__type_parse_relation__null(void** state)
{
    expect_assert_failure(_type_parse_relation(NULL));
}

void test__type_parse_relation__invalid_left_bracket(void** state)
{
    const char* str = "map_t type_abc_t, type_abc_t>";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_MAP, strlen("map_t"), "map_t");

    assert_false(_type_parse_relation(s_formalname));
    assert_true(strncmp(s_formalname, "map_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_relation__invalid_first_descriptor(void** state)
{
    const char* str = "map_t <<type_abc_t, type_abc_t>";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_MAP, strlen("map_t"), "map_t");

    assert_false(_type_parse_relation(s_formalname));
    assert_true(strncmp(s_formalname, "map_t<", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_relation__invalid_comma(void** state)
{
    const char* str = "map_t <type_abc_t type_abc_t>";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_MAP, strlen("map_t"), "map_t");

    assert_false(_type_parse_relation(s_formalname));
    assert_true(strncmp(s_formalname, "map_t<type_abc_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_relation__invalid_second_descriptor(void** state)
{
    const char* str = "map_t <type_abc_t,,type_abc_t>";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_MAP, strlen("map_t"), "map_t");

    assert_false(_type_parse_relation(s_formalname));
    assert_true(strncmp(s_formalname, "map_t<type_abc_t,", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_relation__invalid_right_bracket(void** state)
{
    const char* str = "map_t <type_abc_t,type_abc_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_MAP, strlen("map_t"), "map_t");

    assert_false(_type_parse_relation(s_formalname));
    assert_true(strncmp(s_formalname, "map_t<type_abc_t,type_abc_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_relation__valid(void** state)
{
    const char* str = "map_t <type_abc_t,type_abc_t>";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_MAP, strlen("map_t"), "map_t");

    assert_true(_type_parse_relation(s_formalname));
    assert_true(strncmp(s_formalname, "map_t<type_abc_t,type_abc_t>", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_relation__invalid_token(void** state)
{
    const char* str = "map_t <type_abc_t,type_abc_t>";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_INVALID, strlen("map_t"), "map_t");

    assert_false(_type_parse_relation(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
}

/*
 * test _type_parse_sequence
 */
UT_CASE_DEFINATION(_type_parse_sequence)
void test__type_parse_sequence__null(void** state)
{
    expect_assert_failure(_type_parse_sequence(NULL));
}

void test__type_parse_sequence__invalid_left_bracket(void** state)
{
    const char* str = "vector_t  type_abc_t>";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_VECTOR, strlen("vector_t"), "vector_t");

    assert_false(_type_parse_sequence(s_formalname));
    assert_true(strncmp(s_formalname, "vector_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_sequence__invalid_descriptor(void** state)
{
    const char* str = "vector_t <>";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_VECTOR, strlen("vector_t"), "vector_t");

    assert_false(_type_parse_sequence(s_formalname));
    assert_true(strncmp(s_formalname, "vector_t<", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_sequence__invalid_right_bracket(void** state)
{
    const char* str = "vector_t <type_abc_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_VECTOR, strlen("vector_t"), "vector_t");

    assert_false(_type_parse_sequence(s_formalname));
    assert_true(strncmp(s_formalname, "vector_t<type_abc_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_sequence__valid(void** state)
{
    const char* str = "vector_t <type_abc_t    >";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_VECTOR, strlen("vector_t"), "vector_t");

    assert_true(_type_parse_sequence(s_formalname));
    assert_true(strncmp(s_formalname, "vector_t<type_abc_t>", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_sequence__invalid_token(void** state)
{
    const char* str = "vector_t <type_abc_t>";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_INVALID, strlen("vector_t"), "vector_t");

    assert_false(_type_parse_sequence(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_sequence__basic_string(void** state)
{
    const char* str = "basic_string_t < unsigned long   long    >";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_BASIC_STRING, strlen("basic_string_t"), "basic_string_t");

    assert_true(_type_parse_sequence(s_formalname));
    assert_true(strncmp(s_formalname, "basic_string_t<unsigned long long>", _TYPE_NAME_SIZE) == 0);
}

/*
 * test _type_parse_cstl_builtin
 */
UT_CASE_DEFINATION(_type_parse_cstl_builtin)
void test__type_parse_cstl_builtin__null(void** state)
{
    expect_assert_failure(_type_parse_cstl_builtin(NULL));
}

void test__type_parse_cstl_builtin__sequence(void** state)
{
    const char* str = "vector_t <type_abc_t    >";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_VECTOR, strlen("vector_t"), "vector_t");

    assert_true(_type_parse_cstl_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "vector_t<type_abc_t>", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_cstl_builtin__relation(void** state)
{
    const char* str = "hash_map_t <type_abc_t , int   >";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_HASH_MAP, strlen("hash_map_t"), "hash_map_t");

    assert_true(_type_parse_cstl_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "hash_map_t<type_abc_t,int>", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_cstl_builtin__iterator(void** state)
{
    const char* str = "set_iterator_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_SET_ITERATOR, strlen("set_iterator_t"), "set_iterator_t");

    assert_true(_type_parse_cstl_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "set_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_cstl_builtin__invalid_token(void** state)
{
    const char* str = "vector_t <type_abc_t>";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_INVALID, strlen("vector_t"), "vector_t");

    assert_false(_type_parse_sequence(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_cstl_builtin__string(void** state)
{
    const char* str = "string_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_STRING, strlen("string_t"), "string_t");

    assert_true(_type_parse_cstl_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "string_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_cstl_builtin__range(void** state)
{
    const char* str = "range_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_RANGE, strlen("range_t"), "range_t");

    assert_true(_type_parse_cstl_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "range_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_cstl_builtin__basic_string(void** state)
{
    const char* str = "basic_string_t <map_t<long, long long int>>";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_BASIC_STRING, strlen("basic_string_t"), "basic_string_t");

    assert_true(_type_parse_cstl_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "basic_string_t<map_t<long,long long int>>", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_cstl_builtin__basic_string_iterator(void** state)
{
    const char* str = "basic_string_iterator_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_BASIC_STRING_ITERATOR, strlen("basic_string_iterator_t"), "basic_string_iterator_t");

    assert_true(_type_parse_cstl_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "basic_string_iterator_t", _TYPE_NAME_SIZE) == 0);
}

/*
 * test _type_parse_type_descript
 */
UT_CASE_DEFINATION(_type_parse_type_descript)
void test__type_parse_type_descript__null(void** state)
{
    expect_assert_failure(_type_parse_type_descript(NULL));
}

void test__type_parse_type_descript__c_builtin(void** state)
{
    const char* str = "int";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_INT, strlen("int"), "int");

    assert_true(_type_parse_type_descript(s_formalname));
    assert_true(strncmp(s_formalname, "int", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_type_descript__user_define_invalid(void** state)
{
    const char* str = "xtype_abc_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_IDENTIFIER, strlen("xtype_abc_t"), "xtype_abc_t");

    assert_false(_type_parse_type_descript(s_formalname));
    assert_true(strncmp(s_formalname, "xtype_abc_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_type_descript__user_define(void** state)
{
    const char* str = "type_abc_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};

    test_parse_setup_ex(str, _TOKEN_IDENTIFIER, strlen("type_abc_t"), "type_abc_t");

    assert_true(_type_parse_type_descript(s_formalname));
    assert_true(strncmp(s_formalname, "type_abc_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_type_descript__cstl_builtin(void** state)
{
    const char* str = "vector_t <type_abc_t>";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_VECTOR, strlen("vector_t"), "vector_t");

    assert_true(_type_parse_type_descript(s_formalname));
    assert_true(strncmp(s_formalname, "vector_t<type_abc_t>", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_type_descript__invalid_token(void** state)
{
    const char* str = "vector_t <type_abc_t>";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_INVALID, strlen("vector_t"), "vector_t");

    assert_false(_type_parse_type_descript(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_type_descript__basic_string_iterator(void** state)
{
    const char* str = "basic_string_iterator_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_BASIC_STRING_ITERATOR, strlen("basic_string_iterator_t"), "basic_string_iterator_t");

    assert_true(_type_parse_type_descript(s_formalname));
    assert_true(strncmp(s_formalname, "basic_string_iterator_t", _TYPE_NAME_SIZE) == 0);
}

/*
 * test _type_get_style
 */
UT_CASE_DEFINATION(_type_get_style)
void test__type_get_style__null_typename(void** state)
{
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    expect_assert_failure(_type_get_style(NULL, s_formalname));
}

void test__type_get_style__null_formalname(void** state)
{
    const char* str = "vector_t<int>";
    expect_assert_failure(_type_get_style(str, NULL));
}

void test__type_get_style__name_too_long(void** state)
{
    char s_typename[1024] = {'\0'};
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    memset(s_typename, 'a', 1023);
    expect_assert_failure(_type_get_style(s_typename, s_formalname));
}

void test__type_get_style__c_builtin(void** state)
{
    const char* s_typename = "int";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};

    assert_true(_type_get_style(s_typename, s_formalname) == _TYPE_C_BUILTIN);
    assert_true(strncmp(s_formalname, "int", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_style__c_builtin_invalid(void** state)
{
    const char* s_typename = "int int";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};

    assert_true(_type_get_style(s_typename, s_formalname) == _TYPE_INVALID);
    assert_true(strncmp(s_formalname, "int", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_style__c_builtin_pointer(void** state)
{
    const char* s_typename = "void    *";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};

    assert_true(_type_get_style(s_typename, s_formalname) == _TYPE_C_BUILTIN);
    assert_true(strncmp(s_formalname, "void*", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_style__user_define(void** state)
{
    const char* s_typename = "type_abc_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};

    assert_true(_type_get_style(s_typename, s_formalname) == _TYPE_USER_DEFINE);
    assert_true(strncmp(s_formalname, "type_abc_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_style__user_define_not_register(void** state)
{
    const char* s_typename = "xtype_abc_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};

    assert_true(_type_get_style(s_typename, s_formalname) == _TYPE_USER_DEFINE);
    assert_true(strncmp(s_formalname, "xtype_abc_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_style__user_define_invalid(void** state)
{
    const char* s_typename = "struct enum";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};

    assert_true(_type_get_style(s_typename, s_formalname) == _TYPE_INVALID);
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_style__cstl_builtin(void** state)
{
    const char* s_typename = "vector_t<int>";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};

    assert_true(_type_get_style(s_typename, s_formalname) == _TYPE_CSTL_BUILTIN);
    assert_true(strncmp(s_formalname, "vector_t<int>", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_style__cstl_builtin_invalid(void** state)
{
    const char* s_typename = "vector_t<xtype_abc_t>";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};

    assert_true(_type_get_style(s_typename, s_formalname) == _TYPE_INVALID);
    assert_true(strncmp(s_formalname, "vector_t<xtype_abc_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_style__invalid(void** state)
{
    const char* s_typename = "<<<<";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};

    assert_true(_type_get_style(s_typename, s_formalname) == _TYPE_INVALID);
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_style__basic_string(void** state)
{
    const char* s_typename = "basic_string_t   <basic_string_t<    basic_string_t   <int>>    >";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};

    assert_true(_type_get_style(s_typename, s_formalname) == _TYPE_CSTL_BUILTIN);
    assert_true(strncmp(s_formalname, "basic_string_t<basic_string_t<basic_string_t<int>>>", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_style__basic_string_iterator(void** state)
{
    const char* s_typename = "basic_string_iterator_t";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};

    assert_true(_type_get_style(s_typename, s_formalname) == _TYPE_CSTL_BUILTIN);
    assert_true(strncmp(s_formalname, "basic_string_iterator_t", _TYPE_NAME_SIZE) == 0);
}

#ifndef _MSC_VER
/*
 * test _type_parse_complex_long_suffix
 */
UT_CASE_DEFINATION(_type_parse_complex_long_suffix)
void test__type_parse_complex_long_suffix__null(void** state)
{
    expect_assert_failure(_type_parse_complex_long_suffix(NULL));
}

void test__type_parse_complex_long_suffix__long(void** state)
{
    const char* str = "long";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_LONG, strlen(str), str);

    assert_true(_type_parse_complex_long_suffix(s_formalname));
    assert_true(strncmp(s_formalname, " long", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_complex_long_suffix__common_suffix(void** state)
{
    const char* str = "int";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_INT, strlen(str), str);

    assert_true(_type_parse_complex_long_suffix(s_formalname));
    assert_true(strncmp(s_formalname, " int", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_complex_long_suffix__common_suffix_comma(void** state)
{
    const char* str = ",";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_SIGN_COMMA, strlen(str), str);

    assert_true(_type_parse_complex_long_suffix(s_formalname));
    assert_true(_gt_typeanalysis._t_index == 0);
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_complex_long_suffix__invalid_token(void** state)
{
    const char* str = "struct";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_STRUCT, strlen(str), str);

    assert_false(_type_parse_complex_long_suffix(s_formalname));
    assert_true(strncmp(s_formalname, "", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_signed_builtin__signed_long_long_int(void** state)
{
    const char* str = "signed long long int";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_SIGNED, strlen("signed"), "signed");

    assert_true(_type_parse_signed_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "signed long long int", _TYPE_NAME_SIZE) == 0);
}

void test__type_parse_unsigned_builtin__unsigned_long_long_int(void** state)
{
    const char* str = "unsigned long long int";
    char s_formalname[_TYPE_NAME_SIZE + 1] = {'\0'};
    test_parse_setup_ex(str, _TOKEN_KEY_UNSIGNED, strlen("unsigned"), "unsigned");

    assert_true(_type_parse_unsigned_builtin(s_formalname));
    assert_true(strncmp(s_formalname, "unsigned long long int", _TYPE_NAME_SIZE) == 0);
}
#endif
