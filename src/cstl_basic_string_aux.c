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
#include <cstl/cstring.h>

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
 * Test iterator referenced data is within the basic_string.
 */
bool_t _basic_string_iterator_belong_to_basic_string(
    const basic_string_t* cpt_basic_string, basic_string_iterator_t it_iter)
{
    _byte_t* pby_begin = NULL;
    _byte_t* pby_end = NULL;

    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));
    assert(_BASIC_STRING_ITERATOR_CONTAINER_TYPE(it_iter) == _BASIC_STRING_CONTAINER);
    assert(_BASIC_STRING_ITERATOR_ITERATOR_TYPE(it_iter) == _RANDOM_ACCESS_ITERATOR);
    assert(_BASIC_STRING_ITERATOR_CONTAINER(it_iter) == cpt_basic_string);

    pby_begin = cpt_basic_string->_pby_string;
    pby_end = pby_begin + _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string) * basic_string_size(cpt_basic_string);
    if (_BASIC_STRING_ITERATOR_COREPOS(it_iter) >= pby_begin &&
        _BASIC_STRING_ITERATOR_COREPOS(it_iter) <= pby_end) {
        return true;
    } else {
        return false;
    }
}

/**
 * Test the type that saved in the basic_string container and referenced by it_iter are same.
 */
bool_t _basic_string_same_iterator_type(const basic_string_t* cpt_basic_string, iterator_t it_iter)
{
    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string) || _basic_string_is_created(cpt_basic_string));
    assert(_iterator_is_valid(it_iter));

    return _type_is_same_ex(&cpt_basic_string->_t_typeinfo, _iterator_get_typeinfo(it_iter));
}

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
    size_t t_typesize = 0;
    size_t t_len = 0;

    assert(cpt_basic_string != NULL);
    assert(cpv_value_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string) || _basic_string_is_created(cpt_basic_string));

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    if (strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string), _CHAR_TYPE, _TYPE_NAME_SIZE) == 0) {
        /* char type */
        assert(t_typesize == 1);
        return strlen(cpv_value_string);
    } else if (strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        /* char* type */
        char** ps_terminator = NULL;

        for (ps_terminator = (char**)cpv_value_string; *ps_terminator != NULL; ++ps_terminator) {
            t_len++;
        }

        return t_len;
    } else if (_GET_BASIC_STRING_TYPE_STYLE(cpt_basic_string) == _TYPE_C_BUILTIN) {
        _byte_t* pby_terminator = NULL;

        pby_terminator = (_byte_t*)malloc(t_typesize);
        assert(pby_terminator != NULL);
        memset(pby_terminator, 0x00, t_typesize);

        while (memcmp(pby_terminator, (_byte_t*)cpv_value_string + t_len * t_typesize, t_typesize) != 0) {
            t_len++;
        }

        free(pby_terminator);

        return t_len;
    } else {
        _byte_t** ppby_terminator = NULL;

        for (ppby_terminator = (_byte_t**)cpv_value_string; *ppby_terminator != NULL; ++ppby_terminator) {
            t_len++;
        }

        return t_len;
    }
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
    bool_t   b_result = false;
    _byte_t* pby_terminator = NULL;

    assert(pt_basic_string != NULL);
    assert(pv_varg != NULL);
    assert(_basic_string_is_inited(pt_basic_string) || _basic_string_is_created(pt_basic_string));

    pby_terminator = pt_basic_string->_pby_string +
        basic_string_size(pt_basic_string) * _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
    b_result = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);

    if (memcmp(pv_varg, pby_terminator, _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string)) != 0) {
        _GET_BASIC_STRING_TYPE_DESTROY_FUNCTION(pt_basic_string)(pv_varg, &b_result);
    }
    assert(b_result);
}

/**
 * Initialize data within string according to data type of basic_string.
 */
