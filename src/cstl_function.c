/*
 *  The implementation of function.
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
#include <time.h>

#include "cstl_types.h"
#include "citerator.h"
#include "cstl_tools.h"
#include "cstl_function.h"
#include "cstl_function_private.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* private function */
unary_function_t _fun_get_unary(const char* s_typename, fun_unary_type_t t_funtype)
{
    char sz_builtin[_ELEM_TYPE_NAME_SIZE + 1];

    assert(s_typename != NULL);

    _get_builtin_type(s_typename, sz_builtin);
    /* char */
    if(strncmp(sz_builtin, _CHAR_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
       strncmp(sz_builtin, _SIGNED_CHAR_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        if(t_funtype == _NEGATE_FUN)
        {
            return fun_negate_char;
        }
        else if(t_funtype == _INCREASE_FUN)
        {
            return _fun_increase_char;
        }
    }
    /* unsigned char */
    else if(strncmp(sz_builtin, _UNSIGNED_CHAR_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        if(t_funtype == _INCREASE_FUN)
        {
            return _fun_increase_uchar;
        }
    }
    /* short */
    else if(strncmp(sz_builtin, _SHORT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SHORT_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SIGNED_SHORT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SIGNED_SHORT_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        if(t_funtype == _NEGATE_FUN)
        {
            return fun_negate_short;
        }
        else if(t_funtype == _INCREASE_FUN)
        {
            return _fun_increase_short;
        }
    }
    /* unsigned short */
    else if(strncmp(sz_builtin, _UNSIGNED_SHORT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _UNSIGNED_SHORT_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        if(t_funtype == _INCREASE_FUN)
        {
            return _fun_increase_ushort;
        }
    }
    /* int */
    else if(strncmp(sz_builtin, _INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SIGNED_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SIGNED_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        if(t_funtype == _NEGATE_FUN)
        {
            return fun_negate_int;
        }
        else if(t_funtype == _INCREASE_FUN)
        {
            return _fun_increase_int;
        }
    }
    /* unsigned int */
    else if(strncmp(sz_builtin, _UNSIGNED_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _UNSIGNED_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        if(t_funtype == _INCREASE_FUN)
        {
            return _fun_increase_uint;
        }
    }
    /* long */
    else if(strncmp(sz_builtin, _LONG_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _LONG_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SIGNED_LONG_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SIGNED_LONG_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        if(t_funtype == _NEGATE_FUN)
        {
            return fun_negate_long;
        }
        else if(t_funtype == _INCREASE_FUN)
        {
            return _fun_increase_long;
        }
    }
    /* unsigned long */
    else if(strncmp(sz_builtin, _UNSIGNED_LONG_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _UNSIGNED_LONG_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        if(t_funtype == _INCREASE_FUN)
        {
            return _fun_increase_ulong;
        }
    }
    /* float */
    else if(strncmp(sz_builtin, _FLOAT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        if(t_funtype == _NEGATE_FUN)
        {
            return fun_negate_float;
        }
        else if(t_funtype == _INCREASE_FUN)
        {
            return _fun_increase_float;
        }
    }
    /* double */
    else if(strncmp(sz_builtin, _DOUBLE_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        if(t_funtype == _NEGATE_FUN)
        {
            return fun_negate_double;
        }
        else if(t_funtype == _INCREASE_FUN)
        {
            return _fun_increase_double;
        }
    }
    /* bool_t */
    else if(strncmp(sz_builtin, _BOOL_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        if(t_funtype == _LOGICAL_NOT_FUN)
        {
            return fun_logical_not_bool;
        }
    }

    return fun_default_unary;
}

binary_function_t _fun_get_binary(const char* s_typename, fun_binary_type_t t_funtype)
{
    char sz_builtin[_ELEM_TYPE_NAME_SIZE + 1];

    assert(s_typename != NULL);

    _get_builtin_type(s_typename, sz_builtin);
    /* char */
    if(strncmp(sz_builtin, _CHAR_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
       strncmp(sz_builtin, _SIGNED_CHAR_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _PLUS_FUN:
            return fun_plus_char;
            break;
        case _MINUS_FUN:
            return fun_minus_char;
            break;
        case _MULTIPLIES_FUN:
            return fun_multiplies_char;
            break;
        case _DIVIDES_FUN:
            return fun_divides_char;
            break;
        case _MODULUS_FUN:
            return fun_modulus_char;
            break;
        case _EQUAL_FUN:
            return fun_equal_char;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_char;
            break;
        case _GREAT_FUN:
            return fun_great_char;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_char;
            break;
        case _LESS_FUN:
            return fun_less_char;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_char;
            break;
        default:
            break;
        }
    }
    /* unsigned char */
    else if(strncmp(sz_builtin, _UNSIGNED_CHAR_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _PLUS_FUN:
            return fun_plus_uchar;
            break;
        case _MINUS_FUN:
            return fun_minus_uchar;
            break;
        case _MULTIPLIES_FUN:
            return fun_multiplies_uchar;
            break;
        case _DIVIDES_FUN:
            return fun_divides_uchar;
            break;
        case _MODULUS_FUN:
            return fun_modulus_uchar;
            break;
        case _EQUAL_FUN:
            return fun_equal_uchar;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_uchar;
            break;
        case _GREAT_FUN:
            return fun_great_uchar;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_uchar;
            break;
        case _LESS_FUN:
            return fun_less_uchar;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_uchar;
            break;
        default:
            break;
        }
    }
    /* short */
    else if(strncmp(sz_builtin, _SHORT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SHORT_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SIGNED_SHORT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SIGNED_SHORT_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _PLUS_FUN:
            return fun_plus_short;
            break;
        case _MINUS_FUN:
            return fun_minus_short;
            break;
        case _MULTIPLIES_FUN:
            return fun_multiplies_short;
            break;
        case _DIVIDES_FUN:
            return fun_divides_short;
            break;
        case _MODULUS_FUN:
            return fun_modulus_short;
            break;
        case _EQUAL_FUN:
            return fun_equal_short;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_short;
            break;
        case _GREAT_FUN:
            return fun_great_short;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_short;
            break;
        case _LESS_FUN:
            return fun_less_short;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_short;
            break;
        default:
            break;
        }
    }
    /* unsigned short */
    else if(strncmp(sz_builtin, _UNSIGNED_SHORT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _UNSIGNED_SHORT_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _PLUS_FUN:
            return fun_plus_ushort;
            break;
        case _MINUS_FUN:
            return fun_minus_ushort;
            break;
        case _MULTIPLIES_FUN:
            return fun_multiplies_ushort;
            break;
        case _DIVIDES_FUN:
            return fun_divides_ushort;
            break;
        case _MODULUS_FUN:
            return fun_modulus_ushort;
            break;
        case _EQUAL_FUN:
            return fun_equal_ushort;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_ushort;
            break;
        case _GREAT_FUN:
            return fun_great_ushort;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_ushort;
            break;
        case _LESS_FUN:
            return fun_less_ushort;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_ushort;
            break;
        default:
            break;
        }
    }
    /* int */
    else if(strncmp(sz_builtin, _INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SIGNED_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SIGNED_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _PLUS_FUN:
            return fun_plus_int;
            break;
        case _MINUS_FUN:
            return fun_minus_int;
            break;
        case _MULTIPLIES_FUN:
            return fun_multiplies_int;
            break;
        case _DIVIDES_FUN:
            return fun_divides_int;
            break;
        case _MODULUS_FUN:
            return fun_modulus_int;
            break;
        case _EQUAL_FUN:
            return fun_equal_int;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_int;
            break;
        case _GREAT_FUN:
            return fun_great_int;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_int;
            break;
        case _LESS_FUN:
            return fun_less_int;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_int;
            break;
        default:
            break;
        }
    }
    /* unsigned int */
    else if(strncmp(sz_builtin, _UNSIGNED_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _UNSIGNED_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _PLUS_FUN:
            return fun_plus_uint;
            break;
        case _MINUS_FUN:
            return fun_minus_uint;
            break;
        case _MULTIPLIES_FUN:
            return fun_multiplies_uint;
            break;
        case _DIVIDES_FUN:
            return fun_divides_uint;
            break;
        case _MODULUS_FUN:
            return fun_modulus_uint;
            break;
        case _EQUAL_FUN:
            return fun_equal_uint;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_uint;
            break;
        case _GREAT_FUN:
            return fun_great_uint;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_uint;
            break;
        case _LESS_FUN:
            return fun_less_uint;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_uint;
            break;
        default:
            break;
        }
    }
    /* long */
    else if(strncmp(sz_builtin, _LONG_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _LONG_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SIGNED_LONG_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _SIGNED_LONG_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _PLUS_FUN:
            return fun_plus_long;
            break;
        case _MINUS_FUN:
            return fun_minus_long;
            break;
        case _MULTIPLIES_FUN:
            return fun_multiplies_long;
            break;
        case _DIVIDES_FUN:
            return fun_divides_long;
            break;
        case _MODULUS_FUN:
            return fun_modulus_long;
            break;
        case _EQUAL_FUN:
            return fun_equal_long;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_long;
            break;
        case _GREAT_FUN:
            return fun_great_long;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_long;
            break;
        case _LESS_FUN:
            return fun_less_long;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_long;
            break;
        default:
            break;
        }
    }
    /* unsigned long */
    else if(strncmp(sz_builtin, _UNSIGNED_LONG_TYPE, _ELEM_TYPE_NAME_SIZE) == 0 ||
            strncmp(sz_builtin, _UNSIGNED_LONG_INT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _PLUS_FUN:
            return fun_plus_ulong;
            break;
        case _MINUS_FUN:
            return fun_minus_ulong;
            break;
        case _MULTIPLIES_FUN:
            return fun_multiplies_ulong;
            break;
        case _DIVIDES_FUN:
            return fun_divides_ulong;
            break;
        case _MODULUS_FUN:
            return fun_modulus_ulong;
            break;
        case _EQUAL_FUN:
            return fun_equal_ulong;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_ulong;
            break;
        case _GREAT_FUN:
            return fun_great_ulong;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_ulong;
            break;
        case _LESS_FUN:
            return fun_less_ulong;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_ulong;
            break;
        default:
            break;
        }
    }
    /* float */
    else if(strncmp(sz_builtin, _FLOAT_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _PLUS_FUN:
            return fun_plus_float;
            break;
        case _MINUS_FUN:
            return fun_minus_float;
            break;
        case _MULTIPLIES_FUN:
            return fun_multiplies_float;
            break;
        case _DIVIDES_FUN:
            return fun_divides_float;
            break;
        case _EQUAL_FUN:
            return fun_equal_float;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_float;
            break;
        case _GREAT_FUN:
            return fun_great_float;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_float;
            break;
        case _LESS_FUN:
            return fun_less_float;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_float;
            break;
        default:
            break;
        }
    }
    /* double */
    else if(strncmp(sz_builtin, _DOUBLE_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _PLUS_FUN:
            return fun_plus_double;
            break;
        case _MINUS_FUN:
            return fun_minus_double;
            break;
        case _MULTIPLIES_FUN:
            return fun_multiplies_double;
            break;
        case _DIVIDES_FUN:
            return fun_divides_double;
            break;
        case _EQUAL_FUN:
            return fun_equal_double;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_double;
            break;
        case _GREAT_FUN:
            return fun_great_double;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_double;
            break;
        case _LESS_FUN:
            return fun_less_double;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_double;
            break;
        default:
            break;
        }
    }
    /* bool_t */
    else if(strncmp(sz_builtin, _BOOL_TYPE, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _LOGICAL_AND_FUN:
            return fun_logical_and_bool;
            break;
        case _LOGICAL_OR_FUN:
            return fun_logical_or_bool;
            break;
        default:
            break;
        }
    }

    return fun_default_binary;
}

/* 
 * There is special condition in binary function 
 * when the second parameter is NULL.
 */
/* arithmetic */
/* plus */
void fun_plus_char(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(char*)pv_output = *(char*)cpv_first + *(char*)cpv_second;
}

void fun_plus_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned char*)pv_output = *(unsigned char*)cpv_first + *(unsigned char*)cpv_second;
}

void fun_plus_short(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(short*)pv_output = *(short*)cpv_first + *(short*)cpv_second;
}

void fun_plus_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned short*)pv_output = *(unsigned short*)cpv_first + *(unsigned short*)cpv_second;
}

void fun_plus_int(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(int*)pv_output = *(int*)cpv_first + *(int*)cpv_second;
}

void fun_plus_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned int*)pv_output = *(unsigned int*)cpv_first + *(unsigned int*)cpv_second;
}

void fun_plus_long(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(long*)pv_output = *(long*)cpv_first + *(long*)cpv_second;
}

void fun_plus_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned long*)pv_output = *(unsigned long*)cpv_first + *(unsigned long*)cpv_second;
}

void fun_plus_float(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(float*)pv_output = *(float*)cpv_first + *(float*)cpv_second;
}

void fun_plus_double(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(double*)pv_output = *(double*)cpv_first + *(double*)cpv_second;
}

/* minus */
void fun_minus_char(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(char*)pv_output = *(char*)cpv_first - *(char*)cpv_second;
}

void fun_minus_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned char*)pv_output = *(unsigned char*)cpv_first - *(unsigned char*)cpv_second;
}

void fun_minus_short(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(short*)pv_output = *(short*)cpv_first - *(short*)cpv_second;
}

void fun_minus_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned short*)pv_output = *(unsigned short*)cpv_first - *(unsigned short*)cpv_second;
}

void fun_minus_int(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(int*)pv_output = *(int*)cpv_first - *(int*)cpv_second;
}

void fun_minus_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned int*)pv_output = *(unsigned int*)cpv_first - *(unsigned int*)cpv_second;
}

