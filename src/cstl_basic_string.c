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
 *  Author Email: activesys.wb@gmail.com
 *                activesys@sina.com.cn
 */

/** include section **/
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "cstl_types.h"
#include "cstl_alloc.h"
#include "cstl_iterator.h"
#include "cvector.h"

#include "cstl_basic_string_iterator.h"
#include "cstl_basic_string_private.h"
#include "cstl_basic_string.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
#ifndef NDEBUG
/*
 *  Functionname: _iterator_belong_to_basic_string
 *    Parameters: in) cpt_basic_string: const basic_string_t*
 *                    basic_string pointer.
 *                in) cpt_iterator: const basic_string_iterator_t*
 *                    basic_string iterator pointer.
 *       Returns: bool_t
 *   Description: test the iterator is valid one belong to the basic_string.
 */
static bool_t _iterator_belong_to_basic_string(
    const basic_string_t* cpt_basic_string, 
    const basic_string_iterator_t* cpt_iterator);

/*
 *  Functionname: _same_basic_string_type
 *    Parameters: in) cpt_basic_stringfirst: const basic_string_t*
 *                    first basic_string pointer.
 *                in) cpt_basic_stringsecond: const basic_string_t*
 *                    second basic_string pointer.
 *       Returns: bool_t
 *   Description: test the two basic_string is have the same type.
 */
static bool_t _same_basic_string_type(
    const basic_string_t* cpt_basic_stringfirst, 
    const basic_string_t* cpt_basic_stringsecond);
#endif /* NDEBUG */

/*
 *  Functionname: _get_valuestring_len
 *    Parameters: in) cpv_valuestring: const void*
 *                    value string.
 *                in) t_typesize: size_t
 *                    type size,
 *                in) s_typename: const char*
 *                    type name.
 *       Returns: size_t
 *   Description: get the value string length.
 */
static size_t _get_valuestring_len(
    const void* cpv_valuestring, size_t t_typesize, const char* s_typename);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* basic_string iterator function */
basic_string_iterator_t create_basic_string_iterator(void)
{
    basic_string_iterator_t t_newiterator = create_vector_iterator();
    _GET_BASIC_STRING_CONTAINER_TYPE(&t_newiterator) = _BASIC_STRING_CONTAINER;

    return t_newiterator;
}

bool_t _basic_string_iterator_equal(
    const struct _tagbasicstring* cpt_basic_string,
    const basic_string_iterator_t* cpt_iterator,
    basic_string_iterator_t t_iterator)
{
    bool_t t_result;

    assert(_iterator_belong_to_basic_string(cpt_basic_string, cpt_iterator));
    assert(_iterator_belong_to_basic_string(cpt_basic_string, &t_iterator));

    _GET_VECTOR_CONTAINER_TYPE(&t_iterator) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE((vector_iterator_t*)cpt_iterator) = 
        _VECTOR_CONTAINER;

    t_result = _vector_iterator_equal(
        &cpt_basic_string->_t_vector, cpt_iterator, t_iterator);

    _GET_BASIC_STRING_CONTAINER_TYPE(&t_iterator) = _BASIC_STRING_CONTAINER;
    _GET_BASIC_STRING_CONTAINER_TYPE((basic_string_iterator_t*)cpt_iterator) =
        _BASIC_STRING_CONTAINER;

    return t_result;
}

void _basic_string_iterator_get_value(
    const struct _tagbasicstring* cpt_basic_string,
    const basic_string_iterator_t* cpt_iterator,
    void* pv_value)
{
    assert(_iterator_belong_to_basic_string(cpt_basic_string, cpt_iterator));
    assert(!iterator_equal(cpt_iterator, basic_string_end(cpt_basic_string)));

    _GET_VECTOR_CONTAINER_TYPE((vector_iterator_t*)cpt_iterator) = 
        _VECTOR_CONTAINER;

    _vector_iterator_get_value(
        &cpt_basic_string->_t_vector, cpt_iterator, pv_value);

    _GET_BASIC_STRING_CONTAINER_TYPE((basic_string_iterator_t*)cpt_iterator) = 
        _BASIC_STRING_CONTAINER;
}

void _basic_string_iterator_set_value(
    const struct _tagbasicstring* cpt_basic_string,
    const basic_string_iterator_t* cpt_iterator,
    const void* cpv_value)
{
    assert(_iterator_belong_to_basic_string(cpt_basic_string, cpt_iterator));
    assert(!iterator_equal(cpt_iterator, basic_string_end(cpt_basic_string)));

    _GET_VECTOR_CONTAINER_TYPE((vector_iterator_t*)cpt_iterator) = 
        _VECTOR_CONTAINER;

    _vector_iterator_set_value(
        &cpt_basic_string->_t_vector, cpt_iterator, cpv_value);

    _GET_BASIC_STRING_CONTAINER_TYPE((basic_string_iterator_t*)cpt_iterator) = 
        _BASIC_STRING_CONTAINER;
}

const void* _basic_string_iterator_get_pointer(
    const struct _tagbasicstring* cpt_basic_string,
    const basic_string_iterator_t* cpt_iterator)
{
    void* pv_pointer = NULL;

    assert(_iterator_belong_to_basic_string(cpt_basic_string, cpt_iterator));
    assert(!iterator_equal(cpt_iterator, basic_string_end(cpt_basic_string)));

    _GET_VECTOR_CONTAINER_TYPE((vector_iterator_t*)cpt_iterator) = 
        _VECTOR_CONTAINER;

    pv_pointer = (void*)_vector_iterator_get_pointer(
        &cpt_basic_string->_t_vector, cpt_iterator);

    _GET_BASIC_STRING_CONTAINER_TYPE((basic_string_iterator_t*)cpt_iterator) = 
        _BASIC_STRING_CONTAINER;

    return pv_pointer;
}

void _basic_string_iterator_next(
    const struct _tagbasicstring* cpt_basic_string,
    basic_string_iterator_t* pt_iterator)
{
    assert(_iterator_belong_to_basic_string(cpt_basic_string, pt_iterator));
    assert(!iterator_equal(pt_iterator, basic_string_end(cpt_basic_string)));

    _GET_VECTOR_CONTAINER_TYPE((vector_iterator_t*)pt_iterator) = 
        _VECTOR_CONTAINER;

    _vector_iterator_next(&cpt_basic_string->_t_vector, pt_iterator);

    _GET_BASIC_STRING_CONTAINER_TYPE((basic_string_iterator_t*)pt_iterator) = 
        _BASIC_STRING_CONTAINER;
}

void _basic_string_iterator_prev(
    const struct _tagbasicstring* cpt_basic_string,
    basic_string_iterator_t* pt_iterator)
{
    assert(_iterator_belong_to_basic_string(cpt_basic_string, pt_iterator));
    assert(!iterator_equal(pt_iterator, basic_string_begin(cpt_basic_string)));

    _GET_VECTOR_CONTAINER_TYPE((vector_iterator_t*)pt_iterator) = 
        _VECTOR_CONTAINER;

    _vector_iterator_prev(&cpt_basic_string->_t_vector, pt_iterator);

    _GET_BASIC_STRING_CONTAINER_TYPE((basic_string_iterator_t*)pt_iterator) = 
        _BASIC_STRING_CONTAINER;
}

void* _basic_string_iterator_at(
    const struct _tagbasicstring* cpt_basic_string,
    const basic_string_iterator_t* cpt_iterator,
    unsigned int un_index)
{
    void* pv_value = NULL;
    assert(_iterator_belong_to_basic_string(cpt_basic_string, cpt_iterator));

    _GET_VECTOR_CONTAINER_TYPE((vector_iterator_t*)cpt_iterator) = 
        _VECTOR_CONTAINER;

    pv_value = _vector_iterator_at(
        &cpt_basic_string->_t_vector, cpt_iterator, un_index);
    assert(pv_value != NULL);

    _GET_BASIC_STRING_CONTAINER_TYPE((basic_string_iterator_t*)cpt_iterator) = 
        _BASIC_STRING_CONTAINER;

    return pv_value;
}

void _basic_string_iterator_next_n(
    const struct _tagbasicstring* cpt_basic_string,
    basic_string_iterator_t* pt_iterator,
    int n_step)
{
    assert(_iterator_belong_to_basic_string(cpt_basic_string, pt_iterator));
    assert(!iterator_equal(pt_iterator, basic_string_end(cpt_basic_string)));

    _GET_VECTOR_CONTAINER_TYPE((vector_iterator_t*)pt_iterator) = 
        _VECTOR_CONTAINER;

    _vector_iterator_next_n(&cpt_basic_string->_t_vector, pt_iterator, n_step);

    _GET_BASIC_STRING_CONTAINER_TYPE((basic_string_iterator_t*)pt_iterator) = 
        _BASIC_STRING_CONTAINER;
}

