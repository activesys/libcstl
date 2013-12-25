/*
 *  The implementation of cstl types auxiliary functions.
 *  Copyright (C)  2008 - 2014  Wangbo
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
#include <cstl/cstl_def.h>
#include <cstl/cstl_alloc.h>
#include <cstl/cstl_types.h>

#include <cstl/cvector.h>
#include <cstl/clist.h>
#include <cstl/cslist.h>
#include <cstl/cdeque.h>
#include <cstl/cstack.h>
#include <cstl/cqueue.h>
#include <cstl/cset.h>
#include <cstl/cmap.h>
#include <cstl/chash_set.h>
#include <cstl/chash_map.h>
#include <cstl/cstring.h>

#include "cstl_types_aux.h"
#include "cstl_types_parse.h"
#include "cstl_types_builtin.h"

/** local constant declaration and local macro section **/
/* the pt_type, pt_node and t_pos must be defined before use those macro */
#define _TYPE_REGISTER_BEGIN()\
    _typenode_t* pt_node = NULL;\
    _type_t*     pt_type = NULL;\
    size_t       t_pos = 0
#define _TYPE_REGISTER_TYPE(type, type_text, type_suffix, type_style)\
    do{\
        pt_type = (_type_t*)_alloc_allocate(&_gt_typeregister._t_allocator, sizeof(_type_t), 1);\
        assert(pt_type != NULL);\
        pt_type->_t_typesize = sizeof(type);\
        memset(pt_type->_s_typename, '\0', _TYPE_NAME_SIZE+1);\
        strncpy(pt_type->_s_typename, type_text, _TYPE_NAME_SIZE);\
        assert(type_style != _TYPE_INVALID);\
        pt_type->_t_style = type_style;\
        pt_type->_t_typeinit = _type_init_##type_suffix;\
        pt_type->_t_typecopy = _type_copy_##type_suffix;\
        pt_type->_t_typeless = _type_less_##type_suffix;\
        pt_type->_t_typedestroy = _type_destroy_##type_suffix;\
    }while(false)
#define _TYPE_REGISTER_TYPE_NODE(type, type_text)\
    do{\
        pt_node = (_typenode_t*)_alloc_allocate(\
            &_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);\
        assert(pt_node != NULL);\
        memset(pt_node->_s_typename, '\0', _TYPE_NAME_SIZE+1);\
        strncpy(pt_node->_s_typename, type_text, _TYPE_NAME_SIZE);\
        t_pos = _type_hash(type_text);\
        pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];\
        _gt_typeregister._apt_bucket[t_pos] = pt_node;\
        pt_node->_pt_type = pt_type;\
    }while(false)
#define _TYPE_REGISTER_END()

/* BKDR hash seed */
#define _TYPE_HASH_BKDR_SEED    131

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/
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
 *                             | _s_typename = "abc_t"        |
 *                             | _t_typecopy = abc_copy       | "registered type abc_t"
 *                             | _t_typeless = abc_less       |
 *                             | _t_typeinit = abc_init       |
 *                             | _t_typedestroy = abc_destroy |
 *                             +------------------------------+
 */
#ifdef CSTL_MEMORY_MANAGEMENT
_typeregister_t _gt_typeregister = {false, {NULL}, {{NULL}, NULL, NULL, 0, 0, 0}};
#else
_typeregister_t _gt_typeregister = {false, {NULL}, {0}};
#endif

_typecache_t    _gt_typecache[_TYPE_CACHE_COUNT] = {{'\0'}, {'\0'}, 0};
size_t          _gt_typecache_index = 0;

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Caculate hash from type name.
 */
size_t _type_hash(const char* s_typename)
{
    /*
     * Use BKDR hash function.
     */
    size_t t_hash = 0;

    assert(s_typename != NULL);

    while (*s_typename) {
        t_hash = t_hash * _TYPE_HASH_BKDR_SEED + (*s_typename++);
    }

    return t_hash % _TYPE_REGISTER_BUCKET_COUNT;
}

/**
 * Test the type is registered or not
 */
