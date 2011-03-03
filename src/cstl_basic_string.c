/*
 *  The implementation of basic_string
 *  Copyright (C)  2008,2009,2010,2011  Wangbo
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
#include <cstl/cstl_iterator.h>
#include <cstl/cstl_iterator_private.h>
#include <cstl/cvector.h>
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
    assert(pt_basic_string != NULL);

    vector_init(&pt_basic_string->_t_vector);
}

/**
 * Initialize basic_string container with an exist basic_string container.
 */
void basic_string_init_copy(basic_string_t* pt_dest, const basic_string_t* cpt_src)
{
    assert(pt_dest != NULL);
    assert(cpt_src != NULL);

    vector_init_copy(&pt_dest->_t_vector, &cpt_src->_t_vector);
}

/**
 * Initialize basic_string container with an exist basic_string range.
 */
void basic_string_init_copy_range(
    basic_string_t* pt_basic_string, basic_string_iterator_t it_begin, basic_string_iterator_t it_end)
{
    assert(pt_basic_string != NULL);
    assert(_GET_BASIC_STRING_CONTAINER_TYPE(it_begin) == _BASIC_STRING_CONTAINER);
    assert(_GET_BASIC_STRING_CONTAINER_TYPE(it_end) == _BASIC_STRING_CONTAINER);

    _GET_VECTOR_CONTAINER_TYPE(it_begin) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE(it_end) = _VECTOR_CONTAINER;

    vector_init_copy_range(&pt_basic_string->_t_vector, it_begin, it_end);
}

/**
 * Initialize basic_string container with an exist sub basic_string container.
 */
void basic_string_init_copy_substring(basic_string_t* pt_dest, const basic_string_t* cpt_src, size_t t_pos, size_t t_len)
{
    basic_string_iterator_t it_begin;
    basic_string_iterator_t it_end;

    assert(pt_dest != NULL);
    assert(cpt_src != NULL);
    assert(t_pos < basic_string_size(cpt_src));

    it_begin = iterator_next_n(basic_string_begin(cpt_src), t_pos);

    if(t_len == NPOS || t_len + t_pos >= basic_string_size(cpt_src))
    {
        it_end = basic_string_end(cpt_src);
    }
    else
    {
        it_end = iterator_next_n(basic_string_begin(cpt_src), t_pos + t_len);
    }

    _GET_VECTOR_CONTAINER_TYPE(it_begin) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE(it_end) = _VECTOR_CONTAINER;

    vector_init_copy_range(&pt_dest->_t_vector, it_begin, it_end);
}

/**
 * Initialize empty basic_string container.
 */
void basic_string_init_cstr(basic_string_t* pt_basic_string, const void* cpv_value_string)
{
    basic_string_init_subcstr(pt_basic_string, cpv_value_string, NPOS);
}

/**
 * Initialize basic_string container specific sub value string.
 */
void basic_string_init_subcstr(basic_string_t* pt_basic_string, const void* cpv_value_string, size_t t_len)
{
    size_t   t_typesize = 0;
    size_t   t_length = 0;
    size_t   i = 0;
    _byte_t* pby_value = NULL;
    bool_t   b_result = false;

    assert(pt_basic_string != NULL);
    assert(cpv_value_string != NULL);

    vector_init(&pt_basic_string->_t_vector);
    t_length = _basic_string_get_value_string_length(pt_basic_string, cpv_value_string);
    t_len = (t_len < t_length ? t_len : t_length);

    if(t_len > 0)
    {
        vector_resize(&pt_basic_string->_t_vector, t_len);
        assert(vector_size(&pt_basic_string->_t_vector) == t_len);

        t_typesize = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
        pby_value = _GET_BASIC_STRING_COREPOS(basic_string_begin(pt_basic_string));
        assert(pby_value != NULL);

        /* char* */
        if(strncmp(_GET_BASIC_STRING_TYPE_BASENAME(pt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
        {
            for(i = 0; i < t_len; ++i)
            {
                string_assign_cstr((string_t*)(pby_value + i * t_typesize), *((char**)cpv_value_string + i));
            }
        }
        else if(_GET_BASIC_STRING_TYPE_STYLE(pt_basic_string) == _TYPE_C_BUILTIN)
        {
            for(i = 0; i < t_len; ++i)
            {
                b_result = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
                _GET_BASIC_STRING_TYPE_COPY_FUNCTION(pt_basic_string)(
                    pby_value + i * t_typesize, (_byte_t*)cpv_value_string + i * t_typesize, &b_result);
                assert(b_result);
            }
        }
        else
        {
            for(i = 0; i < t_len; ++i)
            {
                b_result = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
                _GET_BASIC_STRING_TYPE_COPY_FUNCTION(pt_basic_string)(
                    pby_value + i * t_typesize, *((_byte_t**)cpv_value_string + i), &b_result);
                assert(b_result);
            }
        }
    }
}

/**
 * Destroy basic_string container.
 */
void basic_string_destroy(basic_string_t* pt_basic_string)
{
    assert(pt_basic_string != NULL);

    vector_destroy(&pt_basic_string->_t_vector);
}

/**
 * Get data string.
 */
const void* basic_string_c_str(const basic_string_t* cpt_basic_string)
{
    assert(cpt_basic_string != NULL);

    if(basic_string_empty(cpt_basic_string))
    {
        return NULL;
    }
    else
    {
        return basic_string_data(cpt_basic_string);
    }
}

/**
 * Get data string.
 */
const void* basic_string_data(const basic_string_t* cpt_basic_string)
{
    assert(cpt_basic_string != NULL);

    return vector_at(&cpt_basic_string->_t_vector, 0);
}

/**
 * Copy spceificed sub basic_string to buffer.
 */
size_t basic_string_copy(const basic_string_t* cpt_basic_string, void* pv_buffer, size_t t_len, size_t t_pos)
{
    void*  pv_pos = NULL;
    size_t t_size = 0;
    size_t t_typesize = 0;
    size_t i = 0;
    bool_t b_result = false;

    assert(cpt_basic_string != NULL);
    assert(pv_buffer != NULL);

    t_size = basic_string_size(cpt_basic_string);
    assert(t_size > t_pos);
    t_size = (t_size - t_pos) < t_len ? (t_size - t_pos) : t_len;

    /* the elements in buffer must be initialized */
    pv_pos = basic_string_at(cpt_basic_string, t_pos);
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    for(i = 0; i < t_size; ++i)
    {
        b_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
        _GET_BASIC_STRING_TYPE_COPY_FUNCTION(cpt_basic_string)(
            (_byte_t*)pv_buffer + i * t_typesize, (_byte_t*)pv_pos + i * t_typesize, &b_result);
        assert(b_result);
    }

    return t_size;
}

/**
 * Get basic_string element size.
 */
size_t basic_string_size(const basic_string_t* cpt_basic_string)
{
    assert(cpt_basic_string != NULL);

    return vector_size(&cpt_basic_string->_t_vector);
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
    assert(cpt_basic_string != NULL);

    return vector_empty(&cpt_basic_string->_t_vector);
}

/**
 * Return maximum element number.
 */
size_t basic_string_max_size(const basic_string_t* cpt_basic_string)
{
    assert(cpt_basic_string != NULL);

    return vector_max_size(&cpt_basic_string->_t_vector);
}

/**
 * Get basic_string capacity.
 */
size_t basic_string_capacity(const basic_string_t* cpt_basic_string)
{
    assert(cpt_basic_string != NULL);

    return vector_capacity(&cpt_basic_string->_t_vector);
}

/**
 * Access basic_string data using subscript.
 */
void* basic_string_at(const basic_string_t* cpt_basic_string, size_t t_pos)
{
    assert(cpt_basic_string != NULL);

    return vector_at(&cpt_basic_string->_t_vector, t_pos);
}

/**
 * Test the two basic_strings are equal.
 */
bool_t basic_string_equal(const basic_string_t* cpt_first, const basic_string_t* cpt_second)
{
    assert(cpt_first != NULL);
    assert(cpt_second != NULL);

    return vector_equal(&cpt_first->_t_vector, &cpt_second->_t_vector);
}

/**
 * Test the two basic_strings are unequal.
 */
bool_t basic_string_not_equal(const basic_string_t* cpt_first, const basic_string_t* cpt_second)
{
    assert(cpt_first != NULL);
    assert(cpt_second != NULL);

    return vector_not_equal(&cpt_first->_t_vector, &cpt_second->_t_vector);
}

/**
 * Test the first basic_string is less than the second basic_string.
 */
bool_t basic_string_less(const basic_string_t* cpt_first, const basic_string_t* cpt_second)
{
    assert(cpt_first != NULL);
    assert(cpt_second != NULL);

    return vector_less(&cpt_first->_t_vector, &cpt_second->_t_vector);
}

/**
 * Test the first basic_string is less than or equal to the second basic_string.
 */
bool_t basic_string_less_equal(const basic_string_t* cpt_first, const basic_string_t* cpt_second)
{
    assert(cpt_first != NULL);
    assert(cpt_second != NULL);

    return vector_less_equal(&cpt_first->_t_vector, &cpt_second->_t_vector);
}

/**
 * Test the first basic_string is greater than the second basic_string.
 */
bool_t basic_string_greater(const basic_string_t* cpt_first, const basic_string_t* cpt_second)
{
    assert(cpt_first != NULL);
    assert(cpt_second != NULL);

    return vector_greater(&cpt_first->_t_vector, &cpt_second->_t_vector);
}

/**
 * Test the first basic_string is greater than or equal to the second basic_string.
 */
bool_t basic_string_greater_equal(const basic_string_t* cpt_first, const basic_string_t* cpt_second)
{
    assert(cpt_first != NULL);
    assert(cpt_second != NULL);

    return vector_greater_equal(&cpt_first->_t_vector, &cpt_second->_t_vector);
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
    assert(_basic_string_same_type(cpt_first, cpt_second));

    if(cpt_first == cpt_second)
    {
        return 0;
    }

    if(basic_string_empty(cpt_first) && !basic_string_empty(cpt_second))
    {
        return -1;
    }
    else if(!basic_string_empty(cpt_first) && basic_string_empty(cpt_second))
    {
        return 1;
    }
    else if(basic_string_empty(cpt_first) && basic_string_empty(cpt_second))
    {
        return 0;
    }

    return basic_string_compare_substring_string(cpt_first, 0, NPOS, cpt_second);
}

/**
 * Compare the first sub basic_string and the second basic_string.
 */
int basic_string_compare_substring_string(
    const basic_string_t* cpt_first, size_t t_pos, size_t t_len, const basic_string_t* cpt_second)
{
    assert(_basic_string_same_type(cpt_first, cpt_second));
    assert(t_pos < basic_string_size(cpt_first));

    if(t_len == 0 && !basic_string_empty(cpt_second))
    {
        return -1;
    }
    else if(t_len > 0 && basic_string_empty(cpt_second))
    {
        return 1;
    }
    else if(t_len == 0 && basic_string_empty(cpt_second))
    {
        return 0;
    }

    return basic_string_compare_substring_substring(cpt_first, t_pos, t_len, cpt_second, 0, NPOS);
}

/**
 * Compare two sub basic_strings.
 */
int basic_string_compare_substring_substring(
    const basic_string_t* cpt_first, size_t t_firstpos, size_t t_firstlen,
    const basic_string_t* cpt_second, size_t t_secondpos, size_t t_secondlen)
{
    size_t                  t_cmplen = 0;
    size_t                  t_firstlentmp = 0;
    size_t                  t_secondlentmp = 0;
    size_t                  i = 0;
    bool_t                  b_result;
    basic_string_iterator_t it_first;
    basic_string_iterator_t it_second;

    assert(cpt_first != NULL);
    assert(cpt_second != NULL);
    assert(_basic_string_same_type(cpt_first, cpt_second));
    assert(t_firstpos < basic_string_size(cpt_first));
    assert(t_secondpos < basic_string_size(cpt_second));

    t_firstlentmp = basic_string_size(cpt_first) - t_firstpos;
    t_secondlentmp = basic_string_size(cpt_second) - t_secondpos;
    t_firstlen = t_firstlen < t_firstlentmp ? t_firstlen : t_firstlentmp;
    t_secondlen = t_secondlen < t_secondlentmp ? t_secondlen : t_secondlentmp;
    t_cmplen = t_firstlen < t_secondlen ? t_firstlen : t_secondlen;

    if(t_firstlen == 0 && t_secondlen > 0)
    {
        return -1;
    }
    else if(t_firstlen > 0 && t_secondlen == 0)
    {
        return 1;
    }
    else if(t_firstlen == 0 && t_secondlen == 0)
    {
        return 0;
    }

    for(it_first = iterator_next_n(basic_string_begin(cpt_first), t_firstpos),
        it_second = iterator_next_n(basic_string_begin(cpt_second), t_secondpos),
        i = 0;
        i < t_cmplen;
        ++i)
    {
        b_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_first);
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_first)(
            _GET_BASIC_STRING_COREPOS(it_first), _GET_BASIC_STRING_COREPOS(it_second), &b_result);
        if(b_result)
        {
            return -1;
        }

        b_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_first);
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_first)(
            _GET_BASIC_STRING_COREPOS(it_second), _GET_BASIC_STRING_COREPOS(it_first), &b_result);
        if(b_result)
        {
            return 1;
        }

        it_first = iterator_next(it_first);
        it_second = iterator_next(it_second);
    }

    return t_firstlen < t_secondlen ? -1 : (t_firstlen > t_secondlen ? 1 : 0);
}

