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

void test__type_get_token__identifier_pointer(void** state)
{
    test_parse_setup("abc_*");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_IDENTIFIER);
    assert_true(_gt_typeanalysis._t_index == 5);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "abc_*", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__identifier_multipointer(void** state)
{
    test_parse_setup("abc_ *       * **");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_IDENTIFIER);
    assert_true(_gt_typeanalysis._t_index == 17);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "abc_****", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_char(void** state)
{
    test_parse_setup("char");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_CHAR);
    assert_true(_gt_typeanalysis._t_index == 4);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "char", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_char_pointer(void** state)
{
    test_parse_setup("char *  ");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_CHAR_POINTER);
    assert_true(_gt_typeanalysis._t_index == 8);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "char*", _TYPE_NAME_SIZE) == 0);
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

void test__type_get_token__key_bool(void** state)
{
    test_parse_setup("bool_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_BOOL);
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

/*
 * test _type_parse_relation_name
 */
UT_CASE_DEFINATION(_type_parse_relation_name)
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

/*
 * test _type_parse_user_define_type
 */
UT_CASE_DEFINATION(_type_parse_user_define_type)
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

