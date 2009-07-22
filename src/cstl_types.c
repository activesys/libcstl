/*
 *  The implementation of cstl types.
 *  Copyright (C)  2008 2009  Wangbo
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  Author e-mail: activesys.wb@gmail.com
 *                 activesys@sina.com.cn
 */

/** include section **/
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <float.h>

#include "cstl_alloc.h"
#include "cstl_types.h"

#include "cvector.h"
#include "clist.h"
#include "cslist.h"
#include "cdeque.h"
#include "cstack.h"
#include "cqueue.h"
#include "cset.h"
#include "cmap.h"
#include "chash_set.h"
#include "chash_map.h"
#include "cstring.h"
#include "cutility.h"

/** local constant declaration and local macro section **/
/* the pt_type, pt_node and t_pos must be defined before use those macro */
#define _TYPE_REGISTER_BEGIN()\
    _typenode_t* pt_node = NULL;\
    _type_t*     pt_type = NULL;\
    size_t       t_pos = 0
#define _TYPE_REGISTER_TYPE(type, type_text, type_suffix)\
    do{\
        pt_type = (_type_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_type_t), 1);\
        assert(pt_type != NULL);\
        pt_type->_t_typesize = sizeof(type);\
        memset(pt_type->_sz_typename, '\0', _TYPE_NAME_SIZE+1);\
        strncpy(pt_type->_sz_typename, type_text, _TYPE_NAME_SIZE);\
        pt_type->_t_typeinit = _type_init_##type_suffix;\
        pt_type->_t_typecopy = _type_copy_##type_suffix;\
        pt_type->_t_typeless = _type_less_##type_suffix;\
        pt_type->_t_typedestroy = _type_destroy_##type_suffix;\
    }while(false)
#define _TYPE_REGISTER_TYPE_NODE(type, type_text)\
    do{\
        pt_node = (_typenode_t*)allocate(\
            &_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);\
        assert(pt_node != NULL);\
        memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);\
        strncpy(pt_node->_sz_typename, type_text, _TYPE_NAME_SIZE);\
        t_pos = _type_hash(type_text);\
        pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];\
        _gt_typeregister._apt_bucket[t_pos] = pt_node;\
        pt_node->_pt_type = pt_type;\
    }while(false)
#define _TYPE_REGISTER_END()
/*
 * _gt_typeregister
 * +--------------------------------------------------------------------+
 * |     |    |    |    |    |  ...  |    |    |    |    |    |    |    |  
 * +-------+--------------------------------+----+----------------------+
 *         |                                |    |
 *         V                                V    V
 *      +-------------+            +--------+    +----------+
 *      | _typenode_t |            |        |    |          |
 *      +--+----------+            +--------+    +----------+
 *         |                                |    |
 *         V                                V    V
 *      +-------------+                  NULL    +----------+
 *      | "abc_t"     | major name       +-------|"my_abc_t"| duplicated name
 *      +--+----------+                  |       +----------+
 *         |                             |       |
 *         V                             |       V
 *      +-------------+                  |       NULL
 *      |             |----------+-------+ 
 *      +--+----------+          |
 *         |                     |
 *         V                     |
 *         NULL                  V
 *                             +------------------------------+
 *                             | _t_typesize = ???            |
 *                             | _sz_typename = "abc_t"       |
 *                             | _t_typecopy = abc_copy       | "registered type abc_t"
 *                             | _t_typeless = abc_less       |
 *                             | _t_typeinit = abc_init       |
 *                             | _t_typedestroy = abc_destroy |
 *                             +------------------------------+
 */
static _typeregister_t _gt_typeregister = {false, {NULL}, {{NULL}, NULL, NULL, 0, 0, 0}};

/** local data type declaration and local struct, union, enum section **/
typedef enum _tagtypetoken
{
    /* invalid token */
    _TOKEN_INVALID,
    /* EOI */
    _TOKEN_END_OF_INPUT,
    /* c builtin */
    _TOKEN_KEY_CHAR, _TOKEN_KEY_SHORT, _TOKEN_KEY_INT, _TOKEN_KEY_LONG, _TOKEN_KEY_FLOAT,
    _TOKEN_KEY_DOUBLE, _TOKEN_KEY_SIGNED, _TOKEN_KEY_UNSIGNED, _TOKEN_KEY_CHAR_POINTER,
    _TOKEN_KEY_BOOL,
    /* user define */
    _TOKEN_KEY_STRUCT, _TOKEN_KEY_ENUM, _TOKEN_KEY_UNION, _TOKEN_IDENTIFIER,
    /* cstl container */
    _TOKEN_KEY_VECTOR, _TOKEN_KEY_LIST, _TOKEN_KEY_SLIST, _TOKEN_KEY_DEQUE, _TOKEN_KEY_STACK,
    _TOKEN_KEY_QUEUE, _TOKEN_KEY_PRIORITY_QUEUE, _TOKEN_KEY_SET, _TOKEN_KEY_MAP,
    _TOKEN_KEY_MULTISET, _TOKEN_KEY_MULTIMAP, _TOKEN_KEY_HASH_SET, _TOKEN_KEY_HASH_MAP,
    _TOKEN_KEY_HASH_MULTISET, _TOKEN_KEY_HASH_MULTIMAP, _TOKEN_KEY_PAIR, _TOKEN_KEY_STRING,
    /* cst iterator */
    _TOKEN_KEY_ITERATOR, _TOKEN_KEY_VECTOR_ITERATOR, _TOKEN_KEY_LIST_ITERATOR,
    _TOKEN_KEY_SLIST_ITERATOR, _TOKEN_KEY_DEQUE_ITERATOR, _TOKEN_KEY_SET_ITERATOR,
    _TOKEN_KEY_MAP_ITERATOR, _TOKEN_KEY_MULTISET_ITERATOR, _TOKEN_KEY_MULTIMAP_ITERATOR,
    _TOKEN_KEY_HASH_SET_ITERATOR, _TOKEN_KEY_HASH_MAP_ITERATOR,
    _TOKEN_KEY_HASH_MULTISET_ITERATOR, _TOKEN_KEY_HASH_MULTIMAP_ITERATOR,
    _TOKEN_KEY_STRING_ITERATOR, _TOKEN_KEY_INPUT_ITERATOR, _TOKEN_KEY_OUTPUT_ITERATOR,
    _TOKEN_KEY_FORWARD_ITERATOR, _TOKEN_KEY_BIDIRECTIONAL_ITERATOR,
    _TOKEN_KEY_RANDOM_ACCESS_ITERATOR,
    /* sign */
    _TOKEN_SIGN_LEFT_BRACKET, _TOKEN_SIGN_RIGHT_BRACKET, _TOKEN_SIGN_COMMA, _TOKEN_SIGN_SPACE,
    /* ROLLBACK */
    _TOKEN_ROLLBACK
}_typetoken_t;

typedef struct _tagtypeanalysis
{
    char         _sz_typename[_TYPE_NAME_SIZE+1];
    char         _sz_tokentext[_TYPE_NAME_SIZE+1];
    size_t       _t_index;
    _typetoken_t _t_token;
}_typeanalysis_t;
static _typeanalysis_t _gt_typeanalysis = {{'\0'}, {'\0'}, 0, _TOKEN_INVALID};

#define _TOKEN_MATCH(s_tokentext, s_formalname)\
    do{\
        assert(strncmp(_gt_typeanalysis._sz_tokentext, s_tokentext, _TYPE_NAME_SIZE) == 0);\
        strncat(s_formalname, _gt_typeanalysis._sz_tokentext, _TYPE_NAME_SIZE);\
    }while(false)
#define _TOKEN_MATCH_SPACE(s_formalname)\
    strncat(s_formalname, _TOKEN_TEXT_SPACE, _TYPE_NAME_SIZE)
#define _TOKEN_MATCH_IDENTIFIER(s_formalname)\
    strncat(s_formalname, _gt_typeanalysis._sz_tokentext, _TYPE_NAME_SIZE)

#define _TOKEN_TEXT_CHAR                           "char"
#define _TOKEN_TEXT_SHORT                          "short"
#define _TOKEN_TEXT_INT                            "int"
#define _TOKEN_TEXT_LONG                           "long"
#define _TOKEN_TEXT_FLOAT                          "float"
#define _TOKEN_TEXT_DOUBLE                         "double"
#define _TOKEN_TEXT_SIGNED                         "signed"
#define _TOKEN_TEXT_UNSIGNED                       "unsigned"
#define _TOKEN_TEXT_CHAR_POINTER                   "char*"
#define _TOKEN_TEXT_BOOL                           "bool_t"
#define _TOKEN_TEXT_STRUCT                         "struct"
#define _TOKEN_TEXT_ENUM                           "enum"
#define _TOKEN_TEXT_UNION                          "union"
#define _TOKEN_TEXT_VECTOR                         "vector_t"
#define _TOKEN_TEXT_LIST                           "list_t"
#define _TOKEN_TEXT_SLIST                          "slist_t"
#define _TOKEN_TEXT_DEQUE                          "deque_t"
#define _TOKEN_TEXT_STACK                          "stack_t"
#define _TOKEN_TEXT_QUEUE                          "queue_t"
#define _TOKEN_TEXT_PRIORITY_QUEUE                 "priority_queue_t"
#define _TOKEN_TEXT_SET                            "set_t"
#define _TOKEN_TEXT_MAP                            "map_t"
#define _TOKEN_TEXT_MULTISET                       "multiset_t"
#define _TOKEN_TEXT_MULTIMAP                       "multimap_t"
#define _TOKEN_TEXT_HASH_SET                       "hash_set_t"
#define _TOKEN_TEXT_HASH_MAP                       "hash_map_t"
#define _TOKEN_TEXT_HASH_MULTISET                  "hash_multiset_t"
#define _TOKEN_TEXT_HASH_MULTIMAP                  "hash_multimap_t"
#define _TOKEN_TEXT_PAIR                           "pair_t"
#define _TOKEN_TEXT_STRING                         "string_t"
#define _TOKEN_TEXT_ITERATOR                       "iterator_t"
#define _TOKEN_TEXT_VECTOR_ITERATOR                "vector_iterator_t"
#define _TOKEN_TEXT_LIST_ITERATOR                  "list_iterator_t"
#define _TOKEN_TEXT_SLIST_ITERATOR                 "slist_iterator_t"
#define _TOKEN_TEXT_DEQUE_ITERATOR                 "deque_iterator_t"
#define _TOKEN_TEXT_SET_ITERATOR                   "set_iterator_t"
#define _TOKEN_TEXT_MAP_ITERATOR                   "map_iterator_t"
#define _TOKEN_TEXT_MULTISET_ITERATOR              "multiset_iterator_t"
#define _TOKEN_TEXT_MULTIMAP_ITERATOR              "multimap_iterator_t"
#define _TOKEN_TEXT_HASH_SET_ITERATOR              "hash_set_iterator_t"
#define _TOKEN_TEXT_HASH_MAP_ITERATOR              "hash_map_iterator_t"
#define _TOKEN_TEXT_HASH_MULTISET_ITERATOR         "hash_multiset_iterator_t"
#define _TOKEN_TEXT_HASH_MULTIMAP_ITERATOR         "hash_multimap_iterator_t"
#define _TOKEN_TEXT_STRING_ITERATOR                "string_iterator_t"
#define _TOKEN_TEXT_INPUT_ITERATOR                 "input_iterator_t"
#define _TOKEN_TEXT_OUTPUT_ITERATOR                "output_iterator_t"
#define _TOKEN_TEXT_FORWARD_ITERATOR               "forward_iterator_t"
#define _TOKEN_TEXT_BIDIRECTIONAL_ITERATOR         "bidirectional_iterator_t"
#define _TOKEN_TEXT_RANDOM_ACCESS_ITERATOR         "random_access_iterator_t"
#define _TOKEN_TEXT_SPACE                          " "
#define _TOKEN_TEXT_LEFT_BRACKET                   "<"
#define _TOKEN_TEXT_RIGHT_BRACKET                  ">"
#define _TOKEN_TEXT_COMMA                          ","

typedef enum _tagtypelex
{
    _LEX_START, _LEX_IN_IDENTIFIER, _LEX_ACCEPT
}_typelex_t;

/** local function prototype section **/
/******************************* destroy in the future *****************************/
/* default compare function */
static int _cmp_char(const void* cpv_first, const void* cpv_second);
static int _cmp_uchar(const void* cpv_first, const void* cpv_second);
static int _cmp_short(const void* cpv_first, const void* cpv_second);
static int _cmp_ushort(const void* cpv_first, const void* cpv_second);
static int _cmp_int(const void* cpv_first, const void* cpv_second);
static int _cmp_uint(const void* cpv_first, const void* cpv_second);
static int _cmp_long(const void* cpv_first, const void* cpv_second);
static int _cmp_ulong(const void* cpv_first, const void* cpv_second);
static int _cmp_float(const void* cpv_first, const void* cpv_second);
static int _cmp_double(const void* cpv_first, const void* cpv_second);
/******************************* destroy in the future *****************************/

/* register hash function */
static size_t _type_hash(const char* s_typename);
/* init the register and register c builtin type and cstl builtin type */
static void _type_init(void);
/* test the type is registered or not */
static _type_t* _type_is_registered(const char* s_typename);
/* normalize the typename, test the typename is valid or not and get the type style */
static _typestyle_t _type_get_style(const char* s_typename, char* s_formalname);
/* register c builtin and cstl builtin */
static void _type_register_c_builtin(void);
static void _type_register_cstl_builtin(void);

/* the functions blow is used for analyse the type style */
static void _type_get_token(void);
static void _type_token_rollback(void);
static bool_t _type_parse_c_builtin(char* s_formalname);
static bool_t _type_parse_common_suffix(char* s_formalname);
static bool_t _type_parse_simple_long_suffix(char* s_formalname);
static bool_t _type_parse_simple_builtin(char* s_formalname);
static bool_t _type_parse_unsigned_builtin(char* s_formalname);
static bool_t _type_parse_complex_suffix(char* s_formalname);
static bool_t _type_parse_signed_builtin(char* s_formalname);
static bool_t _type_parse_user_define_type(char* s_formalname);
static bool_t _type_parse_user_define(char* s_formalname);
static bool_t _type_parse_sequence_name(char* s_formalname);
static bool_t _type_parse_sequence(char* s_formalname);
static bool_t _type_parse_relation_name(char* s_formalname);
static bool_t _type_parse_iterator(char* s_formalname);
static bool_t _type_parse_relation(char* s_formalname);
static bool_t _type_parse_cstl_builtin(char* s_formalname);

/*
 * the cstl builtin copy, compare destroy function for c builtin type and cstl builtins.
 */
/* c builtin */
/* char */
static void _type_init_char(
    const void* cpv_input, void* pv_output);