void _basic_string_init_elem_range_auxiliary(basic_string_t* pt_basic_string, _byte_t* pby_string, size_t t_len)
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

        for (i = 0, pby_pos = pby_string; i < t_len; ++i, pby_pos += _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string)) {
            _GET_BASIC_STRING_TYPE_INIT_FUNCTION(pt_basic_string)(pby_pos, s_elemtypename);
        }
    } else {
        for (i = 0, pby_pos = pby_string; i < t_len; ++i, pby_pos += _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string)) {
            bool_t b_result = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
            _GET_BASIC_STRING_TYPE_INIT_FUNCTION(pt_basic_string)(pby_pos, &b_result);
            assert(b_result);
        }
    }
}

/**
 * Detach this basic_string from sharable string.
 */
void _basic_string_detach(basic_string_t* pt_basic_string)
{
    _basic_string_rep_t* prep = NULL;

    assert(pt_basic_string != NULL);
    assert(_basic_string_is_inited(pt_basic_string));

    prep = _basic_string_rep_get_representation(pt_basic_string->_pby_string);
    if (_basic_string_rep_is_shared(prep)) {
        /* clone */
        _basic_string_rep_t* prep_clone = _basic_string_clone_representation(pt_basic_string, 0);
        _basic_string_rep_set_sharable(prep_clone);
        /* reduce shared */
        _basic_string_rep_reduce_shared(
            prep, _GET_BASIC_STRING_TYPE_DESTROY_FUNCTION(pt_basic_string), &pt_basic_string->_t_typeinfo);
        /* set new rep */
        pt_basic_string->_pby_string = _basic_string_rep_get_data(prep_clone);
    }
}

/**
 * Check whether the basic_string_t is shared.
 */
bool_t _basic_string_is_shared(const basic_string_t* cpt_basic_string)
{
    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));

    return _basic_string_rep_is_shared(_basic_string_rep_get_representation(cpt_basic_string->_pby_string));
}

/**
 * Clone representation.
 */
_basic_string_rep_t* _basic_string_clone_representation(const basic_string_t* cpt_basic_string, size_t t_addsize)
{
    _basic_string_rep_t* prep_clone = NULL;
    _byte_t*             pby_dest = NULL;
    _byte_t*             pby_src = NULL;

    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));

    prep_clone = _create_basic_string_representation(
        basic_string_size(cpt_basic_string) + t_addsize,
        basic_string_capacity(cpt_basic_string),
        _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string));
    assert(prep_clone != NULL);

    pby_dest = _basic_string_rep_get_data(prep_clone);
    pby_src = cpt_basic_string->_pby_string;
    _basic_string_init_elem_range_auxiliary((basic_string_t*)cpt_basic_string, pby_dest, basic_string_size(cpt_basic_string));
    _basic_string_copy_substring_auxiliary(cpt_basic_string, pby_dest, pby_src, basic_string_size(cpt_basic_string));
    _basic_string_rep_set_length(prep_clone, basic_string_size(cpt_basic_string));
    /* The refcount will be set outof this function, so we do not set here */

    return prep_clone;
}

/**
 * Copy elements from source.
 */
void _basic_string_copy_substring_auxiliary(
    const basic_string_t* cpt_basic_string, _byte_t* pby_dest, _byte_t* pby_src, size_t t_len)
{
    size_t i = 0;
    _byte_t* pby_terminator = NULL;

    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string) || _basic_string_is_created(cpt_basic_string));
    assert(pby_dest != NULL);
    assert(pby_src != NULL);
    assert(t_len <= basic_string_max_size(cpt_basic_string));

    pby_terminator = cpt_basic_string->_pby_string +
        basic_string_size(cpt_basic_string) * _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);

    /*
     * It does not require judgment terminator, 
     * when the type style is c built-in type, 
     * which improves efficiency.
     */
    if (_GET_BASIC_STRING_TYPE_STYLE(cpt_basic_string) == _TYPE_C_BUILTIN &&
        strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) != 0) {
        for (i = 0; i < t_len; ++i) {
            bool_t b_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
            _GET_BASIC_STRING_TYPE_COPY_FUNCTION(cpt_basic_string)(pby_dest, pby_src, &b_result);
            assert(b_result);

            pby_dest += _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
            pby_src += _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
        }
    } else {
        for (i = 0; i < t_len; ++i) {
            _basic_string_copy_elem_with_terminator(cpt_basic_string, pby_dest, pby_src, pby_terminator);

            pby_dest += _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
            pby_src += _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
        }
    }
}

