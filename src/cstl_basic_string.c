/*
 *  The implementation of basic_string
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
/**
 * Initialize empty basic_string container.
 */
void basic_string_init(basic_string_t* pt_basic_string)
{
    _basic_string_rep_t* prep = NULL;

    assert(_basic_string_is_created(pt_basic_string));

    prep = _basic_string_rep_construct(pt_basic_string, 0, 0, 0);
    pt_basic_string->_pby_string = _basic_string_rep_get_data(prep);
}

/**
 * Initialize basic_string container with an exist basic_string container.
 */
void basic_string_init_copy(basic_string_t* pt_dest, const basic_string_t* cpt_src)
{
    assert(pt_dest != NULL);
    assert(cpt_src != NULL);
    assert(_basic_string_is_created(pt_dest));
    assert(_basic_string_is_inited(cpt_src));
    assert(_basic_string_same_type(pt_dest, cpt_src));

    pt_dest->_pby_string = cpt_src->_pby_string;
    _basic_string_rep_increase_shared(_basic_string_rep_get_representation(pt_dest->_pby_string));
}

/**
 * Initialize basic_string container with an exist basic_string range.
 */
void basic_string_init_copy_range(
    basic_string_t* pt_basic_string, basic_string_iterator_t it_begin, basic_string_iterator_t it_end)
{
    size_t               t_len = 0;
    _basic_string_rep_t* prep = NULL;

    assert(pt_basic_string != NULL);
    assert(_basic_string_is_created(pt_basic_string));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));
    assert(_basic_string_same_iterator_type(pt_basic_string, it_begin));
    assert(_basic_string_same_iterator_type(pt_basic_string, it_end));

    /* initialize all elements with default value */
    t_len = iterator_distance(it_begin, it_end);
    prep = _basic_string_rep_construct(pt_basic_string, t_len, t_len, 0);
    pt_basic_string->_pby_string = _basic_string_rep_get_data(prep);

    _basic_string_copy_range_auxiliary(pt_basic_string, pt_basic_string->_pby_string, it_begin, it_end);
}

/**
 * Initialize basic_string container with an exist sub basic_string container.
 */
void basic_string_init_copy_substring(basic_string_t* pt_dest, const basic_string_t* cpt_src, size_t t_pos, size_t t_len)
{
    _basic_string_rep_t* prep = NULL;

    assert(pt_dest != NULL);
    assert(cpt_src != NULL);
    assert(_basic_string_is_created(pt_dest));
    assert(_basic_string_is_inited(cpt_src));
    assert(_basic_string_same_type(pt_dest, cpt_src));
    assert(t_pos <= basic_string_size(cpt_src));

    if (t_len == NPOS || t_len + t_pos >= basic_string_size(cpt_src)) {
        t_len = basic_string_size(cpt_src) - t_pos;
    }

    prep = _basic_string_rep_construct(pt_dest, t_len, t_len, 0);
    pt_dest->_pby_string = _basic_string_rep_get_data(prep);

    _basic_string_copy_substring_auxiliary(
        pt_dest, pt_dest->_pby_string, cpt_src->_pby_string + t_pos * _GET_BASIC_STRING_TYPE_SIZE(pt_dest), t_len);
}

/**
 * Initialize empty basic_string container.
 */
void basic_string_init_cstr(basic_string_t* pt_basic_string, const void* cpv_value_string)
{
    basic_string_init_subcstr(pt_basic_string, cpv_value_string,
        _basic_string_get_value_string_length(pt_basic_string, cpv_value_string));
}

/**
 * Initialize basic_string container specific sub value string.
 */
void basic_string_init_subcstr(basic_string_t* pt_basic_string, const void* cpv_value_string, size_t t_len)
{
    _basic_string_rep_t* prep = NULL;

    assert(pt_basic_string != NULL);
    assert(cpv_value_string != NULL);
    assert(_basic_string_is_created(pt_basic_string));
    assert(t_len <= basic_string_max_size(pt_basic_string));

    prep = _basic_string_rep_construct(pt_basic_string, t_len, t_len, 0);
    pt_basic_string->_pby_string = _basic_string_rep_get_data(prep);

    _basic_string_copy_subcstr_auxiliary(pt_basic_string, pt_basic_string->_pby_string, cpv_value_string, t_len);
}

/**
 * Destroy basic_string container.
 */
void basic_string_destroy(basic_string_t* pt_basic_string)
{
    assert(pt_basic_string != NULL);
    assert(_basic_string_is_inited(pt_basic_string) || _basic_string_is_created(pt_basic_string));

    _basic_string_destroy_auxiliary(pt_basic_string);
    free(pt_basic_string);
}

/**
 * Get data string.
 */
const void* basic_string_c_str(const basic_string_t* cpt_basic_string)
{
    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));

    return cpt_basic_string->_pby_string;
}

/**
 * Get data string.
 */
const void* basic_string_data(const basic_string_t* cpt_basic_string)
{
    return basic_string_c_str(cpt_basic_string);
}

/**
 * Copy spceificed sub basic_string to buffer.
 */
size_t basic_string_copy(const basic_string_t* cpt_basic_string, void* pv_buffer, size_t t_len, size_t t_pos)
{
    size_t   t_size = 0;
    size_t   t_typesize = 0;
    size_t   i = 0;
    bool_t   b_result = false;
    _byte_t* pby_pos = NULL;
    _byte_t* pby_terminator = NULL;

    assert(pv_buffer != NULL);
    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));

    t_size = basic_string_size(cpt_basic_string);
    assert(t_size >= t_pos);
    t_size = (t_size - t_pos) < t_len ? (t_size - t_pos) : t_len;

    /* the elements in buffer must be initialized */
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    pby_pos = cpt_basic_string->_pby_string + t_pos * t_typesize;
    pby_terminator = cpt_basic_string->_pby_string + basic_string_size(cpt_basic_string) * t_typesize;

    if (strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        for (i = 0; i < t_size; ++i) {
            if (memcmp(pby_terminator, pby_pos + i * t_typesize, t_typesize) != 0) {
                *((const char**)pv_buffer + i) = string_c_str((string_t*)(pby_pos + i * t_typesize));
            } else {
                *((const char**)pv_buffer + i) = NULL;
            }
        }
    } else if (_GET_BASIC_STRING_TYPE_STYLE(cpt_basic_string) == _TYPE_C_BUILTIN) {
        for (i = 0; i < t_size; ++i) {
            b_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
            _GET_BASIC_STRING_TYPE_COPY_FUNCTION(cpt_basic_string)(
                (_byte_t*)pv_buffer + i * t_typesize, pby_pos + i * t_typesize, &b_result);
            assert(b_result);
        }
    } else {
        for (i = 0; i < t_size; ++i) {
            if (memcmp(pby_terminator, pby_pos + i * t_typesize, t_typesize) != 0) {
                *((const _byte_t**)pv_buffer + i) = pby_pos + i * t_typesize;
            } else {
                *((const _byte_t**)pv_buffer + i) = NULL;
            }
        }
    }

    return t_size;
}

/**
 * Get basic_string element size.
 */