void fun_minus_long(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(long*)pv_output = *(long*)cpv_first - *(long*)cpv_second;
}

void fun_minus_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned long*)pv_output = *(unsigned long*)cpv_first - *(unsigned long*)cpv_second;
}

void fun_minus_float(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(float*)pv_output = *(float*)cpv_first - *(float*)cpv_second;
}

void fun_minus_double(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(double*)pv_output = *(double*)cpv_first - *(double*)cpv_second;
}

/* multiplies */
void fun_multiplies_char(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(char*)pv_output = *(char*)cpv_first * *(char*)cpv_second;
}

void fun_multiplies_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned char*)pv_output = *(unsigned char*)cpv_first * *(unsigned char*)cpv_second;
}

void fun_multiplies_short(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(short*)pv_output = *(short*)cpv_first * *(short*)cpv_second;
}

void fun_multiplies_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned short*)pv_output = *(unsigned short*)cpv_first * *(unsigned short*)cpv_second;
}

void fun_multiplies_int(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(int*)pv_output = *(int*)cpv_first * *(int*)cpv_second;
}

void fun_multiplies_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned int*)pv_output = *(unsigned int*)cpv_first * *(unsigned int*)cpv_second;
}

void fun_multiplies_long(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(long*)pv_output = *(long*)cpv_first * *(long*)cpv_second;
}