void _basic_string_copy_substring_backward_auxiliary(
    const basic_string_t* cpt_basic_string, _byte_t* pby_dest, _byte_t* pby_src, size_t t_len)
{
    size_t   i = 0;
    _byte_t* pby_terminator = NULL;

    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string) || _basic_string_is_created(cpt_basic_string));
    assert(pby_dest != NULL);
    assert(pby_src != NULL);
    assert(t_len <= basic_string_max_size(cpt_basic_string));

    pby_terminator = cpt_basic_string->_pby_string +
        basic_string_size(cpt_basic_string) * _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    pby_dest = pby_dest + (t_len - 1) * _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    pby_src = pby_src + (t_len - 1) * _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);

    if (_GET_BASIC_STRING_TYPE_STYLE(cpt_basic_string) == _TYPE_C_BUILTIN &&
        strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) != 0) {
        for (i = 0; i < t_len; ++i) {
            bool_t b_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
            _GET_BASIC_STRING_TYPE_COPY_FUNCTION(cpt_basic_string)(pby_dest, pby_src, &b_result);
            assert(b_result);

            pby_dest -= _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
            pby_src -= _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
        }
    } else {
        for (i = 0; i < t_len; ++i) {
            _basic_string_copy_elem_with_terminator(cpt_basic_string, pby_dest, pby_src, pby_terminator);

            pby_dest -= _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
            pby_src -= _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
        }
    }
}

void _basic_string_copy_subcstr_auxiliary(
    const basic_string_t* cpt_basic_string, _byte_t* pby_dest, const void* cpv_value_string, size_t t_len)
{
    size_t   i = 0;
    size_t   t_typesize = 0;
    bool_t   b_result = false;
    int      n_dest_terminator = 0;
    _byte_t* pby_terminator = NULL;

    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string) || _basic_string_is_created(cpt_basic_string));
    assert(pby_dest != NULL);
    assert(cpv_value_string != NULL);
    assert(t_len <= basic_string_max_size(cpt_basic_string));

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    pby_terminator = cpt_basic_string->_pby_string + basic_string_size(cpt_basic_string) * t_typesize;
    /* char* */
    if (strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        for (i = 0; i < t_len; ++i) {
            n_dest_terminator = memcmp(pby_terminator, pby_dest + i * t_typesize, t_typesize);

            if (n_dest_terminator != 0 && *((char**)cpv_value_string + i) != NULL) {
                string_assign_cstr((string_t*)(pby_dest + i * t_typesize), *((char**)cpv_value_string + i));
            } else if (n_dest_terminator != 0 && *((char**)cpv_value_string + i) == NULL) {
                _string_destroy_auxiliary((string_t*)(pby_dest + i * t_typesize));
                memcpy(pby_dest + i * t_typesize, pby_terminator, t_typesize);
            } else if (n_dest_terminator == 0 && *((char**)cpv_value_string + i) != NULL) {
                _basic_string_init_elem_auxiliary((basic_string_t*)cpt_basic_string, pby_dest + i * t_typesize);
                string_assign_cstr((string_t*)(pby_dest + i * t_typesize), *((char**)cpv_value_string + i));
            }
        }
    } else if (_GET_BASIC_STRING_TYPE_STYLE(cpt_basic_string) == _TYPE_C_BUILTIN) {
        for (i = 0; i < t_len; ++i) {
            b_result = t_typesize;
            _GET_BASIC_STRING_TYPE_COPY_FUNCTION(cpt_basic_string)(
                pby_dest + i * t_typesize, (_byte_t*)cpv_value_string + i * t_typesize, &b_result);
            assert(b_result);
        }
    } else {
        for (i = 0; i < t_len; ++i) {
            n_dest_terminator = memcmp(pby_terminator, pby_dest + i * t_typesize, t_typesize);
            b_result = t_typesize;

            if (n_dest_terminator != 0 && *((_byte_t**)cpv_value_string + i) != NULL) {
                _GET_BASIC_STRING_TYPE_COPY_FUNCTION(cpt_basic_string)(
                    pby_dest + i * t_typesize, *((_byte_t**)cpv_value_string + i), &b_result);
                assert(b_result);
            } else if (n_dest_terminator != 0 && *((_byte_t**)cpv_value_string + i) == NULL) {
                /* NOTE:
                 * The elements are inited, so it must be destroied before
                 * it is seted to 0x00 for preventing memory leak.
                 * */
                _GET_BASIC_STRING_TYPE_DESTROY_FUNCTION(cpt_basic_string)(pby_dest + i * t_typesize, &b_result);
                assert(b_result);
                /* set terminator for NULL */
                memcpy(pby_dest + i * t_typesize, pby_terminator, t_typesize);
            } else if (n_dest_terminator == 0 && *((_byte_t**)cpv_value_string + i) != NULL) {
                _basic_string_init_elem_auxiliary((basic_string_t*)cpt_basic_string, pby_dest + i * t_typesize);
                _GET_BASIC_STRING_TYPE_COPY_FUNCTION(cpt_basic_string)(
                    pby_dest + i * t_typesize, *((_byte_t**)cpv_value_string + i), &b_result);
                assert(b_result);
            }
        }
    }
}