/**
 * Compare the basic_string and the value string.
 */
int basic_string_compare_cstr(const basic_string_t* cpt_basic_string, const void* cpv_value_string)
{
    size_t t_stringlen = basic_string_length(cpt_basic_string);
    size_t t_valuelen = _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string);

    if(t_stringlen == 0 && t_valuelen > 0)
    {
        return -1;
    }
    else if(t_stringlen > 0 && t_valuelen == 0)
    {
        return 1;
    }
    else if(t_stringlen == 0 && t_valuelen == 0)
    {
        return 0;
    }

    return basic_string_compare_substring_subcstr(cpt_basic_string, 0, NPOS, cpv_value_string, NPOS);
}

/**
 * Compare the sub basic_string and the value string.
 */
int basic_string_compare_substring_cstr(
    const basic_string_t* cpt_basic_string, size_t t_pos, size_t t_len, const void* cpv_value_string)
{
    return basic_string_compare_substring_subcstr(cpt_basic_string, t_pos, t_len, cpv_value_string, NPOS);
}

/**
 * Compare the sub basic_string and the sub value string.
 */
int basic_string_compare_substring_subcstr(
    const basic_string_t* cpt_basic_string, size_t t_pos, size_t t_len, const void* cpv_value_string, size_t t_valuelen)
{
    size_t   t_lentmp = 0;
    size_t   t_valuelentmp = 0;
    size_t   t_cmplen = 0;
    size_t   t_typesize = 0;
    size_t   i = 0;
    _byte_t* pby_string = NULL;
    bool_t   b_result = false;

    assert(cpt_basic_string != NULL);
    assert(cpv_value_string != NULL);
    assert(t_pos < basic_string_size(cpt_basic_string));

    /* get actual string length and value string length */
    t_lentmp = basic_string_size(cpt_basic_string) - t_pos;
    t_valuelentmp = _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string);
    t_len = t_len < t_lentmp ? t_len : t_lentmp;
    t_valuelen = t_valuelen < t_valuelentmp ? t_valuelen : t_valuelentmp;
    t_cmplen = t_len < t_valuelen ? t_len : t_valuelen;

    if(t_len == 0 && t_valuelen > 0)
    {
        return -1;
    }
    else if(t_len > 0 && t_valuelen == 0)
    {
        return 1;
    }
    else if(t_len == 0 && t_valuelen == 0)
    {
        return 0;
    }

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    pby_string = _GET_BASIC_STRING_COREPOS(basic_string_begin(cpt_basic_string));
    assert(pby_string != NULL);

    /* char* */
    if(strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        for(i = 0; i < t_cmplen; ++i)
        {
            int n_result = string_compare_cstr((string_t*)(pby_string + i * t_typesize), *((char**)cpv_value_string + i));
            if(n_result != 0)
            {
                return n_result;
            }
        }
    }
    else if(_GET_BASIC_STRING_TYPE_STYLE(cpt_basic_string) == _TYPE_C_BUILTIN)
    {
        for(i = 0; i < t_cmplen; ++i)
        {
            b_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                pby_string + i * t_typesize, (_byte_t*)cpv_value_string + i * t_typesize, &b_result);
            if(b_result)
            {
                return -1;
            }
            b_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                (_byte_t*)cpv_value_string + i * t_typesize, pby_string + i * t_typesize, &b_result);
            if(b_result)
            {
                return 1;
            }
        }
    }
    else
    {
        for(i = 0; i < t_cmplen; ++i)
        {
            b_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                pby_string + i * t_typesize, *((_byte_t**)cpv_value_string + i), &b_result);
            if(b_result)
            {
                return -1;
            }
            b_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                *((_byte_t**)cpv_value_string + i), pby_string + i * t_typesize, &b_result);
            if(b_result)
            {
                return 1;
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
    basic_string_iterator_t it_string;
    basic_string_iterator_t it_substr;
    size_t                  t_size = 0;
    bool_t                  b_result = false;

    assert(cpt_basic_string != NULL);
    assert(t_pos < basic_string_size(cpt_basic_string));

    pt_substr = _create_basic_string(_GET_BASIC_STRING_TYPE_NAME(cpt_basic_string));

    t_size = basic_string_size(cpt_basic_string) - t_pos;
    t_len = t_len < t_size ? t_len : t_size;
    vector_init_n(&pt_substr->_t_vector, t_len);

    for(it_string = iterator_next_n(basic_string_begin(cpt_basic_string), t_pos),
        it_substr = basic_string_begin(pt_substr);
        !iterator_equal(it_substr, basic_string_end(pt_substr));
        it_string = iterator_next(it_string),
        it_substr = iterator_next(it_substr))
    {
        b_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
        _GET_BASIC_STRING_TYPE_COPY_FUNCTION(cpt_basic_string)(
            _GET_BASIC_STRING_COREPOS(it_substr), _GET_BASIC_STRING_COREPOS(it_string), &b_result);
        assert(b_result);
    }

    return pt_substr;
}


