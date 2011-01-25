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

void basic_string_init_copy(
    basic_string_t* pt_basic_string, const basic_string_t* cpt_basic_string_src)
{
    assert(pt_basic_string != NULL && cpt_basic_string_src != NULL);

    vector_init_copy(&pt_basic_string->_t_vector, &cpt_basic_string_src->_t_vector);
}

void basic_string_init_copy_range(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin, basic_string_iterator_t t_end)
{
    assert(pt_basic_string != NULL);
    assert(_GET_BASIC_STRING_CONTAINER(t_begin) != pt_basic_string &&
           _GET_BASIC_STRING_CONTAINER(t_end) != pt_basic_string);

    _GET_VECTOR_CONTAINER_TYPE(t_begin) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE(t_end) = _VECTOR_CONTAINER;

    vector_init_copy_range(&pt_basic_string->_t_vector, t_begin, t_end);
}

void basic_string_init_copy_substring(
    basic_string_t* pt_basic_string,
    const basic_string_t* cpt_basic_string_src, size_t t_pos, size_t t_len)
{
    basic_string_iterator_t t_begin;
    basic_string_iterator_t t_end;

    assert(pt_basic_string != NULL && cpt_basic_string_src != NULL);
    assert(t_pos < basic_string_size(cpt_basic_string_src));

    t_begin = iterator_next_n(basic_string_begin(cpt_basic_string_src), t_pos);

    if(t_len == NPOS || t_len + t_pos >= basic_string_size(cpt_basic_string_src))
    {
        t_end = basic_string_end(cpt_basic_string_src);
    }
    else
    {
        t_end = iterator_next_n(basic_string_begin(cpt_basic_string_src), t_pos + t_len);
    }

    _GET_VECTOR_CONTAINER_TYPE(t_begin) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE(t_end) = _VECTOR_CONTAINER;

    vector_init_copy_range(&pt_basic_string->_t_vector, t_begin, t_end);
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


void basic_string_destroy(basic_string_t* pt_basic_string)
{
    assert(pt_basic_string != NULL);

    vector_destroy(&pt_basic_string->_t_vector);
}

/* string and c-string */
const void* basic_string_c_str(const basic_string_t* cpt_basic_string)
{
    if(basic_string_empty(cpt_basic_string))
    {
        return NULL;
    }
    else
    {
        return basic_string_at(cpt_basic_string, 0);
    }
}

const void* basic_string_data(const basic_string_t* cpt_basic_string)
{
    return vector_at(&cpt_basic_string->_t_vector, 0);
}

size_t basic_string_copy(
    const basic_string_t* cpt_basic_string,
    void* pv_buffer, size_t t_copysize, size_t t_copypos)
{
    void*  pv_copypos = NULL;
    size_t t_size = 0;
    size_t t_index = 0;
    bool_t t_result = false;

    assert(cpt_basic_string != NULL && pv_buffer != NULL);

    t_size = basic_string_size(cpt_basic_string);
    assert(t_size > t_copypos);
    t_size = (t_size - t_copypos) < t_copysize ? (t_size - t_copypos) : t_copysize;

    /* the elements in buffer must be initialized */
    pv_copypos = basic_string_at(cpt_basic_string, t_copypos);
    for(t_index = 0; t_index < t_size; ++t_index)
    {
        t_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
        _GET_BASIC_STRING_TYPE_COPY_FUNCTION(cpt_basic_string)(
            (char*)pv_buffer + t_index * _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string),
            (char*)pv_copypos + t_index * _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string),
            &t_result);
        assert(t_result);
    }

    return t_size;
}

/* size and capacity */
size_t basic_string_size(const basic_string_t* cpt_basic_string)
{
    assert(cpt_basic_string != NULL);

    return vector_size(&cpt_basic_string->_t_vector);
}

size_t basic_string_length(const basic_string_t* cpt_basic_string)
{
    return basic_string_size(cpt_basic_string);
}

bool_t basic_string_empty(const basic_string_t* cpt_basic_string)
{
    return basic_string_size(cpt_basic_string) == 0 ? true : false;
}

size_t basic_string_max_size(const basic_string_t* cpt_basic_string)
{
    assert(cpt_basic_string != NULL);

    return (size_t)(-1) / _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
}

size_t basic_string_capacity(const basic_string_t* cpt_basic_string)
{
    assert(cpt_basic_string != NULL);

    return vector_capacity(&cpt_basic_string->_t_vector);
}

/* element access */
void* basic_string_at(const basic_string_t* cpt_basic_string, size_t t_pos)
{
    assert(cpt_basic_string != NULL);
    assert(t_pos < basic_string_size(cpt_basic_string));

    return vector_at(&cpt_basic_string->_t_vector, t_pos);
}

/* comparisons */
bool_t basic_string_equal(
    const basic_string_t* cpt_basic_stringfirst, const basic_string_t* cpt_basic_stringsecond)
{
    assert(cpt_basic_stringfirst != NULL && cpt_basic_stringsecond != NULL);

    return vector_equal(
        &cpt_basic_stringfirst->_t_vector, &cpt_basic_stringsecond->_t_vector);
}

