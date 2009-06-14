/*
 *  The implementation of basic_string
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
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "cstl_alloc.h"
#include "cstl_types.h"
#include "cstl_iterator.h"
#include "cstl_iterator_private.h"
#include "cvector.h"

#include "cstl_basic_string_iterator.h"
#include "cstl_basic_string_private.h"
#include "cstl_basic_string.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/
#define _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string)\
    ((pt_basic_string)->_t_vector._t_typeinfo._pt_type->_t_typesize)
#define _GET_BASIC_STRING_TYPE_NAME(pt_basic_string)\
    ((pt_basic_string)->_t_vector._t_typeinfo._sz_typename)
#define _GET_BASIC_STRING_TYPE_BASENAME(pt_basic_string)\
    ((pt_basic_string)->_t_vector._t_typeinfo._pt_type->_sz_typename)
#define _GET_BASIC_STRING_TYPE_INIT_FUNCTION(pt_basic_string)\
    ((pt_basic_string)->_t_vector._t_typeinfo._pt_type->_t_typeinit)
#define _GET_BASIC_STRING_TYPE_COPY_FUNCTION(pt_basic_string)\
    ((pt_basic_string)->_t_vector._t_typeinfo._pt_type->_t_typecopy)
#define _GET_BASIC_STRING_TYPE_LESS_FUNCTION(pt_basic_string)\
    ((pt_basic_string)->_t_vector._t_typeinfo._pt_type->_t_typeless)
#define _GET_BASIC_STRING_TYPE_DESTROY_FUNCTION(pt_basic_string)\
    ((pt_basic_string)->_t_vector._t_typeinfo._pt_type->_t_typedestroy)

/** local function prototype section **/
#ifndef NDEBUG
/*
 * Assert support.
 */
static bool_t _iterator_belong_to_basic_string(
    const basic_string_t* cpt_basic_string, basic_string_iterator_t t_iter);
static bool_t _basic_string_same_type(
    const basic_string_t* cpt_basic_stringfirst, 
    const basic_string_t* cpt_basic_stringsecond);
#endif /* NDEBUG */

/*
 * Get the value string length.
 */
static size_t _get_valuestring_len(
    const basic_string_t* cpt_basic_string, const void* cpv_valuestring);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* basic_string iterator function */
basic_string_iterator_t create_basic_string_iterator(void)
{
    basic_string_iterator_t t_newiterator = create_vector_iterator();
    _GET_BASIC_STRING_CONTAINER_TYPE(t_newiterator) = _BASIC_STRING_CONTAINER;

    return t_newiterator;
}

bool_t _basic_string_iterator_equal(
    basic_string_iterator_t t_iterfirst, basic_string_iterator_t t_itersecond)
{
    bool_t t_result;

    assert(_iterator_same_type(t_iterfirst, t_itersecond));
    assert(_GET_BASIC_STRING_CONTAINER(t_iterfirst) ==
           _GET_BASIC_STRING_CONTAINER(t_itersecond));
    assert(_iterator_belong_to_basic_string(
        _GET_BASIC_STRING_CONTAINER(t_iterfirst), t_iterfirst));
    assert(_iterator_belong_to_basic_string(
        _GET_BASIC_STRING_CONTAINER(t_itersecond), t_itersecond));

    _GET_VECTOR_CONTAINER_TYPE(t_iterfirst) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE(t_itersecond) = _VECTOR_CONTAINER;

    t_result = _vector_iterator_equal(t_iterfirst, t_itersecond);

    _GET_BASIC_STRING_CONTAINER_TYPE(t_iterfirst) = _BASIC_STRING_CONTAINER;
    _GET_BASIC_STRING_CONTAINER_TYPE(t_itersecond) = _BASIC_STRING_CONTAINER;

    return t_result;
}

void _basic_string_iterator_get_value(
    basic_string_iterator_t t_iter, void* pv_value)
{
    assert(_iterator_belong_to_basic_string(
        _GET_BASIC_STRING_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter,
        basic_string_end(_GET_BASIC_STRING_CONTAINER(t_iter))));

    _GET_VECTOR_CONTAINER_TYPE(t_iter) = _VECTOR_CONTAINER;

    _vector_iterator_get_value(t_iter, pv_value);

    _GET_BASIC_STRING_CONTAINER_TYPE(t_iter) = _BASIC_STRING_CONTAINER;
}

void _basic_string_iterator_set_value(
    basic_string_iterator_t t_iter, const void* cpv_value)
{
    assert(_iterator_belong_to_basic_string(
        _GET_BASIC_STRING_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter,
        basic_string_end(_GET_BASIC_STRING_CONTAINER(t_iter))));

    _GET_VECTOR_CONTAINER_TYPE(t_iter) = _VECTOR_CONTAINER;

    _vector_iterator_set_value(t_iter, cpv_value);

    _GET_BASIC_STRING_CONTAINER_TYPE(t_iter) = _BASIC_STRING_CONTAINER;
}

const void* _basic_string_iterator_get_pointer(basic_string_iterator_t t_iter)
{
    void* pv_pointer = NULL;

    assert(_iterator_belong_to_basic_string(
        _GET_BASIC_STRING_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter,
        basic_string_end(_GET_BASIC_STRING_CONTAINER(t_iter))));

    _GET_VECTOR_CONTAINER_TYPE(t_iter) = _VECTOR_CONTAINER;

    pv_pointer = (void*)_vector_iterator_get_pointer(t_iter);

    _GET_BASIC_STRING_CONTAINER_TYPE(t_iter) = _BASIC_STRING_CONTAINER;

    return pv_pointer;
}

basic_string_iterator_t _basic_string_iterator_next(basic_string_iterator_t t_iter)
{
    assert(_iterator_belong_to_basic_string(
        _GET_BASIC_STRING_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter,
        basic_string_end(_GET_BASIC_STRING_CONTAINER(t_iter))));

    _GET_VECTOR_CONTAINER_TYPE(t_iter) = _VECTOR_CONTAINER;

    t_iter = _vector_iterator_next(t_iter);

    _GET_BASIC_STRING_CONTAINER_TYPE(t_iter) = _BASIC_STRING_CONTAINER;

    return t_iter;
}

basic_string_iterator_t _basic_string_iterator_prev(
    basic_string_iterator_t t_iter)
{
    assert(_iterator_belong_to_basic_string(
        _GET_BASIC_STRING_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter,
        basic_string_begin(_GET_BASIC_STRING_CONTAINER(t_iter))));

    _GET_VECTOR_CONTAINER_TYPE(t_iter) = _VECTOR_CONTAINER;

    t_iter = _vector_iterator_prev(t_iter);

    _GET_BASIC_STRING_CONTAINER_TYPE(t_iter) = _BASIC_STRING_CONTAINER;

    return t_iter;
}

void* _basic_string_iterator_at(basic_string_iterator_t t_iter, int n_index)
{
    void* pv_value = NULL;

    assert(_iterator_belong_to_basic_string(
        _GET_BASIC_STRING_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter,
        basic_string_begin(_GET_BASIC_STRING_CONTAINER(t_iter))));

    _GET_VECTOR_CONTAINER_TYPE(t_iter) = _VECTOR_CONTAINER;

    pv_value = _vector_iterator_at(t_iter, n_index);
    assert(pv_value != NULL);

    _GET_BASIC_STRING_CONTAINER_TYPE(t_iter) = _BASIC_STRING_CONTAINER;

    return pv_value;
}