size_t basic_string_size(const basic_string_t* cpt_basic_string)
{
    assert(_basic_string_is_inited(cpt_basic_string));
    return _basic_string_rep_get_representation(cpt_basic_string->_pby_string)->_t_length;
}

/**
 * Get data string length.
 */
size_t basic_string_length(const basic_string_t* cpt_basic_string)
{
    return basic_string_size(cpt_basic_string);
}

/**
 * Test basic_string is empty.
 */
bool_t basic_string_empty(const basic_string_t* cpt_basic_string)
{
    return basic_string_size(cpt_basic_string) == 0 ? true : false;
}

/**
 * Return maximum element number.
 */
size_t basic_string_max_size(const basic_string_t* cpt_basic_string)
{
    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string) || _basic_string_is_created(cpt_basic_string));

    return ((NPOS - sizeof(_basic_string_rep_t)) / _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string)) - 1;
}

/**
 * Get basic_string capacity.
 */
size_t basic_string_capacity(const basic_string_t* cpt_basic_string)
{
    assert(_basic_string_is_inited(cpt_basic_string));
    return _basic_string_rep_get_representation(cpt_basic_string->_pby_string)->_t_capacity;
}

/**
 * Access basic_string data using subscript.
 */
void* basic_string_at(const basic_string_t* cpt_basic_string, size_t t_pos)
{
    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));
    assert(t_pos < basic_string_size(cpt_basic_string));

    return (void*)iterator_get_pointer(iterator_next_n(basic_string_begin(cpt_basic_string), t_pos));
}

/**
 * Test the two basic_strings are equal.
 */
bool_t basic_string_equal(const basic_string_t* cpt_first, const basic_string_t* cpt_second)
{
    return basic_string_compare(cpt_first, cpt_second) == 0 ? true : false;
}

/**
 * Test the two basic_strings are unequal.
 */
bool_t basic_string_not_equal(const basic_string_t* cpt_first, const basic_string_t* cpt_second)
{
    return basic_string_compare(cpt_first, cpt_second) != 0 ? true : false;
}

/**
 * Test the first basic_string is less than the second basic_string.
 */
bool_t basic_string_less(const basic_string_t* cpt_first, const basic_string_t* cpt_second)
{
    return basic_string_compare(cpt_first, cpt_second) < 0 ? true : false;
}

/**
 * Test the first basic_string is less than or equal to the second basic_string.
 */
bool_t basic_string_less_equal(const basic_string_t* cpt_first, const basic_string_t* cpt_second)
{
    return basic_string_compare(cpt_first, cpt_second) <= 0 ? true : false;
}

/**
 * Test the first basic_string is greater than the second basic_string.
 */
bool_t basic_string_greater(const basic_string_t* cpt_first, const basic_string_t* cpt_second)
{
    return basic_string_compare(cpt_first, cpt_second) > 0 ? true : false;
}

/**
 * Test the first basic_string is greater than or equal to the second basic_string.
 */
bool_t basic_string_greater_equal(const basic_string_t* cpt_first, const basic_string_t* cpt_second)
{
    return basic_string_compare(cpt_first, cpt_second) >= 0 ? true : false;
}

/**
 * Test the basic_string is equal to the value string.
 */
bool_t basic_string_equal_cstr(const basic_string_t* cpt_basic_string, const void* cpv_value_string)
{
    return basic_string_compare_cstr(cpt_basic_string, cpv_value_string) == 0 ? true : false;
}

/**
 * Test the basic_string is not equal to the value string.
 */
bool_t basic_string_not_equal_cstr(const basic_string_t* cpt_basic_string, const void* cpv_value_string)
{
    return basic_string_compare_cstr(cpt_basic_string, cpv_value_string) != 0 ? true : false;
}

/**
 * Test the basic_string is less than the value string.
 */
bool_t basic_string_less_cstr(const basic_string_t* cpt_basic_string, const void* cpv_value_string)
{
    return basic_string_compare_cstr(cpt_basic_string, cpv_value_string) < 0 ? true : false;
}

/**
 * Test the basic_string is less than or equal to the value string.
 */
bool_t basic_string_less_equal_cstr(const basic_string_t* cpt_basic_string, const void* cpv_value_string)
{
    return basic_string_compare_cstr(cpt_basic_string, cpv_value_string) <= 0 ? true : false;
}

/**
 * Test the basic_string is greater than the value string.
 */
bool_t basic_string_greater_cstr(const basic_string_t* cpt_basic_string, const void* cpv_value_string)
{
    return basic_string_compare_cstr(cpt_basic_string, cpv_value_string) > 0 ? true : false;
}

/**
 * Test the basic_string is greater than or equal to the value string.
 */
bool_t basic_string_greater_equal_cstr(const basic_string_t* cpt_basic_string, const void* cpv_value_string)
{
    return basic_string_compare_cstr(cpt_basic_string, cpv_value_string) >= 0 ? true : false;
}

/**
 * Compare two basic_string.
 */
int basic_string_compare(const basic_string_t* cpt_first, const basic_string_t* cpt_second)
{
    assert(cpt_first != NULL);
    assert(cpt_second != NULL);

    if (cpt_first == cpt_second || cpt_first->_pby_string == cpt_second->_pby_string) {
        return 0;
    }

    return basic_string_compare_substring_substring(cpt_first, 0, NPOS, cpt_second, 0, NPOS);
}

/**
 * Compare the first sub basic_string and the second basic_string.
 */
int basic_string_compare_substring_string(
    const basic_string_t* cpt_first, size_t t_pos, size_t t_len, const basic_string_t* cpt_second)
{
    return basic_string_compare_substring_substring(cpt_first, t_pos, t_len, cpt_second, 0, NPOS);
}

/**
 * Compare two sub basic_strings.
 */