bool_t basic_string_not_equal(
    const basic_string_t* cpt_basic_stringfirst, const basic_string_t* cpt_basic_stringsecond)
{
    assert(cpt_basic_stringfirst != NULL && cpt_basic_stringsecond != NULL);

    return vector_not_equal(
        &cpt_basic_stringfirst->_t_vector, &cpt_basic_stringsecond->_t_vector);
}

bool_t basic_string_less(
    const basic_string_t* cpt_basic_stringfirst, const basic_string_t* cpt_basic_stringsecond)
{
    assert(cpt_basic_stringfirst != NULL && cpt_basic_stringsecond != NULL);

    return vector_less(
        &cpt_basic_stringfirst->_t_vector, &cpt_basic_stringsecond->_t_vector);
}

bool_t basic_string_less_equal(
    const basic_string_t* cpt_basic_stringfirst, const basic_string_t* cpt_basic_stringsecond)
{
    assert(cpt_basic_stringfirst != NULL && cpt_basic_stringsecond != NULL);

    return vector_less_equal(
        &cpt_basic_stringfirst->_t_vector, &cpt_basic_stringsecond->_t_vector);
}

bool_t basic_string_greater(
    const basic_string_t* cpt_basic_stringfirst, const basic_string_t* cpt_basic_stringsecond)
{
    assert(cpt_basic_stringfirst != NULL && cpt_basic_stringsecond != NULL);

    return vector_greater(
        &cpt_basic_stringfirst->_t_vector, &cpt_basic_stringsecond->_t_vector);
}

bool_t basic_string_greater_equal(
    const basic_string_t* cpt_basic_stringfirst, const basic_string_t* cpt_basic_stringsecond)
{
    assert(cpt_basic_stringfirst != NULL && cpt_basic_stringsecond != NULL);

    return vector_greater_equal(
        &cpt_basic_stringfirst->_t_vector, &cpt_basic_stringsecond->_t_vector);
}

bool_t basic_string_equal_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string)
{
    return basic_string_compare_cstr(cpt_basic_string, cpv_value_string) == 0 ? true : false;
}

bool_t basic_string_not_equal_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string)
{
    return basic_string_compare_cstr(cpt_basic_string, cpv_value_string) != 0 ? true : false;
}

bool_t basic_string_less_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string)
{
    return basic_string_compare_cstr(cpt_basic_string, cpv_value_string) < 0 ? true : false;
}

bool_t basic_string_less_equal_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string)
{
    return basic_string_compare_cstr(cpt_basic_string, cpv_value_string) <= 0 ? true : false;
}

bool_t basic_string_greater_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string)
{
    return basic_string_compare_cstr(cpt_basic_string, cpv_value_string) > 0 ? true : false;
}

bool_t basic_string_greater_equal_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string)
{
    return basic_string_compare_cstr(cpt_basic_string, cpv_value_string) >= 0 ? true : false;
}

int basic_string_compare(
    const basic_string_t* cpt_basic_stringfirst, const basic_string_t* cpt_basic_stringsecond)
{
    assert(_basic_string_same_type(cpt_basic_stringfirst, cpt_basic_stringsecond));

    return basic_string_compare_substring_string(
        cpt_basic_stringfirst, 0, NPOS, cpt_basic_stringsecond);
}

int basic_string_compare_substring_string(
    const basic_string_t* cpt_basic_stringfirst, size_t t_firstpos, size_t t_firstlen,
    const basic_string_t* cpt_basic_stringsecond)
{
    assert(_basic_string_same_type(cpt_basic_stringfirst, cpt_basic_stringsecond));

    return basic_string_compare_substring_substring(
        cpt_basic_stringfirst, t_firstpos, t_firstlen, cpt_basic_stringsecond, 0, NPOS);
}

int basic_string_compare_substring_substring(
    const basic_string_t* cpt_basic_stringfirst, size_t t_firstpos, size_t t_firstlen,
    const basic_string_t* cpt_basic_stringsecond, size_t t_secondpos, size_t t_secondlen)
{
    assert(_basic_string_same_type(cpt_basic_stringfirst, cpt_basic_stringsecond));
    assert(t_secondpos < basic_string_size(cpt_basic_stringsecond));

    return basic_string_compare_substring_subcstr(
        cpt_basic_stringfirst, t_firstpos, t_firstlen,
        basic_string_at(cpt_basic_stringsecond, t_secondpos), t_secondlen);
}

int basic_string_compare_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string)
{
    return basic_string_compare_substring_subcstr(
        cpt_basic_string, 0, NPOS, cpv_value_string, NPOS);
}

int basic_string_compare_substring_cstr(
    const basic_string_t* cpt_basic_string, size_t t_stringpos, size_t t_stringlen,
    const void* cpv_value_string)
{
    return basic_string_compare_substring_subcstr(
        cpt_basic_string, t_stringpos, t_stringlen, cpv_value_string, NPOS);
}