void _basic_string_copy_range_auxiliary(
    const basic_string_t* cpt_basic_string, _byte_t* pby_dest, iterator_t it_begin, iterator_t it_end)
{
    iterator_t it;
    _byte_t*   pby_terminator = NULL;

    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string) || _basic_string_is_created(cpt_basic_string));
    assert(pby_dest != NULL);
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    pby_terminator = cpt_basic_string->_pby_string +
        basic_string_size(cpt_basic_string) * _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);

    /*
     * It does not require judgment terminator, 
     * when the type style is c built-in type, 
     * which improves efficiency.
     */
    if (_GET_BASIC_STRING_TYPE_STYLE(cpt_basic_string) == _TYPE_C_BUILTIN &&
        strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) != 0) {
        for (it = it_begin; !iterator_equal(it, it_end); it = iterator_next(it)) {
            bool_t b_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
            _GET_BASIC_STRING_TYPE_COPY_FUNCTION(cpt_basic_string)(
                pby_dest, _iterator_get_pointer_ignore_cstr(it), &b_result);
            assert(b_result);

            pby_dest += _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
        }
    } else {
        for (it = it_begin; !iterator_equal(it, it_end); it = iterator_next(it)) {
            _basic_string_copy_elem_with_terminator(
                cpt_basic_string, pby_dest, (_byte_t*)_iterator_get_pointer_ignore_cstr(it), pby_terminator);

            pby_dest += _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
        }
    }
}

void _basic_string_copy_elem_auxiliary(
    const basic_string_t* cpt_basic_string, _byte_t* pby_dest, size_t t_count, va_list val_elemlist)
{
    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string) || _basic_string_is_created(cpt_basic_string));
    assert(pby_dest != NULL);
    assert(t_count <= basic_string_max_size(cpt_basic_string));

    if (t_count > 0) {
        /* get varg value only once */
        size_t   i = 0;
        _byte_t* pby_terminator = NULL;
        void*    pv_varg = malloc(_GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string));
        assert(pv_varg != NULL);
        _basic_string_get_varg_value_auxiliary((basic_string_t*)cpt_basic_string, val_elemlist, pv_varg);

        /* copy varg value to each element */
        pby_terminator = cpt_basic_string->_pby_string +
            basic_string_size(cpt_basic_string) * _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);

        /*
         * It does not require judgment terminator, 
         * when the type style is c built-in type, 
         * which improves efficiency.
         */
        if (_GET_BASIC_STRING_TYPE_STYLE(cpt_basic_string) == _TYPE_C_BUILTIN &&
            strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) != 0) {
            for (i = 0; i < t_count; ++i) {
                bool_t b_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
                _GET_BASIC_STRING_TYPE_COPY_FUNCTION(cpt_basic_string)(pby_dest, pv_varg, &b_result);
                assert(b_result);

                pby_dest += _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
            }
        } else {
            for (i = 0; i < t_count; ++i) {
                _basic_string_copy_elem_with_terminator(cpt_basic_string, pby_dest, pv_varg, pby_terminator);

                pby_dest += _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
            }
        }

        /* destroy varg value and free memory */
        _basic_string_destroy_varg_value_auxiliary((basic_string_t*)cpt_basic_string, pv_varg);
        free(pv_varg);
    }
}