basic_string_iterator_t _basic_string_iterator_next_n(
    basic_string_iterator_t t_iter, int n_step)
{
    assert(_iterator_belong_to_basic_string(
        _GET_BASIC_STRING_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter,
        basic_string_end(_GET_BASIC_STRING_CONTAINER(t_iter))));

    _GET_VECTOR_CONTAINER_TYPE(t_iter) = _VECTOR_CONTAINER;

    t_iter = _vector_iterator_next_n(t_iter, n_step);

    _GET_BASIC_STRING_CONTAINER_TYPE(t_iter) = _BASIC_STRING_CONTAINER;

    return t_iter;
}

basic_string_iterator_t _basic_string_iterator_prev_n(
    basic_string_iterator_t t_iter, int n_step)
{
    assert(_iterator_belong_to_basic_string(
        _GET_BASIC_STRING_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter,
        basic_string_begin(_GET_BASIC_STRING_CONTAINER(t_iter))));

    _GET_VECTOR_CONTAINER_TYPE(t_iter) = _VECTOR_CONTAINER;

    t_iter = _vector_iterator_prev_n(t_iter, n_step);

    _GET_BASIC_STRING_CONTAINER_TYPE(t_iter) = _BASIC_STRING_CONTAINER;

    return t_iter;
}

int _basic_string_iterator_minus(
    basic_string_iterator_t t_iterfirst, basic_string_iterator_t t_itersecond)
{
    int n_distance = 0;

    assert(_iterator_belong_to_basic_string(
        _GET_BASIC_STRING_CONTAINER(t_iterfirst), t_iterfirst));
    assert(_iterator_belong_to_basic_string(
        _GET_BASIC_STRING_CONTAINER(t_itersecond), t_itersecond));

    _GET_VECTOR_CONTAINER_TYPE(t_iterfirst) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE(t_itersecond) = _VECTOR_CONTAINER;

    n_distance = _vector_iterator_minus(t_iterfirst, t_itersecond);

    _GET_BASIC_STRING_CONTAINER_TYPE(t_iterfirst) = _BASIC_STRING_CONTAINER;
    _GET_BASIC_STRING_CONTAINER_TYPE(t_itersecond) = _BASIC_STRING_CONTAINER;

    return n_distance;
}

bool_t _basic_string_iterator_less(
    basic_string_iterator_t t_iterfirst, basic_string_iterator_t t_itersecond)
{
    bool_t t_result;

    assert(_iterator_belong_to_basic_string(
        _GET_BASIC_STRING_CONTAINER(t_iterfirst), t_iterfirst));
    assert(_iterator_belong_to_basic_string(
        _GET_BASIC_STRING_CONTAINER(t_itersecond), t_itersecond));

    _GET_VECTOR_CONTAINER_TYPE(t_iterfirst) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE(t_itersecond) = _VECTOR_CONTAINER;

    t_result = _vector_iterator_less(t_iterfirst, t_itersecond);

    _GET_BASIC_STRING_CONTAINER_TYPE(t_iterfirst) = _BASIC_STRING_CONTAINER;
    _GET_BASIC_STRING_CONTAINER_TYPE(t_itersecond) = _BASIC_STRING_CONTAINER;

    return t_result;   
}

bool_t _basic_string_iterator_before(
    basic_string_iterator_t t_iterfirst, basic_string_iterator_t t_itersecond)
{
    bool_t t_result;

    assert(_iterator_belong_to_basic_string(
        _GET_BASIC_STRING_CONTAINER(t_iterfirst), t_iterfirst));
    assert(_iterator_belong_to_basic_string(
        _GET_BASIC_STRING_CONTAINER(t_itersecond), t_itersecond));

    _GET_VECTOR_CONTAINER_TYPE(t_iterfirst) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE(t_itersecond) = _VECTOR_CONTAINER;

    t_result = _vector_iterator_before(t_iterfirst, t_itersecond);

    _GET_BASIC_STRING_CONTAINER_TYPE(t_iterfirst) = _BASIC_STRING_CONTAINER;
    _GET_BASIC_STRING_CONTAINER_TYPE(t_itersecond) = _BASIC_STRING_CONTAINER;

    return t_result;
}

/* basic_string private function */
basic_string_t* _create_basic_string(const char* s_typename)
{
    return (basic_string_t*)_create_vector(s_typename);
}

/* basic_string function */
/* constructor, copy constructor and destructor */
void basic_string_init(basic_string_t* pt_basic_string)
{
    assert(pt_basic_string != NULL);

    vector_init(&pt_basic_string->_t_vector);
    vector_push_back(&pt_basic_string->_t_vector, 0x00);
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
    vector_push_back(&pt_basic_string->_t_vector, 0x00);
}

void basic_string_init_copy_substring(
    basic_string_t* pt_basic_string,
    const basic_string_t* cpt_basic_string_src, size_t t_pos, size_t t_len)
{
    basic_string_iterator_t t_begin;
    basic_string_iterator_t t_end;

    assert(pt_basic_string != NULL && cpt_basic_string_src != NULL);
    assert(t_pos < basic_string_size(cpt_basic_string_src));

    t_begin = basic_string_begin(cpt_basic_string_src);
    t_begin = iterator_next_n(t_begin, t_pos);

    if(t_len == NPOS || 
       t_len + t_pos >= basic_string_size(cpt_basic_string_src))
    {
        t_end = basic_string_end(cpt_basic_string_src);
    }
    else
    {
        t_end = basic_string_begin(cpt_basic_string_src);
        t_end = iterator_next_n(t_end, t_pos + t_len);
    }

    _GET_VECTOR_CONTAINER_TYPE(t_begin) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE(t_end) = _VECTOR_CONTAINER;

    vector_init_copy_range(&pt_basic_string->_t_vector, t_begin, t_end);
    vector_push_back(&pt_basic_string->_t_vector, 0x00);
}

void basic_string_init_cstr(
    basic_string_t* pt_basic_string, const void* cpv_valuestring)
{
    basic_string_init_subcstr(pt_basic_string, cpv_valuestring, NPOS);
}

void basic_string_init_subcstr(
    basic_string_t* pt_basic_string, const void* cpv_valuestring, size_t t_len)
{
    size_t t_length = 0;
    size_t t_index = 0;
    char*  pc_value = NULL;
    bool_t t_result = false;

    assert(pt_basic_string != NULL);

    t_length = _get_valuestring_len(pt_basic_string, cpv_valuestring);
    t_len = t_len < t_length ? t_len : t_length;

    vector_init(&pt_basic_string->_t_vector);
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
                (char*)cpv_valuestring + t_index*_GET_BASIC_STRING_TYPE_SIZE(pt_basic_string),
                &t_result);
            assert(t_result);
        }
    }

    /* add null-terminated node */
    vector_push_back(&pt_basic_string->_t_vector, 0x00);
}

void _basic_string_init_elem(
    basic_string_t* pt_basic_string, size_t t_count, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_count);
    _basic_string_init_elem_varg(pt_basic_string, t_count, val_elemlist);
}

void _basic_string_init_elem_varg(
    basic_string_t* pt_basic_string, size_t t_count, va_list val_elemlist)
{
    _vector_init_elem_varg(&pt_basic_string->_t_vector, t_count, val_elemlist);
    /* add null-terminated node */
    vector_push_back(&pt_basic_string->_t_vector, 0x00);
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
            pv_buffer + t_index * _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string),
            pv_copypos + t_index * _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string), &t_result);
        assert(t_result);
    }

    return t_size;
}

