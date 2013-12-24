/*
 *  The implementation of private function.
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
#include <cstl/citerator.h>
#include <cstl/cfunctional.h>

#include <cstl/cvector.h>
#include <cstl/clist.h>
#include <cstl/cdeque.h>
#include <cstl/cslist.h>
#include <cstl/cstack.h>
#include <cstl/cqueue.h>
#include <cstl/cstring.h>
#include <cstl/cutility.h>
#include <cstl/cset.h>
#include <cstl/cmap.h>
#include <cstl/chash_set.h>
#include <cstl/chash_map.h>

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Select unary function accroding to unary function type.
 */
ufun_t _fun_get_unary(iterator_t it_iter, fun_type_t ftype_type)
{
    const char* s_typename = NULL;

    assert(_iterator_is_valid(it_iter));
    assert(ftype_type >= _NEGATE_FUN && ftype_type <= _RANDOM_NUMBER_FUN);

    if ((s_typename = _iterator_get_typebasename(it_iter))== NULL) {
        return fun_default_unary;
    }

    if (strncmp(s_typename, _CHAR_TYPE, _TYPE_NAME_SIZE) == 0 ||
        strncmp(s_typename, _SIGNED_CHAR_TYPE, _TYPE_NAME_SIZE) == 0) {                 /* char */
        if (ftype_type == _NEGATE_FUN) {
            return fun_negate_char;
        } else if (ftype_type == _INCREASE_FUN) {
            return _fun_increase_char;
        }
    } else if (strncmp(s_typename, _UNSIGNED_CHAR_TYPE, _TYPE_NAME_SIZE) == 0) {        /* unsigned char */
        if (ftype_type == _INCREASE_FUN) {
            return _fun_increase_uchar;
        }
    } else if (strncmp(s_typename, _SHORT_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _SHORT_INT_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _SIGNED_SHORT_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _SIGNED_SHORT_INT_TYPE, _TYPE_NAME_SIZE) == 0) {     /* short */
        if (ftype_type == _NEGATE_FUN) {
            return fun_negate_short;
        } else if (ftype_type == _INCREASE_FUN) {
            return _fun_increase_short;
        }
    } else if (strncmp(s_typename, _UNSIGNED_SHORT_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _UNSIGNED_SHORT_INT_TYPE, _TYPE_NAME_SIZE) == 0) {   /* unsigned short */
        if (ftype_type == _INCREASE_FUN) {
            return _fun_increase_ushort;
        }
    } else if (strncmp(s_typename, _INT_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _SIGNED_INT_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _SIGNED_TYPE, _TYPE_NAME_SIZE) == 0) {               /* int */
        if (ftype_type == _NEGATE_FUN) {
            return fun_negate_int;
        } else if (ftype_type == _INCREASE_FUN) {
            return _fun_increase_int;
        }
    } else if (strncmp(s_typename, _UNSIGNED_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _UNSIGNED_INT_TYPE, _TYPE_NAME_SIZE) == 0) {         /* unsigned int */
        if (ftype_type == _INCREASE_FUN) {
            return _fun_increase_uint;
        }
    } else if (strncmp(s_typename, _LONG_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _LONG_INT_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _SIGNED_LONG_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _SIGNED_LONG_INT_TYPE, _TYPE_NAME_SIZE) == 0) {      /* long */
        if (ftype_type == _NEGATE_FUN) {
            return fun_negate_long;
        } else if (ftype_type == _INCREASE_FUN) {
            return _fun_increase_long;
        }
    } else if (strncmp(s_typename, _UNSIGNED_LONG_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _UNSIGNED_LONG_INT_TYPE, _TYPE_NAME_SIZE) == 0) {    /* unsigned long */
        if (ftype_type == _INCREASE_FUN) {
            return _fun_increase_ulong;
        }
    } else if (strncmp(s_typename, _FLOAT_TYPE, _TYPE_NAME_SIZE) == 0) {                /* float */
        if (ftype_type == _NEGATE_FUN) {
            return fun_negate_float;
        } else if (ftype_type == _INCREASE_FUN) {
            return _fun_increase_float;
        }
    } else if (strncmp(s_typename, _DOUBLE_TYPE, _TYPE_NAME_SIZE) == 0) {               /* double */
        if (ftype_type == _NEGATE_FUN) {
            return fun_negate_double;
        } else if (ftype_type == _INCREASE_FUN) {
            return _fun_increase_double;
        }
    } else if (strncmp(s_typename, _LONG_DOUBLE_TYPE, _TYPE_NAME_SIZE) == 0) {          /* long double */
        if (ftype_type == _NEGATE_FUN) {
            return fun_negate_long_double;
        }
    } else if (strncmp(s_typename, _CSTL_BOOL_TYPE, _TYPE_NAME_SIZE) == 0) {            /* bool_t */
        if (ftype_type == _LOGICAL_NOT_FUN) {
            return fun_logical_not_cstl_bool;
        }
#ifndef _MSC_VER
    } else if (strncmp(s_typename, _BOOL_TYPE, _TYPE_NAME_SIZE) == 0) {                 /* _Bool */
        if (ftype_type == _LOGICAL_NOT_FUN) {
            return fun_logical_not_bool;
        }
    } else if (strncmp(s_typename, _LONG_LONG_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _LONG_LONG_INT_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _SIGNED_LONG_LONG_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _SIGNED_LONG_LONG_INT_TYPE, _TYPE_NAME_SIZE) == 0) {      /* long */
        if (ftype_type == _NEGATE_FUN) {
            return fun_negate_long_long;
        } else if (ftype_type == _INCREASE_FUN) {
            return _fun_increase_long_long;
        }
    } else if (strncmp(s_typename, _UNSIGNED_LONG_LONG_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _UNSIGNED_LONG_LONG_INT_TYPE, _TYPE_NAME_SIZE) == 0) {    /* unsigned long */
        if (ftype_type == _INCREASE_FUN) {
            return _fun_increase_ulong_long;
        }
#endif
    }

    return fun_default_unary;
}