/**
 * Destroy elements in substring.
 */
void _basic_string_destroy_elem_range_auxiliary(
    const basic_string_t* cpt_basic_string, _byte_t* pby_del, size_t t_len)
{
    size_t   i = 0;
    _byte_t* pby_terminator = NULL;

    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string) || _basic_string_is_created(cpt_basic_string));
    assert(pby_del != NULL);
    assert(t_len <= basic_string_max_size(cpt_basic_string));

    pby_terminator = cpt_basic_string->_pby_string +
        basic_string_size(cpt_basic_string) * _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);

    if (_GET_BASIC_STRING_TYPE_STYLE(cpt_basic_string) == _TYPE_C_BUILTIN &&
        strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) != 0) {
        for (i = 0; i < t_len; ++i) {
            bool_t b_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
            _GET_BASIC_STRING_TYPE_DESTROY_FUNCTION(cpt_basic_string)(pby_del, &b_result);
            assert(b_result);

            pby_del += _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
        }
    } else {
        for (i = 0; i < t_len; ++i) {
            if (memcmp(pby_terminator, pby_del, _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string)) != 0) {
                bool_t b_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
                _GET_BASIC_STRING_TYPE_DESTROY_FUNCTION(cpt_basic_string)(pby_del, &b_result);
                assert(b_result);
            }

            pby_del += _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
        }
    }
}

/**
 * Preparation for replace.
 */
void _basic_string_replace_preparation(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_len, size_t t_replacelen)
{
    size_t   t_size = 0;
    size_t   t_newsize = 0;
    size_t   t_typesize = 0;
    _byte_t* pby_dest = NULL;
    _byte_t* pby_src = NULL;

    assert(pt_basic_string != NULL);
    assert(_basic_string_is_inited(pt_basic_string));
    assert(t_pos <= basic_string_size(pt_basic_string));

    if (t_len == NPOS || t_len + t_pos >= basic_string_size(pt_basic_string)) {
        t_len = basic_string_size(pt_basic_string) - t_pos;
    }

    t_size = basic_string_size(pt_basic_string);
    t_newsize = t_size + t_replacelen - t_len;
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);

    if (t_newsize > basic_string_capacity(pt_basic_string) || _basic_string_is_shared(pt_basic_string)) {
        _basic_string_rep_t* prep = _basic_string_rep_construct(
            pt_basic_string, t_newsize, t_newsize, basic_string_capacity(pt_basic_string));

        /* copy elements before replace range */
        pby_dest = _basic_string_rep_get_data(prep);
        pby_src = pt_basic_string->_pby_string;
        _basic_string_copy_substring_auxiliary(pt_basic_string, pby_dest, pby_src, t_pos);
        /* copy elements after replace range */
        pby_dest = _basic_string_rep_get_data(prep) + (t_pos + t_replacelen) * t_typesize;
        pby_src = pt_basic_string->_pby_string + (t_pos + t_len) * t_typesize;
        _basic_string_copy_substring_auxiliary(pt_basic_string, pby_dest, pby_src, t_size - t_pos - t_len);

        _basic_string_rep_reduce_shared(
            _basic_string_rep_get_representation(pt_basic_string->_pby_string),
            _GET_BASIC_STRING_TYPE_DESTROY_FUNCTION(pt_basic_string), &pt_basic_string->_t_typeinfo);
        pt_basic_string->_pby_string = _basic_string_rep_get_data(prep);
    } else {
        if (t_replacelen > t_len) {
            basic_string_resize(pt_basic_string, t_newsize);
            pby_dest = pt_basic_string->_pby_string + (t_pos + t_replacelen) * t_typesize;
            pby_src = pt_basic_string->_pby_string + (t_pos + t_len) * t_typesize;
            _basic_string_copy_substring_backward_auxiliary(pt_basic_string, pby_dest, pby_src, t_size - t_pos - t_len);
        } else if (t_len > t_replacelen) {
            pby_dest = pt_basic_string->_pby_string + (t_pos + t_replacelen) * t_typesize;
            pby_src = pt_basic_string->_pby_string + (t_pos + t_len) * t_typesize;
            _basic_string_copy_substring_auxiliary(pt_basic_string, pby_dest, pby_src, t_size - t_pos - t_len);
            basic_string_resize(pt_basic_string, t_newsize);
        }
    }
}