void _basic_string_iterator_prev_n(
    const struct _tagbasicstring* cpt_basic_string,
    basic_string_iterator_t* pt_iterator,
    int n_step)
{
    assert(_iterator_belong_to_basic_string(cpt_basic_string, pt_iterator));
    assert(!iterator_equal(pt_iterator, basic_string_begin(cpt_basic_string)));

    _GET_VECTOR_CONTAINER_TYPE((vector_iterator_t*)pt_iterator) = 
        _VECTOR_CONTAINER;

    _vector_iterator_prev_n(&cpt_basic_string->_t_vector, pt_iterator, n_step);

    _GET_BASIC_STRING_CONTAINER_TYPE((basic_string_iterator_t*)pt_iterator) = 
        _BASIC_STRING_CONTAINER;
}

int _basic_string_iterator_minus(
    const struct _tagbasicstring* cpt_basic_string,
    const basic_string_iterator_t* cpt_iterator,
    basic_string_iterator_t t_iterator)
{
    int n_distance = 0;

    assert(_iterator_belong_to_basic_string(cpt_basic_string, cpt_iterator));
    assert(_iterator_belong_to_basic_string(cpt_basic_string, &t_iterator));

    _GET_VECTOR_CONTAINER_TYPE(&t_iterator) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE((vector_iterator_t*)cpt_iterator) = 
        _VECTOR_CONTAINER;

    n_distance = _vector_iterator_minus(
        &cpt_basic_string->_t_vector, cpt_iterator, t_iterator);

    _GET_BASIC_STRING_CONTAINER_TYPE(&t_iterator) = _BASIC_STRING_CONTAINER;
    _GET_BASIC_STRING_CONTAINER_TYPE((basic_string_iterator_t*)cpt_iterator) =
        _BASIC_STRING_CONTAINER;

    return n_distance;   
}

bool_t _basic_string_iterator_less(
    const struct _tagbasicstring* cpt_basic_string,
    const basic_string_iterator_t* cpt_iterator,
    basic_string_iterator_t t_iterator)
{
    bool_t t_result;

    assert(_iterator_belong_to_basic_string(cpt_basic_string, cpt_iterator));
    assert(_iterator_belong_to_basic_string(cpt_basic_string, &t_iterator));

    _GET_VECTOR_CONTAINER_TYPE(&t_iterator) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE((vector_iterator_t*)cpt_iterator) = 
        _VECTOR_CONTAINER;

    t_result = _vector_iterator_less(
        &cpt_basic_string->_t_vector, cpt_iterator, t_iterator);

    _GET_BASIC_STRING_CONTAINER_TYPE(&t_iterator) = _BASIC_STRING_CONTAINER;
    _GET_BASIC_STRING_CONTAINER_TYPE((basic_string_iterator_t*)cpt_iterator) = 
        _BASIC_STRING_CONTAINER;

    return t_result;   
}

bool_t _basic_string_iterator_before(
    const basic_string_iterator_t* cpt_iteratorfirst,
    const basic_string_iterator_t* cpt_iteratorsecond)
{
    bool_t t_result;

    assert(cpt_iteratorfirst != NULL && cpt_iteratorsecond != NULL);

    _GET_VECTOR_CONTAINER_TYPE((vector_iterator_t*)cpt_iteratorfirst) = 
        _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE((vector_iterator_t*)cpt_iteratorsecond) = 
        _VECTOR_CONTAINER;

    t_result = _vector_iterator_before(cpt_iteratorfirst, cpt_iteratorsecond);

    _GET_BASIC_STRING_CONTAINER_TYPE((basic_string_iterator_t*)cpt_iteratorfirst) = 
        _BASIC_STRING_CONTAINER;
    _GET_BASIC_STRING_CONTAINER_TYPE((basic_string_iterator_t*)cpt_iteratorsecond) = 
        _BASIC_STRING_CONTAINER;

    return t_result;
}

/* basic_string private function */
basic_string_t _create_basic_string(size_t t_typesize, const char* s_typename)
{
    basic_string_t t_new_basic_string;
    char           ac_basicstringtypename[_ELEM_TYPE_NAME_SIZE+1];
    char           ac_unifytypename[_ELEM_TYPE_NAME_SIZE+1];

    assert(s_typename != NULL);

    memset(ac_unifytypename, '\0', _ELEM_TYPE_NAME_SIZE+1);
    strncpy(ac_unifytypename, s_typename, _ELEM_TYPE_NAME_SIZE);
    _unify_types(t_typesize, ac_unifytypename);

    memset(ac_basicstringtypename, '\0', _ELEM_TYPE_NAME_SIZE+1);
    strncpy(ac_basicstringtypename, _BASIC_STRING_IDENTIFY, _ELEM_TYPE_NAME_SIZE);
    strcat(ac_basicstringtypename, _BASIC_STRING_LEFT_BRACKET);
    strcat(ac_basicstringtypename, ac_unifytypename);
    strcat(ac_basicstringtypename, _BASIC_STRING_RIGHT_BRACKET);

    t_new_basic_string._t_vector = 
        _create_vector(t_typesize, ac_basicstringtypename);

    return t_new_basic_string;
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
    basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end)
{
    assert(pt_basic_string != NULL);
    assert(
        _GET_BASIC_STRING_CONTAINER(&t_begin) != pt_basic_string &&
        _GET_BASIC_STRING_CONTAINER(&t_end) != pt_basic_string);

    _GET_VECTOR_CONTAINER_TYPE(&t_begin) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE(&t_end) = _VECTOR_CONTAINER;

    vector_init_copy_range(&pt_basic_string->_t_vector, t_begin, t_end);
    vector_push_back(&pt_basic_string->_t_vector, 0x00);
}

void basic_string_init_copy_substring(
    basic_string_t* pt_basic_string,
    const basic_string_t* cpt_basic_string_src,
    size_t t_pos,
    size_t t_len)
{
    basic_string_iterator_t t_begin;
    basic_string_iterator_t t_end;

    assert(pt_basic_string != NULL && cpt_basic_string_src != NULL);
    assert(t_pos < basic_string_size(cpt_basic_string_src));

    t_begin = basic_string_begin(cpt_basic_string_src);
    iterator_next_n(&t_begin, t_pos);

    if(t_len == NPOS || 
       t_len + t_pos >= basic_string_size(cpt_basic_string_src))
    {
        t_end = basic_string_end(cpt_basic_string_src);
    }
    else
    {
        t_end = basic_string_begin(cpt_basic_string_src);
        iterator_next_n(&t_end, t_pos + t_len);
    }

    _GET_VECTOR_CONTAINER_TYPE(&t_begin) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE(&t_end) = _VECTOR_CONTAINER;

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

    assert(pt_basic_string != NULL);

    t_length = _get_valuestring_len(
        cpv_valuestring, 
        pt_basic_string->_t_vector._t_typesize, 
        pt_basic_string->_t_vector._sz_typename);
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
           memcpy(
                pc_value + t_index * pt_basic_string->_t_vector._t_typesize, 
                (char*)cpv_valuestring + t_index * pt_basic_string->_t_vector._t_typesize,
                pt_basic_string->_t_vector._t_typesize);
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
    size_t  t_index = 0;
    char*   pc_value = NULL;

    assert(pt_basic_string != NULL);

    vector_init(&pt_basic_string->_t_vector);
    vector_resize(&pt_basic_string->_t_vector, t_count);
    assert(vector_size(&pt_basic_string->_t_vector) == t_count);

    if(t_count > 0)
    {
        pc_value = (char*)vector_at(&pt_basic_string->_t_vector, 0);
        assert(pc_value != NULL);
        for(t_index = 0; t_index < t_count; ++t_index)
        {
            _get_varg_value(
                pc_value + t_index * pt_basic_string->_t_vector._t_typesize,
                val_elemlist,
                pt_basic_string->_t_vector._t_typesize,
                pt_basic_string->_t_vector._sz_typename);
        }
    }

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
    void* pv_buffer,
    size_t t_copysize,
    size_t t_copypos)
{
    void*  pv_copypos = NULL;
    size_t t_size = 0;

    assert(cpt_basic_string != NULL && pv_buffer != NULL);

    t_size = basic_string_size(cpt_basic_string);
    assert(t_size > t_copypos);
    t_size = (t_size - t_copypos) < t_copysize ?
        t_size - t_copypos : t_copysize;

    memset(
        pv_buffer, 0x00, 
        (t_size+1)*cpt_basic_string->_t_vector._t_typesize);
    pv_copypos = basic_string_at(cpt_basic_string, t_copypos);
    memcpy(
        pv_buffer, pv_copypos, 
        t_size*cpt_basic_string->_t_vector._t_typesize);

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

    return (size_t)(-1) / cpt_basic_string->_t_vector._t_typesize - 1;
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
    assert(_same_basic_string_type(cpt_basic_stringfirst, cpt_basic_stringsecond));

    return basic_string_compare_substring_string(
        cpt_basic_stringfirst, 0, NPOS, cpt_basic_stringsecond);
}

