/*
 *  The implementation of basic_string private functions.
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
/**
 * Create basic_string representation.
 */
_basic_string_rep_t* _create_basic_string_representation(size_t t_newcapacity, size_t t_oldcapacity, size_t t_elemsize)
{
    size_t t_size = 0;
    _basic_string_rep_t* prep = NULL;

    assert(t_elemsize > 0);

    if (t_newcapacity > t_oldcapacity && t_newcapacity < t_oldcapacity * 2) {
        t_newcapacity = t_oldcapacity * 2;
    }
    t_size = (t_newcapacity + 1) * t_elemsize + sizeof(_basic_string_rep_t);

    prep = (_basic_string_rep_t*)malloc(t_size);
    if (prep == NULL) {
        return NULL;
    }
    prep->_t_capacity = t_newcapacity;
    prep->_t_elemsize = t_elemsize;
    prep->_n_refcount = -1;
    prep->_t_length = 0;

    return prep;
}

/**
 * Reduce shared and delete rep if necessary.
 */
_basic_string_rep_t* _basic_string_rep_reduce_shared(
    _basic_string_rep_t* pt_rep, ufun_t ufun_destroy, _typeinfo_t* pt_typeinfo)
{
    assert(pt_rep != NULL);
    assert(ufun_destroy != NULL);
    assert(pt_typeinfo != NULL);

    pt_rep->_n_refcount -= 1;
    if (_basic_string_rep_is_leaked(pt_rep)) {
        size_t   i = 0;
        bool_t   b_result = 0;
        _byte_t* pby_string = _basic_string_rep_get_data(pt_rep);
        _byte_t* pby_terminator = pby_string + pt_rep->_t_length * pt_rep->_t_elemsize;

        /*
         * It does not require judgment terminator,
         * when the type style is c built-in type,
         * which improves efficiency.
         */
        if (pt_typeinfo->_t_style == _TYPE_C_BUILTIN &&
            strncmp(pt_typeinfo->_pt_type->_s_typename, _C_STRING_TYPE, _TYPE_NAME_SIZE) != 0) {
            for (i = 0; i < pt_rep->_t_length; ++i) {
                b_result = pt_rep->_t_elemsize;
                ufun_destroy(pby_string, &b_result);
                assert(b_result);

                pby_string += pt_rep->_t_elemsize;
            }
        } else {
            for (i = 0; i < pt_rep->_t_length; ++i) {
                if (memcmp(pby_string, pby_terminator, pt_rep->_t_elemsize) != 0) {
                    b_result = pt_rep->_t_elemsize;
                    ufun_destroy(pby_string, &b_result);
                    assert(b_result);
                }

                pby_string += pt_rep->_t_elemsize;
            }
        }
        free(pt_rep);
        return NULL;
    } else {
        return pt_rep;
    }
}

/**
 * Increase shared.
 */
void _basic_string_rep_increase_shared(_basic_string_rep_t* pt_rep)
{
    assert(pt_rep != NULL);
    pt_rep->_n_refcount += 1;
}

/**
 * Get data pointer from basic_string_rep.
 */
_byte_t* _basic_string_rep_get_data(const _basic_string_rep_t* cpt_rep)
{
    assert(cpt_rep != NULL);
    return (_byte_t*)(cpt_rep + 1);
}

/**
 * Get basic_string_rep_t pointer from data.
 */
_basic_string_rep_t* _basic_string_rep_get_representation(const _byte_t* cpby_data)
{
    assert(cpby_data != NULL);
    return ((_basic_string_rep_t*)cpby_data) - 1;
}

/**
 * Get length
 */
size_t _basic_string_rep_get_length(const _basic_string_rep_t* cpt_rep)
{
    assert(cpt_rep != NULL);
    return cpt_rep->_t_length;
}

/**
 * Set length
 */