int basic_string_compare_substring_subcstr(
    const basic_string_t* cpt_basic_string, size_t t_stringpos, size_t t_stringlen,
    const void* cpv_value_string, size_t t_valuestringlen)
{
    size_t t_cmplen = 0;
    size_t t_index = 0;
    char*  pc_string = NULL;
    char*  pc_value = NULL;
    size_t t_stringlentmp = 0;
    size_t t_valuestringlentmp = 0;
    bool_t t_result = false;

    assert(cpt_basic_string != NULL && cpv_value_string != NULL);
    assert(t_stringpos <= basic_string_size(cpt_basic_string));

    /* get actual string length and value string length */
    t_stringlentmp = basic_string_size(cpt_basic_string) - t_stringpos;
    t_valuestringlentmp = _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string);
    t_stringlen = t_stringlen < t_stringlentmp ? t_stringlen : t_stringlentmp;
    t_valuestringlen = t_valuestringlen < t_valuestringlentmp ?
                       t_valuestringlen : t_valuestringlentmp;
    t_cmplen = t_stringlen < t_valuestringlen ? t_stringlen : t_valuestringlen;

    if(!basic_string_empty(cpt_basic_string))
    {
        pc_string = (char*)basic_string_at(cpt_basic_string, t_stringpos);
    }
    pc_value = (char*)cpv_value_string;
    assert(pc_value != NULL);

    for(t_index = 0; t_index < t_cmplen; ++t_index)
    {
        t_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pc_string, pc_value, &t_result);
        if(t_result)
        {
            return -1;
        }
        t_result = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pc_value, pc_string, &t_result);
        if(t_result)
        {
            return 1;
        }

        pc_string += _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
        pc_value += _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    }

    return t_stringlen < t_valuestringlen ? -1 : (t_stringlen > t_valuestringlen ? 1 : 0);
}

/* substring and concatenation */
basic_string_t* basic_string_substr(
    const basic_string_t* cpt_basic_string, size_t t_pos, size_t t_len)
{
    basic_string_t* pt_substr = NULL;

    assert(cpt_basic_string != NULL);
    assert(t_pos < basic_string_size(cpt_basic_string));

    pt_substr = _create_basic_string(_GET_BASIC_STRING_TYPE_NAME(cpt_basic_string));
    basic_string_init_subcstr(pt_substr, basic_string_at(cpt_basic_string, t_pos), t_len);

    return pt_substr;
}

void basic_string_connect(
    basic_string_t* pt_basic_string, const basic_string_t* cpt_basic_string_src)
{
    size_t t_destlen = 0;
    size_t t_srclen = 0;
    size_t t_index = 0;
    char*  pc_dest = NULL;
    char*  pc_src = NULL;
    bool_t t_result = false;

    assert(_basic_string_same_type(pt_basic_string, cpt_basic_string_src));

    t_destlen = basic_string_size(pt_basic_string);
    t_srclen = basic_string_size(cpt_basic_string_src);

    if(t_srclen > 0)
    {
        vector_resize(&pt_basic_string->_t_vector, t_destlen + t_srclen);

        pc_dest = (char*)vector_at(&pt_basic_string->_t_vector, t_destlen);
        pc_src = (char*)vector_at(&cpt_basic_string_src->_t_vector, 0);
        assert(pc_dest != NULL && pc_src != NULL);

        for(t_index = 0; t_index < t_srclen; ++t_index)
        {
            t_result = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
            _GET_BASIC_STRING_TYPE_COPY_FUNCTION(pt_basic_string)(pc_dest, pc_src, &t_result);
            pc_dest += _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
            pc_src += _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string_src);
        }
    }
}

void basic_string_connect_cstr(
    basic_string_t* pt_basic_string, const void* cpv_value_string)
{
    size_t t_destlen = 0;
    size_t t_srclen = 0;
    size_t t_index = 0;
    char*  pc_dest = NULL;
    char*  pc_src = NULL;
    bool_t t_result = false;

    assert(pt_basic_string != NULL && cpv_value_string != NULL);

    t_destlen = basic_string_size(pt_basic_string);
    t_srclen = _basic_string_get_value_string_length(pt_basic_string, cpv_value_string);

    if(t_srclen > 0)
    {
        vector_resize(&pt_basic_string->_t_vector, t_destlen + t_srclen);

        pc_dest = (char*)vector_at(&pt_basic_string->_t_vector, t_destlen);
        pc_src = (char*)cpv_value_string;
        assert(pc_dest != NULL && pc_src != NULL);

        for(t_index = 0; t_index < t_srclen; ++t_index)
        {
            t_result = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
            _GET_BASIC_STRING_TYPE_COPY_FUNCTION(pt_basic_string)(pc_dest, pc_src, &t_result);
            pc_dest += _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
            pc_src += _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
        }
    }
}



/* iterator support */
basic_string_iterator_t basic_string_begin(const basic_string_t* cpt_basic_string)
{
    basic_string_iterator_t t_newiterator;

    assert(cpt_basic_string != NULL);

    t_newiterator = vector_begin(&cpt_basic_string->_t_vector);
    _GET_BASIC_STRING_CONTAINER_TYPE(t_newiterator) = _BASIC_STRING_CONTAINER;

    return t_newiterator;
}