static void _type_copy_char(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_char(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_char(
    const void* cpv_input, void* pv_output);
/* unsigned char */
static void _type_init_uchar(
    const void* cpv_input, void* pv_output);
static void _type_copy_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_uchar(
    const void* cpv_input, void* pv_output);
/* short */
static void _type_init_short(
    const void* cpv_input, void* pv_output);
static void _type_copy_short(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_short(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_short(
    const void* cpv_input, void* pv_output);
/* unsigned short */
static void _type_init_ushort(
    const void* cpv_input, void* pv_output);
static void _type_copy_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_ushort(
    const void* cpv_input, void* pv_output);
/* int */
static void _type_init_int(
    const void* cpv_input, void* pv_output);
static void _type_copy_int(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_int(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_int(
    const void* cpv_input, void* pv_output);
/* unsigned int */
static void _type_init_uint(
    const void* cpv_input, void* pv_output);
static void _type_copy_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_uint(
    const void* cpv_input, void* pv_output);
/* long */
static void _type_init_long(
    const void* cpv_input, void* pv_output);
static void _type_copy_long(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_long(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_long(
    const void* cpv_input, void* pv_output);
/* unsigned long */
static void _type_init_ulong(
    const void* cpv_input, void* pv_output);
static void _type_copy_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_ulong(
    const void* cpv_input, void* pv_output);
/* float */
static void _type_init_float(
    const void* cpv_input, void* pv_output);
static void _type_copy_float(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_float(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_float(
    const void* cpv_input, void* pv_output);
/* double */
static void _type_init_double(
    const void* cpv_input, void* pv_output);
static void _type_copy_double(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_double(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_double(
    const void* cpv_input, void* pv_output);
/* long double */
static void _type_init_long_double(
    const void* cpv_input, void* pv_output);
static void _type_copy_long_double(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_long_double(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_long_double(
    const void* cpv_input, void* pv_output);
/* bool_t */
static void _type_init_bool(
    const void* cpv_input, void* pv_output);
static void _type_copy_bool(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_bool(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_bool(
    const void* cpv_input, void* pv_output);
/* char* */
static void _type_init_cstr(
    const void* cpv_input, void* pv_output);
static void _type_copy_cstr(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_cstr(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_cstr(
    const void* cpv_input, void* pv_output);
/* cstl container */
/* vector_t */
static void _type_init_vector(
    const void* cpv_input, void* pv_output);
static void _type_copy_vector(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_vector(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_vector(
    const void* cpv_input, void* pv_output);
/* list_t */
static void _type_init_list(
    const void* cpv_input, void* pv_output);
static void _type_copy_list(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_list(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_list(
    const void* cpv_input, void* pv_output);
/* slist_t */
static void _type_init_slist(
    const void* cpv_input, void* pv_output);
static void _type_copy_slist(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_slist(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_slist(
    const void* cpv_input, void* pv_output);
/* deque_t */
static void _type_init_deque(
    const void* cpv_input, void* pv_output);
static void _type_copy_deque(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_deque(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_deque(
    const void* cpv_input, void* pv_output);
/* stack_t */
static void _type_init_stack(
    const void* cpv_input, void* pv_output);
static void _type_copy_stack(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_stack(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_stack(
    const void* cpv_input, void* pv_output);
/* queue_t */
static void _type_init_queue(
    const void* cpv_input, void* pv_output);
static void _type_copy_queue(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_queue(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_queue(
    const void* cpv_input, void* pv_output);
/* priority_queue_t */
static void _type_init_priority_queue(
    const void* cpv_input, void* pv_output);
static void _type_copy_priority_queue(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_priority_queue(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_priority_queue(
    const void* cpv_input, void* pv_output);
/* set_t */
static void _type_init_set(
    const void* cpv_input, void* pv_output);
static void _type_copy_set(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_set(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_set(
    const void* cpv_input, void* pv_output);
/* map_t */
static void _type_init_map(
    const void* cpv_input, void* pv_output);
static void _type_copy_map(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_map(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_map(
    const void* cpv_input, void* pv_output);
/* multiset_t */
static void _type_init_multiset(
    const void* cpv_input, void* pv_output);
static void _type_copy_multiset(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_multiset(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_multiset(
    const void* cpv_input, void* pv_output);
/* multimap_t */
static void _type_init_multimap(
    const void* cpv_input, void* pv_output);
static void _type_copy_multimap(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_multimap(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_multimap(
    const void* cpv_input, void* pv_output);
/* hash_set_t */
static void _type_init_hash_set(
    const void* cpv_input, void* pv_output);
static void _type_copy_hash_set(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_hash_set(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_hash_set(
    const void* cpv_input, void* pv_output);
/* hash_map_t */
static void _type_init_hash_map(
    const void* cpv_input, void* pv_output);
static void _type_copy_hash_map(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_hash_map(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_hash_map(
    const void* cpv_input, void* pv_output);
/* hash_multiset_t */
static void _type_init_hash_multiset(
    const void* cpv_input, void* pv_output);
static void _type_copy_hash_multiset(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_hash_multiset(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_hash_multiset(
    const void* cpv_input, void* pv_output);
/* hash_multimap_t */
static void _type_init_hash_multimap(
    const void* cpv_input, void* pv_output);
static void _type_copy_hash_multimap(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_hash_multimap(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_hash_multimap(
    const void* cpv_input, void* pv_output);
/* pair_t */
static void _type_init_pair(
    const void* cpv_input, void* pv_output);
static void _type_copy_pair(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_pair(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_pair(
    const void* cpv_input, void* pv_output);
/* string_t */
static void _type_init_string(
    const void* cpv_input, void* pv_output);
static void _type_copy_string(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_string(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_string(
    const void* cpv_input, void* pv_output);
/* iterator_t */
static void _type_init_iterator(
    const void* cpv_input, void* pv_output);
static void _type_copy_iterator(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_iterator(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_iterator(
    const void* cpv_input, void* pv_output);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/*
void type_debug(void)
{
    size_t t_i = 0;
    size_t t_j = 0;
    _typenode_t* pt_node = NULL;
    _type_t* pt_type = NULL;
    _type_t* apt_type[1024] = {NULL};

    for(t_j = 0; t_j < 1024; ++t_j)
    {
        apt_type[t_j] = NULL;
    }

    for(t_i = 0; t_i < _TYPE_REGISTER_BUCKET_COUNT; ++t_i)
    {
        printf("[%u]", t_i);
        pt_node = _gt_typeregister._apt_bucket[t_i];
        while(pt_node != NULL)
        {
            printf("->[%s,%p]", pt_node->_sz_typename, (void*)pt_node->_pt_type);
            for(t_j = 0; t_j < 1024; ++t_j)
            {
                if(apt_type[t_j] == pt_node->_pt_type)
                {
                    break;
                }
                else if(apt_type[t_j] == NULL)
                {
                    apt_type[t_j] = pt_node->_pt_type;
                    break;
                }
            }
            pt_node = pt_node->_pt_next;
        }
        printf("\n");
    }

    for(t_j = 0; t_j < 1024; ++t_j)
    {
        pt_type = apt_type[t_j];
        if(pt_type != NULL)
        {
            printf("%p\n----------\n%d,%s,%p,%p,%p,%p\n========================\n",
                pt_type, pt_type->_t_typesize, pt_type->_sz_typename,
                pt_type->_t_typecopy, pt_type->_t_typeless,
                pt_type->_t_typeinit, pt_type->_t_typedestroy);
        }
    }
}
*/

bool_t _type_register(
    size_t t_typesize, const char* s_typename,
    unary_function_t t_typeinit,
    binary_function_t t_typecopy,
    binary_function_t t_typeless,
    unary_function_t t_typedestroy)
{
    char s_formalname[_TYPE_NAME_SIZE + 1];

    if(!_gt_typeregister._t_isinit)
    {
        _type_init();
    }

    /* the main aim is getting formal name */
    _type_get_style(s_typename, s_formalname);
    if(_type_is_registered(s_formalname) != NULL || strlen(s_typename) > _TYPE_NAME_SIZE)
    {
         return false;
    }
    else
    {
        size_t t_pos = 0;
        _typenode_t* pt_node = (_typenode_t*)allocate(
            &_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
        _type_t* pt_type = (_type_t*)allocate(
            &_gt_typeregister._t_allocator, sizeof(_type_t), 1);

        memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
        memset(pt_type->_sz_typename, '\0', _TYPE_NAME_SIZE+1);

        /* register the new type */
        strncpy(pt_node->_sz_typename, s_formalname, _TYPE_NAME_SIZE);
        strncpy(pt_type->_sz_typename, s_formalname, _TYPE_NAME_SIZE);
        pt_type->_t_typesize = t_typesize;
        pt_type->_t_typeinit = t_typeinit != NULL ? t_typeinit : _type_init_default;
        pt_type->_t_typecopy = t_typecopy != NULL ? t_typecopy : _type_copy_default;
        pt_type->_t_typeless = t_typeless != NULL ? t_typeless : _type_less_default;
        pt_type->_t_typedestroy = t_typedestroy != NULL ? 
            t_typedestroy : _type_destroy_default;

        pt_node->_pt_type = pt_type;
        t_pos = _type_hash(s_formalname);
        pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
        _gt_typeregister._apt_bucket[t_pos] = pt_node;

        return true;
    }
}

/*
void _type_unregister(size_t t_typesize, const char* s_typename)
{
    _type_t*     pt_type = NULL;
    size_t       t_avoidwarning = 0;
    char         s_formalname[_TYPE_NAME_SIZE + 1];

    t_avoidwarning = t_typesize;
    if(strlen(s_typename) > _TYPE_NAME_SIZE)
    {
        return;
    }

    if(_type_get_style(s_typename, s_formalname) != _TYPE_USER_DEFINE)
    {
        return;
    }
    pt_type = _type_is_registered(s_formalname);

    if(pt_type != NULL)
    {
        _typenode_t* pt_curnode = NULL;
        _typenode_t* pt_prevnode = NULL;
        size_t       t_i = 0;

        for(t_i = 0; t_i < _TYPE_REGISTER_BUCKET_COUNT; ++t_i)
        {
            pt_curnode = pt_prevnode = _gt_typeregister._apt_bucket[t_i];
            while(pt_curnode != NULL)
            {
                if(pt_curnode->_pt_type == pt_type)
                {
                    if(pt_curnode == _gt_typeregister._apt_bucket[t_i])
                    {
                        _gt_typeregister._apt_bucket[t_i] = pt_curnode->_pt_next;
                        deallocate(&_gt_typeregister._t_allocator,
                            pt_curnode, sizeof(_typenode_t), 1);
                        pt_curnode = pt_prevnode = _gt_typeregister._apt_bucket[t_i];
                    }
                    else
                    {
                        assert(pt_prevnode->_pt_next == pt_curnode);
                        pt_prevnode->_pt_next = pt_curnode->_pt_next;
                        deallocate(&_gt_typeregister._t_allocator,
                            pt_curnode, sizeof(_typenode_t), 1);
                        pt_curnode = pt_prevnode->_pt_next;
                    }
                }
                else
                {
                    if(pt_curnode == _gt_typeregister._apt_bucket[t_i])
                    {
                        assert(pt_curnode == pt_prevnode);
                        pt_curnode = pt_curnode->_pt_next;
                    }
                    else
                    {
                        assert(pt_curnode == pt_prevnode->_pt_next);
                        pt_prevnode = pt_curnode;
                        pt_curnode = pt_curnode->_pt_next;
                    }
                }
            }
        }

        deallocate(&_gt_typeregister._t_allocator, pt_type, sizeof(_type_t), 1);
    }
}
*/

bool_t _type_duplicate(
    size_t t_typesize1, const char* s_typename1,
    size_t t_typesize2, const char* s_typename2)
{
    _type_t* pt_registered1 = NULL;
    _type_t* pt_registered2 = false;
    char     s_formalname1[_TYPE_NAME_SIZE + 1];
    char     s_formalname2[_TYPE_NAME_SIZE + 1];

    if(!_gt_typeregister._t_isinit)
    {
        _type_init();
    }

    if(strlen(s_typename1) > _TYPE_NAME_SIZE ||
       strlen(s_typename2) > _TYPE_NAME_SIZE ||
       t_typesize1 != t_typesize2)
    {
        return false;
    }

    _type_get_style(s_typename1, s_formalname1);
    _type_get_style(s_typename2, s_formalname2);
    /* test the type1 and type2 is registered or not */
    pt_registered1 = _type_is_registered(s_formalname1);
    pt_registered2 = _type_is_registered(s_formalname2);

    /* type1 and type2 all unregistered */
    if(pt_registered1 == NULL && pt_registered2 == NULL)
    {
        return false;
    }
    /* type1 and type2 all registered */
    else if(pt_registered1 != NULL && pt_registered2 != NULL)
    {
        return pt_registered1 == pt_registered2 ? true : false;
    }
    /* only one type is registered */
    else
    {
        size_t       t_pos = 0;
        char*        s_duplicatename = NULL;
        _typenode_t* pt_duplicate = NULL;
        _type_t*     pt_type = NULL;

        /* type1 is registered and type2 is unregistered */
        if(pt_registered1 != NULL && pt_registered2 == NULL)
        {
            pt_type = pt_registered1;
            s_duplicatename = s_formalname2;
        }
        /* type1 is unregistered and type2 is registered */
        else
        {
            pt_type = pt_registered2;
            s_duplicatename = s_formalname1;
        }

        /* malloc typenode for unregistered type */
        pt_duplicate = (_typenode_t*)allocate(
            &_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
        memset(pt_duplicate->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
        strncpy(pt_duplicate->_sz_typename, s_duplicatename, _TYPE_NAME_SIZE);

        pt_duplicate->_pt_type = pt_type;

        t_pos = _type_hash(s_duplicatename);
        pt_duplicate->_pt_next = _gt_typeregister._apt_bucket[t_pos];
        _gt_typeregister._apt_bucket[t_pos] = pt_duplicate;

        return true;
    }
}

void _type_get_type_pair(
    _typeinfo_t* pt_typeinfofirst, _typeinfo_t* pt_typeinfosecond, const char* s_typename)
{
    /* this function get type information for pair_t and relation container */
    char  s_firsttypename[_TYPE_NAME_SIZE + 1];
    char  s_secondtypename[_TYPE_NAME_SIZE + 1];
    char* pc_commapos = NULL;
    char* pc_newstart = NULL;

    assert(pt_typeinfofirst != NULL && pt_typeinfosecond != NULL && s_typename != NULL);

    pt_typeinfofirst->_t_style = _TYPE_INVALID;
    pt_typeinfofirst->_pt_type = NULL;
    pt_typeinfosecond->_t_style = _TYPE_INVALID;
    pt_typeinfosecond->_pt_type = NULL;

    /* the type name is separated in two section by comma */
    pc_newstart = (char*)s_typename;
    while((pc_commapos = strchr(pc_newstart, _CSTL_COMMA)) != NULL)
    {
        memset(s_firsttypename, '\0', _TYPE_NAME_SIZE + 1);
        memset(s_secondtypename, '\0', _TYPE_NAME_SIZE + 1);
        strncpy(s_firsttypename, s_typename, pc_commapos - s_typename);
        strncpy(s_secondtypename, pc_commapos + 1, _TYPE_NAME_SIZE);

        _type_get_type(pt_typeinfofirst, s_firsttypename);
        _type_get_type(pt_typeinfosecond, s_secondtypename);
        if(pt_typeinfofirst->_t_style != _TYPE_INVALID &&
           pt_typeinfofirst->_pt_type != NULL &&
           pt_typeinfosecond->_t_style != _TYPE_INVALID &&
           pt_typeinfosecond->_pt_type != NULL)
        {
            return;
        }

        pt_typeinfofirst->_t_style = _TYPE_INVALID;
        pt_typeinfofirst->_pt_type = NULL;
        pt_typeinfosecond->_t_style = _TYPE_INVALID;
        pt_typeinfosecond->_pt_type = NULL;

        pc_newstart = pc_commapos + 1;
    }
}

void _type_get_type(_typeinfo_t* pt_typeinfo, const char* s_typename)
{
    char         s_registeredname[_TYPE_NAME_SIZE+1];

    assert(pt_typeinfo != NULL && s_typename != NULL);

    if(!_gt_typeregister._t_isinit)
    {
        _type_init();
    }

    memset(s_registeredname, '\0', _TYPE_NAME_SIZE+1);
    pt_typeinfo->_t_style = _type_get_style(s_typename, pt_typeinfo->_sz_typename);
    if(pt_typeinfo->_t_style == _TYPE_INVALID)
    {
        pt_typeinfo->_pt_type = NULL;
        return;
    }
    else if(pt_typeinfo->_t_style == _TYPE_C_BUILTIN ||
            pt_typeinfo->_t_style == _TYPE_USER_DEFINE)
    {
        strncpy(s_registeredname, pt_typeinfo->_sz_typename, _TYPE_NAME_SIZE);
    }
    else /* get container name */
    {
        char* pc_leftbracket = strchr(pt_typeinfo->_sz_typename, '<');
        assert(pc_leftbracket != NULL);
        strncpy(s_registeredname, pt_typeinfo->_sz_typename,
                pc_leftbracket-pt_typeinfo->_sz_typename);
    }

    pt_typeinfo->_pt_type = _type_is_registered(s_registeredname);
}

bool_t _type_is_same(const char* s_typename1, const char* s_typename2)
{
    /* s_typename1 and s_typename2 is formal name */
    char s_elemname1[_TYPE_NAME_SIZE+1];
    char s_prefix1[_TYPE_NAME_SIZE+1];
    char s_elemname2[_TYPE_NAME_SIZE+1];
    char s_prefix2[_TYPE_NAME_SIZE+1];
    char* pc_index1 = NULL;
    char* pc_leftbracket1 = NULL;
    char* pc_rightbracket1 = NULL;
    char* pc_comma1 = NULL;
    char* pc_index2 = NULL;
    char* pc_leftbracket2 = NULL;
    char* pc_rightbracket2 = NULL;
    char* pc_comma2 = NULL;

    memset(s_elemname1, '\0', _TYPE_NAME_SIZE+1);
    memset(s_elemname2, '\0', _TYPE_NAME_SIZE+1);
    memset(s_prefix1, '\0', _TYPE_NAME_SIZE+1);
    memset(s_prefix2, '\0', _TYPE_NAME_SIZE+1);
    strncpy(s_elemname1, s_typename1, _TYPE_NAME_SIZE);
    strncpy(s_elemname2, s_typename2, _TYPE_NAME_SIZE);

    do{
        pc_leftbracket1 = strchr(s_elemname1, '<');
        pc_comma1 = strchr(s_elemname1, ',');
        pc_rightbracket1 = strchr(s_elemname1, '>');
        pc_leftbracket2 = strchr(s_elemname2, '<');
        pc_comma2 = strchr(s_elemname2, ',');
        pc_rightbracket2 = strchr(s_elemname2, '>');

        if(pc_leftbracket1 != NULL)
        {
            if(pc_comma1 != NULL)
            {
                if(pc_rightbracket1 != NULL)
                {
                    pc_index1 = pc_leftbracket1 - s_elemname1 < pc_comma1 - s_elemname1 ?
                                pc_leftbracket1 - s_elemname1 < pc_rightbracket1 - s_elemname1 ?
                                pc_leftbracket1 : pc_rightbracket1 :
                                pc_comma1 - s_elemname1 < pc_rightbracket1 - s_elemname1 ?
                                pc_comma1 : pc_rightbracket1;
                }
                else
                {
                    pc_index1 = pc_leftbracket1 - s_elemname1 < pc_comma1 - s_elemname1 ?
                                pc_leftbracket1 : pc_comma1;
                }
            }
            else
            {
                if(pc_rightbracket1 != NULL)
                {
                    pc_index1 = pc_leftbracket1 - s_elemname1 < pc_rightbracket1 - s_elemname1 ?
                                pc_leftbracket1 : pc_rightbracket1;
                }
                else
                {
                    pc_index1 = pc_leftbracket1;
                }
            }
        }
        else
        {
            if(pc_comma1 != NULL)
            {
                if(pc_rightbracket1 != NULL)
                {
                    pc_index1 = pc_comma1 - s_elemname1 < pc_rightbracket1 - s_elemname1 ?
                                pc_comma1 : pc_rightbracket1;
                }
                else
                {
                    pc_index1 = pc_comma1;
                }
            }
            else
            {
                pc_index1 = pc_rightbracket1;
            }
        }

        if(pc_leftbracket2 != NULL)
        {
            if(pc_comma2 != NULL)
            {
                if(pc_rightbracket2 != NULL)
                {
                    pc_index2 = pc_leftbracket2 - s_elemname2 < pc_comma2 - s_elemname2 ?
                                pc_leftbracket2 - s_elemname2 < pc_rightbracket2 - s_elemname2 ?
                                pc_leftbracket2 : pc_rightbracket2 :
                                pc_comma2 - s_elemname2 < pc_rightbracket2 - s_elemname2 ?
                                pc_comma2 : pc_rightbracket2;
                }
                else
                {
                    pc_index2 = pc_leftbracket2 - s_elemname2 < pc_comma2 - s_elemname2 ?
                                pc_leftbracket2 : pc_comma2;
                }
            }
            else
            {
                if(pc_rightbracket2 != NULL)
                {
                    pc_index2 = pc_leftbracket2 - s_elemname2 < pc_rightbracket2 - s_elemname2 ?
                                pc_leftbracket2 : pc_rightbracket2;
                }
                else
                {
                    pc_index2 = pc_leftbracket2;
                }
            }
        }
        else
        {
            if(pc_comma2 != NULL)
            {
                if(pc_rightbracket2 != NULL)
                {
                    pc_index2 = pc_comma2 - s_elemname2 < pc_rightbracket2 - s_elemname2 ?
                                pc_comma2 : pc_rightbracket2;
                }
                else
                {
                    pc_index2 = pc_comma2;
                }
            }
            else
            {
                pc_index2 = pc_rightbracket2;
            }
        }

        if(pc_index1 != NULL && pc_index2 != NULL)
        {
            memset(s_prefix1, '\0', _TYPE_NAME_SIZE+1);
            memset(s_prefix2, '\0', _TYPE_NAME_SIZE+1);
            strncpy(s_prefix1, s_elemname1, pc_index1 - s_elemname1);
            strncpy(s_prefix2, s_elemname2, pc_index2 - s_elemname2);

            if(_type_is_registered(s_prefix1) != _type_is_registered(s_prefix2))
            {
                return false;
            }

            memset(s_prefix1, '\0', _TYPE_NAME_SIZE+1);
            memset(s_prefix2, '\0', _TYPE_NAME_SIZE+1);
            strncpy(s_prefix1, pc_index1+1, _TYPE_NAME_SIZE);
            strncpy(s_prefix2, pc_index2+1, _TYPE_NAME_SIZE);
            memset(s_elemname1, '\0', _TYPE_NAME_SIZE+1);
            memset(s_elemname2, '\0', _TYPE_NAME_SIZE+1);
            strncpy(s_elemname1, s_prefix1, _TYPE_NAME_SIZE);
            strncpy(s_elemname2, s_prefix2, _TYPE_NAME_SIZE);
        }
        else
        {
            assert(pc_index1 == NULL && pc_index2 == NULL);
            if(_type_is_registered(s_elemname1) != _type_is_registered(s_elemname2))
            {
                return false;
            }
        }
    }while((pc_leftbracket1 != NULL || pc_comma1 != NULL || pc_rightbracket1 != NULL) &&
           (pc_leftbracket2 != NULL || pc_comma2 != NULL || pc_rightbracket2 != NULL));
    assert(pc_leftbracket1 == NULL && pc_comma1 == NULL && pc_rightbracket1 == NULL &&
           pc_leftbracket2 == NULL && pc_comma2 == NULL && pc_rightbracket2 == NULL);

    return true;
}

void _type_get_elem_typename(const char* s_typename, char* s_elemtypename)
{
    char* pc_left = NULL;   /* left bracket position */
    char* pc_right = NULL;  /* right bracket position */

    assert(s_typename != NULL && s_elemtypename != NULL);

    memset(s_elemtypename, '\0', _TYPE_NAME_SIZE+1);
    /* e.g. "vector_t<map_t<int,long>>" */
    pc_left = strchr(s_typename, '<');
    pc_right = strrchr(s_typename, '>');
    assert(pc_left != NULL && pc_right != NULL && pc_left < pc_right &&
           pc_right == s_typename + strlen(s_typename) - 1);

    strncpy(s_elemtypename, pc_left + 1, pc_right - pc_left - 1);
}

void _type_get_varg_value(_typeinfo_t* pt_typeinfo, va_list val_elemlist, void* pv_output)
{
    assert(pt_typeinfo != NULL && pt_typeinfo->_pt_type != NULL);
    assert(pv_output != NULL);

    /*
     * Note: the va_arg align at byte doundary for char, short and float type,
     * so those type, which are char, short and float, can't be used in va_arg function.
     */
    /* char and shigned char */
    if(strncmp(pt_typeinfo->_pt_type->_sz_typename, _CHAR_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(char));
        *(char*)pv_output = (char)va_arg(val_elemlist, int);
    }
    /* unsigned char */
    else if(strncmp(pt_typeinfo->_pt_type->_sz_typename, _UNSIGNED_CHAR_TYPE,
        _TYPE_NAME_SIZE) == 0)
    {
        assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(unsigned char));
        *(unsigned char*)pv_output = (unsigned char)va_arg(val_elemlist, int);
    }
    /* short, short int, signed short, signed short int */
    else if(strncmp(pt_typeinfo->_pt_type->_sz_typename, _SHORT_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(short));
        *(short*)pv_output = (short)va_arg(val_elemlist, int);
    }
    /* unsigned short, unsigned short int */
    else if(strncmp(pt_typeinfo->_pt_type->_sz_typename, _UNSIGNED_SHORT_TYPE,
        _TYPE_NAME_SIZE) == 0)
    {
        assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(unsigned short));
        *(unsigned short*)pv_output = (unsigned short)va_arg(val_elemlist, int);
    }
    /* int, signed, signed int */
    else if(strncmp(pt_typeinfo->_pt_type->_sz_typename, _INT_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(int));
        *(int*)pv_output = va_arg(val_elemlist, int);
    }
    /* unsigned int, unsigned */
    else if(strncmp(pt_typeinfo->_pt_type->_sz_typename, _UNSIGNED_INT_TYPE,
        _TYPE_NAME_SIZE) == 0)
    {
        assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(unsigned int));
        *(unsigned int*)pv_output = va_arg(val_elemlist, unsigned int);
    }
    /* long, long int, signed long, signed long int */
    else if(strncmp(pt_typeinfo->_pt_type->_sz_typename, _LONG_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(long));
        *(long*)pv_output = va_arg(val_elemlist, long);
    }
    /* unsigned long, unsigned long int */
    else if(strncmp(pt_typeinfo->_pt_type->_sz_typename, _UNSIGNED_LONG_TYPE,
        _TYPE_NAME_SIZE) == 0)
    {
        assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(unsigned long));
        *(unsigned long*)pv_output = va_arg(val_elemlist, unsigned long);
    }
    /* float */
    else if(strncmp(pt_typeinfo->_pt_type->_sz_typename, _FLOAT_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(float));
        *(float*)pv_output = (float)va_arg(val_elemlist, double);
    }
    /* double */
    else if(strncmp(pt_typeinfo->_pt_type->_sz_typename, _DOUBLE_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(double));
        *(double*)pv_output = va_arg(val_elemlist, double);
    }
    /* long double */
    else if(strncmp(pt_typeinfo->_pt_type->_sz_typename, _LONG_DOUBLE_TYPE,
        _TYPE_NAME_SIZE) == 0)
    {
        assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(long double));
        *(long double*)pv_output = va_arg(val_elemlist, long double);
    }
    /* bool_t */
    else if(strncmp(pt_typeinfo->_pt_type->_sz_typename, _BOOL_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(bool_t));
        *(bool_t*)pv_output = va_arg(val_elemlist, int);
    }
    /* char* */
    else if(strncmp(pt_typeinfo->_pt_type->_sz_typename, _C_STRING_TYPE,
        _TYPE_NAME_SIZE) == 0)
    {
        assert(pt_typeinfo->_pt_type->_t_typesize == sizeof(string_t));
        char* s_str = va_arg(val_elemlist, char*);
        string_assign_cstr((string_t*)pv_output, s_str);
    }
    /*
     * other type include cstl built in type and user define type passed type pointer.
     */
    else
    {
        /* the pv_output must be initialized */
        bool_t t_result = pt_typeinfo->_pt_type->_t_typesize;
        void*  pv_elem = va_arg(val_elemlist, void*);
        (*pt_typeinfo->_pt_type->_t_typecopy)(pv_output, pv_elem, &t_result);
        assert(t_result);
    }

    va_end(val_elemlist);
}

/* default copy, less, and destroy function */
void _type_init_default(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    memset((void*)cpv_input, 0x00, *(size_t*)pv_output);
    *(bool_t*)pv_output = true;
}
void _type_copy_default(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    memcpy((void*)cpv_first, cpv_second, *(size_t*)pv_output);
    *(size_t*)pv_output = true;
}
void _type_less_default(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(size_t*)pv_output = memcmp(cpv_first, cpv_second, *(size_t*)pv_output) == 0 ?
                          true : false;
}
void _type_destroy_default(const void* cpv_input, void* pv_output)
{
    void* pv_avoidwarning = NULL;
    assert(cpv_input != NULL && pv_output != NULL);
    pv_avoidwarning = (void*)cpv_input;
    *(bool_t*)pv_output = true;
}

static _type_t* _type_is_registered(const char* s_typename)
{
    _type_t*     pt_registered = NULL;
    _typenode_t* pt_node = NULL;

    if(strlen(s_typename) > _TYPE_NAME_SIZE)
    {
        return NULL;
    }

    /* get the registered type pointer */
    pt_node = _gt_typeregister._apt_bucket[_type_hash(s_typename)];
    if(pt_node != NULL)
    {
        while(pt_node != NULL)
        {
            if(strncmp(s_typename, pt_node->_sz_typename, _TYPE_NAME_SIZE) == 0)
            {
                pt_registered = pt_node->_pt_type;
                assert(pt_registered != NULL);
                break;
            }
            else
            {
                pt_node = pt_node->_pt_next;
            }
        }
    }

    return pt_registered;
}

static size_t _type_hash(const char* s_typename)
{
    size_t t_namesum = 0;
    size_t t_namelen = strlen(s_typename);
    size_t t_i = 0;

    for(t_i = 0; t_i < t_namelen; ++t_i)
    {
        t_namesum += (size_t)s_typename[t_i];
    }

    return t_namesum % _TYPE_REGISTER_BUCKET_COUNT;
}

static _typestyle_t _type_get_style(const char* s_typename, char* s_formalname)
{
    /*
     * this parser algorithm is associated with BNF in cstl.bnf that is issured by
     * activesys.cublog.cn
     */
    char   s_tokentext[_TYPE_NAME_SIZE + 1];
    char   s_userdefine[_TYPE_NAME_SIZE + 1];
    _typestyle_t t_style = _TYPE_INVALID;

    if(strlen(s_typename) > _TYPE_NAME_SIZE)
    {
        return _TYPE_INVALID;
    }

    memset(s_formalname, '\0', _TYPE_NAME_SIZE+1);
    memset(s_tokentext, '\0', _TYPE_NAME_SIZE+1);
    memset(s_userdefine, '\0', _TYPE_NAME_SIZE+1);

    /* initialize the type analysis */
    memset(_gt_typeanalysis._sz_typename, '\0', _TYPE_NAME_SIZE+1);
    memset(_gt_typeanalysis._sz_tokentext, '\0', _TYPE_NAME_SIZE+1);
    _gt_typeanalysis._t_index = 0;
    _gt_typeanalysis._t_token = _TOKEN_INVALID;
    strncpy(_gt_typeanalysis._sz_typename, s_typename, _TYPE_NAME_SIZE);

    /* TYPE_DESCRIPT -> C_BUILTIN | USER_DEFINE | CSTL_BUILTIN */
    _type_get_token();
    switch(_gt_typeanalysis._t_token)
    {
    /* TYPE_DESCRIPT -> C_BUILTIN */
    case _TOKEN_KEY_CHAR:
    case _TOKEN_KEY_SHORT:
    case _TOKEN_KEY_INT:
    case _TOKEN_KEY_LONG:
    case _TOKEN_KEY_FLOAT:
    case _TOKEN_KEY_DOUBLE:
    case _TOKEN_KEY_SIGNED:
    case _TOKEN_KEY_UNSIGNED:
    case _TOKEN_KEY_CHAR_POINTER:
    case _TOKEN_KEY_BOOL:
        t_style = _type_parse_c_builtin(s_formalname) ? _TYPE_C_BUILTIN : _TYPE_INVALID;
        break;
    /* TYPE_DESCRIPT -> USER_DEFINE */
    case _TOKEN_KEY_STRUCT:
    case _TOKEN_KEY_ENUM:
    case _TOKEN_KEY_UNION:
    case _TOKEN_IDENTIFIER:
        if(_type_parse_user_define(s_userdefine))
        {
            if(_type_is_registered(s_userdefine) != NULL)
            {
                t_style = _TYPE_USER_DEFINE;
            }
            else
            {
                t_style = _TYPE_INVALID;
            }
            strncat(s_formalname, s_userdefine, _TYPE_NAME_SIZE);
        }
        else
        {
            t_style = _TYPE_INVALID;
        }
        break;
    /* TYPE_DESCRIPT -> CSTL_BUILTIN */
    case _TOKEN_KEY_VECTOR:
    case _TOKEN_KEY_LIST:
    case _TOKEN_KEY_SLIST:
    case _TOKEN_KEY_DEQUE:
    case _TOKEN_KEY_STACK:
    case _TOKEN_KEY_QUEUE:
    case _TOKEN_KEY_PRIORITY_QUEUE:
    case _TOKEN_KEY_SET:
    case _TOKEN_KEY_MAP:
    case _TOKEN_KEY_MULTISET:
    case _TOKEN_KEY_MULTIMAP:
    case _TOKEN_KEY_HASH_SET:
    case _TOKEN_KEY_HASH_MAP:
    case _TOKEN_KEY_HASH_MULTISET:
    case _TOKEN_KEY_HASH_MULTIMAP:
    case _TOKEN_KEY_PAIR:
    case _TOKEN_KEY_STRING:
    case _TOKEN_KEY_ITERATOR:
    case _TOKEN_KEY_VECTOR_ITERATOR:
    case _TOKEN_KEY_LIST_ITERATOR:
    case _TOKEN_KEY_SLIST_ITERATOR:
    case _TOKEN_KEY_DEQUE_ITERATOR:
    case _TOKEN_KEY_SET_ITERATOR:
    case _TOKEN_KEY_MAP_ITERATOR:
    case _TOKEN_KEY_MULTISET_ITERATOR:
    case _TOKEN_KEY_MULTIMAP_ITERATOR:
    case _TOKEN_KEY_HASH_SET_ITERATOR:
    case _TOKEN_KEY_HASH_MAP_ITERATOR:
    case _TOKEN_KEY_HASH_MULTISET_ITERATOR:
    case _TOKEN_KEY_HASH_MULTIMAP_ITERATOR:
    case _TOKEN_KEY_STRING_ITERATOR:
    case _TOKEN_KEY_INPUT_ITERATOR:
    case _TOKEN_KEY_OUTPUT_ITERATOR:
    case _TOKEN_KEY_FORWARD_ITERATOR:
    case _TOKEN_KEY_BIDIRECTIONAL_ITERATOR:
    case _TOKEN_KEY_RANDOM_ACCESS_ITERATOR:
        t_style = _type_parse_cstl_builtin(s_formalname) ? _TYPE_CSTL_BUILTIN : _TYPE_INVALID;
        break;
    default:
        t_style = _TYPE_INVALID;
        break;
    }

    _type_get_token();
    return _gt_typeanalysis._t_token == _TOKEN_END_OF_INPUT ? t_style : _TYPE_INVALID;
}

static bool_t _type_parse_type_descript(char* s_formalname)
{
    char   s_userdefine[_TYPE_NAME_SIZE + 1];

    memset(s_userdefine, '\0', _TYPE_NAME_SIZE+1);

    /* TYPE_DESCRIPT -> C_BUILTIN | USER_DEFINE | CSTL_BUILTIN */
    switch(_gt_typeanalysis._t_token)
    {
    /* TYPE_DESCRIPT -> C_BUILTIN */
    case _TOKEN_KEY_CHAR:
    case _TOKEN_KEY_SHORT:
    case _TOKEN_KEY_INT:
    case _TOKEN_KEY_LONG:
    case _TOKEN_KEY_FLOAT:
    case _TOKEN_KEY_DOUBLE:
    case _TOKEN_KEY_SIGNED:
    case _TOKEN_KEY_UNSIGNED:
    case _TOKEN_KEY_CHAR_POINTER:
    case _TOKEN_KEY_BOOL:
        return _type_parse_c_builtin(s_formalname);
        break;
    /* TYPE_DESCRIPT -> USER_DEFINE */
    case _TOKEN_KEY_STRUCT:
    case _TOKEN_KEY_ENUM:
    case _TOKEN_KEY_UNION:
    case _TOKEN_IDENTIFIER:
        if(_type_parse_user_define(s_userdefine))
        {
            strncat(s_formalname, s_userdefine, _TYPE_NAME_SIZE);
            return _type_is_registered(s_userdefine) != NULL ? true : false;
        }
        else
        {
            return false;
        }
        break;
    /* TYPE_DESCRIPT -> CSTL_BUILTIN */
    case _TOKEN_KEY_VECTOR:
    case _TOKEN_KEY_LIST:
    case _TOKEN_KEY_SLIST:
    case _TOKEN_KEY_DEQUE:
    case _TOKEN_KEY_STACK:
    case _TOKEN_KEY_QUEUE:
    case _TOKEN_KEY_PRIORITY_QUEUE:
    case _TOKEN_KEY_SET:
    case _TOKEN_KEY_MAP:
    case _TOKEN_KEY_MULTISET:
    case _TOKEN_KEY_MULTIMAP:
    case _TOKEN_KEY_HASH_SET:
    case _TOKEN_KEY_HASH_MAP:
    case _TOKEN_KEY_HASH_MULTISET:
    case _TOKEN_KEY_HASH_MULTIMAP:
    case _TOKEN_KEY_PAIR:
    case _TOKEN_KEY_STRING:
    case _TOKEN_KEY_ITERATOR:
    case _TOKEN_KEY_VECTOR_ITERATOR:
    case _TOKEN_KEY_LIST_ITERATOR:
    case _TOKEN_KEY_SLIST_ITERATOR:
    case _TOKEN_KEY_DEQUE_ITERATOR:
    case _TOKEN_KEY_SET_ITERATOR:
    case _TOKEN_KEY_MAP_ITERATOR:
    case _TOKEN_KEY_MULTISET_ITERATOR:
    case _TOKEN_KEY_MULTIMAP_ITERATOR:
    case _TOKEN_KEY_HASH_SET_ITERATOR:
    case _TOKEN_KEY_HASH_MAP_ITERATOR:
    case _TOKEN_KEY_HASH_MULTISET_ITERATOR:
    case _TOKEN_KEY_HASH_MULTIMAP_ITERATOR:
    case _TOKEN_KEY_STRING_ITERATOR:
    case _TOKEN_KEY_INPUT_ITERATOR:
    case _TOKEN_KEY_OUTPUT_ITERATOR:
    case _TOKEN_KEY_FORWARD_ITERATOR:
    case _TOKEN_KEY_BIDIRECTIONAL_ITERATOR:
    case _TOKEN_KEY_RANDOM_ACCESS_ITERATOR:
        return _type_parse_cstl_builtin(s_formalname);
        break;
    default:
        return false;
        break;
    }
}

static bool_t _type_parse_cstl_builtin(char* s_formalname)
{
    /* CSTL_BUILTIN -> SEQUENCE | RELATION | string_t | ITERATOR */
    switch(_gt_typeanalysis._t_token)
    {
    /* CSTL_BUILTIN -> SEQUENCE */
    case _TOKEN_KEY_VECTOR:
    case _TOKEN_KEY_LIST:
    case _TOKEN_KEY_SLIST:
    case _TOKEN_KEY_DEQUE:
    case _TOKEN_KEY_STACK:
    case _TOKEN_KEY_QUEUE:
    case _TOKEN_KEY_PRIORITY_QUEUE:
    case _TOKEN_KEY_SET:
    case _TOKEN_KEY_MULTISET:
    case _TOKEN_KEY_HASH_SET:
    case _TOKEN_KEY_HASH_MULTISET:
        return _type_parse_sequence(s_formalname);
        break;
    /* CSTL_BUILTIN -> RELATION */
    case _TOKEN_KEY_MAP:
    case _TOKEN_KEY_MULTIMAP:
    case _TOKEN_KEY_HASH_MAP:
    case _TOKEN_KEY_HASH_MULTIMAP:
    case _TOKEN_KEY_PAIR:
        return _type_parse_relation(s_formalname);
        break;
    /* CSTL_BUILTIN -> string_t */
    case _TOKEN_KEY_STRING:
        _TOKEN_MATCH(_TOKEN_TEXT_STRING, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_ITERATOR:
    case _TOKEN_KEY_VECTOR_ITERATOR:
    case _TOKEN_KEY_LIST_ITERATOR:
    case _TOKEN_KEY_SLIST_ITERATOR:
    case _TOKEN_KEY_DEQUE_ITERATOR:
    case _TOKEN_KEY_SET_ITERATOR:
    case _TOKEN_KEY_MAP_ITERATOR:
    case _TOKEN_KEY_MULTISET_ITERATOR:
    case _TOKEN_KEY_MULTIMAP_ITERATOR:
    case _TOKEN_KEY_HASH_SET_ITERATOR:
    case _TOKEN_KEY_HASH_MAP_ITERATOR:
    case _TOKEN_KEY_HASH_MULTISET_ITERATOR:
    case _TOKEN_KEY_HASH_MULTIMAP_ITERATOR:
    case _TOKEN_KEY_STRING_ITERATOR:
    case _TOKEN_KEY_INPUT_ITERATOR:
    case _TOKEN_KEY_OUTPUT_ITERATOR:
    case _TOKEN_KEY_FORWARD_ITERATOR:
    case _TOKEN_KEY_BIDIRECTIONAL_ITERATOR:
    case _TOKEN_KEY_RANDOM_ACCESS_ITERATOR:
        return _type_parse_iterator(s_formalname);
        break;
    default:
        return false;
        break;
    }
}

static bool_t _type_parse_iterator(char* s_formalname)
{
    switch(_gt_typeanalysis._t_token)
    {
    case _TOKEN_KEY_ITERATOR:
        _TOKEN_MATCH(_TOKEN_TEXT_ITERATOR, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_VECTOR_ITERATOR:
        _TOKEN_MATCH(_TOKEN_TEXT_VECTOR_ITERATOR, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_LIST_ITERATOR:
        _TOKEN_MATCH(_TOKEN_TEXT_LIST_ITERATOR, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_SLIST_ITERATOR:
        _TOKEN_MATCH(_TOKEN_TEXT_SLIST_ITERATOR, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_DEQUE_ITERATOR:
        _TOKEN_MATCH(_TOKEN_TEXT_DEQUE_ITERATOR, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_SET_ITERATOR:
        _TOKEN_MATCH(_TOKEN_TEXT_SET_ITERATOR, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_MAP_ITERATOR:
        _TOKEN_MATCH(_TOKEN_TEXT_MAP_ITERATOR, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_MULTISET_ITERATOR:
        _TOKEN_MATCH(_TOKEN_TEXT_MULTISET_ITERATOR, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_MULTIMAP_ITERATOR:
        _TOKEN_MATCH(_TOKEN_TEXT_MULTIMAP_ITERATOR, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_HASH_SET_ITERATOR:
        _TOKEN_MATCH(_TOKEN_TEXT_HASH_SET_ITERATOR, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_HASH_MAP_ITERATOR:
        _TOKEN_MATCH(_TOKEN_TEXT_HASH_MAP_ITERATOR, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_HASH_MULTISET_ITERATOR:
        _TOKEN_MATCH(_TOKEN_TEXT_HASH_MULTISET_ITERATOR, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_HASH_MULTIMAP_ITERATOR:
        _TOKEN_MATCH(_TOKEN_TEXT_HASH_MULTIMAP_ITERATOR, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_STRING_ITERATOR:
        _TOKEN_MATCH(_TOKEN_TEXT_STRING_ITERATOR, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_INPUT_ITERATOR:
        _TOKEN_MATCH(_TOKEN_TEXT_INPUT_ITERATOR, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_OUTPUT_ITERATOR:
        _TOKEN_MATCH(_TOKEN_TEXT_OUTPUT_ITERATOR, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_FORWARD_ITERATOR:
        _TOKEN_MATCH(_TOKEN_TEXT_FORWARD_ITERATOR, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_BIDIRECTIONAL_ITERATOR:
        _TOKEN_MATCH(_TOKEN_TEXT_BIDIRECTIONAL_ITERATOR, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_RANDOM_ACCESS_ITERATOR:
        _TOKEN_MATCH(_TOKEN_TEXT_RANDOM_ACCESS_ITERATOR, s_formalname);
        return true;
        break;
    default:
        return false;
        break;
    }
}

static bool_t _type_parse_relation(char* s_formalname)
{
    /* RELATION -> RELATION_NAME < TYPE_DESCRIPT, TYPE_DESCRIPT > */
    if(_type_parse_relation_name(s_formalname))
    {
        /* < */
        _type_get_token();
        if(_gt_typeanalysis._t_token != _TOKEN_SIGN_LEFT_BRACKET)
        {
            return false;
        }
        _TOKEN_MATCH(_TOKEN_TEXT_LEFT_BRACKET, s_formalname);
        /* TYPE_DESCRIPT */
        _type_get_token();
        if(!_type_parse_type_descript(s_formalname))
        {
            return false;
        }
        /* , */
        _type_get_token();
        if(_gt_typeanalysis._t_token != _TOKEN_SIGN_COMMA)
        {
            return false;
        }
        _TOKEN_MATCH(_TOKEN_TEXT_COMMA, s_formalname);
        /* TYPE_DESCRIPT */
        _type_get_token();
        if(!_type_parse_type_descript(s_formalname))
        {
            return false;
        }
        /* > */
        _type_get_token();
        if(_gt_typeanalysis._t_token != _TOKEN_SIGN_RIGHT_BRACKET)
        {
            return false;
        }
        _TOKEN_MATCH(_TOKEN_TEXT_RIGHT_BRACKET, s_formalname);
        return true;
    }
    else
    {
        return false;
    }
}

static bool_t _type_parse_relation_name(char* s_formalname)
{
    /*
     * RELATION_NAME -> map_t | multimap_t | hash_map_t | hash_multimap_t | pair_t
     */
    switch(_gt_typeanalysis._t_token)
    {
    case _TOKEN_KEY_MAP:
        _TOKEN_MATCH(_TOKEN_TEXT_MAP, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_MULTIMAP:
        _TOKEN_MATCH(_TOKEN_TEXT_MULTIMAP, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_HASH_MAP:
        _TOKEN_MATCH(_TOKEN_TEXT_HASH_MAP, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_HASH_MULTIMAP:
        _TOKEN_MATCH(_TOKEN_TEXT_HASH_MULTIMAP, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_PAIR:
        _TOKEN_MATCH(_TOKEN_TEXT_PAIR, s_formalname);
        return true;
        break;
    default:
        return false;
        break;
    }
}

static bool_t _type_parse_sequence(char* s_formalname)
{
    /* SEQUENCE -> SEQUENCE_NAME < TYPE_DESCRIPT > */
    if(_type_parse_sequence_name(s_formalname))
    {
        /* < */
        _type_get_token();
        if(_gt_typeanalysis._t_token != _TOKEN_SIGN_LEFT_BRACKET)
        {
            return false;
        }
        _TOKEN_MATCH(_TOKEN_TEXT_LEFT_BRACKET, s_formalname);
        /* TYPE_DESCRIPT */
        _type_get_token();
        if(!_type_parse_type_descript(s_formalname))
        {
            return false;
        }
        /* > */
        _type_get_token();
        if(_gt_typeanalysis._t_token != _TOKEN_SIGN_RIGHT_BRACKET)
        {
            return false;
        }
        _TOKEN_MATCH(_TOKEN_TEXT_RIGHT_BRACKET, s_formalname);
        return true;
    }
    else
    {
        return false;
    }
}

static bool_t _type_parse_sequence_name(char* s_formalname)
{
    /* 
     * SEQUENCE_NAME -> vector_t | list_t | slist_t | deque_t | stack_t | 
     *                  queue_t | priority_queue_t | set_t | multiset_t |
     *                  hash_set_t | hash_multiset_t
     */
    switch(_gt_typeanalysis._t_token)
    {
    case _TOKEN_KEY_VECTOR:
        _TOKEN_MATCH(_TOKEN_TEXT_VECTOR, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_LIST:
        _TOKEN_MATCH(_TOKEN_TEXT_LIST, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_SLIST:
        _TOKEN_MATCH(_TOKEN_TEXT_SLIST, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_DEQUE:
        _TOKEN_MATCH(_TOKEN_TEXT_DEQUE, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_STACK:
        _TOKEN_MATCH(_TOKEN_TEXT_STACK, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_QUEUE:
        _TOKEN_MATCH(_TOKEN_TEXT_QUEUE, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_PRIORITY_QUEUE:
        _TOKEN_MATCH(_TOKEN_TEXT_PRIORITY_QUEUE, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_SET:
        _TOKEN_MATCH(_TOKEN_TEXT_SET, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_MULTISET:
        _TOKEN_MATCH(_TOKEN_TEXT_MULTISET, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_HASH_SET:
        _TOKEN_MATCH(_TOKEN_TEXT_HASH_SET, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_HASH_MULTISET:
        _TOKEN_MATCH(_TOKEN_TEXT_HASH_MULTISET, s_formalname);
        return true;
        break;
    default:
        return false;
        break;
    }
}

static bool_t _type_parse_user_define(char* s_formalname)
{
    /* USER_DEFINE -> USER_DEFINE_TYPE {+' '}identifier | identifier */
    switch(_gt_typeanalysis._t_token)
    {
    /* USER_DEFINE -> USER_DEFINE_TYPE {+' '}identifier */
    case _TOKEN_KEY_STRUCT:
    case _TOKEN_KEY_ENUM:
    case _TOKEN_KEY_UNION:
        if(_type_parse_user_define_type(s_formalname))
        {
            _TOKEN_MATCH_SPACE(s_formalname);
            _type_get_token();
            if(_gt_typeanalysis._t_token != _TOKEN_IDENTIFIER)
            {
                return false;
            }
            else
            {
                _TOKEN_MATCH_IDENTIFIER(s_formalname);
                return true;
            }
        }
        else
        {
            return false;
        }
        break;
    /* USER_DEFINE -> identifier */
    case _TOKEN_IDENTIFIER:
        _TOKEN_MATCH_IDENTIFIER(s_formalname);
        return true;
        break;
    default:
        return false;
        break;
    }
}

static bool_t _type_parse_user_define_type(char* s_formalname)
{
    /* USER_DEFINE_TYPE -> struct | enum | union */
    switch(_gt_typeanalysis._t_token)
    {
    case _TOKEN_KEY_STRUCT:
        _TOKEN_MATCH(_TOKEN_TEXT_STRUCT, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_ENUM:
        _TOKEN_MATCH(_TOKEN_TEXT_ENUM, s_formalname);
        return true;
        break;
    case _TOKEN_KEY_UNION:
        _TOKEN_MATCH(_TOKEN_TEXT_UNION, s_formalname);
        return true;
        break;
    default:
        return false;
        break;
    }
}

static bool_t _type_parse_c_builtin(char* s_formalname)
{
    /* C_BUILTIN -> SIMPLE_BUILTIN | SIGNED_BUILTIN | UNSIGNED_BUILTIN */
    switch(_gt_typeanalysis._t_token)
    {
    /* C_BUILTIN -> SIMPLE_BUILTIN */
    case _TOKEN_KEY_CHAR:
    case _TOKEN_KEY_SHORT:
    case _TOKEN_KEY_INT:
    case _TOKEN_KEY_LONG:
    case _TOKEN_KEY_FLOAT:
    case _TOKEN_KEY_DOUBLE:
    case _TOKEN_KEY_CHAR_POINTER:
    case _TOKEN_KEY_BOOL:
        return _type_parse_simple_builtin(s_formalname);
        break;
    /* C_BUILTIN -> SIGNED_BUILTIN */
    case _TOKEN_KEY_SIGNED:
        return _type_parse_signed_builtin(s_formalname);
        break;
    /* C_BUILTIN -> UNSIGNED_BUILTIN */
    case _TOKEN_KEY_UNSIGNED:
        return _type_parse_unsigned_builtin(s_formalname);
        break;
    default:
        return false;
        break;
    }
}

static bool_t _type_parse_signed_builtin(char* s_formalname)
{
    /* SIGNED_BUILTIN -> signed COMPLEX_SUFFIX */
    switch(_gt_typeanalysis._t_token)
    {
    case _TOKEN_KEY_SIGNED:
        _TOKEN_MATCH(_TOKEN_TEXT_SIGNED, s_formalname);
        _type_get_token();
        return _type_parse_complex_suffix(s_formalname);
        break;
    default:
        return false;
        break;
    }
}

static bool_t _type_parse_unsigned_builtin(char* s_formalname)
{
    /* UNSIGNED_BUILTIN -> unsigned COMPLEX_SUFFIX */
    switch(_gt_typeanalysis._t_token)
    {
    case _TOKEN_KEY_UNSIGNED:
        _TOKEN_MATCH(_TOKEN_TEXT_UNSIGNED, s_formalname);
        _type_get_token();
        return _type_parse_complex_suffix(s_formalname);
        break;
    default:
        return false;
        break;
    }
}

static bool_t _type_parse_complex_suffix(char* s_formalname)
{
    char* pc_pointersign = NULL;
    /* 
     * COMPLEX_SUFFIX -> {+' '}char | {+' '}short COMMON_SUFFIX |
     *                   {+' '}int | {+' '}long COMMON_SUFFIX | $
     */
    switch(_gt_typeanalysis._t_token)
    {
    /* COMPLEX_SUFFIX -> {+' '}char */
    case _TOKEN_KEY_CHAR:
        _TOKEN_MATCH_SPACE(s_formalname);
        _TOKEN_MATCH(_TOKEN_TEXT_CHAR, s_formalname);
        return true;
        break;
    /* COMPLEX_SUFFIX -> {+' '}short COMMON_SUFFIX */
    case _TOKEN_KEY_SHORT:
        _TOKEN_MATCH_SPACE(s_formalname);
        _TOKEN_MATCH(_TOKEN_TEXT_SHORT, s_formalname);
        _type_get_token();
        return _type_parse_common_suffix(s_formalname);
        break;
    /* COMPLEX_SUFFIX -> {+' '}int */
    case _TOKEN_KEY_INT:
        _TOKEN_MATCH_SPACE(s_formalname);
        _TOKEN_MATCH(_TOKEN_TEXT_INT, s_formalname);
        return true;
        break;
    /* COMPLEX_SUFFIX -> {+' '}long COMMON_SUFFIX */
    case _TOKEN_KEY_LONG:
        _TOKEN_MATCH_SPACE(s_formalname);
        _TOKEN_MATCH(_TOKEN_TEXT_LONG, s_formalname);
        _type_get_token();
        return _type_parse_common_suffix(s_formalname);
        break;
    /* COMPLEX_SUFFIX -> $ */
    case _TOKEN_END_OF_INPUT:
    case _TOKEN_SIGN_RIGHT_BRACKET:
    case _TOKEN_SIGN_COMMA:
        _type_token_rollback();
        return true;
        break;
    /* COMPLEX_SUFFIX -> {+' '}char|short|int|long*... */
    case _TOKEN_IDENTIFIER:
        pc_pointersign = strchr(_gt_typeanalysis._sz_tokentext, '*');
        if(pc_pointersign == NULL)
        {/* not pointer type */
            return false;
        }
        if(strncmp(_gt_typeanalysis._sz_tokentext, "char",
            pc_pointersign-_gt_typeanalysis._sz_tokentext) != 0 &&
           strncmp(_gt_typeanalysis._sz_tokentext, "int",
            pc_pointersign-_gt_typeanalysis._sz_tokentext) != 0 &&
           strncmp(_gt_typeanalysis._sz_tokentext, "short",
            pc_pointersign-_gt_typeanalysis._sz_tokentext) != 0 &&
           strncmp(_gt_typeanalysis._sz_tokentext, "long",
            pc_pointersign-_gt_typeanalysis._sz_tokentext) != 0)
        {/* not pointer of char or int or short or long type */
            return false;
        }
        _TOKEN_MATCH_SPACE(s_formalname);
        _TOKEN_MATCH_IDENTIFIER(s_formalname);
        return true;
        break;
    default:
        return false;
        break;
    }
}

static bool_t _type_parse_simple_builtin(char* s_formalname)
{
    /* 
     * SIMPLE_BUILTIN -> char | short COMMON_SUFFIX | int | long SIMPLE_LONG_SUFFIX |
     *                   float | double | char* | bool_t
     */
    switch(_gt_typeanalysis._t_token)
    {
    /* SIMPLE_BUILTIN -> char */
    case _TOKEN_KEY_CHAR:
        _TOKEN_MATCH(_TOKEN_TEXT_CHAR, s_formalname);
        return true;
        break;
    /* SIMPLE_BUILTIN -> short COMMON_SUFFIX */
    case _TOKEN_KEY_SHORT:
        _TOKEN_MATCH(_TOKEN_TEXT_SHORT, s_formalname);
        _type_get_token();
        return _type_parse_common_suffix(s_formalname);
        break;
    /* SIMPLE_BUILTIN -> int */
    case _TOKEN_KEY_INT:
        _TOKEN_MATCH(_TOKEN_TEXT_INT, s_formalname);
        return true;
        break;
    /* SIMPLE_BUILTIN -> long SIMPLE_LONG_SUFFIX */
    case _TOKEN_KEY_LONG:
        _TOKEN_MATCH(_TOKEN_TEXT_LONG, s_formalname);
        _type_get_token();
        return _type_parse_simple_long_suffix(s_formalname);
        break;
    /* SIMPLE_BUILTIN -> float */
    case _TOKEN_KEY_FLOAT:
        _TOKEN_MATCH(_TOKEN_TEXT_FLOAT, s_formalname);
        return true;
        break;
    /* SIMPLE_BUILTIN -> double */
    case _TOKEN_KEY_DOUBLE:
        _TOKEN_MATCH(_TOKEN_TEXT_DOUBLE, s_formalname);
        return true;
        break;
    /* SIMPLE_BUILTIN -> char* */
    case _TOKEN_KEY_CHAR_POINTER:
        _TOKEN_MATCH(_TOKEN_TEXT_CHAR_POINTER, s_formalname);
        return true;
        break;
    /* SIMPLE_BUILTIN -> bool_t */
    case _TOKEN_KEY_BOOL:
        _TOKEN_MATCH(_TOKEN_TEXT_BOOL, s_formalname);
        return true;
        break;
    default:
        return false;
        break;
    }
}

static bool_t _type_parse_common_suffix(char* s_formalname)
{
    char* pc_pointersign = NULL;

    /* COMMON_SUFFIX -> {+' '}int | $ */
    switch(_gt_typeanalysis._t_token)
    {
    /* COMMON_SUFFIX -> {+' '}int */
    case _TOKEN_KEY_INT:
        _TOKEN_MATCH_SPACE(s_formalname);
        _TOKEN_MATCH(_TOKEN_TEXT_INT, s_formalname);
        return true;
        break;
    /* COMMON_SUFFIX -> $ */
    case _TOKEN_END_OF_INPUT:
    case _TOKEN_SIGN_RIGHT_BRACKET:
    case _TOKEN_SIGN_COMMA:
        _type_token_rollback();
        return true;
        break;
    /* COMMON_SUFFIX -> {+' '}int*... */
    case _TOKEN_IDENTIFIER:
        pc_pointersign = strchr(_gt_typeanalysis._sz_tokentext, '*');
        if(pc_pointersign == NULL)
        {/* not pointer type */
            return false;
        }
        if(strncmp(_gt_typeanalysis._sz_tokentext, "int",
            pc_pointersign-_gt_typeanalysis._sz_tokentext) != 0)
        {/* not the pointer of int type */
            return false;
        }
        _TOKEN_MATCH_SPACE(s_formalname);
        _TOKEN_MATCH_IDENTIFIER(s_formalname);
        return true;
        break;
    default:
        return false;
        break;
    }
}

static bool_t _type_parse_simple_long_suffix(char* s_formalname)
{
    char* pc_pointersign = NULL;

    /* SIMPLE_LONG_SUFFIX -> {+' '}double | COMMON_SUFFIX */
    switch(_gt_typeanalysis._t_token)
    {
    /* SIMPLE_LONG_SUFFIX -> {+' '}double */
    case _TOKEN_KEY_DOUBLE:
        _TOKEN_MATCH_SPACE(s_formalname);
        _TOKEN_MATCH(_TOKEN_TEXT_DOUBLE, s_formalname);
        return true;
        break;
    /* SIMPLE_LONG_SUFFIX -> COMMON_SUFFIX */
    case _TOKEN_KEY_INT:
    case _TOKEN_END_OF_INPUT:
    case _TOKEN_SIGN_RIGHT_BRACKET:
    case _TOKEN_SIGN_COMMA:
        return _type_parse_common_suffix(s_formalname);
        break;
    /* SIMPLE_LONG_SUFFIX -> {+' '}double*... */
    case _TOKEN_IDENTIFIER:
        pc_pointersign = strchr(_gt_typeanalysis._sz_tokentext, '*');
        if(pc_pointersign == NULL)
        {/* not pointer type */
            return false;
        }
        if(strncmp(_gt_typeanalysis._sz_tokentext, "double",
            pc_pointersign-_gt_typeanalysis._sz_tokentext) != 0)
        {/* not pointer of double type */
            return false;
        }
        _TOKEN_MATCH_SPACE(s_formalname);
        _TOKEN_MATCH_IDENTIFIER(s_formalname);
        return true;
        break;
    default:
        return false;
        break;
    }
}

static void _type_token_rollback(void)
{
    assert(_gt_typeanalysis._t_token == _TOKEN_END_OF_INPUT ||
           _gt_typeanalysis._t_token == _TOKEN_SIGN_COMMA ||
           _gt_typeanalysis._t_token == _TOKEN_SIGN_RIGHT_BRACKET);
    assert(_gt_typeanalysis._sz_typename[_gt_typeanalysis._t_index] == '\0' ||
           _gt_typeanalysis._sz_typename[_gt_typeanalysis._t_index-1] == ',' ||
           _gt_typeanalysis._sz_typename[_gt_typeanalysis._t_index-1] == '>');
    assert(strncmp(_gt_typeanalysis._sz_tokentext, "", _TYPE_NAME_SIZE) == 0 ||
           strncmp(_gt_typeanalysis._sz_tokentext, ",", _TYPE_NAME_SIZE) == 0 ||
           strncmp(_gt_typeanalysis._sz_tokentext, ">", _TYPE_NAME_SIZE) == 0);
    if(_gt_typeanalysis._sz_typename[_gt_typeanalysis._t_index] != '\0')
    {
        _gt_typeanalysis._t_index--;
    }
    _gt_typeanalysis._t_token = _TOKEN_ROLLBACK;
}

static void _type_get_token(void)
{
    /*
     * this lexical analysis algorithm is associated with 
     * lexical state machine in cstl.bnf that is issured by activesys.cublog.cn
     */
    size_t       t_tokentextindex = 0;
    _typelex_t   t_lexstate = _LEX_START;

    memset(_gt_typeanalysis._sz_tokentext, '\0', _TYPE_NAME_SIZE+1);

    while(t_lexstate != _LEX_ACCEPT)
    {
        switch(t_lexstate)
        {
        case _LEX_START:
            if(isalpha(_gt_typeanalysis._sz_typename[_gt_typeanalysis._t_index]) ||
               _gt_typeanalysis._sz_typename[_gt_typeanalysis._t_index] == '_') 
            {
                _gt_typeanalysis._sz_tokentext[t_tokentextindex++] =
                _gt_typeanalysis._sz_typename[_gt_typeanalysis._t_index++];
                t_lexstate = _LEX_IN_IDENTIFIER;
            }
            else if(_gt_typeanalysis._sz_typename[_gt_typeanalysis._t_index] == '<')
            {
                _gt_typeanalysis._sz_tokentext[t_tokentextindex++] =
                _gt_typeanalysis._sz_typename[_gt_typeanalysis._t_index++];
                _gt_typeanalysis._t_token = _TOKEN_SIGN_LEFT_BRACKET;
                t_lexstate = _LEX_ACCEPT;
            }
            else if(_gt_typeanalysis._sz_typename[_gt_typeanalysis._t_index] == '>')
            {
                _gt_typeanalysis._sz_tokentext[t_tokentextindex++] =
                _gt_typeanalysis._sz_typename[_gt_typeanalysis._t_index++];
                _gt_typeanalysis._t_token = _TOKEN_SIGN_RIGHT_BRACKET;
                t_lexstate = _LEX_ACCEPT;
            }
            else if(_gt_typeanalysis._sz_typename[_gt_typeanalysis._t_index] == ',')
            {
                _gt_typeanalysis._sz_tokentext[t_tokentextindex++] =
                _gt_typeanalysis._sz_typename[_gt_typeanalysis._t_index++];
                _gt_typeanalysis._t_token = _TOKEN_SIGN_COMMA;
                t_lexstate = _LEX_ACCEPT;
            }
            else if(isspace(_gt_typeanalysis._sz_typename[_gt_typeanalysis._t_index]))
            {
                _gt_typeanalysis._t_index++;
                t_lexstate = _LEX_START;
            }
            else if(_gt_typeanalysis._sz_typename[_gt_typeanalysis._t_index] == '\0')
            {
                _gt_typeanalysis._t_token =  _TOKEN_END_OF_INPUT;
                t_lexstate = _LEX_ACCEPT;
            }
            else
            {
                _gt_typeanalysis._t_token =  _TOKEN_INVALID;
                t_lexstate = _LEX_ACCEPT;
            }
            break;
        case _LEX_IN_IDENTIFIER:
            if(isalpha(_gt_typeanalysis._sz_typename[_gt_typeanalysis._t_index]) ||
               isdigit(_gt_typeanalysis._sz_typename[_gt_typeanalysis._t_index]) ||
               _gt_typeanalysis._sz_typename[_gt_typeanalysis._t_index] == '_')
            {
                _gt_typeanalysis._sz_tokentext[t_tokentextindex++] =
                _gt_typeanalysis._sz_typename[_gt_typeanalysis._t_index++];
                t_lexstate = _LEX_IN_IDENTIFIER;
            }
            else
            {
                _gt_typeanalysis._t_token = _TOKEN_IDENTIFIER;
                t_lexstate = _LEX_ACCEPT;
            }
            break;
        default:
            _gt_typeanalysis._t_token = _TOKEN_INVALID;
            t_lexstate = _LEX_ACCEPT;
            assert(false);
            break;
        }
    }

    /* if token is identifier then check is keyword */
    if(_gt_typeanalysis._t_token == _TOKEN_IDENTIFIER)
    {
        /* handle pointer type "type*", "type *", "type   *", "type  *  * * *" and so on */
        while(true)
        {
            if(_gt_typeanalysis._sz_typename[_gt_typeanalysis._t_index] == '*')
            {
                _gt_typeanalysis._sz_tokentext[t_tokentextindex++] =
                _gt_typeanalysis._sz_typename[_gt_typeanalysis._t_index++];
            }
            else if(_gt_typeanalysis._sz_typename[_gt_typeanalysis._t_index] == ' ')
            {
                _gt_typeanalysis._t_index++;
            }
            else
            {
                break;
            }
        }

        /* test c builtin */
        if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_CHAR, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_CHAR;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_SHORT, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_SHORT;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_INT, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_INT;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_LONG, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_LONG;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_DOUBLE, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_DOUBLE;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_FLOAT, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_FLOAT;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_SIGNED, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_SIGNED;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_UNSIGNED, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_UNSIGNED;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_CHAR_POINTER, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_CHAR_POINTER;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_BOOL, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_BOOL;
        }
        /* user define */
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_STRUCT, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_STRUCT;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_ENUM, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_ENUM;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_UNION, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_UNION;
        }
        /* cstl containers */
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_VECTOR, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_VECTOR;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_LIST, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_LIST;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_SLIST, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_SLIST;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_DEQUE, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_DEQUE;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_STACK, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_STACK;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_QUEUE, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_QUEUE;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_PRIORITY_QUEUE, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_PRIORITY_QUEUE;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_SET, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_SET;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_MAP, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_MAP;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_MULTISET, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_MULTISET;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_MULTIMAP, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_MULTIMAP;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_HASH_SET, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_HASH_SET;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_HASH_MAP, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_HASH_MAP;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_HASH_MULTISET, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_HASH_MULTISET;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_HASH_MULTIMAP, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_HASH_MULTIMAP;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_PAIR, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_PAIR;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_STRING, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_STRING;
        }
        /* cstl iterator */
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_ITERATOR, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_ITERATOR;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_VECTOR_ITERATOR, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_VECTOR_ITERATOR;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_LIST_ITERATOR, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_LIST_ITERATOR;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_SLIST_ITERATOR, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_SLIST_ITERATOR;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_DEQUE_ITERATOR, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_DEQUE_ITERATOR;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_SET_ITERATOR, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_SET_ITERATOR;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_MAP_ITERATOR, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_MAP_ITERATOR;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_MULTISET_ITERATOR, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_MULTISET_ITERATOR;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_MULTIMAP_ITERATOR, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_MULTIMAP_ITERATOR;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_HASH_SET_ITERATOR, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_HASH_SET_ITERATOR;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_HASH_MAP_ITERATOR, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_HASH_MAP_ITERATOR;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_HASH_MULTISET_ITERATOR, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_HASH_MULTISET_ITERATOR;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_HASH_MULTIMAP_ITERATOR, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_HASH_MULTIMAP_ITERATOR;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_STRING_ITERATOR, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_STRING_ITERATOR;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_INPUT_ITERATOR, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_INPUT_ITERATOR;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_OUTPUT_ITERATOR, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_OUTPUT_ITERATOR;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_FORWARD_ITERATOR, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_FORWARD_ITERATOR;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_BIDIRECTIONAL_ITERATOR, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_BIDIRECTIONAL_ITERATOR;
        }
        else if(strncmp(_gt_typeanalysis._sz_tokentext,
            _TOKEN_TEXT_RANDOM_ACCESS_ITERATOR, _TYPE_NAME_SIZE) == 0)
        {
            _gt_typeanalysis._t_token = _TOKEN_KEY_RANDOM_ACCESS_ITERATOR;
        }
        else
        {
            _gt_typeanalysis._t_token = _TOKEN_IDENTIFIER;
        }
    }
}

static void _type_init(void)
{
    size_t       t_i = 0;

    /* set register hash table */
    for(t_i = 0; t_i < _TYPE_REGISTER_BUCKET_COUNT; ++t_i)
    {
        _gt_typeregister._apt_bucket[t_i] = NULL;
    }
    /* init allocator */
    allocate_init(&_gt_typeregister._t_allocator);

    _type_register_c_builtin();
    _type_register_cstl_builtin();
    
    _gt_typeregister._t_isinit = true;
}

static void _type_register_c_builtin(void)
{
    _TYPE_REGISTER_BEGIN();

    /* register char type */
    _TYPE_REGISTER_TYPE(char, _CHAR_TYPE, char);
    _TYPE_REGISTER_TYPE_NODE(char, _CHAR_TYPE);
    _TYPE_REGISTER_TYPE_NODE(signed char, _SIGNED_CHAR_TYPE);
    /* register unsigned char */
    _TYPE_REGISTER_TYPE(unsigned char, _UNSIGNED_CHAR_TYPE, uchar);
    _TYPE_REGISTER_TYPE_NODE(unsigned char, _UNSIGNED_CHAR_TYPE);
    /* register short */
    _TYPE_REGISTER_TYPE(short, _SHORT_TYPE, short);
    _TYPE_REGISTER_TYPE_NODE(short, _SHORT_TYPE);
    _TYPE_REGISTER_TYPE_NODE(short int, _SHORT_INT_TYPE);
    _TYPE_REGISTER_TYPE_NODE(signed short, _SIGNED_SHORT_TYPE);
    _TYPE_REGISTER_TYPE_NODE(signed short int, _SIGNED_SHORT_INT_TYPE);
    /* register unsigned short */
    _TYPE_REGISTER_TYPE(unsigned short, _UNSIGNED_SHORT_TYPE, ushort);
    _TYPE_REGISTER_TYPE_NODE(unsigned short, _UNSIGNED_SHORT_TYPE);
    _TYPE_REGISTER_TYPE_NODE(unsigned short int, _UNSIGNED_SHORT_INT_TYPE);
    /* register int */
    _TYPE_REGISTER_TYPE(int, _INT_TYPE, int);
    _TYPE_REGISTER_TYPE_NODE(int, _INT_TYPE);
    _TYPE_REGISTER_TYPE_NODE(signed, _SIGNED_TYPE);
    _TYPE_REGISTER_TYPE_NODE(signed int, _SIGNED_INT_TYPE);
    /* register unsigned int */
    _TYPE_REGISTER_TYPE(unsigned int, _UNSIGNED_INT_TYPE, uint);
    _TYPE_REGISTER_TYPE_NODE(unsigned int, _UNSIGNED_INT_TYPE);
    _TYPE_REGISTER_TYPE_NODE(signed, _UNSIGNED_TYPE);
    /* register long */
    _TYPE_REGISTER_TYPE(long, _LONG_TYPE, long);
    _TYPE_REGISTER_TYPE_NODE(long, _LONG_TYPE);
    _TYPE_REGISTER_TYPE_NODE(long int, _LONG_INT_TYPE);
    _TYPE_REGISTER_TYPE_NODE(signed long, _SIGNED_LONG_TYPE);
    _TYPE_REGISTER_TYPE_NODE(signed long int, _SIGNED_LONG_INT_TYPE);
    /* register unsigned long */
    _TYPE_REGISTER_TYPE(unsigned long, _UNSIGNED_LONG_TYPE, ulong);
    _TYPE_REGISTER_TYPE_NODE(unsigned long, _UNSIGNED_LONG_TYPE);
    _TYPE_REGISTER_TYPE_NODE(unsigned long int, _UNSIGNED_LONG_INT_TYPE);
    /* register float */
    _TYPE_REGISTER_TYPE(float, _FLOAT_TYPE, float);
    _TYPE_REGISTER_TYPE_NODE(float, _FLOAT_TYPE);
    /* register double */
    _TYPE_REGISTER_TYPE(double, _DOUBLE_TYPE, double);
    _TYPE_REGISTER_TYPE_NODE(double, _DOUBLE_TYPE);
    /* register long double */
    _TYPE_REGISTER_TYPE(long double, _LONG_DOUBLE_TYPE, long_double);
    _TYPE_REGISTER_TYPE_NODE(long double, _LONG_DOUBLE_TYPE);
    /* register bool_t */
    _TYPE_REGISTER_TYPE(bool_t, _BOOL_TYPE, bool);
    _TYPE_REGISTER_TYPE_NODE(bool_t, _BOOL_TYPE);
     /* register char* */
    _TYPE_REGISTER_TYPE(string_t, _C_STRING_TYPE, cstr);
    _TYPE_REGISTER_TYPE_NODE(string_t, _C_STRING_TYPE);

    _TYPE_REGISTER_END();
}

static void _type_register_cstl_builtin(void)
{
    _TYPE_REGISTER_BEGIN();

    /* register vector_t */
    _TYPE_REGISTER_TYPE(vector_t, _VECTOR_TYPE, vector);
    _TYPE_REGISTER_TYPE_NODE(vector_t, _VECTOR_TYPE);
    /* register list_t */
    _TYPE_REGISTER_TYPE(list_t, _LIST_TYPE, list);
    _TYPE_REGISTER_TYPE_NODE(list_t, _LIST_TYPE);
    /* register slist_t */
    _TYPE_REGISTER_TYPE(slist_t, _SLIST_TYPE, slist);
    _TYPE_REGISTER_TYPE_NODE(slist_t, _SLIST_TYPE);
    /* register deque_t */
    _TYPE_REGISTER_TYPE(deque_t, _DEQUE_TYPE, deque);
    _TYPE_REGISTER_TYPE_NODE(deque_t, _DEQUE_TYPE);
    /* register stack_t */
    _TYPE_REGISTER_TYPE(stack_t, _STACK_TYPE, stack);
    _TYPE_REGISTER_TYPE_NODE(stack_t, _STACK_TYPE);
    /* register queue_t */
    _TYPE_REGISTER_TYPE(queue_t, _QUEUE_TYPE, queue);
    _TYPE_REGISTER_TYPE_NODE(queue_t, _QUEUE_TYPE);
    /* register priority_queue_t */
    _TYPE_REGISTER_TYPE(priority_queue_t, _PRIORITY_QUEUE_TYPE, priority_queue);
    _TYPE_REGISTER_TYPE_NODE(priority_queue_t, _PRIORITY_QUEUE_TYPE);
    /* register set_t */
    _TYPE_REGISTER_TYPE(set_t, _SET_TYPE, set);
    _TYPE_REGISTER_TYPE_NODE(set_t, _SET_TYPE);
    /* register map_t */
    _TYPE_REGISTER_TYPE(map_t, _MAP_TYPE, map);
    _TYPE_REGISTER_TYPE_NODE(map_t, _MAP_TYPE);
    /* register multiset_t */
    _TYPE_REGISTER_TYPE(multiset_t, _MULTISET_TYPE, multiset);
    _TYPE_REGISTER_TYPE_NODE(multiset_t, _MULTISET_TYPE);
    /* register multimap_t */
    _TYPE_REGISTER_TYPE(multimap_t, _MULTIMAP_TYPE, multimap);
    _TYPE_REGISTER_TYPE_NODE(multimap_t, _MULTIMAP_TYPE);
    /* register hash_set_t */
    _TYPE_REGISTER_TYPE(hash_set_t, _HASH_SET_TYPE, hash_set);
    _TYPE_REGISTER_TYPE_NODE(hash_set_t, _HASH_SET_TYPE);
    /* register hash_map_t */
    _TYPE_REGISTER_TYPE(hash_map_t, _HASH_MAP_TYPE, hash_map);
    _TYPE_REGISTER_TYPE_NODE(hash_map_t, _HASH_MAP_TYPE);
    /* register hash_multiset_t */
    _TYPE_REGISTER_TYPE(hash_multiset_t, _HASH_MULTISET_TYPE, hash_multiset);
    _TYPE_REGISTER_TYPE_NODE(hash_multiset_t, _HASH_MULTISET_TYPE);
    /* register hash_multimap_t */
    _TYPE_REGISTER_TYPE(hash_multimap_t, _HASH_MULTIMAP_TYPE, hash_multimap);
    _TYPE_REGISTER_TYPE_NODE(hash_multimap_t, _HASH_MULTIMAP_TYPE);
    /* register pair_t */
    _TYPE_REGISTER_TYPE(pair_t, _PAIR_TYPE, pair);
    _TYPE_REGISTER_TYPE_NODE(pair_t, _PAIR_TYPE);
    /* register string_t */
    _TYPE_REGISTER_TYPE(string_t, _STRING_TYPE, string);
    _TYPE_REGISTER_TYPE_NODE(string_t, _STRING_TYPE);

    /* register iterator_t */
    _TYPE_REGISTER_TYPE(iterator_t, _ITERATOR_TYPE, iterator);
    _TYPE_REGISTER_TYPE_NODE(iterator_t, _ITERATOR_TYPE);
    _TYPE_REGISTER_TYPE_NODE(vector_iterator_t, _VECTOR_ITERATOR_TYPE);
    _TYPE_REGISTER_TYPE_NODE(list_iterator_t, _LIST_ITERATOR_TYPE);
    _TYPE_REGISTER_TYPE_NODE(slist_iterator_t, _SLIST_ITERATOR_TYPE);
    _TYPE_REGISTER_TYPE_NODE(deque_iterator_t, _DEQUE_ITERATOR_TYPE);
    _TYPE_REGISTER_TYPE_NODE(set_iterator_t, _SET_ITERATOR_TYPE);
    _TYPE_REGISTER_TYPE_NODE(map_iterator_t, _MAP_ITERATOR_TYPE);
    _TYPE_REGISTER_TYPE_NODE(multiset_iterator_t, _MULTISET_ITERATOR_TYPE);
    _TYPE_REGISTER_TYPE_NODE(multimap_iterator_t, _MULTIMAP_ITERATOR_TYPE);
    _TYPE_REGISTER_TYPE_NODE(hash_set_iterator_t, _HASH_SET_ITERATOR_TYPE);
    _TYPE_REGISTER_TYPE_NODE(hash_map_iterator_t, _HASH_MAP_ITERATOR_TYPE);
    _TYPE_REGISTER_TYPE_NODE(hash_multiset_iterator_t, _HASH_MULTISET_ITERATOR_TYPE);
    _TYPE_REGISTER_TYPE_NODE(hash_multimap_iterator_t, _HASH_MULTIMAP_ITERATOR_TYPE);
    _TYPE_REGISTER_TYPE_NODE(string_iterator_t, _STRING_ITERATOR_TYPE);
    _TYPE_REGISTER_TYPE_NODE(input_iterator_t, _INPUT_ITERATOR_TYPE);
    _TYPE_REGISTER_TYPE_NODE(output_iterator_t, _OUTPUT_ITERATOR_TYPE);
    _TYPE_REGISTER_TYPE_NODE(forward_iterator_t, _FORWARD_ITERATOR_TYPE);
    _TYPE_REGISTER_TYPE_NODE(bidirectional_iterator_t, _BIDIRECTIONAL_ITERATOR_TYPE);
    _TYPE_REGISTER_TYPE_NODE(random_access_iterator_t, _RANDOM_ACCESS_ITERATOR_TYPE);

    _TYPE_REGISTER_END();
}

/*
 * the cstl builtin copy, compare destroy function for c builtin type and cstl builtins.
 */
/* c builtin */
/* char */
static void _type_init_char(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(char*)cpv_input = '\0';
    *(bool_t*)pv_output = true;
}
static void _type_copy_char(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(char*)cpv_first = *(char*)cpv_second;
    *(bool_t*)pv_output = true;
}
static void _type_less_char(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(char*)cpv_first < *(char*)cpv_second ? true : false;
}
static void _type_destroy_char(
    const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}
/* unsigned char */
static void _type_init_uchar(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(unsigned char*)cpv_input = 0x00;
    *(bool_t*)pv_output = true;
}
static void _type_copy_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(unsigned char*)cpv_first = *(unsigned char*)cpv_second;
    *(bool_t*)pv_output = true;
}
static void _type_less_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(unsigned char*)cpv_first < *(unsigned char*)cpv_second ?
                          true : false;
}
static void _type_destroy_uchar(
    const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}
/* short */
static void _type_init_short(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(short*)cpv_input = 0;
    *(bool_t*)pv_output = true;
}
static void _type_copy_short(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(short*)cpv_first = *(short*)cpv_second;
    *(bool_t*)pv_output = true;
}
static void _type_less_short(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(short*)cpv_first < *(short*)cpv_second ? true : false;
}
static void _type_destroy_short(
    const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}
/* unsigned short */
static void _type_init_ushort(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(unsigned short*)cpv_input = 0;
    *(bool_t*)pv_output = true;
}
static void _type_copy_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(unsigned short*)cpv_first = *(unsigned short*)cpv_second;
    *(bool_t*)pv_output = true;
}
static void _type_less_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(unsigned short*)cpv_first < *(unsigned short*)cpv_second ? 
                          true : false;
}
static void _type_destroy_ushort(
    const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}
/* int */
static void _type_init_int(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(int*)cpv_input = 0;
    *(bool_t*)pv_output = true;
}
static void _type_copy_int(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(int*)cpv_first = *(int*)cpv_second;
    *(bool_t*)pv_output = true;
}
static void _type_less_int(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(int*)cpv_first < *(int*)cpv_second ? true : false;
}
static void _type_destroy_int(
    const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}
/* unsigned int */
static void _type_init_uint(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(unsigned int*)cpv_input = 0;
    *(bool_t*)pv_output = true;
}
static void _type_copy_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(unsigned int*)cpv_first = *(unsigned int*)cpv_second;
    *(bool_t*)pv_output = true;
}
static void _type_less_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(unsigned int*)cpv_first < *(unsigned int*)cpv_second ?
                          true : false;
}
static void _type_destroy_uint(
    const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}
/* long */
static void _type_init_long(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(long*)cpv_input = 0;
    *(bool_t*)pv_output = true;
}
static void _type_copy_long(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(long*)cpv_first = *(long*)cpv_second;
    *(bool_t*)pv_output = true;
}
static void _type_less_long(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(long*)cpv_first < *(long*)cpv_second ? true : false;
}
static void _type_destroy_long(
    const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}
/* unsigned long */
static void _type_init_ulong(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(unsigned long*)cpv_input = 0;
    *(bool_t*)pv_output = true;
}
static void _type_copy_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(unsigned long*)cpv_first = *(unsigned long*)cpv_second;
    *(bool_t*)pv_output = true;
}
static void _type_less_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(unsigned long*)cpv_first < *(unsigned long*)cpv_second ?
                          true : false;
}
static void _type_destroy_ulong(
    const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}
/* float */
static void _type_init_float(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(float*)cpv_input = 0.0;
    *(bool_t*)pv_output = true;
}
static void _type_copy_float(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(float*)cpv_first = *(float*)cpv_second;
    *(bool_t*)pv_output = true;
}
static void _type_less_float(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(float*)cpv_first - *(float*)cpv_second < -FLT_EPSILON ?
                          true : false;
}
static void _type_destroy_float(
    const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}
/* double */
static void _type_init_double(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(double*)cpv_input = 0.0;
    *(bool_t*)pv_output = true;
}
static void _type_copy_double(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(double*)cpv_first = *(double*)cpv_second;
    *(bool_t*)pv_output = true;
}
static void _type_less_double(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(double*)cpv_first - *(double*)cpv_second < -DBL_EPSILON ?
                          true : false;
}
static void _type_destroy_double(
    const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}
/* long double */
static void _type_init_long_double(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(long double*)cpv_input = 0.0;
    *(bool_t*)pv_output = true;
}
static void _type_copy_long_double(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(long double*)cpv_first = *(long double*)cpv_second;
    *(bool_t*)pv_output = true;
}
static void _type_less_long_double(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(long double*)cpv_first - *(long double*)cpv_second < 
                          -LDBL_EPSILON ? true : false;
}
static void _type_destroy_long_double(
    const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}
/* bool_t */
static void _type_init_bool(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    *(bool_t*)cpv_input = false;
    *(bool_t*)pv_output = true;
}
static void _type_copy_bool(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)cpv_first = *(bool_t*)cpv_second;
    *(bool_t*)pv_output = true;
}
static void _type_less_bool(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = *(bool_t*)cpv_first < *(bool_t*)cpv_second ? true : false;
}
static void _type_destroy_bool(
    const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}
/* char* */
/*
 * char* is specific c builtin type, the string_t is used for storing the 
 * char* or c_str type. 
 */
static void _type_init_cstr(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    string_init((string_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
static void _type_copy_cstr(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    string_assign((string_t*)cpv_first, (string_t*)cpv_second);
    *(bool_t*)pv_output = true;
}
static void _type_less_cstr(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = string_less((string_t*)cpv_first, (string_t*)cpv_second);
}
static void _type_destroy_cstr(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    string_destroy((string_t*)cpv_input);
    *(bool_t*)pv_output = true;
}

/* cstl container */
/* vector_t */
static void _type_init_vector(
    const void* cpv_input, void* pv_output)
{
    bool_t t_result = false;

    assert(cpv_input != NULL && pv_output != NULL);

    t_result = _create_vector_auxiliary((vector_t*)cpv_input, (char*)pv_output);
    assert(t_result);
    /* initialize vector_t */
    vector_init((vector_t*)cpv_input);
}
static void _type_copy_vector(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    vector_assign((vector_t*)cpv_first, (vector_t*)cpv_second);
    *(bool_t*)pv_output = true;
}
static void _type_less_vector(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = vector_less((vector_t*)cpv_first, (vector_t*)cpv_second);
}
static void _type_destroy_vector(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _vector_destroy_auxiliary((vector_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* list_t */
static void _type_init_list(
    const void* cpv_input, void* pv_output)
{
    bool_t t_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    t_result = _create_list_auxiliary((list_t*)cpv_input, (char*)pv_output);
    assert(t_result);
    /* initialize list_t */
    list_init((list_t*)cpv_input);
}
static void _type_copy_list(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    list_assign((list_t*)cpv_first, (list_t*)cpv_second);
    *(bool_t*)pv_output = true;
}
static void _type_less_list(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = list_less((list_t*)cpv_first, (list_t*)cpv_second);
}
static void _type_destroy_list(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _list_destroy_auxiliary((list_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* slist_t */
static void _type_init_slist(
    const void* cpv_input, void* pv_output)
{
    bool_t t_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    t_result = _create_slist_auxiliary((slist_t*)cpv_input, (char*)pv_output);
    assert(t_result);
    /* initialize slist_t */
    slist_init((slist_t*)cpv_input);
}
static void _type_copy_slist(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    slist_assign((slist_t*)cpv_first, (slist_t*)cpv_second);
    *(bool_t*)pv_output = true;
}
static void _type_less_slist(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = slist_less((slist_t*)cpv_first, (slist_t*)cpv_second);
}
static void _type_destroy_slist(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _slist_destroy_auxiliary((slist_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* deque_t */
static void _type_init_deque(
    const void* cpv_input, void* pv_output)
{
    bool_t t_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    t_result = _create_deque_auxiliary((deque_t*)cpv_input, (char*)pv_output);
    assert(t_result);
    /* initialize deque_t */
    deque_init((deque_t*)cpv_input);
}
static void _type_copy_deque(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    deque_assign((deque_t*)cpv_first, (deque_t*)cpv_second);
    *(bool_t*)pv_output = true;
}
static void _type_less_deque(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = deque_less((deque_t*)cpv_first, (deque_t*)cpv_second);
}
static void _type_destroy_deque(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _deque_destroy_auxiliary((deque_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* stack_t */
static void _type_init_stack(
    const void* cpv_input, void* pv_output)
{
    bool_t t_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    t_result = _create_stack_auxiliary((stack_t*)cpv_input, (char*)pv_output);
    assert(t_result);
    stack_init((stack_t*)cpv_input);
}
static void _type_copy_stack(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    stack_assign((stack_t*)cpv_first, (stack_t*)cpv_second);
    *(bool_t*)pv_output = true;
}
static void _type_less_stack(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = stack_less((stack_t*)cpv_first, (stack_t*)cpv_second);
}
static void _type_destroy_stack(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _stack_destroy_auxiliary((stack_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* queue_t */
static void _type_init_queue(
    const void* cpv_input, void* pv_output)
{
    bool_t t_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    t_result = _create_queue_auxiliary((queue_t*)cpv_input, (char*)pv_output);
    assert(t_result);

    queue_init((queue_t*)cpv_input);
}
static void _type_copy_queue(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    queue_assign((queue_t*)cpv_first, (queue_t*)cpv_second);
    *(bool_t*)pv_output = true;
}
static void _type_less_queue(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = queue_less((queue_t*)cpv_first, (queue_t*)cpv_second);
}
static void _type_destroy_queue(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _queue_destroy_auxiliary((queue_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* priority_queue_t */
static void _type_init_priority_queue(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    priority_queue_init((priority_queue_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
static void _type_copy_priority_queue(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    priority_queue_assign((priority_queue_t*)cpv_first, (priority_queue_t*)cpv_second);
    *(bool_t*)pv_output = true;
}
static void _type_less_priority_queue(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = vector_less(
        &((priority_queue_t*)cpv_first)->_t_vector, 
        &((priority_queue_t*)cpv_second)->_t_vector);
}
static void _type_destroy_priority_queue(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    priority_queue_destroy((priority_queue_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* set_t */
static void _type_init_set(
    const void* cpv_input, void* pv_output)
{
    bool_t t_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    t_result = _create_set_auxiliary((set_t*)cpv_input, (char*)pv_output);
    assert(t_result);
    set_init((set_t*)cpv_input);
}
static void _type_copy_set(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    set_assign((set_t*)cpv_first, (set_t*)cpv_second);
    *(bool_t*)pv_output = true;
}
static void _type_less_set(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = set_less((set_t*)cpv_first, (set_t*)cpv_second);
}
static void _type_destroy_set(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _set_destroy_auxiliary((set_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* map_t */
static void _type_init_map(
    const void* cpv_input, void* pv_output)
{
    bool_t t_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    t_result = _create_map_auxiliary((map_t*)cpv_input, (char*)pv_output);
    assert(t_result);
    map_init((map_t*)cpv_input);
}
static void _type_copy_map(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    map_assign((map_t*)cpv_first, (map_t*)cpv_second);
    *(bool_t*)pv_output = true;
}
static void _type_less_map(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = map_less((map_t*)cpv_first, (map_t*)cpv_second);
}
static void _type_destroy_map(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _map_destroy_auxiliary((map_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* multiset_t */
static void _type_init_multiset(
    const void* cpv_input, void* pv_output)
{
    bool_t t_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    t_result = _create_multiset_auxiliary((multiset_t*)cpv_input, (char*)pv_output);
    assert(t_result);
    multiset_init((multiset_t*)cpv_input);
}
static void _type_copy_multiset(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    multiset_assign((multiset_t*)cpv_first, (multiset_t*)cpv_second);
    *(bool_t*)pv_output = true;
}
static void _type_less_multiset(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = multiset_less((multiset_t*)cpv_first, (multiset_t*)cpv_second);
}
static void _type_destroy_multiset(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _multiset_destroy_auxiliary((multiset_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* multimap_t */
static void _type_init_multimap(
    const void* cpv_input, void* pv_output)
{
    bool_t t_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    t_result = _create_multimap_auxiliary((multimap_t*)cpv_input, (char*)pv_output);
    assert(t_result);
    multimap_init((multimap_t*)cpv_input);
}
static void _type_copy_multimap(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    multimap_assign((multimap_t*)cpv_first, (multimap_t*)cpv_second);
    *(bool_t*)pv_output = true;
}
static void _type_less_multimap(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = multimap_less((multimap_t*)cpv_first, (multimap_t*)cpv_second);
}
static void _type_destroy_multimap(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _multimap_destroy_auxiliary((multimap_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* hash_set_t */
static void _type_init_hash_set(
    const void* cpv_input, void* pv_output)
{
    bool_t t_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    t_result = _create_hash_set_auxiliary((hash_set_t*)cpv_input, (char*)pv_output);
    assert(t_result);
    hash_set_init((hash_set_t*)cpv_input);
}
static void _type_copy_hash_set(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    hash_set_assign((hash_set_t*)cpv_first, (hash_set_t*)cpv_second);
    *(bool_t*)pv_output = true;
}
static void _type_less_hash_set(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = hash_set_less((hash_set_t*)cpv_first, (hash_set_t*)cpv_second);
}
static void _type_destroy_hash_set(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _hash_set_destroy_auxiliary((hash_set_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* hash_map_t */
static void _type_init_hash_map(
    const void* cpv_input, void* pv_output)
{
    bool_t t_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    t_result = _create_hash_map_auxiliary((hash_map_t*)cpv_input, (char*)pv_output);
    assert(t_result);
    hash_map_init((hash_map_t*)cpv_input);
}
static void _type_copy_hash_map(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    hash_map_assign((hash_map_t*)cpv_first, (hash_map_t*)cpv_second);
    *(bool_t*)pv_output = true;
}
static void _type_less_hash_map(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = hash_map_less((hash_map_t*)cpv_first, (hash_map_t*)cpv_second);
}
static void _type_destroy_hash_map(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _hash_map_destroy_auxiliary((hash_map_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* hash_multiset_t */
static void _type_init_hash_multiset(
    const void* cpv_input, void* pv_output)
{
    bool_t t_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    t_result = _create_hash_multiset_auxiliary((hash_multiset_t*)cpv_input, (char*)pv_output);
    assert(t_result);
    hash_multiset_init((hash_multiset_t*)cpv_input);
}
static void _type_copy_hash_multiset(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    hash_multiset_assign((hash_multiset_t*)cpv_first, (hash_multiset_t*)cpv_second);
    *(bool_t*)pv_output = true;
}
static void _type_less_hash_multiset(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = hash_multiset_less(
        (hash_multiset_t*)cpv_first, (hash_multiset_t*)cpv_second);
}
static void _type_destroy_hash_multiset(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _hash_multiset_destroy_auxiliary((hash_multiset_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* hash_multimap_t */
static void _type_init_hash_multimap(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    hash_multimap_init((hash_multimap_t*)cpv_input, NULL);
    *(bool_t*)pv_output = true;
}
static void _type_copy_hash_multimap(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    hash_multimap_assign((hash_multimap_t*)cpv_first, (hash_multimap_t*)cpv_second);
    *(bool_t*)pv_output = true;
}
static void _type_less_hash_multimap(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = hash_multimap_less(
        (hash_multimap_t*)cpv_first, (hash_multimap_t*)cpv_second);
}
static void _type_destroy_hash_multimap(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    hash_multimap_destroy((hash_multimap_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* pair_t */
static void _type_init_pair(
    const void* cpv_input, void* pv_output)
{
    bool_t t_result = false;
    assert(cpv_input != NULL && pv_output != NULL);

    t_result = _create_pair_auxiliary((pair_t*)cpv_input, (char*)pv_output);
    assert(t_result);
    /* initialize pair */
    pair_init((pair_t*)cpv_input);
}
static void _type_copy_pair(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    pair_assign((pair_t*)cpv_first, (pair_t*)cpv_second);
    *(bool_t*)pv_output = true;
}
static void _type_less_pair(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = pair_less((pair_t*)cpv_first, (pair_t*)cpv_second);
}
static void _type_destroy_pair(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _pair_destroy_auxiliary((pair_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* string_t */
static void _type_init_string(
    const void* cpv_input, void* pv_output)
{
    bool_t t_result = false;
    assert(cpv_input != NULL && pv_output != NULL);
    t_result = _create_string_auxiliary((string_t*)cpv_input);
    assert(t_result);
    string_init((string_t*)cpv_input);
}
static void _type_copy_string(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    string_assign((string_t*)cpv_first, (string_t*)cpv_second);
    *(bool_t*)pv_output = true;
}
static void _type_less_string(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = string_less((string_t*)cpv_first, (string_t*)cpv_second);
}
static void _type_destroy_string(
    const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    _string_destroy_auxiliary((string_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* iterator_t */
static void _type_init_iterator(
    const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = sizeof(iterator_t);
    _type_init_default(cpv_input, pv_output);
}
static void _type_copy_iterator(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    memcpy((iterator_t*)cpv_first, (iterator_t*)cpv_second, sizeof(iterator_t));
    *(bool_t*)pv_output = true;
}
static void _type_less_iterator(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);
    *(bool_t*)pv_output = memcmp((iterator_t*)cpv_first, (iterator_t*)cpv_second,
        sizeof(iterator_t)) < 0 ? true : false;
}
static void _type_destroy_iterator(
    const void* cpv_input, void* pv_output)
{
    _type_destroy_default(cpv_input, pv_output);
}

/************************** destroy in the future ******************************/
void _unify_types(size_t t_typesize, char* sz_typename)
{
    char*  sz_avoidwarning = NULL;
    size_t t_avoidwarning = 0;
    t_avoidwarning = t_typesize;
    sz_avoidwarning = sz_typename;

#if CSTL_TYPES_UNIFICATION == 1
    /* do nothing */
#elif CSTL_TYPES_UNIFICATION == 2
    /* char type */
    if(strncmp(sz_typename, _SIGNED_CHAR_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        memset(sz_typename, '\0', _ELEM_TYPE_NAME_SIZE+1);
        strncpy(sz_typename, _CHAR_TYPE, _ELEM_TYPE_NAME_SIZE);
    }
    /* short type */
    else if(
        strncmp(sz_typename, _SIGNED_SHORT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _SIGNED_SHORT_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _SHORT_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        memset(sz_typename, '\0', _ELEM_TYPE_NAME_SIZE+1);
        strncpy(sz_typename, _SHORT_TYPE, _ELEM_TYPE_NAME_SIZE);
    }
    /* unsigned short */
    else if(
        strncmp(sz_typename, _UNSIGNED_SHORT_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        memset(sz_typename, '\0', _ELEM_TYPE_NAME_SIZE+1);
        strncpy(sz_typename, _UNSIGNED_SHORT_TYPE, _ELEM_TYPE_NAME_SIZE);
    }
    /* int type */
    else if(
        strncmp(sz_typename, _SIGNED_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _SIGNED_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        memset(sz_typename, '\0', _ELEM_TYPE_NAME_SIZE+1);
        strncpy(sz_typename, _INT_TYPE, _ELEM_TYPE_NAME_SIZE);
    }
    /* unsigned */
    else if(
        strncmp(sz_typename, _UNSIGNED_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        memset(sz_typename, '\0', _ELEM_TYPE_NAME_SIZE+1);
        strncpy(sz_typename, _UNSIGNED_INT_TYPE, _ELEM_TYPE_NAME_SIZE);
    }
    /* long type */
    else if(
        strncmp(sz_typename, _SIGNED_LONG_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _SIGNED_LONG_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _LONG_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        memset(sz_typename, '\0', _ELEM_TYPE_NAME_SIZE+1);
        strncpy(sz_typename, _LONG_TYPE, _ELEM_TYPE_NAME_SIZE);
    }
    /* unsigne long */
    else if(
        strncmp(sz_typename, _UNSIGNED_LONG_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        memset(sz_typename, '\0', _ELEM_TYPE_NAME_SIZE+1);
        strncpy(sz_typename, _UNSIGNED_LONG_TYPE, _ELEM_TYPE_NAME_SIZE);
    }
#elif CSTL_TYPES_UNIFICATION == 3
    /* char type */
    if(strncmp(sz_typename, _SIGNED_CHAR_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
       strncmp(sz_typename, _UNSIGNED_CHAR_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        memset(sz_typename, '\0', _ELEM_TYPE_NAME_SIZE+1);
        strncpy(sz_typename, _CHAR_TYPE, _ELEM_TYPE_NAME_SIZE);
    }
    /* short type */
    else if(
        strncmp(sz_typename, _SIGNED_SHORT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _SIGNED_SHORT_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _UNSIGNED_SHORT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _UNSIGNED_SHORT_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _SHORT_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        memset(sz_typename, '\0', _ELEM_TYPE_NAME_SIZE+1);
        strncpy(sz_typename, _SHORT_TYPE, _ELEM_TYPE_NAME_SIZE);
    }
    /* int type */
    else if(
        strncmp(sz_typename, _SIGNED_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _SIGNED_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _UNSIGNED_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _UNSIGNED_TYPE, _ELEM_TYPE_NAME_SIZE) ==0)
    {
        memset(sz_typename, '\0', _ELEM_TYPE_NAME_SIZE+1);
        strncpy(sz_typename, _INT_TYPE, _ELEM_TYPE_NAME_SIZE);
    }
    /* long type */
    else if(
        strncmp(sz_typename, _SIGNED_LONG_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _SIGNED_LONG_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _UNSIGNED_LONG_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _UNSIGNED_LONG_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _LONG_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        memset(sz_typename, '\0', _ELEM_TYPE_NAME_SIZE+1);
        strncpy(sz_typename, _LONG_TYPE, _ELEM_TYPE_NAME_SIZE);
    }
#elif CSTL_TYPES_UNIFICATION == 4
    /* char type */
    if(strncmp(sz_typename, _SIGNED_CHAR_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
       strncmp(sz_typename, _UNSIGNED_CHAR_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
       strncmp(sz_typename, _CHAR_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        memset(sz_typename, '\0', _ELEM_TYPE_NAME_SIZE+1);
        strncpy(sz_typename, _CHAR_TYPE, _ELEM_TYPE_NAME_SIZE);

        if(t_typesize == sizeof(short))
        {
            memset(sz_typename, '\0', _ELEM_TYPE_NAME_SIZE+1);
            strncpy(sz_typename, _SHORT_TYPE, _ELEM_TYPE_NAME_SIZE);
        }
    }
    /* short type */
    else if(
        strncmp(sz_typename, _SIGNED_SHORT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _SIGNED_SHORT_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _UNSIGNED_SHORT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _UNSIGNED_SHORT_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _SHORT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _SHORT_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        memset(sz_typename, '\0', _ELEM_TYPE_NAME_SIZE+1);
        strncpy(sz_typename, _SHORT_TYPE, _ELEM_TYPE_NAME_SIZE);

        if(t_typesize == sizeof(int))
        {
            memset(sz_typename, '\0', _ELEM_TYPE_NAME_SIZE+1);
            strncpy(sz_typename, _INT_TYPE, _ELEM_TYPE_NAME_SIZE);
        }
    }
    /* int type */
    else if(
        strncmp(sz_typename, _SIGNED_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _SIGNED_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _UNSIGNED_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _UNSIGNED_TYPE, _ELEM_TYPE_NAME_SIZE) ==0)
    {
        memset(sz_typename, '\0', _ELEM_TYPE_NAME_SIZE+1);
        strncpy(sz_typename, _INT_TYPE, _ELEM_TYPE_NAME_SIZE);
    }
    /* long type */
    else if(
        strncmp(sz_typename, _SIGNED_LONG_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _SIGNED_LONG_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _UNSIGNED_LONG_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _UNSIGNED_LONG_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _LONG_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
        strncmp(sz_typename, _LONG_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        memset(sz_typename, '\0', _ELEM_TYPE_NAME_SIZE+1);
        strncpy(sz_typename, _LONG_TYPE, _ELEM_TYPE_NAME_SIZE);

        if(t_typesize == sizeof(int))
        {
            memset(sz_typename, '\0', _ELEM_TYPE_NAME_SIZE+1);
            strncpy(sz_typename, _INT_TYPE, _ELEM_TYPE_NAME_SIZE);
        }
    }
    else if(
        strncmp(sz_typename, _FLOAT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 &&
        t_typesize == sizeof(double))
    {
        memset(sz_typename, '\0', _ELEM_TYPE_NAME_SIZE+1);
        strncpy(sz_typename, _DOUBLE_TYPE, _ELEM_TYPE_NAME_SIZE);
    }
#else
#   error invalid CSTL_TYPES_UNIFICATION macro.
#endif
}

void _get_varg_value(
    void* pv_output,
    va_list val_elemlist,
    size_t t_typesize,
    const char* s_typename)
{
    char sz_builtin[_ELEM_TYPE_NAME_SIZE + 1];

    assert(pv_output != NULL && t_typesize > 0);

    _get_builtin_type(s_typename, sz_builtin);
    /* char */
    if(strncmp(sz_builtin, _CHAR_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
       strncmp(sz_builtin, _SIGNED_CHAR_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        assert(t_typesize == sizeof(char));
        *(char*)pv_output = va_arg(val_elemlist, int);
    }
    /* unsigned char */
    else if(strncmp(sz_builtin, _UNSIGNED_CHAR_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        assert(t_typesize == sizeof(unsigned char));
        *(unsigned char*)pv_output = va_arg(val_elemlist, int);
    }
    /* short */
    else if(strncmp(sz_builtin, _SHORT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SHORT_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SIGNED_SHORT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SIGNED_SHORT_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        assert(t_typesize == sizeof(short));
        *(short*)pv_output = va_arg(val_elemlist, int);
    }
    /* unsigned short */
    else if(strncmp(sz_builtin, _UNSIGNED_SHORT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _UNSIGNED_SHORT_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        assert(t_typesize == sizeof(unsigned short));
        *(unsigned short*)pv_output = va_arg(val_elemlist, int);
    }
    /* int */
    else if(strncmp(sz_builtin, _INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SIGNED_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SIGNED_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        assert(t_typesize == sizeof(int));
        *(int*)pv_output = va_arg(val_elemlist, int);
    }
    /* unsigned int */
    else if(strncmp(sz_builtin, _UNSIGNED_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _UNSIGNED_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        assert(t_typesize == sizeof(unsigned int));
        *(unsigned int*)pv_output = va_arg(val_elemlist, unsigned int);
    }
    /* long */
    else if(strncmp(sz_builtin, _LONG_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _LONG_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SIGNED_LONG_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SIGNED_LONG_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        assert(t_typesize == sizeof(long));
        *(long*)pv_output = va_arg(val_elemlist, long);
    }
    /* unsigned long */
    else if(strncmp(sz_builtin, _UNSIGNED_LONG_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _UNSIGNED_LONG_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        assert(t_typesize == sizeof(unsigned long));
        *(unsigned long*)pv_output = va_arg(val_elemlist, unsigned long);
    }
    /* float */
    else if(strncmp(sz_builtin, _FLOAT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        assert(t_typesize == sizeof(float));
        *(float*)pv_output = va_arg(val_elemlist, double);
    }
    /* double */
    else if(strncmp(sz_builtin, _DOUBLE_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        assert(t_typesize == sizeof(double));
        *(double*)pv_output = va_arg(val_elemlist, double);
    }
    /* bool_t */
    else if(strncmp(sz_builtin, _BOOL_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        assert(t_typesize == sizeof(bool_t));
        *(bool_t*)pv_output = va_arg(val_elemlist, int);
    }
    else
    {
        memcpy(pv_output, val_elemlist, t_typesize);
    }
}

void _get_builtin_type(const char* s_typename, char* s_builtin)
{
    assert(s_typename != NULL && s_builtin != NULL);

    memset(s_builtin, '\0', _ELEM_TYPE_NAME_SIZE + 1);

    /* set<...> */
    if(strncmp(s_typename, _SET_IDENTIFY, strlen(_SET_IDENTIFY)) == 0 &&
       s_typename[strlen(_SET_IDENTIFY)] == _CSTL_LEFT_BRACKET &&
       s_typename[strlen(s_typename) - 1] == _CSTL_RIGHT_BRACKET)
    {
        strncpy(
            s_builtin, 
            s_typename + strlen(_SET_IDENTIFY) + 1, 
            strlen(s_typename) - strlen(_SET_IDENTIFY) - 2);
    }
    /* multiset<...> */
    else if(strncmp(s_typename, _MULTISET_IDENTIFY, strlen(_MULTISET_IDENTIFY)) == 0 &&
            s_typename[strlen(_MULTISET_IDENTIFY)] == _CSTL_LEFT_BRACKET &&
            s_typename[strlen(s_typename) - 1] == _CSTL_RIGHT_BRACKET)
    {
        strncpy(
            s_builtin,
            s_typename + strlen(_MULTISET_IDENTIFY) + 1,
            strlen(s_typename) - strlen(_MULTISET_IDENTIFY) - 2);
    }
    /* map<...,...> */
    else if(strncmp(s_typename, _MAP_IDENTIFY, strlen(_MAP_IDENTIFY)) == 0 &&
            s_typename[strlen(_MAP_IDENTIFY)] == _CSTL_LEFT_BRACKET &&
            s_typename[strlen(s_typename) - 1] == _CSTL_RIGHT_BRACKET &&
            strchr(s_typename, _CSTL_COMMA) != NULL)
    {
        strncpy(
            s_builtin,
            s_typename + strlen(_MAP_IDENTIFY) + 1,
            strlen(s_typename) - strlen(_MAP_IDENTIFY) - 2);
    }
    /* multimap<...,...> */
    else if(strncmp(s_typename, _MULTIMAP_IDENTIFY, strlen(_MULTIMAP_IDENTIFY)) == 0 &&
            s_typename[strlen(_MULTIMAP_IDENTIFY)] == _CSTL_LEFT_BRACKET &&
            s_typename[strlen(s_typename) - 1] == _CSTL_RIGHT_BRACKET &&
            strchr(s_typename, _CSTL_COMMA) != NULL)
    {
        strncpy(
            s_builtin,
            s_typename + strlen(_MULTIMAP_IDENTIFY) + 1,
            strlen(s_typename) - strlen(_MULTIMAP_IDENTIFY) - 2);
    }
    /* hash_set<...> */
    else if(strncmp(s_typename, _HASH_SET_IDENTIFY, strlen(_HASH_SET_IDENTIFY)) == 0 &&
            s_typename[strlen(_HASH_SET_IDENTIFY)] == _CSTL_LEFT_BRACKET &&
            s_typename[strlen(s_typename) - 1] == _CSTL_RIGHT_BRACKET)
    {
        strncpy(
            s_builtin,
            s_typename + strlen(_HASH_SET_IDENTIFY) + 1,
            strlen(s_typename) - strlen(_HASH_SET_IDENTIFY) - 2);
    }
    /* hash_multiset<...> */
    else if(strncmp(
            s_typename, _HASH_MULTISET_IDENTIFY, strlen(_HASH_MULTISET_IDENTIFY)) == 0 &&
            s_typename[strlen(_HASH_MULTISET_IDENTIFY)] == _CSTL_LEFT_BRACKET &&
            s_typename[strlen(s_typename) - 1] == _CSTL_RIGHT_BRACKET)
    {
        strncpy(
            s_builtin,
            s_typename + strlen(_HASH_MULTISET_IDENTIFY) + 1,
            strlen(s_typename) - strlen(_HASH_MULTISET_IDENTIFY) - 2);
    }
    /* hash_map<...,...> */
    else if(strncmp(s_typename, _HASH_MAP_IDENTIFY, strlen(_HASH_MAP_IDENTIFY)) == 0 &&
            s_typename[strlen(_HASH_MAP_IDENTIFY)] == _CSTL_LEFT_BRACKET &&
            s_typename[strlen(s_typename) - 1] == _CSTL_RIGHT_BRACKET &&
            strchr(s_typename, _CSTL_COMMA) != NULL)
    {
        strncpy(
            s_builtin,
            s_typename + strlen(_HASH_MAP_IDENTIFY) + 1,
            strlen(s_typename) - strlen(_HASH_MAP_IDENTIFY) - 2);
    }
    /* hash_multimap<...,...> */
    else if(strncmp(
            s_typename, _HASH_MULTIMAP_IDENTIFY, strlen(_HASH_MULTIMAP_IDENTIFY)) == 0 &&
            s_typename[strlen(_HASH_MULTIMAP_IDENTIFY)] == _CSTL_LEFT_BRACKET &&
            s_typename[strlen(s_typename) - 1] == _CSTL_RIGHT_BRACKET &&
            strchr(s_typename, _CSTL_COMMA) != NULL)
    {
        strncpy(
            s_builtin,
            s_typename + strlen(_HASH_MULTIMAP_IDENTIFY) + 1,
            strlen(s_typename) - strlen(_HASH_MULTIMAP_IDENTIFY) - 2);
    }
    /* basic_string<...> */
    else if(strncmp(
            s_typename, _BASIC_STRING_IDENTIFY, strlen(_BASIC_STRING_IDENTIFY)) == 0 &&
            s_typename[strlen(_BASIC_STRING_IDENTIFY)] == _CSTL_LEFT_BRACKET &&
            s_typename[strlen(s_typename) - 1] == _CSTL_RIGHT_BRACKET)
    {
        strncpy(
            s_builtin,
            s_typename + strlen(_BASIC_STRING_IDENTIFY) + 1,
            strlen(s_typename) - strlen(_BASIC_STRING_IDENTIFY) - 2);
    }
    else
    {
        strncpy(s_builtin, s_typename, _ELEM_TYPE_NAME_SIZE);
    }
}

int (*_get_cmp_function(const char* s_typename))(const void*, const void*)
{
    char sz_builtin[_ELEM_TYPE_NAME_SIZE + 1];

    _get_builtin_type(s_typename, sz_builtin);
    /* char */
    if(strncmp(sz_builtin, _CHAR_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
       strncmp(sz_builtin, _SIGNED_CHAR_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        return _cmp_char;
    }
    /* unsigned char */
    else if(strncmp(sz_builtin, _UNSIGNED_CHAR_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        return _cmp_uchar;
    }
    /* short */
    else if(strncmp(sz_builtin, _SHORT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SHORT_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SIGNED_SHORT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SIGNED_SHORT_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        return _cmp_short;
    }
    /* unsigned short */
    else if(strncmp(sz_builtin, _UNSIGNED_SHORT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _UNSIGNED_SHORT_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        return _cmp_ushort;
    }
    /* int */
    else if(strncmp(sz_builtin, _INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SIGNED_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SIGNED_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        return _cmp_int;
    }
    /* unsigned int */
    else if(strncmp(sz_builtin, _UNSIGNED_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _UNSIGNED_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        return _cmp_uint;
    }
    /* long */
    else if(strncmp(sz_builtin, _LONG_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _LONG_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SIGNED_LONG_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SIGNED_LONG_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        return _cmp_long;
    }
    /* unsigned long */
    else if(strncmp(sz_builtin, _UNSIGNED_LONG_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _UNSIGNED_LONG_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        return _cmp_ulong;
    }
    /* float */
    else if(strncmp(sz_builtin, _FLOAT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        return _cmp_float;
    }
    /* double */
    else if(strncmp(sz_builtin, _DOUBLE_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        return _cmp_double;
    }
    else
    {
        return NULL;
    }
}

/** local function implementation section **/
static int _cmp_char(const void* cpv_first, const void* cpv_second)
{
    assert(cpv_first != NULL && cpv_second != NULL);

    return *(char*)cpv_first <= *(char*)cpv_second ?
           *(char*)cpv_first == *(char*)cpv_second ?
           0 : -1 : 1;
}

static int _cmp_uchar(const void* cpv_first, const void* cpv_second)
{
    assert(cpv_first != NULL && cpv_second != NULL);

    return *(unsigned char*)cpv_first <= *(unsigned char*)cpv_second ?
           *(unsigned char*)cpv_first == *(unsigned char*)cpv_second ?
           0 : -1 : 1;
}

static int _cmp_short(const void* cpv_first, const void* cpv_second)
{
    assert(cpv_first != NULL && cpv_second != NULL);

    return *(short*)cpv_first <= *(short*)cpv_second ?
           *(short*)cpv_first == *(short*)cpv_second ?
           0 : -1 : 1;
}

static int _cmp_ushort(const void* cpv_first, const void* cpv_second)
{
    assert(cpv_first != NULL && cpv_second != NULL);

    return *(unsigned short*)cpv_first <= *(unsigned short*)cpv_second ?
           *(unsigned short*)cpv_first == *(unsigned short*)cpv_second ?
           0 : -1 : 1;
}

static int _cmp_int(const void* cpv_first, const void* cpv_second)
{
    assert(cpv_first != NULL && cpv_second != NULL);

    return *(int*)cpv_first <= *(int*)cpv_second ?
           *(int*)cpv_first == *(int*)cpv_second ?
           0 : -1 : 1;
}

static int _cmp_uint(const void* cpv_first, const void* cpv_second)
{
    assert(cpv_first != NULL && cpv_second != NULL);

    return *(unsigned int*)cpv_first <= *(unsigned int*)cpv_second ?
           *(unsigned int*)cpv_first == *(unsigned int*)cpv_second ?
           0 : -1 : 1;
}

static int _cmp_long(const void* cpv_first, const void* cpv_second)
{
    assert(cpv_first != NULL && cpv_second != NULL);

    return *(long*)cpv_first <= *(long*)cpv_second ?
           *(long*)cpv_first == *(long*)cpv_second ?
           0 : -1 : 1;
}

static int _cmp_ulong(const void* cpv_first, const void* cpv_second)
{
    assert(cpv_first != NULL && cpv_second != NULL);

    return *(unsigned long*)cpv_first <= *(unsigned long*)cpv_second ?
           *(unsigned long*)cpv_first == *(unsigned long*)cpv_second ?
           0 : -1 : 1;
}

static int _cmp_float(const void* cpv_first, const void* cpv_second)
{
    assert(cpv_first != NULL && cpv_second != NULL);

    return *(float*)cpv_first - *(float*)cpv_second < FLT_EPSILON ?
           *(float*)cpv_first - *(float*)cpv_second > -FLT_EPSILON ?
           0 : -1 : 1;
}

static int _cmp_double(const void* cpv_first, const void* cpv_second)
{
    assert(cpv_first != NULL && cpv_second != NULL);

    return *(double*)cpv_first - *(double*)cpv_second < DBL_EPSILON ?
           *(double*)cpv_first - *(double*)cpv_second > -DBL_EPSILON ?
           0 : -1 : 1;
}

/** eof **/

