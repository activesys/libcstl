/*
 *  The implementation of basic_string auxiliary functions.
 *  Copyright (C)  2008 - 2013  Wangbo
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

#include <cstl/cstl_basic_string_iterator.h>
#include <cstl/cstl_basic_string_private.h>
#include <cstl/cstl_basic_string.h>

#include "cstl_basic_string_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
#ifndef NDEBUG
/**
 * Test basic_string_t is created by create_basic_string.
 */
bool_t _basic_string_is_created(const basic_string_t* cpt_basic_string)
{
    assert(cpt_basic_string != NULL);

    if (cpt_basic_string->_t_typeinfo._t_style != _TYPE_C_BUILTIN &&
        cpt_basic_string->_t_typeinfo._t_style != _TYPE_CSTL_BUILTIN &&
        cpt_basic_string->_t_typeinfo._t_style != _TYPE_USER_DEFINE) {
        return false;
    }

    if (cpt_basic_string->_t_typeinfo._pt_type == NULL) {
        return false;
    }

    if (cpt_basic_string->_pby_string != NULL) {
        return false;
    }

    return true;
}

/**
 * Test basic_string is initialized by basic_string initialization functions.
 */
bool_t _basic_string_is_inited(const basic_string_t* cpt_basic_string)
{
    assert(cpt_basic_string != NULL);

    if (cpt_basic_string->_t_typeinfo._t_style != _TYPE_C_BUILTIN &&
        cpt_basic_string->_t_typeinfo._t_style != _TYPE_CSTL_BUILTIN &&
        cpt_basic_string->_t_typeinfo._t_style != _TYPE_USER_DEFINE) {
        return false;
    }

    if (cpt_basic_string->_t_typeinfo._pt_type == NULL) {
        return false;
    }

    if (cpt_basic_string->_pby_string == NULL) {
        return false;
    }

    return !_basic_string_rep_is_leaked(_basic_string_rep_get_representation(cpt_basic_string->_pby_string));
}


/**
 * Test iterator referenced data is within the basic_string.
 */
bool_t _iterator_belong_to_basic_string(
    const basic_string_t* cpt_basic_string, basic_string_iterator_t t_iter)
{
    /* comment for 2.2
    assert(cpt_basic_string != NULL);
    assert(_BASIC_STRING_ITERATOR_CONTAINER_TYPE(t_iter) == _BASIC_STRING_CONTAINER &&
           _BASIC_STRING_ITERATOR_ITERATOR_TYPE(t_iter) == _RANDOM_ACCESS_ITERATOR &&
           _BASIC_STRING_ITERATOR_CONTAINER(t_iter) == cpt_basic_string);

    return true;
    */
    return false;
}

/**
 * Test the type that saved in the basic_string container is same.
 */
bool_t _basic_string_same_type(const basic_string_t* cpt_first, const basic_string_t* cpt_second)
{
    assert(cpt_first != NULL);
    assert(cpt_second != NULL);
    assert(_basic_string_is_inited(cpt_first) || _basic_string_is_created(cpt_first));
    assert(_basic_string_is_inited(cpt_second) || _basic_string_is_created(cpt_second));

    if (cpt_first == cpt_second) {
        return true;
    }

    return (cpt_first->_t_typeinfo._pt_type == cpt_second->_t_typeinfo._pt_type) &&
           (cpt_first->_t_typeinfo._t_style == cpt_second->_t_typeinfo._t_style) &&
           _type_is_same(_GET_BASIC_STRING_TYPE_NAME(cpt_first), _GET_BASIC_STRING_TYPE_NAME(cpt_second));
}
#endif /* NDEBUG */

/**
 * Get the value string length.
 */