basic_string_iterator_t basic_string_end(const basic_string_t* cpt_basic_string)
{
    basic_string_iterator_t t_newiterator;

    assert(cpt_basic_string != NULL);

    t_newiterator = vector_end(&cpt_basic_string->_t_vector);
    _GET_BASIC_STRING_CONTAINER_TYPE(t_newiterator) = _BASIC_STRING_CONTAINER;

    return t_newiterator;
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

/* find function series */
size_t basic_string_find(
    const basic_string_t* cpt_basic_string,
    const basic_string_t* cpt_basic_string_find, size_t t_pos)
{
    if(basic_string_empty(cpt_basic_string_find))
    {
        return basic_string_find_cstr(cpt_basic_string, "", t_pos);
    }
    else
    {
        return basic_string_find_cstr(
            cpt_basic_string, basic_string_at(cpt_basic_string_find, 0), t_pos);
    }
}

size_t basic_string_find_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos)
{
    return basic_string_find_subcstr(cpt_basic_string, cpv_value_string, t_pos,
        _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string));
}

size_t basic_string_find_subcstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_value_string, size_t t_pos, size_t t_len)
{
    size_t t_typesize = 0;
    size_t t_stringlen = 0;
    size_t t_cstrlen = 0;
    size_t t_startpos = 0;
    size_t t_endpos = 0;
    char*  pc_string = NULL;
    char*  pc_cstr = NULL;
    bool_t t_less = false;
    bool_t t_greater = false;

    assert(cpt_basic_string != NULL && cpv_value_string != NULL);

    t_stringlen = basic_string_length(cpt_basic_string);
    t_cstrlen = _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string);

    /* find position is beyond the range of cpt_basic_string */
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    if(t_len > t_cstrlen ||
       t_pos > basic_string_size(cpt_basic_string) ||
       t_pos + t_len * t_typesize > basic_string_size(cpt_basic_string))
    {
        return NPOS;
    }
    /* value string is empty */
    if(t_len == 0)
    {
        return t_pos;
    }

    pc_string = (char*)basic_string_at(cpt_basic_string, 0);
    pc_cstr = (char*)cpv_value_string;
    t_startpos = t_pos;
    while(t_startpos != t_stringlen)
    {
        t_less = t_greater = t_typesize;
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pc_string + t_startpos * t_typesize, pc_cstr, &t_less);
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pc_cstr, pc_string + t_startpos * t_typesize, &t_greater);
        if(!t_less && !t_greater)
        {
            t_endpos = 0;
            while(t_endpos + t_startpos != t_stringlen && t_endpos != t_len)
            {
                t_less = t_greater = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    pc_string + (t_endpos + t_startpos) * t_typesize,
                    pc_cstr + t_endpos * t_typesize, &t_less);
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    pc_cstr + t_endpos * t_typesize,
                    pc_string + (t_endpos + t_startpos) * t_typesize, &t_greater);
                if(!t_less && !t_greater)
                {
                    t_endpos++;
                }
                else
                {
                    break;
                }
            }

            if(t_endpos == t_len)
            {
                return t_startpos;
            }
            else if(t_endpos + t_startpos == t_stringlen)
            {
                return NPOS;
            }
        }

        t_startpos++;
    }

    return NPOS;
}



size_t basic_string_rfind(
    const basic_string_t* cpt_basic_string,
    const basic_string_t* cpt_basic_string_find, size_t t_pos)
{
    if(basic_string_empty(cpt_basic_string_find))
    {
        return basic_string_rfind_cstr(cpt_basic_string, "", t_pos);
    }
    else
    {
        return basic_string_rfind_cstr(
            cpt_basic_string, basic_string_at(cpt_basic_string_find, 0), t_pos);
    }
}

size_t basic_string_rfind_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos)
{
    return basic_string_rfind_subcstr(cpt_basic_string, cpv_value_string, t_pos,
        _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string));
}