/**
 * Connect basic string with other basic string.
 */
void basic_string_connect(basic_string_t* pt_dest, const basic_string_t* cpt_src)
{
    size_t   t_destlen = 0;
    size_t   t_srclen = 0;
    size_t   i = 0;
    _byte_t* pby_dest = NULL;
    _byte_t* pby_src = NULL;
    bool_t   b_result = false;

    assert(pt_dest != NULL);
    assert(cpt_src != NULL);
    assert(_basic_string_same_type(pt_dest, cpt_src));

    t_destlen = basic_string_size(pt_dest);
    t_srclen = basic_string_size(cpt_src);

    if(t_srclen > 0)
    {
        vector_resize(&pt_dest->_t_vector, t_destlen + t_srclen);

        pby_dest = _GET_BASIC_STRING_COREPOS(iterator_next_n(basic_string_begin(pt_dest), t_destlen));
        pby_src = _GET_BASIC_STRING_COREPOS(basic_string_begin(cpt_src));
        assert(pby_dest != NULL && pby_src != NULL);

        for(i = 0; i < t_srclen; ++i)
        {
            b_result = _GET_BASIC_STRING_TYPE_SIZE(pt_dest);
            _GET_BASIC_STRING_TYPE_COPY_FUNCTION(pt_dest)(pby_dest, pby_src, &b_result);
            pby_dest += _GET_BASIC_STRING_TYPE_SIZE(pt_dest);
            pby_src += _GET_BASIC_STRING_TYPE_SIZE(cpt_src);
        }
    }
}

/**
 * Connect basic string with value string.
 */
void basic_string_connect_cstr(basic_string_t* pt_basic_string, const void* cpv_value_string)
{
    size_t   t_typesize = 0;
    size_t   t_destlen = 0;
    size_t   t_srclen = 0;
    size_t   i = 0;
    _byte_t* pby_dest = NULL;
    bool_t   b_result = false;

    assert(pt_basic_string != NULL);
    assert(cpv_value_string != NULL);

    t_destlen = basic_string_size(pt_basic_string);
    t_srclen = _basic_string_get_value_string_length(pt_basic_string, cpv_value_string);

    if(t_srclen > 0)
    {
        vector_resize(&pt_basic_string->_t_vector, t_destlen + t_srclen);

        pby_dest = _GET_BASIC_STRING_COREPOS(iterator_next_n(basic_string_begin(pt_basic_string), t_destlen));
        assert(pby_dest != NULL);

        t_typesize = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
        /* char* */
        if(strncmp(_GET_BASIC_STRING_TYPE_BASENAME(pt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
        {
            for(i = 0; i < t_srclen; ++i)
            {
                string_assign_cstr((string_t*)(pby_dest + i * t_typesize), *((char**)cpv_value_string + i));
            }
        }
        else if(_GET_BASIC_STRING_TYPE_STYLE(pt_basic_string) == _TYPE_C_BUILTIN)
        {
            for(i = 0; i < t_srclen; ++i)
            {
                b_result = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
                _GET_BASIC_STRING_TYPE_COPY_FUNCTION(pt_basic_string)(
                    pby_dest + i * t_typesize, (_byte_t*)cpv_value_string + i * t_typesize, &b_result);
                assert(b_result);
            }
        }
        else
        {
            for(i = 0; i < t_srclen; ++i)
            {
                b_result = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
                _GET_BASIC_STRING_TYPE_COPY_FUNCTION(pt_basic_string)(
                    pby_dest + i * t_typesize, *((_byte_t**)cpv_value_string + i), &b_result);
                assert(b_result);
            }
        }
    }
}

/**
 * Return a iterator to the first element in the basic string container.
 */
basic_string_iterator_t basic_string_begin(const basic_string_t* cpt_basic_string)
{
    basic_string_iterator_t it_begin;

    assert(cpt_basic_string != NULL);

    it_begin = vector_begin(&cpt_basic_string->_t_vector);
    _GET_BASIC_STRING_CONTAINER_TYPE(it_begin) = _BASIC_STRING_CONTAINER;

    return it_begin;
}

/**
 * Return a iterator that points just beyond the end of basic_string container.
 */
basic_string_iterator_t basic_string_end(const basic_string_t* cpt_basic_string)
{
    basic_string_iterator_t it_end;

    assert(cpt_basic_string != NULL);

    it_end = vector_end(&cpt_basic_string->_t_vector);
    _GET_BASIC_STRING_CONTAINER_TYPE(it_end) = _BASIC_STRING_CONTAINER;

    return it_end;
}

basic_string_reverse_iterator_t basic_string_rbegin(
    const basic_string_t* cpt_basic_string)
{
    basic_string_reverse_iterator_t t_newiterator;

    assert(cpt_basic_string != NULL);
    assert(vector_size(&cpt_basic_string->_t_vector) > 0);

    if(basic_string_empty(cpt_basic_string))
    {
        t_newiterator = basic_string_rend(cpt_basic_string);
    }
    else
    {
        t_newiterator = vector_rbegin(&cpt_basic_string->_t_vector);
        _GET_BASIC_STRING_CONTAINER_TYPE(t_newiterator) = _BASIC_STRING_CONTAINER;
    }

    return t_newiterator;
}

basic_string_reverse_iterator_t basic_string_rend(const basic_string_t* cpt_basic_string)
{
    basic_string_iterator_t t_newiterator;

    assert(cpt_basic_string != NULL);

    t_newiterator = vector_rend(&cpt_basic_string->_t_vector);
    _GET_BASIC_STRING_CONTAINER_TYPE(t_newiterator) = _BASIC_STRING_CONTAINER;

    return t_newiterator;
}

/**
 * Find basic_string in basic_string.
 */
size_t basic_string_find(const basic_string_t* cpt_basic_string, const basic_string_t* cpt_find, size_t t_pos)
{
    basic_string_iterator_t it_iter;
    basic_string_iterator_t it_string;
    basic_string_iterator_t it_find;
    size_t                  t_stringlen = 0;
    size_t                  t_findlen = 0;
    bool_t                  b_result = false;

    assert(cpt_basic_string != NULL);
    assert(cpt_find != NULL);
    assert(_basic_string_same_type(cpt_basic_string, cpt_find));
    assert(t_pos < basic_string_size(cpt_basic_string));

    if(basic_string_empty(cpt_find))
    {
        return t_pos;
    }

    t_stringlen = basic_string_size(cpt_basic_string);
    t_findlen = basic_string_size(cpt_find);
    for(it_iter = iterator_next_n(basic_string_begin(cpt_basic_string), t_pos);
        !iterator_equal(it_iter, basic_string_end(cpt_basic_string));
        it_iter = iterator_next(it_iter), ++t_pos)
    {
        if(t_stringlen - t_pos < t_findlen)
        {
            return NPOS;
        }

        for(it_string = it_iter, it_find = basic_string_begin(cpt_find);
            !iterator_equal(it_find, basic_string_end(cpt_find));
            it_string = iterator_next(it_string), it_find = iterator_next(it_find))
        {
            b_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                _GET_BASIC_STRING_COREPOS(it_string), _GET_BASIC_STRING_COREPOS(it_find), &b_result);
            if(b_result)
            {
                break;
            }

            b_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                _GET_BASIC_STRING_COREPOS(it_find), _GET_BASIC_STRING_COREPOS(it_string), &b_result);
            if(b_result)
            {
                break;
            }
        }

        if(iterator_equal(it_find, basic_string_end(cpt_find)))
        {
            return t_pos;
        }
    }

    assert(false);
    return NPOS;
}

/**
 * Find value string in basic_string.
 */
size_t basic_string_find_cstr(const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos)
{
    return basic_string_find_subcstr(cpt_basic_string, cpv_value_string, t_pos, NPOS);
}

/**
 * Find sub value string in basic_string.
 */
size_t basic_string_find_subcstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos, size_t t_len)
{
    size_t   t_typesize = 0;
    size_t   t_stringlen = 0;
    size_t   t_cstrlen = 0;
    size_t   t_subcstrlen = 0;
    size_t   t_stringpos = 0;
    size_t   t_subcstrpos = 0;
    _byte_t* pby_string = NULL;
    bool_t   b_result = false;

    assert(cpt_basic_string != NULL);
    assert(cpv_value_string != NULL);
    assert(t_pos < basic_string_size(cpt_basic_string));

    t_stringlen = basic_string_length(cpt_basic_string);
    t_cstrlen = _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string);
    t_subcstrlen = t_len < t_cstrlen ? t_len : t_cstrlen;

    if(t_subcstrlen == 0)
    {
        return t_pos;
    }

    pby_string = _GET_BASIC_STRING_COREPOS(basic_string_begin(cpt_basic_string));
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);

    for(; t_pos < t_stringlen; ++t_pos)
    {
        if(t_stringlen - t_pos < t_subcstrlen)
        {
            return NPOS;
        }

        /* char* */
        if(strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
        {
            for(t_stringpos = t_pos, t_subcstrpos = 0; t_subcstrpos < t_subcstrlen; ++t_stringpos, ++t_subcstrpos)
            {
                if(string_not_equal_cstr(
                    (string_t*)(pby_string + t_stringpos * t_typesize), *((char**)cpv_value_string + t_subcstrpos)))
                {
                    break;
                }
            }
        }
        else if(_GET_BASIC_STRING_TYPE_STYLE(cpt_basic_string) == _TYPE_C_BUILTIN)
        {
            for(t_stringpos = t_pos, t_subcstrpos = 0; t_subcstrpos < t_subcstrlen; ++t_stringpos, ++t_subcstrpos)
            {
                b_result = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    pby_string + t_stringpos * t_typesize,
                    (_byte_t*)cpv_value_string + t_subcstrpos * t_typesize,
                    &b_result);
                if(b_result)
                {
                    break;
                }
                b_result = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    (_byte_t*)cpv_value_string + t_subcstrpos * t_typesize,
                    pby_string + t_stringpos * t_typesize,
                    &b_result);
                if(b_result)
                {
                    break;
                }
            }
        }
        else
        {
            for(t_stringpos = t_pos, t_subcstrpos = 0; t_subcstrpos < t_subcstrlen; ++t_stringpos, ++t_subcstrpos)
            {
                b_result = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    pby_string + t_stringpos * t_typesize,
                    *((_byte_t**)cpv_value_string + t_subcstrpos),
                    &b_result);
                if(b_result)
                {
                    break;
                }
                b_result = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    *((_byte_t**)cpv_value_string + t_subcstrpos),
                    pby_string + t_stringpos * t_typesize,
                    &b_result);
                if(b_result)
                {
                    break;
                }
            }
        }

        if(t_subcstrpos == t_subcstrlen)
        {
            return t_pos;
        }
    }

    assert(false);
    return NPOS;
}