size_t _basic_string_get_value_string_length(const basic_string_t* cpt_basic_string, const void* cpv_value_string)
{
    /* comment for 2.2
    size_t t_typesize = 0;
    size_t t_length = 0;

    assert(cpt_basic_string != NULL);
    assert(cpv_value_string != NULL);

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    / * char type * /
    if (strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string), _CHAR_TYPE, _TYPE_NAME_SIZE) == 0) {
        assert(t_typesize == 1);
        return strlen(cpv_value_string);
    } else if (strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
    / * char* type * /
        char** ps_terminator = NULL;

        for (ps_terminator = (char**)cpv_value_string; *ps_terminator != NULL; ++ps_terminator) {
            t_length++;
        }

        return t_length;
    } else if (_GET_BASIC_STRING_TYPE_STYLE(cpt_basic_string) == _TYPE_C_BUILTIN) {
        _byte_t* pby_terminator = NULL;

        pby_terminator = (_byte_t*)_alloc_allocate(&((basic_string_t*)cpt_basic_string)->_vec_base._t_allocator, t_typesize, 1);
        assert(pby_terminator != NULL);
        memset(pby_terminator, 0x00, t_typesize);

        while (memcmp(pby_terminator, (_byte_t*)cpv_value_string + t_length * t_typesize, t_typesize) != 0) {
            t_length++;
        }

        _alloc_deallocate(&((basic_string_t*)cpt_basic_string)->_vec_base._t_allocator, pby_terminator, t_typesize, 1);

        return t_length;
    } else {
        _byte_t** ppby_terminator = NULL;

        for (ppby_terminator = (_byte_t**)cpv_value_string; *ppby_terminator != NULL; ++ppby_terminator) {
            t_length++;
        }

        return t_length;
    }
    */
    return 0;
}

/**
 * Obtain data from variable argument list, the data type and basic_string element data type are same.
 */
void _basic_string_get_varg_value_auxiliary(basic_string_t* pt_basic_string, va_list val_elemlist, void* pv_varg)
{
    assert(pt_basic_string != NULL);
    assert(pv_varg != NULL);
    assert(_basic_string_is_inited(pt_basic_string) || _basic_string_is_created(pt_basic_string));

    _basic_string_init_elem_auxiliary(pt_basic_string, pv_varg);
    _type_get_varg_value(&pt_basic_string->_t_typeinfo, val_elemlist, pv_varg);
}

/**
 * Destroy data, the data type and basic_string element data type are same.
 */
void _basic_string_destroy_varg_value_auxiliary(basic_string_t* pt_basic_string, void* pv_varg)
{
    bool_t b_result = false;

    assert(pt_basic_string != NULL);
    assert(pv_varg != NULL);
    assert(_basic_string_is_inited(pt_basic_string) || _basic_string_is_created(pt_basic_string));

    b_result = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
    _GET_BASIC_STRING_TYPE_DESTROY_FUNCTION(pt_basic_string)(pv_varg, &b_result);
    assert(b_result);
}

/**
 * Initialize data within string according to data type of basic_string.
 */
void _basic_string_init_elem_range_auxiliary(basic_string_t* pt_basic_string, _byte_t* pby_string, size_t t_length)
{
    size_t   i = 0;
    _byte_t* pby_pos = NULL;

    assert(pt_basic_string != NULL);
    assert(pby_string != NULL);
    assert(_basic_string_is_inited(pt_basic_string) || _basic_string_is_created(pt_basic_string));

    /* initialize new elements */
    if (_GET_BASIC_STRING_TYPE_STYLE(pt_basic_string) == _TYPE_CSTL_BUILTIN) {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_BASIC_STRING_TYPE_NAME(pt_basic_string), s_elemtypename);

        for (i = 0, pby_pos = pby_string; i < t_length; ++i, pby_pos += _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string)) {
            _GET_BASIC_STRING_TYPE_INIT_FUNCTION(pt_basic_string)(pby_pos, s_elemtypename);
        }
    } else {
        for (i = 0, pby_pos = pby_string; i < t_length; ++i, pby_pos += _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string)) {
            bool_t b_result = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
            _GET_BASIC_STRING_TYPE_INIT_FUNCTION(pt_basic_string)(pby_pos, &b_result);
            assert(b_result);
        }
    }
}

/** local function implementation section **/

/** eof **/