size_t basic_string_rfind_subcstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_value_string, size_t t_pos, size_t t_len)
{
    size_t t_typesize = 0;
    size_t t_stringlen = 0;
    size_t t_cstrlen = 0;
    size_t t_startpos = 0;
    size_t t_endpos = 0;
    char*  pc_string = NULL;
    char*  pc_cstr = NULL;
    bool_t t_less = false;
    bool_t t_greater = false;

    assert(cpt_basic_string != NULL && cpv_value_string != NULL);

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    t_stringlen = basic_string_length(cpt_basic_string);
    t_cstrlen = _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string);

    if(t_pos > t_stringlen)
    {
        t_pos = t_stringlen;
    }

    /* value string is empty */
    if(t_len > t_cstrlen)
    {
        return NPOS;
    }
    if(t_len == 0)
    {
        return t_pos;
    }
    /* find position is beyond the range of cpt_basic_string */
    if(basic_string_empty(cpt_basic_string))
    {
        return NPOS;
    }

    pc_string = (char*)basic_string_at(cpt_basic_string, 0);
    pc_cstr = (char*)cpv_value_string;
    t_startpos = t_pos == t_stringlen ? t_pos - 1 : t_pos;
    for(;;)
    {
        t_less = t_greater = t_typesize;
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pc_string + t_startpos * t_typesize, pc_cstr, &t_less);
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pc_cstr, pc_string + t_startpos * t_typesize, &t_greater);
        if(!t_less && !t_greater)
        {
            t_endpos = 0;
            while(t_endpos + t_startpos != t_stringlen && t_endpos != t_len)
            {
                t_less = t_greater = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    pc_string + (t_endpos + t_startpos) * t_typesize,
                    pc_cstr + t_endpos * t_typesize, &t_less);
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    pc_cstr + t_endpos * t_typesize,
                    pc_string + (t_endpos + t_startpos) * t_typesize, &t_greater);
                if(!t_less && !t_greater)
                {
                    t_endpos++;
                }
                else
                {
                    break;
                }
            }

            if(t_endpos == t_len)
            {
                return t_startpos;
            }
        }

        if(t_startpos > 0)
        {
            t_startpos--;
        }
        else
        {
            break;
        }
    }

    return NPOS;
}


size_t basic_string_find_first_of(
    const basic_string_t* cpt_basic_string,
    const basic_string_t* cpt_basic_string_find, size_t t_pos)
{
    if(basic_string_empty(cpt_basic_string_find))
    {
        return basic_string_find_first_of_cstr(cpt_basic_string, "", t_pos);
    }
    else
    {
        return basic_string_find_first_of_cstr(
            cpt_basic_string, basic_string_at(cpt_basic_string_find, 0), t_pos);
    }
}

size_t basic_string_find_first_of_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos)
{
    return basic_string_find_first_of_subcstr(cpt_basic_string, cpv_value_string, t_pos,
        _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string));
}

size_t basic_string_find_first_of_subcstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_value_string, size_t t_pos, size_t t_len)
{
    size_t t_typesize = 0;
    size_t t_stringlen = 0;
    size_t t_cstrlen = 0;
    size_t t_startpos = 0;
    size_t t_endpos = 0;
    char*  pc_string = NULL;
    char*  pc_cstr = NULL;
    bool_t t_less = false;
    bool_t t_greater = false;

    assert(cpt_basic_string != NULL && cpv_value_string != NULL);

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    t_stringlen = basic_string_length(cpt_basic_string);
    t_cstrlen = _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string);

    /* find position is beyond the range of cpt_basic_string */
    if(basic_string_empty(cpt_basic_string) ||
       t_pos >= basic_string_size(cpt_basic_string))
    {
        return NPOS;
    }

    if(t_len > t_cstrlen)
    {
        return NPOS;
    }

    pc_string = (char*)basic_string_at(cpt_basic_string, 0);
    pc_cstr = (char*)cpv_value_string;
    t_startpos = t_pos;
    while(t_startpos != t_stringlen)
    {
        t_endpos = 0;
        while(t_endpos != t_len)
        {
            t_less = t_greater = t_typesize;
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                pc_string + t_startpos * t_typesize,
                pc_cstr + t_endpos * t_typesize, &t_less);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                pc_cstr + t_endpos * t_typesize,
                pc_string + t_startpos * t_typesize, &t_greater);
            if(!t_less && !t_greater)
            {
                return t_startpos;
            }
            else
            {
                t_endpos++;
            }
        }

        t_startpos++;
    }

    return NPOS;
}

size_t basic_string_find_first_not_of(
    const basic_string_t* cpt_basic_string,
    const basic_string_t* cpt_basic_string_find, size_t t_pos)
{
    if(basic_string_empty(cpt_basic_string_find))
    {
        return basic_string_find_first_not_of_cstr(cpt_basic_string, "", t_pos);
    }
    else
    {
        return basic_string_find_first_not_of_cstr(
            cpt_basic_string, basic_string_at(cpt_basic_string_find, 0), t_pos);
    }
}

size_t basic_string_find_first_not_of_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos)
{
    return basic_string_find_first_not_of_subcstr(cpt_basic_string, cpv_value_string, t_pos,
        _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string));
}

