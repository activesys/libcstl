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

#include "cstl_types.h"

/** local constant declaration and local macro section **/

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

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
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