/**
 * Find element in value string/basic_string.
 */
bool_t _basic_string_substring_find(
    const basic_string_t* cpt_basic_string, size_t t_pos, const basic_string_t* cpt_find)
{
    size_t   i = 0;
    size_t   t_typesize = 0;
    bool_t   b_less = false;
    bool_t   b_greater = false;
    _byte_t* pby_string = NULL;
    _byte_t* pby_index = NULL;
    _byte_t* pby_terminator = NULL;

    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));
    assert(cpt_find != NULL);
    assert(_basic_string_is_inited(cpt_find));
    assert(_basic_string_same_type(cpt_basic_string, cpt_find));

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    pby_terminator = cpt_basic_string->_pby_string + basic_string_size(cpt_basic_string) * t_typesize;
    pby_string = cpt_basic_string->_pby_string + t_pos * t_typesize;
    pby_index = cpt_find->_pby_string;

    if (_GET_BASIC_STRING_TYPE_STYLE(cpt_basic_string) == _TYPE_C_BUILTIN &&
        strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) != 0) {
        for (i = 0; i < basic_string_size(cpt_find); ++i) {
            b_less = b_greater = t_typesize;
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pby_string, pby_index, &b_less);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pby_index, pby_string, &b_greater);
            if (!b_less && !b_greater) {
                return true;
            }

            pby_index += t_typesize;
        }
    } else {
        for (i = 0; i < basic_string_size(cpt_find); ++i) {
            int n_string_terminator = memcmp(pby_terminator, pby_string, t_typesize);
            int n_index_terminator = memcmp(pby_terminator, pby_index, t_typesize);

            if (n_string_terminator == 0 && n_index_terminator == 0) {
                return true;
            } else if (n_string_terminator != 0 && n_index_terminator != 0) {
                b_less = b_greater = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pby_string, pby_index, &b_less);
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pby_index, pby_string, &b_greater);
                if (!b_less && !b_greater) {
                    return true;
                }
            }

            pby_index += t_typesize;
        }
    }

    return false;
}