int basic_string_compare_substring_substring(
    const basic_string_t* cpt_first, size_t t_firstpos, size_t t_firstlen,
    const basic_string_t* cpt_second, size_t t_secondpos, size_t t_secondlen)
{
    size_t   t_cmplen = 0;
    size_t   t_firstlentmp = 0;
    size_t   t_secondlentmp = 0;
    size_t   i = 0;
    size_t   t_typesize = 0;
    bool_t   b_result;
    _byte_t* pby_first = NULL;
    _byte_t* pby_second = NULL;
    _byte_t* pby_terminator = NULL;

    assert(cpt_first != NULL);
    assert(cpt_second != NULL);
    assert(_basic_string_is_inited(cpt_first));
    assert(_basic_string_is_inited(cpt_second));
    assert(_basic_string_same_type(cpt_first, cpt_second));
    assert(t_firstpos <= basic_string_size(cpt_first));
    assert(t_secondpos <= basic_string_size(cpt_second));

    t_firstlentmp = basic_string_size(cpt_first) - t_firstpos;
    t_secondlentmp = basic_string_size(cpt_second) - t_secondpos;
    t_firstlen = t_firstlen < t_firstlentmp ? t_firstlen : t_firstlentmp;
    t_secondlen = t_secondlen < t_secondlentmp ? t_secondlen : t_secondlentmp;
    t_cmplen = t_firstlen < t_secondlen ? t_firstlen : t_secondlen;

    if (t_firstlen == 0 && t_secondlen > 0) {
        return -1;
    } else if (t_firstlen > 0 && t_secondlen == 0) {
        return 1;
    } else if (t_firstlen == 0 && t_secondlen == 0) {
        return 0;
    }

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_first);
    pby_first = cpt_first->_pby_string + t_firstpos * t_typesize;
    pby_second = cpt_second->_pby_string + t_secondpos * t_typesize;
    pby_terminator = cpt_first->_pby_string + basic_string_size(cpt_first) * t_typesize;
    if (_GET_BASIC_STRING_TYPE_STYLE(cpt_first) == _TYPE_CSTL_BUILTIN ||
        strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        for (i = 0; i < t_cmplen; ++i) {
            int n_first = memcmp(pby_terminator, pby_first, t_typesize);
            int n_second = memcmp(pby_terminator, pby_second, t_typesize);

            if (n_first == 0 && n_second != 0) {
                return -1;
            } else if (n_first != 0 && n_second == 0) {
                return 1;
            } else if (n_first != 0 && n_second != 0) {
                b_result = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_first)(pby_first, pby_second, &b_result);
                if (b_result) {
                    return -1;
                }

                b_result = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_first)(pby_second, pby_first, &b_result);
                if (b_result) {
                    return 1;
                }
            }

            pby_first += t_typesize;
            pby_second += t_typesize;
        }
    } else {
        for (i = 0; i < t_cmplen; ++i) {
            b_result = t_typesize;
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_first)(pby_first, pby_second, &b_result);
            if (b_result) {
                return -1;
            }

            b_result = t_typesize;
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_first)(pby_second, pby_first, &b_result);
            if (b_result) {
                return 1;
            }

            pby_first += t_typesize;
            pby_second += t_typesize;
        }
    }

    return t_firstlen < t_secondlen ? -1 : (t_firstlen > t_secondlen ? 1 : 0);
}

/**
 * Compare the basic_string and the value string.
 */
int basic_string_compare_cstr(const basic_string_t* cpt_basic_string, const void* cpv_value_string)
{
    return basic_string_compare_substring_subcstr(
        cpt_basic_string, 0, NPOS, cpv_value_string,
        _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string));
}

/**
 * Compare the sub basic_string and the value string.
 */
int basic_string_compare_substring_cstr(
    const basic_string_t* cpt_basic_string, size_t t_pos, size_t t_len, const void* cpv_value_string)
{
    return basic_string_compare_substring_subcstr(
        cpt_basic_string, t_pos, t_len, cpv_value_string,
        _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string));
}

/**
 * Compare the sub basic_string and the sub value string.
 */
int basic_string_compare_substring_subcstr(
    const basic_string_t* cpt_basic_string, size_t t_pos, size_t t_len, const void* cpv_value_string, size_t t_valuelen)
{
    size_t   t_lentmp = 0;
    size_t   t_cmplen = 0;
    size_t   t_typesize = 0;
    size_t   i = 0;
    _byte_t* pby_string = NULL;
    _byte_t* pby_terminator = NULL;
    bool_t   b_result = false;

    assert(cpt_basic_string != NULL);
    assert(cpv_value_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));
    assert(t_pos <= basic_string_size(cpt_basic_string));

    /* get actual string length and value string length */
    t_lentmp = basic_string_size(cpt_basic_string) - t_pos;
    t_len = t_len < t_lentmp ? t_len : t_lentmp;
    t_cmplen = t_len < t_valuelen ? t_len : t_valuelen;

    if (t_len == 0 && t_valuelen > 0) {
        return -1;
    } else if (t_len > 0 && t_valuelen == 0) {
        return 1;
    } else if (t_len == 0 && t_valuelen == 0) {
        return 0;
    }

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    pby_terminator = cpt_basic_string->_pby_string + basic_string_size(cpt_basic_string) * t_typesize;
    pby_string = cpt_basic_string->_pby_string + t_pos * t_typesize;
    assert(pby_string != NULL);

    /* char* */
    if (strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        for (i = 0; i < t_cmplen; ++i) {
            int n_result = memcmp(pby_terminator, pby_string + i * t_typesize, t_typesize);

            if (n_result == 0 && *((char**)cpv_value_string + i) != NULL) {
                return -1;
            } else if (n_result != 0 && *((char**)cpv_value_string + i) == NULL) {
                return 1;
            } else if (n_result != 0 && *((char**)cpv_value_string + i) != NULL) {
                int n_cmp_result = string_compare_cstr(
                    (string_t*)(pby_string + i * t_typesize), *((char**)cpv_value_string + i));
                if (n_cmp_result != 0) {
                    return n_cmp_result;
                }
            }
        }
    } else if (_GET_BASIC_STRING_TYPE_STYLE(cpt_basic_string) == _TYPE_C_BUILTIN) {
        for (i = 0; i < t_cmplen; ++i) {
            b_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                pby_string + i * t_typesize, (_byte_t*)cpv_value_string + i * t_typesize, &b_result);
            if (b_result) {
                return -1;
            }
            b_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                (_byte_t*)cpv_value_string + i * t_typesize, pby_string + i * t_typesize, &b_result);
            if (b_result) {
                return 1;
            }
        }
    } else if (_GET_BASIC_STRING_TYPE_STYLE(cpt_basic_string) == _TYPE_CSTL_BUILTIN) {
        for (i = 0; i < t_cmplen; ++i) {
            int n_result = memcmp(pby_terminator, pby_string + i * t_typesize, t_typesize);

            if (n_result == 0 && *((_byte_t**)cpv_value_string + i) != NULL) {
                return -1;
            } else if (n_result != 0 && *((_byte_t**)cpv_value_string + i) == NULL) {
                return 1;
            } else if (n_result != 0 && *((_byte_t**)cpv_value_string + i) != NULL) {
                b_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    pby_string + i * t_typesize, *((_byte_t**)cpv_value_string + i), &b_result);
                if (b_result) {
                    return -1;
                }
                b_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    *((_byte_t**)cpv_value_string + i), pby_string + i * t_typesize, &b_result);
                if (b_result) {
                    return 1;
                }
            }
        }
    } else {
        for (i = 0; i < t_cmplen; ++i) {
            if (*((_byte_t**)cpv_value_string + i) == NULL) {
                return 1;
            } else {
                b_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    pby_string + i * t_typesize, *((_byte_t**)cpv_value_string + i), &b_result);
                if (b_result) {
                    return -1;
                }
                b_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    *((_byte_t**)cpv_value_string + i), pby_string + i * t_typesize, &b_result);
                if (b_result) {
                    return 1;
                }
            }
        }
    }

    return t_len < t_valuelen ? -1 : (t_len > t_valuelen ? 1 : 0);
}

/**
 * Get specific sub string.
 */
basic_string_t* basic_string_substr(const basic_string_t* cpt_basic_string, size_t t_pos, size_t t_len)
{
    basic_string_t*         pt_substr = NULL;

    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));
    assert(t_pos <= basic_string_size(cpt_basic_string));

    pt_substr = _create_basic_string(_GET_BASIC_STRING_TYPE_NAME(cpt_basic_string));
    if (pt_substr != NULL) {
        basic_string_init_copy_substring(pt_substr, cpt_basic_string, t_pos, t_len);
    }

    return pt_substr;
}