/**
 * Select binary function accroding to binary function type.
 */
bfun_t _fun_get_binary(iterator_t it_iter, fun_type_t ftype_type)
{
    const char*  s_typename = NULL;
    _typeinfo_t* pt_typeinfo = NULL;

    assert(_iterator_is_valid(it_iter));
    assert(ftype_type >= _PLUS_FUN && ftype_type <= _LOGICAL_OR_FUN);

    s_typename = _iterator_get_typebasename(it_iter);
    pt_typeinfo = _iterator_get_typeinfo(it_iter);
    if (s_typename == NULL) {
        return fun_default_binary;
    }

    if (strncmp(s_typename, _CHAR_TYPE, _TYPE_NAME_SIZE) == 0 ||
        strncmp(s_typename, _SIGNED_CHAR_TYPE, _TYPE_NAME_SIZE) == 0) {                 /* char */
        switch (ftype_type) {
            case _PLUS_FUN:             return fun_plus_char;                   break;
            case _MINUS_FUN:            return fun_minus_char;                  break;
            case _MULTIPLIES_FUN:       return fun_multiplies_char;             break;
            case _DIVIDES_FUN:          return fun_divides_char;                break;
            case _MODULUS_FUN:          return fun_modulus_char;                break;
            case _EQUAL_FUN:            return fun_equal_char;                  break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_char;              break;
            case _GREATER_FUN:          return fun_greater_char;                break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_char;          break;
            case _LESS_FUN:             return fun_less_char;                   break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_char;             break;
            default: break;
        }
    } else if (strncmp(s_typename, _UNSIGNED_CHAR_TYPE, _TYPE_NAME_SIZE) == 0) {        /* unsigned char */
        switch (ftype_type) {
            case _PLUS_FUN:             return fun_plus_uchar;                  break;
            case _MINUS_FUN:            return fun_minus_uchar;                 break;
            case _MULTIPLIES_FUN:       return fun_multiplies_uchar;            break;
            case _DIVIDES_FUN:          return fun_divides_uchar;               break;
            case _MODULUS_FUN:          return fun_modulus_uchar;               break;
            case _EQUAL_FUN:            return fun_equal_uchar;                 break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_uchar;             break;
            case _GREATER_FUN:          return fun_greater_uchar;               break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_uchar;         break;
            case _LESS_FUN:             return fun_less_uchar;                  break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_uchar;            break;
            default: break;
        }
    } else if (strncmp(s_typename, _SHORT_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _SHORT_INT_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _SIGNED_SHORT_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _SIGNED_SHORT_INT_TYPE, _TYPE_NAME_SIZE) == 0) {     /* short */
        switch (ftype_type) {
            case _PLUS_FUN:             return fun_plus_short;                  break;
            case _MINUS_FUN:            return fun_minus_short;                 break;
            case _MULTIPLIES_FUN:       return fun_multiplies_short;            break;
            case _DIVIDES_FUN:          return fun_divides_short;               break;
            case _MODULUS_FUN:          return fun_modulus_short;               break;
            case _EQUAL_FUN:            return fun_equal_short;                 break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_short;             break;
            case _GREATER_FUN:          return fun_greater_short;               break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_short;         break;
            case _LESS_FUN:             return fun_less_short;                  break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_short;            break;
            default: break;
        }
    } else if (strncmp(s_typename, _UNSIGNED_SHORT_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _UNSIGNED_SHORT_INT_TYPE, _TYPE_NAME_SIZE) == 0) {   /* unsigned short */
        switch (ftype_type) {
            case _PLUS_FUN:             return fun_plus_ushort;                 break;
            case _MINUS_FUN:            return fun_minus_ushort;                break;
            case _MULTIPLIES_FUN:       return fun_multiplies_ushort;           break;
            case _DIVIDES_FUN:          return fun_divides_ushort;              break;
            case _MODULUS_FUN:          return fun_modulus_ushort;              break;
            case _EQUAL_FUN:            return fun_equal_ushort;                break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_ushort;            break;
            case _GREATER_FUN:          return fun_greater_ushort;              break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_ushort;        break;
            case _LESS_FUN:             return fun_less_ushort;                 break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_ushort;           break;
            default: break;
        }
    } else if (strncmp(s_typename, _INT_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _SIGNED_INT_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _SIGNED_TYPE, _TYPE_NAME_SIZE) == 0) {               /* int */
        switch (ftype_type) {
            case _PLUS_FUN:             return fun_plus_int;                    break;
            case _MINUS_FUN:            return fun_minus_int;                   break;
            case _MULTIPLIES_FUN:       return fun_multiplies_int;              break;
            case _DIVIDES_FUN:          return fun_divides_int;                 break;
            case _MODULUS_FUN:          return fun_modulus_int;                 break;
            case _EQUAL_FUN:            return fun_equal_int;                   break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_int;               break;
            case _GREATER_FUN:          return fun_greater_int;                 break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_int;           break;
            case _LESS_FUN:             return fun_less_int;                    break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_int;              break;
            default: break;
        }
    } else if (strncmp(s_typename, _UNSIGNED_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _UNSIGNED_INT_TYPE, _TYPE_NAME_SIZE) == 0) {         /* unsigned int */
        switch (ftype_type) {
            case _PLUS_FUN:             return fun_plus_uint;                   break;
            case _MINUS_FUN:            return fun_minus_uint;                  break;
            case _MULTIPLIES_FUN:       return fun_multiplies_uint;             break;
            case _DIVIDES_FUN:          return fun_divides_uint;                break;
            case _MODULUS_FUN:          return fun_modulus_uint;                break;
            case _EQUAL_FUN:            return fun_equal_uint;                  break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_uint;              break;
            case _GREATER_FUN:          return fun_greater_uint;                break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_uint;          break;
            case _LESS_FUN:             return fun_less_uint;                   break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_uint;             break;
            default: break;
        }
    } else if (strncmp(s_typename, _LONG_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _LONG_INT_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _SIGNED_LONG_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _SIGNED_LONG_INT_TYPE, _TYPE_NAME_SIZE) == 0) {      /* long */
        switch (ftype_type) {
            case _PLUS_FUN:             return fun_plus_long;                   break;
            case _MINUS_FUN:            return fun_minus_long;                  break;
            case _MULTIPLIES_FUN:       return fun_multiplies_long;             break;
            case _DIVIDES_FUN:          return fun_divides_long;                break;
            case _MODULUS_FUN:          return fun_modulus_long;                break;
            case _EQUAL_FUN:            return fun_equal_long;                  break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_long;              break;
            case _GREATER_FUN:          return fun_greater_long;                break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_long;          break;
            case _LESS_FUN:             return fun_less_long;                   break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_long;             break;
            default: break;
        }
    } else if (strncmp(s_typename, _UNSIGNED_LONG_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _UNSIGNED_LONG_INT_TYPE, _TYPE_NAME_SIZE) == 0) {    /* unsigned long */
        switch (ftype_type) {
            case _PLUS_FUN:             return fun_plus_ulong;                  break;
            case _MINUS_FUN:            return fun_minus_ulong;                 break;
            case _MULTIPLIES_FUN:       return fun_multiplies_ulong;            break;
            case _DIVIDES_FUN:          return fun_divides_ulong;               break;
            case _MODULUS_FUN:          return fun_modulus_ulong;               break;
            case _EQUAL_FUN:            return fun_equal_ulong;                 break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_ulong;             break;
            case _GREATER_FUN:          return fun_greater_ulong;               break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_ulong;         break;
            case _LESS_FUN:             return fun_less_ulong;                  break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_ulong;            break;
            default: break;
        }
    } else if (strncmp(s_typename, _FLOAT_TYPE, _TYPE_NAME_SIZE) == 0) {                /* float */
        switch (ftype_type) {
            case _PLUS_FUN:             return fun_plus_float;                  break;
            case _MINUS_FUN:            return fun_minus_float;                 break;
            case _MULTIPLIES_FUN:       return fun_multiplies_float;            break;
            case _DIVIDES_FUN:          return fun_divides_float;               break;
            case _EQUAL_FUN:            return fun_equal_float;                 break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_float;             break;
            case _GREATER_FUN:          return fun_greater_float;               break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_float;         break;
            case _LESS_FUN:             return fun_less_float;                  break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_float;            break;
            default: break;
        }
    } else if (strncmp(s_typename, _DOUBLE_TYPE, _TYPE_NAME_SIZE) == 0) {               /* double */
        switch (ftype_type) {
            case _PLUS_FUN:             return fun_plus_double;                 break;
            case _MINUS_FUN:            return fun_minus_double;                break;
            case _MULTIPLIES_FUN:       return fun_multiplies_double;           break;
            case _DIVIDES_FUN:          return fun_divides_double;              break;
            case _EQUAL_FUN:            return fun_equal_double;                break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_double;            break;
            case _GREATER_FUN:          return fun_greater_double;              break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_double;        break;
            case _LESS_FUN:             return fun_less_double;                 break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_double;           break;
            default: break;
        }
    } else if (strncmp(s_typename, _LONG_DOUBLE_TYPE, _TYPE_NAME_SIZE) == 0) {          /* long double */
        switch (ftype_type) {
            case _PLUS_FUN:             return fun_plus_long_double;            break;
            case _MINUS_FUN:            return fun_minus_long_double;           break;
            case _MULTIPLIES_FUN:       return fun_multiplies_long_double;      break;
            case _DIVIDES_FUN:          return fun_divides_long_double;         break;
            case _EQUAL_FUN:            return fun_equal_long_double;           break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_long_double;       break;
            case _GREATER_FUN:          return fun_greater_long_double;         break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_long_double;   break;
            case _LESS_FUN:             return fun_less_long_double;            break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_long_double;      break;
            default: break;
        }
    } else if (strncmp(s_typename, _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {             /* c-string */
        switch (ftype_type) {
            case _EQUAL_FUN:            return fun_equal_cstr;                  break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_cstr;              break;
            case _GREATER_FUN:          return fun_greater_cstr;                break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_cstr;          break;
            case _LESS_FUN:             return fun_less_cstr;                   break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_cstr;             break;
            default: break;
        }
    } else if (strncmp(s_typename, _POINTER_TYPE, _TYPE_NAME_SIZE) == 0) {              /* void* */
        switch (ftype_type) {
            case _EQUAL_FUN:            return fun_equal_pointer;               break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_pointer;           break;
            case _GREATER_FUN:          return fun_greater_pointer;             break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_pointer;       break;
            case _LESS_FUN:             return fun_less_pointer;                break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_pointer;          break;
            default: break;
        }
    } else if (strncmp(s_typename, _CSTL_BOOL_TYPE, _TYPE_NAME_SIZE) == 0) {            /* bool_t */
        switch (ftype_type) {
            case _LOGICAL_AND_FUN:      return fun_logical_and_cstl_bool;       break;
            case _LOGICAL_OR_FUN:       return fun_logical_or_cstl_bool;        break;
            default: break;
        }
#ifndef _MSC_VER
    } else if (strncmp(s_typename, _BOOL_TYPE, _TYPE_NAME_SIZE) == 0) {                 /* _Bool */
        switch (ftype_type) {
            case _LOGICAL_AND_FUN:      return fun_logical_and_bool;            break;
            case _LOGICAL_OR_FUN:       return fun_logical_or_bool;             break;
            default: break;
        }
    } else if (strncmp(s_typename, _LONG_LONG_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _LONG_LONG_INT_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _SIGNED_LONG_LONG_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _SIGNED_LONG_LONG_INT_TYPE, _TYPE_NAME_SIZE) == 0) { /* long long */
        switch (ftype_type) {
            case _PLUS_FUN:             return fun_plus_long_long;              break;
            case _MINUS_FUN:            return fun_minus_long_long;             break;
            case _MULTIPLIES_FUN:       return fun_multiplies_long_long;        break;
            case _DIVIDES_FUN:          return fun_divides_long_long;           break;
            case _MODULUS_FUN:          return fun_modulus_long_long;           break;
            case _EQUAL_FUN:            return fun_equal_long_long;             break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_long_long;         break;
            case _GREATER_FUN:          return fun_greater_long_long;           break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_long_long;     break;
            case _LESS_FUN:             return fun_less_long_long;              break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_long_long;        break;
            default: break;
        }
    } else if (strncmp(s_typename, _UNSIGNED_LONG_LONG_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _UNSIGNED_LONG_LONG_INT_TYPE, _TYPE_NAME_SIZE) == 0) {/* unsigned long long */
        switch (ftype_type) {
            case _PLUS_FUN:             return fun_plus_ulong_long;             break;
            case _MINUS_FUN:            return fun_minus_ulong_long;            break;
            case _MULTIPLIES_FUN:       return fun_multiplies_ulong_long;       break;
            case _DIVIDES_FUN:          return fun_divides_ulong_long;          break;
            case _MODULUS_FUN:          return fun_modulus_ulong_long;          break;
            case _EQUAL_FUN:            return fun_equal_ulong_long;            break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_ulong_long;        break;
            case _GREATER_FUN:          return fun_greater_ulong_long;          break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_ulong_long;    break;
            case _LESS_FUN:             return fun_less_ulong_long;             break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_ulong_long;       break;
            default: break;
        }
#endif
    } else if (strncmp(s_typename, _VECTOR_TYPE, _TYPE_NAME_SIZE) == 0) {               /* vector_t */
        switch (ftype_type) {
            case _EQUAL_FUN:            return fun_equal_vector;                break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_vector;            break;
            case _GREATER_FUN:          return fun_greater_vector;              break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_vector;        break;
            case _LESS_FUN:             return fun_less_vector;                 break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_vector;           break;
            default: break;
        }
    } else if (strncmp(s_typename, _DEQUE_TYPE, _TYPE_NAME_SIZE) == 0) {                /* deque_t */
        switch (ftype_type) {
            case _EQUAL_FUN:            return fun_equal_deque;                 break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_deque;             break;
            case _GREATER_FUN:          return fun_greater_deque;               break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_deque;         break;
            case _LESS_FUN:             return fun_less_deque;                  break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_deque;            break;
            default: break;
        }
    } else if (strncmp(s_typename, _LIST_TYPE, _TYPE_NAME_SIZE) == 0) {                 /* list_t */
        switch (ftype_type) {
            case _EQUAL_FUN:            return fun_equal_list;                  break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_list;              break;
            case _GREATER_FUN:          return fun_greater_list;                break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_list;          break;
            case _LESS_FUN:             return fun_less_list;                   break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_list;             break;
            default: break;
        }
    } else if (strncmp(s_typename, _SLIST_TYPE, _TYPE_NAME_SIZE) == 0) {                /* slist_t */
        switch (ftype_type) {
            case _EQUAL_FUN:            return fun_equal_slist;                 break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_slist;             break;
            case _GREATER_FUN:          return fun_greater_slist;               break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_slist;         break;
            case _LESS_FUN:             return fun_less_slist;                  break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_slist;            break;
            default: break;
        }
    } else if (strncmp(s_typename, _QUEUE_TYPE, _TYPE_NAME_SIZE) == 0) {                /* queue_t */
        switch (ftype_type) {
            case _EQUAL_FUN:            return fun_equal_queue;                 break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_queue;             break;
            case _GREATER_FUN:          return fun_greater_queue;               break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_queue;         break;
            case _LESS_FUN:             return fun_less_queue;                  break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_queue;            break;
            default: break;
        }
    } else if (strncmp(s_typename, _STACK_TYPE, _TYPE_NAME_SIZE) == 0) {                /* stack_t */
        switch (ftype_type) {
            case _EQUAL_FUN:            return fun_equal_stack;                 break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_stack;             break;
            case _GREATER_FUN:          return fun_greater_stack;               break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_stack;         break;
            case _LESS_FUN:             return fun_less_stack;                  break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_stack;            break;
            default: break;
        }
    } else if (strncmp(s_typename, _PAIR_TYPE, _TYPE_NAME_SIZE) == 0) {                 /* pair_t */
        switch (ftype_type) {
            case _EQUAL_FUN:            return fun_equal_pair;                  break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_pair;              break;
            case _GREATER_FUN:          return fun_greater_pair;                break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_pair;          break;
            case _LESS_FUN:             return fun_less_pair;                   break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_pair;             break;
            default: break;
        }
    } else if (strncmp(s_typename, _SET_TYPE, _TYPE_NAME_SIZE) == 0) {                  /* set_t */
        switch (ftype_type) {
            case _EQUAL_FUN:            return fun_equal_set;                   break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_set;               break;
            case _GREATER_FUN:          return fun_greater_set;                 break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_set;           break;
            case _LESS_FUN:             return fun_less_set;                    break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_set;              break;
            default: break;
        }
    } else if (strncmp(s_typename, _MAP_TYPE, _TYPE_NAME_SIZE) == 0) {                  /* map_t */
        switch (ftype_type) {
            case _EQUAL_FUN:            return fun_equal_map;                   break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_map;               break;
            case _GREATER_FUN:          return fun_greater_map;                 break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_map;           break;
            case _LESS_FUN:             return fun_less_map;                    break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_map;              break;
            default: break;
        }
    } else if (strncmp(s_typename, _MULTISET_TYPE, _TYPE_NAME_SIZE) == 0) {             /* multiset_t */
        switch (ftype_type) {
            case _EQUAL_FUN:            return fun_equal_multiset;              break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_multiset;          break;
            case _GREATER_FUN:          return fun_greater_multiset;            break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_multiset;      break;
            case _LESS_FUN:             return fun_less_multiset;               break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_multiset;         break;
            default: break;
        }
    } else if (strncmp(s_typename, _MULTIMAP_TYPE, _TYPE_NAME_SIZE) == 0) {             /* multimap_t */
        switch (ftype_type) {
            case _EQUAL_FUN:            return fun_equal_multimap;              break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_multimap;          break;
            case _GREATER_FUN:          return fun_greater_multimap;            break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_multimap;      break;
            case _LESS_FUN:             return fun_less_multimap;               break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_multimap;         break;
            default: break;
        }
    } else if (strncmp(s_typename, _HASH_SET_TYPE, _TYPE_NAME_SIZE) == 0) {             /* hash_set_t */
        switch (ftype_type) {
            case _EQUAL_FUN:            return fun_equal_hash_set;              break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_hash_set;          break;
            case _GREATER_FUN:          return fun_greater_hash_set;            break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_hash_set;      break;
            case _LESS_FUN:             return fun_less_hash_set;               break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_hash_set;         break;
            default: break;
        }
    } else if (strncmp(s_typename, _HASH_MAP_TYPE, _TYPE_NAME_SIZE) == 0) {             /* hash_map_t */
        switch (ftype_type) {
            case _EQUAL_FUN:            return fun_equal_hash_map;              break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_hash_map;          break;
            case _GREATER_FUN:          return fun_greater_hash_map;            break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_hash_map;      break;
            case _LESS_FUN:             return fun_less_hash_map;               break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_hash_map;         break;
            default: break;
        }
    } else if (strncmp(s_typename, _HASH_MULTISET_TYPE, _TYPE_NAME_SIZE) == 0) {        /* hash_multiset_t */
        switch (ftype_type) {
            case _EQUAL_FUN:            return fun_equal_hash_multiset;         break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_hash_multiset;     break;
            case _GREATER_FUN:          return fun_greater_hash_multiset;       break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_hash_multiset; break;
            case _LESS_FUN:             return fun_less_hash_multiset;          break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_hash_multiset;    break;
            default: break;
        }
    } else if (strncmp(s_typename, _HASH_MULTIMAP_TYPE, _TYPE_NAME_SIZE) == 0) {        /* hash_multimap_t */
        switch (ftype_type) {
            case _EQUAL_FUN:            return fun_equal_hash_multimap;         break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_hash_multimap;     break;
            case _GREATER_FUN:          return fun_greater_hash_multimap;       break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_hash_multimap; break;
            case _LESS_FUN:             return fun_less_hash_multimap;          break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_hash_multimap;    break;
            default: break;
        }
    } else if (strncmp(s_typename, _STRING_TYPE, _TYPE_NAME_SIZE) == 0) {               /* string_t */
        switch (ftype_type) {
            case _EQUAL_FUN:            return fun_equal_string;                break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_string;            break;
            case _GREATER_FUN:          return fun_greater_string;              break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_string;        break;
            case _LESS_FUN:             return fun_less_string;                 break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_string;           break;
            default: break;
        }
    } else if (strncmp(s_typename, _BASIC_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {          /* basic_string_t */
        switch (ftype_type) {
            case _EQUAL_FUN:            return fun_equal_basic_string;          break;
            case _NOT_EQUAL_FUN:        return fun_not_equal_basic_string;      break;
            case _GREATER_FUN:          return fun_greater_basic_string;        break;
            case _GREATER_EQUAL_FUN:    return fun_greater_equal_basic_string;  break;
            case _LESS_FUN:             return fun_less_basic_string;           break;
            case _LESS_EQUAL_FUN:       return fun_less_equal_basic_string;     break;
            default: break;
        }
    }

    if (pt_typeinfo != NULL && pt_typeinfo->_pt_type != NULL &&
        pt_typeinfo->_t_style == _TYPE_USER_DEFINE && ftype_type == _LESS_FUN) {
        return pt_typeinfo->_pt_type->_t_typeless;
    }

    return fun_default_binary;
}


/**
 * Increase.
 */
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

    *(float*)pv_output = *(float*)cpv_input + 1.0f;
}

void _fun_increase_double(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(double*)pv_output = *(double*)cpv_input + 1.0;
}

#ifndef _MSC_VER
void _fun_increase_long_long(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(long long*)pv_output = *(long long*)cpv_input + 1;
}

void _fun_increase_ulong_long(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);

    *(unsigned long long*)pv_output = *(unsigned long long*)cpv_input + 1;
}
#endif

/** local function implementation section **/

/** eof **/