void _basic_string_rep_set_length(_basic_string_rep_t* pt_rep, size_t t_len)
{
    _byte_t* pby_terminator = NULL;

    assert(pt_rep != NULL);
    assert(t_len <= pt_rep->_t_capacity);

    pt_rep->_t_length = t_len;
    /* For all types use 0x00 as terminator */
    pby_terminator = _basic_string_rep_get_data(pt_rep) + pt_rep->_t_length * pt_rep->_t_elemsize;
    memset(pby_terminator, 0x00, pt_rep->_t_elemsize);
}

/**
 * Check whether the rep is shared.
 */
bool_t _basic_string_rep_is_shared(const _basic_string_rep_t* cpt_rep)
{
    assert(cpt_rep != NULL);
    return cpt_rep->_n_refcount > 0 ? true : false;
}

/**
 * Set rep as sharable
 */
void _basic_string_rep_set_sharable(_basic_string_rep_t* pt_rep)
{
    assert(pt_rep != NULL);
    pt_rep->_n_refcount = 0;
}

/**
 * Check whether the rep is leaked.
 */
bool_t _basic_string_rep_is_leaked(const _basic_string_rep_t* cpt_rep)
{
    assert(cpt_rep != NULL);
    return cpt_rep->_n_refcount < 0 ? true : false;
}

/**
 * Set rep as leaked
 */
void _basic_string_rep_set_leaked(_basic_string_rep_t* pt_rep)
{
    assert(pt_rep != NULL);
    pt_rep->_n_refcount = -1;
}

/**
 * Create basic_string container.
 */
basic_string_t* _create_basic_string(const char* s_typename)
{
    basic_string_t* pt_basic_string = NULL;

    assert(s_typename != NULL);

    if ((pt_basic_string = (basic_string_t*)malloc(sizeof(basic_string_t))) == NULL) {
        return NULL;
    }

    if (!_create_basic_string_auxiliary(pt_basic_string, s_typename)) {
        free(pt_basic_string);
        return NULL;
    }

    return pt_basic_string;
}

/**
 * Create basic_string container auxiliary function.
 */
bool_t _create_basic_string_auxiliary(basic_string_t* pt_basic_string, const char* s_typename)
{
    assert(pt_basic_string != NULL);
    assert(s_typename != NULL);

    _type_get_type(&pt_basic_string->_t_typeinfo, s_typename); 
    if (pt_basic_string->_t_typeinfo._t_style == _TYPE_INVALID) {
        return false;
    }

    pt_basic_string->_pby_string = NULL;
    return true;
}

/**
 * Destroy basic_string container auxiliary function.
 */
void _basic_string_destroy_auxiliary(basic_string_t* pt_basic_string)
{
    assert(pt_basic_string != NULL);
    assert(_basic_string_is_inited(pt_basic_string) || _basic_string_is_created(pt_basic_string));

    if (pt_basic_string->_pby_string != NULL) {
        _basic_string_rep_reduce_shared(
            _basic_string_rep_get_representation(pt_basic_string->_pby_string),
            _GET_BASIC_STRING_TYPE_DESTROY_FUNCTION(pt_basic_string), &pt_basic_string->_t_typeinfo);
        pt_basic_string->_pby_string = NULL;
    }
}

/**
 * Initialize basic_string with specified element.
 */