size_t basic_string_find_first_not_of_subcstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_value_string, size_t t_pos, size_t t_len)
{
    size_t t_typesize = 0;
    size_t t_stringlen = 0;
    size_t t_cstrlen = 0;
    size_t t_startpos = 0;
    size_t t_endpos = 0;
    char*  pc_string = NULL;
    char*  pc_cstr = NULL;
    bool_t t_less = false;
    bool_t t_greater = false;

    assert(cpt_basic_string != NULL && cpv_value_string != NULL);

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    t_stringlen = basic_string_length(cpt_basic_string);
    t_cstrlen = _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string);

    /* find position is beyond the range of cpt_basic_string */
    if(basic_string_empty(cpt_basic_string) ||
       t_pos >= basic_string_size(cpt_basic_string))
    {
        return NPOS;
    }

    if(t_len > t_cstrlen)
    {
        return NPOS;
    }
    if(t_len == 0)
    {
        return t_pos;
    }

    pc_string = (char*)basic_string_at(cpt_basic_string, 0);
    pc_cstr = (char*)cpv_value_string;
    t_startpos = t_pos;
    while(t_startpos != t_stringlen)
    {
        t_endpos = 0;
        while(t_endpos != t_len)
        {
            t_less = t_greater = t_typesize;
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                pc_string + t_startpos * t_typesize,
                pc_cstr + t_endpos * t_typesize, &t_less);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                pc_cstr + t_endpos * t_typesize,
                pc_string + t_startpos * t_typesize, &t_greater);
            if(!t_less && !t_greater)
            {
                break;
            }
            else
            {
                t_endpos++;
            }
        }

        if(t_endpos == t_len)
        {
            return t_startpos;
        }
        else
        {
            t_startpos++;
        }
    }

    return NPOS;
}


size_t basic_string_find_last_of(
    const basic_string_t* cpt_basic_string,
    const basic_string_t* cpt_basic_string_find, size_t t_pos)
{
    if(basic_string_empty(cpt_basic_string_find))
    {
        return basic_string_find_last_of_cstr(cpt_basic_string, "", t_pos);
    }
    else
    {
        return basic_string_find_last_of_cstr(
            cpt_basic_string, basic_string_at(cpt_basic_string_find, 0), t_pos);
    }
}

size_t basic_string_find_last_of_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos)
{
    return basic_string_find_last_of_subcstr(cpt_basic_string, cpv_value_string, t_pos,
        _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string));
}

size_t basic_string_find_last_of_subcstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_value_string, size_t t_pos, size_t t_len)
{
    size_t t_typesize = 0;
    size_t t_stringlen = 0;
    size_t t_cstrlen = 0;
    size_t t_startpos = 0;
    size_t t_endpos = 0;
    char*  pc_string = NULL;
    char*  pc_cstr = NULL;
    bool_t t_less = false;
    bool_t t_greater = false;

    assert(cpt_basic_string != NULL && cpv_value_string != NULL);

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    t_stringlen = basic_string_length(cpt_basic_string);
    t_cstrlen = _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string);

    if(t_pos > t_stringlen)
    {
        t_pos = t_stringlen;
    }

    /* find position is beyond the range of cpt_basic_string */
    if(basic_string_empty(cpt_basic_string))
    {
        return NPOS;
    }

    if(t_len > t_cstrlen)
    {
        return NPOS;
    }

    pc_string = (char*)basic_string_at(cpt_basic_string, 0);
    pc_cstr = (char*)cpv_value_string;
    t_startpos = t_pos == t_stringlen ? t_pos - 1 : t_pos;
    for(;;)
    {
        t_endpos = 0;
        while(t_endpos != t_len)
        {
            t_less = t_greater = t_typesize;
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                pc_string + t_startpos * t_typesize,
                pc_cstr + t_endpos * t_typesize, &t_less);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                pc_cstr + t_endpos * t_typesize,
                pc_string + t_startpos * t_typesize, &t_greater);
            if(!t_less && !t_greater)
            {
                return t_startpos;
            }
            else
            {
                t_endpos++;
            }
        }

        if(t_startpos > 0)
        {
            t_startpos--;
        }
        else
        {
            break;
        }
    }

    return NPOS;
}

size_t basic_string_find_last_not_of(
    const basic_string_t* cpt_basic_string,
    const basic_string_t* cpt_basic_string_find, size_t t_pos)
{
    if(basic_string_empty(cpt_basic_string_find))
    {
        return basic_string_find_last_not_of_cstr(cpt_basic_string, "", t_pos);
    }
    else
    {
        return basic_string_find_last_not_of_cstr(
            cpt_basic_string, basic_string_at(cpt_basic_string_find, 0), t_pos);
    }
}

size_t basic_string_find_last_not_of_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string, size_t t_pos)
{
    return basic_string_find_last_not_of_subcstr(cpt_basic_string, cpv_value_string, t_pos,
        _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string));
}