_type_t* _type_is_registered(const char* s_typename)
{
    _type_t*     pt_registered = NULL;
    _typenode_t* pt_node = NULL;

    assert(s_typename != NULL);
    assert(strlen(s_typename) <= _TYPE_NAME_SIZE);

    /* get the registered type pointer */
    pt_node = _gt_typeregister._apt_bucket[_type_hash(s_typename)];
    while (pt_node != NULL) {
        if (strncmp(s_typename, pt_node->_s_typename, _TYPE_NAME_SIZE) == 0) {
            pt_registered = pt_node->_pt_type;
            assert(pt_registered != NULL);
            break;
        } else {
            pt_node = pt_node->_pt_next;
        }
    }

    return pt_registered;
}

/**
 * Initialize the register and register c builtin type and cstl builtin type 
 */
void _type_init(void)
{
    size_t i = 0;

    /* set register hash table */
    for (i = 0; i < _TYPE_REGISTER_BUCKET_COUNT; ++i) {
        _gt_typeregister._apt_bucket[i] = NULL;
    }
    /* init allocator */
    _alloc_init(&_gt_typeregister._t_allocator);

    _type_register_c_builtin();
    _type_register_cstl_builtin();
    
    _gt_typeregister._t_isinit = true;
}

void _type_register_c_builtin(void)
{
    _TYPE_REGISTER_BEGIN();

    /* register char type */
    _TYPE_REGISTER_TYPE(char, _CHAR_TYPE, char, _TYPE_C_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(char, _CHAR_TYPE);
    _TYPE_REGISTER_TYPE_NODE(signed char, _SIGNED_CHAR_TYPE);
    /* register unsigned char */
    _TYPE_REGISTER_TYPE(unsigned char, _UNSIGNED_CHAR_TYPE, uchar, _TYPE_C_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(unsigned char, _UNSIGNED_CHAR_TYPE);
    /* register short */
    _TYPE_REGISTER_TYPE(short, _SHORT_TYPE, short, _TYPE_C_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(short, _SHORT_TYPE);
    _TYPE_REGISTER_TYPE_NODE(short int, _SHORT_INT_TYPE);
    _TYPE_REGISTER_TYPE_NODE(signed short, _SIGNED_SHORT_TYPE);
    _TYPE_REGISTER_TYPE_NODE(signed short int, _SIGNED_SHORT_INT_TYPE);
    /* register unsigned short */
    _TYPE_REGISTER_TYPE(unsigned short, _UNSIGNED_SHORT_TYPE, ushort, _TYPE_C_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(unsigned short, _UNSIGNED_SHORT_TYPE);
    _TYPE_REGISTER_TYPE_NODE(unsigned short int, _UNSIGNED_SHORT_INT_TYPE);
    /* register int */
    _TYPE_REGISTER_TYPE(int, _INT_TYPE, int, _TYPE_C_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(int, _INT_TYPE);
    _TYPE_REGISTER_TYPE_NODE(signed, _SIGNED_TYPE);
    _TYPE_REGISTER_TYPE_NODE(signed int, _SIGNED_INT_TYPE);
    /* register unsigned int */
    _TYPE_REGISTER_TYPE(unsigned int, _UNSIGNED_INT_TYPE, uint, _TYPE_C_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(unsigned int, _UNSIGNED_INT_TYPE);
    _TYPE_REGISTER_TYPE_NODE(signed, _UNSIGNED_TYPE);
    /* register long */
    _TYPE_REGISTER_TYPE(long, _LONG_TYPE, long, _TYPE_C_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(long, _LONG_TYPE);
    _TYPE_REGISTER_TYPE_NODE(long int, _LONG_INT_TYPE);
    _TYPE_REGISTER_TYPE_NODE(signed long, _SIGNED_LONG_TYPE);
    _TYPE_REGISTER_TYPE_NODE(signed long int, _SIGNED_LONG_INT_TYPE);
    /* register unsigned long */
    _TYPE_REGISTER_TYPE(unsigned long, _UNSIGNED_LONG_TYPE, ulong, _TYPE_C_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(unsigned long, _UNSIGNED_LONG_TYPE);
    _TYPE_REGISTER_TYPE_NODE(unsigned long int, _UNSIGNED_LONG_INT_TYPE);
    /* register float */
    _TYPE_REGISTER_TYPE(float, _FLOAT_TYPE, float, _TYPE_C_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(float, _FLOAT_TYPE);
    /* register double */
    _TYPE_REGISTER_TYPE(double, _DOUBLE_TYPE, double, _TYPE_C_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(double, _DOUBLE_TYPE);
    /* register long double */
    _TYPE_REGISTER_TYPE(long double, _LONG_DOUBLE_TYPE, long_double, _TYPE_C_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(long double, _LONG_DOUBLE_TYPE);
    /* register bool_t */
    _TYPE_REGISTER_TYPE(bool_t, _CSTL_BOOL_TYPE, cstl_bool, _TYPE_C_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(bool_t, _CSTL_BOOL_TYPE);
    /* register char* */
    _TYPE_REGISTER_TYPE(string_t, _C_STRING_TYPE, cstr, _TYPE_C_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(string_t, _C_STRING_TYPE);
    /* register void* */
    _TYPE_REGISTER_TYPE(void*, _POINTER_TYPE, pointer, _TYPE_C_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(void*, _POINTER_TYPE);

#ifndef _MSC_VER
    /* register _Bool */
    _TYPE_REGISTER_TYPE(_Bool, _BOOL_TYPE, bool, _TYPE_C_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(_Bool, _BOOL_TYPE);
    /* register long long */
    _TYPE_REGISTER_TYPE(long long, _LONG_LONG_TYPE, long_long, _TYPE_C_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(long long, _LONG_LONG_TYPE);
    _TYPE_REGISTER_TYPE_NODE(long long int, _LONG_LONG_INT_TYPE);
    _TYPE_REGISTER_TYPE_NODE(signed long long, _SIGNED_LONG_LONG_TYPE);
    _TYPE_REGISTER_TYPE_NODE(signed long long int, _SIGNED_LONG_LONG_INT_TYPE);
    /* register unsigned long long */
    _TYPE_REGISTER_TYPE(unsigned long long, _UNSIGNED_LONG_LONG_TYPE, ulong_long, _TYPE_C_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(unsigned long long, _UNSIGNED_LONG_LONG_TYPE);
    _TYPE_REGISTER_TYPE_NODE(unsigned long long int, _UNSIGNED_LONG_LONG_INT_TYPE);
#endif

    _TYPE_REGISTER_END();
}

void _type_register_cstl_builtin(void)
{
    _TYPE_REGISTER_BEGIN();

    /* register vector_t */
    _TYPE_REGISTER_TYPE(vector_t, _VECTOR_TYPE, vector, _TYPE_CSTL_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(vector_t, _VECTOR_TYPE);
    /* register list_t */
    _TYPE_REGISTER_TYPE(list_t, _LIST_TYPE, list, _TYPE_CSTL_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(list_t, _LIST_TYPE);
    /* register slist_t */
    _TYPE_REGISTER_TYPE(slist_t, _SLIST_TYPE, slist, _TYPE_CSTL_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(slist_t, _SLIST_TYPE);
    /* register deque_t */
    _TYPE_REGISTER_TYPE(deque_t, _DEQUE_TYPE, deque, _TYPE_CSTL_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(deque_t, _DEQUE_TYPE);
    /* register stack_t */
    _TYPE_REGISTER_TYPE(stack_t, _STACK_TYPE, stack, _TYPE_CSTL_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(stack_t, _STACK_TYPE);
    /* register queue_t */
    _TYPE_REGISTER_TYPE(queue_t, _QUEUE_TYPE, queue, _TYPE_CSTL_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(queue_t, _QUEUE_TYPE);
    /* register priority_queue_t */
    _TYPE_REGISTER_TYPE(priority_queue_t, _PRIORITY_QUEUE_TYPE, priority_queue, _TYPE_CSTL_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(priority_queue_t, _PRIORITY_QUEUE_TYPE);
    /* register set_t */
    _TYPE_REGISTER_TYPE(set_t, _SET_TYPE, set, _TYPE_CSTL_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(set_t, _SET_TYPE);
    /* register map_t */
    _TYPE_REGISTER_TYPE(map_t, _MAP_TYPE, map, _TYPE_CSTL_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(map_t, _MAP_TYPE);
    /* register multiset_t */
    _TYPE_REGISTER_TYPE(multiset_t, _MULTISET_TYPE, multiset, _TYPE_CSTL_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(multiset_t, _MULTISET_TYPE);
    /* register multimap_t */
    _TYPE_REGISTER_TYPE(multimap_t, _MULTIMAP_TYPE, multimap, _TYPE_CSTL_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(multimap_t, _MULTIMAP_TYPE);
    /* register hash_set_t */
    _TYPE_REGISTER_TYPE(hash_set_t, _HASH_SET_TYPE, hash_set, _TYPE_CSTL_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(hash_set_t, _HASH_SET_TYPE);
    /* register hash_map_t */
    _TYPE_REGISTER_TYPE(hash_map_t, _HASH_MAP_TYPE, hash_map, _TYPE_CSTL_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(hash_map_t, _HASH_MAP_TYPE);
    /* register hash_multiset_t */
    _TYPE_REGISTER_TYPE(hash_multiset_t, _HASH_MULTISET_TYPE, hash_multiset, _TYPE_CSTL_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(hash_multiset_t, _HASH_MULTISET_TYPE);
    /* register hash_multimap_t */
    _TYPE_REGISTER_TYPE(hash_multimap_t, _HASH_MULTIMAP_TYPE, hash_multimap, _TYPE_CSTL_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(hash_multimap_t, _HASH_MULTIMAP_TYPE);
    /* register pair_t */
    _TYPE_REGISTER_TYPE(pair_t, _PAIR_TYPE, pair, _TYPE_CSTL_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(pair_t, _PAIR_TYPE);
    /* register string_t */
    _TYPE_REGISTER_TYPE(string_t, _STRING_TYPE, string, _TYPE_CSTL_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(string_t, _STRING_TYPE);
    /* register range_t */
    _TYPE_REGISTER_TYPE(range_t, _RANGE_TYPE, range, _TYPE_CSTL_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(range_t, _RANGE_TYPE);
    /* register basic_string_t */
    _TYPE_REGISTER_TYPE(basic_string_t, _BASIC_STRING_TYPE, basic_string, _TYPE_CSTL_BUILTIN);
    _TYPE_REGISTER_TYPE_NODE(basic_string_t, _BASIC_STRING_TYPE);

    /* register iterator_t */
    _TYPE_REGISTER_TYPE(iterator_t, _ITERATOR_TYPE, iterator, _TYPE_CSTL_BUILTIN);
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
    _TYPE_REGISTER_TYPE_NODE(basic_string_iterator_t, _BASIC_STRING_ITERATOR_TYPE);

    _TYPE_REGISTER_END();
}

/**
 * Find in type style cache and update cache.
 */
_typestyle_t _type_cache_find(const char* s_typename, char* s_formalname)
{
    size_t i = 0;

    assert(s_typename != NULL);
    assert(s_formalname != NULL);

    for (i = 0; i < _TYPE_CACHE_COUNT; ++i) {
        if (_gt_typecache[i]._t_style == _TYPE_INVALID) {
            return _TYPE_INVALID;
        } else if (strncmp(s_typename, _gt_typecache[i]._s_typename, _TYPE_NAME_SIZE) == 0) {
            strncpy(s_formalname, _gt_typecache[i]._s_formalname, _TYPE_NAME_SIZE);
            return _gt_typecache[i]._t_style;
        }
    }

    return _TYPE_INVALID;
}

void _type_cache_update(const char* s_typename, const char* s_formalname, _typestyle_t t_style)
{
    assert(s_typename != NULL);
    assert(strlen(s_typename) > 0);
    assert(s_formalname != NULL);
    assert(strlen(s_formalname) > 0);
    assert(t_style == _TYPE_C_BUILTIN || t_style == _TYPE_USER_DEFINE || t_style == _TYPE_CSTL_BUILTIN);

    strncpy(_gt_typecache[_gt_typecache_index]._s_typename, s_typename, _TYPE_NAME_SIZE);
    strncpy(_gt_typecache[_gt_typecache_index]._s_formalname, s_formalname, _TYPE_NAME_SIZE);
    _gt_typecache[_gt_typecache_index]._t_style = t_style;

    _gt_typecache_index = (++_gt_typecache_index) % _TYPE_CACHE_COUNT;
}

/** eof **/