/* size and capacity */
size_t basic_string_size(const basic_string_t* cpt_basic_string)
{
    assert(cpt_basic_string != NULL);

    return vector_size(&cpt_basic_string->_t_vector) - 1;
}

size_t basic_string_length(const basic_string_t* cpt_basic_string)
{
    return basic_string_size(cpt_basic_string);
}

bool_t basic_string_empty(const basic_string_t* cpt_basic_string)
{
    if(basic_string_size(cpt_basic_string) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

size_t basic_string_max_size(const basic_string_t* cpt_basic_string)
{
    assert(cpt_basic_string != NULL);

    return (size_t)(-1) / _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string) - 1;
}

size_t basic_string_capacity(const basic_string_t* cpt_basic_string)
{
    assert(cpt_basic_string != NULL);

    return vector_capacity(&cpt_basic_string->_t_vector) - 1;
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
    const basic_string_t* cpt_basic_stringfirst,
    const basic_string_t* cpt_basic_stringsecond)
{
    assert(cpt_basic_stringfirst != NULL && cpt_basic_stringsecond != NULL);

    return vector_equal(
        &cpt_basic_stringfirst->_t_vector, &cpt_basic_stringsecond->_t_vector);
}

bool_t basic_string_not_equal(
    const basic_string_t* cpt_basic_stringfirst,
    const basic_string_t* cpt_basic_stringsecond)
{
    assert(cpt_basic_stringfirst != NULL && cpt_basic_stringsecond != NULL);

    return vector_not_equal(
        &cpt_basic_stringfirst->_t_vector, &cpt_basic_stringsecond->_t_vector);
}

bool_t basic_string_less(
    const basic_string_t* cpt_basic_stringfirst,
    const basic_string_t* cpt_basic_stringsecond)
{
    assert(cpt_basic_stringfirst != NULL && cpt_basic_stringsecond != NULL);

    return vector_less(
        &cpt_basic_stringfirst->_t_vector, &cpt_basic_stringsecond->_t_vector);
}

bool_t basic_string_less_equal(
    const basic_string_t* cpt_basic_stringfirst,
    const basic_string_t* cpt_basic_stringsecond)
{
    assert(cpt_basic_stringfirst != NULL && cpt_basic_stringsecond != NULL);

    return vector_less_equal(
        &cpt_basic_stringfirst->_t_vector, &cpt_basic_stringsecond->_t_vector);
}

bool_t basic_string_great(
    const basic_string_t* cpt_basic_stringfirst,
    const basic_string_t* cpt_basic_stringsecond)
{
    assert(cpt_basic_stringfirst != NULL && cpt_basic_stringsecond != NULL);

    return vector_great(
        &cpt_basic_stringfirst->_t_vector, &cpt_basic_stringsecond->_t_vector);
}

bool_t basic_string_great_equal(
    const basic_string_t* cpt_basic_stringfirst,
    const basic_string_t* cpt_basic_stringsecond)
{
    assert(cpt_basic_stringfirst != NULL && cpt_basic_stringsecond != NULL);

    return vector_great_equal(
        &cpt_basic_stringfirst->_t_vector, &cpt_basic_stringsecond->_t_vector);
}

bool_t basic_string_equal_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_valuestring)
{
    if(basic_string_compare_cstr(cpt_basic_string, cpv_valuestring) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool_t basic_string_not_equal_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_valuestring)
{
    if(basic_string_compare_cstr(cpt_basic_string, cpv_valuestring) != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool_t basic_string_less_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_valuestring)
{
    if(basic_string_compare_cstr(cpt_basic_string, cpv_valuestring) < 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool_t basic_string_less_equal_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_valuestring)
{
    if(basic_string_compare_cstr(cpt_basic_string, cpv_valuestring) <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool_t basic_string_great_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_valuestring)
{
    if(basic_string_compare_cstr(cpt_basic_string, cpv_valuestring) > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool_t basic_string_great_equal_cstr(
    const basic_string_t* cpt_basic_string, const void* cpv_valuestring)
{
    if(basic_string_compare_cstr(cpt_basic_string, cpv_valuestring) >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int basic_string_compare(
    const basic_string_t* cpt_basic_stringfirst,
    const basic_string_t* cpt_basic_stringsecond)
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
        cpt_basic_stringfirst, t_firstpos, t_firstlen,
        cpt_basic_stringsecond, 0, NPOS);
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
    const basic_string_t* cpt_basic_string, const void* cpv_valuestring)
{
    return basic_string_compare_substring_subcstr(
        cpt_basic_string, 0, NPOS, cpv_valuestring, NPOS);
}

int basic_string_compare_substring_cstr(
    const basic_string_t* cpt_basic_string, size_t t_stringpos, size_t t_stringlen,
    const void* cpv_valuestring)
{
    return basic_string_compare_substring_subcstr(
        cpt_basic_string, t_stringpos, t_stringlen, cpv_valuestring, NPOS);
}

int basic_string_compare_substring_subcstr(
    const basic_string_t* cpt_basic_string, size_t t_stringpos, size_t t_stringlen,
    const void* cpv_valuestring, size_t t_valuestringlen)
{
    size_t t_cmplen = 0;
    size_t t_index = 0;
    char*  pc_string = NULL;
    char*  pc_value = NULL;
    size_t t_stringlentmp = 0;
    size_t t_valuestringlentmp = 0;
    bool_t t_result = false;

    assert(cpt_basic_string != NULL && cpv_valuestring != NULL);
    assert(t_stringpos < basic_string_size(cpt_basic_string));

    /* get actual string length and value string length */
    t_stringlentmp = basic_string_size(cpt_basic_string) - t_stringpos;
    t_valuestringlentmp = _get_valuestring_len(cpt_basic_string, cpv_valuestring);
    t_stringlen = t_stringlen < t_stringlentmp ?
                  t_stringlen : t_stringlentmp;
    t_valuestringlen = t_valuestringlen < t_valuestringlentmp ? 
                       t_valuestringlen : t_valuestringlentmp;
    t_cmplen = t_stringlen < t_valuestringlen ? 
               t_stringlen : t_valuestringlen;

    pc_string = (char*)basic_string_at(cpt_basic_string, t_stringpos);
    pc_value = (char*)cpv_valuestring;
    assert(pc_string != NULL && pc_value != NULL);

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

        /* add null-terminated */
        vector_push_back(&pt_basic_string->_t_vector, 0x00);
    }
}

void basic_string_connect_cstr(
    basic_string_t* pt_basic_string, const void* cpv_valuestring)
{
    size_t t_destlen = 0;
    size_t t_srclen = 0;
    size_t t_index = 0;
    char*  pc_dest = NULL;
    char*  pc_src = NULL;
    bool_t t_result = false;

    assert(pt_basic_string != NULL && cpv_valuestring != NULL);

    t_destlen = basic_string_size(pt_basic_string);
    t_srclen = _get_valuestring_len(pt_basic_string, cpv_valuestring);

    if(t_srclen > 0)
    {
        vector_resize(&pt_basic_string->_t_vector, t_destlen + t_srclen);

        pc_dest = (char*)vector_at(&pt_basic_string->_t_vector, t_destlen);
        pc_src = (char*)cpv_valuestring;
        assert(pc_dest != NULL && pc_src != NULL);

        for(t_index = 0; t_index < t_srclen; ++t_index)
        {
            t_result = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
            _GET_BASIC_STRING_TYPE_COPY_FUNCTION(pt_basic_string)(pc_dest, pc_src, &t_result);
            pc_dest += _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
            pc_src += _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
        }

        /* add null-terminated */
        vector_push_back(&pt_basic_string->_t_vector, 0x00);
    }
}

void _basic_string_connect_elem(basic_string_t* pt_basic_string, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_basic_string);
    _basic_string_connect_elem_varg(pt_basic_string, val_elemlist);
}

void _basic_string_connect_elem_varg(
    basic_string_t* pt_basic_string, va_list val_elemlist)
{
    size_t  t_typesize = 0;
    char*   pc_dest = NULL;
    void*   pv_varg = NULL;
    void*   pv_nullterminated = NULL;
    bool_t  t_result = false;

    assert(pt_basic_string != NULL);

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
    pv_varg = allocate(&pt_basic_string->_t_vector._t_allocater, t_typesize, 1);
    pv_nullterminated = allocate(&pt_basic_string->_t_vector._t_allocater, t_typesize, 1);
    assert(pv_varg != NULL && pv_nullterminated != NULL);
    t_result = t_typesize;
    _GET_BASIC_STRING_TYPE_INIT_FUNCTION(pt_basic_string)(pv_varg, &t_result);
    assert(t_result);
    memset(pv_nullterminated, 0x00, t_typesize);

    _type_get_varg_value(&pt_basic_string->_t_vector._t_typeinfo, val_elemlist, pv_varg);
    /* check input element is the null-terminated node */
    if(memcmp(pv_varg, pv_nullterminated, t_typesize) != 0)
    {
        pc_dest = (char*)vector_at(
            &pt_basic_string->_t_vector, basic_string_size(pt_basic_string));
        assert(pc_dest != NULL);
        t_result = t_typesize;
        _GET_BASIC_STRING_TYPE_COPY_FUNCTION(pt_basic_string)(pc_dest, pv_varg, &t_result);
        assert(t_result);
        /* add null-terminated */
        vector_push_back(&pt_basic_string->_t_vector, 0x00);
    }

    deallocate(&pt_basic_string->_t_vector._t_allocater, pv_varg, t_typesize, 1);
    deallocate(&pt_basic_string->_t_vector._t_allocater, pv_nullterminated, t_typesize, 1);
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
    assert(vector_size(&cpt_basic_string->_t_vector) > 0);

    t_newiterator = vector_rbegin(&cpt_basic_string->_t_vector);
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
        t_newiterator = iterator_prev(t_newiterator);
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
    const basic_string_t* cpt_basic_string, const void* cpv_valuestring, size_t t_pos)
{
    return basic_string_find_subcstr(cpt_basic_string, cpv_valuestring, t_pos, NPOS);
}

size_t basic_string_find_subcstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring, size_t t_pos, size_t t_len)
{
    size_t t_typesize = 0;
    size_t t_stringlen = 0;
    size_t t_cstrlen = 0;
    size_t t_startpos = 0;
    size_t t_endpos = 0;
    char*  pc_string = NULL;
    char*  pc_cstr = NULL;
    bool_t t_less = false;
    bool_t t_great = false;

    assert(cpt_basic_string != NULL && cpv_valuestring != NULL);

    t_stringlen = basic_string_length(cpt_basic_string);
    t_cstrlen = _get_valuestring_len(cpt_basic_string, cpv_valuestring);
    t_cstrlen = t_len < t_cstrlen ? t_len : t_cstrlen;

    /* find position is beyond the range of cpt_basic_string */
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    if(basic_string_empty(cpt_basic_string) ||
       t_pos > basic_string_size(cpt_basic_string) ||
       t_pos + t_cstrlen * t_typesize > basic_string_size(cpt_basic_string))
    {
        return NPOS;
    }
    /* value string is empty */
    if(t_cstrlen == 0)
    {
        return t_pos;
    }

    pc_string = (char*)basic_string_at(cpt_basic_string, 0);
    pc_cstr = (char*)cpv_valuestring;
    t_startpos = t_pos;
    while(t_startpos != t_stringlen)
    {
        t_less = t_great = t_typesize;
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pc_string + t_startpos * t_typesize, pc_cstr, &t_less);
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pc_cstr, pc_string + t_startpos * t_typesize, &t_great);
        if(!t_less && !t_great)
        {
            t_endpos = 0;
            while(t_endpos + t_startpos != t_stringlen && t_endpos != t_cstrlen)
            {
                t_less = t_great = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    pc_string + (t_endpos + t_startpos) * t_typesize,
                    pc_cstr + t_endpos * t_typesize, &t_less);
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    pc_cstr + t_endpos * t_typesize,
                    pc_string + (t_endpos + t_startpos) * t_typesize, &t_great);
                if(!t_less && !t_great)
                {
                    t_endpos++;
                }
                else
                {
                    break;
                }
            }

            if(t_endpos == t_cstrlen)
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

size_t _basic_string_find_elem(
    const basic_string_t* cpt_basic_string, size_t t_pos, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_pos);
    return _basic_string_find_elem_varg(cpt_basic_string, t_pos, val_elemlist);
}

size_t _basic_string_find_elem_varg(
    const basic_string_t* cpt_basic_string, size_t t_pos, va_list val_elemlist)
{
    size_t  t_typesize = 0;
    size_t  t_findpos = 0;
    size_t  t_stringlen = 0;
    void*   pv_varg = NULL;
    char*   pc_string = NULL;
    bool_t  t_result = false;
    bool_t  t_less = false;
    bool_t  t_great = false;

    assert(cpt_basic_string != NULL);

    if(t_pos > basic_string_size(cpt_basic_string))
    {
        return NPOS;
    }

    /* get element */
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    pv_varg = allocate(
        &((basic_string_t*)cpt_basic_string)->_t_vector._t_allocater, t_typesize, 1);
    assert(pv_varg != NULL);
    t_result = t_typesize;
    _GET_BASIC_STRING_TYPE_INIT_FUNCTION(cpt_basic_string)(pv_varg, &t_result);
    assert(t_result);
    _type_get_varg_value(
        &((basic_string_t*)cpt_basic_string)->_t_vector._t_typeinfo, val_elemlist, pv_varg);

    /* find elemen */
    t_stringlen = basic_string_length(cpt_basic_string);
    pc_string = (char*)basic_string_at(cpt_basic_string, 0);
    t_findpos = t_pos;
    while(t_findpos != t_stringlen)
    {
        t_less = t_great = t_typesize;
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pc_string + t_findpos * t_typesize, pv_varg, &t_less);
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pv_varg, pc_string + t_findpos * t_typesize, &t_great);
        if(!t_less && !t_great)
        {
            break;
        }
        else
        {
            t_findpos++;
        }
    }

    if(t_findpos == t_stringlen)
    {
        t_findpos = NPOS;
    }
    deallocate(&((basic_string_t*)cpt_basic_string)->_t_vector._t_allocater, pv_varg,
        _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string), 1);

    return t_findpos;
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
    const basic_string_t* cpt_basic_string, const void* cpv_valuestring, size_t t_pos)
{
    return basic_string_rfind_subcstr(cpt_basic_string, cpv_valuestring, t_pos, NPOS);
}