size_t basic_string_find_last_not_of_subcstr(
    const basic_string_t* cpt_basic_string, const void* cpv_value_string,
    size_t t_pos, size_t t_len)
{
    size_t t_typesize = 0;
    size_t t_stringlen = 0;
    size_t t_cstrlen = 0;
    size_t t_startpos = 0;
    size_t t_endpos = 0;
    char*  pc_string = NULL;
    char*  pc_cstr = NULL;
    bool_t t_less = false;
    bool_t t_greater = false;

    assert(cpt_basic_string != NULL && cpv_value_string != NULL);

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    t_stringlen = basic_string_length(cpt_basic_string);
    t_cstrlen = _basic_string_get_value_string_length(cpt_basic_string, cpv_value_string);

    if(t_pos > t_stringlen)
    {
        t_pos = t_stringlen;
    }

    /* find position is beyond the range of cpt_basic_string */
    if(basic_string_empty(cpt_basic_string))
    {
        return NPOS;
    }

    if(t_len > t_cstrlen)
    {
        return NPOS;
    }
    if(t_len == 0)
    {
        if(t_pos == t_stringlen)
        {
            return t_pos - 1;
        }
        else
        {
            return t_pos;
        }
    }

    pc_string = (char*)basic_string_at(cpt_basic_string, 0);
    pc_cstr = (char*)cpv_value_string;
    t_startpos = t_pos == t_stringlen ? t_pos - 1 : t_pos;
    for(;;)
    {
        t_endpos = 0;
        while(t_endpos != t_len)
        {
            t_less = t_greater = t_typesize;
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                pc_string + t_startpos * t_typesize,
                pc_cstr + t_endpos * t_typesize, &t_less);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                pc_cstr + t_endpos * t_typesize,
                pc_string + t_startpos * t_typesize, &t_greater);
            if(!t_less && !t_greater)
            {
                break;
            }
            else
            {
                t_endpos++;
            }
        }

        if(t_endpos == t_len)
        {
            return t_startpos;
        }
        else
        {
            if(t_startpos > 0)
            {
                t_startpos--;
            }
            else
            {
                break;
            }
        }
    }

    return NPOS;
}


/* modifiers */
void basic_string_clear(basic_string_t* pt_basic_string)
{
    assert(pt_basic_string != NULL);

    vector_clear(&pt_basic_string->_t_vector);
}

void basic_string_swap(
    basic_string_t* pt_basic_stringfirst, basic_string_t* pt_basic_stringsecond)
{
    assert(pt_basic_stringfirst != NULL && pt_basic_stringsecond != NULL);

    vector_swap(&pt_basic_stringfirst->_t_vector, &pt_basic_stringsecond->_t_vector);
}

void basic_string_reserve(basic_string_t* pt_basic_string, size_t t_reservesize)
{
    assert(pt_basic_string != NULL);

    vector_reserve(&pt_basic_string->_t_vector, t_reservesize);
}






void basic_string_assign(
    basic_string_t* pt_basic_string, const basic_string_t* cpt_basic_string_assign)
{
    assert(_basic_string_same_type(pt_basic_string, cpt_basic_string_assign));

    basic_string_assign_range(pt_basic_string,
        basic_string_begin(cpt_basic_string_assign),
        basic_string_end(cpt_basic_string_assign));
}

void basic_string_assign_substring(
    basic_string_t* pt_basic_string, const basic_string_t* cpt_basic_string_assign,
    size_t t_pos, size_t t_len)
{
    basic_string_iterator_t t_begin;
    basic_string_iterator_t t_end;

    assert(_basic_string_same_type(pt_basic_string, cpt_basic_string_assign));

    t_begin = iterator_next_n(basic_string_begin(cpt_basic_string_assign), t_pos);
    t_end = iterator_next_n(basic_string_begin(cpt_basic_string_assign), t_pos + t_len);
    basic_string_assign_range(pt_basic_string, t_begin, t_end);
}

void basic_string_assign_cstr(
    basic_string_t* pt_basic_string, const void* cpv_value_string)
{
    basic_string_assign_subcstr(pt_basic_string, cpv_value_string, NPOS);
}

void basic_string_assign_subcstr(
    basic_string_t* pt_basic_string, const void* cpv_value_string, size_t t_len)
{
    size_t t_length = 0;
    size_t t_index = 0;
    char*  pc_value = NULL;
    bool_t t_result = false;

    assert(pt_basic_string != NULL && cpv_value_string != NULL);

    t_length = _basic_string_get_value_string_length(pt_basic_string, cpv_value_string);
    t_len = t_len < t_length ? t_len : t_length;

    vector_resize(&pt_basic_string->_t_vector, t_len);
    assert(vector_size(&pt_basic_string->_t_vector) == t_len);

    if(t_len > 0)
    {
        pc_value = (char*)vector_at(&pt_basic_string->_t_vector, 0); 
        assert(pc_value != NULL);
        for(t_index = 0; t_index < t_len; ++t_index)
        {
            t_result = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
            _GET_BASIC_STRING_TYPE_COPY_FUNCTION(pt_basic_string)(
                pc_value + t_index * _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string),
                (char*)cpv_value_string + t_index*_GET_BASIC_STRING_TYPE_SIZE(pt_basic_string),
                &t_result);
            assert(t_result);
        }
    }
}

void basic_string_assign_range(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin, basic_string_iterator_t t_end)
{
    assert(_GET_BASIC_STRING_CONTAINER(t_begin) != pt_basic_string &&
           _GET_BASIC_STRING_CONTAINER(t_end) != pt_basic_string);
    assert(_basic_string_same_type(pt_basic_string, _GET_BASIC_STRING_CONTAINER(t_begin)) &&
           _basic_string_same_type(pt_basic_string, _GET_BASIC_STRING_CONTAINER(t_end)));

    _GET_VECTOR_CONTAINER_TYPE(t_begin) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE(t_end) = _VECTOR_CONTAINER;
    vector_assign_range(&pt_basic_string->_t_vector, t_begin, t_end);
    _GET_BASIC_STRING_CONTAINER_TYPE(t_begin) = _BASIC_STRING_CONTAINER;
    _GET_BASIC_STRING_CONTAINER_TYPE(t_end) = _BASIC_STRING_CONTAINER;
}