/**
 * Find basic_string in basic_string in a backward direction.
 */
size_t basic_string_rfind(const basic_string_t* cpt_basic_string, const basic_string_t* cpt_find, size_t t_pos)
{
    basic_string_iterator_t it_iter;
    basic_string_iterator_t it_string;
    basic_string_iterator_t it_find;
    size_t                  t_stringlen = 0;
    size_t                  t_findlen = 0;
    bool_t                  b_result = false;

    assert(cpt_basic_string != NULL);
    assert(cpt_find != NULL);
    assert(_basic_string_same_type(cpt_basic_string, cpt_find));

    if(cpt_basic_string == cpt_find)
    {
        return 0;
    }

    t_stringlen = basic_string_size(cpt_basic_string);
    t_findlen = basic_string_size(cpt_find);

    if(t_stringlen == 0 || t_stringlen < t_findlen)
    {
        return NPOS;
    }

    t_pos = t_pos < t_stringlen ? t_pos : t_stringlen - 1;
    if(basic_string_empty(cpt_find))
    {
        return t_pos;
    }

    for(it_iter = iterator_next_n(basic_string_begin(cpt_basic_string), t_pos);
        ;
        it_iter = iterator_prev(it_iter), --t_pos)
    {
        for(it_string = it_iter,
            it_find = basic_string_begin(cpt_find);
            !iterator_equal(it_string, basic_string_end(cpt_basic_string)) &&
            !iterator_equal(it_find, basic_string_end(cpt_find));
            it_string = iterator_next(it_string),
            it_find = iterator_next(it_find))
        {
            b_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                _GET_BASIC_STRING_COREPOS(it_string), _GET_BASIC_STRING_COREPOS(it_find), &b_result);
            if(b_result)
            {
                break;
            }

            b_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                _GET_BASIC_STRING_COREPOS(it_find), _GET_BASIC_STRING_COREPOS(it_string), &b_result);
            if(b_result)
            {
                break;
            }
        }

        if(iterator_equal(it_find, basic_string_end(cpt_find)))
        {
            return t_pos;
        }
        if(t_pos == 0)
        {
            return NPOS;
        }
    }

    assert(false);
    return NPOS;
}

/**
 * Find value string in basic_string in a backward direction.
 */
size_t basic_string_rfind_cstr(const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos)
{
    return basic_string_rfind_subcstr(cpt_basic_string, cpv_value_string, t_pos, NPOS);
}

/**
 * Find sub value string in basic_string in a backward direction.
 */
size_t basic_string_rfind_subcstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos, size_t t_len)
{
    size_t   t_typesize = 0;
    size_t   t_stringlen = 0;
    size_t   t_cstrlen = 0;
    size_t   t_subcstrlen = 0;
    size_t   t_stringpos = 0;
    size_t   t_subcstrpos = 0;
    _byte_t* pby_string = NULL;
    bool_t   b_result = false;

    assert(cpt_basic_string != NULL);
    assert(cpv_value_string != NULL);

    t_stringlen = basic_string_length(cpt_basic_string);
    t_cstrlen = _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string);
    t_subcstrlen = t_len < t_cstrlen ? t_len : t_cstrlen;

    if(t_stringlen == 0 || t_stringlen < t_subcstrlen)
    {
        return NPOS;
    }

    t_pos = t_pos < t_stringlen ? t_pos : t_stringlen - 1;
    if(t_subcstrlen == 0)
    {
        return t_pos;
    }

    pby_string = _GET_BASIC_STRING_COREPOS(basic_string_begin(cpt_basic_string));
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);

    for(;; --t_pos)
    {
        /* char* */
        if(strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
        {
            for(t_stringpos = t_pos, t_subcstrpos = 0; t_subcstrpos < t_subcstrlen; ++t_stringpos, ++t_subcstrpos)
            {
                if(string_not_equal_cstr(
                    (string_t*)(pby_string + t_stringpos * t_typesize), *((char**)cpv_value_string + t_subcstrpos)))
                {
                    break;
                }
            }
        }
        else if(_GET_BASIC_STRING_TYPE_STYLE(cpt_basic_string) == _TYPE_C_BUILTIN)
        {
            for(t_stringpos = t_pos, t_subcstrpos = 0; t_subcstrpos < t_subcstrlen; ++t_stringpos, ++t_subcstrpos)
            {
                b_result = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    pby_string + t_stringpos * t_typesize,
                    (_byte_t*)cpv_value_string + t_subcstrpos * t_typesize,
                    &b_result);
                if(b_result)
                {
                    break;
                }
                b_result = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    (_byte_t*)cpv_value_string + t_subcstrpos * t_typesize,
                    pby_string + t_stringpos * t_typesize,
                    &b_result);
                if(b_result)
                {
                    break;
                }
            }
        }
        else
        {
            for(t_stringpos = t_pos, t_subcstrpos = 0; t_subcstrpos < t_subcstrlen; ++t_stringpos, ++t_subcstrpos)
            {
                b_result = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    pby_string + t_stringpos * t_typesize,
                    *((_byte_t**)cpv_value_string + t_subcstrpos),
                    &b_result);
                if(b_result)
                {
                    break;
                }
                b_result = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    *((_byte_t**)cpv_value_string + t_subcstrpos),
                    pby_string + t_stringpos * t_typesize,
                    &b_result);
                if(b_result)
                {
                    break;
                }
            }
        }

        if(t_subcstrpos == t_subcstrlen)
        {
            return t_pos;
        }
        if(t_pos == 0)
        {
            return NPOS;
        }
    }

    assert(false);
    return NPOS;
}

/**
 * Find basic_string for first element that matches any element of specific string.
 */
size_t basic_string_find_first_of(
    const basic_string_t* cpt_basic_string, const basic_string_t* cpt_find, size_t t_pos)
{
    basic_string_iterator_t it_string;
    basic_string_iterator_t it_find;
    bool_t                  b_less = false;
    bool_t                  b_greater = false;

    assert(cpt_basic_string != NULL);
    assert(cpt_find != NULL);
    assert(_basic_string_same_type(cpt_basic_string, cpt_find));
    assert(t_pos < basic_string_size(cpt_basic_string));

    if(basic_string_empty(cpt_find))
    {
        return t_pos;
    }

    for(it_string = iterator_next_n(basic_string_begin(cpt_basic_string), t_pos);
        !iterator_equal(it_string, basic_string_end(cpt_basic_string));
        it_string = iterator_next(it_string), ++t_pos)
    {
        for(it_find = basic_string_begin(cpt_find);
            !iterator_equal(it_find, basic_string_end(cpt_find));
            it_find = iterator_next(it_find))
        {
            b_less = b_greater = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                _GET_BASIC_STRING_COREPOS(it_string), _GET_BASIC_STRING_COREPOS(it_find), &b_less);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                _GET_BASIC_STRING_COREPOS(it_find), _GET_BASIC_STRING_COREPOS(it_string), &b_greater);
            if(!b_less && !b_greater)
            {
                return t_pos;
            }
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
    return basic_string_find_first_of_subcstr(cpt_basic_string, cpv_value_string, t_pos, NPOS);
}

/**
 * Find basic_string for first element that matches any element of specific sub value string.
 */