size_t basic_string_rfind_subcstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring, size_t t_pos, size_t t_len)
{
    size_t t_typesize = 0;
    size_t t_stringlen = 0;
    size_t t_cstrlen = 0;
    size_t t_startpos = 0;
    size_t t_endpos = 0;
    char*  pc_string = NULL;
    char*  pc_cstr = NULL;
    bool_t t_less = false;
    bool_t t_great = false;

    assert(cpt_basic_string != NULL && cpv_valuestring != NULL);

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    t_stringlen = basic_string_length(cpt_basic_string);
    t_cstrlen = _get_valuestring_len(cpt_basic_string, cpv_valuestring);
    t_cstrlen = t_len < t_cstrlen ? t_len : t_cstrlen;
    if(t_pos > t_stringlen)
    {
        t_pos = t_stringlen;
    }

    /* find position is beyond the range of cpt_basic_string */
    if(basic_string_empty(cpt_basic_string))
    {
        return NPOS;
    }
    /* value string is empty */
    if(t_cstrlen == 0)
    {
        return t_pos;
    }

    pc_string = (char*)basic_string_at(cpt_basic_string, 0);
    pc_cstr = (char*)cpv_valuestring;
    t_startpos = t_pos == t_stringlen ? t_pos - 1 : t_pos;
    for(;;)
    {
        t_less = t_great = t_typesize;
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pc_string + t_startpos * t_typesize, pc_cstr, &t_less);
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pc_cstr, pc_string + t_startpos * t_typesize, &t_great);
        if(!t_less && !t_great)
        {
            t_endpos = 0;
            while(t_endpos + t_startpos != t_stringlen && t_endpos != t_cstrlen)
            {
                t_less = t_great = t_typesize;
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    pc_string + (t_endpos + t_startpos) * t_typesize,
                    pc_cstr + t_endpos * t_typesize, &t_less);
                _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                    pc_cstr + t_endpos * t_typesize,
                    pc_string + (t_endpos + t_startpos) * t_typesize, &t_great);
                if(!t_less && !t_great)
                {
                    t_endpos++;
                }
                else
                {
                    break;
                }
            }

            if(t_endpos == t_cstrlen)
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