/**
 * Connect basic string with other basic string.
 */
void basic_string_connect(basic_string_t* pt_dest, const basic_string_t* cpt_src)
{
    basic_string_append(pt_dest, cpt_src);
}

/**
 * Connect basic string with value string.
 */
void basic_string_connect_cstr(basic_string_t* pt_basic_string, const void* cpv_value_string)
{
    basic_string_append_cstr(pt_basic_string, cpv_value_string);
}

/**
 * Return a iterator to the first element in the basic string container.
 */
basic_string_iterator_t basic_string_begin(const basic_string_t* cpt_basic_string)
{
    basic_string_iterator_t it_begin;

    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));

    _basic_string_detach((basic_string_t*)cpt_basic_string);

    it_begin = _create_basic_string_iterator();
    _ITERATOR_CONTAINER(it_begin) = (basic_string_t*)cpt_basic_string;
    _BASIC_STRING_ITERATOR_COREPOS(it_begin) = cpt_basic_string->_pby_string;

    return it_begin;
}

/**
 * Return a iterator that points just beyond the end of basic_string container.
 */
basic_string_iterator_t basic_string_end(const basic_string_t* cpt_basic_string)
{
    basic_string_iterator_t it_end;
    size_t                  t_elemsize = 0;
    size_t                  t_len = 0;

    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));

    _basic_string_detach((basic_string_t*)cpt_basic_string);

    t_elemsize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    t_len = basic_string_size(cpt_basic_string);
    it_end = _create_basic_string_iterator();
    _ITERATOR_CONTAINER(it_end) = (basic_string_t*)cpt_basic_string;
    _BASIC_STRING_ITERATOR_COREPOS(it_end) = cpt_basic_string->_pby_string + t_elemsize * t_len;

    return it_end;
}

/**** private ****/
basic_string_reverse_iterator_t basic_string_rbegin(const basic_string_t* cpt_basic_string)
{
    return basic_string_end(cpt_basic_string);
}
basic_string_reverse_iterator_t basic_string_rend(const basic_string_t* cpt_basic_string)
{
    return basic_string_begin(cpt_basic_string);
}

/**
 * Find basic_string in basic_string.
 */
size_t basic_string_find(const basic_string_t* cpt_basic_string, const basic_string_t* cpt_find, size_t t_pos)
{
    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));
    assert(cpt_find != NULL);
    assert(_basic_string_is_inited(cpt_find));
    assert(_basic_string_same_type(cpt_basic_string, cpt_find));

    if (basic_string_empty(cpt_find)) {
        return t_pos <= basic_string_size(cpt_basic_string) ? t_pos : NPOS;
    }

    if (basic_string_size(cpt_find) <= basic_string_size(cpt_basic_string)) {
        for (; t_pos <= basic_string_size(cpt_basic_string) - basic_string_size(cpt_find); ++t_pos) {
            if (basic_string_compare_substring_substring(
                    cpt_basic_string, t_pos, basic_string_size(cpt_find),
                    cpt_find, 0, basic_string_size(cpt_find)) == 0) {
                return t_pos;
            }
        }
    }

    return NPOS;
}

/**
 * Find value string in basic_string.
 */
size_t basic_string_find_cstr(const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos)
{
    return basic_string_find_subcstr(
        cpt_basic_string, cpv_value_string, t_pos, _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string));
}

/**
 * Find sub value string in basic_string.
 */
size_t basic_string_find_subcstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos, size_t t_len)
{
    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));
    assert(cpv_value_string != NULL);

    if (t_len == 0) {
        return t_pos <= basic_string_size(cpt_basic_string) ? t_pos : NPOS;
    }

    if (t_len <= basic_string_size(cpt_basic_string)) {
        for (; t_pos <= basic_string_size(cpt_basic_string) - t_len; ++t_pos) {
            if (basic_string_compare_substring_subcstr(cpt_basic_string, t_pos, t_len, cpv_value_string, t_len) == 0) {
                return t_pos;
            }
        }
    }

    return NPOS;
}

/**
 * Find basic_string in basic_string in a backward direction.
 */
size_t basic_string_rfind(const basic_string_t* cpt_basic_string, const basic_string_t* cpt_find, size_t t_pos)
{
    size_t t_len = 0;

    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));
    assert(cpt_find != NULL);
    assert(_basic_string_is_inited(cpt_find));
    assert(_basic_string_same_type(cpt_basic_string, cpt_find));

    t_len = basic_string_size(cpt_find);
    if (t_len <= basic_string_size(cpt_basic_string)) {
        t_pos = t_pos < basic_string_size(cpt_basic_string) - t_len ?
                t_pos : basic_string_size(cpt_basic_string) - t_len;

        do {
            if (basic_string_compare_substring_substring(cpt_basic_string, t_pos, t_len, cpt_find, 0, t_len) == 0) {
                return t_pos;
            }
        } while (t_pos-- > 0);
    }

    return NPOS;
}

/**
 * Find value string in basic_string in a backward direction.
 */
size_t basic_string_rfind_cstr(const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos)
{
    return basic_string_rfind_subcstr(
        cpt_basic_string, cpv_value_string, t_pos,
        _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string));
}

/**
 * Find sub value string in basic_string in a backward direction.
 */
size_t basic_string_rfind_subcstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos, size_t t_len)
{
    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));
    assert(cpv_value_string != NULL);

    if (t_len <= basic_string_size(cpt_basic_string)) {
        t_pos = t_pos < basic_string_size(cpt_basic_string) - t_len ?
                t_pos : basic_string_size(cpt_basic_string) - t_len;

        do {
            if (basic_string_compare_substring_subcstr(cpt_basic_string, t_pos, t_len, cpv_value_string, t_len) == 0) {
                return t_pos;
            }
        } while (t_pos-- > 0);
    }

    return NPOS;
}

/**
 * Find basic_string for first element that matches any element of specific string.
 */
size_t basic_string_find_first_of(
    const basic_string_t* cpt_basic_string, const basic_string_t* cpt_find, size_t t_pos)
{
    size_t t_len = 0;

    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));
    assert(cpt_find != NULL);
    assert(_basic_string_is_inited(cpt_find));
    assert(_basic_string_same_type(cpt_basic_string, cpt_find));

    t_len = basic_string_size(cpt_find);
    for (; t_len > 0 && t_pos < basic_string_size(cpt_basic_string); ++t_pos) {
        if (_basic_string_substring_find(cpt_basic_string, t_pos, cpt_find)) {
            return t_pos;
        }
    }

    return NPOS;
}

/**
 * Find basic_string for first element that matches any element of specific value string.
 */
size_t basic_string_find_first_of_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos)
{
    return basic_string_find_first_of_subcstr(
        cpt_basic_string, cpv_value_string, t_pos,
        _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string));
}

/**
 * Find basic_string for first element that matches any element of specific sub value string.
 */