size_t basic_string_find_first_of_subcstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos, size_t t_len)
{
    size_t   t_typesize = 0;
    size_t   t_stringlen = 0;
    size_t   t_cstrlen = 0;
    size_t   t_subcstrlen = 0;
    size_t   t_stringpos = 0;
    size_t   t_subcstrpos = 0;
    _byte_t* pby_string = NULL;
    bool_t   b_less = false;
    bool_t   b_greater = false;

    assert(cpt_basic_string != NULL);
    assert(cpv_value_string != NULL);
    assert(t_pos < basic_string_size(cpt_basic_string));

    t_stringlen = basic_string_length(cpt_basic_string);
    t_cstrlen = _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string);
    t_subcstrlen = t_len < t_cstrlen ? t_len : t_cstrlen;

    if(t_subcstrlen == 0)
    {
        return t_pos;
    }

    pby_string = _GET_BASIC_STRING_COREPOS(basic_string_begin(cpt_basic_string));
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);

    for(; t_pos < t_stringlen; ++t_pos)
    {
        /* char* */
        if(strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
        {
            for(t_stringpos = t_pos, t_subcstrpos = 0; t_subcstrpos < t_subcstrlen; ++t_subcstrpos)
            {
                if(string_equal_cstr(
                    (string_t*)(pby_string + t_stringpos * t_typesize), *((char**)cpv_value_string + t_subcstrpos)))
                {
                    return t_stringpos;
                }
            }
        }
        else if(_GET_BASIC_STRING_TYPE_STYLE(cpt_basic_string) == _TYPE_C_BUILTIN)
        {
            for(t_stringpos = t_pos, t_subcstrpos = 0; t_subcstrpos < t_subcstrlen; ++t_subcstrpos)
            {
                b_less = b_greater = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    pby_string + t_stringpos * t_typesize,
                    (_byte_t*)cpv_value_string + t_subcstrpos * t_typesize,
                    &b_less);
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    (_byte_t*)cpv_value_string + t_subcstrpos * t_typesize,
                    pby_string + t_stringpos * t_typesize,
                    &b_greater);
                if(!b_less && !b_greater)
                {
                    return t_stringpos;
                }
            }
        }
        else
        {
            for(t_stringpos = t_pos, t_subcstrpos = 0; t_subcstrpos < t_subcstrlen; ++t_subcstrpos)
            {
                b_less = b_greater = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    pby_string + t_stringpos * t_typesize,
                    *((_byte_t**)cpv_value_string + t_subcstrpos),
                    &b_less);
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    *((_byte_t**)cpv_value_string + t_subcstrpos),
                    pby_string + t_stringpos * t_typesize,
                    &b_greater);
                if(!b_less && !b_greater)
                {
                    return t_stringpos;
                }
            }
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
    basic_string_iterator_t it_string;
    basic_string_iterator_t it_find;
    bool_t                  b_less = false;
    bool_t                  b_greater = false;

    assert(cpt_basic_string != NULL);
    assert(cpt_find != NULL);
    assert(_basic_string_same_type(cpt_basic_string, cpt_find));
    assert(t_pos < basic_string_size(cpt_basic_string));

    if(basic_string_empty(cpt_find))
    {
        return t_pos;
    }

    for(it_string = iterator_next_n(basic_string_begin(cpt_basic_string), t_pos);
        !iterator_equal(it_string, basic_string_end(cpt_basic_string));
        it_string = iterator_next(it_string), ++t_pos)
    {
        for(it_find = basic_string_begin(cpt_find);
            !iterator_equal(it_find, basic_string_end(cpt_find));
            it_find = iterator_next(it_find))
        {
            b_less = b_greater = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                _GET_BASIC_STRING_COREPOS(it_string), _GET_BASIC_STRING_COREPOS(it_find), &b_less);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                _GET_BASIC_STRING_COREPOS(it_find), _GET_BASIC_STRING_COREPOS(it_string), &b_greater);
            if(!b_less && !b_greater)
            {
                break;
            }
        }

        if(iterator_equal(it_find, basic_string_end(cpt_find)))
        {
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
    return basic_string_find_first_not_of_subcstr(cpt_basic_string, cpv_value_string, t_pos, NPOS); 
}

/**
 * Find basic_string for first element that is not matches any element of specific sub value string.
 */
size_t basic_string_find_first_not_of_subcstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos, size_t t_len)
{
    size_t   t_typesize = 0;
    size_t   t_stringlen = 0;
    size_t   t_cstrlen = 0;
    size_t   t_subcstrlen = 0;
    size_t   t_stringpos = 0;
    size_t   t_subcstrpos = 0;
    _byte_t* pby_string = NULL;
    bool_t   b_less = false;
    bool_t   b_greater = false;

    assert(cpt_basic_string != NULL);
    assert(cpv_value_string != NULL);
    assert(t_pos < basic_string_size(cpt_basic_string));

    t_stringlen = basic_string_length(cpt_basic_string);
    t_cstrlen = _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string);
    t_subcstrlen = t_len < t_cstrlen ? t_len : t_cstrlen;

    if(t_subcstrlen == 0)
    {
        return t_pos;
    }

    pby_string = _GET_BASIC_STRING_COREPOS(basic_string_begin(cpt_basic_string));
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);

    for(; t_pos < t_stringlen; ++t_pos)
    {
        /* char* */
        if(strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
        {
            for(t_stringpos = t_pos, t_subcstrpos = 0; t_subcstrpos < t_subcstrlen; ++t_subcstrpos)
            {
                if(string_equal_cstr(
                    (string_t*)(pby_string + t_stringpos * t_typesize), *((char**)cpv_value_string + t_subcstrpos)))
                {
                    break;
                }
            }
        }
        else if(_GET_BASIC_STRING_TYPE_STYLE(cpt_basic_string) == _TYPE_C_BUILTIN)
        {
            for(t_stringpos = t_pos, t_subcstrpos = 0; t_subcstrpos < t_subcstrlen; ++t_subcstrpos)
            {
                b_less = b_greater = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    pby_string + t_stringpos * t_typesize,
                    (_byte_t*)cpv_value_string + t_subcstrpos * t_typesize,
                    &b_less);
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    (_byte_t*)cpv_value_string + t_subcstrpos * t_typesize,
                    pby_string + t_stringpos * t_typesize,
                    &b_greater);
                if(!b_less && !b_greater)
                {
                    break;
                }
            }
        }
        else
        {
            for(t_stringpos = t_pos, t_subcstrpos = 0; t_subcstrpos < t_subcstrlen; ++t_subcstrpos)
            {
                b_less = b_greater = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    pby_string + t_stringpos * t_typesize, *((_byte_t**)cpv_value_string + t_subcstrpos), &b_less);
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    *((_byte_t**)cpv_value_string + t_subcstrpos), pby_string + t_stringpos * t_typesize, &b_greater);
                if(!b_less && !b_greater)
                {
                    break;
                }
            }
        }

        if(t_subcstrpos == t_subcstrlen)
        {
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
    basic_string_iterator_t it_iter;
    basic_string_iterator_t it_string;
    basic_string_iterator_t it_find;
    size_t                  t_stringlen = 0;
    size_t                  t_findlen = 0;
    bool_t                  b_less = false;
    bool_t                  b_greater = false;

    assert(cpt_basic_string != NULL);
    assert(cpt_find != NULL);
    assert(_basic_string_same_type(cpt_basic_string, cpt_find));

    t_stringlen = basic_string_size(cpt_basic_string);
    t_findlen = basic_string_size(cpt_find);

    if(t_stringlen == 0 || t_stringlen < t_findlen)
    {
        return NPOS;
    }

    t_pos = t_pos < t_stringlen ? t_pos : t_stringlen - 1;
    if(basic_string_empty(cpt_find))
    {
        return t_pos;
    }

    for(it_iter = iterator_next_n(basic_string_begin(cpt_basic_string), t_pos);
        ;
        it_iter = iterator_prev(it_iter), --t_pos)
    {
        for(it_string = it_iter, it_find = basic_string_begin(cpt_find);
            !iterator_equal(it_find, basic_string_end(cpt_find));
            it_find = iterator_next(it_find))
        {
            b_less = b_greater = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                _GET_BASIC_STRING_COREPOS(it_string), _GET_BASIC_STRING_COREPOS(it_find), &b_less);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                _GET_BASIC_STRING_COREPOS(it_find), _GET_BASIC_STRING_COREPOS(it_string), &b_greater);
            if(!b_less && !b_greater)
            {
                return t_pos;
            }
        }

        if(t_pos == 0)
        {
            return NPOS;
        }
    }

    assert(false);
    return NPOS;
}

/**
 * Find basic_string for last element that matches any element of specific value string.
 */
size_t basic_string_find_last_of_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos)
{
    return basic_string_find_last_of_subcstr(cpt_basic_string, cpv_value_string, t_pos, NPOS);
}

/**
 * Find basic_string for last element that matches any element of specific sub value string.
 */