size_t _basic_string_rfind_elem(
    const basic_string_t* cpt_basic_string, size_t t_pos, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_pos);
    return _basic_string_rfind_elem_varg(cpt_basic_string, t_pos, val_elemlist);
}

size_t _basic_string_rfind_elem_varg(
    const basic_string_t* cpt_basic_string, size_t t_pos, va_list val_elemlist)
{
    size_t  t_typesize = 0;
    size_t  t_stringlen = 0;
    void*   pv_varg = NULL;
    char*   pc_string = NULL;
    size_t  t_findpos = 0;
    bool_t  t_result = false;
    bool_t  t_less = false;
    bool_t  t_great = false;

    assert(cpt_basic_string != NULL);

    t_stringlen = basic_string_length(cpt_basic_string);
    if(t_pos > t_stringlen)
    {
        t_pos = t_stringlen;
    }

    /* get element */
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    pv_varg = allocate(
        &((basic_string_t*)cpt_basic_string)->_t_vector._t_allocater, t_typesize, 1);
    assert(pv_varg != NULL);
    t_result = t_typesize;
    _GET_BASIC_STRING_TYPE_INIT_FUNCTION(cpt_basic_string)(pv_varg, &t_result);
    assert(t_result);
    _type_get_varg_value(
        &((basic_string_t*)cpt_basic_string)->_t_vector._t_typeinfo, val_elemlist, pv_varg);

    /* find elemen */
    pc_string = (char*)basic_string_at(cpt_basic_string, 0);
    t_findpos = t_pos == t_stringlen ? t_pos - 1 : t_pos;
    for(;;)
    {
        t_less = t_great = t_typesize;
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pc_string + t_findpos * t_typesize, pv_varg, &t_less);
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pv_varg, pc_string + t_findpos * t_typesize, &t_great);
        if(!t_less && !t_great)
        {
            break;
        }
        else
        {
            if(t_findpos > 0)
            {
                t_findpos--;
            }
            else
            {
                t_findpos = NPOS;
                break;
            }
        }
    }
    deallocate(&((basic_string_t*)cpt_basic_string)->_t_vector._t_allocater, pv_varg,
        _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string), 1);

    return t_findpos;
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
    const basic_string_t* cpt_basic_string, const void* cpv_valuestring, size_t t_pos)
{
    return basic_string_find_first_of_subcstr(
        cpt_basic_string, cpv_valuestring, t_pos, NPOS);
}

size_t basic_string_find_first_of_subcstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring, size_t t_pos, size_t t_len)
{
    size_t t_typesize = 0;
    size_t t_stringlen = 0;
    size_t t_cstrlen = 0;
    size_t t_startpos = 0;
    size_t t_endpos = 0;
    char*  pc_string = NULL;
    char*  pc_cstr = NULL;
    bool_t t_less = false;
    bool_t t_great = false;

    assert(cpt_basic_string != NULL && cpv_valuestring != NULL);

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    t_stringlen = basic_string_length(cpt_basic_string);
    t_cstrlen = _get_valuestring_len(cpt_basic_string, cpv_valuestring);
    t_cstrlen = t_len < t_cstrlen ? t_len : t_cstrlen;

    /* find position is beyond the range of cpt_basic_string */
    if(basic_string_empty(cpt_basic_string) ||
       t_pos >= basic_string_size(cpt_basic_string))
    {
        return NPOS;
    }

    pc_string = (char*)basic_string_at(cpt_basic_string, 0);
    pc_cstr = (char*)cpv_valuestring;
    t_startpos = t_pos;
    while(t_startpos != t_stringlen)
    {
        t_endpos = 0;
        while(t_endpos != t_cstrlen)
        {
            t_less = t_great = t_typesize;
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                pc_string + t_startpos * t_typesize,
                pc_cstr + t_endpos * t_typesize, &t_less);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                pc_cstr + t_endpos * t_typesize,
                pc_string + t_endpos * t_typesize, &t_great);
            if(!t_less && !t_great)
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
    const basic_string_t* cpt_basic_string, const void* cpv_valuestring, size_t t_pos)
{
    return basic_string_find_first_not_of_subcstr(
        cpt_basic_string, cpv_valuestring, t_pos, NPOS);
}

size_t basic_string_find_first_not_of_subcstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring, size_t t_pos, size_t t_len)
{
    size_t t_typesize = 0;
    size_t t_stringlen = 0;
    size_t t_cstrlen = 0;
    size_t t_startpos = 0;
    size_t t_endpos = 0;
    char*  pc_string = NULL;
    char*  pc_cstr = NULL;
    bool_t t_less = false;
    bool_t t_great = false;

    assert(cpt_basic_string != NULL && cpv_valuestring != NULL);

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    t_stringlen = basic_string_length(cpt_basic_string);
    t_cstrlen = _get_valuestring_len(cpt_basic_string, cpv_valuestring);
    t_cstrlen = t_len < t_cstrlen ? t_len : t_cstrlen;

    /* find position is beyond the range of cpt_basic_string */
    if(basic_string_empty(cpt_basic_string) ||
       t_pos >= basic_string_size(cpt_basic_string))
    {
        return NPOS;
    }

    pc_string = (char*)basic_string_at(cpt_basic_string, 0);
    pc_cstr = (char*)cpv_valuestring;
    t_startpos = t_pos;
    while(t_startpos != t_stringlen)
    {
        t_endpos = 0;
        while(t_endpos != t_cstrlen)
        {
            t_less = t_great = t_typesize;
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                pc_string + t_startpos * t_typesize,
                pc_cstr + t_endpos * t_typesize, &t_less);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                pc_cstr + t_endpos * t_typesize,
                pc_string + t_startpos * t_typesize, &t_great);
            if(!t_less && !t_great)
            {
                break;
            }
            else
            {
                t_endpos++;
            }
        }

        if(t_endpos == t_cstrlen)
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

