/*
 *  The implementation of function.
 *  Copyright (C)  2008,2009,2010  Wangbo
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

#include "cstl_alloc.h"
#include "cstl_types.h"
#include "citerator.h"
#include "cstl_function.h"
#include "cstl_function_private.h"

#include "cvector.h"
#include "clist.h"
#include "cdeque.h"
#include "cslist.h"
#include "cstack.h"
#include "cqueue.h"
#include "cstring.h"
#include "cutility.h"
#include "cset.h"
#include "cmap.h"
#include "chash_set.h"
#include "chash_map.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* private function */
unary_function_t _fun_get_unary(iterator_t t_iter, fun_unary_type_t t_funtype)
{
    const char* s_typename = _iterator_get_typebasename(t_iter);

    if(s_typename == NULL)
    {
        return fun_default_unary;
    }

    /* char */
    if(strncmp(s_typename, _CHAR_TYPE, _TYPE_NAME_SIZE) == 0 ||
       strncmp(s_typename, _SIGNED_CHAR_TYPE, _TYPE_NAME_SIZE) == 0)
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
    else if(strncmp(s_typename, _UNSIGNED_CHAR_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        if(t_funtype == _INCREASE_FUN)
        {
            return _fun_increase_uchar;
        }
    }
    /* short */
    else if(strncmp(s_typename, _SHORT_TYPE, _TYPE_NAME_SIZE) == 0 ||
            strncmp(s_typename, _SHORT_INT_TYPE, _TYPE_NAME_SIZE) == 0 ||
            strncmp(s_typename, _SIGNED_SHORT_TYPE, _TYPE_NAME_SIZE) == 0 ||
            strncmp(s_typename, _SIGNED_SHORT_INT_TYPE, _TYPE_NAME_SIZE) == 0)
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
    else if(strncmp(s_typename, _UNSIGNED_SHORT_TYPE, _TYPE_NAME_SIZE) == 0 ||
            strncmp(s_typename, _UNSIGNED_SHORT_INT_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        if(t_funtype == _INCREASE_FUN)
        {
            return _fun_increase_ushort;
        }
    }
    /* int */
    else if(strncmp(s_typename, _INT_TYPE, _TYPE_NAME_SIZE) == 0 ||
            strncmp(s_typename, _SIGNED_INT_TYPE, _TYPE_NAME_SIZE) == 0 ||
            strncmp(s_typename, _SIGNED_TYPE, _TYPE_NAME_SIZE) == 0)
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
    else if(strncmp(s_typename, _UNSIGNED_TYPE, _TYPE_NAME_SIZE) == 0 ||
            strncmp(s_typename, _UNSIGNED_INT_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        if(t_funtype == _INCREASE_FUN)
        {
            return _fun_increase_uint;
        }
    }
    /* long */
    else if(strncmp(s_typename, _LONG_TYPE, _TYPE_NAME_SIZE) == 0 ||
            strncmp(s_typename, _LONG_INT_TYPE, _TYPE_NAME_SIZE) == 0 ||
            strncmp(s_typename, _SIGNED_LONG_TYPE, _TYPE_NAME_SIZE) == 0 ||
            strncmp(s_typename, _SIGNED_LONG_INT_TYPE, _TYPE_NAME_SIZE) == 0)
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
    else if(strncmp(s_typename, _UNSIGNED_LONG_TYPE, _TYPE_NAME_SIZE) == 0 ||
            strncmp(s_typename, _UNSIGNED_LONG_INT_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        if(t_funtype == _INCREASE_FUN)
        {
            return _fun_increase_ulong;
        }
    }
    /* float */
    else if(strncmp(s_typename, _FLOAT_TYPE, _TYPE_NAME_SIZE) == 0)
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
    else if(strncmp(s_typename, _DOUBLE_TYPE, _TYPE_NAME_SIZE) == 0)
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
    else if(strncmp(s_typename, _LONG_DOUBLE_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        if(t_funtype == _NEGATE_FUN)
        {
            return fun_negate_long_double;
        }
    }
    /* bool_t */
    else if(strncmp(s_typename, _BOOL_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        if(t_funtype == _LOGICAL_NOT_FUN)
        {
            return fun_logical_not_bool;
        }
    }

    return fun_default_unary;
}

binary_function_t _fun_get_binary(iterator_t t_iter, fun_binary_type_t t_funtype)
{
    const char* s_typename = _iterator_get_typebasename(t_iter);
    _typeinfo_t* pt_typeinfo = _iterator_get_typeinfo(t_iter);

    if(s_typename == NULL)
    {
        return fun_default_binary;
    }

    /* char */
    if(strncmp(s_typename, _CHAR_TYPE, _TYPE_NAME_SIZE) == 0 ||
       strncmp(s_typename, _SIGNED_CHAR_TYPE, _TYPE_NAME_SIZE) == 0)
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
    else if(strncmp(s_typename, _UNSIGNED_CHAR_TYPE, _TYPE_NAME_SIZE) == 0)
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
    else if(strncmp(s_typename, _SHORT_TYPE, _TYPE_NAME_SIZE) == 0 ||
            strncmp(s_typename, _SHORT_INT_TYPE, _TYPE_NAME_SIZE) == 0 ||
            strncmp(s_typename, _SIGNED_SHORT_TYPE, _TYPE_NAME_SIZE) == 0 ||
            strncmp(s_typename, _SIGNED_SHORT_INT_TYPE, _TYPE_NAME_SIZE) == 0)
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
    else if(strncmp(s_typename, _UNSIGNED_SHORT_TYPE, _TYPE_NAME_SIZE) == 0 ||
            strncmp(s_typename, _UNSIGNED_SHORT_INT_TYPE, _TYPE_NAME_SIZE) == 0)
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
    else if(strncmp(s_typename, _INT_TYPE, _TYPE_NAME_SIZE) == 0 ||
            strncmp(s_typename, _SIGNED_INT_TYPE, _TYPE_NAME_SIZE) == 0 ||
            strncmp(s_typename, _SIGNED_TYPE, _TYPE_NAME_SIZE) == 0)
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
    else if(strncmp(s_typename, _UNSIGNED_TYPE, _TYPE_NAME_SIZE) == 0 ||
            strncmp(s_typename, _UNSIGNED_INT_TYPE, _TYPE_NAME_SIZE) == 0)
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
    else if(strncmp(s_typename, _LONG_TYPE, _TYPE_NAME_SIZE) == 0 ||
            strncmp(s_typename, _LONG_INT_TYPE, _TYPE_NAME_SIZE) == 0 ||
            strncmp(s_typename, _SIGNED_LONG_TYPE, _TYPE_NAME_SIZE) == 0 ||
            strncmp(s_typename, _SIGNED_LONG_INT_TYPE, _TYPE_NAME_SIZE) == 0)
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
    else if(strncmp(s_typename, _UNSIGNED_LONG_TYPE, _TYPE_NAME_SIZE) == 0 ||
            strncmp(s_typename, _UNSIGNED_LONG_INT_TYPE, _TYPE_NAME_SIZE) == 0)
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
    else if(strncmp(s_typename, _FLOAT_TYPE, _TYPE_NAME_SIZE) == 0)
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
    else if(strncmp(s_typename, _DOUBLE_TYPE, _TYPE_NAME_SIZE) == 0)
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
    /* long double */
    else if(strncmp(s_typename, _LONG_DOUBLE_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _PLUS_FUN:
            return fun_plus_long_double;
            break;
        case _MINUS_FUN:
            return fun_minus_long_double;
            break;
        case _MULTIPLIES_FUN:
            return fun_multiplies_long_double;
            break;
        case _DIVIDES_FUN:
            return fun_divides_long_double;
            break;
        case _EQUAL_FUN:
            return fun_equal_long_double;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_long_double;
            break;
        case _GREAT_FUN:
            return fun_great_long_double;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_long_double;
            break;
        case _LESS_FUN:
            return fun_less_long_double;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_long_double;
            break;
        default:
            break;
        }
    }
    /* bool_t */
    else if(strncmp(s_typename, _BOOL_TYPE, _TYPE_NAME_SIZE) == 0)
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
    /* vector_t */
    else if(strncmp(s_typename, _VECTOR_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _EQUAL_FUN:
            return fun_equal_vector;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_vector;
            break;
        case _GREAT_FUN:
            return fun_great_vector;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_vector;
            break;
        case _LESS_FUN:
            return fun_less_vector;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_vector;
            break;
        default:
            break;
        }
    }
    /* deque_t */
    else if(strncmp(s_typename, _DEQUE_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _EQUAL_FUN:
            return fun_equal_deque;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_deque;
            break;
        case _GREAT_FUN:
            return fun_great_deque;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_deque;
            break;
        case _LESS_FUN:
            return fun_less_deque;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_deque;
            break;
        default:
            break;
        }
    }
    /* list_t */
    else if(strncmp(s_typename, _LIST_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _EQUAL_FUN:
            return fun_equal_list;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_list;
            break;
        case _GREAT_FUN:
            return fun_great_list;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_list;
            break;
        case _LESS_FUN:
            return fun_less_list;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_list;
            break;
        default:
            break;
        }
    }
    /* slist_t */
    else if(strncmp(s_typename, _SLIST_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _EQUAL_FUN:
            return fun_equal_slist;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_slist;
            break;
        case _GREAT_FUN:
            return fun_great_slist;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_slist;
            break;
        case _LESS_FUN:
            return fun_less_slist;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_slist;
            break;
        default:
            break;
        }
    }
    /* queue_t */
    else if(strncmp(s_typename, _QUEUE_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _EQUAL_FUN:
            return fun_equal_queue;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_queue;
            break;
        case _GREAT_FUN:
            return fun_great_queue;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_queue;
            break;
        case _LESS_FUN:
            return fun_less_queue;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_queue;
            break;
        default:
            break;
        }
    }
    /* stack_t */
    else if(strncmp(s_typename, _STACK_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _EQUAL_FUN:
            return fun_equal_stack;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_stack;
            break;
        case _GREAT_FUN:
            return fun_great_stack;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_stack;
            break;
        case _LESS_FUN:
            return fun_less_stack;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_stack;
            break;
        default:
            break;
        }
    }
    /* pair_t */
    else if(strncmp(s_typename, _PAIR_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _EQUAL_FUN:
            return fun_equal_pair;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_pair;
            break;
        case _GREAT_FUN:
            return fun_great_pair;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_pair;
            break;
        case _LESS_FUN:
            return fun_less_pair;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_pair;
            break;
        default:
            break;
        }
    }
    /* set_t */
    else if(strncmp(s_typename, _SET_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _EQUAL_FUN:
            return fun_equal_set;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_set;
            break;
        case _GREAT_FUN:
            return fun_great_set;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_set;
            break;
        case _LESS_FUN:
            return fun_less_set;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_set;
            break;
        default:
            break;
        }
    }
    /* map_t */
    else if(strncmp(s_typename, _MAP_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _EQUAL_FUN:
            return fun_equal_map;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_map;
            break;
        case _GREAT_FUN:
            return fun_great_map;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_map;
            break;
        case _LESS_FUN:
            return fun_less_map;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_map;
            break;
        default:
            break;
        }
    }
    /* multiset_t */
    else if(strncmp(s_typename, _MULTISET_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _EQUAL_FUN:
            return fun_equal_multiset;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_multiset;
            break;
        case _GREAT_FUN:
            return fun_great_multiset;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_multiset;
            break;
        case _LESS_FUN:
            return fun_less_multiset;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_multiset;
            break;
        default:
            break;
        }
    }
    /* multimap_t */
    else if(strncmp(s_typename, _MULTIMAP_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _EQUAL_FUN:
            return fun_equal_multimap;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_multimap;
            break;
        case _GREAT_FUN:
            return fun_great_multimap;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_multimap;
            break;
        case _LESS_FUN:
            return fun_less_multimap;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_multimap;
            break;
        default:
            break;
        }
    }
    /* hash_set_t */
    else if(strncmp(s_typename, _HASH_SET_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _EQUAL_FUN:
            return fun_equal_hash_set;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_hash_set;
            break;
        case _GREAT_FUN:
            return fun_great_hash_set;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_hash_set;
            break;
        case _LESS_FUN:
            return fun_less_hash_set;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_hash_set;
            break;
        default:
            break;
        }
    }
    /* hash_map_t */
    else if(strncmp(s_typename, _HASH_MAP_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _EQUAL_FUN:
            return fun_equal_hash_map;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_hash_map;
            break;
        case _GREAT_FUN:
            return fun_great_hash_map;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_hash_map;
            break;
        case _LESS_FUN:
            return fun_less_hash_map;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_hash_map;
            break;
        default:
            break;
        }
    }
    /* hash_multiset_t */
    else if(strncmp(s_typename, _HASH_MULTISET_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _EQUAL_FUN:
            return fun_equal_hash_multiset;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_hash_multiset;
            break;
        case _GREAT_FUN:
            return fun_great_hash_multiset;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_hash_multiset;
            break;
        case _LESS_FUN:
            return fun_less_hash_multiset;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_hash_multiset;
            break;
        default:
            break;
        }
    }
    /* hash_multimap_t */
    else if(strncmp(s_typename, _HASH_MULTIMAP_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _EQUAL_FUN:
            return fun_equal_hash_multimap;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_hash_multimap;
            break;
        case _GREAT_FUN:
            return fun_great_hash_multimap;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_hash_multimap;
            break;
        case _LESS_FUN:
            return fun_less_hash_multimap;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_hash_multimap;
            break;
        default:
            break;
        }
    }
    /* string_t */
    else if(strncmp(s_typename, _STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        switch(t_funtype)
        {
        case _EQUAL_FUN:
            return fun_equal_string;
            break;
        case _NOT_EQUAL_FUN:
            return fun_not_equal_string;
            break;
        case _GREAT_FUN:
            return fun_great_string;
            break;
        case _GREAT_EQUAL_FUN:
            return fun_great_equal_string;
            break;
        case _LESS_FUN:
            return fun_less_string;
            break;
        case _LESS_EQUAL_FUN:
            return fun_less_equal_string;
            break;
        default:
            break;
        }
    }

    if(pt_typeinfo != NULL && pt_typeinfo->_pt_type != NULL && t_funtype == _LESS_FUN)
    {
        return pt_typeinfo->_pt_type->_t_typeless;
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

void fun_plus_long_double(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(long double*)pv_output = *(long double*)cpv_first + *(long double*)cpv_second;
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

void fun_minus_long_double(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(long double*)pv_output = *(long double*)cpv_first - *(long double*)cpv_second;
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

void fun_multiplies_long_double(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(long double*)pv_output = *(long double*)cpv_first * *(long double*)cpv_second;
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

void fun_divides_long_double(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    assert(*(long double*)cpv_second > LDBL_EPSILON ||
           *(long double*)cpv_second < -LDBL_EPSILON);
    *(long double*)pv_output = *(long double*)cpv_first / *(long double*)cpv_second;
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

void fun_negate_long_double(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(long double*)pv_output = -*(long double*)cpv_input;
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

void fun_equal_long_double(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(long double*)cpv_first - *(long double*)cpv_second < LDBL_EPSILON &&
        *(long double*)cpv_first - *(long double*)cpv_second > -LDBL_EPSILON ? true : false;
}

void fun_equal_vector(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = vector_equal((vector_t*)cpv_first, (vector_t*)cpv_second);
}

void fun_equal_deque(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = deque_equal((deque_t*)cpv_first, (deque_t*)cpv_second);
}

void fun_equal_list(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = list_equal((list_t*)cpv_first, (list_t*)cpv_second);
}

void fun_equal_slist(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = slist_equal((slist_t*)cpv_first, (slist_t*)cpv_second);
}

void fun_equal_queue(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = queue_equal((queue_t*)cpv_first, (queue_t*)cpv_second);
}

void fun_equal_stack(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = stack_equal((stack_t*)cpv_first, (stack_t*)cpv_second);
}

void fun_equal_string(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = string_equal((string_t*)cpv_first, (string_t*)cpv_second);
}

void fun_equal_pair(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = pair_equal((pair_t*)cpv_first, (pair_t*)cpv_second);
}

void fun_equal_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = set_equal((set_t*)cpv_first, (set_t*)cpv_second);
}

void fun_equal_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = map_equal((map_t*)cpv_first, (map_t*)cpv_second);
}

void fun_equal_multiset(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = multiset_equal((multiset_t*)cpv_first, (multiset_t*)cpv_second);
}

void fun_equal_multimap(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = multimap_equal((multimap_t*)cpv_first, (multimap_t*)cpv_second);
}

void fun_equal_hash_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_set_equal((hash_set_t*)cpv_first, (hash_set_t*)cpv_second);
}

void fun_equal_hash_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_map_equal((hash_map_t*)cpv_first, (hash_map_t*)cpv_second);
}

void fun_equal_hash_multiset(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_multiset_equal(
        (hash_multiset_t*)cpv_first, (hash_multiset_t*)cpv_second);
}

void fun_equal_hash_multimap(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_multimap_equal(
        (hash_multimap_t*)cpv_first, (hash_multimap_t*)cpv_second);
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

void fun_not_equal_long_double(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(long double*)cpv_first - *(long double*)cpv_second >= LDBL_EPSILON ||
        *(long double*)cpv_first - *(long double*)cpv_second <= -LDBL_EPSILON ? true : false;
}

void fun_not_equal_vector(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = vector_not_equal((vector_t*)cpv_first, (vector_t*)cpv_second);
}

void fun_not_equal_deque(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = deque_not_equal((deque_t*)cpv_first, (deque_t*)cpv_second);
}

void fun_not_equal_list(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = list_not_equal((list_t*)cpv_first, (list_t*)cpv_second);
}

void fun_not_equal_slist(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = slist_not_equal((slist_t*)cpv_first, (slist_t*)cpv_second);
}

void fun_not_equal_queue(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = queue_not_equal((queue_t*)cpv_first, (queue_t*)cpv_second);
}

void fun_not_equal_stack(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = stack_not_equal((stack_t*)cpv_first, (stack_t*)cpv_second);
}

void fun_not_equal_string(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = string_not_equal((string_t*)cpv_first, (string_t*)cpv_second);
}

void fun_not_equal_pair(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = pair_not_equal((pair_t*)cpv_first, (pair_t*)cpv_second);
}

void fun_not_equal_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = set_not_equal((set_t*)cpv_first, (set_t*)cpv_second);
}

void fun_not_equal_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = map_not_equal((map_t*)cpv_first, (map_t*)cpv_second);
}

void fun_not_equal_multiset(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = multiset_not_equal((multiset_t*)cpv_first, (multiset_t*)cpv_second);
}

void fun_not_equal_multimap(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = multimap_not_equal((multimap_t*)cpv_first, (multimap_t*)cpv_second);
}

void fun_not_equal_hash_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_set_not_equal((hash_set_t*)cpv_first, (hash_set_t*)cpv_second);
}

void fun_not_equal_hash_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_map_not_equal((hash_map_t*)cpv_first, (hash_map_t*)cpv_second);
}

void fun_not_equal_hash_multiset(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_multiset_not_equal(
        (hash_multiset_t*)cpv_first, (hash_multiset_t*)cpv_second);
}

void fun_not_equal_hash_multimap(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_multimap_not_equal(
        (hash_multimap_t*)cpv_first, (hash_multimap_t*)cpv_second);
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

void fun_great_long_double(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(long double*)cpv_first - *(long double*)cpv_second >= LDBL_EPSILON ? true : false;
}

void fun_great_vector(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = vector_great((vector_t*)cpv_first, (vector_t*)cpv_second);
}

void fun_great_deque(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = deque_great((deque_t*)cpv_first, (deque_t*)cpv_second);
}

void fun_great_list(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = list_great((list_t*)cpv_first, (list_t*)cpv_second);
}

void fun_great_slist(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = slist_great((slist_t*)cpv_first, (slist_t*)cpv_second);
}

void fun_great_queue(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = queue_great((queue_t*)cpv_first, (queue_t*)cpv_second);
}

void fun_great_stack(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = stack_great((stack_t*)cpv_first, (stack_t*)cpv_second);
}

void fun_great_string(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = string_great((string_t*)cpv_first, (string_t*)cpv_second);
}

void fun_great_pair(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = pair_great((pair_t*)cpv_first, (pair_t*)cpv_second);
}

void fun_great_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = set_great((set_t*)cpv_first, (set_t*)cpv_second);
}

void fun_great_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = map_great((map_t*)cpv_first, (map_t*)cpv_second);
}

void fun_great_multiset(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = multiset_great((multiset_t*)cpv_first, (multiset_t*)cpv_second);
}

void fun_great_multimap(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = multimap_great((multimap_t*)cpv_first, (multimap_t*)cpv_second);
}

void fun_great_hash_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_set_great((hash_set_t*)cpv_first, (hash_set_t*)cpv_second);
}

void fun_great_hash_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_map_great((hash_map_t*)cpv_first, (hash_map_t*)cpv_second);
}

void fun_great_hash_multiset(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_multiset_great(
        (hash_multiset_t*)cpv_first, (hash_multiset_t*)cpv_second);
}

void fun_great_hash_multimap(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_multimap_great(
        (hash_multimap_t*)cpv_first, (hash_multimap_t*)cpv_second);
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

void fun_great_equal_long_double(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(long double*)cpv_first - *(long double*)cpv_second > -LDBL_EPSILON ? true : false;
}

void fun_great_equal_vector(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = vector_great_equal((vector_t*)cpv_first, (vector_t*)cpv_second);
}

void fun_great_equal_deque(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = deque_great_equal((deque_t*)cpv_first, (deque_t*)cpv_second);
}

void fun_great_equal_list(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = list_great_equal((list_t*)cpv_first, (list_t*)cpv_second);
}

void fun_great_equal_slist(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = slist_great_equal((slist_t*)cpv_first, (slist_t*)cpv_second);
}

void fun_great_equal_queue(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = queue_great_equal((queue_t*)cpv_first, (queue_t*)cpv_second);
}

void fun_great_equal_stack(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = stack_great_equal((stack_t*)cpv_first, (stack_t*)cpv_second);
}

void fun_great_equal_string(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = string_great_equal((string_t*)cpv_first, (string_t*)cpv_second);
}

void fun_great_equal_pair(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = pair_great_equal((pair_t*)cpv_first, (pair_t*)cpv_second);
}

void fun_great_equal_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = set_great_equal((set_t*)cpv_first, (set_t*)cpv_second);
}

void fun_great_equal_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = map_great_equal((map_t*)cpv_first, (map_t*)cpv_second);
}

void fun_great_equal_multiset(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = multiset_great_equal(
        (multiset_t*)cpv_first, (multiset_t*)cpv_second);
}

void fun_great_equal_multimap(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = multimap_great_equal(
        (multimap_t*)cpv_first, (multimap_t*)cpv_second);
}

void fun_great_equal_hash_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_set_great_equal(
        (hash_set_t*)cpv_first, (hash_set_t*)cpv_second);
}

void fun_great_equal_hash_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_map_great_equal(
        (hash_map_t*)cpv_first, (hash_map_t*)cpv_second);
}

void fun_great_equal_hash_multiset(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_multiset_great_equal(
        (hash_multiset_t*)cpv_first, (hash_multiset_t*)cpv_second);
}

void fun_great_equal_hash_multimap(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_multimap_great_equal(
        (hash_multimap_t*)cpv_first, (hash_multimap_t*)cpv_second);
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

void fun_less_long_double(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(long double*)cpv_first - *(long double*)cpv_second < -LDBL_EPSILON ? true : false;
}

void fun_less_vector(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = vector_less((vector_t*)cpv_first, (vector_t*)cpv_second);
}

void fun_less_deque(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = deque_less((deque_t*)cpv_first, (deque_t*)cpv_second);
}

void fun_less_list(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = list_less((list_t*)cpv_first, (list_t*)cpv_second);
}

void fun_less_slist(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = slist_less((slist_t*)cpv_first, (slist_t*)cpv_second);
}

void fun_less_queue(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = queue_less((queue_t*)cpv_first, (queue_t*)cpv_second);
}

void fun_less_stack(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = stack_less((stack_t*)cpv_first, (stack_t*)cpv_second);
}

void fun_less_string(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = string_less((string_t*)cpv_first, (string_t*)cpv_second);
}

void fun_less_pair(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = pair_less((pair_t*)cpv_first, (pair_t*)cpv_second);
}

void fun_less_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = set_less((set_t*)cpv_first, (set_t*)cpv_second);
}

void fun_less_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = map_less((map_t*)cpv_first, (map_t*)cpv_second);
}