size_t basic_string_find_last_of_subcstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos, size_t t_len)
{
    size_t   t_typesize = 0;
    size_t   t_stringlen = 0;
    size_t   t_cstrlen = 0;
    size_t   t_subcstrlen = 0;
    size_t   t_stringpos = 0;
    size_t   t_subcstrpos = 0;
    _byte_t* pby_string = NULL;
    bool_t   b_less = false;
    bool_t   b_greater = false;

    assert(cpt_basic_string != NULL);
    assert(cpv_value_string != NULL);

    t_stringlen = basic_string_length(cpt_basic_string);
    t_cstrlen = _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string);
    t_subcstrlen = t_len < t_cstrlen ? t_len : t_cstrlen;

    if(t_stringlen == 0 || t_stringlen < t_subcstrlen)
    {
        return NPOS;
    }

    t_pos = t_pos < t_stringlen ? t_pos : t_stringlen - 1;
    if(t_subcstrlen == 0)
    {
        return t_pos;
    }

    pby_string = _GET_BASIC_STRING_COREPOS(basic_string_begin(cpt_basic_string));
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);

    for(;; --t_pos)
    {
        /* char* */
        if(strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
        {
            for(t_stringpos = t_pos, t_subcstrpos = 0; t_subcstrpos < t_subcstrlen; ++t_subcstrpos)
            {
                if(string_equal_cstr(
                    (string_t*)(pby_string + t_stringpos * t_typesize), *((char**)cpv_value_string + t_subcstrpos)))
                {
                    return t_stringpos;
                }
            }
        }
        else if(_GET_BASIC_STRING_TYPE_STYLE(cpt_basic_string) == _TYPE_C_BUILTIN)
        {
            for(t_stringpos = t_pos, t_subcstrpos = 0; t_subcstrpos < t_subcstrlen; ++t_subcstrpos)
            {
                b_less = b_greater = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    pby_string + t_stringpos * t_typesize,
                    (_byte_t*)cpv_value_string + t_subcstrpos * t_typesize,
                    &b_less);
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    (_byte_t*)cpv_value_string + t_subcstrpos * t_typesize,
                    pby_string + t_stringpos * t_typesize,
                    &b_greater);
                if(!b_less && !b_greater)
                {
                    return t_stringpos;
                }
            }
        }
        else
        {
            for(t_stringpos = t_pos, t_subcstrpos = 0; t_subcstrpos < t_subcstrlen; ++t_subcstrpos)
            {
                b_less = b_greater = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    pby_string + t_stringpos * t_typesize,
                    *((_byte_t**)cpv_value_string + t_subcstrpos),
                    &b_less);
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    *((_byte_t**)cpv_value_string + t_subcstrpos),
                    pby_string + t_stringpos * t_typesize,
                    &b_greater);
                if(!b_less && !b_greater)
                {
                    return t_stringpos;
                }
            }
        }

        if(t_pos == 0)
        {
            return NPOS;
        }
    }

    assert(false);
    return NPOS;
}

/**
 * Find basic_string for last element that is not matches any element of specific string.
 */
size_t basic_string_find_last_not_of(
    const basic_string_t* cpt_basic_string, const basic_string_t* cpt_find, size_t t_pos)
{
    basic_string_iterator_t it_iter;
    basic_string_iterator_t it_string;
    basic_string_iterator_t it_find;
    size_t                  t_stringlen = 0;
    size_t                  t_findlen = 0;
    bool_t                  b_less = false;
    bool_t                  b_greater = false;

    assert(cpt_basic_string != NULL);
    assert(cpt_find != NULL);
    assert(_basic_string_same_type(cpt_basic_string, cpt_find));

    t_stringlen = basic_string_size(cpt_basic_string);
    t_findlen = basic_string_size(cpt_find);

    if(t_stringlen == 0 || t_stringlen < t_findlen)
    {
        return NPOS;
    }

    t_pos = t_pos < t_stringlen ? t_pos : t_stringlen - 1;
    if(basic_string_empty(cpt_find))
    {
        return t_pos;
    }

    for(it_iter = iterator_next_n(basic_string_begin(cpt_basic_string), t_pos);
        ;
        it_iter = iterator_prev(it_iter), --t_pos)
    {
        for(it_string = it_iter, it_find = basic_string_begin(cpt_find);
            !iterator_equal(it_find, basic_string_end(cpt_find));
            it_find = iterator_next(it_find))
        {
            b_less = b_greater = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                _GET_BASIC_STRING_COREPOS(it_string), _GET_BASIC_STRING_COREPOS(it_find), &b_less);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                _GET_BASIC_STRING_COREPOS(it_find), _GET_BASIC_STRING_COREPOS(it_string), &b_greater);
            if(!b_less && !b_greater)
            {
                break;
            }
        }

        if(iterator_equal(it_find, basic_string_end(cpt_find)))
        {
            return t_pos;
        }

        if(t_pos == 0)
        {
            return NPOS;
        }
    }

    assert(false);
    return NPOS;
}

/**
 * Find basic_string for last element that is not matches any element of specific value string.
 */
size_t basic_string_find_last_not_of_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos)
{
    return basic_string_find_last_not_of_subcstr(cpt_basic_string, cpv_value_string, t_pos, NPOS);
}

/**
 * Find basic_string for last element that is not matches any element of specific sub value string.
 */
size_t basic_string_find_last_not_of_subcstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos, size_t t_len)
{
    size_t   t_typesize = 0;
    size_t   t_stringlen = 0;
    size_t   t_cstrlen = 0;
    size_t   t_subcstrlen = 0;
    size_t   t_stringpos = 0;
    size_t   t_subcstrpos = 0;
    _byte_t* pby_string = NULL;
    bool_t   b_less = false;
    bool_t   b_greater = false;

    assert(cpt_basic_string != NULL);
    assert(cpv_value_string != NULL);

    t_stringlen = basic_string_length(cpt_basic_string);
    t_cstrlen = _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string);
    t_subcstrlen = t_len < t_cstrlen ? t_len : t_cstrlen;

    if(t_stringlen == 0 || t_stringlen < t_subcstrlen)
    {
        return NPOS;
    }

    t_pos = t_pos < t_stringlen ? t_pos : t_stringlen - 1;
    if(t_subcstrlen == 0)
    {
        return t_pos;
    }

    pby_string = _GET_BASIC_STRING_COREPOS(basic_string_begin(cpt_basic_string));
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);

    for(;; --t_pos)
    {
        /* char* */
        if(strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
        {
            for(t_stringpos = t_pos, t_subcstrpos = 0; t_subcstrpos < t_subcstrlen; ++t_subcstrpos)
            {
                if(string_equal_cstr(
                    (string_t*)(pby_string + t_stringpos * t_typesize), *((char**)cpv_value_string + t_subcstrpos)))
                {
                    break;
                }
            }
        }
        else if(_GET_BASIC_STRING_TYPE_STYLE(cpt_basic_string) == _TYPE_C_BUILTIN)
        {
            for(t_stringpos = t_pos, t_subcstrpos = 0; t_subcstrpos < t_subcstrlen; ++t_subcstrpos)
            {
                b_less = b_greater = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    pby_string + t_stringpos * t_typesize,
                    (_byte_t*)cpv_value_string + t_subcstrpos * t_typesize,
                    &b_less);
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    (_byte_t*)cpv_value_string + t_subcstrpos * t_typesize,
                    pby_string + t_stringpos * t_typesize,
                    &b_greater);
                if(!b_less && !b_greater)
                {
                    break;
                }
            }
        }
        else
        {
            for(t_stringpos = t_pos, t_subcstrpos = 0; t_subcstrpos < t_subcstrlen; ++t_subcstrpos)
            {
                b_less = b_greater = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    pby_string + t_stringpos * t_typesize,
                    *((_byte_t**)cpv_value_string + t_subcstrpos),
                    &b_less);
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    *((_byte_t**)cpv_value_string + t_subcstrpos),
                    pby_string + t_stringpos * t_typesize,
                    &b_greater);
                if(!b_less && !b_greater)
                {
                    break;
                }
            }
        }

        if(t_subcstrpos == t_subcstrlen)
        {
            return t_pos;
        }

        if(t_pos == 0)
        {
            return NPOS;
        }
    }

    assert(false);
    return NPOS;
}

/**
 * Erases the elements of basic_string.
 */
void basic_string_clear(basic_string_t* pt_basic_string)
{
    assert(pt_basic_string != NULL);

    vector_clear(&pt_basic_string->_t_vector);
}

/**
 * Swap basic_string datas.
 */
void basic_string_swap(basic_string_t* pt_first, basic_string_t* pt_second)
{
    assert(pt_first != NULL);
    assert(pt_second != NULL);

    vector_swap(&pt_first->_t_vector, &pt_second->_t_vector);
}

/**
 * Set basic_string capacity.
 */
void basic_string_reserve(basic_string_t* pt_basic_string, size_t t_reservesize)
{
    assert(pt_basic_string != NULL);

    vector_reserve(&pt_basic_string->_t_vector, t_reservesize);
}

/**
 * Assign basic_string element with an exist basic_string container.
 */
void basic_string_assign(basic_string_t* pt_dest, const basic_string_t* cpt_src)
{
    assert(pt_dest != NULL);
    assert(cpt_src != NULL);

    vector_assign(&pt_dest->_t_vector, &cpt_src->_t_vector);
}

/**
 * Assign basic_string element with an exist sub basic_string container.
 */
void basic_string_assign_substring(basic_string_t* pt_dest, const basic_string_t* cpt_src, size_t t_pos, size_t t_len)
{
    basic_string_iterator_t it_begin;
    basic_string_iterator_t it_end;

    assert(pt_dest != NULL);
    assert(cpt_src != NULL);
    assert(_basic_string_same_type(pt_dest, cpt_src));
    assert(t_pos < basic_string_size(cpt_src));

    it_begin = iterator_next_n(basic_string_begin(cpt_src), t_pos);
    if(t_len == NPOS || t_pos + t_len >= basic_string_size(cpt_src))
    {
        it_end = basic_string_end(cpt_src);
    }
    else
    {
        it_end = iterator_next_n(basic_string_begin(cpt_src), t_pos + t_len);
    }
    basic_string_assign_range(pt_dest, it_begin, it_end);
}