void _basic_string_init_elem(basic_string_t* pt_basic_string, size_t t_count, ...)
{
    va_list val_elemlist;

    assert(pt_basic_string != NULL);
    assert(_basic_string_is_created(pt_basic_string));

    va_start(val_elemlist, t_count);
    _basic_string_init_elem_varg(pt_basic_string, t_count, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Initialize basic_string with variable argument list of specified element.
 */
void _basic_string_init_elem_varg(basic_string_t* pt_basic_string, size_t t_count, va_list val_elemlist)
{
    _basic_string_rep_t* prep = NULL;

    assert(pt_basic_string != NULL);
    assert(_basic_string_is_created(pt_basic_string));
    assert(t_count <= basic_string_max_size(pt_basic_string));

    prep = _basic_string_rep_construct(pt_basic_string, t_count, t_count, 0);
    pt_basic_string->_pby_string = _basic_string_rep_get_data(prep);
    _basic_string_copy_elem_auxiliary(pt_basic_string, pt_basic_string->_pby_string, t_count, val_elemlist);
}

/**
 * Appends specificed element to basic string.
 */
void _basic_string_connect_elem(basic_string_t* pt_basic_string, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, pt_basic_string);
    _basic_string_connect_elem_varg(pt_basic_string, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Appends specificed element to basic string.
 */
void _basic_string_connect_elem_varg(basic_string_t* pt_basic_string, va_list val_elemlist)
{
    _basic_string_push_back_varg(pt_basic_string, val_elemlist);
}

/**
 * Find a first occurrence of a substring
 */
size_t _basic_string_find_elem(const basic_string_t* cpt_basic_string, size_t t_pos, ...)
{
    va_list val_elemlist;

    assert(cpt_basic_string != NULL);

    va_start(val_elemlist, t_pos);
    t_pos = _basic_string_find_elem_varg(cpt_basic_string, t_pos, val_elemlist);
    va_end(val_elemlist);

    return t_pos;
}

/**
 * Find a first occurrence of a substring
 */
size_t _basic_string_find_elem_varg(const basic_string_t* cpt_basic_string, size_t t_pos, va_list val_elemlist)
{
    size_t   t_typesize = 0;
    size_t   t_findpos = 0;
    size_t   t_len = 0;
    void*    pv_varg = NULL;
    _byte_t* pby_string = NULL;
    _byte_t* pby_terminator = NULL;
    bool_t   b_less = false;
    bool_t   b_greater = false;

    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));

    if (t_pos >= basic_string_size(cpt_basic_string)) {
        return NPOS;
    }

    /* get element */
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    pv_varg = malloc(t_typesize);
    assert(pv_varg != NULL);
    _basic_string_get_varg_value_auxiliary((basic_string_t*)cpt_basic_string, val_elemlist, pv_varg);

    /* find elemen */
    t_len = basic_string_length(cpt_basic_string);
    pby_string = cpt_basic_string->_pby_string;
    pby_terminator = pby_string + t_len * t_typesize;
    t_findpos = t_pos;

    if (_GET_BASIC_STRING_TYPE_STYLE(cpt_basic_string) == _TYPE_C_BUILTIN &&
        strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) != 0) {
        while (t_findpos != t_len) {
            b_less = b_greater = t_typesize;
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pby_string + t_findpos * t_typesize, pv_varg, &b_less);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pv_varg, pby_string + t_findpos * t_typesize, &b_greater);
            if (!b_less && !b_greater) {
                break;
            } else {
                t_findpos++;
            }
        }
    } else {
        while (t_findpos != t_len) {
            int n_string_terminator = memcmp(pby_terminator, pby_string + t_findpos * t_typesize, t_typesize);
            int n_varg_terminator = memcmp(pby_terminator, pv_varg, t_typesize);

            if (n_string_terminator != n_varg_terminator) {
                t_findpos++;
            } else if (n_string_terminator == 0) {
                break;
            } else {
                b_less = b_greater = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pby_string + t_findpos * t_typesize, pv_varg, &b_less);
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pv_varg, pby_string + t_findpos * t_typesize, &b_greater);
                if (!b_less && !b_greater) {
                    break;
                } else {
                    t_findpos++;
                }
            }
        }
    }
    if (t_findpos == t_len) {
        t_findpos = NPOS;
    }

    _basic_string_destroy_varg_value_auxiliary((basic_string_t*)cpt_basic_string, pv_varg);
    free(pv_varg);

    return t_findpos;
}

/**
 * Find a last occurrence of a substring
 */
size_t _basic_string_rfind_elem(const basic_string_t* cpt_basic_string, size_t t_pos, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_pos);
    t_pos = _basic_string_rfind_elem_varg(cpt_basic_string, t_pos, val_elemlist);
    va_end(val_elemlist);

    return t_pos;
}

/**
 * Find a last occurrence of a substring
 */