void fun_multiplies_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(unsigned long*)pv_output = *(unsigned long*)cpv_first * *(unsigned long*)cpv_second;
}

void fun_multiplies_float(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(float*)pv_output = *(float*)cpv_first * *(float*)cpv_second;
}

void fun_multiplies_double(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(double*)pv_output = *(double*)cpv_first * *(double*)cpv_second;
}

/* divides */
void fun_divides_char(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(char*)cpv_second != 0x00);
    *(char*)pv_output = *(char*)cpv_first / *(char*)cpv_second;
}

void fun_divides_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(unsigned char*)cpv_second != 0x00);
    *(unsigned char*)pv_output = *(unsigned char*)cpv_first / *(unsigned char*)cpv_second;
}

void fun_divides_short(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(short*)cpv_second != 0);
    *(short*)pv_output = *(short*)cpv_first / *(short*)cpv_second;
}

void fun_divides_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(unsigned short*)cpv_second != 0);
    *(unsigned short*)pv_output = *(unsigned short*)cpv_first / *(unsigned short*)cpv_second;
}

void fun_divides_int(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(int*)cpv_second != 0);
    *(int*)pv_output = *(int*)cpv_first / *(int*)cpv_second;
}

void fun_divides_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(unsigned int*)cpv_second != 0);
    *(unsigned int*)pv_output = *(unsigned int*)cpv_first / *(unsigned int*)cpv_second;
}