int basic_string_compare_substring_string(
    const basic_string_t* cpt_basic_stringfirst,
    size_t t_firstpos,
    size_t t_firstlen,
    const basic_string_t* cpt_basic_stringsecond)
{
    assert(_same_basic_string_type(cpt_basic_stringfirst, cpt_basic_stringsecond));

    return basic_string_compare_substring_substring(
        cpt_basic_stringfirst,
        t_firstpos,
        t_firstlen,
        cpt_basic_stringsecond,
        0,
        NPOS);
}

int basic_string_compare_substring_substring(
    const basic_string_t* cpt_basic_stringfirst,
    size_t t_firstpos,
    size_t t_firstlen,
    const basic_string_t* cpt_basic_stringsecond,
    size_t t_secondpos,
    size_t t_secondlen)
{
    assert(_same_basic_string_type(cpt_basic_stringfirst, cpt_basic_stringsecond));
    assert(t_secondpos < basic_string_size(cpt_basic_stringsecond));

    return basic_string_compare_substring_subcstr(
        cpt_basic_stringfirst,
        t_firstpos,
        t_firstlen,
        basic_string_at(cpt_basic_stringsecond, t_secondpos),
        t_secondlen);
}

int basic_string_compare_cstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring)
{
    return basic_string_compare_substring_subcstr(
        cpt_basic_string, 0, NPOS, cpv_valuestring, NPOS);
}

int basic_string_compare_substring_cstr(
    const basic_string_t* cpt_basic_string,
    size_t t_stringpos,
    size_t t_stringlen,
    const void* cpv_valuestring)
{
    return basic_string_compare_substring_subcstr(
        cpt_basic_string, t_stringpos, t_stringlen, cpv_valuestring, NPOS);
}

int basic_string_compare_substring_subcstr(
    const basic_string_t* cpt_basic_string,
    size_t t_stringpos,
    size_t t_stringlen,
    const void* cpv_valuestring,
    size_t t_valuestringlen)
{
    size_t t_cmplen = 0;
    size_t t_index = 0;
    char*  pc_string = NULL;
    char*  pc_value = NULL;
    int    n_cmpresult = 0;
    size_t t_stringlentmp = 0;
    size_t t_valuestringlentmp = 0;

    assert(cpt_basic_string != NULL && cpv_valuestring != NULL);
    assert(t_stringpos < basic_string_size(cpt_basic_string));

    /* get actual string length and value string length */
    t_stringlentmp = basic_string_size(cpt_basic_string) - t_stringpos;
    t_valuestringlentmp = 
        _get_valuestring_len(
            cpv_valuestring, 
            cpt_basic_string->_t_vector._t_typesize,
            cpt_basic_string->_t_vector._sz_typename);
    t_stringlen = 
        t_stringlen < t_stringlentmp ? 
        t_stringlen : t_stringlentmp;
    t_valuestringlen = 
        t_valuestringlen < t_valuestringlentmp ? 
        t_valuestringlen : t_valuestringlentmp;
    t_cmplen = 
        t_stringlen < t_valuestringlen ? 
        t_stringlen : t_valuestringlen;

    pc_string = (char*)basic_string_at(cpt_basic_string, t_stringpos);
    pc_value = (char*)cpv_valuestring;
    assert(pc_string != NULL && pc_value != NULL);

    if(cpt_basic_string->_t_vector._pfun_cmp != NULL)
    {
        for(t_index = 0; t_index < t_cmplen; ++t_index)
        {
            if((n_cmpresult = 
                (*cpt_basic_string->_t_vector._pfun_cmp)(pc_string, pc_value)) != 0)
            {
                return n_cmpresult;
            }
            else
            {
                pc_string += cpt_basic_string->_t_vector._t_typesize;
                pc_value += cpt_basic_string->_t_vector._t_typesize;
            }
        }
    }
    else
    {
        for(t_index = 0; t_index < t_cmplen; ++t_index)
        {
            if((n_cmpresult = memcmp(
                pc_string, pc_value, cpt_basic_string->_t_vector._t_typesize)) != 0)
            {
                return n_cmpresult;
            }
            else
            {
                pc_string += cpt_basic_string->_t_vector._t_typesize;
                pc_value += cpt_basic_string->_t_vector._t_typesize;
            }
        }
    }

    return t_stringlen < t_valuestringlen ? -1 : 
          (t_stringlen > t_valuestringlen ? 1 : 0);
}

/* substring and concatenation */
basic_string_t basic_string_substr(
    const basic_string_t* cpt_basic_string, size_t t_pos, size_t t_len)
{
    basic_string_t t_substr;

    assert(cpt_basic_string != NULL);
    assert(t_pos < basic_string_size(cpt_basic_string));

    t_substr._t_vector = _create_vector(
        cpt_basic_string->_t_vector._t_typesize,
        cpt_basic_string->_t_vector._sz_typename);
    basic_string_init_subcstr(
        &t_substr, basic_string_at(cpt_basic_string, t_pos), t_len);

    return t_substr;
}

void basic_string_connect(
    basic_string_t* pt_basic_string, const basic_string_t* cpt_basic_string_src)
{
    size_t t_destlen = 0;
    size_t t_srclen = 0;
    char*  pc_dest = NULL;
    char*  pc_src = NULL;

    assert(_same_basic_string_type(pt_basic_string, cpt_basic_string_src));

    t_destlen = basic_string_size(pt_basic_string);
    t_srclen = basic_string_size(cpt_basic_string_src);

    if(t_srclen > 0)
    {
        vector_resize(&pt_basic_string->_t_vector, t_destlen + t_srclen);

        pc_dest = (char*)vector_at(&pt_basic_string->_t_vector, t_destlen);
        pc_src = (char*)vector_at(&cpt_basic_string_src->_t_vector, 0);
        assert(pc_dest != NULL && pc_src != NULL);

        memcpy(pc_dest, pc_src, t_srclen * pt_basic_string->_t_vector._t_typesize);

        /* add null-terminated */
        vector_push_back(&pt_basic_string->_t_vector, 0x00);
    }
}

void basic_string_connect_cstr(
    basic_string_t* pt_basic_string, const void* cpv_valuestring)
{
    size_t t_destlen = 0;
    size_t t_srclen = 0;
    char*  pc_dest = NULL;
    char*  pc_src = NULL;

    assert(pt_basic_string != NULL && cpv_valuestring != NULL);

    t_destlen = basic_string_size(pt_basic_string);
    t_srclen = _get_valuestring_len(
        cpv_valuestring, 
        pt_basic_string->_t_vector._t_typesize,
        pt_basic_string->_t_vector._sz_typename);

    if(t_srclen > 0)
    {
        vector_resize(&pt_basic_string->_t_vector, t_destlen + t_srclen);

        pc_dest = (char*)vector_at(&pt_basic_string->_t_vector, t_destlen);
        pc_src = (char*)cpv_valuestring;
        assert(pc_dest != NULL && pc_src != NULL);

        memcpy(pc_dest, pc_src, t_srclen * pt_basic_string->_t_vector._t_typesize);

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
    char*   pc_dest = NULL;
    char*   pc_value = NULL;
    char*   pc_nullterminated = NULL;

    assert(pt_basic_string != NULL);

    pc_dest = (char*)vector_at(
        &pt_basic_string->_t_vector, basic_string_size(pt_basic_string));
    assert(pc_dest != NULL);

    pc_value = (char*)malloc(pt_basic_string->_t_vector._t_typesize);
    pc_nullterminated = (char*)malloc(pt_basic_string->_t_vector._t_typesize);
    if(pc_value == NULL || pc_nullterminated == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_nullterminated, 0x00, pt_basic_string->_t_vector._t_typesize);
    }

    _get_varg_value(
        pc_value,
        val_elemlist,
        pt_basic_string->_t_vector._t_typesize,
        pt_basic_string->_t_vector._sz_typename);
    /* check input element is the null-terminated node */
    if(memcmp(pc_value, pc_nullterminated, pt_basic_string->_t_vector._t_typesize) != 0)
    {
        memcpy(pc_dest, pc_value, pt_basic_string->_t_vector._t_typesize);
        /* add null-terminated */
        vector_push_back(&pt_basic_string->_t_vector, 0x00);
    }

    free(pc_value);
    free(pc_nullterminated);
    pc_value = NULL;
    pc_nullterminated = NULL;
}

/* iterator support */
basic_string_iterator_t basic_string_begin(const basic_string_t* cpt_basic_string)
{
    basic_string_iterator_t t_newiterator;

    assert(cpt_basic_string != NULL);

    t_newiterator = vector_begin(&cpt_basic_string->_t_vector);
    _GET_BASIC_STRING_CONTAINER_TYPE(&t_newiterator) = _BASIC_STRING_CONTAINER;

    return t_newiterator;
}

basic_string_iterator_t basic_string_end(const basic_string_t* cpt_basic_string)
{
    basic_string_iterator_t t_newiterator;

    assert(cpt_basic_string != NULL);
    assert(vector_size(&cpt_basic_string->_t_vector) > 0);

    t_newiterator = vector_rbegin(&cpt_basic_string->_t_vector);
    _GET_BASIC_STRING_CONTAINER_TYPE(&t_newiterator) = _BASIC_STRING_CONTAINER;

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
        iterator_prev(&t_newiterator);
        _GET_BASIC_STRING_CONTAINER_TYPE(&t_newiterator) = _BASIC_STRING_CONTAINER;
    }

    return t_newiterator;
}

