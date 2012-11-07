/*
 *  The implementation of private function.
 *  Copyright (C)  2008 - 2012  Wangbo
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
unary_function_t _fun_get_unary(iterator_t it_iter, fun_unary_type_t uftype_type)
{
    const char* s_typename = NULL;

    assert(_iterator_is_valid(it_iter));
    assert(uftype_type >= _NEGATE_FUN && uftype_type <= _RANDOM_NUMBER_FUN);

    if ((s_typename = _iterator_get_typebasename(it_iter))== NULL) {
        return fun_default_unary;
    }

    if (strncmp(s_typename, _CHAR_TYPE, _TYPE_NAME_SIZE) == 0 ||
        strncmp(s_typename, _SIGNED_CHAR_TYPE, _TYPE_NAME_SIZE) == 0) {                 /* char */
        if (uftype_type == _NEGATE_FUN) {
            return fun_negate_char;
        } else if (uftype_type == _INCREASE_FUN) {
            return _fun_increase_char;
        }
    } else if (strncmp(s_typename, _UNSIGNED_CHAR_TYPE, _TYPE_NAME_SIZE) == 0) {        /* unsigned char */
        if (uftype_type == _INCREASE_FUN) {
            return _fun_increase_uchar;
        }
    } else if (strncmp(s_typename, _SHORT_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _SHORT_INT_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _SIGNED_SHORT_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _SIGNED_SHORT_INT_TYPE, _TYPE_NAME_SIZE) == 0) {     /* short */
        if (uftype_type == _NEGATE_FUN) {
            return fun_negate_short;
        } else if (uftype_type == _INCREASE_FUN) {
            return _fun_increase_short;
        }
    } else if (strncmp(s_typename, _UNSIGNED_SHORT_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _UNSIGNED_SHORT_INT_TYPE, _TYPE_NAME_SIZE) == 0) {   /* unsigned short */
        if (uftype_type == _INCREASE_FUN) {
            return _fun_increase_ushort;
        }
    } else if (strncmp(s_typename, _INT_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _SIGNED_INT_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _SIGNED_TYPE, _TYPE_NAME_SIZE) == 0) {               /* int */
        if (uftype_type == _NEGATE_FUN) {
            return fun_negate_int;
        } else if (uftype_type == _INCREASE_FUN) {
            return _fun_increase_int;
        }
    } else if (strncmp(s_typename, _UNSIGNED_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _UNSIGNED_INT_TYPE, _TYPE_NAME_SIZE) == 0) {         /* unsigned int */
        if (uftype_type == _INCREASE_FUN) {
            return _fun_increase_uint;
        }
    } else if (strncmp(s_typename, _LONG_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _LONG_INT_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _SIGNED_LONG_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _SIGNED_LONG_INT_TYPE, _TYPE_NAME_SIZE) == 0) {      /* long */
        if (uftype_type == _NEGATE_FUN) {
            return fun_negate_long;
        } else if (uftype_type == _INCREASE_FUN) {
            return _fun_increase_long;
        }
    } else if (strncmp(s_typename, _UNSIGNED_LONG_TYPE, _TYPE_NAME_SIZE) == 0 ||
               strncmp(s_typename, _UNSIGNED_LONG_INT_TYPE, _TYPE_NAME_SIZE) == 0) {    /* unsigned long */
        if (uftype_type == _INCREASE_FUN) {
            return _fun_increase_ulong;
        }
    } else if (strncmp(s_typename, _FLOAT_TYPE, _TYPE_NAME_SIZE) == 0) {                /* float */
        if (uftype_type == _NEGATE_FUN) {
            return fun_negate_float;
        } else if (uftype_type == _INCREASE_FUN) {
            return _fun_increase_float;
        }
    } else if (strncmp(s_typename, _DOUBLE_TYPE, _TYPE_NAME_SIZE) == 0) {               /* double */
        if (uftype_type == _NEGATE_FUN) {
            return fun_negate_double;
        } else if (uftype_type == _INCREASE_FUN) {
            return _fun_increase_double;
        }
    } else if (strncmp(s_typename, _LONG_DOUBLE_TYPE, _TYPE_NAME_SIZE) == 0) {          /* long double */
        if (uftype_type == _NEGATE_FUN) {
            return fun_negate_long_double;
        }
    } else if (strncmp(s_typename, _BOOL_TYPE, _TYPE_NAME_SIZE) == 0) {                 /* bool_t */
        if (uftype_type == _LOGICAL_NOT_FUN) {
            return fun_logical_not_bool;
        }
    }

    return fun_default_unary;
}

/** local function implementation section **/

/** eof **/