size_t _basic_string_rfind_elem_varg(const basic_string_t* cpt_basic_string, size_t t_pos, va_list val_elemlist)
{
    size_t   t_typesize = 0;
    void*    pv_varg = NULL;
    _byte_t* pby_string = NULL;
    _byte_t* pby_terminator = NULL;
    size_t   t_findpos = 0;
    bool_t   b_less = false;
    bool_t   b_greater = false;

    assert(cpt_basic_string != NULL);

    if (basic_string_empty(cpt_basic_string)) {
        return NPOS;
    }

    /* get element */
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    pv_varg = malloc(t_typesize);
    assert(pv_varg != NULL);
    _basic_string_get_varg_value_auxiliary((basic_string_t*)cpt_basic_string, val_elemlist, pv_varg);

    /* find elemen */
    pby_string = cpt_basic_string->_pby_string;
    pby_terminator = pby_string + basic_string_size(cpt_basic_string) * t_typesize;
    t_findpos = t_pos < basic_string_size(cpt_basic_string) ? t_pos + 1 : basic_string_size(cpt_basic_string);

    if (_GET_BASIC_STRING_TYPE_STYLE(cpt_basic_string) == _TYPE_C_BUILTIN &&
        strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) != 0) {
        while (t_findpos-- > 0) {
            /* The t_findpos is NPOS when underflow. */
            b_less = b_greater = t_typesize;
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pby_string + t_findpos * t_typesize, pv_varg, &b_less);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pv_varg, pby_string + t_findpos * t_typesize, &b_greater);
            if (!b_less && !b_greater) {
                break;
            }
        }
    } else {
        while (t_findpos-- > 0) {
            /* The t_findpos is NPOS when underflow. */
            int n_string_terminator = memcmp(pby_terminator, pby_string + t_findpos * t_typesize, t_typesize);
            int n_varg_terminator = memcmp(pby_terminator, pv_varg, t_typesize);

            if (n_string_terminator == 0 && n_varg_terminator == 0) {
                break;
            } else if (n_string_terminator != 0 && n_varg_terminator != 0) {
                b_less = b_greater = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pby_string + t_findpos * t_typesize, pv_varg, &b_less);
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pv_varg, pby_string + t_findpos * t_typesize, &b_greater);
                if (!b_less && !b_greater) {
                    break;
                }
            }
        }
    }

    _basic_string_destroy_varg_value_auxiliary((basic_string_t*)cpt_basic_string, pv_varg);
    free(pv_varg);

    return t_findpos;
}

/**
 * Find a first occurrence of a character that is not equal to specificed element.
 */
size_t _basic_string_find_first_not_of_elem(const basic_string_t* cpt_basic_string, size_t t_pos, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_pos);
    t_pos = _basic_string_find_first_not_of_elem_varg(cpt_basic_string, t_pos, val_elemlist);
    va_end(val_elemlist);

    return t_pos;
}

/**
 * Find a first occurrence of a character that is not equal to specificed element.
 */