/**
 * Assign basic_string element with an exist value string.
 */
void basic_string_assign_cstr(basic_string_t* pt_basic_string, const void* cpv_value_string)
{
    basic_string_assign_subcstr(pt_basic_string, cpv_value_string, NPOS);
}

/**
 * Assign basic_string element with an exist sub value string.
 */
void basic_string_assign_subcstr(basic_string_t* pt_basic_string, const void* cpv_value_string, size_t t_len)
{
    size_t   t_typesize = 0;
    size_t   t_length = 0;
    size_t   i = 0;
    _byte_t* pby_value = NULL;
    bool_t   b_result = false;

    assert(pt_basic_string != NULL);
    assert(cpv_value_string != NULL);

    t_length = _basic_string_get_value_string_length(pt_basic_string, cpv_value_string);
    t_len = t_len < t_length ? t_len : t_length;

    vector_resize(&pt_basic_string->_t_vector, t_len);
    assert(vector_size(&pt_basic_string->_t_vector) == t_len);

    if(t_len > 0)
    {
        t_typesize = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
        pby_value = _GET_BASIC_STRING_COREPOS(basic_string_begin(pt_basic_string));
        assert(pby_value != NULL);

        /* char* */
        if(strncmp(_GET_BASIC_STRING_TYPE_BASENAME(pt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
        {
            for(i = 0; i < t_len; ++i)
            {
                string_assign_cstr((string_t*)(pby_value + i * t_typesize), *((char**)cpv_value_string + i));
            }
        }
        else if(_GET_BASIC_STRING_TYPE_STYLE(pt_basic_string) == _TYPE_C_BUILTIN)
        {
            for(i = 0; i < t_len; ++i)
            {
                b_result = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
                _GET_BASIC_STRING_TYPE_COPY_FUNCTION(pt_basic_string)(
                    pby_value + i * t_typesize, (_byte_t*)cpv_value_string + i * t_typesize, &b_result);
                assert(b_result);
            }
        }
        else
        {
            for(i = 0; i < t_len; ++i)
            {
                b_result = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
                _GET_BASIC_STRING_TYPE_COPY_FUNCTION(pt_basic_string)(
                    pby_value + i * t_typesize, *((_byte_t**)cpv_value_string + i), &b_result);
                assert(b_result);
            }
        }
    }
}

/**
 * Assign basic_string element with an exist basic_string container range.
 */
void basic_string_assign_range(
    basic_string_t* pt_basic_string, basic_string_iterator_t it_begin, basic_string_iterator_t it_end)
{
    assert(pt_basic_string != NULL);
    assert(_GET_BASIC_STRING_CONTAINER_TYPE(it_begin) == _BASIC_STRING_CONTAINER);
    assert(_GET_BASIC_STRING_CONTAINER_TYPE(it_end) == _BASIC_STRING_CONTAINER);

    _GET_VECTOR_CONTAINER_TYPE(it_begin) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE(it_end) = _VECTOR_CONTAINER;
    vector_assign_range(&pt_basic_string->_t_vector, it_begin, it_end);
}

/**
 * Append specific basic_string to destination basic_string.
 */
void basic_string_append(basic_string_t* pt_dest, const basic_string_t* cpt_src)
{
    assert(pt_dest != NULL);
    assert(cpt_src != NULL);
    assert(_basic_string_same_type(pt_dest, cpt_src));

    if(!basic_string_empty(cpt_src))
    {
        basic_string_append_substring(pt_dest, cpt_src, 0, NPOS);
    }
}

/**
 * Append specific sub basic_string to destination basic_string.
 */
void basic_string_append_substring(basic_string_t* pt_dest, const basic_string_t* cpt_src, size_t t_pos, size_t t_len)
{
    basic_string_iterator_t it_begin;
    basic_string_iterator_t it_end;

    assert(pt_dest != NULL);
    assert(cpt_src != NULL);
    assert(_basic_string_same_type(pt_dest, cpt_src));
    assert(t_pos < basic_string_size(cpt_src));

    it_begin = iterator_next_n(basic_string_begin(cpt_src), t_pos);
    if(t_len == NPOS || t_pos + t_len >= basic_string_size(cpt_src))
    {
        it_end = basic_string_end(cpt_src);
    }
    else
    {
        it_end = iterator_next_n(basic_string_begin(cpt_src), t_pos + t_len);
    }

    basic_string_append_range(pt_dest, it_begin, it_end);
}

/**
 * Append specific value string to destination basic_string.
 */
void basic_string_append_cstr(basic_string_t* pt_basic_string, const void* cpv_value_string)
{
    basic_string_append_subcstr(pt_basic_string, cpv_value_string, NPOS);
}

/**
 * Append specific sub value string to destination basic_string.
 */
void basic_string_append_subcstr(basic_string_t* pt_basic_string, const void* cpv_value_string, size_t t_len)
{
    size_t   t_typesize = 0;
    size_t   t_cstrlen = 0;
    size_t   t_stringlen = 0;
    size_t   i = 0;
    _byte_t* pby_value = NULL;
    bool_t   b_result = false;

    assert(pt_basic_string != NULL);
    assert(cpv_value_string != NULL);

    t_stringlen = basic_string_length(pt_basic_string);
    t_cstrlen = _basic_string_get_value_string_length(pt_basic_string, cpv_value_string);
    t_len = t_len < t_cstrlen ? t_len : t_cstrlen;

    if(t_len > 0)
    {
        t_typesize = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
        vector_resize(&pt_basic_string->_t_vector, t_stringlen + t_len);
        pby_value = _GET_BASIC_STRING_COREPOS(iterator_next_n(basic_string_begin(pt_basic_string), t_stringlen));
        assert(pby_value != NULL);

        /* char* */
        if(strncmp(_GET_BASIC_STRING_TYPE_BASENAME(pt_basic_string), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
        {
            for(i = 0; i < t_len; ++i)
            {
                string_assign_cstr((string_t*)(pby_value + i * t_typesize), *((char**)cpv_value_string + i));
            }
        }
        else if(_GET_BASIC_STRING_TYPE_STYLE(pt_basic_string) == _TYPE_C_BUILTIN)
        {
            for(i = 0; i < t_len; ++i)
            {
                b_result = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
                _GET_BASIC_STRING_TYPE_COPY_FUNCTION(pt_basic_string)(
                    pby_value + i * t_typesize, (_byte_t*)cpv_value_string + i * t_typesize, &b_result);
                assert(b_result);
            }
        }
        else
        {
            for(i = 0; i < t_len; ++i)
            {
                b_result = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
                _GET_BASIC_STRING_TYPE_COPY_FUNCTION(pt_basic_string)(
                    pby_value + i * t_typesize, *((_byte_t**)cpv_value_string + i), &b_result);
                assert(b_result);
            }
        }
    }
}

/**
 * Append specific range to destination basic_string.
 */
void basic_string_append_range(
    basic_string_t* pt_basic_string, basic_string_iterator_t it_begin, basic_string_iterator_t it_end)
{
    assert(pt_basic_string != NULL);
    assert(_GET_BASIC_STRING_CONTAINER_TYPE(it_begin) == _BASIC_STRING_CONTAINER);
    assert(_GET_BASIC_STRING_CONTAINER_TYPE(it_end) == _BASIC_STRING_CONTAINER);

    _GET_VECTOR_CONTAINER_TYPE(it_begin) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE(it_end) = _VECTOR_CONTAINER;
    vector_insert_range(&pt_basic_string->_t_vector, vector_end(&pt_basic_string->_t_vector), it_begin, it_end);
}

/**
 * Insert specific basic_string into the destination basic_string at specific position.
 */
void basic_string_insert_string(basic_string_t* pt_basic_string, size_t t_pos, const basic_string_t* cpt_insert)
{
    assert(pt_basic_string != NULL);
    assert(cpt_insert != NULL);
    assert(pt_basic_string != cpt_insert);
    assert(_basic_string_same_type(pt_basic_string, cpt_insert));
    assert(t_pos < basic_string_size(pt_basic_string));

    if(!basic_string_empty(cpt_insert))
    {
        basic_string_insert_substring(pt_basic_string, t_pos, cpt_insert, 0, NPOS);
    }
}

/**
 * Insert specific sub basic_string into the destination basic_string at specific position.
 */
void basic_string_insert_substring(
    basic_string_t* pt_basic_string, size_t t_pos, const basic_string_t* cpt_insert, size_t t_startpos, size_t t_len)
{
    basic_string_iterator_t it_pos;
    basic_string_iterator_t it_begin;
    basic_string_iterator_t it_end;

    assert(pt_basic_string != NULL);
    assert(cpt_insert != NULL);
    assert(pt_basic_string != cpt_insert);
    assert(_basic_string_same_type(pt_basic_string, cpt_insert));
    assert(t_pos < basic_string_size(pt_basic_string));
    assert(t_startpos < basic_string_size(cpt_insert));

    it_pos = iterator_next_n(basic_string_begin(pt_basic_string), t_pos);
    it_begin = iterator_next_n(basic_string_begin(cpt_insert), t_startpos);
    if(t_len == NPOS || t_startpos + t_len >= basic_string_size(cpt_insert))
    {
        it_end = basic_string_end(cpt_insert);
    }
    else
    {
        it_end = iterator_next_n(basic_string_begin(cpt_insert), t_startpos + t_len);
    }

    basic_string_insert_range(pt_basic_string, it_pos, it_begin, it_end);
}

void basic_string_insert_cstr(
    basic_string_t* pt_basic_string, size_t t_pos, const void* cpv_value_string)
{
    basic_string_insert_subcstr(pt_basic_string, t_pos, cpv_value_string, NPOS);
}

void basic_string_insert_subcstr(
    basic_string_t* pt_basic_string, size_t t_pos,
    const void* cpv_value_string, size_t t_len)
{
    basic_string_t* pt_string;

    assert(pt_basic_string != NULL && cpv_value_string != NULL);

    pt_string = _create_basic_string(_GET_BASIC_STRING_TYPE_NAME(pt_basic_string));
    basic_string_init_subcstr(pt_string, cpv_value_string, t_len);
    basic_string_insert_string(pt_basic_string, t_pos, pt_string);
    basic_string_destroy(pt_string);
}

void basic_string_insert_range(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_pos,
    basic_string_iterator_t t_begin, basic_string_iterator_t t_end)
{
    assert(
        _GET_BASIC_STRING_CONTAINER(t_begin) != pt_basic_string &&
        _GET_BASIC_STRING_CONTAINER(t_end) != pt_basic_string &&
        _GET_BASIC_STRING_CONTAINER(t_pos) == pt_basic_string);
    assert(
        _basic_string_same_type(pt_basic_string, _GET_BASIC_STRING_CONTAINER(t_begin)) &&
        _basic_string_same_type(pt_basic_string, _GET_BASIC_STRING_CONTAINER(t_end)));

    _GET_VECTOR_CONTAINER_TYPE(t_begin) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE(t_end) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE(t_pos) = _VECTOR_CONTAINER;

    vector_insert_range(&pt_basic_string->_t_vector, t_pos, t_begin, t_end);
}



/* erase */
basic_string_iterator_t basic_string_erase(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_pos)
{
    basic_string_iterator_t t_iterator;

    assert(_iterator_belong_to_basic_string(pt_basic_string, t_pos));
    assert(!iterator_equal(t_pos, basic_string_end(pt_basic_string)));

    _GET_VECTOR_CONTAINER_TYPE(t_pos) = _VECTOR_CONTAINER;

    t_iterator = vector_erase(&pt_basic_string->_t_vector, t_pos);
    _GET_BASIC_STRING_CONTAINER_TYPE(t_iterator) = _BASIC_STRING_CONTAINER;

    return t_iterator;
}

basic_string_iterator_t basic_string_erase_range(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin, basic_string_iterator_t t_end)
{
    basic_string_iterator_t t_iterator;

    assert(_iterator_belong_to_basic_string(pt_basic_string, t_begin) &&
           _iterator_belong_to_basic_string(pt_basic_string, t_end));

    _GET_VECTOR_CONTAINER_TYPE(t_begin) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE(t_end) = _VECTOR_CONTAINER;

    t_iterator = vector_erase_range(&pt_basic_string->_t_vector, t_begin, t_end);
    _GET_BASIC_STRING_CONTAINER_TYPE(t_iterator) = _BASIC_STRING_CONTAINER;

    return t_iterator;
}

void basic_string_erase_substring(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_len)
{
    basic_string_iterator_t t_begin = basic_string_begin(pt_basic_string);
    basic_string_iterator_t t_end   = basic_string_begin(pt_basic_string);

    assert(t_pos <= basic_string_size(pt_basic_string));

    if(t_pos != 0)
    {
        t_begin = iterator_next_n(t_begin, t_pos);
    }
    if(t_len == NPOS || t_pos + t_len >= basic_string_size(pt_basic_string))
    {
        t_end = basic_string_end(pt_basic_string);
    }
    else
    {
        t_end = iterator_next_n(t_end, t_pos + t_len);
    }

    basic_string_erase_range(pt_basic_string, t_begin, t_end);
}

/* replace */
void basic_string_replace(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_len,
    const basic_string_t* cpt_basic_string_replace)
{
    basic_string_iterator_t t_begin = basic_string_begin(pt_basic_string);
    basic_string_iterator_t t_end   = basic_string_begin(pt_basic_string);

    assert(t_pos <= basic_string_size(pt_basic_string));

    t_begin = iterator_next_n(t_begin, t_pos);
    if(t_len == NPOS || t_pos + t_len >= basic_string_size(pt_basic_string))
    {
        t_end = basic_string_end(pt_basic_string);
    }
    else
    {
        t_end = iterator_next_n(t_end, t_pos + t_len);
    }

    basic_string_range_replace(
        pt_basic_string, t_begin, t_end, cpt_basic_string_replace);
}

void basic_string_replace_substring(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_len,
    const basic_string_t* cpt_basic_string_replace, size_t t_position, size_t t_length)
{
    basic_string_iterator_t t_begin = basic_string_begin(pt_basic_string);
    basic_string_iterator_t t_end   = basic_string_begin(pt_basic_string);

    assert(t_pos <= basic_string_size(pt_basic_string));

    t_begin = iterator_next_n(t_begin, t_pos);
    if(t_len == NPOS || t_pos + t_len >= basic_string_size(pt_basic_string))
    {
        t_end = basic_string_end(pt_basic_string);
    }
    else
    {
        t_end = iterator_next_n(t_end, t_pos + t_len);
    }

    basic_string_range_replace_substring(
        pt_basic_string, t_begin, t_end, cpt_basic_string_replace, t_position, t_length);
}

void basic_string_replace_cstr(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_len,
    const void* cpv_value_string)
{
    basic_string_iterator_t t_begin = basic_string_begin(pt_basic_string);
    basic_string_iterator_t t_end   = basic_string_begin(pt_basic_string);

    assert(t_pos <= basic_string_size(pt_basic_string));

    t_begin = iterator_next_n(t_begin, t_pos);
    if(t_len == NPOS || t_pos + t_len >= basic_string_size(pt_basic_string))
    {
        t_end = basic_string_end(pt_basic_string);
    }
    else
    {
        t_end = iterator_next_n(t_end, t_pos + t_len);
    }

    basic_string_range_replace_cstr(
        pt_basic_string, t_begin, t_end, cpv_value_string);
}

void basic_string_replace_subcstr(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_len,
    const void* cpv_value_string, size_t t_length)
{
    basic_string_iterator_t t_begin = basic_string_begin(pt_basic_string);
    basic_string_iterator_t t_end   = basic_string_begin(pt_basic_string);

    assert(t_pos <= basic_string_size(pt_basic_string));

    t_begin = iterator_next_n(t_begin, t_pos);
    if(t_len == NPOS || t_pos + t_len >= basic_string_size(pt_basic_string))
    {
        t_end = basic_string_end(pt_basic_string);
    }
    else
    {
        t_end = iterator_next_n(t_end, t_pos + t_len);
    }

    basic_string_range_replace_subcstr(
        pt_basic_string, t_begin, t_end, cpv_value_string, t_length);
}



void basic_string_range_replace(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end, const basic_string_t* cpt_basic_string_replace)
{
    basic_string_iterator_t t_iterator = 
        basic_string_erase_range(pt_basic_string, t_begin, t_end);
    basic_string_insert_string(
        pt_basic_string,
        iterator_distance(basic_string_begin(pt_basic_string), t_iterator),
        cpt_basic_string_replace);
}

void basic_string_range_replace_substring(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin, basic_string_iterator_t t_end,
    const basic_string_t* cpt_basic_string_replace, size_t t_pos, size_t t_len)
{
    basic_string_iterator_t t_iterator = 
        basic_string_erase_range(pt_basic_string, t_begin, t_end);
    basic_string_insert_substring(
        pt_basic_string,
        iterator_distance(basic_string_begin(pt_basic_string), t_iterator),
        cpt_basic_string_replace, t_pos, t_len);
}

void basic_string_range_replace_cstr(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end, const void* cpv_value_string)
{
    basic_string_iterator_t t_iterator = 
        basic_string_erase_range(pt_basic_string, t_begin, t_end);
    basic_string_insert_cstr(
        pt_basic_string,
        iterator_distance(basic_string_begin(pt_basic_string), t_iterator),
        cpv_value_string);
}

void basic_string_range_replace_subcstr(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end, const void* cpv_value_string, size_t t_len)
{
    basic_string_iterator_t t_iterator = 
        basic_string_erase_range(pt_basic_string, t_begin, t_end);
    basic_string_insert_subcstr(
        pt_basic_string,
        iterator_distance(basic_string_begin(pt_basic_string), t_iterator),
        cpv_value_string, t_len);
}



void basic_string_replace_range(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin, basic_string_iterator_t t_end,
    basic_string_iterator_t t_first, basic_string_iterator_t t_last)
{
    basic_string_iterator_t t_iterator = 
        basic_string_erase_range(pt_basic_string, t_begin, t_end);
    basic_string_insert_range(pt_basic_string, t_iterator, t_first, t_last);
}


/** local function implementation section **/

/** eof **/