size_t _basic_string_find_first_not_of_elem(
    const basic_string_t* cpt_basic_string, size_t t_pos, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_pos);
    return _basic_string_find_first_not_of_elem_varg(
        cpt_basic_string, t_pos, val_elemlist);
}

size_t _basic_string_find_first_not_of_elem_varg(
    const basic_string_t* cpt_basic_string, size_t t_pos, va_list val_elemlist)
{
    size_t  t_typesize = 0;
    size_t  t_findpos = 0;
    size_t  t_stringlen = 0;
    void*   pv_varg = NULL;
    char*   pc_string = NULL;
    bool_t  t_result = false;
    bool_t  t_less = false;
    bool_t  t_great = false;

    assert(cpt_basic_string != NULL);

    if(t_pos > basic_string_size(cpt_basic_string))
    {
        return NPOS;
    }

    /* get element */
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    pv_varg = allocate(
        &((basic_string_t*)cpt_basic_string)->_t_vector._t_allocater, t_typesize, 1);
    assert(pv_varg != NULL);
    t_result = t_typesize;
    _GET_BASIC_STRING_TYPE_INIT_FUNCTION(cpt_basic_string)(pv_varg, &t_result);
    assert(t_result);
    _type_get_varg_value(
        &((basic_string_t*)cpt_basic_string)->_t_vector._t_typeinfo, val_elemlist, pv_varg);

    /* find elemen */
    t_stringlen = basic_string_length(cpt_basic_string);
    pc_string = (char*)basic_string_at(cpt_basic_string, 0);
    t_findpos = t_pos;
    while(t_findpos != t_stringlen)
    {
        t_less = t_great = t_typesize;
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pc_string + t_findpos * t_typesize, pv_varg, &t_less);
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pv_varg, pc_string + t_findpos * t_typesize, &t_great);
        if(!t_less && !t_great)
        {
            break;
        }
        else
        {
            t_findpos++;
        }
    }

    if(t_findpos == t_stringlen)
    {
        t_findpos = NPOS;
    }
    deallocate(&((basic_string_t*)cpt_basic_string)->_t_vector._t_allocater, pv_varg,
        _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string), 1);

    return t_findpos;
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
    const basic_string_t* cpt_basic_string, const void* cpv_valuestring, size_t t_pos)
{
    return basic_string_find_last_of_subcstr(
        cpt_basic_string, cpv_valuestring, t_pos, NPOS);
}

size_t basic_string_find_last_of_subcstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring, size_t t_pos, size_t t_len)
{
    size_t t_typesize = 0;
    size_t t_stringlen = 0;
    size_t t_cstrlen = 0;
    size_t t_startpos = 0;
    size_t t_endpos = 0;
    char*  pc_string = NULL;
    char*  pc_cstr = NULL;
    bool_t t_less = false;
    bool_t t_great = false;

    assert(cpt_basic_string != NULL && cpv_valuestring != NULL);

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    t_stringlen = basic_string_length(cpt_basic_string);
    t_cstrlen = _get_valuestring_len(cpt_basic_string, cpv_valuestring);
    t_cstrlen = t_len < t_cstrlen ? t_len : t_cstrlen;

    if(t_pos > t_stringlen)
    {
        t_pos = t_stringlen;
    }

    /* find position is beyond the range of cpt_basic_string */
    if(basic_string_empty(cpt_basic_string))
    {
        return NPOS;
    }

    pc_string = (char*)basic_string_at(cpt_basic_string, 0);
    pc_cstr = (char*)cpv_valuestring;
    t_startpos = t_pos == t_stringlen ? t_pos - 1 : t_pos;
    for(;;)
    {
        t_endpos = 0;
        while(t_endpos != t_cstrlen)
        {
            t_less = t_great = t_typesize;
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                pc_string + t_startpos * t_typesize,
                pc_cstr + t_endpos * t_typesize, &t_less);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                pc_cstr + t_endpos * t_typesize,
                pc_string + t_startpos * t_typesize, &t_great);
            if(!t_less && !t_great)
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
    const basic_string_t* cpt_basic_string, const void* cpv_valuestring, size_t t_pos)
{
    return basic_string_find_last_not_of_subcstr(
        cpt_basic_string, cpv_valuestring, t_pos, NPOS);
}

size_t basic_string_find_last_not_of_subcstr(
    const basic_string_t* cpt_basic_string, const void* cpv_valuestring,
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
    bool_t t_great = false;

    assert(cpt_basic_string != NULL && cpv_valuestring != NULL);

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    t_stringlen = basic_string_length(cpt_basic_string);
    t_cstrlen = _get_valuestring_len(cpt_basic_string, cpv_valuestring);
    t_cstrlen = t_len < t_cstrlen ? t_len : t_cstrlen;

    if(t_pos > t_stringlen)
    {
        t_pos = t_stringlen;
    }

    /* find position is beyond the range of cpt_basic_string */
    if(basic_string_empty(cpt_basic_string))
    {
        return NPOS;
    }

    pc_string = (char*)basic_string_at(cpt_basic_string, 0);
    pc_cstr = (char*)cpv_valuestring;
    t_startpos = t_pos == t_stringlen ? t_pos - 1 : t_pos;
    for(;;)
    {
        t_endpos = 0;
        while(t_endpos != t_cstrlen)
        {
            t_less = t_great = t_typesize;
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                pc_string + t_startpos * t_typesize,
                pc_cstr + t_endpos * t_typesize, &t_less);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                pc_cstr + t_endpos * t_typesize,
                pc_string + t_startpos * t_typesize, &t_great);
            if(!t_less && !t_great)
            {
                break;
            }
            else
            {
                t_endpos++;
            }
        }

        if(t_endpos == t_cstrlen)
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

size_t _basic_string_find_last_not_of_elem(
    const basic_string_t* cpt_basic_string, size_t t_pos, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_pos);
    return _basic_string_find_last_not_of_elem_varg(
        cpt_basic_string, t_pos, val_elemlist);
}

size_t _basic_string_find_last_not_of_elem_varg(
    const basic_string_t* cpt_basic_string, size_t t_pos, va_list val_elemlist)
{
    size_t  t_typesize = 0;
    size_t  t_stringlen = 0;
    void*   pv_varg = NULL;
    char*   pc_string = NULL;
    size_t  t_findpos = 0;
    bool_t  t_result = false;
    bool_t  t_less = false;
    bool_t  t_great = false;

    assert(cpt_basic_string != NULL);

    t_stringlen = basic_string_length(cpt_basic_string);
    if(t_pos > t_stringlen)
    {
        t_pos = t_stringlen;
    }

    /* get element */
    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    pv_varg = allocate(
        &((basic_string_t*)cpt_basic_string)->_t_vector._t_allocater, t_typesize, 1);
    assert(pv_varg != NULL);
    t_result = t_typesize;
    _GET_BASIC_STRING_TYPE_INIT_FUNCTION(cpt_basic_string)(pv_varg, &t_result);
    assert(t_result);
    _type_get_varg_value(
        &((basic_string_t*)cpt_basic_string)->_t_vector._t_typeinfo, val_elemlist, pv_varg);

    /* find elemen */
    pc_string = (char*)basic_string_at(cpt_basic_string, 0);
    t_findpos = t_pos == t_stringlen ? t_pos - 1 : t_pos;
    for(;;)
    {
        t_less = t_great = t_typesize;
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pc_string + t_findpos * t_typesize, pv_varg, &t_less);
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pv_varg, pc_string + t_findpos * t_typesize, &t_great);
        if(!t_less && !t_great)
        {
            break;
        }
        else
        {
            if(t_findpos > 0)
            {
                t_findpos--;
            }
            else
            {
                t_findpos = NPOS;
                break;
            }
        }
    }

    deallocate(&((basic_string_t*)cpt_basic_string)->_t_vector._t_allocater, pv_varg,
        _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string), 1);

    return t_findpos;
}