void fun_divides_long(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(long*)cpv_second != 0);
    *(long*)pv_output = *(long*)cpv_first / *(long*)cpv_second;
}

void fun_divides_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(unsigned long*)cpv_second != 0);
    *(unsigned long*)pv_output = *(unsigned long*)cpv_first / *(unsigned long*)cpv_second;
}

void fun_divides_float(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(float*)cpv_second > FLT_EPSILON || *(float*)cpv_second < -FLT_EPSILON);
    *(float*)pv_output = *(float*)cpv_first / *(float*)cpv_second;
}

void fun_divides_double(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(double*)cpv_second > DBL_EPSILON || *(double*)cpv_second < -DBL_EPSILON);
    *(double*)pv_output = *(double*)cpv_first / *(double*)cpv_second;
}

/* modulus */
void fun_modulus_char(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(char*)cpv_second != 0x00);
    *(char*)pv_output = *(char*)cpv_first % *(char*)cpv_second;
}

void fun_modulus_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(unsigned char*)cpv_second != 0x00);
    *(unsigned char*)pv_output = *(unsigned char*)cpv_first % *(unsigned char*)cpv_second;
}

void fun_modulus_short(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(short*)cpv_second != 0);
    *(short*)pv_output = *(short*)cpv_first % *(short*)cpv_second;
}