size_t basic_string_find_first_of_subcstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos, size_t t_len)
{
    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));
    assert(cpv_value_string != NULL);

    for (; t_len > 0 && t_pos < basic_string_size(cpt_basic_string); ++t_pos) {
        if (_basic_string_value_string_find(cpt_basic_string, t_pos, cpv_value_string, t_len)) {
            return t_pos;
        }
    }

    return NPOS;
}

/**
 * Find basic_string for first element that is not matches any element of specific string.
 */
size_t basic_string_find_first_not_of(
    const basic_string_t* cpt_basic_string, const basic_string_t* cpt_find, size_t t_pos)
{
    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));
    assert(cpt_find != NULL);
    assert(_basic_string_is_inited(cpt_find));
    assert(_basic_string_same_type(cpt_basic_string, cpt_find));

    for (; t_pos < basic_string_size(cpt_basic_string); ++t_pos) {
        if (!_basic_string_substring_find(cpt_basic_string, t_pos, cpt_find)) {
            return t_pos;
        }
    }

    return NPOS;
}

/**
 * Find basic_string for first element that is not matches any element of specific value string.
 */
size_t basic_string_find_first_not_of_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos)
{
    return basic_string_find_first_not_of_subcstr(
        cpt_basic_string, cpv_value_string, t_pos,
        _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string)); 
}

/**
 * Find basic_string for first element that is not matches any element of specific sub value string.
 */
size_t basic_string_find_first_not_of_subcstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos, size_t t_len)
{
    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));
    assert(cpv_value_string != NULL);

    for (; t_pos < basic_string_size(cpt_basic_string); ++t_pos) {
        if (!_basic_string_value_string_find(cpt_basic_string, t_pos, cpv_value_string, t_len)) {
            return t_pos;
        }
    }

    return NPOS;
}

/**
 * Find basic_string for last element that matches any element of specific string.
 */
size_t basic_string_find_last_of(
    const basic_string_t* cpt_basic_string, const basic_string_t* cpt_find, size_t t_pos)
{
    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));
    assert(cpt_find != NULL);
    assert(_basic_string_is_inited(cpt_find));
    assert(_basic_string_same_type(cpt_basic_string, cpt_find));

    if (basic_string_size(cpt_basic_string) > 0 && basic_string_size(cpt_find) > 0) {
        if (t_pos >= basic_string_size(cpt_basic_string)) {
            t_pos = basic_string_size(cpt_basic_string) - 1;
        }

        do {
            if (_basic_string_substring_find(cpt_basic_string, t_pos, cpt_find)) {
                return t_pos;
            }
        } while (t_pos-- > 0);
    }

    return NPOS;
}

/**
 * Find basic_string for last element that matches any element of specific value string.
 */
size_t basic_string_find_last_of_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos)
{
    return basic_string_find_last_of_subcstr(
        cpt_basic_string, cpv_value_string, t_pos,
        _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string));
}

/**
 * Find basic_string for last element that matches any element of specific sub value string.
 */
size_t basic_string_find_last_of_subcstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos, size_t t_len)
{
    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));
    assert(cpv_value_string != NULL);

    if (basic_string_size(cpt_basic_string) > 0  && t_len > 0) {
        if (t_pos >= basic_string_size(cpt_basic_string)) {
            t_pos = basic_string_size(cpt_basic_string) - 1;
        }

        do {
            if (_basic_string_value_string_find(cpt_basic_string, t_pos, cpv_value_string, t_len)) {
                return t_pos;
            }
        } while (t_pos-- > 0);
    }

    return NPOS;
}

/**
 * Find basic_string for last element that is not matches any element of specific string.
 */
size_t basic_string_find_last_not_of(
    const basic_string_t* cpt_basic_string, const basic_string_t* cpt_find, size_t t_pos)
{
    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));
    assert(cpt_find != NULL);
    assert(_basic_string_is_inited(cpt_find));
    assert(_basic_string_same_type(cpt_basic_string, cpt_find));

    if (basic_string_size(cpt_basic_string) > 0) {
        if (t_pos >= basic_string_size(cpt_basic_string)) {
            t_pos = basic_string_size(cpt_basic_string) - 1;
        }

        do {
            if (!_basic_string_substring_find(cpt_basic_string, t_pos, cpt_find)) {
                return t_pos;
            }
        } while (t_pos-- > 0);
    }

    return NPOS;
}

/**
 * Find basic_string for last element that is not matches any element of specific value string.
 */
size_t basic_string_find_last_not_of_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos)
{
    return basic_string_find_last_not_of_subcstr(
        cpt_basic_string, cpv_value_string, t_pos,
        _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string));
}

/**
 * Find basic_string for last element that is not matches any element of specific sub value string.
 */
size_t basic_string_find_last_not_of_subcstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos, size_t t_len)
{
    assert(cpt_basic_string != NULL);
    assert(_basic_string_is_inited(cpt_basic_string));
    assert(cpv_value_string != NULL);

    if (basic_string_size(cpt_basic_string) > 0) {
        if (t_pos >= basic_string_size(cpt_basic_string)) {
            t_pos = basic_string_size(cpt_basic_string) - 1;
        }

        do {
            if (!_basic_string_value_string_find(cpt_basic_string, t_pos, cpv_value_string, t_len)) {
                return t_pos;
            }
        } while (t_pos-- > 0);
    }

    return NPOS;
}

/**
 * Erases the elements of basic_string.
 */
void basic_string_clear(basic_string_t* pt_basic_string)
{
    assert(pt_basic_string != NULL);
    assert(_basic_string_is_inited(pt_basic_string));

    if (_basic_string_is_shared(pt_basic_string)) {
        _basic_string_rep_t* prep = _basic_string_rep_construct(pt_basic_string, 0, 0, 0);
        _basic_string_rep_reduce_shared(
            _basic_string_rep_get_representation(pt_basic_string->_pby_string),
            _GET_BASIC_STRING_TYPE_DESTROY_FUNCTION(pt_basic_string), &pt_basic_string->_t_typeinfo);
        pt_basic_string->_pby_string = _basic_string_rep_get_data(prep);
    } else {
        _basic_string_destroy_elem_range_auxiliary(
            pt_basic_string, pt_basic_string->_pby_string, basic_string_size(pt_basic_string));
        _basic_string_rep_set_length(_basic_string_rep_get_representation(pt_basic_string->_pby_string), 0);
    }
}

/**
 * Swap basic_string datas.
 */
void basic_string_swap(basic_string_t* pt_first, basic_string_t* pt_second)
{
    assert(pt_first != NULL);
    assert(pt_second != NULL);
    assert(_basic_string_is_inited(pt_first));
    assert(_basic_string_is_inited(pt_second));
    assert(_basic_string_same_type(pt_first, pt_second));

    if (pt_first != pt_second && pt_first->_pby_string != pt_second->_pby_string) {
        _byte_t* pby_tmp = pt_first->_pby_string;
        pt_first->_pby_string = pt_second->_pby_string;
        pt_second->_pby_string = pby_tmp;
    }
}

/**
 * Set basic_string capacity.
 */