/* modifiers */
void basic_string_clear(basic_string_t* pt_basic_string)
{
    assert(pt_basic_string != NULL);

    vector_clear(&pt_basic_string->_t_vector);
    vector_push_back(&pt_basic_string->_t_vector, 0x00);
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

    vector_reserve(&pt_basic_string->_t_vector, t_reservesize+1);
}

void _basic_string_resize(basic_string_t* pt_basic_string, size_t t_resize, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_resize);
    _basic_string_resize_varg(pt_basic_string, t_resize, val_elemlist);
}

void _basic_string_resize_varg(
    basic_string_t* pt_basic_string, size_t t_resize, va_list val_elemlist)
{
    assert(pt_basic_string != NULL);

    vector_pop_back(&pt_basic_string->_t_vector);
    _vector_resize_elem_varg(&pt_basic_string->_t_vector, t_resize, val_elemlist);
    vector_push_back(&pt_basic_string->_t_vector, 0x00);
}

void _basic_string_push_back(basic_string_t* pt_basic_string, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_basic_string);
    _basic_string_push_back_varg(pt_basic_string, val_elemlist);
}

void _basic_string_push_back_varg(basic_string_t* pt_basic_string, va_list val_elemlist)
{
    void*   pv_nullterminated = NULL;
    void*   pv_varg = NULL;
    char*   pc_dest = NULL;
    size_t  t_typesize = 0;
    bool_t  t_result = false;

    assert(pt_basic_string != NULL);

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
    pv_nullterminated = allocate(&pt_basic_string->_t_vector._t_allocater, t_typesize, 1);
    pv_varg = allocate(&pt_basic_string->_t_vector._t_allocater, t_typesize, 1);
    assert(pv_nullterminated != NULL && pv_varg != NULL);
    t_result = t_typesize;
    _GET_BASIC_STRING_TYPE_INIT_FUNCTION(pt_basic_string)(pv_varg, &t_result);
    assert(t_result);
    _type_get_varg_value(&pt_basic_string->_t_vector._t_typeinfo, val_elemlist, pv_varg);
    memset(pv_nullterminated, 0x00, t_typesize);

    if(memcmp(pv_nullterminated, pv_varg, t_typesize) != 0)
    {
        pc_dest = vector_at(
            &pt_basic_string->_t_vector, basic_string_size(pt_basic_string));
        assert(pc_dest != NULL);

        t_result = t_typesize;
        _GET_BASIC_STRING_TYPE_COPY_FUNCTION(pt_basic_string)(pc_dest, pv_varg, &t_result);
        assert(t_result);
        vector_push_back(&pt_basic_string->_t_vector, 0x00);
    }

    deallocate(&pt_basic_string->_t_vector._t_allocater, pv_nullterminated, t_typesize, 1);
    deallocate(&pt_basic_string->_t_vector._t_allocater, pv_varg, t_typesize, 1);
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
    basic_string_t* pt_basic_string, const void* cpv_valuestring)
{
    basic_string_assign_subcstr(pt_basic_string, cpv_valuestring, NPOS);
}

void basic_string_assign_subcstr(
    basic_string_t* pt_basic_string, const void* cpv_valuestring, size_t t_len)
{
    size_t t_length = 0;
    size_t t_index = 0;
    char*  pc_value = NULL;
    bool_t t_result = false;

    assert(pt_basic_string != NULL && cpv_valuestring != NULL);

    t_length = _get_valuestring_len(pt_basic_string, cpv_valuestring);
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
                (char*)cpv_valuestring + t_index*_GET_BASIC_STRING_TYPE_SIZE(pt_basic_string),
                &t_result);
            assert(t_result);
        }
    }

    /* add null-terminated node */
    vector_push_back(&pt_basic_string->_t_vector, 0x00);
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

void _basic_string_assign_elem(
    basic_string_t* pt_basic_string, size_t t_count, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_count);
    _basic_string_assign_elem_varg(pt_basic_string, t_count, val_elemlist);
}

void _basic_string_assign_elem_varg(
    basic_string_t* pt_basic_string, size_t t_count, va_list val_elemlist)
{
    size_t  t_index = 0;

    assert(pt_basic_string != NULL);

    vector_clear(&pt_basic_string->_t_vector);
    assert(vector_size(&pt_basic_string->_t_vector) == 0);

    for(t_index = 0; t_index < t_count; ++t_index)
    {
        _vector_push_back_varg(&pt_basic_string->_t_vector, val_elemlist);
    }

    /* add null-terminated node */
    vector_push_back(&pt_basic_string->_t_vector, 0x00);
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
    basic_string_t* pt_basic_string, const void* cpv_valuestring)
{
    basic_string_append_subcstr(pt_basic_string, cpv_valuestring, NPOS);
}

void basic_string_append_subcstr(
    basic_string_t* pt_basic_string, const void* cpv_valuestring, size_t t_len)
{
    size_t t_typesize = 0;
    size_t t_cstrlen = 0;
    size_t t_stringlen = 0;
    size_t t_index = 0;
    char*  pc_value = NULL;
    bool_t t_result = false;

    assert(pt_basic_string != NULL && cpv_valuestring != NULL);

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
    t_stringlen = basic_string_length(pt_basic_string);
    t_cstrlen = _get_valuestring_len(pt_basic_string, cpv_valuestring);
    t_len = t_len < t_cstrlen ? t_len : t_cstrlen;

    if(t_len > 0)
    {
        basic_string_resize(pt_basic_string, t_stringlen + t_len, 0xcc);
        pc_value = (char*)basic_string_at(pt_basic_string, t_stringlen);
        assert(pc_value != NULL);
        for(t_index = 0; t_index < t_len; ++t_index)
        {
            t_result = t_typesize;
            _GET_BASIC_STRING_TYPE_COPY_FUNCTION(pt_basic_string)(
                pc_value + t_index * t_typesize,
                (char*)cpv_valuestring + t_index * t_typesize, &t_result);
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

void _basic_string_append_elem(
    basic_string_t* pt_basic_string, size_t t_count, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_count);
    _basic_string_append_elem_varg(pt_basic_string, t_count, val_elemlist);
}

void _basic_string_append_elem_varg(
    basic_string_t* pt_basic_string, size_t t_count, va_list val_elemlist)
{
    _basic_string_resize_varg(
        pt_basic_string, basic_string_size(pt_basic_string) + t_count, val_elemlist);
}

/* insert */
basic_string_iterator_t _basic_string_insert(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_pos, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_pos);
    return _basic_string_insert_n_varg(pt_basic_string, t_pos, 1, val_elemlist);
}

basic_string_iterator_t _basic_string_insert_n(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_pos, size_t t_count, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_count);
    return _basic_string_insert_n_varg(pt_basic_string, t_pos, t_count, val_elemlist);
}

basic_string_iterator_t _basic_string_insert_n_varg(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_pos,
    size_t t_count, va_list val_elemlist)
{
    assert(pt_basic_string != NULL);

    return _vector_insert_n_varg(
        &pt_basic_string->_t_vector, t_pos, t_count, val_elemlist);
}

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
    basic_string_t* pt_basic_string, size_t t_pos, const void* cpv_valuestring)
{
    basic_string_insert_subcstr(pt_basic_string, t_pos, cpv_valuestring, NPOS);
}