void fun_modulus_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(unsigned short*)cpv_second != 0);
    *(unsigned short*)pv_output = *(unsigned short*)cpv_first % *(unsigned short*)cpv_second;
}

void fun_modulus_int(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(int*)cpv_second != 0);
    *(int*)pv_output = *(int*)cpv_first % *(int*)cpv_second;
}

void fun_modulus_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(unsigned int*)cpv_second != 0);
    *(unsigned int*)pv_output = *(unsigned int*)cpv_first % *(unsigned int*)cpv_second;
}

void fun_modulus_long(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(long*)cpv_second != 0);
    *(long*)pv_output = *(long*)cpv_first % *(long*)cpv_second;
}

void fun_modulus_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(unsigned long*)cpv_second != 0);
    *(unsigned long*)pv_output = *(unsigned long*)cpv_first % *(unsigned long*)cpv_second;
}

/* negation */
void fun_negate_char(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(char*)pv_output = -*(char*)cpv_input;
}

void fun_negate_short(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(short*)pv_output = -*(short*)cpv_input;
}

void fun_negate_int(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(int*)pv_output = -*(int*)cpv_input;
}

void fun_negate_long(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(long*)pv_output = -*(long*)cpv_input;
}

void fun_negate_float(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(float*)pv_output = -*(float*)cpv_input;
}

void fun_negate_double(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(double*)pv_output = -*(double*)cpv_input;
}

/* comparisons */
/* equality */
void fun_equal_char(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(char*)cpv_first == *(char*)cpv_second ? true : false;
}

void fun_equal_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(unsigned char*)cpv_first == *(unsigned char*)cpv_second ? true : false;
}

void fun_equal_short(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(short*)cpv_first == *(short*)cpv_second ? true : false;
}

void fun_equal_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(unsigned short*)cpv_first == *(unsigned short*)cpv_second ? true : false;
}

void fun_equal_int(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(int*)cpv_first == *(int*)cpv_second ? true : false;
}

void fun_equal_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(unsigned int*)cpv_first == *(unsigned int*)cpv_second ? true : false;
}

void fun_equal_long(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(long*)cpv_first == *(long*)cpv_second ? true : false;
}

void fun_equal_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(unsigned long*)cpv_first == *(unsigned long*)cpv_second ? true : false;
}

void fun_equal_float(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(float*)cpv_first - *(float*)cpv_second < FLT_EPSILON &&
        *(float*)cpv_first - *(float*)cpv_second > -FLT_EPSILON ? true : false;
}

void fun_equal_double(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(double*)cpv_first - *(double*)cpv_second < DBL_EPSILON &&
        *(double*)cpv_first - *(double*)cpv_second > -DBL_EPSILON ? true : false;
}