void basic_string_reserve(basic_string_t* pt_basic_string, size_t t_reservesize)
{
    _basic_string_rep_t* prep = NULL;
    bool_t               b_exec = false;

    assert(pt_basic_string != NULL);
    assert(_basic_string_is_inited(pt_basic_string));
    assert(t_reservesize <= basic_string_max_size(pt_basic_string));

    if (_basic_string_is_shared(pt_basic_string)) {
        if (t_reservesize < basic_string_size(pt_basic_string)) {
            t_reservesize = basic_string_size(pt_basic_string);
        }
        b_exec = true;
    } else if (t_reservesize > basic_string_capacity(pt_basic_string)) {
        b_exec = true;
    }

    if (b_exec) {
        prep = _basic_string_clone_representation(pt_basic_string, t_reservesize - basic_string_size(pt_basic_string));
        _basic_string_rep_set_sharable(prep);
        _basic_string_rep_reduce_shared(
            _basic_string_rep_get_representation(pt_basic_string->_pby_string),
            _GET_BASIC_STRING_TYPE_DESTROY_FUNCTION(pt_basic_string), &pt_basic_string->_t_typeinfo);
        pt_basic_string->_pby_string = _basic_string_rep_get_data(prep);
    }
}

/**
 * Assign basic_string element with an exist basic_string container.
 */
void basic_string_assign(basic_string_t* pt_dest, const basic_string_t* cpt_src)
{
    assert(pt_dest != NULL);
    assert(cpt_src != NULL);
    assert(_basic_string_is_inited(pt_dest));
    assert(_basic_string_is_inited(cpt_src));
    assert(_basic_string_same_type(pt_dest, cpt_src));

    if (pt_dest->_pby_string != cpt_src->_pby_string) {
        _basic_string_rep_reduce_shared(
            _basic_string_rep_get_representation(pt_dest->_pby_string),
            _GET_BASIC_STRING_TYPE_DESTROY_FUNCTION(pt_dest), &pt_dest->_t_typeinfo);
        pt_dest->_pby_string = cpt_src->_pby_string;
        _basic_string_rep_increase_shared(_basic_string_rep_get_representation(pt_dest->_pby_string));
    }
}

/**
 * Assign basic_string element with an exist sub basic_string container.
 */
void basic_string_assign_substring(basic_string_t* pt_dest, const basic_string_t* cpt_src, size_t t_pos, size_t t_len)
{
    basic_string_replace_substring(pt_dest, 0, NPOS, cpt_src, t_pos, t_len);
}

/**
 * Assign basic_string element with an exist value string.
 */
void basic_string_assign_cstr(basic_string_t* pt_basic_string, const void* cpv_value_string)
{
    basic_string_assign_subcstr(
        pt_basic_string, cpv_value_string, _basic_string_get_value_string_length(pt_basic_string, cpv_value_string));
}

/**
 * Assign basic_string element with an exist sub value string.
 */
void basic_string_assign_subcstr(basic_string_t* pt_basic_string, const void* cpv_value_string, size_t t_len)
{
    basic_string_replace_subcstr(pt_basic_string, 0, NPOS, cpv_value_string, t_len);
}

/**
 * Assign basic_string element with an exist basic_string container range.
 */
void basic_string_assign_range(
    basic_string_t* pt_basic_string, basic_string_iterator_t it_begin, basic_string_iterator_t it_end)
{
    basic_string_replace_range(
        pt_basic_string, basic_string_begin(pt_basic_string), basic_string_end(pt_basic_string), it_begin, it_end);
}

/**
 * Append specific basic_string to destination basic_string.
 */
void basic_string_append(basic_string_t* pt_dest, const basic_string_t* cpt_src)
{
    basic_string_append_substring(pt_dest, cpt_src, 0, NPOS);
}

/**
 * Append specific sub basic_string to destination basic_string.
 */
void basic_string_append_substring(basic_string_t* pt_dest, const basic_string_t* cpt_src, size_t t_pos, size_t t_len)
{
    basic_string_replace_substring(pt_dest, basic_string_size(pt_dest), 0, cpt_src, t_pos, t_len);
}

/**
 * Append specific value string to destination basic_string.
 */
void basic_string_append_cstr(basic_string_t* pt_basic_string, const void* cpv_value_string)
{
    basic_string_append_subcstr(
        pt_basic_string, cpv_value_string, _basic_string_get_value_string_length(pt_basic_string, cpv_value_string));
}

/**
 * Append specific sub value string to destination basic_string.
 */
void basic_string_append_subcstr(basic_string_t* pt_basic_string, const void* cpv_value_string, size_t t_len)
{
    basic_string_replace_subcstr(pt_basic_string, basic_string_size(pt_basic_string), 0, cpv_value_string, t_len);
}

/**
 * Append specific range to destination basic_string.
 */
void basic_string_append_range(
    basic_string_t* pt_basic_string, basic_string_iterator_t it_begin, basic_string_iterator_t it_end)
{
    basic_string_replace_range(
        pt_basic_string, basic_string_end(pt_basic_string), basic_string_end(pt_basic_string), it_begin, it_end);
}

/**
 * Insert specific basic_string into the destination basic_string at specific position.
 */
void basic_string_insert_string(basic_string_t* pt_basic_string, size_t t_pos, const basic_string_t* cpt_insert)
{
    basic_string_insert_substring(pt_basic_string, t_pos, cpt_insert, 0, NPOS);
}

/**
 * Insert specific sub basic_string into the destination basic_string at specific position.
 */
void basic_string_insert_substring(
    basic_string_t* pt_basic_string, size_t t_pos, const basic_string_t* cpt_insert, size_t t_startpos, size_t t_len)
{
    basic_string_replace_substring(pt_basic_string, t_pos, 0, cpt_insert, t_startpos, t_len);
}

/**
 * Insert specific value string into the destination basic_string at specific position.
 */
void basic_string_insert_cstr(basic_string_t* pt_basic_string, size_t t_pos, const void* cpv_value_string)
{
    basic_string_insert_subcstr(
        pt_basic_string, t_pos, cpv_value_string,
        _basic_string_get_value_string_length(pt_basic_string, cpv_value_string));
}

/**
 * Insert specific sub value string into the destination basic_string at specific position.
 */
void basic_string_insert_subcstr(
    basic_string_t* pt_basic_string, size_t t_pos, const void* cpv_value_string, size_t t_len)
{
    basic_string_replace_subcstr(pt_basic_string, t_pos, 0, cpv_value_string, t_len);
}

/**
 * Insert a range of elements into basic_string at a specificed position.
 */
void basic_string_insert_range(
    basic_string_t* pt_basic_string, basic_string_iterator_t it_pos,
    basic_string_iterator_t it_begin, basic_string_iterator_t it_end)
{
    basic_string_replace_range(pt_basic_string, it_pos, it_pos, it_begin, it_end);
}

/**
 * Erase an element in a basic string from a specificed position.
 */
