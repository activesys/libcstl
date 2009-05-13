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
 *                             | _t_typecopy = abc_copy       | "registed type abc_t"
 *                             | _t_typecmp = abc_cmp         |
 *                             | _t_typedestroy = abc_destroy |
 *                             +------------------------------+
 */
static _typeregister_t _gt_typeregister = {false, {NULL}, {{NULL}, NULL, NULL, 0, 0, 0}};

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
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

/* register hash function */
static size_t _type_hash(size_t t_typesize, const char* s_typename);
/* init the register and register c builtin type and cstl builtin type */
static void _type_init(void);
/* test the type is registed or not */
static bool_t _type_is_registed(size_t t_typesize, const char* s_typename);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
bool_t _type_register(
    size_t t_typesize, const char* s_typename,
    binary_function_t t_typecopy,
    binary_function_t t_typecmp,
    unary_function_t t_typedestroy)
{
    if(!_gt_typeregister._t_isinit)
    {
        _type_init();
    }

    /* if the type is registed */
    if(_type_is_registed(t_typesize, s_typename) || strlen(s_typename) > _TYPE_NAME_SIZE)
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

        memset(pt_node, 1, sizeof(_typenode_t));
        memset(pt_type, 1, sizeof(_type_t));

        /* register the new type */
        strncpy(pt_node->_sz_typename, s_typename, _TYPE_NAME_SIZE);
        strncpy(pt_type->_sz_typename, s_typename, _TYPE_NAME_SIZE);
        pt_type->_t_typesize = t_typesize;
        pt_type->_t_typecopy = t_typecopy;
        pt_type->_t_typecmp = t_typecmp;
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

    /* get the registed type pointer */
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
    bool_t t_registed1 = false;
    bool_t t_registed2 = false;

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

    /* test the type1 and type2 is registed or not */
    t_registed1 = _type_is_registed(t_typesize1, s_typename1);
    t_registed2 = _type_is_registed(t_typesize2, s_typename2);

    /* type1 and type2 all not registed */
    if(!t_registed1 && !t_registed2)
    {
        return false;
    }
    /* type1 and type2 all registed */
    else if(t_registed1 && t_registed2)
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

        /* is same registed type */
        if(pt_type1 == pt_type2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    /* only one type is registed */
    else
    {
        size_t       t_typesize = t_typesize1;
        size_t       t_pos = 0;
        char*        s_registedname = NULL;
        char*        s_duplicatename = NULL;
        _typenode_t* pt_registed = NULL;
        _typenode_t* pt_duplicate = NULL;
        _type_t*     pt_type = NULL;

        /* type1 is registed and type2 is not registed */
        if(t_registed1 && !t_registed2)
        {
            s_registedname = (char*)s_typename1;
            s_duplicatename = (char*)s_typename2;
        }
        /* type1 is not registed and type2 is registed */
        else
        {
            s_registedname = (char*)s_typename2;
            s_duplicatename = (char*)s_typename1;
        }

        /* get the registed type pointer */
        pt_registed = _gt_typeregister._apt_bucket[_type_hash(t_typesize, s_registedname)];
        assert(pt_registed != NULL);
        while(pt_registed != NULL)
        {
            if(strncmp(pt_registed->_sz_typename, s_registedname, _TYPE_NAME_SIZE) == 0)
            {
                pt_type = pt_registed->_pt_type;
                assert(pt_type != NULL);
                assert(pt_type->_t_typesize == t_typesize);
                break;
            }
            else
            {
                pt_registed = pt_registed->_pt_next;
            }
        }
        assert(pt_registed != NULL && pt_type != NULL);

        /* malloc typenode for not registed type */
        pt_duplicate = (_typenode_t*)allocate(
            &_gt_typeregister._t_allocator, sizeof(_typenode_t), 1);
        memset(pt_duplicate, 1, sizeof(_typenode_t));
        strncpy(pt_duplicate->_sz_typename, s_duplicatename, _TYPE_NAME_SIZE);

        pt_duplicate->_pt_type = pt_type;

        t_pos = _type_hash(t_typesize, s_duplicatename);
        pt_duplicate->_pt_next = _gt_typeregister._apt_bucket[t_pos];
        _gt_typeregister._apt_bucket[t_pos] = pt_duplicate;

        return true;
    }
}

static bool_t _type_is_registed(size_t t_typesize, const char* s_typename)
{
    _type_t*     pt_registed = NULL;
    _typenode_t* pt_node = NULL;

    if(strlen(s_typename) > _TYPE_NAME_SIZE)
    {
        return false;
    }

    /* get the registed type pointer */
    pt_node = _gt_typeregister._apt_bucket[_type_hash(t_typesize, s_typename)];
    if(pt_node != NULL)
    {
        while(pt_node != NULL)
        {
            if(strncmp(s_typename, pt_node->_sz_typename, _TYPE_NAME_SIZE) == 0)
            {
                pt_registed = pt_node->_pt_type;
                assert(pt_registed != NULL);
                assert(t_typesize == pt_registed->_t_typesize);
                break;
            }
            else
            {
                pt_node = pt_node->_pt_next;
            }
        }

        if(pt_registed != NULL)
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

static void _type_init(void)
{
}

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