/* inequality */
void fun_not_equal_char(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(char*)cpv_first != *(char*)cpv_second ? true : false;
}

void fun_not_equal_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(unsigned char*)cpv_first != *(unsigned char*)cpv_second ? true : false;
}

void fun_not_equal_short(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(short*)cpv_first != *(short*)cpv_second ? true : false;
}

void fun_not_equal_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(unsigned short*)cpv_first != *(unsigned short*)cpv_second ? true : false;
}

void fun_not_equal_int(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(int*)cpv_first != *(int*)cpv_second ? true : false;
}

void fun_not_equal_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(unsigned int*)cpv_first != *(unsigned int*)cpv_second ? true : false;
}

void fun_not_equal_long(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(long*)cpv_first != *(long*)cpv_second ? true : false;
}

void fun_not_equal_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(unsigned long*)cpv_first != *(unsigned long*)cpv_second ? true : false;
}

void fun_not_equal_float(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(float*)cpv_first - *(float*)cpv_second >= FLT_EPSILON ||
        *(float*)cpv_first - *(float*)cpv_second <= -FLT_EPSILON ? true : false;
}

void fun_not_equal_double(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(double*)cpv_first - *(double*)cpv_second >= DBL_EPSILON ||
        *(double*)cpv_first - *(double*)cpv_second <= -DBL_EPSILON ? true : false;
}

/* greater */
void fun_great_char(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(char*)cpv_first > *(char*)cpv_second ? true : false;
}

void fun_great_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(unsigned char*)cpv_first > *(unsigned char*)cpv_second ? true : false;
}

void fun_great_short(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(short*)cpv_first > *(short*)cpv_second ? true : false;
}

void fun_great_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(unsigned short*)cpv_first > *(unsigned short*)cpv_second ? true : false;
}

void fun_great_int(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(int*)cpv_first > *(int*)cpv_second ? true : false;
}

void fun_great_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(unsigned int*)cpv_first > *(unsigned int*)cpv_second ? true : false;
}

void fun_great_long(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(long*)cpv_first > *(long*)cpv_second ? true : false;
}

void fun_great_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(unsigned long*)cpv_first > *(unsigned long*)cpv_second ? true : false;
}

void fun_great_float(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(float*)cpv_first - *(float*)cpv_second >= FLT_EPSILON ? true : false;
}

void fun_great_double(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(double*)cpv_first - *(double*)cpv_second >= DBL_EPSILON ? true : false;
}

/* greater or equal*/
void fun_great_equal_char(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(char*)cpv_first >= *(char*)cpv_second ? true : false;
}

void fun_great_equal_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(unsigned char*)cpv_first >= *(unsigned char*)cpv_second ? true : false;
}

void fun_great_equal_short(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(short*)cpv_first >= *(short*)cpv_second ? true : false;
}

void fun_great_equal_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(unsigned short*)cpv_first >= *(unsigned short*)cpv_second ? true : false;
}

void fun_great_equal_int(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(int*)cpv_first >= *(int*)cpv_second ? true : false;
}

void fun_great_equal_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(unsigned int*)cpv_first >= *(unsigned int*)cpv_second ? true : false;
}

void fun_great_equal_long(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(long*)cpv_first >= *(long*)cpv_second ? true : false;
}

void fun_great_equal_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(unsigned long*)cpv_first >= *(unsigned long*)cpv_second ? true : false;
}

void fun_great_equal_float(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(float*)cpv_first - *(float*)cpv_second > -FLT_EPSILON ? true : false;
}

void fun_great_equal_double(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(double*)cpv_first - *(double*)cpv_second > -DBL_EPSILON ? true : false;
}

/* less */
void fun_less_char(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(char*)cpv_first < *(char*)cpv_second ? true : false;
}

void fun_less_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(unsigned char*)cpv_first < *(unsigned char*)cpv_second ? true : false;
}

void fun_less_short(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(short*)cpv_first < *(short*)cpv_second ? true : false;
}

void fun_less_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(unsigned short*)cpv_first < *(unsigned short*)cpv_second ? true : false;
}

void fun_less_int(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(int*)cpv_first < *(int*)cpv_second ? true : false;
}