size_t _basic_string_find_first_not_of_elem_varg(const basic_string_t* cpt_basic_string, size_t t_pos, va_list val_elemlist)
{
    size_t   t_typesize = 0;
    size_t   t_findpos = NPOS;
    size_t   t_len = 0;
    void*    pv_varg = NULL;
    _byte_t* pby_string = NULL;
    _byte_t* pby_terminator = NULL;
    bool_t   b_less = false;
    bool_t   b_greater = false;

    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));

    /* get element */
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    pv_varg = malloc(t_typesize);
    assert(pv_varg != NULL);
    _basic_string_get_varg_value_auxiliary((basic_string_t*)cpt_basic_string, val_elemlist, pv_varg);

    /* find elemen */
    t_len = basic_string_length(cpt_basic_string);
    pby_terminator = cpt_basic_string->_pby_string + t_len * t_typesize;

    if (_GET_BASIC_STRING_TYPE_STYLE(cpt_basic_string) == _TYPE_C_BUILTIN &&
        strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) != 0) {
        for (; t_pos < t_len; ++t_pos) {
            pby_string = cpt_basic_string->_pby_string + t_pos * t_typesize;
            b_less = b_greater = t_typesize;
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pby_string, pv_varg, &b_less);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pv_varg, pby_string, &b_greater);
            if (b_less || b_greater) {
                t_findpos = t_pos;
                break;
            }
        }
    } else {
        for (; t_pos < t_len; ++t_pos) {
            int n_string_terminator = 0;
            int n_varg_terminator = 0;

            pby_string = cpt_basic_string->_pby_string + t_pos * t_typesize;
            n_string_terminator = memcmp(pby_terminator, pby_string, t_typesize);
            n_varg_terminator = memcmp(pby_terminator, pv_varg, t_typesize);

            if (n_string_terminator != n_varg_terminator) {
                t_findpos = t_pos;
                break;
            } else if (n_string_terminator != 0) {
                b_less = b_greater = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pby_string, pv_varg, &b_less);
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pv_varg, pby_string, &b_greater);
                if (b_less || b_greater) {
                    t_findpos = t_pos;
                    break;
                }
            }
        }
    }

    _basic_string_destroy_varg_value_auxiliary((basic_string_t*)cpt_basic_string, pv_varg);
    free(pv_varg);

    return t_findpos;
}

/**
 * Find a last occurrence of a character that is not equal to specificed element.
 */
size_t _basic_string_find_last_not_of_elem(const basic_string_t* cpt_basic_string, size_t t_pos, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_pos);
    t_pos = _basic_string_find_last_not_of_elem_varg(cpt_basic_string, t_pos, val_elemlist);
    va_end(val_elemlist);

    return t_pos;
}

/**
 * Find a last occurrence of a character that is not equal to specificed element.
 */
size_t _basic_string_find_last_not_of_elem_varg(const basic_string_t* cpt_basic_string, size_t t_pos, va_list val_elemlist)
{
    size_t   t_typesize = 0;
    size_t   t_len = 0;
    void*    pv_varg = NULL;
    _byte_t* pby_string = NULL;
    _byte_t* pby_terminator = NULL;
    size_t   t_findpos = NPOS;
    bool_t   b_less = false;
    bool_t   b_greater = false;

    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));

    t_len = basic_string_size(cpt_basic_string);
    if (t_len > 0) {
        /* get element */
        t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
        pv_varg = malloc(t_typesize);
        assert(pv_varg != NULL);
        _basic_string_get_varg_value_auxiliary((basic_string_t*)cpt_basic_string, val_elemlist, pv_varg);

        if (t_pos >= t_len) {
            t_pos = t_len - 1;
        }

        /* find elemen */
        pby_terminator = cpt_basic_string->_pby_string + t_len * t_typesize;

        if (_GET_BASIC_STRING_TYPE_STYLE(cpt_basic_string) == _TYPE_C_BUILTIN &&
            strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) != 0) {
            do {
                b_less = b_greater = t_typesize;
                pby_string = cpt_basic_string->_pby_string + t_pos * t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pby_string, pv_varg, &b_less);
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pv_varg, pby_string, &b_greater);
                if (b_less || b_greater) {
                    t_findpos = t_pos;
                    break;
                }
            } while (t_pos-- > 0);
        } else {
            do {
                int n_string_terminator = 0;
                int n_varg_terminator = 0;

                pby_string = cpt_basic_string->_pby_string + t_pos * t_typesize;
                n_string_terminator = memcmp(pby_terminator, pby_string, t_typesize);
                n_varg_terminator = memcmp(pby_terminator, pv_varg, t_typesize);

                if (n_string_terminator != n_varg_terminator) {
                    t_findpos = t_pos;
                    break;
                } else if (n_string_terminator != 0) {
                    b_less = b_greater = t_typesize;
                    _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pby_string, pv_varg, &b_less);
                    _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(pv_varg, pby_string, &b_greater);
                    if (b_less || b_greater) {
                        t_findpos = t_pos;
                        break;
                    }
                }
            } while (t_pos-- > 0);
        }

        _basic_string_destroy_varg_value_auxiliary((basic_string_t*)cpt_basic_string, pv_varg);
        free(pv_varg);
    }

    return t_findpos;
}