basic_string_reverse_iterator_t basic_string_rend(const basic_string_t* cpt_basic_string)
{
    basic_string_iterator_t t_newiterator;

    assert(cpt_basic_string != NULL);

    t_newiterator = vector_rend(&cpt_basic_string->_t_vector);
    _GET_BASIC_STRING_CONTAINER_TYPE(&t_newiterator) = _BASIC_STRING_CONTAINER;

    return t_newiterator;
}

/* find function series */
size_t basic_string_find(
    const basic_string_t* cpt_basic_string,
    const basic_string_t* cpt_basic_string_find,
    size_t t_pos)
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
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring,
    size_t t_pos)
{
    return basic_string_find_subcstr(cpt_basic_string, cpv_valuestring, t_pos, NPOS);
}

size_t basic_string_find_subcstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring,
    size_t t_pos,
    size_t t_len)
{
    size_t t_typesize = 0;
    size_t t_stringlen = 0;
    size_t t_cstrlen = 0;
    size_t t_startpos = 0;
    size_t t_endpos = 0;
    char*  pc_string = NULL;
    char*  pc_cstr = NULL;

    assert(cpt_basic_string != NULL && cpv_valuestring != NULL);

    t_typesize = cpt_basic_string->_t_vector._t_typesize;
    t_stringlen = basic_string_length(cpt_basic_string);
    t_cstrlen = _get_valuestring_len(
        cpv_valuestring, t_typesize, cpt_basic_string->_t_vector._sz_typename);
    t_cstrlen = t_len < t_cstrlen ? t_len : t_cstrlen;

    /* find position is beyond the range of cpt_basic_string */
    if(basic_string_empty(cpt_basic_string) ||
       t_pos > basic_string_size(cpt_basic_string) ||
       t_pos + t_cstrlen*t_typesize > basic_string_size(cpt_basic_string))
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
    if(cpt_basic_string->_t_vector._pfun_cmp != NULL)
    {
        t_startpos = t_pos;
        while(t_startpos != t_stringlen)
        {
            if(cpt_basic_string->_t_vector._pfun_cmp(
                pc_string + t_startpos * t_typesize, pc_cstr) == 0)
            {
                t_endpos = 0;
                while(t_endpos + t_startpos != t_stringlen && t_endpos != t_cstrlen)
                {
                    if(cpt_basic_string->_t_vector._pfun_cmp(
                        pc_string + (t_endpos+t_startpos) * t_typesize,
                        pc_cstr + t_endpos * t_typesize) == 0)
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
    else
    {
        t_startpos = t_pos;
        while(t_startpos != t_stringlen)
        {
            if(memcmp(pc_string + t_startpos * t_typesize, pc_cstr, t_typesize) == 0)
            {
                t_endpos = 0;
                while(t_endpos + t_startpos != t_stringlen && t_endpos != t_cstrlen)
                {
                    if(memcmp(
                        pc_string + (t_endpos+t_startpos) * t_typesize,
                        pc_cstr + t_endpos * t_typesize,
                        t_typesize) == 0)
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
    char*   pc_value = NULL;
    char*   pc_string = NULL;

    assert(cpt_basic_string != NULL);

    if(t_pos > basic_string_size(cpt_basic_string))
    {
        return NPOS;
    }

    /* get element */
    t_typesize = cpt_basic_string->_t_vector._t_typesize;
    pc_value = (char*)malloc(t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, t_typesize);
    }

    _get_varg_value(
        pc_value, 
        val_elemlist,
        t_typesize,
        cpt_basic_string->_t_vector._sz_typename);

    /* find elemen */
    t_stringlen = basic_string_length(cpt_basic_string);
    pc_string = (char*)basic_string_at(cpt_basic_string, 0);
    if(cpt_basic_string->_t_vector._pfun_cmp != NULL)
    {
        t_findpos = t_pos;
        while(t_findpos != t_stringlen)
        {
            if(cpt_basic_string->_t_vector._pfun_cmp(
                pc_string + t_findpos * t_typesize, pc_value) == 0)
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
    }
    else
    {
        t_findpos = t_pos;
        while(t_findpos != t_stringlen)
        {
            if(memcmp(pc_string + t_findpos * t_typesize, pc_value, t_typesize) == 0)
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
    }
    free(pc_value);
    pc_value = NULL;

    return t_findpos;
}

size_t basic_string_rfind(
    const basic_string_t* cpt_basic_string,
    const basic_string_t* cpt_basic_string_find,
    size_t t_pos)
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
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring,
    size_t t_pos)
{
    return basic_string_rfind_subcstr(cpt_basic_string, cpv_valuestring, t_pos, NPOS);
}

size_t basic_string_rfind_subcstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring,
    size_t t_pos,
    size_t t_len)
{
    size_t t_typesize = 0;
    size_t t_stringlen = 0;
    size_t t_cstrlen = 0;
    long   l_startpos = 0;
    size_t t_endpos = 0;
    char*  pc_string = NULL;
    char*  pc_cstr = NULL;

    assert(cpt_basic_string != NULL && cpv_valuestring != NULL);

    t_typesize = cpt_basic_string->_t_vector._t_typesize;
    t_stringlen = basic_string_length(cpt_basic_string);
    t_cstrlen = _get_valuestring_len(
        cpv_valuestring, t_typesize, cpt_basic_string->_t_vector._sz_typename);
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
    if(cpt_basic_string->_t_vector._pfun_cmp != NULL)
    {
        l_startpos = t_pos == t_stringlen ? t_pos - 1 : t_pos;
        while(l_startpos >= 0)
        {
            if(cpt_basic_string->_t_vector._pfun_cmp(
                pc_string + l_startpos * t_typesize, pc_cstr) == 0)
            {
                t_endpos = 0;
                while(t_endpos + l_startpos != t_stringlen && t_endpos != t_cstrlen)
                {
                    if(cpt_basic_string->_t_vector._pfun_cmp(
                        pc_string + (t_endpos+l_startpos) * t_typesize,
                        pc_cstr + t_endpos * t_typesize) == 0)
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
                    return l_startpos;
                }
            }

            l_startpos--;
        }

        return NPOS;
    }
    else
    {
        l_startpos = t_pos == t_stringlen ? t_pos - 1 : t_pos;
        while(l_startpos >= 0)
        {
            if(memcmp(pc_string + l_startpos * t_typesize, pc_cstr, t_typesize) == 0)
            {
                t_endpos = 0;
                while(t_endpos + l_startpos != t_stringlen && t_endpos != t_cstrlen)
                {
                    if(memcmp(
                        pc_string + (t_endpos+l_startpos) * t_typesize,
                        pc_cstr + t_endpos * t_typesize,
                        t_typesize) == 0)
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
                    return l_startpos;
                }
            }

            l_startpos--;
        }

        return NPOS;
    }
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
    char*   pc_value = NULL;
    char*   pc_string = NULL;
    long    l_findpos = 0;

    assert(cpt_basic_string != NULL);

    t_stringlen = basic_string_length(cpt_basic_string);
    if(t_pos > t_stringlen)
    {
        t_pos = t_stringlen;
    }

    /* get element */
    t_typesize = cpt_basic_string->_t_vector._t_typesize;
    pc_value = (char*)malloc(t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, t_typesize);
    }

    _get_varg_value(
        pc_value,
        val_elemlist,
        t_typesize,
        cpt_basic_string->_t_vector._sz_typename);

    /* find elemen */
    pc_string = (char*)basic_string_at(cpt_basic_string, 0);
    if(cpt_basic_string->_t_vector._pfun_cmp != NULL)
    {
        l_findpos = t_pos == t_stringlen ? t_pos - 1 : t_pos;
        while(l_findpos >= 0)
        {
            if(cpt_basic_string->_t_vector._pfun_cmp(
                pc_string + l_findpos * t_typesize, pc_value) == 0)
            {
                break;
            }
            else
            {
                l_findpos--;
            }
        }

        if(l_findpos < 0)
        {
            l_findpos = NPOS;
        }
    }
    else
    {
        l_findpos = t_pos == t_stringlen ? t_pos - 1 : t_pos;
        while(l_findpos >= 0)
        {
            if(memcmp(pc_string + l_findpos * t_typesize, pc_value, t_typesize) == 0)
            {
                break;
            }
            else
            {
                l_findpos--;
            }
        }

        if(l_findpos < 0)
        {
            l_findpos = NPOS;
        }
    }
    free(pc_value);
    pc_value = NULL;

    return l_findpos;
}

size_t basic_string_find_first_of(
    const basic_string_t* cpt_basic_string,
    const basic_string_t* cpt_basic_string_find,
    size_t t_pos)
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
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring,
    size_t t_pos)
{
    return basic_string_find_first_of_subcstr(
        cpt_basic_string, cpv_valuestring, t_pos, NPOS);
}

size_t basic_string_find_first_of_subcstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring,
    size_t t_pos,
    size_t t_len)
{
    size_t t_typesize = 0;
    size_t t_stringlen = 0;
    size_t t_cstrlen = 0;
    size_t t_startpos = 0;
    size_t t_endpos = 0;
    char*  pc_string = NULL;
    char*  pc_cstr = NULL;

    assert(cpt_basic_string != NULL && cpv_valuestring != NULL);

    t_typesize = cpt_basic_string->_t_vector._t_typesize;
    t_stringlen = basic_string_length(cpt_basic_string);
    t_cstrlen = _get_valuestring_len(
        cpv_valuestring, t_typesize, cpt_basic_string->_t_vector._sz_typename);
    t_cstrlen = t_len < t_cstrlen ? t_len : t_cstrlen;

    /* find position is beyond the range of cpt_basic_string */
    if(basic_string_empty(cpt_basic_string) ||
       t_pos >= basic_string_size(cpt_basic_string))
    {
        return NPOS;
    }

    pc_string = (char*)basic_string_at(cpt_basic_string, 0);
    pc_cstr = (char*)cpv_valuestring;
    if(cpt_basic_string->_t_vector._pfun_cmp != NULL)
    {
        t_startpos = t_pos;
        while(t_startpos != t_stringlen)
        {
            t_endpos = 0;
            while(t_endpos != t_cstrlen)
            {
                if(cpt_basic_string->_t_vector._pfun_cmp(
                    pc_string + t_startpos * t_typesize,
                    pc_cstr + t_endpos * t_typesize) == 0)
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
    else
    {
        t_startpos = t_pos;
        while(t_startpos != t_stringlen)
        {
            t_endpos = 0;
            while(t_endpos != t_cstrlen)
            {
                if(memcmp(
                    pc_string + t_startpos * t_typesize,
                    pc_cstr + t_endpos * t_typesize,
                    t_typesize) == 0)
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
}

size_t basic_string_find_first_not_of(
    const basic_string_t* cpt_basic_string,
    const basic_string_t* cpt_basic_string_find,
    size_t t_pos)
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
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring,
    size_t t_pos)
{
    return basic_string_find_first_not_of_subcstr(
        cpt_basic_string, cpv_valuestring, t_pos, NPOS);
}

size_t basic_string_find_first_not_of_subcstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring,
    size_t t_pos,
    size_t t_len)
{
    size_t t_typesize = 0;
    size_t t_stringlen = 0;
    size_t t_cstrlen = 0;
    size_t t_startpos = 0;
    size_t t_endpos = 0;
    char*  pc_string = NULL;
    char*  pc_cstr = NULL;

    assert(cpt_basic_string != NULL && cpv_valuestring != NULL);

    t_typesize = cpt_basic_string->_t_vector._t_typesize;
    t_stringlen = basic_string_length(cpt_basic_string);
    t_cstrlen = _get_valuestring_len(
        cpv_valuestring, t_typesize, cpt_basic_string->_t_vector._sz_typename);
    t_cstrlen = t_len < t_cstrlen ? t_len : t_cstrlen;

    /* find position is beyond the range of cpt_basic_string */
    if(basic_string_empty(cpt_basic_string) ||
       t_pos >= basic_string_size(cpt_basic_string))
    {
        return NPOS;
    }

    pc_string = (char*)basic_string_at(cpt_basic_string, 0);
    pc_cstr = (char*)cpv_valuestring;
    if(cpt_basic_string->_t_vector._pfun_cmp != NULL)
    {
        t_startpos = t_pos;
        while(t_startpos != t_stringlen)
        {
            t_endpos = 0;
            while(t_endpos != t_cstrlen)
            {
                if(cpt_basic_string->_t_vector._pfun_cmp(
                    pc_string + t_startpos * t_typesize,
                    pc_cstr + t_endpos * t_typesize) == 0)
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
    else
    {
        t_startpos = t_pos;
        while(t_startpos != t_stringlen)
        {
            t_endpos = 0;
            while(t_endpos != t_cstrlen)
            {
                if(memcmp(
                    pc_string + t_startpos * t_typesize,
                    pc_cstr + t_endpos * t_typesize,
                    t_typesize) == 0)
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
    char*   pc_value = NULL;
    char*   pc_string = NULL;

    assert(cpt_basic_string != NULL);

    if(t_pos > basic_string_size(cpt_basic_string))
    {
        return NPOS;
    }

    /* get element */
    t_typesize = cpt_basic_string->_t_vector._t_typesize;
    pc_value = (char*)malloc(t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, t_typesize);
    }

    _get_varg_value(
        pc_value,
        val_elemlist,
        t_typesize,
        cpt_basic_string->_t_vector._sz_typename);

    /* find elemen */
    t_stringlen = basic_string_length(cpt_basic_string);
    pc_string = (char*)basic_string_at(cpt_basic_string, 0);
    if(cpt_basic_string->_t_vector._pfun_cmp != NULL)
    {
        t_findpos = t_pos;
        while(t_findpos != t_stringlen)
        {
            if(cpt_basic_string->_t_vector._pfun_cmp(
                pc_string + t_findpos * t_typesize, pc_value) != 0)
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
    }
    else
    {
        t_findpos = t_pos;
        while(t_findpos != t_stringlen)
        {
            if(memcmp(pc_string + t_findpos * t_typesize, pc_value, t_typesize) != 0)
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
    }
    free(pc_value);
    pc_value = NULL;

    return t_findpos;
}

size_t basic_string_find_last_of(
    const basic_string_t* cpt_basic_string,
    const basic_string_t* cpt_basic_string_find,
    size_t t_pos)
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
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring,
    size_t t_pos)
{
    return basic_string_find_last_of_subcstr(
        cpt_basic_string, cpv_valuestring, t_pos, NPOS);
}

size_t basic_string_find_last_of_subcstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring,
    size_t t_pos,
    size_t t_len)
{
    size_t t_typesize = 0;
    size_t t_stringlen = 0;
    size_t t_cstrlen = 0;
    long   l_startpos = 0;
    size_t t_endpos = 0;
    char*  pc_string = NULL;
    char*  pc_cstr = NULL;

    assert(cpt_basic_string != NULL && cpv_valuestring != NULL);

    t_typesize = cpt_basic_string->_t_vector._t_typesize;
    t_stringlen = basic_string_length(cpt_basic_string);
    t_cstrlen = _get_valuestring_len(
        cpv_valuestring, t_typesize, cpt_basic_string->_t_vector._sz_typename);
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
    if(cpt_basic_string->_t_vector._pfun_cmp != NULL)
    {
        l_startpos = t_pos == t_stringlen ? t_pos - 1 : t_pos;
        while(l_startpos >= 0)
        {
            t_endpos = 0;
            while(t_endpos != t_cstrlen)
            {
                if(cpt_basic_string->_t_vector._pfun_cmp(
                    pc_string + l_startpos * t_typesize,
                    pc_cstr + t_endpos * t_typesize) == 0)
                {
                    return l_startpos;
                }
                else
                {
                    t_endpos++;
                }
            }

            l_startpos--;
        }

        return NPOS;
    }
    else
    {
        l_startpos = t_pos == t_stringlen ? t_pos - 1 : t_pos;
        while(l_startpos >= 0)
        {
            t_endpos = 0;
            while(t_endpos != t_cstrlen)
            {
                if(memcmp(
                    pc_string + l_startpos * t_typesize,
                    pc_cstr + t_endpos * t_typesize,
                    t_typesize) == 0)
                {
                    return l_startpos;
                }
                else
                {
                    t_endpos++;
                }
            }

            l_startpos--;
        }

        return NPOS;
    }
}

size_t basic_string_find_last_not_of(
    const basic_string_t* cpt_basic_string,
    const basic_string_t* cpt_basic_string_find,
    size_t t_pos)
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
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring,
    size_t t_pos)
{
    return basic_string_find_last_not_of_subcstr(
        cpt_basic_string, cpv_valuestring, t_pos, NPOS);
}

size_t basic_string_find_last_not_of_subcstr(
    const basic_string_t* cpt_basic_string,
    const void* cpv_valuestring,
    size_t t_pos,
    size_t t_len)
{
    size_t t_typesize = 0;
    size_t t_stringlen = 0;
    size_t t_cstrlen = 0;
    long   l_startpos = 0;
    size_t t_endpos = 0;
    char*  pc_string = NULL;
    char*  pc_cstr = NULL;

    assert(cpt_basic_string != NULL && cpv_valuestring != NULL);

    t_typesize = cpt_basic_string->_t_vector._t_typesize;
    t_stringlen = basic_string_length(cpt_basic_string);
    t_cstrlen = _get_valuestring_len(
        cpv_valuestring, t_typesize, cpt_basic_string->_t_vector._sz_typename);
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
    if(cpt_basic_string->_t_vector._pfun_cmp != NULL)
    {
        l_startpos = t_pos == t_stringlen ? t_pos - 1 : t_pos;
        while(l_startpos >= 0)
        {
            t_endpos = 0;
            while(t_endpos != t_cstrlen)
            {
                if(cpt_basic_string->_t_vector._pfun_cmp(
                    pc_string + l_startpos * t_typesize,
                    pc_cstr + t_endpos * t_typesize) == 0)
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
                return l_startpos;
            }
            else
            {
                l_startpos--;
            }
        }

        return NPOS;
    }
    else
    {
        l_startpos = t_pos == t_stringlen ? t_pos - 1 : t_pos;
        while(l_startpos >= 0)
        {
            t_endpos = 0;
            while(t_endpos != t_cstrlen)
            {
                if(memcmp(
                    pc_string + l_startpos * t_typesize,
                    pc_cstr + t_endpos * t_typesize,
                    t_typesize) == 0)
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
                return l_startpos;
            }
            else
            {
                l_startpos--;
            }
        }

        return NPOS;
    }
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
    char*   pc_value = NULL;
    char*   pc_string = NULL;
    long    l_findpos = 0;

    assert(cpt_basic_string != NULL);

    t_stringlen = basic_string_length(cpt_basic_string);
    if(t_pos > t_stringlen)
    {
        t_pos = t_stringlen;
    }

    /* get element */
    t_typesize = cpt_basic_string->_t_vector._t_typesize;
    pc_value = (char*)malloc(t_typesize);
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_value, 0x00, t_typesize);
    }

    _get_varg_value(
        pc_value,
        val_elemlist,
        t_typesize,
        cpt_basic_string->_t_vector._sz_typename);

    /* find elemen */
    pc_string = (char*)basic_string_at(cpt_basic_string, 0);
    if(cpt_basic_string->_t_vector._pfun_cmp != NULL)
    {
        l_findpos = t_pos == t_stringlen ? t_pos - 1 : t_pos;
        while(l_findpos >= 0)
        {
            if(cpt_basic_string->_t_vector._pfun_cmp(
                pc_string + l_findpos * t_typesize, pc_value) != 0)
            {
                break;
            }
            else
            {
                l_findpos--;
            }
        }

        if(l_findpos < 0)
        {
            l_findpos = NPOS;
        }
    }
    else
    {
        l_findpos = t_pos == t_stringlen ? t_pos - 1 : t_pos;
        while(l_findpos >= 0)
        {
            if(memcmp(pc_string + l_findpos * t_typesize, pc_value, t_typesize) != 0)
            {
                break;
            }
            else
            {
                l_findpos--;
            }
        }

        if(l_findpos < 0)
        {
            l_findpos = NPOS;
        }
    }
    free(pc_value);
    pc_value = NULL;

    return l_findpos;
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

void basic_string_reserve(
    basic_string_t* pt_basic_string, size_t t_reservesize)
{
    assert(pt_basic_string != NULL);

    vector_reserve(&pt_basic_string->_t_vector, t_reservesize+1);
}

void _basic_string_resize(
    basic_string_t* pt_basic_string, size_t t_resize, ...)
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

void _basic_string_push_back_varg(
    basic_string_t* pt_basic_string, va_list val_elemlist)
{
    char*   pc_nullterminated = NULL;
    char*   pc_value = NULL;
    char*   pc_dest = NULL;
    size_t  t_typesize = 0;

    assert(pt_basic_string != NULL);

    t_typesize = pt_basic_string->_t_vector._t_typesize;
    pc_nullterminated = (char*)malloc(t_typesize);
    pc_value = (char*)malloc(t_typesize);
    if(pc_nullterminated == NULL || pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        memset(pc_nullterminated, 0x00, t_typesize);
    }
    _get_varg_value(
        pc_value,
        val_elemlist,
        t_typesize,
        pt_basic_string->_t_vector._sz_typename);

    if(memcmp(pc_nullterminated, pc_value, t_typesize) != 0)
    {
        pc_dest = vector_at(
            &pt_basic_string->_t_vector, basic_string_size(pt_basic_string));
        assert(pc_value != NULL);

        memcpy(pc_dest, pc_value, t_typesize);
        vector_push_back(&pt_basic_string->_t_vector, 0x00);
    }

    free(pc_nullterminated);
    free(pc_value);
    pc_nullterminated = NULL;
    pc_value = NULL;
}

void basic_string_assign(
    basic_string_t* pt_basic_string, const basic_string_t* cpt_basic_string_assign)
{
    assert(_same_basic_string_type(pt_basic_string, cpt_basic_string_assign));

    basic_string_destroy(pt_basic_string);
    basic_string_init_copy(pt_basic_string, cpt_basic_string_assign);
}

void basic_string_assign_substring(
    basic_string_t* pt_basic_string,
    const basic_string_t* cpt_basic_string_assign,
    size_t t_pos,
    size_t t_len)
{
    assert(_same_basic_string_type(pt_basic_string, cpt_basic_string_assign));

    basic_string_destroy(pt_basic_string);
    basic_string_init_copy_substring(
        pt_basic_string, cpt_basic_string_assign, t_pos, t_len);
}

void basic_string_assign_cstr(
    basic_string_t* pt_basic_string,
    const void* cpv_valuestring)
{
    basic_string_assign_subcstr(pt_basic_string, cpv_valuestring, NPOS);
}

void basic_string_assign_subcstr(
    basic_string_t* pt_basic_string,
    const void* cpv_valuestring,
    size_t t_len)
{
    int (*pfun_cmp)(const void*, const void*);
    void (*pfun_destroy_elem)(void*);

    assert(pt_basic_string != NULL && cpv_valuestring != NULL);

    /* same compare and destroy function */
    pfun_cmp = pt_basic_string->_t_vector._pfun_cmp;
    pfun_destroy_elem = NULL;
    /* destroy the basic_string */
    basic_string_destroy(pt_basic_string);
    /* initialize basic_string with value string */
    basic_string_init_subcstr(pt_basic_string, cpv_valuestring, t_len);
}

void basic_string_assign_range(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end)
{
    assert(
        _GET_BASIC_STRING_CONTAINER(&t_begin) != pt_basic_string &&
        _GET_BASIC_STRING_CONTAINER(&t_end) != pt_basic_string);
    assert(
        _same_basic_string_type(pt_basic_string, _GET_BASIC_STRING_CONTAINER(&t_begin)) &&
        _same_basic_string_type(pt_basic_string, _GET_BASIC_STRING_CONTAINER(&t_end)));

    basic_string_destroy(pt_basic_string);
    basic_string_init_copy_range(pt_basic_string, t_begin, t_end);
}

void _basic_string_assign_elem(
    basic_string_t* pt_basic_string,
    size_t t_count,
    ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_count);
    _basic_string_assign_elem_varg(pt_basic_string, t_count, val_elemlist);
}

void _basic_string_assign_elem_varg(
    basic_string_t* pt_basic_string,
    size_t t_count,
    va_list val_elemlist)
{
    int (*pfun_cmp)(const void*, const void*);
    void (*pfun_destroy_elem)(void*);
    size_t  t_index = 0;

    assert(pt_basic_string != NULL);

    /* same compare and destroy function */
    pfun_cmp = pt_basic_string->_t_vector._pfun_cmp;
    pfun_destroy_elem = NULL;

    /* destroy basic_string */
    basic_string_destroy(pt_basic_string);

    /* initialize basic_string */
    vector_init(&pt_basic_string->_t_vector);
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
    basic_string_t* pt_basic_string,
    const basic_string_t* cpt_basic_string_append)
{
    basic_string_append_substring(pt_basic_string, cpt_basic_string_append, 0, NPOS);
}

void basic_string_append_substring(
    basic_string_t* pt_basic_string,
    const basic_string_t* cpt_basic_string_append,
    size_t t_pos,
    size_t t_len)
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
    basic_string_t* pt_basic_string,
    const void* cpv_valuestring)
{
    basic_string_append_subcstr(pt_basic_string, cpv_valuestring, NPOS);
}

void basic_string_append_subcstr(
    basic_string_t* pt_basic_string,
    const void* cpv_valuestring,
    size_t t_len)
{
    size_t t_typesize = 0;
    size_t t_cstrlen = 0;
    size_t t_stringlen = 0;
    char*  pc_value = NULL;

    assert(pt_basic_string != NULL && cpv_valuestring != NULL);

    t_typesize = pt_basic_string->_t_vector._t_typesize;
    t_stringlen = basic_string_length(pt_basic_string);
    t_cstrlen = _get_valuestring_len(
        cpv_valuestring, t_typesize, pt_basic_string->_t_vector._sz_typename);
    t_len = t_len < t_cstrlen ? t_len : t_cstrlen;

    if(t_len > 0)
    {
        basic_string_resize(pt_basic_string, t_stringlen + t_len, 0xcc);
        pc_value = (char*)basic_string_at(pt_basic_string, t_stringlen);
        assert(pc_value != NULL);
        memcpy(pc_value, (char*)cpv_valuestring, t_len * t_typesize);
    }
}

void basic_string_append_range(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end)
{
    assert(
        _GET_BASIC_STRING_CONTAINER(&t_begin) != pt_basic_string &&
        _GET_BASIC_STRING_CONTAINER(&t_end) != pt_basic_string);
    assert(
        _same_basic_string_type(pt_basic_string, _GET_BASIC_STRING_CONTAINER(&t_begin)) &&
        _same_basic_string_type(pt_basic_string, _GET_BASIC_STRING_CONTAINER(&t_end)));

    basic_string_append_subcstr(
        pt_basic_string, 
        iterator_get_pointer(&t_begin), 
        iterator_distance(t_begin, t_end));
}

void _basic_string_append_elem(
    basic_string_t* pt_basic_string,
    size_t t_count,
    ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_count);
    _basic_string_append_elem_varg(pt_basic_string, t_count, val_elemlist);
}

void _basic_string_append_elem_varg(
    basic_string_t* pt_basic_string,
    size_t t_count,
    va_list val_elemlist)
{
    _basic_string_resize_varg(
        pt_basic_string, basic_string_size(pt_basic_string) + t_count, val_elemlist);
}

/* insert */
basic_string_iterator_t _basic_string_insert(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_pos,
    ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_pos);
    return _basic_string_insert_n_varg(pt_basic_string, t_pos, 1, val_elemlist);
}

basic_string_iterator_t _basic_string_insert_n(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_pos,
    size_t t_count,
    ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_count);
    return _basic_string_insert_n_varg(pt_basic_string, t_pos, t_count, val_elemlist);
}

basic_string_iterator_t _basic_string_insert_n_varg(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_pos,
    size_t t_count,
    va_list val_elemlist)
{
    assert(pt_basic_string != NULL);

    return _vector_insert_n_varg(
        &pt_basic_string->_t_vector, t_pos, t_count, val_elemlist);
}

void basic_string_insert_string(
    basic_string_t* pt_basic_string,
    size_t t_pos,
    const basic_string_t* cpt_basic_string_insert)
{
    basic_string_iterator_t t_insert = basic_string_begin(pt_basic_string);

    assert(t_pos <= basic_string_size(pt_basic_string));

    if(t_pos != 0)
    {
        iterator_next_n(&t_insert, t_pos);
    }

    basic_string_insert_range(
        pt_basic_string, 
        t_insert, 
        basic_string_begin(cpt_basic_string_insert),
        basic_string_end(cpt_basic_string_insert));
}

void basic_string_insert_substring(
    basic_string_t* pt_basic_string,
    size_t t_pos,
    const basic_string_t* cpt_basic_string_insert,
    size_t t_startpos,
    size_t t_len)
{
    basic_string_iterator_t t_insert = basic_string_begin(pt_basic_string);
    basic_string_iterator_t t_begin  = basic_string_begin(cpt_basic_string_insert);
    basic_string_iterator_t t_end    = basic_string_begin(cpt_basic_string_insert);

    if(t_pos != 0)
    {
        iterator_next_n(&t_insert, t_pos);
    }
    if(t_startpos != 0)
    {
        iterator_next_n(&t_begin, t_startpos);
    }
    if(t_len == NPOS ||
       t_startpos + t_len >= basic_string_size(cpt_basic_string_insert))
    {
        t_end = basic_string_end(cpt_basic_string_insert);
    }
    else
    {
        iterator_next_n(&t_end, t_startpos + t_len);
    }

    basic_string_insert_range(pt_basic_string, t_insert, t_begin, t_end);
}

void basic_string_insert_cstr(
    basic_string_t* pt_basic_string,
    size_t t_pos,
    const void* cpv_valuestring)
{
    basic_string_insert_subcstr(pt_basic_string, t_pos, cpv_valuestring, NPOS);
}

void basic_string_insert_subcstr(
    basic_string_t* pt_basic_string,
    size_t t_pos,
    const void* cpv_valuestring,
    size_t t_len)
{
    basic_string_t t_string;

    assert(pt_basic_string != NULL && cpv_valuestring != NULL);

    t_string = _create_basic_string(
        pt_basic_string->_t_vector._t_typesize, 
        pt_basic_string->_t_vector._sz_typename);
    /* unify the type name */
    memcpy(
        t_string._t_vector._sz_typename, 
        pt_basic_string->_t_vector._sz_typename,
        _ELEM_TYPE_NAME_SIZE);

    basic_string_init_subcstr(&t_string, cpv_valuestring, t_len);

    basic_string_insert_string(pt_basic_string, t_pos, &t_string);

    basic_string_destroy(&t_string);
}

void basic_string_insert_range(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_pos,
    basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end)
{
    assert(
        _GET_BASIC_STRING_CONTAINER(&t_begin) != pt_basic_string &&
        _GET_BASIC_STRING_CONTAINER(&t_end) != pt_basic_string &&
        _GET_BASIC_STRING_CONTAINER(&t_pos) == pt_basic_string);
    assert(
        _same_basic_string_type(pt_basic_string, _GET_BASIC_STRING_CONTAINER(&t_begin)) &&
        _same_basic_string_type(pt_basic_string, _GET_BASIC_STRING_CONTAINER(&t_end)));

    _GET_VECTOR_CONTAINER_TYPE(&t_begin) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE(&t_end) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE(&t_pos) = _VECTOR_CONTAINER;

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
    basic_string_t* pt_basic_string,
    size_t t_pos,
    size_t t_count,
    va_list val_elemlist)
{
    basic_string_iterator_t t_insert;

    assert(pt_basic_string != NULL);
    assert(t_pos <= basic_string_size(pt_basic_string));

    t_insert = basic_string_begin(pt_basic_string);
    iterator_next_n(&t_insert, t_pos);
    _GET_VECTOR_CONTAINER_TYPE(&t_insert) = _VECTOR_CONTAINER;
    _vector_insert_n_varg(
        &pt_basic_string->_t_vector, t_insert, t_count, val_elemlist);
}

/* erase */
basic_string_iterator_t basic_string_erase(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_pos)
{
    basic_string_iterator_t t_iterator;

    assert(_iterator_belong_to_basic_string(pt_basic_string, &t_pos));
    assert(!iterator_equal(&t_pos, basic_string_end(pt_basic_string)));

    _GET_VECTOR_CONTAINER_TYPE(&t_pos) = _VECTOR_CONTAINER;

    t_iterator = vector_erase(&pt_basic_string->_t_vector, t_pos);
    _GET_BASIC_STRING_CONTAINER_TYPE(&t_iterator) = _BASIC_STRING_CONTAINER;

    return t_iterator;
}

basic_string_iterator_t basic_string_erase_range(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end)
{
    basic_string_iterator_t t_iterator;

    assert(
        _iterator_belong_to_basic_string(pt_basic_string, &t_begin) &&
        _iterator_belong_to_basic_string(pt_basic_string, &t_end));

    _GET_VECTOR_CONTAINER_TYPE(&t_begin) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE(&t_end) = _VECTOR_CONTAINER;

    t_iterator = vector_erase_range(&pt_basic_string->_t_vector, t_begin, t_end);
    _GET_BASIC_STRING_CONTAINER_TYPE(&t_iterator) = _BASIC_STRING_CONTAINER;

    return t_iterator;
}

void basic_string_erase_substring(
    basic_string_t* pt_basic_string,
    size_t t_pos,
    size_t t_len)
{
    basic_string_iterator_t t_begin = basic_string_begin(pt_basic_string);
    basic_string_iterator_t t_end   = basic_string_begin(pt_basic_string);

    assert(t_pos < basic_string_size(pt_basic_string));

    if(t_pos != 0)
    {
        iterator_next_n(&t_begin, t_pos);
    }
    if(t_len == NPOS || t_pos + t_len >= basic_string_size(pt_basic_string))
    {
        t_end = basic_string_end(pt_basic_string);
    }
    else
    {
        iterator_next_n(&t_end, t_pos + t_len);
    }

    basic_string_erase_range(pt_basic_string, t_begin, t_end);
}

/* replace */
void basic_string_replace(
    basic_string_t* pt_basic_string,
    size_t t_pos,
    size_t t_len,
    const basic_string_t* cpt_basic_string_replace)
{
    basic_string_iterator_t t_begin = basic_string_begin(pt_basic_string);
    basic_string_iterator_t t_end   = basic_string_begin(pt_basic_string);

    assert(t_pos < basic_string_size(pt_basic_string));

    iterator_next_n(&t_begin, t_pos);
    if(t_len == NPOS || t_pos + t_len >= basic_string_size(pt_basic_string))
    {
        t_end = basic_string_end(pt_basic_string);
    }
    else
    {
        iterator_next_n(&t_end, t_pos + t_len);
    }

    basic_string_range_replace(
        pt_basic_string, t_begin, t_end, cpt_basic_string_replace);
}

void basic_string_replace_substring(
    basic_string_t* pt_basic_string,
    size_t t_pos,
    size_t t_len,
    const basic_string_t* cpt_basic_string_replace,
    size_t t_position,
    size_t t_length)
{
    basic_string_iterator_t t_begin = basic_string_begin(pt_basic_string);
    basic_string_iterator_t t_end   = basic_string_begin(pt_basic_string);

    assert(t_pos < basic_string_size(pt_basic_string));

    iterator_next_n(&t_begin, t_pos);
    if(t_len == NPOS || t_pos + t_len >= basic_string_size(pt_basic_string))
    {
        t_end = basic_string_end(pt_basic_string);
    }
    else
    {
        iterator_next_n(&t_end, t_pos + t_len);
    }

    basic_string_range_replace_substring(
        pt_basic_string, t_begin, t_end, 
        cpt_basic_string_replace, t_position, t_length);
}

void basic_string_replace_cstr(
    basic_string_t* pt_basic_string,
    size_t t_pos,
    size_t t_len,
    const void* cpv_valuestring)
{
    basic_string_iterator_t t_begin = basic_string_begin(pt_basic_string);
    basic_string_iterator_t t_end   = basic_string_begin(pt_basic_string);

    assert(t_pos < basic_string_size(pt_basic_string));

    iterator_next_n(&t_begin, t_pos);
    if(t_len == NPOS || t_pos + t_len >= basic_string_size(pt_basic_string))
    {
        t_end = basic_string_end(pt_basic_string);
    }
    else
    {
        iterator_next_n(&t_end, t_pos + t_len);
    }

    basic_string_range_replace_cstr(
        pt_basic_string, t_begin, t_end, cpv_valuestring);
}

void basic_string_replace_subcstr(
    basic_string_t* pt_basic_string,
    size_t t_pos,
    size_t t_len,
    const void* cpv_valuestring,
    size_t t_length)
{
    basic_string_iterator_t t_begin = basic_string_begin(pt_basic_string);
    basic_string_iterator_t t_end   = basic_string_begin(pt_basic_string);

    assert(t_pos < basic_string_size(pt_basic_string));

    iterator_next_n(&t_begin, t_pos);
    if(t_len == NPOS || t_pos + t_len >= basic_string_size(pt_basic_string))
    {
        t_end = basic_string_end(pt_basic_string);
    }
    else
    {
        iterator_next_n(&t_end, t_pos + t_len);
    }

    basic_string_range_replace_subcstr(
        pt_basic_string, t_begin, t_end, cpv_valuestring, t_length);
}

void _basic_string_replace_elem(
    basic_string_t* pt_basic_string,
    size_t t_pos,
    size_t t_len,
    size_t t_count,
    ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_count);
    _basic_string_replace_elem_varg(
        pt_basic_string, t_pos, t_len, t_count, val_elemlist);
}

void _basic_string_replace_elem_varg(
    basic_string_t* pt_basic_string,
    size_t t_pos,
    size_t t_len,
    size_t t_count,
    va_list val_elemlist)
{
    basic_string_iterator_t t_begin = basic_string_begin(pt_basic_string);
    basic_string_iterator_t t_end   = basic_string_begin(pt_basic_string);

    assert(t_pos < basic_string_size(pt_basic_string));

    iterator_next_n(&t_begin, t_pos);
    if(t_len == NPOS || t_pos + t_len >= basic_string_size(pt_basic_string))
    {
        t_end = basic_string_end(pt_basic_string);
    }
    else
    {
        iterator_next_n(&t_end, t_pos + t_len);
    }
    _basic_string_range_replace_elem_varg(
        pt_basic_string, t_begin, t_end, t_count, val_elemlist);
}

void basic_string_range_replace(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end,
    const basic_string_t* cpt_basic_string_replace)
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
    basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end,
    const basic_string_t* cpt_basic_string_replace,
    size_t t_pos,
    size_t t_len)
{
    basic_string_iterator_t t_iterator = 
        basic_string_erase_range(pt_basic_string, t_begin, t_end);
    basic_string_insert_substring(
        pt_basic_string,
        iterator_distance(basic_string_begin(pt_basic_string), t_iterator),
        cpt_basic_string_replace,
        t_pos,
        t_len);
}

void basic_string_range_replace_cstr(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end,
    const void* cpv_valuestring)
{
    basic_string_iterator_t t_iterator = 
        basic_string_erase_range(pt_basic_string, t_begin, t_end);
    basic_string_insert_cstr(
        pt_basic_string,
        iterator_distance(basic_string_begin(pt_basic_string), t_iterator),
        cpv_valuestring);
}

void basic_string_range_replace_subcstr(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end,
    const void* cpv_valuestring,
    size_t t_len)
{
    basic_string_iterator_t t_iterator = 
        basic_string_erase_range(pt_basic_string, t_begin, t_end);
    basic_string_insert_subcstr(
        pt_basic_string,
        iterator_distance(basic_string_begin(pt_basic_string), t_iterator),
        cpv_valuestring,
        t_len);
}

void _basic_string_range_replace_elem(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end,
    size_t t_count,
    ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_count);
    _basic_string_range_replace_elem_varg(
        pt_basic_string, t_begin, t_end, t_count, val_elemlist);
}

void _basic_string_range_replace_elem_varg(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end,
    size_t t_count,
    va_list val_elemlist)
{
    basic_string_iterator_t t_iterator = basic_string_erase_range(
        pt_basic_string, t_begin, t_end);
    size_t t_pos = (size_t)iterator_distance(
        basic_string_begin(pt_basic_string), t_iterator);

    _basic_string_insert_elem_varg(pt_basic_string, t_pos, t_count, val_elemlist);
}

void basic_string_replace_range(
    basic_string_t* pt_basic_string,
    basic_string_iterator_t t_begin,
    basic_string_iterator_t t_end,
    basic_string_iterator_t t_first,
    basic_string_iterator_t t_last)
{
    basic_string_iterator_t t_iterator = 
        basic_string_erase_range(pt_basic_string, t_begin, t_end);
    basic_string_insert_range(pt_basic_string, t_iterator, t_first, t_last);
}

/** local function implementation section **/
#ifndef NDEBUG
static bool_t _iterator_belong_to_basic_string(
    const basic_string_t* cpt_basic_string,
    const basic_string_iterator_t* cpt_iterator)
{
    assert(cpt_basic_string != NULL && cpt_iterator != NULL);
    assert(
        _GET_BASIC_STRING_CONTAINER_TYPE(cpt_iterator) == _BASIC_STRING_CONTAINER &&
        _GET_BASIC_STRING_ITERATOR_TYPE(cpt_iterator) == _RANDOM_ACCESS_ITERATOR &&
        _GET_BASIC_STRING_CONTAINER(cpt_iterator) == cpt_basic_string);

    return true;
}

static bool_t _same_basic_string_type(
    const basic_string_t* cpt_basic_stringfirst,
    const basic_string_t* cpt_basic_stringsecond)
{
    assert(cpt_basic_stringfirst != NULL && cpt_basic_stringsecond != NULL);
    assert(
        cpt_basic_stringfirst->_t_vector._t_typesize ==
            cpt_basic_stringsecond->_t_vector._t_typesize &&
        strncmp(
            cpt_basic_stringfirst->_t_vector._sz_typename,
            cpt_basic_stringsecond->_t_vector._sz_typename,
            _ELEM_TYPE_NAME_SIZE) == 0);
    assert(
        cpt_basic_stringfirst->_t_vector._pfun_cmp ==
            cpt_basic_stringsecond->_t_vector._pfun_cmp);

    return true;
}
#endif /* NDEBUG */

static size_t _get_valuestring_len(
    const void* cpv_valuestring, size_t t_typesize, const char* s_typename)
{
    char ac_basicstringtypename[_ELEM_TYPE_NAME_SIZE+1];

    assert(cpv_valuestring != NULL && s_typename != NULL && t_typesize > 0);

    /* special handle for char */
    memset(ac_basicstringtypename, '\0', _ELEM_TYPE_NAME_SIZE+1);
    strncpy(ac_basicstringtypename, _BASIC_STRING_IDENTIFY, _ELEM_TYPE_NAME_SIZE);
    strcat(ac_basicstringtypename, _BASIC_STRING_LEFT_BRACKET);
    strcat(ac_basicstringtypename, _CHAR_TYPE);
    strcat(ac_basicstringtypename, _BASIC_STRING_RIGHT_BRACKET);

    /* char type */
    if(strncmp(ac_basicstringtypename, s_typename, _ELEM_TYPE_NAME_SIZE) == 0)
    {
        assert(t_typesize == 1);
        return strlen(cpv_valuestring);
    }
    else
    {
        size_t t_len = 0;
        char*  pc_nullterminated = NULL;

        pc_nullterminated = (char*)malloc(t_typesize);
        if(pc_nullterminated == NULL)
        {
            fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            memset(pc_nullterminated, 0x00, t_typesize);
        }

        while(memcmp(
            (char*)cpv_valuestring + t_len * t_typesize, 
            pc_nullterminated, 
            t_typesize) != 0)
        {
            t_len++;
        }
        
        free(pc_nullterminated);
        pc_nullterminated = NULL;

        return t_len;
    }
}

/** eof **/

