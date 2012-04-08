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

/*
 * test _type_get_token
 */
UT_CASE_DEFINATION(_type_get_token)

static void test__type_get_token__setup(const char* typename)
{
    _gt_typeanalysis._t_token = _TOKEN_INVALID;
    _gt_typeanalysis._t_index = 0;
    memset(_gt_typeanalysis._s_tokentext, '\0', _TYPE_NAME_SIZE + 1);
    memset(_gt_typeanalysis._s_typename, '\0', _TYPE_NAME_SIZE + 1);
    strncpy(_gt_typeanalysis._s_typename, typename, _TYPE_NAME_SIZE);
}

void test__type_get_token__sign_left_bracket(void** state)
{
    test__type_get_token__setup("<");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_SIGN_LEFT_BRACKET);
    assert_true(_gt_typeanalysis._t_index == 1);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "<", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__sign_right_bracket(void** state)
{
    test__type_get_token__setup(">");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_SIGN_RIGHT_BRACKET);
    assert_true(_gt_typeanalysis._t_index == 1);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, ">", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__sign_comma(void** state)
{
    test__type_get_token__setup(",");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_SIGN_COMMA);
    assert_true(_gt_typeanalysis._t_index == 1);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, ",", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__sign_space_and_eoi(void** state)
{
    test__type_get_token__setup(" \t\v\f\r\n");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_END_OF_INPUT);
    assert_true(_gt_typeanalysis._t_index == 6);
    assert_true(strlen(_gt_typeanalysis._s_tokentext) == 0);
}

void test__type_get_token__sign_invalid(void** state)
{
    test__type_get_token__setup("@#$");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_INVALID);
    assert_true(_gt_typeanalysis._t_index == 0);
    assert_true(strlen(_gt_typeanalysis._s_tokentext) == 0);
}