basic_string_iterator_t basic_string_erase(basic_string_t* pt_basic_string, basic_string_iterator_t it_pos)
{
    size_t t_pos = 0;

    assert(pt_basic_string != NULL);
    assert(_basic_string_is_inited(pt_basic_string));
    assert(_basic_string_iterator_belong_to_basic_string(pt_basic_string, it_pos));
    assert(!iterator_equal(it_pos, basic_string_end(pt_basic_string)));

    t_pos = iterator_distance(basic_string_begin(pt_basic_string), it_pos);
    basic_string_erase_substring(pt_basic_string, t_pos, 1);
    return iterator_next_n(basic_string_begin(pt_basic_string), t_pos);
}

/**
 * Erase a range of elements in a basic string from a specificed range.
 */
basic_string_iterator_t basic_string_erase_range(
    basic_string_t* pt_basic_string, basic_string_iterator_t it_begin, basic_string_iterator_t it_end)
{
    assert(pt_basic_string != NULL);
    assert(_basic_string_is_inited(pt_basic_string));
    assert(_basic_string_iterator_belong_to_basic_string(pt_basic_string, it_begin));
    assert(_basic_string_iterator_belong_to_basic_string(pt_basic_string, it_end));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    if (iterator_equal(it_begin, it_end)) {
        return it_begin;
    } else {
        size_t t_pos = iterator_distance(basic_string_begin(pt_basic_string), it_begin);
        basic_string_erase_substring(pt_basic_string, t_pos, iterator_distance(it_begin, it_end));
        return iterator_next_n(basic_string_begin(pt_basic_string), t_pos);
    }
}

/**
 * Erase a sub basic string in a basic string from a specificed range.
 */
void basic_string_erase_substring(basic_string_t* pt_basic_string, size_t t_pos, size_t t_len)
{
    basic_string_replace_elem(pt_basic_string, t_pos, t_len, 0, NULL);
}

/**
 * Replace elements in a basic_string at a specificed position with specificed basic_string.
 */
void basic_string_replace(basic_string_t* pt_basic_string, size_t t_pos, size_t t_len, const basic_string_t* cpt_replace)
{
    basic_string_replace_substring(pt_basic_string, t_pos, t_len, cpt_replace, 0, NPOS);
}

/**
 * Replace elements in a basic_string at a specificed position with specificed sub basic_string.
 */
void basic_string_replace_substring(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_len,
    const basic_string_t* cpt_replace, size_t t_position, size_t t_length)
{
    size_t          t_size = 0;
    size_t          t_newsize = 0;
    size_t          t_typesize = 0;
    _byte_t*        pby_dest = NULL;
    _byte_t*        pby_dest_end = NULL;
    _byte_t*        pby_src = NULL;
    _byte_t*        pby_src_end = NULL;
    basic_string_t* pt_basic_temp = NULL;

    assert(pt_basic_string != NULL);
    assert(cpt_replace != NULL);
    assert(_basic_string_is_inited(pt_basic_string));
    assert(_basic_string_is_inited(cpt_replace));
    assert(_basic_string_same_type(pt_basic_string, cpt_replace));
    assert(t_pos <= basic_string_size(pt_basic_string));
    assert(t_position <= basic_string_size(cpt_replace));

    if (t_len == NPOS || t_len + t_pos >= basic_string_size(pt_basic_string)) {
        t_len = basic_string_size(pt_basic_string) - t_pos;
    }
    if (t_length == NPOS || t_length + t_position >= basic_string_size(cpt_replace)) {
        t_length = basic_string_size(cpt_replace) - t_position;
    }

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
    t_size = basic_string_size(pt_basic_string);
    t_newsize = t_size + t_length - t_len;
    pby_dest = pt_basic_string->_pby_string + t_pos * t_typesize;
    pby_dest_end = pby_dest + t_len * t_typesize;
    pby_src = cpt_replace->_pby_string + t_position * t_typesize;
    pby_src_end = pby_src + t_length * t_typesize;

    /* Overlapping case */
    if ((pby_src_end > pby_dest && pby_src_end <= pby_dest_end) ||
        (pby_src >= pby_dest && pby_src < pby_dest_end)) {
        pt_basic_temp = _create_basic_string(_GET_BASIC_STRING_TYPE_NAME(cpt_replace));
        basic_string_init_copy_substring(pt_basic_temp, cpt_replace, t_position, t_length);
    }

    _basic_string_replace_preparation(pt_basic_string, t_pos, t_len, t_length);

    /* Must be calculate dest and src because the memory pt_basic_string->_pby_string may be reallocated. */
    pby_dest = pt_basic_string->_pby_string + t_pos * t_typesize;
    pby_dest_end = pby_dest + t_len * t_typesize;
    pby_src = cpt_replace->_pby_string + t_position * t_typesize;
    pby_src_end = pby_src + t_length * t_typesize;

    if (pt_basic_temp != NULL) {
        pby_src = pt_basic_temp->_pby_string;
    } else if (pby_src >= pby_dest_end && pby_src <= pt_basic_string->_pby_string + t_size * t_typesize) {
        if (t_newsize > t_size) {
            pby_src = pby_src + (t_newsize - t_size) * t_typesize;
        } else {
            pby_src = pby_src - (t_size - t_newsize) * t_typesize;
        }
    }

    /* copy elements in replace range */
    _basic_string_copy_substring_auxiliary(pt_basic_string, pby_dest, pby_src, t_length);

    if (pt_basic_temp != NULL) {
        basic_string_destroy(pt_basic_temp);
    }
}

/**
 * Replace elements in a basic_string at a specificed position with specificed value string.
 */
void basic_string_replace_cstr(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_len, const void* cpv_value_string)
{
    basic_string_replace_subcstr(
        pt_basic_string, t_pos, t_len, cpv_value_string,
        _basic_string_get_value_string_length(pt_basic_string, cpv_value_string));
}

/**
 * Replace elements in a basic_string at a specificed position with specificed sub value string.
 */
void basic_string_replace_subcstr(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_len, const void* cpv_value_string, size_t t_length)
{
    size_t   t_size = 0;
    size_t   t_newsize = 0;
    size_t   t_typesize = 0;
    _byte_t* pby_dest = NULL;

    assert(pt_basic_string != NULL);
    assert(cpv_value_string != NULL);
    assert(_basic_string_is_inited(pt_basic_string));
    assert(t_pos <= basic_string_size(pt_basic_string));
    assert(t_length <= basic_string_max_size(pt_basic_string));

    if (t_len == NPOS || t_len + t_pos >= basic_string_size(pt_basic_string)) {
        t_len = basic_string_size(pt_basic_string) - t_pos;
    }

    _basic_string_replace_preparation(pt_basic_string, t_pos, t_len, t_length);

    /* copy elements in replace range */
    t_size = basic_string_size(pt_basic_string);
    t_newsize = t_size + t_length - t_len;
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
    pby_dest = pt_basic_string->_pby_string + t_pos * t_typesize;
    _basic_string_copy_subcstr_auxiliary(pt_basic_string, pby_dest, cpv_value_string, t_length);
}

/**
 * Replace elements in a basic_string at a specificed range with specificed basic_string.
 */
void basic_string_range_replace(
    basic_string_t* pt_basic_string, basic_string_iterator_t it_begin,
    basic_string_iterator_t it_end, const basic_string_t* cpt_replace)
{
    basic_string_range_replace_substring(pt_basic_string, it_begin, it_end, cpt_replace, 0, NPOS);
}