/* append */
void basic_string_append(
    basic_string_t* pt_basic_string, const basic_string_t* cpt_basic_string_append)
{
    basic_string_append_substring(pt_basic_string, cpt_basic_string_append, 0, NPOS);
}

void basic_string_append_substring(
    basic_string_t* pt_basic_string, const basic_string_t* cpt_basic_string_append,
    size_t t_pos, size_t t_len)
{
    size_t t_size = 0;

    assert(pt_basic_string != NULL && cpt_basic_string_append != NULL);

    t_size = basic_string_size(cpt_basic_string_append);
    assert(t_pos <= t_size);

    if(t_pos + t_len >= t_size)
    {
        t_len = NPOS;
    }

    if(basic_string_empty(cpt_basic_string_append))
    {
        basic_string_append_subcstr(pt_basic_string, "", t_len);
    }
    else
    {
        basic_string_append_subcstr(
            pt_basic_string, basic_string_at(cpt_basic_string_append, t_pos), t_len);
    }
}

void basic_string_append_cstr(
    basic_string_t* pt_basic_string, const void* cpv_value_string)
{
    basic_string_append_subcstr(pt_basic_string, cpv_value_string, NPOS);
}

void basic_string_append_subcstr(
    basic_string_t* pt_basic_string, const void* cpv_value_string, size_t t_len)
{
    size_t t_typesize = 0;
    size_t t_cstrlen = 0;
    size_t t_stringlen = 0;
    size_t t_index = 0;
    char*  pc_value = NULL;
    bool_t t_result = false;

    assert(pt_basic_string != NULL && cpv_value_string != NULL);

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
    t_stringlen = basic_string_length(pt_basic_string);
    t_cstrlen = _basic_string_get_value_string_length(pt_basic_string, cpv_value_string);
    t_len = t_len < t_cstrlen ? t_len : t_cstrlen;

    if(t_len > 0)
    {
        vector_resize(&pt_basic_string->_t_vector, t_stringlen + t_len);
        pc_value = (char*)basic_string_at(pt_basic_string, t_stringlen);
        assert(pc_value != NULL);
        for(t_index = 0; t_index < t_len; ++t_index)
        {
            t_result = t_typesize;
            _GET_BASIC_STRING_TYPE_COPY_FUNCTION(pt_basic_string)(
                pc_value + t_index * t_typesize,
                (char*)cpv_value_string + t_index * t_typesize, &t_result);
            assert(t_result);
        }
    }
}

void basic_string_append_range(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin, basic_string_iterator_t t_end)
{
    assert(
        _GET_BASIC_STRING_CONTAINER(t_begin) != pt_basic_string &&
        _GET_BASIC_STRING_CONTAINER(t_end) != pt_basic_string);
    assert(
        _basic_string_same_type(pt_basic_string, _GET_BASIC_STRING_CONTAINER(t_begin)) &&
        _basic_string_same_type(pt_basic_string, _GET_BASIC_STRING_CONTAINER(t_end)));

    basic_string_append_subcstr(
        pt_basic_string, iterator_get_pointer(t_begin),
        iterator_distance(t_begin, t_end));
}



/* insert */



void basic_string_insert_string(
    basic_string_t* pt_basic_string, size_t t_pos,
    const basic_string_t* cpt_basic_string_insert)
{
    basic_string_iterator_t t_insert = basic_string_begin(pt_basic_string);

    assert(t_pos <= basic_string_size(pt_basic_string));

    if(t_pos != 0)
    {
        t_insert = iterator_next_n(t_insert, t_pos);
    }

    basic_string_insert_range(
        pt_basic_string, t_insert, 
        basic_string_begin(cpt_basic_string_insert),
        basic_string_end(cpt_basic_string_insert));
}

void basic_string_insert_substring(
    basic_string_t* pt_basic_string, size_t t_pos,
    const basic_string_t* cpt_basic_string_insert, size_t t_startpos, size_t t_len)
{
    basic_string_iterator_t t_insert = basic_string_begin(pt_basic_string);
    basic_string_iterator_t t_begin  = basic_string_begin(cpt_basic_string_insert);
    basic_string_iterator_t t_end    = basic_string_begin(cpt_basic_string_insert);

    if(t_pos != 0)
    {
        t_insert = iterator_next_n(t_insert, t_pos);
    }
    if(t_startpos != 0)
    {
        t_begin = iterator_next_n(t_begin, t_startpos);
    }
    if(t_len == NPOS || t_startpos + t_len >= basic_string_size(cpt_basic_string_insert))
    {
        t_end = basic_string_end(cpt_basic_string_insert);
    }
    else
    {
        t_end = iterator_next_n(t_end, t_startpos + t_len);
    }

    basic_string_insert_range(pt_basic_string, t_insert, t_begin, t_end);
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