/**
 * Reset the size of basic_string elements.
 */
void _basic_string_resize_elem(basic_string_t* pt_basic_string, size_t t_resize, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_resize);
    _basic_string_resize_elem_varg(pt_basic_string, t_resize, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Reset the size of basic_string elements, and filled element is from variable argument list.
 */
void _basic_string_resize_elem_varg(basic_string_t* pt_basic_string, size_t t_resize, va_list val_elemlist)
{
    assert(pt_basic_string != NULL);
    assert(_basic_string_is_inited(pt_basic_string));
    assert(t_resize <= basic_string_max_size(pt_basic_string));

    if (t_resize > basic_string_size(pt_basic_string)) {
        _basic_string_append_elem_varg(pt_basic_string, t_resize - basic_string_size(pt_basic_string), val_elemlist);
    } else if (t_resize < basic_string_size(pt_basic_string)) {
        basic_string_erase_substring(pt_basic_string, t_resize, NPOS);
    }
}

/**
 * Adds an element to basic string.
 */
void _basic_string_push_back(basic_string_t* pt_basic_string, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, pt_basic_string);
    _basic_string_push_back_varg(pt_basic_string, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Adds an element to basic string.
 */
void _basic_string_push_back_varg(basic_string_t* pt_basic_string, va_list val_elemlist)
{
    _basic_string_replace_elem_varg(pt_basic_string, basic_string_size(pt_basic_string), 0, 1, val_elemlist);
}

/**
 * Assign new element to basic_string.
 */
void _basic_string_assign_elem(basic_string_t* pt_basic_string, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _basic_string_assign_elem_varg(pt_basic_string, t_count, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Assign new element to basic_string.
 */
void _basic_string_assign_elem_varg(basic_string_t* pt_basic_string, size_t t_count, va_list val_elemlist)
{
    _basic_string_replace_elem_varg(pt_basic_string, 0, NPOS, t_count, val_elemlist);
}

/**
 * Appends characters to the end of basic string.
 */
void _basic_string_append_elem(basic_string_t* pt_basic_string, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _basic_string_append_elem_varg(pt_basic_string, t_count, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Appends characters to the end of basic string.
 */
void _basic_string_append_elem_varg(basic_string_t* pt_basic_string, size_t t_count, va_list val_elemlist)
{
    assert(t_count + basic_string_size(pt_basic_string) <= basic_string_max_size(pt_basic_string));
    _basic_string_replace_elem_varg(pt_basic_string, basic_string_size(pt_basic_string), 0, t_count, val_elemlist);
}

/**
 * Insert one copy of element befor specificed position.
 */
basic_string_iterator_t _basic_string_insert(basic_string_t* pt_basic_string, basic_string_iterator_t it_pos, ...)
{
    basic_string_iterator_t it_iter;
    va_list val_elemlist;

    va_start(val_elemlist, it_pos);
    it_iter = _basic_string_insert_n_varg(pt_basic_string, it_pos, 1, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Insert multiple copys of element befor specificed position.
 */
basic_string_iterator_t _basic_string_insert_n(
    basic_string_t* pt_basic_string, basic_string_iterator_t it_pos, size_t t_count, ...)
{
    basic_string_iterator_t it_iter;
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    it_iter = _basic_string_insert_n_varg(pt_basic_string, it_pos, t_count, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Insert multiple copys of element befor specificed position, the element is from variable argument list.
 */
basic_string_iterator_t _basic_string_insert_n_varg(
    basic_string_t* pt_basic_string, basic_string_iterator_t it_pos, size_t t_count, va_list val_elemlist)
{
    int n_len = iterator_distance(basic_string_begin(pt_basic_string), it_pos);
    _basic_string_range_replace_elem_varg(pt_basic_string, it_pos, it_pos, t_count, val_elemlist);
    return iterator_next_n(basic_string_begin(pt_basic_string), n_len);
}

/**
 * Insert multiple copys of element befor specificed position.
 */
void _basic_string_insert_elem(basic_string_t* pt_basic_string, size_t t_pos, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _basic_string_insert_elem_varg(pt_basic_string, t_pos, t_count, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Insert multiple copys of element befor specificed position, the element is from variable argument list.
 */
void _basic_string_insert_elem_varg(basic_string_t* pt_basic_string, size_t t_pos, size_t t_count, va_list val_elemlist)
{
    _basic_string_replace_elem_varg(pt_basic_string, t_pos, 0, t_count, val_elemlist);
}

/**
 * Replace elements at specificed posititon.
 */
void _basic_string_replace_elem(basic_string_t* pt_basic_string, size_t t_pos, size_t t_len, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _basic_string_replace_elem_varg(pt_basic_string, t_pos, t_len, t_count, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Replace elements at specificed posititon.
 */
void _basic_string_replace_elem_varg(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_len, size_t t_count, va_list val_elemlist)
{
    size_t   t_size = 0;
    size_t   t_newsize = 0;
    size_t   t_typesize = 0;
    _byte_t* pby_dest = NULL;

    assert(pt_basic_string != NULL);
    assert(_basic_string_is_inited(pt_basic_string));
    assert(t_pos <= basic_string_size(pt_basic_string));
    assert(t_count <= basic_string_max_size(pt_basic_string));

    if (t_len == NPOS || t_len + t_pos >= basic_string_size(pt_basic_string)) {
        t_len = basic_string_size(pt_basic_string) - t_pos;
    }

    _basic_string_replace_preparation(pt_basic_string, t_pos, t_len, t_count);

    /* copy elements in replace range */
    t_size = basic_string_size(pt_basic_string);
    t_newsize = t_size + t_count - t_len;
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
    pby_dest = pt_basic_string->_pby_string + t_pos * t_typesize;
    _basic_string_copy_elem_auxiliary(pt_basic_string, pby_dest, t_count, val_elemlist);
}

/**
 * Replace elements at specificed posititon.
 */
void _basic_string_range_replace_elem(
    basic_string_t* pt_basic_string, basic_string_iterator_t it_begin, basic_string_iterator_t it_end,
    size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _basic_string_range_replace_elem_varg(pt_basic_string, it_begin, it_end, t_count, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Replace elements at specificed posititon.
 */
void _basic_string_range_replace_elem_varg(
    basic_string_t* pt_basic_string, basic_string_iterator_t it_begin, basic_string_iterator_t it_end,
    size_t t_count, va_list val_elemlist)
{
    assert(pt_basic_string != NULL);
    assert(_basic_string_is_inited(pt_basic_string));
    assert(_basic_string_iterator_belong_to_basic_string(pt_basic_string, it_begin));
    assert(_basic_string_iterator_belong_to_basic_string(pt_basic_string, it_end));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    _basic_string_replace_elem_varg(
        pt_basic_string, iterator_distance(basic_string_begin(pt_basic_string), it_begin),
        iterator_distance(it_begin, it_end), t_count, val_elemlist);
}

/**
 * Initialize element with basic_string element type auxiliary function.
 */
void _basic_string_init_elem_auxiliary(basic_string_t* pt_basic_string, void* pv_elem)
{
    assert(pt_basic_string != NULL);
    assert(pv_elem != NULL);
    assert(_basic_string_is_inited(pt_basic_string) || _basic_string_is_created(pt_basic_string));

    /* initialize new elements */
    if (_GET_BASIC_STRING_TYPE_STYLE(pt_basic_string) == _TYPE_CSTL_BUILTIN) {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_BASIC_STRING_TYPE_NAME(pt_basic_string), s_elemtypename);

        _GET_BASIC_STRING_TYPE_INIT_FUNCTION(pt_basic_string)(pv_elem, s_elemtypename);
    } else {
        bool_t b_result = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
        _GET_BASIC_STRING_TYPE_INIT_FUNCTION(pt_basic_string)(pv_elem, &b_result);
        assert(b_result);
    }
}

/** local function implementation section **/

/** eof **/