void basic_string_insert_subcstr(
    basic_string_t* pt_basic_string, size_t t_pos,
    const void* cpv_valuestring, size_t t_len)
{
    basic_string_t* pt_string;

    assert(pt_basic_string != NULL && cpv_valuestring != NULL);

    pt_string = _create_basic_string(_GET_BASIC_STRING_TYPE_NAME(pt_basic_string));

    basic_string_init_subcstr(pt_string, cpv_valuestring, t_len);

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

void _basic_string_insert_elem(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_count, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_count);
    _basic_string_insert_elem_varg(pt_basic_string, t_pos, t_count, val_elemlist);
}

void _basic_string_insert_elem_varg(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_count, va_list val_elemlist)
{
    basic_string_iterator_t t_insert;

    assert(pt_basic_string != NULL);
    assert(t_pos <= basic_string_size(pt_basic_string));

    t_insert = basic_string_begin(pt_basic_string);
    t_insert = iterator_next_n(t_insert, t_pos);
    _GET_VECTOR_CONTAINER_TYPE(t_insert) = _VECTOR_CONTAINER;
    _vector_insert_n_varg(&pt_basic_string->_t_vector, t_insert, t_count, val_elemlist);
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

    assert(t_pos < basic_string_size(pt_basic_string));

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

    assert(t_pos < basic_string_size(pt_basic_string));

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

    assert(t_pos < basic_string_size(pt_basic_string));

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
    const void* cpv_valuestring)
{
    basic_string_iterator_t t_begin = basic_string_begin(pt_basic_string);
    basic_string_iterator_t t_end   = basic_string_begin(pt_basic_string);

    assert(t_pos < basic_string_size(pt_basic_string));

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
        pt_basic_string, t_begin, t_end, cpv_valuestring);
}

void basic_string_replace_subcstr(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_len,
    const void* cpv_valuestring, size_t t_length)
{
    basic_string_iterator_t t_begin = basic_string_begin(pt_basic_string);
    basic_string_iterator_t t_end   = basic_string_begin(pt_basic_string);

    assert(t_pos < basic_string_size(pt_basic_string));

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
        pt_basic_string, t_begin, t_end, cpv_valuestring, t_length);
}

void _basic_string_replace_elem(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_len, size_t t_count, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_count);
    _basic_string_replace_elem_varg(pt_basic_string, t_pos, t_len, t_count, val_elemlist);
}

void _basic_string_replace_elem_varg(
    basic_string_t* pt_basic_string, size_t t_pos, 
    size_t t_len, size_t t_count, va_list val_elemlist)
{
    basic_string_iterator_t t_begin = basic_string_begin(pt_basic_string);
    basic_string_iterator_t t_end   = basic_string_begin(pt_basic_string);

    assert(t_pos < basic_string_size(pt_basic_string));

    t_begin = iterator_next_n(t_begin, t_pos);
    if(t_len == NPOS || t_pos + t_len >= basic_string_size(pt_basic_string))
    {
        t_end = basic_string_end(pt_basic_string);
    }
    else
    {
        t_end = iterator_next_n(t_end, t_pos + t_len);
    }
    _basic_string_range_replace_elem_varg(
        pt_basic_string, t_begin, t_end, t_count, val_elemlist);
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
    basic_string_iterator_t t_end, const void* cpv_valuestring)
{
    basic_string_iterator_t t_iterator = 
        basic_string_erase_range(pt_basic_string, t_begin, t_end);
    basic_string_insert_cstr(
        pt_basic_string,
        iterator_distance(basic_string_begin(pt_basic_string), t_iterator),
        cpv_valuestring);
}

void basic_string_range_replace_subcstr(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end, const void* cpv_valuestring, size_t t_len)
{
    basic_string_iterator_t t_iterator = 
        basic_string_erase_range(pt_basic_string, t_begin, t_end);
    basic_string_insert_subcstr(
        pt_basic_string,
        iterator_distance(basic_string_begin(pt_basic_string), t_iterator),
        cpv_valuestring, t_len);
}

void _basic_string_range_replace_elem(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end, size_t t_count, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_count);
    _basic_string_range_replace_elem_varg(
        pt_basic_string, t_begin, t_end, t_count, val_elemlist);
}

void _basic_string_range_replace_elem_varg(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end, size_t t_count, va_list val_elemlist)
{
    basic_string_iterator_t t_iterator = basic_string_erase_range(
        pt_basic_string, t_begin, t_end);
    size_t t_pos = (size_t)iterator_distance(
        basic_string_begin(pt_basic_string), t_iterator);

    _basic_string_insert_elem_varg(pt_basic_string, t_pos, t_count, val_elemlist);
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
#ifndef NDEBUG
static bool_t _iterator_belong_to_basic_string(
    const basic_string_t* cpt_basic_string,
    basic_string_iterator_t t_iter)
{
    assert(cpt_basic_string != NULL);
    assert(_GET_BASIC_STRING_CONTAINER_TYPE(t_iter) == _BASIC_STRING_CONTAINER &&
           _GET_BASIC_STRING_ITERATOR_TYPE(t_iter) == _RANDOM_ACCESS_ITERATOR &&
           _GET_BASIC_STRING_CONTAINER(t_iter) == cpt_basic_string);

    return true;
}

static bool_t _basic_string_same_type(
    const basic_string_t* cpt_basic_stringfirst,
    const basic_string_t* cpt_basic_stringsecond)
{
    assert(cpt_basic_stringfirst != NULL && cpt_basic_stringsecond != NULL);
    return _type_is_same(_GET_BASIC_STRING_TYPE_NAME(cpt_basic_stringfirst),
                         _GET_BASIC_STRING_TYPE_NAME(cpt_basic_stringsecond)) &&
           (cpt_basic_stringfirst->_t_vector._t_typeinfo._pt_type ==
            cpt_basic_stringsecond->_t_vector._t_typeinfo._pt_type);
}
#endif /* NDEBUG */

static size_t _get_valuestring_len(
    const basic_string_t* cpt_basic_string, const void* cpv_valuestring)
{
    size_t t_typesize = 0;

    assert(cpt_basic_string != NULL && cpv_valuestring != NULL);

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    /* char type */
    if(strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string),
        _CHAR_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        assert(t_typesize == 1);
        return strlen(cpv_valuestring);
    }
    else
    {
        size_t t_len = 0;
        char*  pc_nullterminated = NULL;
        bool_t t_less = false;
        bool_t t_great = false;

        pc_nullterminated = (char*)allocate(
            &((basic_string_t*)cpt_basic_string)->_t_vector._t_allocater, t_typesize, 1);
        assert(pc_nullterminated != NULL);
        memset(pc_nullterminated, 0x00, t_typesize);

        t_less = t_great = t_typesize;
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            cpv_valuestring, pc_nullterminated, &t_less);
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pc_nullterminated, cpv_valuestring, &t_great);
        while(t_less || t_great)
        {
            t_len++;

            t_less = t_great = t_typesize;
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                (char*)cpv_valuestring+t_len*t_typesize, pc_nullterminated, &t_less);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                pc_nullterminated, (char*)cpv_valuestring+t_len*t_typesize, &t_great);
        }
        
        deallocate(&((basic_string_t*)cpt_basic_string)->_t_vector._t_allocater,
            pc_nullterminated, t_typesize, 1);

        return t_len;
    }
}

/** eof **/