/**
 * Replace elements in a basic_string at a specificed range with specificed sub basic_string.
 */
void basic_string_range_replace_substring(
    basic_string_t* pt_basic_string, basic_string_iterator_t it_begin, basic_string_iterator_t it_end,
    const basic_string_t* cpt_replace, size_t t_pos, size_t t_len)
{
    assert(pt_basic_string != NULL);
    assert(cpt_replace != NULL);
    assert(_basic_string_is_inited(pt_basic_string));
    assert(_basic_string_is_inited(cpt_replace));
    assert(_basic_string_iterator_belong_to_basic_string(pt_basic_string, it_begin));
    assert(_basic_string_iterator_belong_to_basic_string(pt_basic_string, it_end));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    basic_string_replace_substring(
        pt_basic_string, iterator_distance(basic_string_begin(pt_basic_string), it_begin),
        iterator_distance(it_begin, it_end), cpt_replace, t_pos, t_len);
}

/**
 * Replace elements in a basic_string at a specificed range with specificed value string.
 */
void basic_string_range_replace_cstr(
    basic_string_t* pt_basic_string, basic_string_iterator_t it_begin,
    basic_string_iterator_t it_end, const void* cpv_value_string)
{
    basic_string_range_replace_subcstr(
        pt_basic_string, it_begin, it_end, cpv_value_string,
        _basic_string_get_value_string_length(pt_basic_string, cpv_value_string));
}

/**
 * Replace elements in a basic_string at a specificed range with specificed sub value string.
 */
void basic_string_range_replace_subcstr(
    basic_string_t* pt_basic_string, basic_string_iterator_t it_begin,
    basic_string_iterator_t it_end, const void* cpv_value_string, size_t t_len)
{
    assert(pt_basic_string != NULL);
    assert(cpv_value_string != NULL);
    assert(_basic_string_is_inited(pt_basic_string));
    assert(_basic_string_iterator_belong_to_basic_string(pt_basic_string, it_begin));
    assert(_basic_string_iterator_belong_to_basic_string(pt_basic_string, it_end));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    basic_string_replace_subcstr(
        pt_basic_string, iterator_distance(basic_string_begin(pt_basic_string), it_begin),
        iterator_distance(it_begin, it_end), cpv_value_string, t_len);
}

/**
 * Replace elements in a basic_string at a specificed range with specificed range.
 */
void basic_string_replace_range(
    basic_string_t* pt_basic_string, basic_string_iterator_t it_begin, basic_string_iterator_t it_end,
    basic_string_iterator_t it_first, basic_string_iterator_t it_last)
{
    size_t   t_pos = 0;
    size_t   t_len = 0;
    size_t   t_position = 0;
    size_t   t_length = 0;
    size_t   t_replacelen = 0;
    size_t   t_size = 0;
    size_t   t_newsize = 0;
    size_t   t_typesize = 0;
    _byte_t* pby_dest = NULL;
    basic_string_t* pt_replace = NULL;

    assert(pt_basic_string != NULL);
    assert(_basic_string_is_inited(pt_basic_string));
    assert(_basic_string_iterator_belong_to_basic_string(pt_basic_string, it_begin));
    assert(_basic_string_iterator_belong_to_basic_string(pt_basic_string, it_end));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));
    assert(_basic_string_same_iterator_type(pt_basic_string, it_first));
    assert(_basic_string_same_iterator_type(pt_basic_string, it_last));
    assert(iterator_equal(it_first, it_last) || _iterator_before(it_first, it_last));

    if (_BASIC_STRING_ITERATOR_CONTAINER(it_first) == pt_basic_string) {
        pt_replace = _BASIC_STRING_ITERATOR_CONTAINER(it_first);
        t_pos = iterator_distance(basic_string_begin(pt_basic_string), it_begin);
        t_len = iterator_distance(it_begin, it_end);
        t_position = iterator_distance(basic_string_begin(pt_replace), it_first);
        t_length = iterator_distance(it_first, it_last);

        basic_string_replace_substring(pt_basic_string, t_pos, t_len, pt_replace, t_position, t_length);
    } else {
        t_pos = iterator_distance(basic_string_begin(pt_basic_string), it_begin);
        t_len = iterator_distance(it_begin, it_end);
        t_replacelen = iterator_distance(it_first, it_last);
        _basic_string_replace_preparation(pt_basic_string, t_pos, t_len, t_replacelen);

        t_size = basic_string_size(pt_basic_string);
        t_newsize = t_size + t_replacelen - t_len;
        t_typesize = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
        pby_dest = pt_basic_string->_pby_string + t_pos * t_typesize;
        _basic_string_copy_range_auxiliary(pt_basic_string, pby_dest, it_first, it_last);
    }
}

/**
 * Reset the size of basic_string elements.
 */
void basic_string_resize(basic_string_t* pt_basic_string, size_t t_resize)
{
    assert(pt_basic_string != NULL);
    assert(_basic_string_is_inited(pt_basic_string));
    assert(t_resize <= basic_string_max_size(pt_basic_string));

    if (t_resize > basic_string_capacity(pt_basic_string) || _basic_string_is_shared(pt_basic_string)) {
        size_t               t_copylen = 0;
        _byte_t*             pby_dest = NULL;
        _byte_t*             pby_src = NULL;
        _basic_string_rep_t* prep = _basic_string_rep_construct(pt_basic_string, t_resize, t_resize, 0);

        pby_dest = _basic_string_rep_get_data(prep);
        pby_src = pt_basic_string->_pby_string;
        t_copylen = t_resize < basic_string_size(pt_basic_string) ? t_resize : basic_string_size(pt_basic_string);
        _basic_string_copy_substring_auxiliary(pt_basic_string, pby_dest, pby_src, t_copylen);

        _basic_string_rep_reduce_shared(
            _basic_string_rep_get_representation(pt_basic_string->_pby_string),
            _GET_BASIC_STRING_TYPE_DESTROY_FUNCTION(pt_basic_string), &pt_basic_string->_t_typeinfo);
        pt_basic_string->_pby_string = _basic_string_rep_get_data(prep);
    } else {
        if (t_resize < basic_string_size(pt_basic_string)) {
            size_t   t_delpos = t_resize;
            size_t   t_dellen = basic_string_size(pt_basic_string) - t_resize;
            _byte_t* pby_del = pt_basic_string->_pby_string + t_delpos * _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
            _basic_string_destroy_elem_range_auxiliary(pt_basic_string, pby_del, t_dellen);
        } else {
            size_t   t_initpos = basic_string_size(pt_basic_string);
            size_t   t_initlen = t_resize - basic_string_size(pt_basic_string);
            _byte_t* pby_init = pt_basic_string->_pby_string + t_initpos * _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
            _basic_string_init_elem_range_auxiliary(pt_basic_string, pby_init, t_initlen);
        }
        _basic_string_rep_set_length(_basic_string_rep_get_representation(pt_basic_string->_pby_string), t_resize);
    }
}

/** local function implementation section **/

/** eof **/

