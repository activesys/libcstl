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
 *                             | _t_typedestroy = abc_destroy |
 *                             +------------------------------+
 */
static _typeregister_t _gt_typeregister = {false, {NULL}, {{NULL}, NULL, NULL, 0, 0, 0}};

/** local data type declaration and local struct, union, enum section **/
typedef enum _tagtypestley
{
    _TYPE_INVALID, _TYPE_C_BUILTIN, _TYPE_CSTL, _TYPE_STRUCT, _TYPE_USER_DEFINE
}_typestyle_t;

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
static size_t _type_hash(size_t t_typesize, const char* s_typename);
/* init the register and register c builtin type and cstl builtin type */
static void _type_init(void);
/* test the type is registered or not */
static bool_t _type_is_registered(size_t t_typesize, const char* s_typename);
/* normalize the typename, test the typename is valid or not and get the type style */
static _typestyle_t _type_get_style(const char* s_typename);
/* register c builtin and cstl container */
static void _type_register_c_builtin(void);
static void _type_register_cstl_container(void);

/*
 * the cstl builtin copy, compare destroy function for c builtin type and cstl containers.
 */
/* c builtin */
/* char */
static void _type_copy_char(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_char(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_char(
    const void* cpv_input, void* pv_output);
/* unsigned char */
static void _type_copy_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_uchar(
    const void* cpv_input, void* pv_output);
/* short */
static void _type_copy_short(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_short(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_short(
    const void* cpv_input, void* pv_output);
/* unsigned short */
static void _type_copy_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_ushort(
    const void* cpv_input, void* pv_output);
/* int */
static void _type_copy_int(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_int(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_int(
    const void* cpv_input, void* pv_output);
/* unsigned int */
static void _type_copy_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_uint(
    const void* cpv_input, void* pv_output);
/* long */
static void _type_copy_long(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_long(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_long(
    const void* cpv_input, void* pv_output);
/* unsigned long */
static void _type_copy_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_ulong(
    const void* cpv_input, void* pv_output);
/* float */
static void _type_copy_float(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_float(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_float(
    const void* cpv_input, void* pv_output);
/* double */
static void _type_copy_double(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_double(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_double(
    const void* cpv_input, void* pv_output);
/* long double */
static void _type_copy_long_double(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_long_double(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_long_double(
    const void* cpv_input, void* pv_output);
/* bool_t */
static void _type_copy_bool(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_bool(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_bool(
    const void* cpv_input, void* pv_output);
/* char* */
static void _type_copy_cstr(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_cstr(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_cstr(
    const void* cpv_input, void* pv_output);
/* cstl container */
/* vector_t */
static void _type_copy_vector(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_vector(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_vector(
    const void* cpv_input, void* pv_output);
/* list_t */
static void _type_copy_list(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_list(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_list(
    const void* cpv_input, void* pv_output);
/* slist_t */
static void _type_copy_slist(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_slist(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_slist(
    const void* cpv_input, void* pv_output);
/* deque_t */
static void _type_copy_deque(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_deque(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_deque(
    const void* cpv_input, void* pv_output);
/* stack_t */
static void _type_copy_stack(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_stack(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_stack(
    const void* cpv_input, void* pv_output);
/* queue_t */
static void _type_copy_queue(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_queue(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_queue(
    const void* cpv_input, void* pv_output);
/* priority_queue_t */
static void _type_copy_priority_queue(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_priority_queue(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_priority_queue(
    const void* cpv_input, void* pv_output);
/* set_t */
static void _type_copy_set(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_set(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_set(
    const void* cpv_input, void* pv_output);
/* map_t */
static void _type_copy_map(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_map(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_map(
    const void* cpv_input, void* pv_output);
/* multiset_t */
static void _type_copy_multiset(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_multiset(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_multiset(
    const void* cpv_input, void* pv_output);
/* multimap_t */
static void _type_copy_multimap(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_multimap(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_multimap(
    const void* cpv_input, void* pv_output);
/* hash_set_t */
static void _type_copy_hash_set(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_hash_set(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_hash_set(
    const void* cpv_input, void* pv_output);
/* hash_map_t */
static void _type_copy_hash_map(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_hash_map(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_hash_map(
    const void* cpv_input, void* pv_output);
/* hash_multiset_t */
static void _type_copy_hash_multiset(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_hash_multiset(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_hash_multiset(
    const void* cpv_input, void* pv_output);
/* hash_multimap_t */
static void _type_copy_hash_multimap(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_hash_multimap(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_hash_multimap(
    const void* cpv_input, void* pv_output);
/* pair_t */
static void _type_copy_pair(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_pair(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_pair(
    const void* cpv_input, void* pv_output);
/* string_t */
static void _type_copy_string(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_less_string(
    const void* cpv_first, const void* cpv_second, void* pv_output);
static void _type_destroy_string(
    const void* cpv_input, void* pv_output);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
bool_t _type_register(
    size_t t_typesize, const char* s_typename,
    binary_function_t t_typecopy,
    binary_function_t t_typeless,
    unary_function_t t_typedestroy)
{
    if(!_gt_typeregister._t_isinit)
    {
        _type_init();
    }

    /* test the typename is valid */
    /* if the type is registered */
    if(_type_is_registered(t_typesize, s_typename) || strlen(s_typename) > _TYPE_NAME_SIZE)
    {
         return false;
    }
    /* else */
    else
    {
        size_t t_pos = 0;
        _typenode_t* pt_node = (_typenode_t*)allocate(
            &_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
        _type_t* pt_type = (_type_t*)allocate(
            &_gt_typeregister._t_allocator, sizeof(_type_t*), 1);

        memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
        memset(pt_type->_sz_typename, '\0', _TYPE_NAME_SIZE+1);

        /* register the new type */
        strncpy(pt_node->_sz_typename, s_typename, _TYPE_NAME_SIZE);
        strncpy(pt_type->_sz_typename, s_typename, _TYPE_NAME_SIZE);
        pt_type->_t_typesize = t_typesize;
        pt_type->_t_typecopy = t_typecopy;
        pt_type->_t_typeless = t_typeless;
        pt_type->_t_typedestroy = t_typedestroy;

        pt_node->_pt_type = pt_type;
        t_pos = _type_hash(t_typesize, s_typename);
        pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
        _gt_typeregister._apt_bucket[t_pos] = pt_node;

        return true;
    }
}

void _type_unregister(size_t t_typesize, const char* s_typename)
{
    _typenode_t* pt_node = NULL;
    _type_t*     pt_type = NULL;

    if(strlen(s_typename) > _TYPE_NAME_SIZE)
    {
        return;
    }

    /* get the registered type pointer */
    pt_node = _gt_typeregister._apt_bucket[_type_hash(t_typesize, s_typename)];
    while(pt_node != NULL)
    {
        if(strncmp(pt_node->_sz_typename, s_typename, _TYPE_NAME_SIZE) == 0)
        {
            pt_type = pt_node->_pt_type;
            assert(pt_type != NULL);
            assert(pt_type->_t_typesize == t_typesize);
            break;
        }
        else
        {
            pt_node = pt_node->_pt_next;
        }
    }

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

bool_t _type_duplicate(
    size_t t_typesize1, const char* s_typename1,
    size_t t_typesize2, const char* s_typename2)
{
    bool_t t_registered1 = false;
    bool_t t_registered2 = false;

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

    /* test the type1 and type2 is registered or not */
    t_registered1 = _type_is_registered(t_typesize1, s_typename1);
    t_registered2 = _type_is_registered(t_typesize2, s_typename2);

    /* type1 and type2 all unregistered */
    if(!t_registered1 && !t_registered2)
    {
        return false;
    }
    /* type1 and type2 all registered */
    else if(t_registered1 && t_registered2)
    {
        _typenode_t* pt_node1 = NULL;
        _typenode_t* pt_node2 = NULL;
        _type_t*     pt_type1 = NULL;
        _type_t*     pt_type2 = NULL;

        pt_node1 = _gt_typeregister._apt_bucket[_type_hash(t_typesize1, s_typename1)];
        pt_node2 = _gt_typeregister._apt_bucket[_type_hash(t_typesize2, s_typename2)]; 
        assert(pt_node1 != NULL && pt_node2 != NULL);

        while(pt_node1 != NULL)
        {
            if(strncmp(pt_node1->_sz_typename, s_typename1, _TYPE_NAME_SIZE) == 0)
            {
                pt_type1 = pt_node1->_pt_type;
                assert(pt_type1 != NULL);
                assert(pt_type1->_t_typesize == t_typesize1);
                break;
            }
            else
            {
                pt_node1 = pt_node1->_pt_next;
            }
        }
        assert(pt_node1 != NULL && pt_type1 != NULL);

        while(pt_node2 != NULL)
        {
            if(strncmp(pt_node2->_sz_typename, s_typename2, _TYPE_NAME_SIZE) == 0)
            {
                pt_type2 = pt_node2->_pt_type;
                assert(pt_type2 != NULL);
                assert(pt_type2->_t_typesize == t_typesize2);
                break;
            }
            else
            {
                pt_node2 = pt_node2->_pt_next;
            }
        }
        assert(pt_node2 != NULL && pt_type2 != NULL);

        /* is same registered type */
        if(pt_type1 == pt_type2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    /* only one type is registered */
    else
    {
        size_t       t_typesize = t_typesize1;
        size_t       t_pos = 0;
        char*        s_registeredname = NULL;
        char*        s_duplicatename = NULL;
        _typenode_t* pt_registered = NULL;
        _typenode_t* pt_duplicate = NULL;
        _type_t*     pt_type = NULL;

        /* type1 is registered and type2 is unregistered */
        if(t_registered1 && !t_registered2)
        {
            s_registeredname = (char*)s_typename1;
            s_duplicatename = (char*)s_typename2;
        }
        /* type1 is unregistered and type2 is registered */
        else
        {
            s_registeredname = (char*)s_typename2;
            s_duplicatename = (char*)s_typename1;
        }

        /* get the registered type pointer */
        pt_registered = _gt_typeregister._apt_bucket[_type_hash(t_typesize, s_registeredname)];
        assert(pt_registered != NULL);
        while(pt_registered != NULL)
        {
            if(strncmp(pt_registered->_sz_typename, s_registeredname, _TYPE_NAME_SIZE) == 0)
            {
                pt_type = pt_registered->_pt_type;
                assert(pt_type != NULL);
                assert(pt_type->_t_typesize == t_typesize);
                break;
            }
            else
            {
                pt_registered = pt_registered->_pt_next;
            }
        }
        assert(pt_registered != NULL && pt_type != NULL);

        /* malloc typenode for unregistered type */
        pt_duplicate = (_typenode_t*)allocate(
            &_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
        memset(pt_duplicate->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
        strncpy(pt_duplicate->_sz_typename, s_duplicatename, _TYPE_NAME_SIZE);

        pt_duplicate->_pt_type = pt_type;

        t_pos = _type_hash(t_typesize, s_duplicatename);
        pt_duplicate->_pt_next = _gt_typeregister._apt_bucket[t_pos];
        _gt_typeregister._apt_bucket[t_pos] = pt_duplicate;

        return true;
    }
}

/* default copy, less, and destroy function */
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
    assert(cpv_first != NULL && pv_output != NULL);
    pv_avoidwarning = (void*)cpv_input;
    *(bool_t*)pv_output = true;
}

static bool_t _type_is_registered(size_t t_typesize, const char* s_typename)
{
    _type_t*     pt_registered = NULL;
    _typenode_t* pt_node = NULL;

    if(strlen(s_typename) > _TYPE_NAME_SIZE)
    {
        return false;
    }

    /* get the registered type pointer */
    pt_node = _gt_typeregister._apt_bucket[_type_hash(t_typesize, s_typename)];
    if(pt_node != NULL)
    {
        while(pt_node != NULL)
        {
            if(strncmp(s_typename, pt_node->_sz_typename, _TYPE_NAME_SIZE) == 0)
            {
                pt_registered = pt_node->_pt_type;
                assert(pt_registered != NULL);
                assert(t_typesize == pt_registered->_t_typesize);
                break;
            }
            else
            {
                pt_node = pt_node->_pt_next;
            }
        }

        if(pt_registered != NULL)
        {
            assert(pt_node != NULL);
            return true;
        }
        else
        {
            assert(pt_node == NULL);
            return false;
        }
    }
    else
    {
        return false;
    }
}

static size_t _type_hash(size_t t_typesize, const char* s_typename)
{
    size_t t_namesum = 0;
    size_t t_namelen = strlen(s_typename);
    size_t t_i = 0;

    t_typesize = 0; /* avoid warning */
    for(t_i = 0; t_i < t_namelen; ++t_i)
    {
        t_namesum += (size_t)s_typename[t_i];
    }

    return t_namesum % _TYPE_REGISTER_BUCKET_COUNT;
}

static _typestyle_t _type_get_style(const char* s_typename)
{
    /* incomplete */
    /*char sz_normalname[_TYPE_NAME_SIZE + 1];*/

    if(strlen(s_typename) > _TYPE_NAME_SIZE)
    {
        return _TYPE_INVALID;
    }

    return _TYPE_INVALID;
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
    _type_register_cstl_container();
    
    _gt_typeregister._t_isinit = true;
}

static void _type_register_c_builtin(void)
{
    _typenode_t* pt_node = NULL;
    _type_t*     pt_type = NULL;
    size_t       t_pos = 0;

    /* 
     * register char type 
     */
    /* char type node */
    pt_type = (_type_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_type_t), 1);
    assert(pt_type != NULL);
    pt_type->_t_typesize = sizeof(char);
    memset(pt_type->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_node->_sz_typename, _CHAR_TYPE, _TYPE_NAME_SIZE);
    pt_type->_t_typecopy = _type_copy_char;
    pt_type->_t_typeless = _type_less_char;
    pt_type->_t_typedestroy = _type_destroy_char;
    /* insert char node */
    pt_node = (_typenode_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
    assert(pt_node != NULL);
    memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_node->_sz_typename, _CHAR_TYPE, _TYPE_NAME_SIZE);
    t_pos = _type_hash(sizeof(char), _CHAR_TYPE);
    pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
    _gt_typeregister._apt_bucket[t_pos] = pt_node;
    pt_node->_pt_type = pt_type;
    /* insert signed char node */
    pt_node = (_typenode_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
    assert(pt_node != NULL);
    memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_node->_sz_typename, _SIGNED_CHAR_TYPE, _TYPE_NAME_SIZE);
    t_pos = _type_hash(sizeof(signed char), _SIGNED_CHAR_TYPE);
    pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
    _gt_typeregister._apt_bucket[t_pos] = pt_node;
    pt_node->_pt_type = pt_type;

    /*
     * register unsigned char
     */
    /* unsigned char type node */
    pt_type = (_type_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_type_t), 1);
    assert(pt_type != NULL);
    pt_type->_t_typesize = sizeof(unsigned char);
    memset(pt_type->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_type->_sz_typename, _UNSIGNED_CHAR_TYPE, _TYPE_NAME_SIZE);
    pt_type->_t_typecopy = _type_copy_uchar;
    pt_type->_t_typeless = _type_less_uchar;
    pt_type->_t_typedestroy = _type_destroy_uchar;
    /* insert unsigned char */
    pt_node = (_typenode_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
    assert(pt_node != NULL);
    memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_node->_sz_typename, _UNSIGNED_CHAR_TYPE, _TYPE_NAME_SIZE);
    t_pos = _type_hash(sizeof(unsigned char), _UNSIGNED_CHAR_TYPE);
    pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
    _gt_typeregister._apt_bucket[t_pos] = pt_node;
    pt_node->_pt_type = pt_type;

    /*
     * register short
     */
    /* short type node */
    pt_type = (_type_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_type_t), 1);
    assert(pt_type != NULL);
    pt_type->_t_typesize = sizeof(short);
    memset(pt_type->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_type->_sz_typename, _SHORT_TYPE, _TYPE_NAME_SIZE);
    pt_type->_t_typecopy = _type_copy_short;
    pt_type->_t_typeless = _type_less_short;
    pt_type->_t_typedestroy = _type_destroy_short;
    /* insert short */
    pt_node = (_typenode_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
    assert(pt_node != NULL);
    memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_node->_sz_typename, _SHORT_TYPE, _TYPE_NAME_SIZE);
    t_pos = _type_hash(sizeof(short), _SHORT_TYPE);
    pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
    _gt_typeregister._apt_bucket[t_pos] = pt_node;
    pt_node->_pt_type = pt_type;
    /* insert short int */
    pt_node = (_typenode_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
    assert(pt_node != NULL);
    memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_node->_sz_typename, _SHORT_INT_TYPE, _TYPE_NAME_SIZE);
    t_pos = _type_hash(sizeof(short int), _SHORT_INT_TYPE);
    pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
    _gt_typeregister._apt_bucket[t_pos] = pt_node;
    pt_node->_pt_type = pt_type;
    /* insert signed short */
    pt_node = (_typenode_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
    assert(pt_node != NULL);
    memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_node->_sz_typename, _SIGNED_SHORT_TYPE, _TYPE_NAME_SIZE);
    t_pos = _type_hash(sizeof(signed short), _SIGNED_SHORT_TYPE);
    pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
    _gt_typeregister._apt_bucket[t_pos] = pt_node;
    pt_node->_pt_type = pt_type;
    /* insert signed short int */
    pt_node = (_typenode_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
    assert(pt_node != NULL);
    memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_node->_sz_typename, _SIGNED_SHORT_INT_TYPE, _TYPE_NAME_SIZE);
    t_pos = _type_hash(sizeof(signed short int), _SIGNED_SHORT_INT_TYPE);
    pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
    _gt_typeregister._apt_bucket[t_pos] = pt_node;
    pt_node->_pt_type = pt_type;

    /*
     * register unsigned short
     */
    /* unsigned short type node */
    pt_type = (_type_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_type_t), 1);
    assert(pt_type != NULL);
    pt_type->_t_typesize = sizeof(unsigned short);
    memset(pt_type->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_type->_sz_typename, _UNSIGNED_SHORT_TYPE, _TYPE_NAME_SIZE);
    pt_type->_t_typecopy = _type_copy_ushort;
    pt_type->_t_typeless = _type_less_ushort;
    pt_type->_t_typedestroy = _type_destroy_ushort;
    /* insert unsigned short */
    pt_node = (_typenode_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
    assert(pt_node != NULL);
    memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_node->_sz_typename, _UNSIGNED_SHORT_TYPE, _TYPE_NAME_SIZE);
    t_pos = _type_hash(sizeof(unsigned short), _UNSIGNED_SHORT_TYPE);
    pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
    _gt_typeregister._apt_bucket[t_pos] = pt_node;
    pt_node->_pt_type = pt_type;
    /* insert unsigned short int */
    pt_node = (_typenode_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
    assert(pt_node != NULL);
    memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_node->_sz_typename, _UNSIGNED_SHORT_INT_TYPE, _TYPE_NAME_SIZE);
    t_pos = _type_hash(sizeof(unsigned short int), _UNSIGNED_SHORT_INT_TYPE);
    pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
    _gt_typeregister._apt_bucket[t_pos] = pt_node;
    pt_node->_pt_type = pt_type;

    /*
     * register int
     */
    /* int type node */
    pt_type = (_type_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_type_t), 1);
    assert(pt_type != NULL);
    pt_type->_t_typesize = sizeof(int);
    memset(pt_type->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_type->_sz_typename, _INT_TYPE, _TYPE_NAME_SIZE);
    pt_type->_t_typecopy = _type_copy_int;
    pt_type->_t_typeless = _type_less_int;
    pt_type->_t_typedestroy = _type_destroy_int;
    /* insert int */
    pt_node = (_typenode_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
    assert(pt_node != NULL);
    memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_node->_sz_typename, _INT_TYPE, _TYPE_NAME_SIZE);
    t_pos = _type_hash(sizeof(int), _INT_TYPE);
    pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
    _gt_typeregister._apt_bucket[t_pos] = pt_node;
    pt_node->_pt_type = pt_type;
    /* insert signed */
    pt_node = (_typenode_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
    assert(pt_node != NULL);
    memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_node->_sz_typename, _SIGNED_TYPE, _TYPE_NAME_SIZE);
    t_pos = _type_hash(sizeof(signed), _SIGNED_TYPE);
    pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
    _gt_typeregister._apt_bucket[t_pos] = pt_node;
    pt_node->_pt_type = pt_type;
    /* insert signed int */
    pt_node = (_typenode_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
    assert(pt_node != NULL);
    memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_node->_sz_typename, _SIGNED_INT_TYPE, _TYPE_NAME_SIZE);
    t_pos = _type_hash(sizeof(signed int), _SIGNED_INT_TYPE);
    pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
    _gt_typeregister._apt_bucket[t_pos] = pt_node;
    pt_node->_pt_type = pt_type;

    /* 
     * register unsigned int
     */
    /* unsigned int type node */
    pt_type = (_type_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_type_t), 1);
    assert(pt_type != NULL);
    pt_type->_t_typesize = sizeof(unsigned int);
    memset(pt_type->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_type->_sz_typename, _UNSIGNED_INT_TYPE, _TYPE_NAME_SIZE);
    pt_type->_t_typecopy = _type_copy_uint;
    pt_type->_t_typeless = _type_less_uint;
    pt_type->_t_typedestroy = _type_destroy_uint;
    /* insert unsigned int */
    pt_node = (_typenode_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
    assert(pt_node != NULL);
    memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_node->_sz_typename, _UNSIGNED_INT_TYPE, _TYPE_NAME_SIZE);
    t_pos = _type_hash(sizeof(unsigned int), _UNSIGNED_INT_TYPE);
    pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
    _gt_typeregister._apt_bucket[t_pos] = pt_node;
    pt_node->_pt_type = pt_type;
    /* insert unsigned */
    pt_node = (_typenode_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
    assert(pt_node != NULL);
    memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_node->_sz_typename, _UNSIGNED_TYPE, _TYPE_NAME_SIZE);
    t_pos = _type_hash(sizeof(unsigned), _UNSIGNED_TYPE);
    pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
    _gt_typeregister._apt_bucket[t_pos] = pt_node;
    pt_node->_pt_type = pt_type;

    /*
     * register long
     */
    /* long type node */
    pt_type = (_type_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_type_t), 1);
    assert(pt_type != NULL);
    pt_type->_t_typesize = sizeof(long);
    memset(pt_type->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_type->_sz_typename, _LONG_TYPE, _TYPE_NAME_SIZE);
    pt_type->_t_typecopy = _type_copy_long;
    pt_type->_t_typeless = _type_less_long;
    pt_type->_t_typedestroy = _type_destroy_long;
    /* insert long */
    pt_node = (_typenode_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
    assert(pt_node != NULL);
    memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_node->_sz_typename, _LONG_TYPE, _TYPE_NAME_SIZE);
    t_pos = _type_hash(sizeof(long), _LONG_TYPE);
    pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
    _gt_typeregister._apt_bucket[t_pos] = pt_node;
    pt_node->_pt_type = pt_type;
    /* insert long int */
    pt_node = (_typenode_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
    assert(pt_node != NULL);
    memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_node->_sz_typename, _LONG_INT_TYPE, _TYPE_NAME_SIZE);
    t_pos = _type_hash(sizeof(long int), _LONG_INT_TYPE);
    pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
    _gt_typeregister._apt_bucket[t_pos] = pt_node;
    pt_node->_pt_type = pt_type;
    /* insert signed long */
    pt_node = (_typenode_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
    assert(pt_node != NULL);
    memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_node->_sz_typename, _SIGNED_LONG_TYPE, _TYPE_NAME_SIZE);
    t_pos = _type_hash(sizeof(signed long), _SIGNED_LONG_TYPE);
    pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
    _gt_typeregister._apt_bucket[t_pos] = pt_node;
    pt_node->_pt_type = pt_type;
    /* insert signed long int */
    pt_node = (_typenode_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
    assert(pt_node != NULL);
    memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_node->_sz_typename, _SIGNED_LONG_INT_TYPE, _TYPE_NAME_SIZE);
    t_pos = _type_hash(sizeof(signed long int), _SIGNED_LONG_INT_TYPE);
    pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
    _gt_typeregister._apt_bucket[t_pos] = pt_node;
    pt_node->_pt_type = pt_type;

    /*
     * register unsigned long
     */
    /* unsigned long type node */
    pt_type = (_type_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_type_t), 1);
    assert(pt_type != NULL);
    pt_type->_t_typesize = sizeof(unsigned long);
    memset(pt_type->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_type->_sz_typename, _UNSIGNED_LONG_TYPE, _TYPE_NAME_SIZE);
    pt_type->_t_typecopy = _type_copy_ulong;
    pt_type->_t_typeless = _type_less_ulong;
    pt_type->_t_typedestroy = _type_destroy_ulong;
    /* insert unsigned long */
    pt_node = (_typenode_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
    assert(pt_node != NULL);
    memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_node->_sz_typename, _UNSIGNED_LONG_TYPE, _TYPE_NAME_SIZE);
    t_pos = _type_hash(sizeof(unsigned long), _UNSIGNED_LONG_TYPE);
    pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
    _gt_typeregister._apt_bucket[t_pos] = pt_node;
    pt_node->_pt_type = pt_type;
    /* insert unsigned long int */
    pt_node = (_typenode_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
    assert(pt_node != NULL);
    memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_node->_sz_typename, _UNSIGNED_LONG_INT_TYPE, _TYPE_NAME_SIZE);
    t_pos = _type_hash(sizeof(unsigned long int), _UNSIGNED_LONG_INT_TYPE);
    pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
    _gt_typeregister._apt_bucket[t_pos] = pt_node;
    pt_node->_pt_type = pt_type;

    /*
     * register float
     */
    /* float type node */
    pt_type = (_type_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_type_t), 1);
    assert(pt_type != NULL);
    pt_type->_t_typesize = sizeof(float);
    memset(pt_type->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_type->_sz_typename, _FLOAT_TYPE, _TYPE_NAME_SIZE);
    pt_type->_t_typecopy = _type_copy_float;
    pt_type->_t_typeless = _type_less_float;
    pt_type->_t_typedestroy = _type_destroy_float;
    /* insert float */
    pt_node = (_typenode_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
    assert(pt_node != NULL);
    memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_node->_sz_typename, _FLOAT_TYPE, _TYPE_NAME_SIZE);
    t_pos = _type_hash(sizeof(float), _FLOAT_TYPE);
    pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
    _gt_typeregister._apt_bucket[t_pos] = pt_node;
    pt_node->_pt_type = pt_type;

    /*
     * register double
     */
    /* double type node */
    pt_type = (_type_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_type_t), 1);
    assert(pt_type != NULL);
    pt_type->_t_typesize = sizeof(double);
    memset(pt_type->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_type->_sz_typename, _DOUBLE_TYPE, _TYPE_NAME_SIZE);
    pt_type->_t_typecopy = _type_copy_double;
    pt_type->_t_typeless = _type_less_double;
    pt_type->_t_typedestroy = _type_destroy_double;
    /* insert double */
    pt_node = (_typenode_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
    assert(pt_node != NULL);
    memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_node->_sz_typename, _DOUBLE_TYPE, _TYPE_NAME_SIZE);
    t_pos = _type_hash(sizeof(double), _DOUBLE_TYPE);
    pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
    _gt_typeregister._apt_bucket[t_pos] = pt_node;
    pt_node->_pt_type = pt_type;

    /*
     * register long double
     */
    /* long double type node */
    pt_type = (_type_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_type_t), 1);
    assert(pt_type != NULL);
    pt_type->_t_typesize = sizeof(long double);
    memset(pt_type->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_type->_sz_typename, _LONG_DOUBLE_TYPE, _TYPE_NAME_SIZE);
    pt_type->_t_typecopy = _type_copy_long_double;
    pt_type->_t_typeless = _type_less_long_double;
    pt_type->_t_typedestroy = _type_destroy_long_double;
    /* insert long double */
    pt_node = (_typenode_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
    assert(pt_node != NULL);
    memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_node->_sz_typename, _LONG_DOUBLE_TYPE, _TYPE_NAME_SIZE);
    t_pos = _type_hash(sizeof(long double), _LONG_DOUBLE_TYPE);
    pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
    _gt_typeregister._apt_bucket[t_pos] = pt_node;
    pt_node->_pt_type = pt_type;

    /*
     * register bool_t
     */
    /* bool_t type node */
    pt_type = (_type_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_type_t), 1);
    assert(pt_type != NULL);
    pt_type->_t_typesize = sizeof(bool_t);
    memset(pt_type->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_type->_sz_typename, _BOOL_TYPE, _TYPE_NAME_SIZE);
    pt_type->_t_typecopy = _type_copy_bool;
    pt_type->_t_typeless = _type_less_bool;
    pt_type->_t_typedestroy = _type_destroy_bool;
    /* insert bool_t */
    pt_node = (_typenode_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
    assert(pt_node != NULL);
    memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_node->_sz_typename, _BOOL_TYPE, _TYPE_NAME_SIZE);
    t_pos = _type_hash(sizeof(bool_t), _BOOL_TYPE);
    pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
    _gt_typeregister._apt_bucket[t_pos] = pt_node;
    pt_node->_pt_type = pt_type;

    /*
     * register char*
     */
    /* char* type node */
    pt_type = (_type_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_type_t), 1);
    assert(pt_type != NULL);
    pt_type->_t_typesize = sizeof(string_t);
    memset(pt_type->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_type->_sz_typename, _C_STRING_TYPE, _TYPE_NAME_SIZE);
    pt_type->_t_typecopy = _type_copy_cstr;
    pt_type->_t_typeless = _type_less_cstr;
    pt_type->_t_typedestroy = _type_destroy_cstr;
    /* insert char* */
    pt_node = (_typenode_t*)allocate(&_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
    assert(pt_node != NULL);
    memset(pt_node->_sz_typename, '\0', _TYPE_NAME_SIZE+1);
    strncpy(pt_node->_sz_typename, _C_STRING_TYPE, _TYPE_NAME_SIZE);
    t_pos = _type_hash(sizeof(string_t), _C_STRING_TYPE);
    pt_node->_pt_next = _gt_typeregister._apt_bucket[t_pos];
    _gt_typeregister._apt_bucket[t_pos] = pt_node;
    pt_node->_pt_type = pt_type;
}

static void _type_register_cstl_container(void)
{
}

/*
 * the cstl builtin copy, compare destroy function for c builtin type and cstl containers.
 */
/* c builtin */
/* char */
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
    vector_destroy((vector_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* list_t */
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
    list_destroy((list_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* slist_t */
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
    slist_destroy((slist_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* deque_t */
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
    deque_destroy((deque_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* stack_t */
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
    stack_destroy((stack_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* queue_t */
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
    queue_destroy((queue_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* priority_queue_t */
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
    set_destroy((set_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* map_t */
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
    map_destroy((map_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* multiset_t */
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
    multiset_destroy((multiset_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* multimap_t */
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
    multimap_destroy((multimap_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* hash_set_t */
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
    hash_set_destroy((hash_set_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* hash_map_t */
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
    hash_map_destroy((hash_map_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* hash_multiset_t */
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
    hash_multiset_destroy((hash_multiset_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* hash_multimap_t */
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
    pair_destroy((pair_t*)cpv_input);
    *(bool_t*)pv_output = true;
}
/* string_t */
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
    string_destroy((string_t*)cpv_input);
    *(bool_t*)pv_output = true;
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