void test__type_get_token__identifier(void** state)
{
    test__type_get_token__setup("abc");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_IDENTIFIER);
    assert_true(_gt_typeanalysis._t_index == 3);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "abc", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__identifier_with_underline(void** state)
{
    test__type_get_token__setup("_abc_xyz_");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_IDENTIFIER);
    assert_true(_gt_typeanalysis._t_index == 9);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "_abc_xyz_", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__identifier_pointer(void** state)
{
    test__type_get_token__setup("abc_*");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_IDENTIFIER);
    assert_true(_gt_typeanalysis._t_index == 5);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "abc_*", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__identifier_multipointer(void** state)
{
    test__type_get_token__setup("abc_ *       * **");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_IDENTIFIER);
    assert_true(_gt_typeanalysis._t_index == 17);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "abc_****", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_char(void** state)
{
    test__type_get_token__setup("char");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_CHAR);
    assert_true(_gt_typeanalysis._t_index == 4);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "char", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_char_pointer(void** state)
{
    test__type_get_token__setup("char *  ");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_CHAR_POINTER);
    assert_true(_gt_typeanalysis._t_index == 8);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "char*", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_short(void** state)
{
    test__type_get_token__setup("short");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_SHORT);
    assert_true(_gt_typeanalysis._t_index == 5);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "short", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_int(void** state)
{
    test__type_get_token__setup("int");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_INT);
    assert_true(_gt_typeanalysis._t_index == 3);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "int", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_long(void** state)
{
    test__type_get_token__setup("long");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_LONG);
    assert_true(_gt_typeanalysis._t_index == 4);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "long", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_double(void** state)
{
    test__type_get_token__setup("double");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_DOUBLE);
    assert_true(_gt_typeanalysis._t_index == 6);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "double", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_float(void** state)
{
    test__type_get_token__setup("float");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_FLOAT);
    assert_true(_gt_typeanalysis._t_index == 5);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "float", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_signed(void** state)
{
    test__type_get_token__setup("signed");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_SIGNED);
    assert_true(_gt_typeanalysis._t_index == 6);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "signed", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_unsigned(void** state)
{
    test__type_get_token__setup("unsigned");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_UNSIGNED);
    assert_true(_gt_typeanalysis._t_index == 8);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "unsigned", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_bool(void** state)
{
    test__type_get_token__setup("bool_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_BOOL);
    assert_true(_gt_typeanalysis._t_index == 6);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "bool_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_struct(void** state)
{
    test__type_get_token__setup("struct");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_STRUCT);
    assert_true(_gt_typeanalysis._t_index == 6);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "struct", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_enum(void** state)
{
    test__type_get_token__setup("enum");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_ENUM);
    assert_true(_gt_typeanalysis._t_index == 4);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "enum", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_union(void** state)
{
    test__type_get_token__setup("union");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_UNION);
    assert_true(_gt_typeanalysis._t_index == 5);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "union", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_vector(void** state)
{
    test__type_get_token__setup("vector_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_VECTOR);
    assert_true(_gt_typeanalysis._t_index == 8);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "vector_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_list(void** state)
{
    test__type_get_token__setup("list_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_LIST);
    assert_true(_gt_typeanalysis._t_index == 6);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "list_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_slist(void** state)
{
    test__type_get_token__setup("slist_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_SLIST);
    assert_true(_gt_typeanalysis._t_index == 7);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "slist_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_deque(void** state)
{
    test__type_get_token__setup("deque_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_DEQUE);
    assert_true(_gt_typeanalysis._t_index == 7);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "deque_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_stack(void** state)
{
    test__type_get_token__setup("stack_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_STACK);
    assert_true(_gt_typeanalysis._t_index == 7);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "stack_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_queue(void** state)
{
    test__type_get_token__setup("queue_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_QUEUE);
    assert_true(_gt_typeanalysis._t_index == 7);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "queue_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_priority_queue(void** state)
{
    test__type_get_token__setup("priority_queue_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_PRIORITY_QUEUE);
    assert_true(_gt_typeanalysis._t_index == 16);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "priority_queue_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_set(void** state)
{
    test__type_get_token__setup("set_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_SET);
    assert_true(_gt_typeanalysis._t_index == 5);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "set_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_map(void** state)
{
    test__type_get_token__setup("map_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_MAP);
    assert_true(_gt_typeanalysis._t_index == 5);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "map_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_multiset(void** state)
{
    test__type_get_token__setup("multiset_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_MULTISET);
    assert_true(_gt_typeanalysis._t_index == 10);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "multiset_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_multimap(void** state)
{
    test__type_get_token__setup("multimap_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_MULTIMAP);
    assert_true(_gt_typeanalysis._t_index == 10);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "multimap_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_hash_set(void** state)
{
    test__type_get_token__setup("hash_set_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_HASH_SET);
    assert_true(_gt_typeanalysis._t_index == 10);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "hash_set_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_hash_map(void** state)
{
    test__type_get_token__setup("hash_map_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_HASH_MAP);
    assert_true(_gt_typeanalysis._t_index == 10);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "hash_map_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_hash_multiset(void** state)
{
    test__type_get_token__setup("hash_multiset_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_HASH_MULTISET);
    assert_true(_gt_typeanalysis._t_index == 15);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "hash_multiset_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_hash_multimap(void** state)
{
    test__type_get_token__setup("hash_multimap_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_HASH_MULTIMAP);
    assert_true(_gt_typeanalysis._t_index == 15);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "hash_multimap_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_pair(void** state)
{
    test__type_get_token__setup("pair_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_PAIR);
    assert_true(_gt_typeanalysis._t_index == 6);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "pair_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_string(void** state)
{
    test__type_get_token__setup("string_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_STRING);
    assert_true(_gt_typeanalysis._t_index == 8);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "string_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_iterator(void** state)
{
    test__type_get_token__setup("iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 10);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_vector_iterator(void** state)
{
    test__type_get_token__setup("vector_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_VECTOR_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 17);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "vector_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_list_iterator(void** state)
{
    test__type_get_token__setup("list_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_LIST_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 15);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "list_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_slist_iterator(void** state)
{
    test__type_get_token__setup("slist_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_SLIST_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 16);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "slist_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_deque_iterator(void** state)
{
    test__type_get_token__setup("deque_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_DEQUE_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 16);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "deque_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_set_iterator(void** state)
{
    test__type_get_token__setup("set_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_SET_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 14);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "set_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_map_iterator(void** state)
{
    test__type_get_token__setup("map_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_MAP_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 14);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "map_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_multiset_iterator(void** state)
{
    test__type_get_token__setup("multiset_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_MULTISET_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 19);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "multiset_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_multimap_iterator(void** state)
{
    test__type_get_token__setup("multimap_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_MULTIMAP_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 19);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "multimap_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_hash_set_iterator(void** state)
{
    test__type_get_token__setup("hash_set_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_HASH_SET_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 19);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "hash_set_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_hash_map_iterator(void** state)
{
    test__type_get_token__setup("hash_map_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_HASH_MAP_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 19);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "hash_map_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_hash_multiset_iterator(void** state)
{
    test__type_get_token__setup("hash_multiset_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_HASH_MULTISET_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 24);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "hash_multiset_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_hash_multimap_iterator(void** state)
{
    test__type_get_token__setup("hash_multimap_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_HASH_MULTIMAP_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 24);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "hash_multimap_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_string_iterator(void** state)
{
    test__type_get_token__setup("string_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_STRING_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 17);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "string_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_input_iterator(void** state)
{
    test__type_get_token__setup("input_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_INPUT_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 16);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "input_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_output_iterator(void** state)
{
    test__type_get_token__setup("output_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_OUTPUT_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 17);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "output_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_forward_iterator(void** state)
{
    test__type_get_token__setup("forward_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_FORWARD_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 18);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "forward_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_bidirectional_iterator(void** state)
{
    test__type_get_token__setup("bidirectional_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_BIDIRECTIONAL_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 24);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "bidirectional_iterator_t", _TYPE_NAME_SIZE) == 0);
}

void test__type_get_token__key_random_access_iterator(void** state)
{
    test__type_get_token__setup("random_access_iterator_t");
    _type_get_token();
    assert_true(_gt_typeanalysis._t_token == _TOKEN_KEY_RANDOM_ACCESS_ITERATOR);
    assert_true(_gt_typeanalysis._t_index == 24);
    assert_true(strncmp(_gt_typeanalysis._s_tokentext, "random_access_iterator_t", _TYPE_NAME_SIZE) == 0);
}