void fun_less_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(unsigned int*)cpv_first < *(unsigned int*)cpv_second ? true : false;
}

void fun_less_long(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(long*)cpv_first < *(long*)cpv_second ? true : false;
}

void fun_less_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(unsigned long*)cpv_first < *(unsigned long*)cpv_second ? true : false;
}

void fun_less_float(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(float*)cpv_first - *(float*)cpv_second < -FLT_EPSILON ? true : false;
}

void fun_less_double(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(double*)cpv_first - *(double*)cpv_second < -DBL_EPSILON ? true : false;
}

/* less or equal*/
void fun_less_equal_char(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(char*)cpv_first <= *(char*)cpv_second ? true : false;
}

void fun_less_equal_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(unsigned char*)cpv_first <= *(unsigned char*)cpv_second ? true : false;
}

void fun_less_equal_short(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(short*)cpv_first <= *(short*)cpv_second ? true : false;
}

void fun_less_equal_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(unsigned short*)cpv_first <= *(unsigned short*)cpv_second ? true : false;
}

void fun_less_equal_int(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(int*)cpv_first <= *(int*)cpv_second ? true : false;
}

void fun_less_equal_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(unsigned int*)cpv_first <= *(unsigned int*)cpv_second ? true : false;
}

void fun_less_equal_long(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(long*)cpv_first <= *(long*)cpv_second ? true : false;
}

void fun_less_equal_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(unsigned long*)cpv_first <= *(unsigned long*)cpv_second ? true : false;
}

void fun_less_equal_float(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(float*)cpv_first - *(float*)cpv_second < FLT_EPSILON ? true : false;
}

void fun_less_equal_double(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(double*)cpv_first - *(double*)cpv_second < DBL_EPSILON ? true : false;
}

/* logical */
/* logical and */
void fun_logical_and_bool(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(bool_t*)cpv_first && *(bool_t*)cpv_second;
}
/* logical or */
void fun_logical_or_bool(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = *(bool_t*)cpv_first || *(bool_t*)cpv_second;
}
/* logical not */
void fun_logical_not_bool(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(bool_t*)pv_output = !*(bool_t*)cpv_input;
}

/* random nunber */
void fun_random_number(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    srand((unsigned int)time(NULL) + rand());
    *(size_t*)pv_output = *(size_t*)cpv_input != 0 ? rand() % *(size_t*)cpv_input : 0;
}

/* default unary and binary function */
void fun_default_unary(const void* cpv_input, void* pv_output)
{
    void* pv_avoidwarning1 = NULL;
    void* pv_avoidwarning2 = NULL;
    pv_avoidwarning1 = (void*)cpv_input;
    pv_avoidwarning2 = (void*)pv_output;
}

void fun_default_binary(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    void* pv_avoidwarning1 = NULL;
    void* pv_avoidwarning2 = NULL;
    void* pv_avoidwarning3 = NULL;
    pv_avoidwarning1 = (void*)cpv_first;
    pv_avoidwarning2 = (void*)cpv_second;
    pv_avoidwarning3 = (void*)pv_output;
}

/* increase function */
void _fun_increase_char(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(char*)pv_output = *(char*)cpv_input + 0x01;
}

void _fun_increase_uchar(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(unsigned char*)pv_output = *(unsigned char*)cpv_input + 0x01;
}

void _fun_increase_short(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(short*)pv_output = *(short*)cpv_input + 1;
}

void _fun_increase_ushort(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(unsigned short*)pv_output = *(unsigned short*)cpv_input + 1;
}

void _fun_increase_int(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(int*)pv_output = *(int*)cpv_input + 1;
}

void _fun_increase_uint(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(unsigned int*)pv_output = *(unsigned int*)cpv_input + 1;
}

void _fun_increase_long(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(long*)pv_output = *(long*)cpv_input + 1;
}

void _fun_increase_ulong(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(unsigned long*)pv_output = *(unsigned long*)cpv_input + 1;
}

void _fun_increase_float(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(float*)pv_output = *(float*)cpv_input + 1.0;
}

void _fun_increase_double(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(double*)pv_output = *(double*)cpv_input + 1.0;
}

/** local function implementation section **/

/** eof **/