bool_t _basic_string_value_string_find(
    const basic_string_t* cpt_basic_string, size_t t_pos, const void* cpv_value_string, size_t t_len)
{
    size_t   i = 0;
    size_t   t_typesize = 0;
    bool_t   b_less = false;
    bool_t   b_greater = false;
    _byte_t* pby_string = NULL;
    _byte_t* pby_index = NULL;
    _byte_t* pby_terminator = NULL;

    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));
    assert(cpv_value_string != NULL);

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    pby_terminator = cpt_basic_string->_pby_string + basic_string_size(cpt_basic_string) * t_typesize;
    pby_string = cpt_basic_string->_pby_string + t_pos * t_typesize;
    pby_index = (_byte_t*)cpv_value_string;
    /* char* */
    if (strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        for (i = 0; i < t_len; ++i) {
            int n_string_terminator = memcmp(pby_terminator, pby_string, t_typesize);

            if (n_string_terminator == 0 && *((char**)cpv_value_string + i) == NULL) {
                return true;
            } else if (n_string_terminator != 0 && *((_byte_t**)cpv_value_string + i) != NULL) {
                if (string_equal_cstr((string_t*)pby_string, *((char**)cpv_value_string + i))) {
                    return true;
                }
            }
        }
    } else if (_GET_BASIC_STRING_TYPE_STYLE(cpt_basic_string) == _TYPE_C_BUILTIN) {
        for (i = 0; i < t_len; ++i) {
            b_less = b_greater = t_typesize;
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pby_string, pby_index, &b_less);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pby_index, pby_string, &b_greater);
            if (!b_less && !b_greater) {
                return true;
            }

            pby_index += t_typesize;
        }
    } else {
        for (i = 0; i < t_len; ++i) {
            int n_string_terminator = memcmp(pby_terminator, pby_string, t_typesize);

            if (n_string_terminator == 0 && *((_byte_t**)cpv_value_string + i) == NULL) {
                return true;
            } else if (n_string_terminator != 0 && *((_byte_t**)cpv_value_string + i) != NULL) {
                b_less = b_greater = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    pby_string, *((_byte_t**)cpv_value_string + i), &b_less);
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    *((_byte_t**)cpv_value_string + i), pby_string, &b_greater);
                if (!b_less && !b_greater) {
                    return true;
                }
            }
        }
    }

    return false;
}

/**
 * Create basic_string representation and initialize it.
 */
_basic_string_rep_t* _basic_string_rep_construct(
    const basic_string_t* cpt_basic_string, size_t t_len, size_t t_newcapacity, size_t t_oldcapacity)
{
    _basic_string_rep_t* prep = NULL;

    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string) || _basic_string_is_created(cpt_basic_string));

    prep = _create_basic_string_representation(
        t_newcapacity, t_oldcapacity, _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string));
    assert(prep != NULL);
    _basic_string_rep_set_length(prep, t_len);
    _basic_string_rep_set_sharable(prep);
    _basic_string_init_elem_range_auxiliary((basic_string_t*)cpt_basic_string, _basic_string_rep_get_data(prep), t_len);

    return prep;
}

/**
 * Copy element with terminator.
 */
void _basic_string_copy_elem_with_terminator(
    const basic_string_t* cpt_basic_string, _byte_t* pby_dest, _byte_t* pby_src, _byte_t* pby_terminator)
{
    int    n_dest_terminator = 0;
    int    n_src_terminator = 0;
    bool_t b_result = false;

    assert(cpt_basic_string != NULL);
    assert(pby_dest != NULL);
    assert(pby_src != NULL);
    assert(pby_terminator != NULL);
    assert(_basic_string_is_inited(cpt_basic_string) || _basic_string_is_created(cpt_basic_string));

    n_dest_terminator = memcmp(pby_terminator, pby_dest, _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string));
    n_src_terminator = memcmp(pby_terminator, pby_src, _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string));
    b_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);

    if (n_dest_terminator != 0 && n_src_terminator != 0) {
        _GET_BASIC_STRING_TYPE_COPY_FUNCTION(cpt_basic_string)(pby_dest, pby_src, &b_result);
    } else if (n_dest_terminator != 0 && n_src_terminator == 0) {
        _GET_BASIC_STRING_TYPE_DESTROY_FUNCTION(cpt_basic_string)(pby_dest, &b_result);
        memcpy(pby_dest, pby_terminator, _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string));
    } else if (n_dest_terminator == 0 && n_src_terminator != 0) {
        _basic_string_init_elem_auxiliary((basic_string_t*)cpt_basic_string, pby_dest);
        _GET_BASIC_STRING_TYPE_COPY_FUNCTION(cpt_basic_string)(pby_dest, pby_src, &b_result);
    }
}

/** local function implementation section **/

/** eof **/