void fun_less_multiset(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = multiset_less(
        (multiset_t*)cpv_first, (multiset_t*)cpv_second);
}

void fun_less_multimap(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = multimap_less(
        (multimap_t*)cpv_first, (multimap_t*)cpv_second);
}

void fun_less_hash_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_set_less(
        (hash_set_t*)cpv_first, (hash_set_t*)cpv_second);
}

void fun_less_hash_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_map_less(
        (hash_map_t*)cpv_first, (hash_map_t*)cpv_second);
}

void fun_less_hash_multiset(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_multiset_less(
        (hash_multiset_t*)cpv_first, (hash_multiset_t*)cpv_second);
}

void fun_less_hash_multimap(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_multimap_less(
        (hash_multimap_t*)cpv_first, (hash_multimap_t*)cpv_second);
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

void fun_less_equal_long_double(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = 
        *(long double*)cpv_first - *(long double*)cpv_second < LDBL_EPSILON ? true : false;
}

void fun_less_equal_vector(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = vector_less_equal((vector_t*)cpv_first, (vector_t*)cpv_second);
}

void fun_less_equal_deque(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = deque_less_equal((deque_t*)cpv_first, (deque_t*)cpv_second);
}

void fun_less_equal_list(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = list_less_equal((list_t*)cpv_first, (list_t*)cpv_second);
}

void fun_less_equal_slist(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = slist_less_equal((slist_t*)cpv_first, (slist_t*)cpv_second);
}

void fun_less_equal_queue(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = queue_less_equal((queue_t*)cpv_first, (queue_t*)cpv_second);
}

void fun_less_equal_stack(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = stack_less_equal((stack_t*)cpv_first, (stack_t*)cpv_second);
}

void fun_less_equal_string(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = string_less_equal((string_t*)cpv_first, (string_t*)cpv_second);
}

void fun_less_equal_pair(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = pair_less_equal((pair_t*)cpv_first, (pair_t*)cpv_second);
}

void fun_less_equal_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = set_less_equal((set_t*)cpv_first, (set_t*)cpv_second);
}

void fun_less_equal_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = map_less_equal((map_t*)cpv_first, (map_t*)cpv_second);
}

void fun_less_equal_multiset(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = multiset_less_equal(
        (multiset_t*)cpv_first, (multiset_t*)cpv_second);
}

void fun_less_equal_multimap(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = multimap_less_equal(
        (multimap_t*)cpv_first, (multimap_t*)cpv_second);
}

void fun_less_equal_hash_set(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_set_less_equal(
        (hash_set_t*)cpv_first, (hash_set_t*)cpv_second);
}

void fun_less_equal_hash_map(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_map_less_equal(
        (hash_map_t*)cpv_first, (hash_map_t*)cpv_second);
}

void fun_less_equal_hash_multiset(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_multiset_less_equal(
        (hash_multiset_t*)cpv_first, (hash_multiset_t*)cpv_second);
}

void fun_less_equal_hash_multimap(
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

    *(bool_t*)pv_output = hash_multimap_less_equal(
        (hash_multimap_t*)cpv_first, (hash_multimap_t*)cpv_second);
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

